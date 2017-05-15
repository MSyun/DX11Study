// メッシュ
// 2017.05.12	: プログラム作成
// author		: SyunMizuno



#include	"Mesh.h"
#include	"../../Graphic/Graphics.h"
#include	"../../Camera/Manager/CameraManager.h"
#include	"../../Time/Time.h"

#include	"../Texture/Texture.h"
#include	"../Manager/ResourceManager.h"
#include	"../../Path/Path.h"
#include	"../Shader/Base/Shader.h"


/*									//
//			コンストラクタ			//
//									*/
Mesh::Mesh() :
	m_pMeshData(nullptr),
	m_pVertex(nullptr),
	m_pVertexBuffer(nullptr),
	m_pIndexBuffer(nullptr)
{
}


/*									//
//			デストラクタ			//
//									*/
Mesh::~Mesh() {
	Delete();
}


/*									//
//				作成				//
//									*/
bool Mesh::Create(const string fileName) {
	Delete();

	m_pMeshData = new Pmd(fileName);
	m_pVertex = new SimpleVertex[m_pMeshData->vert_count];
	for (unsigned int i = 0; i < m_pMeshData->vert_count; ++i) {
		int pos_vec = m_pMeshData->face_vert_index[i];
		m_pVertex[i].Pos = m_pMeshData->vertex[i].pos;
		m_pVertex[i].Normal = m_pMeshData->vertex[i].normal_vec;
		m_pVertex[i].Tex = m_pMeshData->vertex[i].uv;
	}

	// テクスチャ読み込み
	this->LoadTexture(fileName);

	// 頂点
	if (!this->CreateVertex())
		goto MISS;

	// インデックス
	if (!this->CreateIndex())
		goto MISS;

	return true;


MISS:
	Delete();
	return false;
}


/*									//
//			テクスチャ読み込み		//
//									*/
void Mesh::LoadTexture(const string& fileName) {
	string dir = Path::GetDirectoryName(fileName);

	TCHAR szCurDir[_MAX_PATH];
	GetCurrentDirectory(_MAX_PATH, szCurDir);
	SetCurrentDirectory(dir.c_str());

	for (unsigned int i = 0; i < m_pMeshData->material_count; ++i) {
		string name(m_pMeshData->material[i].texfile_name);
		if (name.empty())
			continue;

		GetResourceManager<Texture>()->Create(name);
	}

	SetCurrentDirectory(szCurDir);
}


/*									//
//				頂点の作成			//
//									*/
bool Mesh::CreateVertex() {
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * m_pMeshData->vert_count;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = m_pVertex;
	HRESULT hr = GetDevice()->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
	if (FAILED(hr))	return false;

	return true;
}


/*									//
//		インデックスの作成			//
//									*/
bool Mesh::CreateIndex() {
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(unsigned short) * m_pMeshData->face_vert_count;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = m_pMeshData->face_vert_index;
	HRESULT hr = GetDevice()->CreateBuffer(&bd, &InitData, &m_pIndexBuffer);
	if (FAILED(hr))	return false;

	return true;
}


/*									//
//				削除				//
//									*/
void Mesh::Delete() {
	SAFE_DELETE_ARRAY(m_pVertex);
	SAFE_DELETE(m_pMeshData);
}


void Mesh::Draw(Matrix* mat) {
	auto context = Graphics::GetDevice();

	Shader* shader = GetResourceManager<Shader>()->Get("Phong.hlsl");

	static float angle = 0.0f;
	angle += Time::GetDeltaTime();
	Matrix mWorld, mRot;
	MatrixRotationY(&mRot, angle);
	MatrixScaling(&mWorld, 0.1f, 0.1f, 0.1f);
	mWorld *= mRot;

	Camera* camera = GetCameraManager()->CurrentCamera();
	Vector3 pos = camera->GetTransform()->GetPos();

	auto cb = shader->GetBuffer()->GetSetting();
	auto MatBuff = shader->GetBuffMat();

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

	cb->mWorld = mWorld;
	MatrixTranspose(&cb->mWorld, &cb->mWorld);
	Matrix m = mWorld * camera->GetView() * camera->GetProj();
	MatrixTranspose(&m, &m);
	cb->mWVP = m;

	for (unsigned int i = 0; i < m_pMeshData->material_count; ++i) {
		for (unsigned int j = 0; j < m_pMeshData->material[i].face_vert_count; ++j) {
			shader->GetBuffer()->BeginPass();
			cb->vEye = Vector4(pos.x, pos.y, pos.z, 1.0f);
			shader->GetBuffer()->EndPass();
		}

		string texName(m_pMeshData->material[i].texfile_name);
		if (texName != "") {
			Texture* texture = GetResourceManager<Texture>()->Get(texName);
			auto samp = texture->GetSample();
			auto tex = texture->GetTexture();
			context->PSSetSamplers(0, 1, &samp);
			context->PSSetShaderResources(0, 1, &tex);
		}

		MatBuff->BeginPass();
		MatBuff->Diffuse(m_pMeshData->material[i].diffuse);
		MatBuff->Ambient(m_pMeshData->material[i].ambient);
		MatBuff->Emissive(Vector3(0.0f, 0.0f, 0.0f));
		MatBuff->Alpha(m_pMeshData->material[i].alpha);
		MatBuff->Specular(m_pMeshData->material[i].specular);
		MatBuff->Shininess(m_pMeshData->material[i].specularity);
		MatBuff->EndPass();
	}

	context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	context->DrawIndexed(m_pMeshData->face_vert_count, 0, 0);
}

void Mesh::LateDraw(Matrix* mat) {

}