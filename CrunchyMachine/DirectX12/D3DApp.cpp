#include "D3DApp.h"
#include "Resources/Color.h"
#include "GameTimer.h"
#include "DirectX12/UploadBuffer.h"
#include "RenderComponent.h"
#include "Window/Window.h"	
#include "GeoManager.h"
#include "Engine/GameObject.h"
#include"Transform.h"




D3D12_INPUT_ELEMENT_DESC descVertex2[] =
{
   {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
   {"NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
   {"TEXCOORD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
   {"TEXCOORD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
};


D3DApp* D3DApp::mInstance = nullptr;


D3DApp* D3DApp::GetInstance()
{
	if (mInstance == nullptr)
		mInstance = new D3DApp(&Window::GetHWND());
	return mInstance;
}


D3DApp::D3DApp() { }

D3DApp::D3DApp(HWND* wH)
{
#if defined(DEBUG) || defined(_DEBUG)
	DebugLayer();
#endif

	mWindow = wH;

	mDebugController = nullptr;

	md3dDevice = nullptr;
	mdxgiFactory = nullptr;
	pWarpAdapter = nullptr;

	mFence = nullptr;
	mRtvDescriptorSize = 0;
	mDsvDescriptorSize = 0;
	mCbvSrvDescriptorSize = 0;

	mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	m4xMsaaQuality = 0;
	m4xMsaaState = false;

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

	mIndexBufferGPU = nullptr;
	mIndexBufferUploader = nullptr;
	mVertexBufferGPU = nullptr;
	mVertexBufferUploader = nullptr;

	mRootSignature = nullptr;

	mvsByteCode = nullptr;
	mpsByteCode = nullptr;
	mPSO = nullptr;

	mRotate = 0;
}

void D3DApp::DebugLayer()
{
	D3D12GetDebugInterface(IID_PPV_ARGS(&mDebugController));
	mDebugController->EnableDebugLayer();
}

void D3DApp::Init()
{
	RECT r;
	GetClientRect(*mWindow, &r);
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

	//CreateGeometry();
	//mInputLayout[0] = descVertex1[0];
	//mInputLayout[1] = descVertex1[1];

	//CreateRootSignature();
	//CreateGraphicsPipelineState();

	mCommandList->Close();
	ID3D12CommandList* cmdLists3[] = { mCommandList };
	mCommandQueue->ExecuteCommandLists(_countof(cmdLists3), cmdLists3);
	FlushCommandQueue();
}

void D3DApp::CreateFactoryAndDevice()
{
	CreateDXGIFactory1(IID_PPV_ARGS(&mdxgiFactory));

	HRESULT hardWareResult = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&md3dDevice));

	if (FAILED(hardWareResult))
	{
		mdxgiFactory->EnumWarpAdapter(IID_PPV_ARGS(&pWarpAdapter));
		D3D12CreateDevice(pWarpAdapter, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&md3dDevice));
	}

	ID3D12InfoQueue* InfoQueue = nullptr;
	md3dDevice->QueryInterface(IID_PPV_ARGS(&InfoQueue));
	InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
	InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
	InfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, false);
}

void D3DApp::CreateFenceAndDescSize()
{
	md3dDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&mFence));

	mRtvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	mDsvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
	mCbvSrvDescriptorSize = md3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

void D3DApp::CheckMSAASupport()
{
	D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS msQualityLevels;

	msQualityLevels.Format = mBackBufferFormat;
	msQualityLevels.SampleCount = 4;
	msQualityLevels.Flags = D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
	msQualityLevels.NumQualityLevels = 0;

	md3dDevice->CheckFeatureSupport(
		D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS,
		&msQualityLevels,
		sizeof(msQualityLevels));

	m4xMsaaQuality = msQualityLevels.NumQualityLevels;
	assert(m4xMsaaQuality > 0 && "MSAA Quality level should be greater than 0");
}

