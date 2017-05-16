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

#include	"../GameFramework/framework/Input/Input.h"

CheckScene::CheckScene() {
}

CheckScene::~CheckScene() {

}

bool CheckScene::Init() {
	Object3D* obj;


	m_pQuad = new Quad;
	m_pQuad->GetPolygon()->SetTexture(GetResourceManager<Texture>()->Get("data/Texture/Sprite.jpg"));
//	m_pQuad->GetTransform()->Rotate(-90.0f, 0.0f, 0.0f);
	m_pQuad->GetTransform()->SetScale(10.0f, 10.0f, 10.0f);

	m_pObj = new Object3D;
	m_pObj->SetModel(GetResourceManager<Mesh>()->Get(Archives::Mesh("Watch")));
	m_pObj->GetTransform()->Translate(-3.0f, 0.0f, 0.0f);
	m_pObj->GetTransform()->SetScale(0.2f, 0.2f, 0.2f);

	//obj = new Object3D;
	//obj->SetModel(GetResourceManager<Mesh>()->Get(Archives::Mesh("Watch")));
	//obj->GetTransform()->Translate(3.0f, 0.0f, -3.0f);
	//obj->GetTransform()->SetScale(0.05f, 0.05f, 0.05f);

	//obj = new Object3D;
	//obj->SetModel(GetResourceManager<Mesh>()->Get(Archives::Mesh("Watch")));
	//obj->GetTransform()->Translate(-3.0f, 0.0f, 0.0f);
	//obj->GetTransform()->SetScale(0.05f, 0.05f, 0.05f);

	obj = GetCameraManager()->Create("mainCamera");
	obj->GetTransform()->SetPos(10.0f, 5.0f, -10.0f);
	obj->GetTransform()->LookAt(m_pObj->GetTransform());

	m_pLight = new Light;
	m_pLight->GetTransform()->SetPos(10.0f, 5.0f, -10.0f);
	m_pLight->GetTransform()->Rotate(-25.0f, 0.0f, 0.0f);
	m_pLight->GetTransform()->LookAt(m_pObj->GetTransform());

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

	m_pQuad->GetTransform()->Rotate(0.0f, 90.0f * Time::GetDeltaTime(), 0.0f);

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
	GetGraphics()->SetBlend(BlendType::BLEND_NORMAL);
	GetGraphics()->SetAlphaEnable(false);
	GetObject3DManager()->Draw();
	GetGraphics()->SetAlphaEnable(true);
	GetObject3DManager()->LateDraw();

	m_pShader->End();
}