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
#include	"../GameFramework/framework/Resource/Shader/Phong/Phong.h"
#include	"../GameFramework/framework/Resource/Shader/Fog/Fog.h"

using namespace MSLib;


CheckScene::CheckScene() {
}

CheckScene::~CheckScene() {

}

bool CheckScene::Init() {
	Object3D* obj;

	m_pObj = new Object3D;
	m_pObj->SetModel(GetResourceManager<Mesh>()->Get(Archives::Mesh("Watch")));
	m_pObj->GetTransform()->Translate(-3.0f, 0.0f, 0.0f);
	m_pObj->GetTransform()->SetScale(0.3f, 0.3f, 0.3f);

	obj = new Object3D;
	obj->SetModel(GetResourceManager<Mesh>()->Get(Archives::Mesh("Watch")));
	obj->GetTransform()->SetScale(5.0f, 0.1f, 5.0f);
	obj->GetTransform()->SetPos(0.0f, -2.0f, 0.0f);

	obj = new Camera;
	obj->SetName("mainCamera");
	obj->GetTransform()->SetPos(10.0f, 10.0f, -30.0f);
	obj->GetTransform()->LookAt(m_pObj->GetTransform());

	obj = new Light;
	obj->SetName("Direction");
	obj->GetTransform()->SetPos(10.0f, 5.0f, -10.0f);
	obj->GetTransform()->Rotate(-25.0f, 0.0f, 0.0f);
	obj->GetTransform()->LookAt(m_pObj->GetTransform());

//	m_pShader = GetResourceManager<Shader>()->Create(Archives::Shader("Default/Phong"));
	ShaderCollection::Fog* shader = new ShaderCollection::Fog;
	ShaderCollection::Fog::Instance()->Create();

	return true;
}

void CheckScene::Release() {
	GetResourceManager<Mesh>()->Delete(Archives::Mesh("Watch"));
	auto shader = ShaderCollection::Fog::Instance();
	SAFE_DELETE(shader);
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
//	m_pShader->Begin();
	auto shader = ShaderCollection::Fog::Instance();
	shader->Begin();

	// ライト
	Light* light = GetLightManager()->Get("Direction");
	auto LightBuff = shader->GetBuffLight();
	Color col;
	col = light->GetColor(Light::LIGHT_DIFFUSE);
	LightBuff->Diffuse(Vector3(col.r, col.g, col.b));
	col = light->GetColor(Light::LIGHT_AMBIENT);
	LightBuff->Ambient(Vector3(col.r, col.g, col.b));
	col = light->GetColor(Light::LIGHT_SPECULAR);
	LightBuff->Specular(Vector3(col.r, col.g, col.b));
	LightBuff->Direction(light->GetDirection4());
	LightBuff->Alpha(col.a);
	LightBuff->Set();

	// プリミティブをレンダリング
	GetGraphics()->SetBlend(BlendType::BLEND_NORMAL);
	GetGraphics()->SetAlphaEnable(false);
	GetObject3DManager()->Draw();
	GetGraphics()->SetAlphaEnable(true);
	GetObject3DManager()->LateDraw();

//	m_pShader->End();
	shader->End();
}