// リソースインターフェース
// 2017.04.24	: プログラム作成
// author		: SyunMizuno

#include	"IResource.h"
#include	"../../Debug/Debug.h"


namespace MSLib {

	ID3D11Device* IResource::m_pDevice = nullptr;

	/*									//
	//			デバイスの設定			//
	//									*/
	void IResource::SetDevice(ID3D11Device* device) {
		m_pDevice = device;

		Debug::Log("デバイスを生成");
	}


	/*									//
	//			デバイスの取得			//
	//									*/
	ID3D11Device* IResource::GetDevice() {
		return m_pDevice;
	}

}