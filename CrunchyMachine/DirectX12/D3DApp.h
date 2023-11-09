#pragma once
#include "EngineResources/framework.h"
#include "Engine/Component/RenderComponent.h"
#include "MeshGeometry.h"
#include "DirectXCollision.h"


class GameTimer;
class MeshGeometry;


//This class manages all the functionalities linked to DirectX12.
//It stores necessary variables and provides functions to create render elements as geometries, shaders or textures.
class D3DApp
{
private:
	// All variables needed by directX12 for the render pipeline
#pragma region Private Fields

	static D3DApp* mInstance;

	ID3D12Debug* mDebugController;

	HANDLE mEventHandle;

	HWND mWindow;
	UINT mClientWidth;
	UINT mClientHeight;

	ID3D12Device* mD3dDevice;
	IDXGIFactory4* mDxgiFactory;
	IDXGIAdapter* mWarpAdapter;

	ID3D12Fence* mFence;
	UINT mCurrentFence = 0;

	UINT mRtvDescriptorSize;
	UINT mDsvDescriptorSize;
	UINT mCbvSrvDescriptorSize;

	DXGI_FORMAT mBackBufferFormat;
	UINT m4XMsaaQuality;
	bool m4XMsaaState;

	ID3D12GraphicsCommandList* mCommandList;
	ID3D12CommandQueue* mCommandQueue;
	ID3D12CommandAllocator* mDirectCmdListAlloc;

	IDXGISwapChain* mSwapChain;
	static constexpr int SwapChainBufferCount = 2;
	int mCurrBackBuffer;
	ID3D12Resource* mSwapChainBuffer[SwapChainBufferCount];

	ID3D12DescriptorHeap* mRtvHeap;
	ID3D12DescriptorHeap* mDsvHeap;
	ID3D12DescriptorHeap* mCbvHeap;

	ID3D12Resource* mDepthStencilBuffer;
	D3D12_RESOURCE_DESC mDepthStencilDesc;
	D3D12_CLEAR_VALUE mOptClear;
	DXGI_FORMAT mDepthStencilFormat;

	D3D12_VIEWPORT mViewPort;
	tagRECT mScissorRect;

	BoundingFrustum mFrustum;

#pragma endregion


	// Initialize functions for each component of DirectX12
#pragma region Private fonctions

	void DebugLayer();

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
	
	// Private Getting functions

	D3D12_CPU_DESCRIPTOR_HANDLE CurrentBackBufferView();

	D3D12_CPU_DESCRIPTOR_HANDLE DepthStencilView();

	void FlushCommandQueue();

public:
	D3DApp() = default;
	D3DApp(HWND wH);
	~D3DApp();
	
	void Init();

	void Draw();

	XMFLOAT2 GetWindowSize();

	MeshGeometry* CreateGeometry(Vertex vertices[], int numVer, uint16_t indices[], int numInd, string name);

	Texture* CreateTexture(string name, const wchar_t* path, int offset, bool cubeMap);

	void CreateShader(Shader* shader, const wchar_t* path, bool defaultPso = true) const;

	float GetAspectRatio() const;
	
	static D3DApp* GetInstance();
};