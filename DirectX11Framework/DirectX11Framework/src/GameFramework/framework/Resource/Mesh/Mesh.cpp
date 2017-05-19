// メッシュ
// 2017.05.12	: プログラム作成
// author		: SyunMizuno

#include	"Mesh.h"
#include	"../../Graphic/Graphics.h"
#include	"../../Camera/Manager/CameraManager.h"
#include	"../Texture/Texture.h"
#include	"../Manager/ResourceManager.h"
#include	"../../Path/Path.h"
#include	"../Shader/Base/Shader.h"


namespace MSLib {

	Mesh::Mesh() :
		m_pMeshData(nullptr),
		m_pVertex(nullptr),
		m_pVertexBuffer(nullptr)
	{
	}


	Mesh::~Mesh() {
		Delete();
	}


	/*									//
	//				作成				//
	//									*/
	bool Mesh::Create(const std::string& name) {
		Delete();

		m_pMeshData = new Pmd(name);
		m_pVertex = new SimpleVertex[m_pMeshData->vert_count];
		for (unsigned int i = 0; i < m_pMeshData->vert_count; ++i) {
			int pos_vec = m_pMeshData->face_vert_index[i];
			m_pVertex[i].Pos = m_pMeshData->vertex[i].pos;
			m_pVertex[i].Normal = m_pMeshData->vertex[i].normal_vec;
			m_pVertex[i].Tex = m_pMeshData->vertex[i].uv;
		}

		// テクスチャ読み込み
		this->LoadTexture(name);

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
	void Mesh::LoadTexture(const std::string& fileName) {
		string dir = Path::GetDirectoryName(fileName);

		TCHAR szCurDir[_MAX_PATH];
		GetCurrentDirectory(_MAX_PATH, szCurDir);
		SetCurrentDirectory(dir.c_str());

		for (unsigned int i = 0; i < m_pMeshData->material_count; ++i) {
			std::string name(m_pMeshData->material[i].texfile_name);
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
		int hoge = 0;
		for (unsigned int i = 0; i < m_pMeshData->material_count; ++i) {
			ID3D11Buffer* buffer;
			D3D11_BUFFER_DESC bd;
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(unsigned short) * m_pMeshData->material[i].face_vert_count;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;
			bd.MiscFlags = 0;
			bd.StructureByteStride = sizeof(unsigned short);

			D3D11_SUBRESOURCE_DATA InitData;
			// マテリアル事の先頭アドレス
			InitData.pSysMem = &m_pMeshData->face_vert_index[hoge];
			HRESULT hr = GetDevice()->CreateBuffer(&bd, &InitData, &buffer);
			hoge += m_pMeshData->material[i].face_vert_count;
			if (FAILED(hr))	return false;

			m_vecIndexBuffer.push_back(buffer);
		}

		return true;
	}


	/*									//
	//				削除				//
	//									*/
	void Mesh::Delete() {
		SAFE_DELETE_ARRAY(m_pVertex);
		SAFE_DELETE(m_pMeshData);
	}


	/*									//
	//				描画				//
	//									*/
	void Mesh::Draw(Matrix* mat, _eAlphaCheck type) {
		auto context = Graphics::GetDevice();

//		Shader* shader = GetResourceManager<Shader>()->Get("Phong.hlsl");
		shared_ptr<Shader> shader = GetResourceManager<Shader>()->Get("Phong.hlsl");

		Camera* camera = GetCameraManager()->CurrentCamera();
		Vector3 pos = camera->GetTransform()->GetPos();

		auto MatBuff = shader->GetBuffMat();

		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		Graphics::GetDevice()->IASetVertexBuffers(
			0,
			1,
			&m_pVertexBuffer,
			&stride,
			&offset);

		auto MeshBuff = shader->GetBuffMesh();
		MeshBuff->BeginPass();
		Matrix m;
		m = *mat;
		MatrixTranspose(&m, &m);
		MeshBuff->World(m);
		m = *mat * camera->GetView() * camera->GetProj();
		MatrixTranspose(&m, &m);
		MeshBuff->WVP(m);
		MeshBuff->EndPass();

		auto FrameBuff = shader->GetBuffFrame();
		FrameBuff->BeginPass();
		FrameBuff->EyePos(Vector4(pos.x, pos.y, pos.z, 1.0f));
		FrameBuff->EndPass();

		for (unsigned int i = 0; i < m_pMeshData->material_count; ++i) {
			if (!CheckAlpha(type, m_pMeshData->material[i].alpha)) {
				continue;
			}

			Graphics::GetDevice()->IASetIndexBuffer(
				m_vecIndexBuffer[i],
				DXGI_FORMAT_R16_UINT,
				0);

			MatBuff->BeginPass();
			MatBuff->Diffuse(m_pMeshData->material[i].diffuse);
			MatBuff->Ambient(m_pMeshData->material[i].ambient);
			MatBuff->Emissive(Vector3(0.0f, 0.0f, 0.0f));
			MatBuff->Alpha(m_pMeshData->material[i].alpha);
			MatBuff->Specular(m_pMeshData->material[i].specular);
			MatBuff->Shininess(m_pMeshData->material[i].specularity);
			MatBuff->EndPass();

			string texName(m_pMeshData->material[i].texfile_name);
			if (texName != "") {
//				Texture* texture = GetResourceManager<Texture>()->Get(texName);
				shared_ptr<Texture> texture = GetResourceManager<Texture>()->Get(texName);
				auto samp = texture->GetSample();
				auto tex = texture->GetTexture();
				context->PSSetSamplers(0, 1, &samp);
				context->PSSetShaderResources(0, 1, &tex);
			}

			context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			context->DrawIndexed(m_pMeshData->material[i].face_vert_count, 0, 0);
		}
	}

	bool Mesh::CheckAlpha(_eAlphaCheck type, float alpha) {
		switch (type) {
		case CHECK_ALL:
			return true;

		case CHECK_ALPHA:
			if (alpha < 1.0f)
				return true;
			break;

		case CHECK_NOALPHA:
			if (alpha >= 1.0f)
				return true;
			break;
		};

		return false;
	}

}