///////////////////////////////////////////////////////////////
// �V�[���}�l�[�W���[�N���X
// author		SyunMizuno
// 2015.12.05	�v���O�����쐬
// 2016.01.26	vector����map�֕ύX
// 2017. 1.22	�f�o�b�O���O��ǉ�
///////////////////////////////////////////////////////////////

#include	"SceneManager.h"
#include	"../../Debug/Debug.h"


namespace MSLib {

	SceneManagerBase::SceneManagerBase() {
		while (!m_Stack.empty()) {
			m_Stack.pop();
		}
		m_TmpSceneName.clear();
		m_nCommand = SCENEMANAGER_NO;
		m_MapScene.clear();
		m_pFade = nullptr;
	}


	////////////////////////////////////////////////////////////////////////////
	//	�֐���	�F	Release
	//	�����T�v�F	�J���֐�
	//	����	�F
	//	�o��	�F
	////////////////////////////////////////////////////////////////////////////
	void SceneManagerBase::Release() {
		// �X�^�b�N�̉������
		while (!m_Stack.empty()) {
			m_Stack.pop();
		}
		DeleteFadeScene();
		// �o�^�����V�[���̍폜
		SceneAllDelete();
		m_nCommand = SCENEMANAGER_NO;
		m_TmpSceneName.clear();
	}


	////////////////////////////////////////////////////////////////////////////
	//	�֐���	�F	RegistScene
	//	�����T�v�F	�V�[���I�u�W�F�N�g��o�^����
	//	����	�F	pScene		�o�^����V�[���I�u�W�F�N�g
	//				SceneName	�o�^����V�[����
	//	�o��	�F	����������true,���s������false
	////////////////////////////////////////////////////////////////////////////
	bool SceneManagerBase::RegistScene(SceneBase* pScene, const string SceneName) {
		if (!pScene) {
			Debug::LogError("�V�[����" + SceneName + "�̎��Ԃ�����܂���");
			return false;
		}

		if (m_MapScene.end() != m_MapScene.find(SceneName)) {
			Debug::LogError("�V�[����" + SceneName + "�͓o�^�ς݂ł�");
			return false;
		}

		m_MapScene.insert(pair<string, SceneBase*>(SceneName, pScene));

		return true;
	}


	////////////////////////////////////////////////////////////////////////////
	//	�֐���	�F	DeleteRegistedScene
	//	�����T�v�F	�V�[���I�u�W�F�N�g���폜����
	//	����	�F	SceneName	�V�[����
	//	�o��	�F	
	////////////////////////////////////////////////////////////////////////////
	void SceneManagerBase::DeleteScene(const string SceneName) {
		auto it = m_MapScene.find(SceneName);

		if (it == m_MapScene.end()) {
			Debug::Log("�V�[����" + SceneName + "�͓o�^����Ă��Ȃ����ߍ폜�ł��܂���");
			return;
		}

		it->second->ReleaseMain();
		delete it->second;
		it->second = nullptr;

		m_MapScene.erase(SceneName);
	}


	////////////////////////////////////////////////////////////////////////////
	//	�֐���	�F	RegistFadeScene
	//	�����T�v�F	Fade���s���V�[����o�^
	//	����	�F	pScene		�o�^����V�[���I�u�W�F�N�g
	//				*pScene
	//	�o��	�F	����������true,���s������false
	////////////////////////////////////////////////////////////////////////////
	bool SceneManagerBase::RegistFadeScene(SceneFadeBase* pScene) {
		if (!pScene) {
			Debug::LogError("�t�F�[�h�p�V�[���̎��Ԃ�����܂���");
			return false;
		}

		if (m_pFade) {
			m_pFade->ReleaseMain();
			delete m_pFade;
			m_pFade = nullptr;
		}

		m_pFade = pScene;
		return m_pFade->InitMain();
	}


	////////////////////////////////////////////////////////////////////////////
	//	�֐���	�F	DeleteFadeScene
	//	�����T�v�F	Fade�J���֐�
	//	����	�F
	//	�o��	�F
	////////////////////////////////////////////////////////////////////////////
	void SceneManagerBase::DeleteFadeScene() {
		if (!m_pFade)	return;

		m_pFade->ReleaseMain();
		delete m_pFade;
		m_pFade = nullptr;
	}


