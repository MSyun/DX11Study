// �V�F�[�_
// 2017.05.12	: �v���O�����쐬
// author		: SyunMizuno


#pragma once


#include	"../../Base/IResource.h"
#include	"../../../Convert/Convert.h"



class Shader	:	public	IResource {
private:
	struct SIMPLESHADER_CONSTANT_BUFFER {
		Matrix	mWorld;
		Matrix	mWVP;
		Vector4	vLightDir;
		Vector4	vDiffuse;
		Vector4	vEye;
	};


	ID3D11InputLayout*	m_pVertexLayout;
	ID3D11VertexShader*	m_pVertexShader;
	ID3D11PixelShader*	m_pPixelShader;

	ID3D11Buffer*		m_pConstantBuffer;

public:
	Shader();
	virtual ~Shader();

	bool Create(const string name) override;
	void Delete() override;

	ID3D11InputLayout* GetVertexLayout() { return m_pVertexLayout; }
	ID3D11VertexShader* GetVertexShader() { return m_pVertexShader; }
	ID3D11PixelShader* GetPixelShader() { return m_pPixelShader; }
	ID3D11Buffer* GetConstantBuffer() { return m_pConstantBuffer; }

private:
	/* ���_�V�F�[�_�쐬
	// fileName	: �t�@�C����
	*/
	bool CreateVertexShader(const string fileName);

	/* �s�N�Z���V�F�[�_�쐬
	// fileName	: �t�@�C����
	*/
	bool CreatePixelShader(const string fileName);

	/* ���_�C���v�b�g���C�A�E�g�쐬
	// pCompiled	: ���_�u���u
	*/
	bool CreateInputLayout(ID3DBlob* pCompiled);

	/* �R���X�^���g�o�b�t�@�[�쐬 */
	bool CreateConstantBuffer();
};