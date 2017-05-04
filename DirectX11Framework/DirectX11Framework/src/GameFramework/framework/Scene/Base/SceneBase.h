///////////////////////////////////////////////////////////////
// �V�[���x�[�X�N���X
// author		SyunMizuno
// 2015.12.05	�v���O�����쐬
// 2016. 1. 3	�����������
///////////////////////////////////////////////////////////////

#pragma once

/*
	memo	:
		�V�[���͂��̃N���X���p�����邱��
		�R���X�g���N�^�A�f�X�g���N�^��Init,Release���Ăяo���Ȃ�����
*/
class SceneBase {
private:
#pragma region variable

	bool m_bMakeFlg;	// Init���Ăяo���ꂽ��

#pragma endregion

protected:
#pragma region conceal method

	// ���\�[�X�n�͂���
	virtual bool Init() = 0;
	virtual void Release() = 0;

#pragma endregion

public:
#pragma region method

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual bool ReStart() { return true; }

	virtual bool InitMain() { m_bMakeFlg = true;	if (!Init()) { return false; } return true; }
	virtual void ReleaseMain() { m_bMakeFlg = false;	Release(); }

	SceneBase() { m_bMakeFlg = false; }
	virtual ~SceneBase() {}
	bool GetMakeFlg(void) { return m_bMakeFlg; }	// SceneManager�N���X�Ŏg�p

#pragma endregion
};