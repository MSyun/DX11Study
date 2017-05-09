// リソースマネージャー
// 2017.04.24	: プログラム作成
// author		: SyunMizuno


#pragma once

#include	<map>
using namespace std;
#include	"../../Singleton/Singleton.h"


template<class T>
class ResourceManager	:	public	Singleton<ResourceManager<T>> {
protected:
#pragma region variable

	// リソースマップ
	map<string, T*>	m_MapResources;

	// 削除補助機能
	bool m_bHelper;

#pragma endregion

public:
#pragma region method

	ResourceManager();

	virtual ~ResourceManager();

	/* 作成
	// name		: 作成したいファイル名
	// return	: 生成したインスタンス
	*/
	T* Create(const string name);

	/* 削除
	// name		: 削除したいファイル名
	// return	: true. 成功、 false. 失敗
	*/
	bool Delete(const string name);

	/* 取得
	// name		: 取得したいファイル名
	// return	: 生成したインスタンス
	*/
	T* Get(const string name);

	/* 補助機能設定
	// helper	: 補助機能 ON : OFF
	*/
	void SetHelper(bool helper);

#pragma endregion
};

template<class T>
inline ResourceManager<T>* GetResourceManager();


#include	"ResourceManager.inl"