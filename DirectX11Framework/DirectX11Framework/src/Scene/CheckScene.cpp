// ゲーム用DirectX11
// 2016. 5.10	:	プログラム作成
// author		:	SyunMizuno


#include	"CheckScene.h"
#include	"../GameFramework/framework/Graphic/Graphics.h"
#include	"../GameFramework/framework/Time/Time.h"
#include	"../GameFramework/framework/Resource/Manager/ResourceManager.h"
#include	"../GameFramework/framework/Camera/Manager/CameraManager.h"
#include	"../GameFramework/framework/Object/3DObject/Manager/Object3DManager.h"



CheckScene::CheckScene() :
	m_pLight(nullptr),
	m_pObj(nullptr)
{
}

CheckScene::~CheckScene() {

}

bool CheckScene::Init() {
	GetGraphics()->SetBlend(BlendType::BLEND_NORMAL);

	Camera* camera = GetCameraManager()->Create("mainCamera");
	camera->GetTransform()->SetPos(0.0f, 2.0f, -4.0f);
	camera->GetTransform()->Rotate(-25.0f, 0.0f, 0.0f);
	m_pLight = new Light;
	m_pLight->GetTransform()->SetPos(0.0f, 2.0f, -4.0f);
	m_pLight->GetTransform()->Rotate(-25.0f, 0.0f, 0.0f);

	m_pQuad = new Quad;
	m_pQuad->GetPolygon()->SetTexture(GetResourceManager<Texture>()->Get("data/Texture/Sprite.jpg"));

	m_pObj = new Object3D;
	m_pObj->SetModel(GetResourceManager<Mesh>()->Create("data/Mesh/Watch/Watch.pmd"));

	m_pShader = GetResourceManager<Shader>()->Create("Phong.hlsl");

	return true;
}

void CheckScene::Release() {
	GetObject3DManager()->AllClear();
}

void CheckScene::Update() {
	m_pQuad->GetTransform()->Rotate(0.0f, 180.0f * Time::GetDeltaTime(), 0.0f);

	GetObject3DManager()->Update();
	GetObject3DManager()->LateUpdate();
	GetObject3DManager()->CheckDestroy();
}

void CheckScene::Draw() {
	// カメラ
	GetCameraManager()->Set("mainCamera");

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
	LightBuff->Alpha(col.a);
	LightBuff->EndPass();

	// プリミティブをレンダリング
	GetObject3DManager()->Draw();
	GetObject3DManager()->LateDraw();

	m_pShader->End();
}