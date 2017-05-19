// グラフィック
// 2017. 4.24	プログラム作成
// author	:	SyunMizuno

#include	"Graphics.h"
#include	"../Resource/Base/IResource.h"


namespace MSLib {

	ID3D11DeviceContext* Graphics::m_pDeviceContext = nullptr;

	Graphics::Graphics() {

	}

	Graphics::~Graphics() {

	}


	/*									//
	//			デバイスの取得			//
	//									*/
	ID3D11DeviceContext* Graphics::GetDevice() {
		return m_pDeviceContext;
	}


	/*									//
	//			デバイスの設定			//
	//									*/
	void Graphics::SetDevice(ID3D11DeviceContext* _dev) {
		m_pDeviceContext = _dev;
	}


	/*									//
	//			ブレンドの設定			//
	//									*/
	void Graphics::SetBlend(BlendType type) {
		m_Blend.Set(type, IResource::GetDevice(), GetDevice());
	}

	void Graphics::SetAlphaEnable(const bool alpha) {
		m_Blend.SetAlphaEnable(alpha, IResource::GetDevice(), GetDevice());
	}

};