//	�A�j���[�V�����J�[�u
// 2017. 2.20	�v���O�����쐬
// Author		SyunMizuno

#pragma once


#include	"../Convert/Convert.h"
#include	<vector>


namespace MSLib {

	//----- �⊮�̎��
	enum EaseType {
		// Quad
		EaseInQuad,
		EaseOutQuad,
		EaseInOutQuad,
		// Cubic
		EaseInCubic,
		EaseOutCubic,
		EaseInOutCubic,
		// Quart
		EaseInQuart,
		EaseOutQuart,
		EaseInOutQuart,
		// Quint
		EaseInQuint,
		EaseOutQuint,
		EaseInOutQuint,
		// Expo
		EaseInExpo,
		EaseOutExpo,
		EaseInOutExpo,
		// Circ
		EaseInCirc,
		EaseOutCirc,
		EaseInOutCirc,
		// Sine
		EaseInSine,
		EaseOutSine,
		EaseInOutSine,
		// liner
		EaseLiner,
		// Bounce
		EaseInBounce,
		EaseOutBounce,
		EaseInOutBounce,
		// Back
		EaseInBack,
		EaseOutBack,
		EaseInOutBack,
		// Elastic
		EaseInElastic,
		EaseOutElastic,
		EaseInOutElastic,
	};

	//----- �L�[�t���[��
	struct tKeyframe {
		Vector2	fInTangent;		// �O�̃L�[�t���[������A���̃L�[�t���[���ɋ߂Â��Ƃ��̐ڐ�
		Vector2	fOutTangent;	// ���̃L�[�t���[���Ɍ������āA�L�[�t���[���𗣂��ۂ̐ڐ�
		float	fTime;			// �L�[�t���[���̎���
		float	fValue;			// �L�[�t���[���ł̃J�[�u�̒l

		tKeyframe(float time, float value) :
			fInTangent(time, value),
			fOutTangent(time, value),
			fTime(time),
			fValue(value) {}
		tKeyframe(float time, float value, Vector2 inTangent, Vector2 outTangent) :
			fInTangent(inTangent),
			fOutTangent(outTangent),
			fTime(time),
			fValue(value) {}
		explicit tKeyframe(tKeyframe& key) :
			fInTangent(key.fInTangent),
			fOutTangent(key.fOutTangent),
			fTime(key.fTime),
			fValue(key.fValue) {}
	};


	class AnimationCurve {
	private:
		std::vector<tKeyframe*>	m_Keys;			// �o�^�ς݂̃L�[�t���[��
		EaseType				m_CurrentEase;	// ���݂̕⊮�̎��

	public:
		AnimationCurve();
		virtual ~AnimationCurve();

		// �⊮�ݒ�
		void SetEase(EaseType type);
		// �⊮�擾
		EaseType GetEase();

		// �L�[�̐����擾
		int Length();

		/* �L�[�̒ǉ�
		// time		:	�L�[��ǉ����鎞��
		// value	:	�L�[�̒l
		// return	:	�ǉ����ꂽ�L�[�̃C���f�b�N�X
		//				���ɃL�[�����̎��Ԃɑ��݂���ꍇ��-1
		*/
		int AddKey(float time, float value);

		/* �L�[�̒ǉ�
		// key		:	�ǉ�����L�[�t���[��
		// return	:	�ǉ����ꂽ�L�[�̃C���f�b�N�X
		//				���ɃL�[�����̎��Ԃɑ��݂���ꍇ��-1
		*/
		int AddKey(tKeyframe& key);

		/* �L�[�̍폜
		// index	:	�폜����L�[�̃C���f�b�N�X
		*/
		void RemoveKey(int index);

		/* time�̃J�[�u��]��
		// time		:	�]���������J�[�u���̎���
		// return	:	�w�肳�ꂽ���Ԃ̃J�[�u�̒l
		*/
		float Evaluate(float time);

#pragma region EaseCreate
		// Liner
		void CreateLiner();
		// Quad
		void CreateInQuad();
		void CreateOutQuad();
		void CreateInOutQuad();
		// Cubic
		void CreateInCubic();
		void CreateOutCubic();
		void CreateInOutCubic();
		// Quart
		void CreateInQuart();
		void CreateOutQuart();
		void CreateInOutQuart();
		// Quint
		void CreateInQuint();
		void CreateOutQuint();
		void CreateInOutQuint();
		// Expo
		void CreateInExpo();
		void CreateOutExpo();
		void CreateInOutExpo();
		// Circ
		void CreateInCirc();
		void CreateOutCirc();
		void CreateInOutCirc();
		// Sine
		void CreateInSine();
		void CreateOutSine();
		void CreateInOutSine();
		// Bounce
		void CreateInBounce();
		void CreateOutBounce();
		void CreateInOutBounce();
		// Back
		void CreateInBack();
		void CreateOutBack();
		void CreateInOutBack();
		// Elastic
		void CreateInElastic();
		void CreateOutElastic();
		void CreateInOutElastic();
#pragma endregion

	protected:
		// �⊮�̕ύX
		void ChangeEase(EaseType type);
	};

};