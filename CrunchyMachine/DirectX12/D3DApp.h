#pragma once
#include "../Resources/framework.h"
#include "../GameTimer.h"
#include "../Resources/Color.h"
#include "MeshGeometry.h"
#include "../Engine/GameObjectManager.h"
#include "../Shader.h"
#include "RenderComponent.h"
#include "UploadBuffer.h"

class GameTimer;
class MeshGeometry;

class D3DApp
{
private:

	//ShaderBasic mShader;

	static D3DApp* mInstance;

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

	void FlushCommandQueue();

public:
	D3DApp();
	D3DApp(HWND* wH);
	~D3DApp() = default;

	void Init();

	void Draw(GameTimer* timer);

	MeshGeometry* CreateGeometry(Vertex1 vertex[], int numVer, uint16_t index[], int numInd, string name);

	void CreateShader(Shader* shader, const wchar_t* path);

	RenderComponent* CreateRenderComponent(MeshGeometry* geometry, Shader* shader);

	float GetAspectRatio();

	static D3DApp* GetInstance();
};