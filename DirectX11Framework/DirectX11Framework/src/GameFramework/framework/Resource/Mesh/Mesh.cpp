// メッシュ
// 2017.05.12	: プログラム作成
// author		: SyunMizuno



#include	"Mesh.h"
#include	"../../Graphic/Graphics.h"
#include	"../../Time/Time.h"

#include	"../../Debug/Debug.h"
#include	"../Texture/Texture.h"
#include	"../Manager/ResourceManager.h"
#include	"../../Path/Path.h"

struct SIMPLESHADER_CONSTANT_BUFFER {
	Matrix	mWorld;
	Matrix	mWVP;
	Vector4	vLightDir;
	Vector4	vDiffuse;
	Vector4	vEye;
};





Mesh::Mesh() :
	m_pMeshData(nullptr),
	m_pVertex(nullptr),
	m_pVertexBuffer(nullptr),
	m_pIndexBuffer(nullptr)
{
}


Mesh::~Mesh() {
	Delete();
}

bool Mesh::Create(const string fileName) {
	m_pMeshData = NEW Pmd(fileName);
	m_pVertex = NEW SimpleVertex[m_pMeshData->vert_count];
	for (int i = 0; i < m_pMeshData->vert_count; ++i) {
		m_pVertex[i].Pos = m_pMeshData->vertex[i].pos;
		m_pVertex[i].Normal = m_pMeshData->vertex[i].normal_vec;
		m_pVertex[i].Tex = m_pMeshData->vertex[i].uv;
	}

	// テクスチャ読み込み
	this->LoadTexture(fileName);

	// 頂点
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * m_pMeshData->vert_count;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = m_pVertex;
	auto device = GetDevice();
	HRESULT hr = device->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
	if (FAILED(hr))	return false;

	// インデックス
	D3D11_BUFFER_DESC Ibd;
	Ibd.Usage = D3D11_USAGE_DEFAULT;
	Ibd.ByteWidth = sizeof(unsigned short) * m_pMeshData->face_vert_count;
	Ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	Ibd.CPUAccessFlags = 0;
	Ibd.MiscFlags = 0;
	Ibd.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA InData;
	InData.pSysMem = m_pMeshData->face_vert_index;
	hr = device->CreateBuffer(&Ibd, &InData, &m_pIndexBuffer);
	if (FAILED(hr))	return false;

	// コンスタントバッファ―作成
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	hr = GetDevice()->CreateBuffer(&cb, NULL, &m_pConstantBuffer);
	if (FAILED(hr))	return false;

	return true;
}


void Mesh::LoadTexture(const string& fileName) {
	string dir = Path::GetDirectoryName(fileName);

	TCHAR szCurDir[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, szCurDir);
	SetCurrentDirectory(dir.c_str());

	for (int i = 0; i < m_pMeshData->material_count; ++i) {
		string name(m_pMeshData->material[i].texfile_name);
		if (name.empty())
			continue;

		GetResourceManager<Texture>()->Create(name);
	}

	SetCurrentDirectory(szCurDir);
}

void Mesh::Delete() {
	SAFE_DELETE_ARRAY(m_pVertex);
	SAFE_DELETE(m_pMeshData);
}


void Mesh::Draw(Camera* camera, Light* light) {
	auto context = Graphics::GetDevice();

	static float angle = 0.0f;
	angle += Time::GetDeltaTime();
	Matrix mWorld, mRot;
	MatrixRotationY(&mRot, angle);
	MatrixScaling(&mWorld, 0.07f, 0.07f, 0.07f);
	mWorld *= mRot;

	Vector3 pos = camera->GetTransform()->GetPos();

	D3D11_MAPPED_SUBRESOURCE pData;
	SIMPLESHADER_CONSTANT_BUFFER cb;
	HRESULT hr;

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	Graphics::GetDevice()->IASetVertexBuffers(
		0,
		1,
		&m_pVertexBuffer,
		&stride,
		&offset);
	Graphics::GetDevice()->IASetIndexBuffer(
		m_pIndexBuffer,
		DXGI_FORMAT_R16_UINT,
		0);

	MatrixTranspose(&cb.mWorld, &cb.mWorld);
	Matrix m = mWorld * camera->GetView() * camera->GetProj();
	MatrixTranspose(&m, &m);


	hr = context->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (FAILED(hr))	return;
	int cnt_idx = 0;	// インデックスカウンター
	for (int i = 0; i < m_pMeshData->material_count; ++i) {
		for (int j = 0; j < m_pMeshData->material[i].face_vert_count; ++j) {
			int pos_vec = m_pMeshData->face_vert_index[cnt_idx];
			++cnt_idx;
			cb.mWorld = mWorld;
			cb.mWVP = m;
//			cb.vDiffuse = m_pMeshData->material[pos_vec].diffuse;
			cb.vDiffuse = m_pMeshData->material[i].diffuse;
			cb.vLightDir = light->GetDirection4();
			cb.vEye = Vector4(pos.x, pos.y, pos.z, 1.0f);
			memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
			context->Unmap(m_pConstantBuffer, 0);
		}

		string texName(m_pMeshData->material[i].texfile_name);
		if (texName != "") {
			Texture* texture = GetResourceManager<Texture>()->Get(texName);
			auto samp = texture->GetSample();
			auto tex = texture->GetTexture();
			context->PSSetSamplers(0, 1, &samp);
			context->PSSetShaderResources(0, 1, &tex);
		}
	}
	// このコンスタントバッファーを使うシェーダの登録
	context->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	context->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->DrawIndexed(m_pMeshData->face_vert_count, 0, 0);
}