void D3DApp::CreateCommandObjects()
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	md3dDevice->CreateCommandQueue(
		&queueDesc, IID_PPV_ARGS(&mCommandQueue));

	md3dDevice->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&mDirectCmdListAlloc));

	md3dDevice->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		mDirectCmdListAlloc, // Associated command allocator
		nullptr, // Initial PipelineStateObject
		IID_PPV_ARGS(&mCommandList));

	// Start off in a closed state. This is because the first time we
	// refer to the command list we will Reset it, and it needs to be
	// closed before calling Reset.
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
	sd.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	sd.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = SwapChainBufferCount;
	sd.OutputWindow = *mWindow;
	sd.Windowed = true;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	// Note: Swap chain uses queue to perform flush.
	mdxgiFactory->CreateSwapChain(
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

	md3dDevice->CreateDescriptorHeap(
		&rtvHeapDesc, IID_PPV_ARGS(&mRtvHeap));
	D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc;
	dsvHeapDesc.NumDescriptors = 1;
	dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
	dsvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	dsvHeapDesc.NodeMask = 0;
	md3dDevice->CreateDescriptorHeap(
		&dsvHeapDesc, IID_PPV_ARGS(&mDsvHeap));

	D3D12_DESCRIPTOR_HEAP_DESC cbvHeapDesc;
	cbvHeapDesc.NumDescriptors = 10;
	cbvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	cbvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
	cbvHeapDesc.NodeMask = 0;
	md3dDevice->CreateDescriptorHeap(&cbvHeapDesc,
		IID_PPV_ARGS(&mCbvHeap));
}

D3D12_CPU_DESCRIPTOR_HANDLE D3DApp::CurrentBackBufferView()
{
	// CD3DX12 constructor to offset to the RTV of the current back buffer.
	return CD3DX12_CPU_DESCRIPTOR_HANDLE(
		mRtvHeap->GetCPUDescriptorHandleForHeapStart(),// handle start
		mCurrBackBuffer, // index to offset
		mRtvDescriptorSize); // byte size of descriptor
}

D3D12_CPU_DESCRIPTOR_HANDLE D3DApp::DepthStencilView() { return mDsvHeap->GetCPUDescriptorHandleForHeapStart(); }

void D3DApp::CreateRTV() {
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHeapHandle(mRtvHeap->GetCPUDescriptorHandleForHeapStart());

	for (UINT i = 0; i < SwapChainBufferCount; i++)
	{
		// Get the ith buffer in the swap chain.
		mSwapChain->GetBuffer(
			i, IID_PPV_ARGS(&mSwapChainBuffer[i]));
		// Create an RTV to it.
		md3dDevice->CreateRenderTargetView(
			mSwapChainBuffer[i], nullptr, rtvHeapHandle);
		// Next entry in heap.
		rtvHeapHandle.Offset(1, mRtvDescriptorSize);
	}
}

void D3DApp::CreateDepthStencil()
{
	depthStencilDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	depthStencilDesc.Alignment = 0;
	depthStencilDesc.Width = mClientWidth;
	depthStencilDesc.Height = mClientHeight;
	depthStencilDesc.DepthOrArraySize = 1;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.Format = mDepthStencilFormat;
	depthStencilDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	depthStencilDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	depthStencilDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
	depthStencilDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	optClear.Format = mDepthStencilFormat;
	optClear.DepthStencil.Depth = 1.0f;
	optClear.DepthStencil.Stencil = 0;

	HRESULT hr = md3dDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&depthStencilDesc,
		D3D12_RESOURCE_STATE_DEPTH_WRITE,
		&optClear,
		IID_PPV_ARGS(&mDepthStencilBuffer));
	// Create descriptor to mip level 0 of entire resource using the
	// format of the resource.
	md3dDevice->CreateDepthStencilView(
		mDepthStencilBuffer,
		nullptr,
		DepthStencilView());
}

void D3DApp::CreateViewPortAndScissorRect()
{
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = static_cast<float>(mClientWidth);
	vp.Height = static_cast<float>(mClientHeight);
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	mScissorRect = { 0, 0, (long)mClientWidth, (long)mClientHeight };
}

