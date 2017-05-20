// ゲーム用DirectX11
// 2016. 5.10	:	プログラム作成
// author		:	SyunMizuno


#include	"CheckScene.h"
#include	"../GameFramework/framework/Graphic/Graphics.h"
#include	"../GameFramework/framework/Time/Time.h"
#include	"../GameFramework/framework/Resource/Manager/ResourceManager.h"
#include	"../GameFramework/framework/Camera/Manager/CameraManager.h"
#include	"../GameFramework/framework/Object/3DObject/Manager/Object3DManager.h"
#include	"../GameFramework/framework/Archives/Archives.h"
#include	"../GameFramework/framework/Light/Manager/LightManager.h"

#include	"../GameFramework/framework/Input/Input.h"

using namespace MSLib;

CheckScene::CheckScene() {
}

CheckScene::~CheckScene() {

}

bool CheckScene::Init() {
	Object3D* obj;

	m_pObj = new Object3D;
	m_pObj->SetModel(GetResourceManager<Mesh>()->Get(Archives::Mesh("Miku2")));
	m_pObj->GetTransform()->Translate(-3.0f, 0.0f, 0.0f);
	m_pObj->GetTransform()->SetScale(0.3f, 0.3f, 0.3f);
	m_pObj->DontDestroyOnLoad();

	obj = new Object3D;
	obj->SetModel(GetResourceManager<Mesh>()->Get(Archives::Mesh("Watch")));
	obj->GetTransform()->SetScale(0.2f, 0.2f, 0.2f);

	obj = new Camera;
	obj->SetName("mainCamera");
	obj->GetTransform()->SetPos(10.0f, 5.0f, -10.0f);
	obj->GetTransform()->LookAt(m_pObj->GetTransform());

	obj = new Light;
	obj->SetName("Direction");
	obj->GetTransform()->SetPos(10.0f, 5.0f, -10.0f);
	obj->GetTransform()->Rotate(-25.0f, 0.0f, 0.0f);
	obj->GetTransform()->LookAt(m_pObj->GetTransform());

	m_pShader = GetResourceManager<Shader>()->Create(Archives::Shader("Default/Phong"));

	return true;
}

void CheckScene::Release() {
	GetObject3DManager()->AllClear();
}

void CheckScene::Update() {
	float angle = 180.0f * Time::GetDeltaTime();

	if (Input::GetKeyPress(DIK_DOWN)) {
		m_pObj->GetTransform()->Rotate(angle, 0.0f, 0.0f);
	}
	if (Input::GetKeyPress(DIK_UP)) {
		m_pObj->GetTransform()->Rotate(-angle, 0.0f, 0.0f);
	}
	if (Input::GetKeyPress(DIK_RIGHT)) {
		m_pObj->GetTransform()->Rotate(0.0f, angle, 0.0f);
	}
	if (Input::GetKeyPress(DIK_LEFT)) {
		m_pObj->GetTransform()->Rotate(0.0f, -angle, 0.0f);
	}
	if (Input::GetKeyTrigger(DIK_RETURN)) {
		m_pObj->Destroy();
	}

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
	Light* light = GetLightManager()->Get("Direction");
	auto LightBuff = m_pShader->GetBuffLight();
	LightBuff->BeginPass();
	Color col;
	col = light->GetColor(Light::LIGHT_DIFFUSE);
	LightBuff->Diffuse(Vector3(col.r, col.g, col.b));
	col = light->GetColor(Light::LIGHT_AMBIENT);
	LightBuff->Ambient(Vector3(col.r, col.g, col.b));
	col = light->GetColor(Light::LIGHT_SPECULAR);
	LightBuff->Specular(Vector3(col.r, col.g, col.b));
	LightBuff->Direction(light->GetDirection4());
	LightBuff->Alpha(col.a);
	LightBuff->EndPass();

	// プリミティブをレンダリング
	GetGraphics()->SetBlend(BlendType::BLEND_NORMAL);
	GetGraphics()->SetAlphaEnable(false);
	GetObject3DManager()->Draw();
	GetGraphics()->SetAlphaEnable(true);
	GetObject3DManager()->LateDraw();

	m_pShader->End();
}