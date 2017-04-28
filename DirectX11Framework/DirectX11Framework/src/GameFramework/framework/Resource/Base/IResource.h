// リソースインターフェース
// 2017.04.24	: プログラム作成
// author		: SyunMizuno


#pragma once
#include	<string>
#include	<D3D11.h>
#include	"../../Debug/Debug.h"
using namespace std;


class IResource {
private:
	// デバイス
	static ID3D11Device* m_pDevice;

public:

	/* デバイスの設定
	// device : 設定したいデバイス
	*/
	static void SetDevice(ID3D11Device* device);

	/* デバイスの取得
	// return : デバイス
	*/
	static ID3D11Device* GetDevice();

	/* 作成 */
	virtual bool Create(const string name) = 0;

	/* 削除 */
	virtual void Delete() = 0;
};