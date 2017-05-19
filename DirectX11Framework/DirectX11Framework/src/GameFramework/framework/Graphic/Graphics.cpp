// �O���t�B�b�N
// 2017. 4.24	�v���O�����쐬
// author	:	SyunMizuno

#include	"Graphics.h"
#include	"../Resource/Base/IResource.h"


namespace MSLib {

	ID3D11DeviceContext* Graphics::m_pDeviceContext = nullptr;

	Graphics::Graphics() {

	}

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


	/*									//
	//			�u�����h�̐ݒ�			//
	//									*/
	void Graphics::SetBlend(BlendType type) {
		m_Blend.Set(type, IResource::GetDevice(), GetDevice());
	}

	void Graphics::SetAlphaEnable(const bool alpha) {
		m_Blend.SetAlphaEnable(alpha, IResource::GetDevice(), GetDevice());
	}

};