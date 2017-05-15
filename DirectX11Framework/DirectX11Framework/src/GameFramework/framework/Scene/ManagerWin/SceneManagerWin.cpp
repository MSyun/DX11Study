// Windows�pSceneManager�N���X
// 2015.12.16	�v���O�����쐬
// 2016. 1. 3	�����������
// 2016.01.26	vector����map�֕ύX
// 2017. 1.22	�f�o�b�O���O��ǉ�


#include	"SceneManagerWin.h"
#include	"../../Input/Input.h"
#include	"../../Debug/Debug.h"

/*
	memo:
		�����œǂݍ��ݏI�����̃L�[���͂�ύX���邱��
		GetScene�֐��͂����ƌp�����Ă�������
*/


#define		LOAD_END_KEY	(DIK_RETURN)



// ChangeSceneThread�̈����p
typedef struct {
	SceneBase *top;
	SceneBase *cScene;
} _ChangeData;

// ���[�h�t���O
typedef enum {
	LOADING_NO = 0,	// No����
	LOADING_NOW,	// �ǂݍ��ݒ�
	LOADING_MAX,	// �ǂݍ��݊���
	LOADING_END,	// �ǂݍ��ݏI��
} _Loading;


////////////////////////////////////////////////////////////////////////////
//	�֐���	�F	InitSceneThread
//	�����T�v�F	�ǂݍ��ݏ���
//	����	�F
//	�o��	�F
////////////////////////////////////////////////////////////////////////////
unsigned _stdcall InitSceneThread(void* pThreadParam) {
	//----- �V�[���}�l�[�W���̃C���X�^���X�擾
	SceneManagerWins* Si = GetSceneManagerWins();
	if (!Si) _endthreadex(0);// �C���X�^���X���Ȃ��ꍇ

	// �������擾
	SceneBase* tmp = (SceneBase*)pThreadParam;

	//----- ������
	if (tmp->InitMain()) {
		Si->SetLoadSuc(true);
	} else {
		Si->SetLoadSuc(false);
	}
	//----- ���[�h�I��
	Si->SetLoadingFlag(LOADING_END);
	_endthreadex(0);
	return 0;
}


////////////////////////////////////////////////////////////////////////////
//	�֐���	�F	ReleaseSceneThread
//	�����T�v�F	�ǂݍ��ݏ���
//	����	�F
//	�o��	�F
////////////////////////////////////////////////////////////////////////////
unsigned _stdcall ReleaseSceneThread(void* pThreadParam) {
	//----- �V�[���}�l�[�W���̃C���X�^���X�擾
	SceneManagerWins* Si = GetSceneManagerWins();
	if (!Si) _endthreadex(0);// �C���X�^���X���Ȃ��ꍇ

	// �������擾
	SceneBase* tmp = (SceneBase*)pThreadParam;

	//----- ���
	tmp->ReleaseMain();

	//----- ���[�h�I��
	Si->SetLoadSuc(true);
	Si->SetLoadingFlag(LOADING_END);
	_endthreadex(0);
	return 0;
}


////////////////////////////////////////////////////////////////////////////
//	�֐���	�F	ChangeSceneThread
//	�����T�v�F	�t���[���ύX����
//	����	�F
//	�o��	�F
////////////////////////////////////////////////////////////////////////////
unsigned _stdcall ChangeSceneThread(void* pThreadParam) {
	//----- �V�[���}�l�[�W���̃C���X�^���X�擾
	SceneManagerWins* Si = GetSceneManagerWins();
	if (!Si) _endthreadex(0);// �C���X�^���X���Ȃ��ꍇ

	// �������擾
	_ChangeData* tmp = (_ChangeData*)pThreadParam;

	//----- ���
	tmp->top->ReleaseMain();

	//----- ������
	if (tmp->cScene->InitMain()) {
		Si->SetLoadSuc(true);
	} else {
		Si->SetLoadSuc(false);
	}
	delete tmp;

	//----- ���[�h�I��
	Si->SetLoadingFlag(LOADING_END);
	_endthreadex(0);
	return 0;
}