ID3D12Resource* D3DApp::CreateDefaultBuffer(const void* initData, UINT64 byteSize, ID3D12Resource* uploadBuffer)
{
	ID3D12Resource* defaultBuffer = nullptr;

	// Create the actual default buffer resource.
	md3dDevice->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(byteSize),
		D3D12_RESOURCE_STATE_COMMON,
		nullptr,
		IID_PPV_ARGS(&defaultBuffer));

	// In order to copy CPU memory data into our default buffer, we need
	// to create an intermediate upload heap.
	md3dDevice->CreateCommittedResource(
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

MeshGeometry* D3DApp::CreateGeometry(Vertex1 vertices[], int numVer, uint16_t indices[], int numInd, string name)
{
	const UINT64 vbByteSize = 8 * sizeof(Vertex1);
	UINT ibByteSize = 36 * sizeof(UINT);

	mDirectCmdListAlloc->Reset();
	mCommandList->Reset(mDirectCmdListAlloc, nullptr);

	geo = new MeshGeometry(name);

	//D3DCreateBlob(vbByteSize, &squareGeo.VertexBufferCPU);
	//CopyMemory(&squareGeo.VertexBufferCPU.GetBufferPointer(), vertices.data(), vbByteSize);
	geo->mVertexBufferGPU = CreateDefaultBuffer(vertices, vbByteSize, geo->mVertexBufferUploader);
	geo->mVertexByteStride = sizeof(Vertex1);
	geo->mVertexBufferByteSize = sizeof(Vertex1) * numVer;

	//D3DCreateBlob(ibByteSize, &squareGeo.IndexBufferCPU);
	//CopyMemory(squareGeo.IndexBufferCPU->GetBufferPointer(), indices.data(), ibByteSize);
	geo->mIndexBufferGPU = CreateDefaultBuffer(indices, ibByteSize, geo->mIndexBufferUploader);
	geo->mIndexBufferByteSize = ibByteSize;

	geo->mIndexCount = numInd;

	//mAllItems.push_back(CreateRenderComponent(geo));
	//mAllItems.push_back(CreateRenderComponent(geo));

	mCommandList->Close();
	ID3D12CommandList* cmdLists3[] = { mCommandList };
	mCommandQueue->ExecuteCommandLists(_countof(cmdLists3), cmdLists3);
	FlushCommandQueue();

	return geo;
}
RenderComponent* D3DApp::CreateRenderComponent(MeshGeometry* geometry)
{
	RenderComponent* item = new RenderComponent();
	item->Geo = geometry;
	item->Geo->mIndexCount = geometry->mIndexCount;
	//item->ObjCBIndex = mAllItems.size();
	//mAllItems.push_back(item);
	CreateConstantBuffer(item);

	return item;
}

void D3DApp::CreateConstantBuffer(RenderComponent* item)
{
	UINT elementByteSize = (sizeof(ObjectConstants) + 255) & ~255;
	int NumElements = 1;

	UploadBuffer<ObjectConstants>* mCBuf = new UploadBuffer<ObjectConstants>(md3dDevice, NumElements, true);
	D3D12_GPU_VIRTUAL_ADDRESS address = mCBuf->GetResource()->GetGPUVirtualAddress();

	D3D12_CONSTANT_BUFFER_VIEW_DESC cbvDesc;
	cbvDesc.BufferLocation = address;
	cbvDesc.SizeInBytes = elementByteSize;

	md3dDevice->CreateConstantBufferView(&cbvDesc, mCbvHeap->GetCPUDescriptorHandleForHeapStart());

	mCBuf->GetResource()->Map(0, nullptr, reinterpret_cast<void**>(mCBuf->GetMappedData()));

	item->mConstantBuffer = mCBuf;

	//UpdateConstantBuffer(item);
}

void D3DApp::UpdateConstantBuffer(RenderComponent* item, XMMATRIX objMat)
{
	ObjectConstants objConst;

	XMMATRIX view, proj;

	// Camera
	XMVECTOR pos = XMVectorSet(0.0F, 0.5F, -1.5F, 1.0F);
	XMVECTOR target = XMVectorSet(0.0F, 0.0F, 0.0F, 0.0F);
	XMVECTOR up = XMVectorSet(0.0F, 1.0F, 0.0F, 0.0F);
	view = XMMatrixLookAtLH(pos, target, up);

	proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0F), (float)mClientWidth / mClientHeight, 0.05F, 1000.0F);
	// end camera

	XMStoreFloat4x4(&objConst.World, XMMatrixTranspose(objMat * view * proj));

	item->mConstantBuffer->CopyData(0, objConst);
}

