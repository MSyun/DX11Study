// �X�N���[��
// 2017. 2.19	�v���O�����쐬
// author		SyunMizuno


#pragma once


class Screen {
private:
	static int	m_nWidth;
	static int	m_nHeight;
	static bool	m_bFullScreen;

public:
	Screen() {};
	virtual ~Screen() {};

	// �����擾
	static int GetWidth();
	// �c���擾
	static int GetHeight();
	// �T�C�Y�ݒ�
	static void SetSize(int width, int height);
	// �t���X�N���[���m�F
	static bool GetFullScreen();
	// �t���X�N���[���ݒ�
	static void SetFullScreen(bool fullScreen);
};