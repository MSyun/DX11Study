// スカイドーム
// 2017.05.21	: プログラム作成
// author		: SyunMizuno


#include	"Skydome.h"
#include	"../Archives/Archives.h"
#include	"../Resource/Manager/ResourceManager.h"


namespace MSLib {

	Skydome::Skydome() {
		SetModel(GetResourceManager<Mesh>()->Get(Archives::Mesh("Skydome")));
		SetName("Skydome");
	}

	Skydome::~Skydome() {
		GetResourceManager<Mesh>()->Delete(Archives::Mesh("Skydomw"));
	}

	void Skydome::Update() {
		Object3D::Update();
	}

	void Skydome::Draw() {
		//DWORD Z, L;
		//LPDIRECT3DDEVICE9 pDevice = GetGraphics()->GetDevice();
		//pDevice->GetRenderState(D3DRS_ZWRITEENABLE, &Z);
		//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		//pDevice->GetRenderState(D3DRS_LIGHTING, &L);
		//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		Object3D::Draw();
		//pDevice->SetRenderState(D3DRS_LIGHTING, L);
		//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, Z);
	}

}