#include "D3DApp.h"

#include "Engine/GameTimer.h"
#include "Engine/Component/RenderComponent.h"
#include "Engine/ComponentManager/RenderManager.h"
#include "Engine/ComponentManager/ComponentManager.h"
#include "Window/Window.h"	
#include "Engine/Engine.h"
#include "Engine/GameObject.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"
#include "Engine/Component/Transform.h"
#include "Shaders/DDSTextureLoader.h"
#include "DirectXCollision.h"
#include "Shaders/Shader.h"


D3DApp* D3DApp::mInstance = nullptr;


D3DApp* D3DApp::GetInstance()
{
	if (mInstance == nullptr) {
		mInstance = new D3DApp(Window::GetHWND());
		mInstance->Init();
	}
	return mInstance;
}

D3DApp::D3DApp(HWND wH)
{
#if defined(DEBUG) || defined(_DEBUG)
	DebugLayer();
#endif

	mWindow = wH;

	mDebugController = nullptr;

	mD3dDevice = nullptr;
	mDxgiFactory = nullptr;
	mWarpAdapter = nullptr;

	mFence = nullptr;
	mRtvDescriptorSize = 0;
	mDsvDescriptorSize = 0;
	mCbvSrvDescriptorSize = 0;

	mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	m4XMsaaQuality = 0;
	m4XMsaaState = false;

	mCommandList = nullptr;
	mCommandQueue = nullptr;
	mDirectCmdListAlloc = nullptr;

	mSwapChain = nullptr;
	mCurrBackBuffer = 0;

	mRtvHeap = nullptr;
	mDsvHeap = nullptr;
	mCbvHeap = nullptr;

	mDepthStencilBuffer = nullptr;
	mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
}

D3DApp::~D3DApp()
{
	RELPTRDX(mDepthStencilBuffer);

	RELPTRDX(mCbvHeap);
	RELPTRDX(mDsvHeap);
	RELPTRDX(mRtvHeap);

	for (auto sw : mSwapChainBuffer)
		RELPTRDX(sw);

	mSwapChain->SetFullscreenState(false, 0);
	RELPTRDX(mSwapChain);

	RELPTRDX(mCommandQueue);
	RELPTRDX(mCommandList);
	RELPTRDX(mDirectCmdListAlloc);

	RELPTRDX(mFence);

	RELPTRDX(mWarpAdapter);
	RELPTRDX(mD3dDevice);
	RELPTRDX(mDxgiFactory);


	RELPTRDX(mDebugController);

	//RELPTR(mInstance);
	//RELPTR(mWindow);
}

void D3DApp::DebugLayer()
{
	D3D12GetDebugInterface(IID_PPV_ARGS(&mDebugController));
	mDebugController->EnableDebugLayer();
}

#pragma region Initializing fonctions

void D3DApp::Init()
{
	RECT r;
	GetClientRect(mWindow, &r);
	mClientWidth = r.right - r.left;
	mClientHeight = r.bottom - r.top;

	CreateFactoryAndDevice();

	CreateFenceAndDescSize();
	CheckMSAASupport();
	CreateCommandObjects();
	CreateSwapChain();
	
	mDirectCmdListAlloc->Reset();
	mCommandList->Reset(mDirectCmdListAlloc, nullptr);

	CreateDescriptorHeaps();
	CreateRTV();
	CreateDepthStencil();
	CreateViewPortAndScissorRect();

	mCommandList->Close();
	ID3D12CommandList* cmdLists3[] = { mCommandList };
	mCommandQueue->ExecuteCommandLists(_countof(cmdLists3), cmdLists3);
	FlushCommandQueue();
}

void D3DApp::CreateFactoryAndDevice()
{
	CreateDXGIFactory1(IID_PPV_ARGS(&mDxgiFactory));

	HRESULT hResult = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&mD3dDevice));

	if (FAILED(hResult))
	{
		mDxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&mWarpAdapter));
		D3D12CreateDevice(mWarpAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&mD3dDevice));
	}

	ID3D12InfoQueue* infoQueue = nullptr;
	mD3dDevice->QueryInterface(IID_PPV_ARGS(&infoQueue));
	infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
	infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
	infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, false);
}

void D3DApp::CreateFenceAndDescSize()
{
	mD3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence));

	mRtvDescriptorSize = mD3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	mDsvDescriptorSize = mD3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	mCbvSrvDescriptorSize = mD3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void D3DApp::CheckMSAASupport()
{
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;

	msQualityLevels.Format = mBackBufferFormat;
	msQualityLevels.SampleCount = 4;
	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msQualityLevels.NumQualityLevels = 0;

	mD3dDevice->CheckFeatureSupport(
		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
		&msQualityLevels,
		sizeof(msQualityLevels));

	m4XMsaaQuality = msQualityLevels.NumQualityLevels;
	assert(m4XMsaaQuality > 0 && "MSAA Quality level should be greater than 0");
}

