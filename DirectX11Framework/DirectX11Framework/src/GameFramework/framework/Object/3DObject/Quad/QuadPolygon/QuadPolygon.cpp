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


struct SimpleVertex {
	Point3 Pos;
	Vector3 Normal;
	Vector2 Tex;
};


QuadPolygon::QuadPolygon() :
	m_pVertexBuffer(nullptr)
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

	Shader* shader = GetResourceManager<Shader>()->Get("Phong.hlsl");
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

	// シェーダのコンスタントバッファーに各種データを渡す
	auto cb = shader->GetBuffer()->GetSetting();

	shader->GetBuffer()->BeginPass();

	cb->mWorld = *world;
	MatrixTranspose(&cb->mWorld, &cb->mWorld);
	// ワールド、カメラ、射影行列を渡す
	Matrix m = *world * camera->GetView() * camera->GetProj();
	MatrixTranspose(&m, &m);
	cb->mWVP = m;
	// カメラの位置（視点）をシェーダに渡す
	cb->vEye = Vector4(pos.x, pos.y, pos.z, 0.0f);

	shader->GetBuffer()->EndPass();

	auto MatBuff = shader->GetBuffMat();
	MatBuff->BeginPass();
	MatBuff->Diffuse(Vector3(1.0f, 1.0f, 1.0f));
	MatBuff->Ambient(Vector3(1.0f, 1.0f, 1.0f));
	MatBuff->Alpha(1.0f);
	MatBuff->Emissive(Vector3(0.0f, 0.0f, 0.0f));
	MatBuff->Shininess(1);
	MatBuff->EndPass();

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