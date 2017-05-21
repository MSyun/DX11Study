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
#include	"../ConstantBuffer/Mesh/ConstantBufferMesh.h"
#include	"../ConstantBuffer/Frame/ConstantBufferFrame.h"


namespace MSLib {

	class Shader : public	IResource {
	private:
		ShaderCollection::VertexShader* m_pVS;
		ShaderCollection::PixelShader* m_pPS;
		ShaderCollection::ConstantBufferFrame* m_pFrameBuff;
		ShaderCollection::ConstantBufferMaterial* m_pMatBuff;
		ShaderCollection::ConstantBufferLight* m_pLightBuff;
		ShaderCollection::ConstantBufferMesh* m_pMeshBuff;

	public:
		Shader();
		virtual ~Shader();

		bool Create(const std::string& name) override;
		void Delete() override;

		void Begin();
		void End();

		ShaderCollection::ConstantBufferFrame* GetBuffFrame();
		ShaderCollection::ConstantBufferMaterial* GetBuffMat();
		ShaderCollection::ConstantBufferLight* GetBuffLight();
		ShaderCollection::ConstantBufferMesh* GetBuffMesh();
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

}