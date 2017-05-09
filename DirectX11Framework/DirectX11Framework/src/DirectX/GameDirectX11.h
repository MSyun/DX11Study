// �Q�[���pDirectX11
// 2016. 5.10	:	�v���O�����쐬
// author		:	SyunMizuno


#pragma once


#include	"../GameFramework/DirectX/GameDirectX11Base.h"



class GameDirectX11	:	public	GameDirectX11Base {
public:
	GameDirectX11(Application* app);
	virtual ~GameDirectX11();

private:
	HRESULT InitGame() override;
	HRESULT ReleaseGame() override;
	HRESULT InvalidateDeviceObjectsGame() override;
	HRESULT RestoreDeviceObjectsGame() override;
};