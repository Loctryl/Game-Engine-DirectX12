// header.h : fichier Include pour les fichiers Include système standard,
// ou les fichiers Include spécifiques aux projets
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // Exclure les en-têtes Windows rarement utilisés
// Fichiers d'en-tête Windows
#include <windows.h>

#define MAX_LOADSTRING 100
#define DEBUG

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

using namespace DirectX;
using namespace std;

struct Vertex1
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};

struct Vertex2
{
	XMFLOAT3 Pos;
	XMFLOAT3 Normal;
	XMFLOAT2 Tex0;
	XMFLOAT2 Tex1;
};

struct Texture 
{
	string name;

	const wchar_t* filename;

	ID3D12Resource* Resource = nullptr;
	ID3D12Resource* UploadHeap = nullptr;

};