// 3Dオブジェクトマネージャー
// 2016. 5.15	:	プログラム作成
// author		:	SyunMizuno


#include	"Object3DManager.h"
#include	"../../../Utility/System/SystemUtility.h"
#include	"../../../Debug/Debug.h"


namespace MSLib {

	Object3DManager::Object3DManager() :
		m_bHelper(true)
	{
		m_lstObject.clear();
		Debug::Log("Object3DManagerを作成");
	}

	Object3DManager::~Object3DManager() {
		Debug::Log("Object3DManagerを削除");
		if (!m_bHelper)	return;

		while (m_lstObject.begin() != m_lstObject.end()) {
			auto it = m_lstObject.begin();
			delete[](*it)->pObject;
		}
		m_lstObject.clear();
	}

	Object3D* Object3DManager::Find(const string& name) {
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if (!(*it)->pObject->GetActive())	continue;

			if ((*it)->pObject->GetName() == name) {
				return (*it)->pObject;
			}
		}

		Debug::Log("3Dオブジェクト名 " + name + " は存在しません");
		return nullptr;
	}

	Object3D* Object3DManager::FindWithTag(const byte tag) {
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if (!(*it)->pObject->GetActive())	continue;

			if ((*it)->pObject->GetTag() == tag) {
				return (*it)->pObject;
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

		_3DOBJECT* regist = new _3DOBJECT;
		regist->pObject = obj;

		m_lstObject.push_back(regist);
	}

	void Object3DManager::AllClear() {
		list<_3DOBJECT*> lstBuff;
		while (m_lstObject.begin() != m_lstObject.end()) {
			auto it = m_lstObject.begin();
			if ((*it)->pObject->GetDontDestroy()) {
				lstBuff.push_back(*it);
				m_lstObject.erase(it);
				continue;
			}
			delete[](*it)->pObject;
		}
		m_lstObject.clear();

		for (auto it = lstBuff.begin(); it != lstBuff.end(); ++it) {
			m_lstObject.push_back(*it);
		}
	}

	void Object3DManager::Delete(Object3D* obj) {
		if (!obj) {
			Debug::LogError("オブジェクトの実態がありません");
			return;
		}
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if ((*it)->pObject != obj)	continue;

			SAFE_DELETE(*it);

			m_lstObject.erase(it);

			return;
		}
	}

	void Object3DManager::Update() {
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if ((*it)->pObject->GetTransform()->CheckParent())
				continue;

			(*it)->pObject->UpdateAll();
		}
	}

	void Object3DManager::LateUpdate() {
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if ((*it)->pObject->GetTransform()->CheckParent())
				continue;

			(*it)->pObject->LateUpdateAll();
		}
	}

	void Object3DManager::Draw() {
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if ((*it)->pObject->GetTransform()->CheckParent())
				continue;

			(*it)->pObject->DrawAll();
		}
	}

	void Object3DManager::LateDraw() {
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if ((*it)->pObject->GetTransform()->CheckParent())
				continue;

			(*it)->pObject->LateDrawAll();
		}
	}

	void Object3DManager::CheckDestroy() {
		list<_3DOBJECT*>	lstObj;
		for (auto it = m_lstObject.begin(); it != m_lstObject.end(); ++it) {
			if ((*it)->pObject->GetDestroy()) {
				(*it)->pObject->OnDestroy();
				lstObj.push_back(*it);
				continue;
			}
		}
		while (lstObj.begin() != lstObj.end()) {
			auto it = lstObj.begin();
			delete[](*it)->pObject;
			lstObj.erase(it);
		}
	}

	void Object3DManager::SetHelper(bool helper) {
		string swit = (helper ? "ON" : "OFF");
		Debug::Log("Object3DManagerの補助機能 ： " + swit);
		m_bHelper = helper;
	}


	Object3DManager* GetObject3DManager() {
		return Object3DManager::Instance();
	}

};