////////////////////////////////////////////////////////////////////////////
//	�R���X�g���N�^
////////////////////////////////////////////////////////////////////////////
SceneManagerWin::SceneManagerWin() {
	m_Loading		= nullptr;			// ���[�h�V�[��
	m_nLoadingFlag	= LOADING_NO;	// ���[�h�t���O
	m_hThread		= nullptr;			// �X���b�h�n���h��
	m_bLoadSuc		= true;			// ���[�h����
	m_uLoadWaitTime	= 10;			// ���[�h�J�n�E�F�C�g����
	m_uLoadRate		= 0;			// �ǂݍ��ݗ�
	m_bLoadKey		= false;
	m_bLoadEndAfter = false;
}


////////////////////////////////////////////////////////////////////////////
//	�f�X�g���N�^
////////////////////////////////////////////////////////////////////////////
SceneManagerWin::~SceneManagerWin() {
	Release();
}


////////////////////////////////////////////////////////////////////////////
//	�֐���	�F	Release
//	�����T�v�F	�J���֐�
//	����	�F
//	�o��	�F
////////////////////////////////////////////////////////////////////////////
void SceneManagerWin::Release(void) {
	//----- ���[�h��
	while (m_nLoadingFlag == LOADING_NOW || m_nLoadingFlag == LOADING_END) {
		if (m_nLoadingFlag == LOADING_END) {
			// �X���b�h�����
			CloseHandle(m_hThread);
			break;
		}
	}

	DeleteLoadingScene();
	// �e�N���X�̃����[�X����
	SceneManagerBase::Release();
}


////////////////////////////////////////////////////////////////////////////
//	�֐���	�F	RegistLoadingScene
//	�����T�v�F	NowLoading��ʗp�V�[���ǂݍ��݂��s��
//	����	�F	*pScene
//	�o��	�F	���������true���s�����false
////////////////////////////////////////////////////////////////////////////
bool SceneManagerWin::RegistLoadingScene(SceneBase* pScene) {
	if (!pScene) {
		Debug::LogError("Loading��ʗp�V�[���̎��Ԃ�����܂���");
		return false;
	}

	if (m_Loading) {
		m_Loading->ReleaseMain();
		delete m_Loading;
		m_Loading = nullptr;
	}

	m_Loading = pScene;
	return m_Loading->InitMain();
}


////////////////////////////////////////////////////////////////////////////
//	�֐���	�F	DeleteLoadingScene
//	�����T�v�F	�ǂݍ��݉�ʊJ���֐�
//	����	�F
//	�o��	�F
////////////////////////////////////////////////////////////////////////////
void SceneManagerWin::DeleteLoadingScene(void) {
	if (!m_Loading)
		return;

	m_Loading->ReleaseMain();
	delete m_Loading;
	m_Loading = nullptr;
}


