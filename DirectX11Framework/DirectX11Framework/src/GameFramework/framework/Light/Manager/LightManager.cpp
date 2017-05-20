// ���C�g�}�l�[�W���N���X
// 2016. 5.17	:	�v���O�����쐬
// author		:	SyunMizuno


#include	"LightManager.h"
#include	"../../Debug/Debug.h"


namespace MSLib {

	LightManager::LightManager() {
		Debug::Log("LightManager ���쐬");
		m_aLight.resize(10);
		m_aLight.clear();
	}

	LightManager::~LightManager() {
		Debug::Log("LightManager ���폜");
		m_aLight.clear();
	}

	void LightManager::Add(Light* light) {
		if (!light) {
			Debug::LogError("���C�g�̎��Ԃ�����܂���");
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
		Debug::LogError("LightManager : �폜�������I�u�W�F�N�g��������܂���");
		return false;
	}

	Light* LightManager::Get(const std::string& Name) {
		if (Name.empty()) {
			Debug::LogError("���C�g�̖��O������܂���");
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