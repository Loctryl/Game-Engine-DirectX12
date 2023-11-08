#pragma once
#include "EngineResources/framework.h"
#include "Engine/Component/RenderComponent.h"
#include "MeshGeometry.h"
#include "Shaders/Shader.h"

class GameTimer;
class MeshGeometry;


//This class manages all the fonctionalities linked to DirectX12.
//It stores necessary variables and provides fonctions to create render elements as geometries, shaders or textures.
class D3DApp
{
private:
	// All variables needed by directX12 for the render pipeline
#pragma region Private Fields

	static D3DApp* mInstance;

	ID3D12Debug* mDebugController;
	void DebugLayer();

	HANDLE eventHandle;

	HWND* mWindow;
	UINT mClientWidth;
	UINT mClientHeight;

	ID3D12Device* md3dDevice;
	IDXGIFactory4* mdxgiFactory;
	IDXGIAdapter* pWarpAdapter;

	ID3D12Fence* mFence;
	UINT64 mCurrentFence = 0;

	UINT mRtvDescriptorSize;
	UINT mDsvDescriptorSize;
	UINT mCbvSrvDescriptorSize;

	DXGI_FORMAT mBackBufferFormat;
	UINT m4xMsaaQuality;
	bool m4xMsaaState;

	ID3D12GraphicsCommandList* mCommandList;
	ID3D12CommandQueue* mCommandQueue;
	ID3D12CommandAllocator* mDirectCmdListAlloc;

	IDXGISwapChain* mSwapChain;
	static const int SwapChainBufferCount = 2;
	int mCurrBackBuffer;
	ID3D12Resource* mSwapChainBuffer[SwapChainBufferCount];

	ID3D12DescriptorHeap* mRtvHeap;
	ID3D12DescriptorHeap* mDsvHeap;

	ID3D12Resource* mDepthStencilBuffer;
	D3D12_RESOURCE_DESC depthStencilDesc;
	D3D12_CLEAR_VALUE optClear;
	DXGI_FORMAT mDepthStencilFormat;

	D3D12_VIEWPORT vp;
	tagRECT mScissorRect;

#pragma endregion


	// Initialize fonctions for each component of DirectX12
#pragma region Private fonctions

	void CreateFactoryAndDevice();

	void CreateFenceAndDescSize();

	void CheckMSAASupport();

	void CreateCommandObjects();

	void CreateSwapChain();

	void CreateDescriptorHeaps();

	void CreateRTV();

	void CreateDepthStencil();

	void CreateViewPortAndScissorRect();

	ID3D12Resource* CreateDefaultBuffer(const void* initData, UINT64 byteSize, ID3D12Resource* uploadBuffer);

#pragma endregion


	// Private Getting fonctions

	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView();

	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView();

	void FlushCommandQueue();


public:
	D3DApp() = default;
	D3DApp(HWND* wH);
	~D3DApp();

	ID3D12DescriptorHeap* mCbvHeap;


	void Init();

	void Draw();

	XMFLOAT2 GetWindowSize();

	MeshGeometry* CreateGeometry(Vertex vertex[], int numVer, uint16_t index[], int numInd, string name);

	Texture* CreateTexture(string name, const wchar_t* path, int offset, bool cubeMap);

	void CreateShader(Shader* shader, const wchar_t* path, bool defaultPso = true);

	float GetAspectRatio();

	int GetClientWidth();
	int GetClientHeight();


	static D3DApp* GetInstance();
};