void D3DApp::CreateCommandObjects()
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	mD3dDevice->CreateCommandQueue(
		&queueDesc, IID_PPV_ARGS(&mCommandQueue));

	mD3dDevice->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&mDirectCmdListAlloc));

	mD3dDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		mDirectCmdListAlloc, // Associated command allocator
		nullptr, // Initial PipelineStateObject
		IID_PPV_ARGS(&mCommandList));

	mCommandList->Close();
}

void D3DApp::CreateSwapChain()
{
	// Release the previous swapchain we will be recreating.
	if (mSwapChain != nullptr) mSwapChain->Release();

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferDesc.Width = mClientWidth;
	sd.BufferDesc.Height = mClientHeight;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Format = mBackBufferFormat;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.SampleDesc.Count = m4XMsaaState ? 4 : 1;
	sd.SampleDesc.Quality = m4XMsaaState ? (m4XMsaaQuality - 1) : 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = SwapChainBufferCount;
	sd.OutputWindow = mWindow;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	// Note: Swap chain uses queue to perform flush.
	mDxgiFactory->CreateSwapChain(
		mCommandQueue,
		&sd,
		&mSwapChain);
}

void D3DApp::CreateDescriptorHeaps()
{
	D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc;
	rtvHeapDesc.NumDescriptors = SwapChainBufferCount;
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	rtvHeapDesc.NodeMask = 0;
	mD3dDevice->CreateDescriptorHeap(
		&rtvHeapDesc, IID_PPV_ARGS(&mRtvHeap));

	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;
	mD3dDevice->CreateDescriptorHeap(
		&dsvHeapDesc, IID_PPV_ARGS(&mDsvHeap));

	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
	cbvHeapDesc.NumDescriptors = 1000;
	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvHeapDesc.NodeMask = 0;
	mD3dDevice->CreateDescriptorHeap(&cbvHeapDesc,
		IID_PPV_ARGS(&mCbvHeap));

}

void D3DApp::CreateRTV() {
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(mRtvHeap->GetCPUDescriptorHandleForHeapStart());

	for (UINT i = 0; i < SwapChainBufferCount; i++)
	{
		// Get the ith buffer in the swap chain.
		mSwapChain->GetBuffer(
			i, IID_PPV_ARGS(&mSwapChainBuffer[i]));

		// Create an RTV to it.
		mD3dDevice->CreateRenderTargetView(
			mSwapChainBuffer[i], nullptr, rtvHeapHandle);
		// Next entry in heap.
		rtvHeapHandle.Offset(1, mRtvDescriptorSize);
	}
}

void D3DApp::CreateDepthStencil()
{
	mDepthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	mDepthStencilDesc.Alignment = 0;
	mDepthStencilDesc.Width = mClientWidth;
	mDepthStencilDesc.Height = mClientHeight;
	mDepthStencilDesc.DepthOrArraySize = 1;
	mDepthStencilDesc.MipLevels = 1;
	mDepthStencilDesc.Format = mDepthStencilFormat;
	mDepthStencilDesc.SampleDesc.Count = m4XMsaaState ? 4 : 1;
	mDepthStencilDesc.SampleDesc.Quality = m4XMsaaState ? (m4XMsaaQuality - 1) : 0;
	mDepthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	mDepthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	mOptClear.Format = mDepthStencilFormat;
	mOptClear.DepthStencil.Depth = 1.0f;
	mOptClear.DepthStencil.Stencil = 0;

	HRESULT hr = mD3dDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&mDepthStencilDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&mOptClear,
		IID_PPV_ARGS(&mDepthStencilBuffer));
	// Create descriptor to mip level 0 of entire resource using the
	// format of the resource.
	mD3dDevice->CreateDepthStencilView(
		mDepthStencilBuffer,
		nullptr,
		DepthStencilView());
}

void D3DApp::CreateViewPortAndScissorRect()
{
	mViewPort.TopLeftX = 0.0f;
	mViewPort.TopLeftY = 0.0f;
	mViewPort.Width = static_cast<float>(mClientWidth);
	mViewPort.Height = static_cast<float>(mClientHeight);
	mViewPort.MinDepth = 0.0f;
	mViewPort.MaxDepth = 1.0f;

	mScissorRect = { 0, 0, (long)mClientWidth, (long)mClientHeight };
}

