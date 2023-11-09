#pragma once

#define WIN32_LEAN_AND_MEAN        

#define MAX_LOADSTRING 100
#define DEBUG

// Release pointers functions
#define RELPTRDX(ptr) if (ptr) { ptr->Release(); ptr = nullptr; }
#define RELPTR(ptr) if (ptr) { delete ptr; ptr = nullptr; }


// DirectX Librairies
#pragma comment(lib, "D3D12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

// DirectX Header Files
#include <d3d12.h>
#include "../d3dx12.h"
#include <dxgi1_6.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#define GRID_SIZE 1
#define MAX_COLLISION_DIST 1900
#define KILLBOX 3000

using namespace DirectX;
using namespace std;

struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
	XMFLOAT3 Normal;
	XMFLOAT2 TexCoord;
};

struct Texture 
{
	string name;

	const wchar_t* filename;

	ID3D12Resource* Resource = nullptr;
};

enum ComponentType
{
	TEMPLATE,
	TRANSFORM,
	PHYSICS,
	RENDER,
	STATE_MACHINE
};
