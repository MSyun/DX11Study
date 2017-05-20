// 3Dオブジェクトマネージャー
// 2016. 5.15	:	プログラム作成
// author		:	SyunMizuno


#include	"Object3DManager.h"
#include	"../../../Utility/System/SystemUtility.h"
#include	"../../../Debug/Debug.h"


namespace MSLib {

	Object3DManager::Object3DManager() {
		m_lstObject.clear();
		Debug::Log("Object3DManagerを作成");
	}

	Object3DManager::~Object3DManager() {
		for(auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			it->reset();
		}
		m_lstObject.clear();
		Debug::Log("Object3DManagerを削除");
	}

	Object3D* Object3DManager::Find(const std::string& name) {
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if (!(*it)->GetActive())	continue;

			if((*it)->GetName() == name) {
				return (*it).get();
			}
		}

		Debug::Log("3Dオブジェクト名 " + name + " は存在しません");
		return nullptr;
	}

	Object3D* Object3DManager::FindWithTag(const byte tag) {
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if (!(*it)->GetActive())	continue;

			if((*it)->GetTag() == tag) {
				return (*it).get();
			}
		}

		Debug::Log("3Dオブジェクトにタグ名は存在しません");
		return nullptr;
	}

	void Object3DManager::Add(Object3D* obj) {
		if (!obj) {
			Debug::LogError("オブジェクトの実態がありません");
			return;
		}

		m_lstObject.push_back(std::shared_ptr<Object3D>(obj));
	}

	void Object3DManager::AllClear() {
		for(auto it = m_lstObject.begin(); it != m_lstObject.end();) {
			if((*it)->GetDontDestroy()) {
				++it;
				continue;
			}
			(*it).reset();
			it = m_lstObject.erase(it);
		}
	}

	void Object3DManager::Update() {
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if((*it)->GetTransform()->CheckParent())
				continue;

			(*it)->UpdateAll();
		}
	}

	void Object3DManager::LateUpdate() {
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if((*it)->GetTransform()->CheckParent())
				continue;

			(*it)->LateUpdateAll();
		}
	}

	void Object3DManager::Draw() {
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if((*it)->GetTransform()->CheckParent())
				continue;

			(*it)->DrawAll();
		}
	}

	void Object3DManager::LateDraw() {
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if((*it)->GetTransform()->CheckParent())
				continue;

			(*it)->LateDrawAll();
		}
	}

	void Object3DManager::CheckDestroy() {
		std::list<_3DOBJECT*>	lstObj;
		for (auto it = m_lstObject.begin(); it != m_lstObject.end();) {
			if((*it)->GetDestroy()) {
				(*it)->OnDestroy();
				(*it).reset();
				it = m_lstObject.erase(it);
				continue;
			}
			++it;
		}
	}

	Object3DManager* GetObject3DManager() {
		return Object3DManager::Instance();
	}

};