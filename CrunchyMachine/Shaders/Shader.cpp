#pragma once
#include "Shader.h"
#include "Engine/GameObjectManager.h"
#include "Engine/Component/Camera.h"
#include "Engine/Component/Transform.h"

Shader::Shader() {
	mDevice = nullptr;
	mCbvHeap = nullptr;
	mDescriptorSize = 0;
	mSerializedRootSignature = nullptr;
	mPass = nullptr;
	mRootSignature = nullptr;
	mVS = nullptr;
	mPS = nullptr;
	mPso = nullptr;
	mIndex = 0;
}

Shader::~Shader() { Destroy(); }

bool Shader::Create(ID3D12Device* Device, ID3D12DescriptorHeap* CbvHeap, const wchar_t* path, bool defaultPso)
{
	mDevice = Device;
	mCbvHeap = CbvHeap;
	mDescriptorSize = mDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	mVS = Compile(path, "VS", "vs_5_0");
	if (mVS == nullptr)
	{
		Destroy();
		return false;
	}

	mPS = Compile(path, "PS", "ps_5_0");
	if (mPS == nullptr)
	{
		Destroy();
		return false;
	}

	if (!OnCreate())
	{
		Destroy();
		return false;
	}

	mDevice->CreateRootSignature(
		0,
		mSerializedRootSignature->GetBufferPointer(),
		mSerializedRootSignature->GetBufferSize(),
		IID_PPV_ARGS(&mRootSignature)
	);

	AddObject();
	mPass = OnCreatePassUploadBuffer();


	D3D12_INPUT_ELEMENT_DESC inputLayout[] =
	{
	   {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	   {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	   {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 28, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	   {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}
	};

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc;
	ZeroMemory(&psoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	psoDesc.InputLayout = { inputLayout, _countof(inputLayout) };
	psoDesc.pRootSignature = mRootSignature;
	psoDesc.VS =
	{
	reinterpret_cast<BYTE*>(mVS->GetBufferPointer()),

	mVS->GetBufferSize()
	};
	psoDesc.PS =
	{
	reinterpret_cast<BYTE*>(mPS->GetBufferPointer()),
	mPS->GetBufferSize()
	};
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	if (!defaultPso)
	{
		psoDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
		psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS_EQUAL;
	}
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	psoDesc.SampleDesc.Count = 1;
	psoDesc.SampleDesc.Quality = 0;
	psoDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;

	mDevice->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mPso));

	return true;
}

void Shader::Destroy()
{
	RELPTRDX(mDevice);
	RELPTRDX(mCbvHeap);
	RELPTRDX(mSerializedRootSignature);
	RELPTRDX(mRootSignature);
	RELPTRDX(mVS);
	RELPTRDX(mPS);
	RELPTRDX(mPso);

	RELPTR(mPass);

	for (auto buf : mObjects)
		RELPTR(buf);
	mObjects.clear();
}

void Shader::UpdatePass() { mPass->CopyData(GetPassCB()); }

void Shader::UpdateObject() { mObjects[mIndex]->CopyData(GetObjectCB()); }

void Shader::Reset() { mIndex = 0; }

void Shader::Draw(ID3D12GraphicsCommandList* list, MeshGeometry* mesh, int textureIndex)
{
	D3D12_VERTEX_BUFFER_VIEW vbv = mesh->VertexBufferView();
	D3D12_INDEX_BUFFER_VIEW ibv = mesh->IndexBufferView();
	list->IASetVertexBuffers(0, 1, &vbv);
	list->IASetIndexBuffer(&ibv);

	CD3DX12_GPU_DESCRIPTOR_HANDLE tex(mCbvHeap->GetGPUDescriptorHandleForHeapStart());

	if (textureIndex != -1)
	{
		tex.Offset(textureIndex, mDescriptorSize);

		list->SetGraphicsRootDescriptorTable(0, tex);

		list->SetGraphicsRootConstantBufferView(1, mObjects[mIndex]->GetResource()->GetGPUVirtualAddress());

	}
	else {
		list->SetGraphicsRootConstantBufferView(0, mObjects[mIndex]->GetResource()->GetGPUVirtualAddress());
	}

	list->DrawIndexedInstanced(mesh->mIndexCount, 1, 0, 0, 0);

	mIndex++;
	if (mIndex == mObjects.size())
		AddObject();
}

void Shader::AddObject()
{
	UploadBufferBase* UB = OnCreateObjectUploadBuffer();
	mObjects.push_back(UB);
}

ID3DBlob* Shader::Compile(const wchar_t* path, std::string entrypoint, std::string target)
{
	UINT compileFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	HRESULT hr = S_OK;
	ID3DBlob* byteCode = nullptr;
	ID3DBlob* errors = nullptr;

	hr = D3DCompileFromFile(path, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		entrypoint.c_str(), target.c_str(), compileFlags, 0, &byteCode,
		&errors);
	// Output errors to debug window.
	if (errors != nullptr)
		OutputDebugStringA((char*)errors->GetBufferPointer());
	return byteCode;
}




void ColorShader::Begin(ID3D12GraphicsCommandList* list)
{
	list->SetGraphicsRootSignature(mRootSignature);
	list->SetGraphicsRootConstantBufferView(1, mPass->GetResource()->GetGPUVirtualAddress());
	list->SetPipelineState(mPso);
	list->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

bool ColorShader::OnCreate()
{
	CD3DX12_ROOT_PARAMETER slotRootParameter[2];

	slotRootParameter[0].InitAsConstantBufferView(0);
	slotRootParameter[1].InitAsConstantBufferView(1);

	CD3DX12_ROOT_SIGNATURE_DESC rootSigDesc(
		2, slotRootParameter,
		0, nullptr,
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ID3DBlob* errorBlob = nullptr;
	D3D12SerializeRootSignature(&rootSigDesc,
		D3D_ROOT_SIGNATURE_VERSION_1,
		&mSerializedRootSignature,
		&errorBlob);

	return true;
}

void ColorShader::SetPassCB()
{
	mPc.viewProj = GameObjectManager::GetInstance()->GetCamera()->GetViewProjTranspose();
}

void ColorShader::SetObjectCB(RenderComponent* renderItem)
{
	mOc.world = renderItem->mGameObject->mTransform->GetSuperWorldMatrixTranspose();
	mOc.color = renderItem->mColor;
}

UploadBufferBase* ColorShader::OnCreatePassUploadBuffer() { return new UploadBuffer<PassConstColor>(mDevice, 1, true); }

UploadBufferBase* ColorShader::OnCreateObjectUploadBuffer() { return new UploadBuffer<ObjConstColor>(mDevice, 1, true); }