// �V�F�[�_
// 2017.05.12	: �v���O�����쐬
// author		: SyunMizuno


#pragma once


#include	"../../Base/IResource.h"
#include	"../../../Convert/Convert.h"
#include	"../TypeShader/VertexShader/VertexShader.h"
#include	"../TypeShader/PixelShader/PixelShader.h"

#include	"../ConstantBuffer/Base/ConstantBuffer.h"
#include	"../ConstantBuffer/Material/ConstantBufferMaterial.h"
#include	"../ConstantBuffer/Light/ConstantBufferLight.h"





class Shader	:	public	IResource {
private:
	ShaderCollection::VertexShader* m_pVS;
	ShaderCollection::PixelShader* m_pPS;
	ShaderCollection::Buffer::ConstantBuffer* m_pBuffer;
	ShaderCollection::Buffer::ConstantBufferMaterial* m_pMatBuff;
	ShaderCollection::Buffer::ConstantBufferLight* m_pLightBuff;

public:
	Shader();
	virtual ~Shader();

	bool Create(const string name) override;
	void Delete() override;

	void Begin();
	void End();

	ShaderCollection::Buffer::ConstantBuffer* GetBuffer();
	ShaderCollection::Buffer::ConstantBufferMaterial* GetBuffMat();
	ShaderCollection::Buffer::ConstantBufferLight* GetBuffLight();
};

namespace ShaderCollection {
	/* �V�F�[�_�t�@�C������u���u�̐���
	// pFileName		: �t�@�C����
	// pFunctionName	: �֐���
	// pProfile			: �o�[�W����
	// return			: ���������u���u
	*/
	bool CompileFromFileToBlob(
		LPCSTR pFileName,
		LPCSTR pFunctionName,
		LPCSTR pProfile,
		ID3DBlob** ppBlob);
};