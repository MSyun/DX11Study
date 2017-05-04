// リソースマネージャー
// 2017.04.24	: プログラム作成
// author		: SyunMizuno


#pragma once

#include	"../Base/IResource.h"
#include	<map>
#include	"../../Utility/System/SystemUtility.h"
#include	"../../Debug/Debug.h"
#include	<typeinfo>
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

	/* コンストラクタ */
	ResourceManager() :
		m_bHelper(true)
	{
		m_MapResources.clear();
		SetHelper(m_bHelper);
	}

	/* デストラクタ */
	virtual ~ResourceManager() {
		if (!m_bHelper)	return;

		map<string, T*>::iterator it = m_MapResources.begin();

		// 全要素削除
		while (it != m_MapResources.end()) {
			SAFE_DELETE(it->second);
			++it;
		}

		m_MapResources.clear();
	}

	/* 作成
	// name		: 作成したいファイル名
	// return	: 生成したインスタンス
	*/
	T* Create(const string name) {
		if (name.empty()) {
			Debug::LogError("ファイル名がありません");
			return nullptr;
		}

		// 登録済みか確認
		if (m_MapResources.end() != m_MapResources.find(name)) {
			Debug::Log("リソース : " + name + " は既に作成済みです");
			return Get(name);
		}

		T* resource = new T;
		if (!resource->Create(name)) {
			Debug::LogError("リソース : " + name + " の作成に失敗しました");
			SAFE_DELETE(resource);
			return nullptr;
		}

		// 登録
		Debug::Log(string(typeid(T).name()) + " : " + name + " を作成");
		m_MapResources.insert(pair<string, T*>(name, resource));

		return resource;
	}

	/* 削除
	// name		: 削除したいファイル名
	// return	: true. 成功、 false. 失敗
	*/
	bool Delete(const string name) {
		// 検索
		auto it = m_MapResources.find(name);

		// 登録確認
		if (it == m_MapResources.end()) {
			Debug::Log("リソース : " + name + " は登録されていないため削除できません");
			return false;
		}

		// 削除
		it->second->Delete();
		SAFE_DELETE(it->second);

		m_MapResources.erase(name)

		return true;
	}

	/* 取得
	// name		: 取得したいファイル名
	// return	: 生成したインスタンス
	*/
	T* Get(const string name) {
		// 検索
		auto it = m_MapResources.find(name);

		if (it == m_MapResources.end()) {
			return Create(name);
		}

		return it->second;
	}

	/* 補助機能設定
	// helper	: 補助機能 ON : OFF
	*/
	void SetHelper(bool helper) {
		const type_info& id = typeid(T);
		string swit = (helper ? "ON" : "OFF");
		Debug::Log("ResourceManager<" + string(typeid(T).name()) + ">の補助機能 ： " + swit);

		m_bHelper = helper;
	}

#pragma endregion
};


template<class T>
inline ResourceManager<T>* GetResourceManager() {
	return ResourceManager<T>::Instance();
}