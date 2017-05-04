///////////////////////////////////////////////////////////////
// �V�[���}�l�[�W���[�N���X
// author		SyunMizuno
// 2015.12.07	�v���O�����쐬
// 2016.01.26	vector����map�֕ύX
// 2016.01.27	�t�F�[�h�ǉ�
// 2016.07.06	2�V�[���Đ��@�\�ǉ�
///////////////////////////////////////////////////////////////

#pragma once

#include	"../Base/SceneBase.h"
#include	"../Fade/SceneFadeBase.h"
#include	<stack>
#include	<map>
#include	<string>
#include	"../../Singleton/Singleton.h"

using namespace std;


/*
	memo:
		�e���@�\�ǉ����͗񋓌^�ɒǉ����R�}���h����邱��
*/

class SceneManagerBase {
protected:
#pragma region enum

	// �񋓌^
	typedef enum {
		SCENEMANAGER_NO = 0,	// �ύX���Ȃ�

		SCENEMANAGER_POP,		// pop����
		SCENEMANAGER_PUSH,		// push����
		SCENEMANAGER_CHANGE,	// �ύX����
		SCENEMANAGER_RESTART,	// �ď�����

		// ���N���X�p����Ŏg�p��
		SCENEMANAGER_LOADING_POP,		// ���[�h��ʂ���pop
		SCENEMANAGER_LOADING_PUSH,		// ���[�h��ʂ���push
		SCENEMANAGER_LOADING_CHANGE,	// ���[�h��ʂ���ύX
		SCENEMANAGER_LOADING_RESTART,	// ���[�h��ʂ���ď�����
	} _command;

#pragma endregion

#pragma region variable

	map<string, SceneBase*>	m_MapScene;		// �o�^���ꂽ�V�[��
	stack<SceneBase*>		m_Stack;		// �V�[���̃X�^�b�N
	string					m_TmpSceneName;	// �ύX��V�[��
	int						m_nCommand;		// �V�[������̃R�}���h
	SceneFadeBase*			m_pFade;		// �t�F�[�h�p�V�[��

#pragma endregion

public:
#pragma region method

	SceneManagerBase();
	~SceneManagerBase() { Release(); }
	void Release(void);

	// �V�[���̒ǉ��E�폜
	bool RegistScene(SceneBase* pScene, const string SceneName);
	template<typename T>bool RegistSceneMakeInstance(string SceneName) { T* data = new T; return RegistScene(data, SceneName); }
	void DeleteScene(const string SceneName);
	bool RegistFadeScene(SceneFadeBase* pScene);
	void DeleteFadeScene();

#pragma region Command

	void PopCommand(void) { m_nCommand = SCENEMANAGER_POP; }
	void PushCommand(const string SceneName) { m_TmpSceneName.clear(); m_TmpSceneName = SceneName; m_nCommand = SCENEMANAGER_PUSH; }
	void ChangeCommand(const string SceneName) { m_TmpSceneName.clear(); m_TmpSceneName = SceneName; m_nCommand = SCENEMANAGER_CHANGE; }
	void RestartCommand(void) { m_nCommand = SCENEMANAGER_RESTART; }
	void CancelCommand(void) { m_nCommand = SCENEMANAGER_NO; }
	void PopLoadCommand(void) { m_nCommand = SCENEMANAGER_LOADING_POP; }
	void PushLoadCommand(const string SceneName) { m_TmpSceneName = SceneName; m_nCommand = SCENEMANAGER_LOADING_PUSH; }
	void ChangeLoadCommand(const string SceneName) { m_TmpSceneName = SceneName; m_nCommand = SCENEMANAGER_LOADING_CHANGE; }
	void RestartLoadCommand(void) { m_nCommand = SCENEMANAGER_LOADING_RESTART; }

#pragma endregion

	void Draw() { if (m_pFade) m_pFade->Draw(); }

	SceneBase* GetScene(void);

	SceneFadeBase* GetFade(void) { return m_pFade; }

#pragma endregion

protected:
#pragma region conceal method

	SceneBase* GetTopScene(void) { return ((m_Stack.empty()) ? NULL : m_Stack.top()); }
	void PopScene(void);
	bool PushScene(SceneBase* pScene);
	bool ChangeScene(SceneBase* pScene);
	void SceneAllDelete(void);

#pragma endregion
};

class SceneManager : public SceneManagerBase, public Singleton<SceneManager> {};

// ����Ŏg�p���₷���Ȃ�
inline SceneManager* GetSceneManager(void) {
	return SceneManager::Instance();
}