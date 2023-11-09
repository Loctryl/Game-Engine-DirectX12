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

// Release pointers fonctions
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
#define KILLBOX 2000

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
	STATEMACHINE
};