////////////////////////////////////////////////////////////////////////////
//	�֐���	�F	GetScene
//	�����T�v�F	�V�[���̍X�V��Atop�̃V�[�����擾
//	����	�F
//	�o��	�F	top�V�[���̃|�C���^�B�Ȃ��ꍇ��NULL��Ԃ�
////////////////////////////////////////////////////////////////////////////
SceneBase* SceneManagerWin::GetScene() {
	//----- �t�F�[�h
	if (m_pFade)
		m_pFade->Update();

	//----- ���[�h��
	if (m_nLoadingFlag != LOADING_NO) {
		Sleep(m_uLoadWaitTime);

		//----- �ǂݍ��ݏI����
		if (m_nLoadingFlag == LOADING_MAX) {
			if (!m_bLoadKey) {
				// �{�^�����͂ɂ��J��
				if(m_bLoadEndAfter)
					m_bLoadKey = true;
			} else {
				// �t�F�[�h���s
				if (m_pFade) {
					m_pFade->Exe();
					m_bLoadEndAfter = false;
					if (!m_pFade->Change()) {
						return m_Loading;
					}
					// �t���O��ύX
					m_nLoadingFlag = LOADING_NO;
					m_uLoadRate = 0;
					m_bLoadKey = false;
				}
			}
		}

		//----- �X���b�h�I����
		if (m_nLoadingFlag == LOADING_END) {
			CloseHandle(m_hThread);	// �X���b�h�����
			// �ǂݍ��ݎ��s
			if (!m_bLoadSuc) {
				return nullptr;
			}
			// �t���O��ύX
			m_nLoadingFlag = LOADING_MAX;
		}

		m_nCommand = SCENEMANAGER_NO;
		return m_Loading;
	}

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

		// �����m�F
		bool bSuccess = true;

		// �R�}���h����
		switch (m_nCommand) {
		case SCENEMANAGER_POP:
			PopScene();
			break;

		case SCENEMANAGER_PUSH:
			bSuccess = PushScene(it->second);
			break;

		case SCENEMANAGER_CHANGE:
			bSuccess = ChangeScene(it->second);
			break;

		case SCENEMANAGER_RESTART:
			bSuccess = GetTopScene()->ReStart();
			break;

		case SCENEMANAGER_LOADING_POP:
			PopLoadScene();
			m_nCommand = SCENEMANAGER_NO;
			return m_Loading;

		case SCENEMANAGER_LOADING_PUSH:
			PushLoadScene(it->second);
			m_nCommand = SCENEMANAGER_NO;
			return m_Loading;

		case SCENEMANAGER_LOADING_CHANGE:
			ChangeLoadScene(it->second);
			m_nCommand = SCENEMANAGER_NO;
			return m_Loading;

		case SCENEMANAGER_LOADING_RESTART:
			ChangeLoadScene(GetTopScene());
			m_nCommand = SCENEMANAGER_NO;
			return m_Loading;

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
//	�֐���	�F	ChangeLoadScene
//	�����T�v�F	top�V�[����ύX����B�ǂݍ��݉�ʂ���
//	����	�F	pScene	�ύX����V�[���̃|�C���^
//	�o��	�F	���������true���s�����false
////////////////////////////////////////////////////////////////////////////
bool SceneManagerWin::ChangeLoadScene(SceneBase* pScene) {
	if (!pScene) {
		Debug::LogError("Change�������V�[���̎��Ԃ�����܂���");
		return false;
	}

	//----- �ǂݍ��݊J�n
	m_nLoadingFlag = LOADING_NOW;
	if (!m_Loading->ReStart()) {
		Debug::LogError("���[�f�B���O��ʗp�V�[���̍ď������Ɏ��s���܂���");
	}

	//----- �������̊m�F
	if (pScene->GetMakeFlg() && pScene != GetTopScene()) {
		if (!m_Stack.empty()) {
			m_hThread = (HANDLE)_beginthreadex(
				nullptr,				// SECURITY_ATTRIBUTES�ւ̃|�C���^orNULL
				0,					// �X�^�b�N�T�C�Y
				ReleaseSceneThread,	// �X���b�h�֐��̃A�h���X
				GetTopScene(),		// �X���b�h�ɓn������
				0,					// 0�i�������s�j�ACREATE_SUSPENDED�i�ꎞ��~�j
				nullptr);				// �X���b�h���ʎq�BNULL�ł���
			m_Stack.pop();
		}
		if (!pScene->ReStart()) {
			Debug::LogError("�V�[���̍ď������Ɏ��s���܂���");
			return false;
		}
	} else {
		// ����������ĂȂ���`
		if (!m_Stack.empty()) {
			// �ς�ł���ꍇ
			_ChangeData *Data;
			Data = new _ChangeData;
			Data->top = GetTopScene();
			Data->cScene = pScene;
			// �X���b�h�J�n
			m_hThread = (HANDLE)_beginthreadex(
				nullptr,				// SECURITY_ATTRIBUTES�ւ̃|�C���^orNULL
				0,					// �X�^�b�N�T�C�Y
				ChangeSceneThread,	// �X���b�h�֐��̃A�h���X
				Data,				// �X���b�h�ɓn������
				0,					// 0�i�������s�j�ACREATE_SUSPENDED�i�ꎞ��~�j
				nullptr);				// �X���b�h���ʎq�BNULL�ł���
			m_Stack.pop();
		} else {
			// ��̏ꍇ
			// �X���b�h�J�n
			m_hThread = (HANDLE)_beginthreadex(
				nullptr,				// SECURITY_ATTRIBUTES�ւ̃|�C���^orNULL
				0,					// �X�^�b�N�T�C�Y
				InitSceneThread,	// �X���b�h�֐��̃A�h���X
				pScene,				// �X���b�h�ɓn������
				0,					// 0�i�������s�j�ACREATE_SUSPENDED�i�ꎞ��~�j
				nullptr);				// �X���b�h���ʎq�BNULL�ł���
		}
	}

	m_Stack.push(pScene);
	return true;
}


////////////////////////////////////////////////////////////////////////////
//	�֐���	�F	PopLoadScene
//	�����T�v�F	�t���[����pop����B�ǂݍ��݉�ʂ���
//	����	�F	
//	�o��	�F	
////////////////////////////////////////////////////////////////////////////
void SceneManagerWin::PopLoadScene(void) {
	if (m_Stack.empty()) {
		Debug::Log("pop����V�[���͂���܂���");
		return;
	}

	SceneBase* pScene = m_Stack.top();

	//----- �ǂݍ��݊J�n
	m_Loading->ReStart();
	m_nLoadingFlag = LOADING_NOW;

	//----- �X���b�h�J�n
	m_hThread = (HANDLE)_beginthreadex(
		nullptr,				// SECURITY_ATTRIBUTES�ւ̃|�C���^orNULL
		0,					// �X�^�b�N�T�C�Y
		ReleaseSceneThread,	// �X���b�h�֐��̃A�h���X
		pScene,				// �X���b�h�ɓn������
		0,					// 0�i�������s�j�ACREATE_SUSPENDED�i�ꎞ��~�j
		nullptr);				// �X���b�h���ʎq�BNULL�ł���

	m_Stack.pop();
}


////////////////////////////////////////////////////////////////////////////
//	�֐���	�F	PushLoadScene
//	�����T�v�F	�V�[����push����B�ǂݍ��݉�ʂ���
//	����	�F	pScene	push����V�[���̃|�C���^
//	�o��	�F	���������true���s�����false
////////////////////////////////////////////////////////////////////////////
bool SceneManagerWin::PushLoadScene(SceneBase* pScene) {
	if (!pScene) {
		Debug::LogError("Push�������V�[���̎��Ԃ�����܂���");
		return false;
	}

	//----- �ǂݍ��݊J�n
	if (!m_Loading->ReStart()) {
		Debug::LogError("���[�f�B���O��ʗp�V�[���̍ď������Ɏ��s���܂���");
	}

	if (pScene->GetMakeFlg()) {
		// ���\�[�X�m�ۍς�
		if (!pScene->ReStart()) {
			Debug::LogError("Push�����V�[���̍ď������Ɏ��s���܂���");
			pScene->ReleaseMain();
			return false;
		}
	} else {
		// ���\�[�X�m�ۂ��Ă˂�
		m_nLoadingFlag = LOADING_NOW;
		//----- �X���b�h�J�n
		m_hThread = (HANDLE)_beginthreadex(
			nullptr,				// SECURITY_ATTRIBUTES�ւ̃|�C���^orNULL
			0,					// �X�^�b�N�T�C�Y
			InitSceneThread,	// �X���b�h�֐��̃A�h���X
			pScene,				// �X���b�h�ɓn������
			0,					// 0�i�������s�j�ACREATE_SUSPENDED�i�ꎞ��~�j
			nullptr);				// �X���b�h���ʎq�BNULL�ł���
	}

	m_Stack.push(pScene);
	return true;
}