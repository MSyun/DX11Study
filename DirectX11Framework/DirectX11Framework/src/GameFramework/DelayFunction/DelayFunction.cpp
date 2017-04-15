//	�x���^�֐��N���X
// 2017. 3.22	�v���O�����쐬
// author		SyunMizuno


#include	"DelayFunction.h"
#include	"Collection/DelayFunctionCollection.h"
#include	"../framework/Debug/Debug.h"
#include	"../framework/Time/Time.h"


/*
	memo	:
			��ɃC���X�^���X�G���[���N����͂��Ȃ̂ŃX�}�[�g�|�C���^��
			�g�p����`�ɕύX���邱��
*/



/*									//
//			�R���X�g���N�^			//
//									*/
DelayFunction::DelayFunction(
	std::function<void(void)> func,
	double time,
	bool timeScale) :
	m_dExeTime(-1.0),
	m_bTimeScale(timeScale)
{
	Regist(func, time);
	DelayFunctionCollection::Add(this);
}


/*									//
//			�f�X�g���N�^			//
//									*/
DelayFunction::~DelayFunction() {
}


/*									//
//				�v��				//
//									*/
// return : true ���s�I��. false ���s��
bool DelayFunction::TimeMate() {
	if (m_bTimeScale) {
		m_dExeTime -= MateScale();
	} else {
		m_dExeTime -= MateNoScale();
	}

	bool end = CheckEnd();
	if (end) {
		m_Function.Invoke();
	}
	return CheckEnd();
}


/*									//
//				�o�^				//
//									*/
void DelayFunction::Regist(std::function<void(void)> func, double time) {
	if (time < 0.0f) {
		Debug::LogError("DelayFunction::Regist : �ݒ肵�����Ԃ������ɂȂ��Ă��܂�");
	}
	m_Function.Set(func);
	m_dExeTime = time;
}


/*									//
//			���s�I���m�F			//
//									*/
// return : true ���s�I��. false ���s��
bool DelayFunction::CheckEnd() {
	return m_dExeTime <= 0.0;
}


/*									//
//		TimeScale�Ɉˑ�����v��		//
//									*/
double DelayFunction::MateScale() {
	return Time::GetDeltaTime();
}


/*									//
//		TimeScale�Ɉˑ����Ȃ��v��	//
//									*/
double DelayFunction::MateNoScale() {
	return Time::GetUnScaledDeltaTime();
}



void DelayFunc(std::function<void(void)> func, double time, bool timeScale) {
	DelayFunction* DF = new DelayFunction(func, time, timeScale);
}