// Direct3Dデバッグフォントクラス宣言部
// 作成者		:	SyunMizuno
// 2015.11.28	:	プログラム作成
// 2016. 1. 2	:	InvalidateDeviceObjects,RestoreDeviceObjectsを追加
// 2016.12.31	:	Log関数追加
// 2017. 3.26	:	実装処理を.cppへ移動
//  HP    : http://www.h6.dion.ne.jp/~game296o/index.html

#pragma once

#pragma warning( disable : 4996 )

#include	<d3dx9.h>
#include	<string>
#include	<stdlib.h>
#include	"../Convert/Convert.h"


/*
	memo:
		_stprintfはUnicode,ANCIの両対応、有能
		インターフェースを作る事
*/


using namespace std;


class Debug {
public:
#pragma region method

	Debug();
	~Debug();

#pragma region Log
	// エディター上にログを表示
	static void Log(const string& message);
	static void Log(const Vector2& val);
	static void Log(const Vector3& val);
	static void Log(const Vector4& val);
	static void Log(const Quaternion& qua);
#pragma endregion

	// エラーログの表示
	// エディターがここで止まるのでF10で場所を確認してください
	static void LogError(const string& message);

	// デバイスロスト
	static HRESULT InvalidateDeviceObjects();

	// デバイスリセット
	static HRESULT RestoreDeviceObjects();

#pragma endregion
};