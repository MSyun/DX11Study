// ゲーム用DirectX11
// 2016. 5.10	:	プログラム作成
// author		:	SyunMizuno


#pragma once


#include	"../GameFramework/DirectX/GameDirectX11Base.h"


class GameDirectX11	:	public	MSLib::GameDirectX11Base {
public:
	explicit GameDirectX11(MSLib::Application* app);
	virtual ~GameDirectX11();

private:
	HRESULT InitGame() override;
	HRESULT ReleaseGame() override;
	HRESULT InvalidateDeviceObjectsGame() override;
	HRESULT RestoreDeviceObjectsGame() override;
};