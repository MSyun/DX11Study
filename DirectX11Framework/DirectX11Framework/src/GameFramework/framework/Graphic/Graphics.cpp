// �O���t�B�b�N
// 2017. 4.24	�v���O�����쐬
// author	:	SyunMizuno


#include	"Graphics.h"


ID3D11DeviceContext* Graphics::m_pDeviceContext = nullptr;



/*									//
//			�R���X�g���N�^			//
//									*/
Graphics::Graphics() {

}


/*									//
//			�f�X�g���N�^			//
//									*/
Graphics::~Graphics() {

}


/*									//
//			�f�o�C�X�̎擾			//
//									*/
ID3D11DeviceContext* Graphics::GetDevice() {
	return m_pDeviceContext;
}


/*									//
//			�f�o�C�X�̐ݒ�			//
//									*/
void Graphics::SetDevice(ID3D11DeviceContext* _dev) {
	m_pDeviceContext = _dev;
}