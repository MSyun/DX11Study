// ゲーム用DirectX11
// 2016. 5.10	:	プログラム作成
// author		:	SyunMizuno


#include	"CheckScene.h"
#include	"../GameFramework/framework/Graphic/Graphics.h"
#include	"../GameFramework/framework/Time/Time.h"
#include	"../GameFramework/framework/Resource/Manager/ResourceManager.h"

struct SimpleVertex {
	Point3 Pos;
	Vector3 Normal;
	Vector2 Tex;
};

CheckScene::CheckScene() :
	m_pVertexBuffer(nullptr),
	m_pCamera(nullptr),
	m_pLight(nullptr)
{
}

CheckScene::~CheckScene() {

}

bool CheckScene::Init() {
	CreatePolygon();

	m_pMesh = GetResourceManager<Mesh>()->Create("data/Mesh/Watch/Watch.pmd");
//	m_pMesh = GetResourceManager<Mesh>()->Create("data/Mesh/miku/kio_miku_20111121.pmd");
//	m_pMesh = GetResourceManager<Mesh>()->Create("data/Mesh/miku1/初音ミク_アノマロver.pmd");
//	m_pMesh = GetResourceManager<Mesh>()->Create("data/Mesh/miku2/初音ミク@七葉1052式.pmd");
	m_pShader = GetResourceManager<Shader>()->Create("Phong.hlsl");

	return true;
}

void CheckScene::Release() {
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pLight);

	SAFE_RELEASE(m_pVertexBuffer);
}

void CheckScene::Update() {

}

void CheckScene::Draw() {
	auto context = Graphics::GetDevice();

	Matrix mWorld;
	// ワールドトランスフォーム（絶対座標変換）
	static float an = 0.0f;
	an -= Time::GetDeltaTime();
	MatrixRotationY(&mWorld, an);

	// カメラ
	m_pCamera->Set();
	Vector3 pos = m_pCamera->GetTransform()->GetPos();

	// 使用するシェーダの登録
	m_pShader->Begin();

	// ライト
	auto LightBuff = m_pShader->GetBuffLight();
	LightBuff->BeginPass();
	Color col;
	col = m_pLight->GetColor(Light::LIGHT_DIFFUSE);
	LightBuff->Diffuse(Vector3(col.r, col.g, col.b));
	col = m_pLight->GetColor(Light::LIGHT_AMBIENT);
	LightBuff->Ambient(Vector3(col.r, col.g, col.b));
	col = m_pLight->GetColor(Light::LIGHT_SPECULAR);
	LightBuff->Specular(Vector3(col.r, col.g, col.b));
	LightBuff->Direction(m_pLight->GetDirection4());
	LightBuff->EndPass();

	// シェーダのコンスタントバッファーに各種データを渡す
	auto cb = m_pShader->GetBuffer()->GetSetting();

	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	Graphics::GetDevice()->IASetVertexBuffers(
		0,
		1,
		&m_pVertexBuffer,
		&stride,
		&offset);

	m_pShader->GetBuffer()->BeginPass();

	cb->mWorld = mWorld;
	MatrixTranspose(&cb->mWorld, &cb->mWorld);
	// ワールド、カメラ、射影行列を渡す
	Matrix m = mWorld * m_pCamera->GetView() * m_pCamera->GetProj();
	MatrixTranspose(&m, &m);
	cb->mWVP = m;
	// カメラの位置（視点）をシェーダに渡す
	cb->vEye = Vector4(pos.x, pos.y, pos.z, 0.0f);

	m_pShader->GetBuffer()->EndPass();

	auto MatBuff = m_pShader->GetBuffMat();
	MatBuff->BeginPass();
	MatBuff->Diffuse(Vector3(1.0f, 1.0f, 1.0f));
	MatBuff->Ambient(Vector3(1.0f, 1.0f, 1.0f));
	MatBuff->Alpha(1.0f);
	MatBuff->Emissive(Vector3(0.0f, 0.0f, 0.0f));
	MatBuff->Shininess(5);
	MatBuff->EndPass();

	// プリミティブ・トポロジーをセット
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// テクスチャ―をシェーダに渡す
	auto samp = m_pTexture->GetSample();
	auto tex = m_pTexture->GetTexture();
	context->PSSetSamplers(0, 1, &samp);
	context->PSSetShaderResources(0, 1, &tex);

	// プリミティブをレンダリング
	context->Draw(4, 0);
	GetGraphics()->SetBlend(BlendType::BLEND_NORMAL);
	m_pMesh->Draw(m_pCamera, m_pLight, m_pShader);

	m_pShader->End();
}


void CheckScene::CreatePolygon() {
	HRESULT hr;
	ID3D11Device* device = IResource::GetDevice();

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
	if (FAILED(hr))	return;

	// バーテックスバッファーをセット
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	Graphics::GetDevice()->IASetVertexBuffers(
		0,
		1,
		&m_pVertexBuffer,
		&stride,
		&offset);

	m_pTexture = GetResourceManager<Texture>()->Create("data/Texture/Sprite.jpg");
	m_pCamera = new Camera;
	m_pCamera->GetTransform()->SetPos(0.0f, 2.0f, -4.0f);
	m_pCamera->GetTransform()->Rotate(-25.0f, 0.0f, 0.0f);
	m_pLight = new Light;
	m_pLight->GetTransform()->SetPos(0.0f, 2.0f, -4.0f);
	m_pLight->GetTransform()->Rotate(-25.0f, 0.0f, 0.0f);
}