///////////////////////////////////////////////////////////////
// �V�[���t�F�[�h�x�[�X�N���X
// author		SyunMizuno
// 2016. 1.27	�v���O�����쐬
// 2016. 4.18	�֐��ǉ�
// 2017. 1. 4	Event�ǉ�
///////////////////////////////////////////////////////////////

#pragma once

#include	"../Base/SceneBase.h"
#include	"../../Convert/Convert.h"
#include	"../../CPPEvent/CPPEvent.h"

/*
	memo	:
		�t�F�[�h�p�V�[���͂��̃N���X���p�����邱��
		�R���X�g���N�^�A�f�X�g���N�^��Init,Release���Ăяo���Ȃ�����
*/

namespace MSLib {

	class	SceneFadeBase : public	SceneBase {
	private:
		float	m_fAlpha;	// �A���t�@�l
		Vector2	m_vSize;

	protected:
		bool	m_bExe;		// ���s�t���O
		bool	m_bIn;		// �t�F�[�h�C���E�t�F�[�h�A�E�g
		float	m_fTime;	// �t�F�[�h����
		bool	m_bChange;	// �ύX�\�t���O

		// �`��p�N���X
	//	Sprite*			m_pSprite;

		// Event
		CPPEvent<>*	m_onBeginFadeIn;
		CPPEvent<>*	m_onEndFadeIn;
		CPPEvent<>*	m_onBeginFadeOut;
		CPPEvent<>*	m_onEndFadeOut;

	public:
		SceneFadeBase(
			bool _awake = false,
			int _width = 1280,
			int _height = 720,
			float _time = 1.0f);
		virtual ~SceneFadeBase() {};
		void Update();
		virtual void Draw();

		// �ď�����
		virtual bool ReStart(void);
		// ���s
		void Exe(void);
		bool Change(void);

		void SetFadeTime(float _time) { if (_time > 0.0f) m_fTime = _time; }
		void SetSize(int width, int height);

		// Event
		CPPEvent<>* GetOnBeginFadeIn() { return m_onBeginFadeIn; }
		CPPEvent<>* GetOnEndFadeIn() { return m_onEndFadeIn; }
		CPPEvent<>* GetOnBeginFadeOut() { return m_onBeginFadeOut; }
		CPPEvent<>* GetOnEndFadeOut() { return m_onEndFadeOut; }

	protected:
		virtual bool Init();
		virtual void Release();
		// �t�F�[�h����
		virtual void FadeIn();
		virtual void FadeOut();

		virtual void OnAwake();
	};

}