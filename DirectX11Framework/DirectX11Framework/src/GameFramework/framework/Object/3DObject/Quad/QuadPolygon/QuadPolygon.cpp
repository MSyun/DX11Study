// 板ポリゴンメッシュ
// 2017.05.15	: プログラム作成
// author		: SyunMizuno


#include	"QuadPolygon.h"
#include	"../../../../Convert/Convert.h"
#include	"../../../../Utility/System/SystemUtility.h"
#include	"../../../../Graphic/Graphics.h"
#include	"../../../../Resource/Manager/ResourceManager.h"
#include	"../../../../Camera/Manager/CameraManager.h"
#include	"../../../../Resource/Shader/Base/Shader.h"

namespace MSLib {

	struct SimpleVertex {
		Point3 Pos;
		Vector3 Normal;
		Vector2 Tex;
	};


	QuadPolygon::QuadPolygon() :
		m_pVertexBuffer(nullptr),
		m_Diffuse(1.0f, 1.0f, 1.0f),
		m_Alpha(1.0f),
		m_Ambient(0.2f, 0.2f, 0.2f),
		m_Emissive(0.0f, 0.0f, 0.0f),
		m_Specular(1.0f, 1.0f, 1.0f),
		m_Shininess(2)
	{
	}

	QuadPolygon::~QuadPolygon() {
		Delete();
	}

	bool QuadPolygon::Create() {
		HRESULT hr;
		auto device = IResource::GetDevice();

		// バーテックスバッファー作成
		SimpleVertex vertices[] = {
			Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0, 1),
			Vector3(-0.5f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0, 0),
			Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1, 1),
			Vector3(0.5f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1, 0),
		};
		D3D11_BUFFER_DESC bd;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(SimpleVertex) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData;
		InitData.pSysMem = vertices;
		hr = device->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
		if (FAILED(hr))	return false;

		return true;
	}

	void QuadPolygon::Delete() {
		SAFE_RELEASE(m_pVertexBuffer);
	}


	void QuadPolygon::Draw(Matrix* world) {
		auto context = Graphics::GetDevice();

		std::shared_ptr<Shader> shader = GetResourceManager<Shader>()->Get("Phong.hlsl");
		Camera* camera = GetCameraManager()->CurrentCamera();
		Vector3 pos = camera->GetTransform()->GetPos();

		UINT stride = sizeof(SimpleVertex);
		UINT offset = 0;
		Graphics::GetDevice()->IASetVertexBuffers(
			0,
			1,
			&m_pVertexBuffer,
			&stride,
			&offset);

		auto MeshBuff = shader->GetBuffMesh();
		Matrix m = *world;
		MatrixTranspose(&m, &m);
		MeshBuff->World(m);
		// ワールド、カメラ、射影行列を渡す
		m = *world * camera->GetView() * camera->GetProj();
		MatrixTranspose(&m, &m);
		MeshBuff->WVP(m);
		MeshBuff->Set();

		auto FrameBuff = shader->GetBuffFrame();
		FrameBuff->EyePos(Vector4(pos.x, pos.y, pos.z, 0.0f));
		FrameBuff->Set();

		auto MatBuff = shader->GetBuffMat();
		MatBuff->Diffuse(m_Diffuse);
		MatBuff->Alpha(m_Alpha);
		MatBuff->Ambient(m_Ambient);
		MatBuff->Emissive(m_Emissive);
		MatBuff->Specular(m_Specular);
		MatBuff->Shininess(m_Shininess);
		MatBuff->Set();

		// プリミティブ・トポロジーをセット
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// テクスチャ―をシェーダに渡す
		if (m_pTexture) {
			auto samp = m_pTexture->GetSample();
			auto tex = m_pTexture->GetTexture();
			context->PSSetSamplers(0, 1, &samp);
			context->PSSetShaderResources(0, 1, &tex);
		}

		context->Draw(4, 0);
	}


	void QuadPolygon::SetTexture(Texture* tex) {
		m_pTexture = tex;
	}

};