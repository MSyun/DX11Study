#include	"ResourceManager.h"
#include	"../../Utility/System/SystemUtility.h"
#include	"../../Debug/Debug.h"
#include	<typeinfo>


namespace MSLib {

	template<class T>
	ResourceManager<T>::ResourceManager() :
		m_bHelper(true)
	{
		Debug::Log("ResourceManager<" + string(typeid(T).name()) + "> を作成");
		m_MapResources.clear();
		SetHelper(m_bHelper);
	}


	template<class T>
	ResourceManager<T>::~ResourceManager() {
		Debug::Log("ResourceManager<" + string(typeid(T).name()) + "> を削除");
		if (!m_bHelper)	return;

		auto it = m_MapResources.begin();

		// 全要素削除
		while (it != m_MapResources.end()) {
			SAFE_DELETE(it->second);
//			it->second.reset();
			++it;
		}

		m_MapResources.clear();
	}


	/*									//
	//				作成				//
	//									*/
	template<class T>
	T* ResourceManager<T>::Create(const std::string& name) {
//	std::shared_ptr<T> ResourceManager<T>::Create(const std::string& name) {
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
//		shared_ptr<T> ptr = make_shared<T>(resource);
//		m_MapResources.insert(pair<string, std::shared_ptr<T>>(name, ptr));

		return resource;
//		return ptr;
	}


	/*									//
	//				削除				//
	//									*/
	template<class T>
	bool ResourceManager<T>::Delete(const std::string& name) {
		auto it = m_MapResources.find(name);

		// 登録確認
		if (it == m_MapResources.end()) {
			Debug::Log("リソース : " + name + " は登録されていないため削除できません");
			return false;
		}

		// 削除
		it->second->Delete();
		SAFE_DELETE(it->second);
//		if (it->second->use_count() > 1) {
//			Debug::Log("リソース : " + name + " は参照されているため削除できません");
//			return false;
//		}
//		it->second->reset();

		m_MapResources.erase(name);

		return true;
	}


	/*									//
	//				取得				//
	//									*/
	template<class T>
	T* ResourceManager<T>::Get(const std::string& name) {
//	std::shared_ptr<T> ResourceManager<T>::Get(const std::string& name) {
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

}