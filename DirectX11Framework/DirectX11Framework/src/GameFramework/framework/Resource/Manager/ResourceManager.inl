
#include	"../../Utility/System/SystemUtility.h"
#include	"../../Debug/Debug.h"
#include	<typeinfo>


namespace MSLib {

	template<class T>
	ResourceManager<T>::ResourceManager() {
		Debug::Log("ResourceManager<" + string(typeid(T).name()) + "> を作成");
		m_MapResources.clear();
	}


	template<class T>
	ResourceManager<T>::~ResourceManager() {
		Debug::Log("ResourceManager<" + std::string(typeid(T).name()) + "> を削除");

		auto it = m_MapResources.begin();

		// 全要素削除
		while (it != m_MapResources.end()) {
			it->second.reset();
			++it;
		}

		m_MapResources.clear();
	}


	/*									//
	//				作成				//
	//									*/
	template<class T>
	std::shared_ptr<T> ResourceManager<T>::Create(const std::string& name) {
		if (name.empty()) {
			Debug::LogError("ファイル名がありません");
		}

		// 登録済みか確認
		auto it = m_MapResources.find(name);
		if (m_MapResources.end() != it) {
			Debug::Log("リソース : " + name + " は既に作成済みです");
			return it->second;
		}

		std::shared_ptr<T> ptr(new T);
		if(!ptr->Create(name)) {
			Debug::LogError("リソース : " + name + " の作成に失敗しました");
			ptr.reset();
		}

		// 登録
		Debug::Log(std::string(typeid(T).name()) + " : " + name + " を作成");
		m_MapResources.insert(std::pair<std::string, std::shared_ptr<T>>(name, ptr));

		return ptr;
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
		if (it->second->use_count() > 1) {
			Debug::Log("リソース : " + name + " は参照されているため削除できません");
			return false;
		}
		it->second->reset();

		m_MapResources.erase(name);

		return true;
	}


	/*									//
	//				取得				//
	//									*/
	template<class T>
	std::shared_ptr<T> ResourceManager<T>::Get(const std::string& name) {
		auto it = m_MapResources.find(name);

		if (it == m_MapResources.end()) {
			return Create(name);
		}

		return it->second;
	}


	/*									//
	//			マネージャの取得		//
	//									*/
	template<class T>
	inline ResourceManager<T>* GetResourceManager() {
		return ResourceManager<T>::Instance();
	}

}