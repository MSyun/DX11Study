// ゲーム用DirectX11
// 2016. 5.10	:	プログラム作成
// author		:	SyunMizuno


#include	"GameDirectX11.h"

#include	"../Scene/CheckScene.h"



GameDirectX11::GameDirectX11(Application* app) :
	GameDirectX11Base(app)
{
}

GameDirectX11::~GameDirectX11() {

}

HRESULT GameDirectX11::InitGame() {
	m_pSceneManager->RegistSceneMakeInstance<CheckScene>("Scene");
	m_pSceneManager->PushCommand("Scene");

	return S_OK;
}

HRESULT GameDirectX11::ReleaseGame() {
	return S_OK;
}

HRESULT GameDirectX11::InvalidateDeviceObjectsGame() {
	return S_OK;
}

HRESULT GameDirectX11::RestoreDeviceObjectsGame() {
	return S_OK;
}