// グラフィック
// 2017. 4.24	プログラム作成
// author	:	SyunMizuno


#include	"Graphics.h"


ID3D11DeviceContext* Graphics::m_pDeviceContext = nullptr;



/*									//
//			コンストラクタ			//
//									*/
Graphics::Graphics() {

}


/*									//
//			デストラクタ			//
//									*/
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