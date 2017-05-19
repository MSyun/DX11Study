// ���\�[�X�C���^�[�t�F�[�X
// 2017.04.24	: �v���O�����쐬
// author		: SyunMizuno

#include	"IResource.h"
#include	"../../Debug/Debug.h"


namespace MSLib {

	ID3D11Device* IResource::m_pDevice = nullptr;

	/*									//
	//			�f�o�C�X�̐ݒ�			//
	//									*/
	void IResource::SetDevice(ID3D11Device* device) {
		m_pDevice = device;

		Debug::Log("�f�o�C�X�𐶐�");
	}


	/*									//
	//			�f�o�C�X�̎擾			//
	//									*/
	ID3D11Device* IResource::GetDevice() {
		return m_pDevice;
	}

}