	////////////////////////////////////////////////////////////////////////////
	//	�֐���	�F	GetScene
	//	�����T�v�F	�V�[���̍X�V��Atop�̃V�[�����擾
	//	����	�F	
	//	�o��	�F	top�̃V�[���̃|�C���^�A�Ȃ����NULL��Ԃ�
	////////////////////////////////////////////////////////////////////////////
	SceneBase* SceneManagerBase::GetScene(void) {
		//----- �t�F�[�h
		if (m_pFade)
			m_pFade->Update();

		//----- �ϐ��錾
		bool bSuccess = true;

		//----- �R�}���h�ύX�m�F
		if (m_nCommand == SCENEMANAGER_NO) {
			return GetTopScene();
		} else {
			// �t�F�[�h
			if (m_pFade) {
				// ���s
				m_pFade->Exe();
				if (!m_pFade->Change()) {
					return GetTopScene();
				}
			}

			map< string, SceneBase* >::iterator it = m_MapScene.find(m_TmpSceneName);

			if (it == m_MapScene.end()) {
				m_nCommand = SCENEMANAGER_NO;
				Debug::LogError("�V�[����" + m_TmpSceneName + "�͑��݂��܂���");
				return nullptr;
			}

			// �R�}���h����
			switch (m_nCommand) {
			case SCENEMANAGER_POP:
				PopScene();
				break;

			case SCENEMANAGER_CHANGE:
				bSuccess = ChangeScene(it->second);
				break;

			case SCENEMANAGER_PUSH:
				bSuccess = PushScene(it->second);
				break;

			case SCENEMANAGER_RESTART:
				bSuccess = GetTopScene()->ReStart();
				break;

			default:
				break;
			}

			// �ύX�Ȃ��ŏ㏑��
			m_nCommand = SCENEMANAGER_NO;

			// ���s���̏���
			if (!bSuccess) {
				Debug::LogError("�V�[���̕ύX�Ɏ��s���܂���");
				return nullptr;
			}
		}

		// �ŐV�̃V�[����Ԃ�
		return GetTopScene();
	}


	////////////////////////////////////////////////////////////////////////////
	//	�֐���	�F	PopScene
	//	�����T�v�F	�V�[����pop����
	//	����	�F	
	//	�o��	�F	
	////////////////////////////////////////////////////////////////////////////
	void SceneManagerBase::PopScene(void) {
		if (m_Stack.empty())
			return;

		m_Stack.top()->ReleaseMain();
		m_Stack.pop();
	}


	////////////////////////////////////////////////////////////////////////////
	//	�֐���	�F	PushScene
	//	�����T�v�F	�V�[����push����
	//	����	�F	pScene	push����V�[���̃|�C���^
	//	�o��	�F	
	////////////////////////////////////////////////////////////////////////////
	bool SceneManagerBase::PushScene(SceneBase* pScene) {
		if (!pScene) {
			Debug::LogError("Push�����V�[���̎��Ԃ�����܂���");
			return false;
		}

		// �������m�F
		if (pScene->GetMakeFlg()) {
			if (!pScene->ReStart()) {
				Debug::LogError("�V�[���̍ď������Ɏ��s���܂���");
				pScene->ReleaseMain();
				return false;
			}
		} else {
			if (!pScene->InitMain()) {
				Debug::LogError("�V�[���̏������Ɏ��s���܂���");
				pScene->ReleaseMain();
				return false;
			}
		}

		m_Stack.push(pScene);
		return true;
	}


	////////////////////////////////////////////////////////////////////////////
	//	�֐���	�F	ChangeScene
	//	�����T�v�F	top�V�[����ύX����
	//	����	�F	pScene	�ύX����V�[��
	//	�o��	�F	���݂����true���݂��Ȃ����false
	////////////////////////////////////////////////////////////////////////////
	bool SceneManagerBase::ChangeScene(SceneBase* pScene) {
		if (!pScene) {
			Debug::LogError("Change�������V�[���̎��Ԃ�����܂���");
			return false;
		}

		PopScene();
		if (!PushScene(pScene)) {
			Debug::LogError("�V�[����Push�Ɏ��s���܂���");
			return false;
		}

		return true;
	}


	////////////////////////////////////////////////////////////////////////////
	//	�֐���	�F	SceneAllDelete
	//	�����T�v�F	�o�^���ꂽ�V�[�������ׂĊJ��
	//	����	�F	
	//	�o��	�F	
	////////////////////////////////////////////////////////////////////////////
	void SceneManagerBase::SceneAllDelete(void) {
		map<string, SceneBase*>::iterator it = m_MapScene.begin();
		while (it != m_MapScene.end()) {
			if (it->second->GetMakeFlg())
				it->second->ReleaseMain();
			delete it->second;
			it->second = nullptr;
			it++;
		}
		m_MapScene.clear();
	}

}