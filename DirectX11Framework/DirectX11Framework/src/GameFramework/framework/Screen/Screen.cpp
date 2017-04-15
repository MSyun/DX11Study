// �X�N���[��
// 2017. 2.19	�v���O�����쐬
// author		SyunMizuno


#include	"Screen.h"


int		Screen::m_nWidth = -1;
int		Screen::m_nHeight = -1;
bool	Screen::m_bFullScreen = false;



/*									//
//				�����擾			//
//									*/
int Screen::GetWidth() {
	return m_nWidth;
}


/*									//
//				�c���擾			//
//									*/
int Screen::GetHeight() {
	return m_nHeight;
}


/*									//
//				�T�C�Y�ݒ�			//
//									*/
void Screen::SetSize(int width, int height) {
	m_nWidth = width;
	m_nHeight = height;
}


/*									//
//			�t���X�N���[���m�F		//
//									*/
bool Screen::GetFullScreen() {
	return m_bFullScreen;
}


/*									//
//			�t���X�N���[���ݒ�		//
//									*/
void Screen::SetFullScreen(bool fullScreen) {
	m_bFullScreen = fullScreen;
}