void D3DApp::CreateRootSignature()
{
	// Root parameter can be a table, root descriptor or root constants.
	CD3DX12_ROOT_PARAMETER slotRootParameter[1];
	// Create a single descriptor table of CBVs
	slotRootParameter[0].InitAsConstantBufferView(0); // Pointer to array of ranges
	// A root signature is an array of root parameters.
	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(1, slotRootParameter, 0,
		nullptr,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
	// create a root signature with a single slot which points to a
	// descriptor range consisting of a single constant buffer.
	ID3DBlob* serializedRootSig = nullptr;
	ID3DBlob* errorBlob = nullptr;
	D3D12SerializeRootSignature(&rootSigDesc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&serializedRootSig,
		&errorBlob);
	md3dDevice->CreateRootSignature(
		0,
		serializedRootSig->GetBufferPointer(),
		serializedRootSig->GetBufferSize(),
		IID_PPV_ARGS(&mRootSignature));
}

ID3DBlob* D3DApp::CompileShader(const std::wstring& filename, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target)
{
	UINT compileFlags = 0;

#if defined(DEBUG) || defined(_DEBUG)
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	HRESULT hr = S_OK;
	ID3DBlob* byteCode = nullptr;
	ID3DBlob* errors;
	hr = D3DCompileFromFile(filename.c_str(), defines, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entrypoint.c_str(), target.c_str(), compileFlags, 0, &byteCode,
		&errors);
	// Output errors to debug window.
	if (errors != nullptr)
		OutputDebugStringA((char*)errors->GetBufferPointer());

	return byteCode;
}

void D3DApp::CreateGraphicsPipelineState()
{

	mvsByteCode = CompileShader(L"Shaders\\VertexShader.hlsl", nullptr, "VS", "vs_5_0");
	mpsByteCode = CompileShader(L"Shaders\\VertexShader.hlsl", nullptr, "PS", "ps_5_0");

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psoDesc.InputLayout = { mInputLayout, _countof(mInputLayout) };
	psoDesc.pRootSignature = mRootSignature;

	psoDesc.VS =
	{
	reinterpret_cast<BYTE*>(mvsByteCode->GetBufferPointer()),
	mvsByteCode->GetBufferSize()
	};

	psoDesc.PS =
	{
	reinterpret_cast<BYTE*>(mpsByteCode->GetBufferPointer()),
	mpsByteCode->GetBufferSize()
	};

	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = mBackBufferFormat;
	psoDesc.SampleDesc.Count = m4xMsaaState ? 4 : 1;
	psoDesc.SampleDesc.Quality = m4xMsaaState ? (m4xMsaaQuality - 1) : 0;
	psoDesc.DSVFormat = mDepthStencilFormat;

	md3dDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPSO));
}

