//////////////////////////////////////////////////////////////
// �^�C�}�[�N���X
// 2016. 7. 8	�N���X�쐬
// �쐬��		SyunMizuno
//////////////////////////////////////////////////////////////

#pragma once

#include	<Windows.h>


class	Time {
private:
#pragma region variable

	static DWORD	m_dwCurrentFrameRate;	// ���݂�1�b�Ԃ�FPS
	static DWORD	m_dwSettingFrameRate;	// �ݒ肵��FPS
	static float	m_fDeltaTime;			// �t���[���X�V�̊����i��{1.0f
	static float	m_fTimeScale;			// ���Ԍo�߂̃t�@�N�^�i1.0�Œʏ�A2.0��2�{��
	static float	m_fTime;				// �Q�[���J�n����̎���
	static float	m_fTimeUnScaled;		// �Q�[���J�n����̎���(TimeScale�̉e���Ȃ�

#pragma endregion

#pragma region conceal variable

	static DWORD	m_dwFrameCount;		// �t���[���ʉ߉�
	static DWORD	m_dwLastTime;		// �O�̃t���[�������s���ꂽ��������
	static float	m_fFrameTime;		// 1�t���[���Ԃ̃~���b
	static DWORD	m_dwPrevMinutes;	// �O�̃t���[������

#pragma endregion

public:
#pragma region method

	Time();
	virtual ~Time();

	// �t���[�����[�g�̐ݒ�
	static void SetFrameRate(DWORD frame);
	// ���Ԃ̃X�P�[���̐ݒ�
	static void SetTimeScale(float scale);
	// �X�V
	static void Update();
	// �t���[�����[�g�̎擾
	static DWORD GetFrameRate();
	// �ݒ肵��FPS���擾
	static DWORD GetSettingFrameRate();
	// TimeScale�Ɉˑ������t�@�N�^���擾
	static float GetDeltaTime();
	// TimeScale�Ɉˑ����Ȃ��t�@�N�^���擾
	static float GetUnScaledDeltaTime();

	// TimeScale�Ɉˑ����鎞��
	static float GetTime();
	// TimeScale�Ɉˑ����Ȃ�����
	static float GetUnScaledTime();

#pragma endregion
};