ID3D12Resource* D3DApp::CreateDefaultBuffer(const void* initData, UINT64 byteSize, ID3D12Resource* uploadBuffer)
{
	ID3D12Resource* defaultBuffer = nullptr;

	// Create the actual default buffer resource.
	mD3dDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(byteSize),
		D3D12_RESOURCE_STATE_COMMON,
		nullptr,
		IID_PPV_ARGS(&defaultBuffer));

	// In order to copy CPU memory data into our default buffer, we need
	// to create an intermediate upload heap.
	mD3dDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(byteSize),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&uploadBuffer));

	// Describe the data we want to copy into the default buffer.
	D3D12_SUBRESOURCE_DATA subResourceData = {};
	subResourceData.pData = initData;
	subResourceData.RowPitch = byteSize;
	subResourceData.SlicePitch = subResourceData.RowPitch;

	mCommandList->ResourceBarrier(1,
		&CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer,
			D3D12_RESOURCE_STATE_COMMON,
			D3D12_RESOURCE_STATE_COPY_DEST)
	);

	UpdateSubresources<1>(mCommandList, defaultBuffer, uploadBuffer, 0, 0, 1, &subResourceData);
	
	mCommandList->ResourceBarrier(1,
		&CD3DX12_RESOURCE_BARRIER::Transition(defaultBuffer,
			D3D12_RESOURCE_STATE_COPY_DEST,
			D3D12_RESOURCE_STATE_GENERIC_READ)
	);

	return defaultBuffer;
}

#pragma endregion


#pragma region Getting fonctions

D3D12_CPU_DESCRIPTOR_HANDLE D3DApp::CurrentBackBufferView()
{
	// CD3DX12 constructor to offset to the RTV of the current back buffer.
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		mRtvHeap->GetCPUDescriptorHandleForHeapStart(),// handle start
		mCurrBackBuffer, // index to offset
		mRtvDescriptorSize); // byte size of descriptor
}

D3D12_CPU_DESCRIPTOR_HANDLE D3DApp::DepthStencilView() { return mDsvHeap->GetCPUDescriptorHandleForHeapStart(); }

float D3DApp::GetAspectRatio() const { return (float)mClientWidth / (float)mClientHeight; }

#pragma endregion


#pragma region Creating fonctions for rendering elements

MeshGeometry* D3DApp::CreateGeometry(Vertex vertices[], int numVer, uint16_t indices[], int numInd, string name)
{
	const UINT64 vbByteSize = numVer * sizeof(Vertex);
	const UINT ibByteSize = numInd * sizeof(UINT);

	mDirectCmdListAlloc->Reset();
	mCommandList->Reset(mDirectCmdListAlloc, nullptr);

	MeshGeometry* geo = new MeshGeometry(name);

	//D3DCreateBlob(vbByteSize, &squareGeo.VertexBufferCPU);
	//CopyMemory(&squareGeo.VertexBufferCPU.GetBufferPointer(), vertices.data(), vbByteSize);
	geo->mVertexBufferGPU = CreateDefaultBuffer(vertices, vbByteSize, geo->mVertexBufferUploader);
	geo->mVertexByteSize = sizeof(Vertex);
	geo->mVertexBufferByteSize = sizeof(Vertex) * numVer;

	//D3DCreateBlob(ibByteSize, &squareGeo.IndexBufferCPU);
	//CopyMemory(squareGeo.IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);
	geo->mIndexBufferGPU = CreateDefaultBuffer(indices, ibByteSize, geo->mIndexBufferUploader);
	geo->mIndexBufferByteSize = ibByteSize;

	geo->mIndexCount = numInd;
	geo->mVertexCount = numVer;

	mCommandList->Close();
	ID3D12CommandList* cmdLists[] = { mCommandList };
	mCommandQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);
	FlushCommandQueue();

	return geo;
}

Texture* D3DApp::CreateTexture(string name, const wchar_t* path, int offset, bool cubeMap)
{
	Texture* tex = new Texture();
	tex->name = name;
	tex->filename = path;

	Microsoft::WRL::ComPtr<ID3D12Resource> texture;
	Microsoft::WRL::ComPtr<ID3D12Resource> uploadHeap;

	mDirectCmdListAlloc->Reset();
	mCommandList->Reset(mDirectCmdListAlloc, nullptr);

	HRESULT hr = CreateDDSTextureFromFile12(mD3dDevice, mCommandList, tex->filename, texture, uploadHeap);

	mCommandList->Close();
	ID3D12CommandList* cmdLists[] = { mCommandList };
	mCommandQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);
	FlushCommandQueue();

	tex->Resource = texture.Get();

	CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(mCbvHeap->GetCPUDescriptorHandleForHeapStart());
	hDescriptor.Offset(offset, mCbvSrvDescriptorSize);

	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.Format = tex->Resource->GetDesc().Format;

	if (!cubeMap) {
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = tex->Resource->GetDesc().MipLevels;
		srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
	}
	else
	{
		srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURECUBE;
		srvDesc.TextureCube.MostDetailedMip = 0;
		srvDesc.TextureCube.MipLevels = tex->Resource->GetDesc().MipLevels;
		srvDesc.TextureCube.ResourceMinLODClamp = 0.0f;
	}

	mD3dDevice->CreateShaderResourceView(tex->Resource, &srvDesc, hDescriptor);

	texture.Detach();

	return tex;
}

