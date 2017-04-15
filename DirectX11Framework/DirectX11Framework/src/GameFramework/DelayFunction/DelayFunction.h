//	�x���^�֐��N���X
// 2017. 3.22	�v���O�����쐬
// author		SyunMizuno


#pragma once


#include	<functional>
#include	"../framework/Delegate/Delegate.h"


class DelayFunction {
private:
	double			m_dExeTime;		// ���s����
	Delegate<void>	m_Function;		// �o�^�֐�
	bool			m_bTimeScale;	// TimeScale�̈ˑ�

public:
	DelayFunction(
		std::function<void(void)> func,
		double time,
		bool timeScale = true);
	virtual ~DelayFunction();

	// ���Ԍv��
	// return : true ���s�I��. false ���s��
	bool TimeMate();

private:
	// �o�^
	void Regist(std::function<void(void)> func, double time);

	// ���s�I���m�F
	// return : true ���s�I��. false ���s��
	bool CheckEnd();

	// TimeScale�Ɉˑ�����v��
	double MateScale();
	// TimeScale�Ɉˑ����Ȃ��v��
	double MateNoScale();
};

// �g�p
void DelayFunc(std::function<void(void)> func, double time, bool timeScale = true);