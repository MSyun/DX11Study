//////////////////////////////////////////////////////////////
// �^�C�}�[�N���X
// 2016. 7. 8	�N���X�쐬
// �쐬��		SyunMizuno
//////////////////////////////////////////////////////////////


#include	"Time.h"

/*
	MEMO	:
			//�f���^�^�C���������[�X�ɂȂ�ƑS�����肵�Ȃ�����
			//1.0f�ŋ����ɉ�����
*/


#pragma comment(lib, "winmm.lib")

DWORD	Time::m_dwCurrentFrameRate	= 0;		// ���݂�1�b�Ԃ�FPS
DWORD	Time::m_dwSettingFrameRate	= 60;		// �ݒ肵��FPS
float	Time::m_fDeltaTime			= 1.0f;		// �t���[���X�V�̊����i��{1.0f
float	Time::m_fTimeScale			= 1.0f;		// ���Ԍo�߂̃t�@�N�^�i1.0�Œʏ�A2.0��2�{��
float	Time::m_fTime				= -1.0f;	// �Q�[���J�n����̎���
float	Time::m_fTimeUnScaled		= -1.0f;	// �Q�[���J�n����̎���(TimeScale�̉e���Ȃ�
DWORD	Time::m_dwFrameCount		= 0;		// �t���[���ʉ߉�
DWORD	Time::m_dwLastTime			= 0;		// �O�̃t���[�������s���ꂽ��������
float	Time::m_fFrameTime			= 0.0f;		// 1�t���[���Ԃ̃~���b
DWORD	Time::m_dwPrevMinutes		= 0;		// �O�̃t���[������


/*									//
//			�R���X�g���N�^			//
//									*/
Time::Time() {
	timeBeginPeriod(1);

	SetFrameRate(m_dwSettingFrameRate);
}


/*									//
//			�f�X�g���N�^			//
//									*/
Time::~Time() {
	timeEndPeriod(1);
}


/*									//
//		�t���[�����[�g�̐ݒ�		//
//									*/
void Time::SetFrameRate(DWORD frame) {
	m_dwSettingFrameRate = frame;
	m_fFrameTime = 1000.0f / frame;
}


/*									//
//		���Ԃ̃X�P�[���̐ݒ�		//
//									*/
void Time::SetTimeScale(float scale) {
	m_fTimeScale = scale;
}


/*									//
//				�X�V				//
//									*/
void Time::Update() {
	m_dwFrameCount++;

	// �v���J�n
	if( m_fTime == -1.0f ) {
		m_dwLastTime = m_dwPrevMinutes = timeGetTime();
		m_fTime = 0.0f;
		m_fTimeUnScaled = 0.0f;
		return;
	}

	// ���Ԃ܂ő҂���
	DWORD dwTime = (DWORD)(m_dwFrameCount * m_fFrameTime + m_dwLastTime);
//	DWORD hoge = timeGetTime();
////	while(timeGetTime() <= dwTime) {
//	while(hoge <= dwTime) {
//		hoge += (DWORD)m_fFrameTime;
////		Sleep(1);	// �x��
//	}
	DWORD time = timeGetTime();

	// �X�V�X�s�[�h�̊����v�Z
	m_fDeltaTime = (time - m_dwPrevMinutes) / m_fFrameTime / m_dwSettingFrameRate;
	m_fTime += m_fDeltaTime * m_fTimeScale;
	m_fTimeUnScaled += m_fDeltaTime;
	m_dwPrevMinutes = time;

	// 1�b�o��
	if( time - m_dwLastTime >= 1000 ) {
		m_dwLastTime = time;
		m_dwCurrentFrameRate = m_dwFrameCount;	// �ŐV�t���[����
		m_dwFrameCount		= 0;
	}
}


/*									//
//		���݂�1�b�Ԃ�FPS���擾		//
//									*/
DWORD Time::GetFrameRate() {
	return m_dwCurrentFrameRate;
}


/*									//
//			�ݒ肵��FPS���擾		//
//									*/
DWORD Time::GetSettingFrameRate() {
	return m_dwSettingFrameRate;
}


/*									//
//			�t�@�N�^���擾			//
//									*/
// TimeScale�Ɉˑ�����
float Time::GetDeltaTime() {
	return m_fDeltaTime * m_fTimeScale;
}
// TimeScale�Ɉˑ����Ȃ�
float Time::GetUnScaledDeltaTime() {
	return m_fDeltaTime;
}


/*									//
//		�Q�[���J�n����̎���		//
//									*/
// TimeScale�Ɉˑ�����
float Time::GetTime() {
	return m_fTime;
}
// TimeScale�Ɉˑ����Ȃ�
float Time::GetUnScaledTime() {
	return m_fTimeUnScaled;
}