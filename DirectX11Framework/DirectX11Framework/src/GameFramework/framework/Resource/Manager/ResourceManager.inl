#pragma once


#include	"../../Utility/System/SystemUtility.h"
#include	"../../Debug/Debug.h"
#include	<typeinfo>



/*									//
//			コンストラクタ			//
//									*/
template<class T>
ResourceManager<T>::ResourceManager() :
	m_bHelper(true)
{
	m_MapResources.clear();
	SetHelper(m_bHelper);
}


/*									//
//			デストラクタ			//
//									*/
template<class T>
ResourceManager<T>::~ResourceManager() {
	if (!m_bHelper)	return;

	map<string, T*>::iterator it = m_MapResources.begin();

	// 全要素削除
	while (it != m_MapResources.end()) {
		SAFE_DELETE(it->second);
		++it;
	}

	m_MapResources.clear();
}


/*									//
//				作成				//
//									*/
template<class T>
T* ResourceManager<T>::Create(const string name) {
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


/*									//
//				削除				//
//									*/
template<class T>
bool ResourceManager<T>::Delete(const string name) {
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


/*									//
//				取得				//
//									*/
template<class T>
T* ResourceManager<T>::Get(const string name) {
	// 検索
	auto it = m_MapResources.find(name);

	if (it == m_MapResources.end()) {
		return Create(name);
	}

	return it->second;
}


/*									//
//			補助機能設定			//
//									*/
template<class T>
void ResourceManager<T>::SetHelper(bool helper) {
	string swit = (helper ? "ON" : "OFF");
	Debug::Log("ResourceManager<" + string(typeid(T).name()) + ">の補助機能 ： " + swit);

	m_bHelper = helper;
}


/*									//
//			マネージャの取得		//
//									*/
template<class T>
inline ResourceManager<T>* GetResourceManager() {
	return ResourceManager<T>::Instance();
}