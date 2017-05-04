// Windows�pSceneManager�N���X
// 2015.12.15	�v���O�����쐬
// 2016.01.26	vector����map�֕ύX
// 2016.01.28	�ǂݍ��ݗ��ǉ�
// ���ώ�		SyunMizuno

#pragma once

#include	"../Base/SceneBase.h"
#include	"../Manager/SceneManager.h"
#include	<Windows.h>
#include	<process.h>


class SceneManagerWin : public	SceneManagerBase {
protected:
#pragma region variable

	SceneBase*		m_Loading;		// ���[�h�V�[��
	int				m_nLoadingFlag;	// ���[�h�t���O�B
	HANDLE			m_hThread;		// �X���b�h�n���h��
	bool			m_bLoadSuc;		// ���[�h�̐���
	unsigned int	m_uLoadWaitTime;// ���[�h���X���b�h���J�n����܂ł̃E�F�C�g
	unsigned char	m_uLoadRate;	// �ǂݍ��ݗ�
	bool			m_bLoadKey;		// �ǂݍ��ݏI���m�F
	bool			m_bLoadEndAfter;// �ǂݍ��݌�̃V�[���J�ڊm�F

#pragma endregion

public:
#pragma region method

	SceneManagerWin();
	~SceneManagerWin();
	void Release(void);

	void SetLoadingFlag(int flag) { m_nLoadingFlag = flag; }
	void SetLoadSuc(bool Success) { m_bLoadSuc = Success; }
	void SetLoadWait(unsigned int time) { m_uLoadWaitTime = time; }
	void SetLoadRate(unsigned char _rate) { m_uLoadRate = _rate; }
	unsigned char GetLoadRate(void) { return m_uLoadRate; }
	// �ǂݍ��ݏI���m�F�itrue. �ǂݍ��ݐ��� : false. �ǂݍ��ݒ�
	bool CheckLoadingEnd() { return !m_bLoadKey; }
	// �ǂݍ��ݏI��
	void LoadingEnd() { m_bLoadEndAfter = true; }

	// �V�[���̒ǉ�
	bool RegistLoadingScene(SceneBase* pScene);
	template<typename T> bool RegistLoadingSceneMakeInstance(void) { T *data = new T; return RegistLoadingScene(data); }
	void DeleteLoadingScene(void);

	SceneBase* GetScene(void);

#pragma endregion

protected:
#pragma region conceal method

	bool ChangeLoadScene(SceneBase* pScene);
	void PopLoadScene(void);
	bool PushLoadScene(SceneBase* pScene);

#pragma endregion
};

class SceneManagerWins : public	SceneManagerWin, public	Singleton<SceneManagerWins> {};

// ����Ŏg�p���₷���Ȃ�
inline SceneManagerWins* GetSceneManagerWins(void) {
	return SceneManagerWins::Instance();
}