// グラフィック
// 2017. 4.24	プログラム作成
// author	:	SyunMizuno


#pragma once


#include	<D3DX11.h>
#include	"IGraphics/IGraphics.h"
#include	"../Singleton/Singleton.h"
#include	"Blend/GraphicBlend.h"



class Graphics	:	public	IGraphics,	public	Singleton<Graphics> {
private:
	static ID3D11DeviceContext*	m_pDeviceContext;
	static GraphicBlend m_Blend;

public:
	Graphics();
	virtual ~Graphics();

	static ID3D11DeviceContext* GetDevice();
	static void SetDevice(ID3D11DeviceContext* _dev);

	// ブレンドを設定
	static void SetBlend(BlendType type);

	// 透過を設定
	static void SetAlphaEnable(const bool alpha);

//#pragma region Z Enable
//	// Zバッファを使用するか設定
//	virtual void SetZEnable(bool flg);
//	// Zバッファの設定を取得
//	// true. 使用中 : false. 未使用
//	virtual bool GetZEnable();
//#pragma endregion
//
//#pragma region Wrap Mode
//	// Wrapの設定
//	virtual void SetWrapMode(_eWrapMode mode, _eWrapVec vec = WRAPVEC_UV);
//	// Wrapの取得
//	virtual _eWrapMode GetWrapMode(_eWrapVec vec);
//#pragma endregion
//
//#pragma region Cull Mode
//	// Cullingの設定
//	virtual void SetCullMode(_eCullMode mode);
//	// Cullingの取得
//	virtual _eCullMode GetCullMode();
//#pragma endregion
//
//
//private:
//	// Wrapから数字へ変更
//	DWORD WrapModeToNum(_eWrapMode mode);
//	// 数字からWrapへ変更
//	_eWrapMode NumToWrapMode(DWORD num);
};


inline Graphics* GetGraphics() {
	return Graphics::Instance();
}