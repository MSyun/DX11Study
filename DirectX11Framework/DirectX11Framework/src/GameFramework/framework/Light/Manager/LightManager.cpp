// ���C�g�}�l�[�W���N���X
// 2016. 5.17	:	�v���O�����쐬
// author		:	SyunMizuno


#include	"LightManager.h"
#include	"../../Debug/Debug.h"


namespace MSLib {

	LightManager::LightManager() :
		m_bHelper(true)
	{
		Debug::Log("LightManager ���쐬");
		m_MapLight.clear();
		SetHelper(m_bHelper);
	}

	LightManager::~LightManager() {
		Debug::Log("LightManager ���폜");
		if (!m_bHelper)	return;

		m_MapLight.clear();
	}

	void LightManager::Set() {
		auto it = m_MapLight.begin();

		while (it != m_MapLight.end()) {
			it->second->Set();
			++it;
		}
	}

	Light* LightManager::Create(const string& Name) {
		if (m_MapLight.end() != m_MapLight.find(Name)) {
			Debug::Log("�J������ : " + Name + " �͂��łɐ�������Ă��܂�");
			return Get(Name);
		}

		Light* light = new Light;
		light->SetName(Name);
		m_MapLight.insert(pair<string, Light*>(Name, light));

		return light;
	}

	bool LightManager::Delete(const string& Name) {
		auto it = m_MapLight.find(Name);

		if (it == m_MapLight.end()) {
			Debug::Log("Light : " + Name + " �͓o�^����Ă��Ȃ����ߍ폜�ł��܂���");
			return false;
		}

		SAFE_DELETE(it->second);

		m_MapLight.erase(Name);

		return true;
	}

	Light* LightManager::Get(const string& Name) {
		auto it = m_MapLight.find(Name);

		if (it == m_MapLight.end()) {
			return Create(Name);
		}

		return it->second;
	}

	void LightManager::SetHelper(bool helper) {
		string swit = (helper ? "ON" : "OFF");
		Debug::Log("LightManager�̕⏕�@�\ : " + swit);

		m_bHelper = helper;
	}


	LightManager* GetLightManager() {
		return LightManager::Instance();
	}

};