void D3DApp::CreateShader(Shader* shader, const wchar_t* path, bool defaultPso) const
{
	shader->Create(mD3dDevice, mCbvHeap, path, defaultPso);
	shader->Reset();
}

#pragma endregion


void D3DApp::FlushCommandQueue()
{
	// Advance the fence value to mark commands up to this fence point.
	mCurrentFence++;

	(mCommandQueue->Signal(mFence, mCurrentFence));
	// Wait until the GPU has completed commands up to this fence point.
	if (mFence->GetCompletedValue() < mCurrentFence)
	{
		mEventHandle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);

		// Fire event when GPU hits current fence.
		mFence->SetEventOnCompletion(mCurrentFence, mEventHandle);
		// Wait until the GPU hits current fence event is fired.
		WaitForSingleObject(mEventHandle, INFINITE);
		CloseHandle(mEventHandle);
	}
}

void D3DApp::Draw()
{
	mDirectCmdListAlloc->Reset();
	mCommandList->Reset(mDirectCmdListAlloc, nullptr);

	mCommandList->ResourceBarrier(
		1,
		&CD3DX12_RESOURCE_BARRIER::Transition(
			mSwapChainBuffer[mCurrBackBuffer],
			D3D12_RESOURCE_STATE_PRESENT,
			D3D12_RESOURCE_STATE_RENDER_TARGET)
	);

	mCommandList->RSSetViewports(1, &mViewPort);
	mCommandList->RSSetScissorRects(1, &mScissorRect);

	mCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());

	float color[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	mCommandList->ClearRenderTargetView(CurrentBackBufferView(), color, 0, nullptr);

	mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	ID3D12DescriptorHeap* descriptorHeaps[] = { mCbvHeap };
	mCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);

	Engine::GetInstance()->mRenderManager->ResetShaders();

	//CALL FRUSTUM
	Camera* cam = GameObjectManager::GetInstance()->GetCamera();

	BoundingFrustum::CreateFromMatrix(mFrustum, XMLoadFloat4x4(&cam->GetProj()));

	XMMATRIX invView = XMMatrixInverse(nullptr, cam->GetView());
	BoundingFrustum frust;
	mFrustum.Transform(frust, invView);

	for (auto obj : Engine::GetInstance()->mRenderManager->GetComponents()) {

		if (obj->mGameObject->mDigit == -1)
		{
			BoundingSphere bs;
			bs.Center = obj->mGameObject->mTransform->GetPosition();
			bs.Radius = max(max(obj->mGameObject->mTransform->GetScale().x, obj->mGameObject->mTransform->GetScale().y ), obj->mGameObject->mTransform->GetScale().z);

			if (frust.Contains(bs) != DirectX::DISJOINT)
			{
				obj->mGameObject->mTransform->CalcSuperWorldMatrix();

				obj->mShader->Begin(mCommandList);
				obj->mShader->SetObjectCB(obj);
				obj->mShader->UpdateObject();
				obj->mShader->Draw(mCommandList, obj->mGeo, obj->mTextureOffset);
			}
		}
		else
		{
			obj->mGameObject->mTransform->CalcSuperWorldMatrix();

			obj->mShader->Begin(mCommandList);
			obj->mShader->SetObjectCB(obj);
			obj->mShader->UpdateObject();
			obj->mShader->Draw(mCommandList, obj->mGeo, obj->mTextureOffset);
		}
	}

	mCommandList->ResourceBarrier(
		1,
		&CD3DX12_RESOURCE_BARRIER::Transition(
			mSwapChainBuffer[mCurrBackBuffer],
			D3D12_RESOURCE_STATE_RENDER_TARGET,
			D3D12_RESOURCE_STATE_PRESENT));

	mCommandList->Close();
	ID3D12CommandList* cmdLists[] = { mCommandList };
	mCommandQueue->ExecuteCommandLists(_countof(cmdLists), cmdLists);

	mSwapChain->Present(1, 0);
	mCurrBackBuffer = (mCurrBackBuffer + 1) % SwapChainBufferCount;

	FlushCommandQueue();
}

XMFLOAT2 D3DApp::GetWindowSize() {
	return XMFLOAT2(mClientWidth, mClientHeight);
}