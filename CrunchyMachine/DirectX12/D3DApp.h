#pragma once
#include "../GameTimer.h"
#include "RenderComponent.h"

class D3DApp
{
private:
	//Debug
	ID3D12Debug* mDebugController;
	void DebugLayer();

	HANDLE eventHandle;

	//Window
	HWND* mWindow;
	UINT mClientWidth;
	UINT mClientHeight;

	//Device, Factory and Adaptater
	ID3D12Device* md3dDevice;
	IDXGIFactory4* mdxgiFactory;
	IDXGIAdapter* pWarpAdapter;

	//Fence
	ID3D12Fence* mFence;
	UINT64 mCurrentFence = 0;
	UINT mRtvDescriptorSize;
	UINT mDsvDescriptorSize;
	UINT mCbvSrvDescriptorSize;

	//MSAA Support
	DXGI_FORMAT mBackBufferFormat;
	UINT m4xMsaaQuality;
	bool m4xMsaaState;

	//Command Objects
	ID3D12GraphicsCommandList* mCommandList;
	ID3D12CommandQueue* mCommandQueue;
	ID3D12CommandAllocator* mDirectCmdListAlloc;

	//SwapChain
	IDXGISwapChain* mSwapChain;
	static const int SwapChainBufferCount = 2;
	int mCurrBackBuffer;
	ID3D12Resource* mSwapChainBuffer[SwapChainBufferCount];

	//Descriptor Heaps
	ID3D12DescriptorHeap* mRtvHeap;
	ID3D12DescriptorHeap* mDsvHeap;
	ID3D12DescriptorHeap* mCbvHeap;

	//Depth/Stencil Buffer
	ID3D12Resource* mDepthStencilBuffer;
	D3D12_RESOURCE_DESC depthStencilDesc;
	D3D12_CLEAR_VALUE optClear;
	DXGI_FORMAT mDepthStencilFormat;

	//ViewPort and scissor Rect
	D3D12_VIEWPORT vp;
	tagRECT mScissorRect;

	//Index and vertices
	ID3D12Resource* mIndexBufferGPU = nullptr;
	ID3D12Resource* mIndexBufferUploader = nullptr;
	ID3D12Resource* mVertexBufferGPU = nullptr;
	ID3D12Resource* mVertexBufferUploader = nullptr;
	D3D12_INDEX_BUFFER_VIEW mIndexBufferView;
	D3D12_VERTEX_BUFFER_VIEW mVertexBufferView;
	D3D12_INPUT_ELEMENT_DESC mInputLayout[2];

	//Constant Buffer
	//UploadBuffer<ObjectConstants>* mConstantBuffer;
	float mRotate;
	MeshGeometry squareGeo;
	MeshGeometry worldAxis;
	std::vector<RenderComponent*> mAllItems = vector<RenderComponent*>();

	//Root signature
	ID3D12RootSignature* mRootSignature;

	//PSO
	ID3DBlob* mvsByteCode;
	ID3DBlob* mpsByteCode;
	ID3D12PipelineState* mPSO;

		
	void CreateFactoryAndDevice();

	void CreateFenceAndDescSize();

	void CheckMSAASupport();

	void CreateCommandObjects();

	void CreateSwapChain();

	void CreateDescriptorHeaps();

	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView();

	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView();

	void CreateRTV();

	void CreateDepthStencil();

	void CreateViewPortAndScissorRect();

	ID3D12Resource* CreateDefaultBuffer(const void* initData, UINT64 byteSize, ID3D12Resource* uploadBuffer);

	void UpdateConstantBuffer(RenderComponent* item);

	void CreateVertexAndIndices();

	void CreateConstantBuffer(RenderComponent* item);

	void CreateRootSignature();

	ID3DBlob* CompileShader(const std::wstring& filename, const D3D_SHADER_MACRO* defines, const std::string& entrypoint, const std::string& target);

	void CreateGraphicsPipelineState();

	void FlushCommandQueue();

public:
	D3DApp();
	D3DApp(HWND* wH);
	~D3DApp() = default;

	void Init();

	void Update(GameTimer timer);

	void Draw(GameTimer timer);
};