// ライトマネージャクラス
// 2016. 5.17	:	プログラム作成
// author		:	SyunMizuno


#include	"LightManager.h"
#include	"../../Debug/Debug.h"


namespace MSLib {

	LightManager::LightManager() {
		Debug::Log("LightManager を作成");
		m_aLight.resize(10);
		m_aLight.clear();
	}

	LightManager::~LightManager() {
		Debug::Log("LightManager を削除");
		m_aLight.clear();
	}

	void LightManager::Add(Light* light) {
		if (!light) {
			Debug::LogError("ライトの実態がありません");
			return;
		}

		m_aLight.push_back(light);
	}

	bool LightManager::Delete(Light* light) {
		for (auto it = m_aLight.begin(); it != m_aLight.end(); ++it) {
			if ((*it) == light) {
				m_aLight.erase(it);
				return true;
			}
		}
		Debug::LogError("LightManager : 削除したいオブジェクトが見つかりません");
		return false;
	}

	Light* LightManager::Get(const std::string& Name) {
		if (Name.empty()) {
			Debug::LogError("ライトの名前がありません");
			return nullptr;
		}

		for (auto it = m_aLight.begin(); it != m_aLight.end(); ++it) {
			if ((*it)->GetName() == Name)
				return (*it);
		}

		return nullptr;
	}

	void LightManager::Set() {
		for (auto it = m_aLight.begin(); it != m_aLight.end(); ++it) {
			(*it)->Set();
		}
	}


	LightManager* GetLightManager() {
		return LightManager::Instance();
	}

};