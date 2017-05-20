// �J�����}�l�[�W���[
// 2017.05.15	: �v���O�����쐬
// author		: SyunMizuno


#include	"CameraManager.h"
#include	"../../Debug/Debug.h"


namespace MSLib {

	CameraManager::CameraManager() :
		m_CurCameraName("")
	{
		Debug::Log("CameraManager ���쐬");
		m_aCamera.resize(3);
		m_aCamera.clear();
	}


	CameraManager::~CameraManager() {
		Debug::Log("CameraManager ���폜");
		m_aCamera.clear();
	}


	/*									//
	//				�ǉ�				//
	//									*/
	void CameraManager::Add(Camera* camera) {
		if (!camera) {
			Debug::LogError("�J�����̎��Ԃ�����܂���");
			return;
		}

		m_aCamera.push_back(camera);
	}


	/*									//
	//			�J�����̍폜			//
	//									*/
	bool CameraManager::Delete(Camera* camera) {
		for (auto it = m_aCamera.begin(); it != m_aCamera.end(); ++it) {
			if ((*it) == camera) {
				m_aCamera.erase(it);
				return true;
			}
		}
		Debug::LogError("CameraManager : �폜�������I�u�W�F�N�g��������܂���");
		return false;
	}


	/*									//
	//			�J�����̎擾			//
	//									*/
	Camera* CameraManager::Get(const std::string& Name) {
		if (Name.empty()) {
			Debug::LogError("�J�����̖��O������܂���");
			return nullptr;
		}

		for (auto it = m_aCamera.begin(); it != m_aCamera.end(); ++it) {
			if ((*it)->GetName() == Name)
				return (*it);
		}

		return nullptr;
	}


	/*									//
	//			�J�����̐ݒ�			//
	//									*/
	bool CameraManager::Set(const std::string& Name) {
		Camera* camera = Get(Name);
		if (!camera) {
			Debug::LogError("�J������ : " + Name + " �͑��݂��܂���ł���");
			return false;
		}

		camera->Set();
		m_CurCameraName = Name;
		return true;
	}


	/*									//
	//		�Ō�Ɏg�p�������̂��擾	//
	//									*/
	Camera* CameraManager::CurrentCamera() {
		return Get(m_CurCameraName);
	}


	/*									//
	//			�}�l�[�W���̎擾		//
	//									*/
	CameraManager* GetCameraManager() {
		return CameraManager::Instance();
	}

};