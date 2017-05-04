// ���\�[�X�C���^�[�t�F�[�X
// 2017.04.24	: �v���O�����쐬
// author		: SyunMizuno


#pragma once
#include	<string>
#include	<d3d11.h>
using namespace std;


class IResource {
private:
	// �f�o�C�X
	static ID3D11Device* m_pDevice;

public:

	/* �f�o�C�X�̐ݒ�
	// device : �ݒ肵�����f�o�C�X
	*/
	static void SetDevice(ID3D11Device* device);

	/* �f�o�C�X�̎擾
	// return : �f�o�C�X
	*/
	static ID3D11Device* GetDevice();

	/* ���\�[�X���쐬
	// name	: �t�@�C���f�B���N�g��
	*/
	virtual bool Create(const string name) = 0;

	/* ���\�[�X���폜 */
	virtual void Delete() = 0;
};