void D3DApp::FlushCommandQueue()
{
	// Advance the fence value to mark commands up to this fence point.
	mCurrentFence++;
	// Add an instruction to the command queue to set a new fence point.
	// Because we are on the GPU timeline, the new fence point won’t be
	// set until the GPU finishes processing all the commands prior to
	// this Signal().
	(mCommandQueue->Signal(mFence, mCurrentFence));
	// Wait until the GPU has completed commands up to this fence point.
	if (mFence->GetCompletedValue() < mCurrentFence)
	{
		eventHandle = CreateEventEx(nullptr, false, false, EVENT_ALL_ACCESS);

		// Fire event when GPU hits current fence.
		mFence->SetEventOnCompletion(mCurrentFence, eventHandle);
		// Wait until the GPU hits current fence event is fired.
		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}

void D3DApp::Update(GameTimer* timer)
{
	mRotate += 1 * timer->DeltaTime();
}

void D3DApp::Draw(GameTimer* timer)
{
	//for (int i = 0; i < mAllItems.size(); i++)
	//	UpdateConstantBuffer(mAllItems[i]);

	mDirectCmdListAlloc->Reset();

	mCommandList->Reset(mDirectCmdListAlloc, nullptr);

	mCommandList->ResourceBarrier(
		1,
		&CD3DX12_RESOURCE_BARRIER::Transition(
			mSwapChainBuffer[mCurrBackBuffer],
			D3D12_RESOURCE_STATE_PRESENT,
			D3D12_RESOURCE_STATE_RENDER_TARGET)
	);

	mCommandList->RSSetViewports(1, &vp);
	mCommandList->RSSetScissorRects(1, &mScissorRect);

	mCommandList->OMSetRenderTargets(1, &CurrentBackBufferView(), true, &DepthStencilView());

	float color[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	mCommandList->ClearRenderTargetView(CurrentBackBufferView(), color, 0, nullptr);

	mCommandList->ClearDepthStencilView(DepthStencilView(), D3D12_CLEAR_FLAG_DEPTH | D3D12_CLEAR_FLAG_STENCIL, 1.0f, 0, 0, nullptr);

	ID3D12DescriptorHeap* descriptorHeaps[] = { mCbvHeap };
	mCommandList->SetDescriptorHeaps(_countof(descriptorHeaps), descriptorHeaps);


	ShaderBasic mShader;
	mShader.Create(md3dDevice, mCbvHeap, L"C:\\Users\\rmateescu\\Documents\\GitHub\\gtech3-proj3-directX12_engine\\CrunchyMachine\\Shaders\\VertexShader.hlsl");
	mShader.Reset();

	XMFLOAT4X4 viewProj;
	XMMATRIX view, proj;
	XMVECTOR pos = XMVectorSet(0.0F, 0.0F, -3.0F, 1.0F);
	XMVECTOR target = XMVectorSet(0.0F, 0.0F, 0.0F, 0.0F);
	XMVECTOR up = XMVectorSet(0.0F, 1.0F, 0.0F, 0.0F);
	view = XMMatrixLookAtLH(pos, target, up);

	proj = XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0F), (float)mClientWidth / mClientHeight, 0.05F, 1000.0F);
	DirectX::XMStoreFloat4x4(&viewProj, XMMatrixTranspose(view * proj));

	mShader.mPc.viewProj = viewProj;
	mShader.UpdatePass();

	for (auto obj : GeoManager::GetInstance()->gObj) {
		mCommandList->SetGraphicsRootSignature(mRootSignature);

		obj->mTransform->CalcWorldMatrix();

		mShader.Begin(mCommandList);
		mShader.mOc.world = obj->mTransform->GetWorldMatrix();
		mShader.UpdateObject();
		mShader.Draw(mCommandList, obj->mItem->Geo);


		//mCommandList->SetGraphicsRootSignature(mRootSignature);

		//mCommandList->SetPipelineState(mPSO);

		//// Offset the CBV we want to use for this draw call.
		//CD3DX12_GPU_DESCRIPTOR_HANDLE cbv(mCbvHeap->GetGPUDescriptorHandleForHeapStart());
		//cbv.Offset(i, mCbvSrvDescriptorSize);

		//mCommandList->SetGraphicsRootConstantBufferView(0, mAllItems[i]->mConstantBuffer->GetResource()->GetGPUVirtualAddress());

		//mCommandList->IASetVertexBuffers(0, 1, &mAllItems[i]->Geo->VertexBufferView());

		//mCommandList->IASetIndexBuffer(&mAllItems[i]->Geo->IndexBufferView());

		//mCommandList->IASetPrimitiveTopology(mAllItems[i]->Geo->mPrimitiveType);

		//mCommandList->DrawIndexedInstanced(mAllItems[i]->Geo->mIndexCount, 1, 0, 0, 0);
		//Offset the CBV we want to use for this draw call.
		CD3DX12_GPU_DESCRIPTOR_HANDLE cbv(mCbvHeap->GetGPUDescriptorHandleForHeapStart());
		cbv.Offset(0, mCbvSrvDescriptorSize);

		mCommandList->SetGraphicsRootConstantBufferView(0, obj->mItem->mConstantBuffer->GetResource()->GetGPUVirtualAddress());

		mCommandList->IASetVertexBuffers(0, 1, &obj->mItem->Geo->VertexBufferView());

		mCommandList->IASetIndexBuffer(&obj->mItem->Geo->IndexBufferView());

		mCommandList->IASetPrimitiveTopology(obj->mItem->Geo->mPrimitiveType);

		mCommandList->DrawIndexedInstanced(obj->mItem->Geo->mIndexCount, 1, 0, 0, 0);
	}

	//for (int i = 0; i < GeoManager::GetInstance()->gObj.size(); i++)
	//{
	//	mCommandList->SetGraphicsRootSignature(mRootSignature);

	//	mCommandList->SetPipelineState(mPSO);

	//	// Offset the CBV we want to use for this draw call.
	//	CD3DX12_GPU_DESCRIPTOR_HANDLE cbv(mCbvHeap->GetGPUDescriptorHandleForHeapStart());
	//	cbv.Offset(i, mCbvSrvDescriptorSize);

	//	mCommandList->SetGraphicsRootConstantBufferView(0, mAllItems[i]->mConstantBuffer->GetResource()->GetGPUVirtualAddress());

	//	mCommandList->IASetVertexBuffers(0, 1, &mAllItems[i]->Geo->VertexBufferView());

	//	mCommandList->IASetIndexBuffer(&mAllItems[i]->Geo->IndexBufferView());

	//	mCommandList->IASetPrimitiveTopology(mAllItems[i]->Geo->mPrimitiveType);

	//	mCommandList->DrawIndexedInstanced(mAllItems[i]->Geo->mIndexCount, 1, 0, 0, 0);
	//}



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