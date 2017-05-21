// シェーダ
// 2017.05.12	: プログラム作成
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
		/* シェーダファイルからブロブの生成
		// pFileName		: ファイル名
		// pFunctionName	: 関数名
		// pProfile			: バージョン
		// return			: 生成したブロブ
		*/
		bool CompileFromFileToBlob(
			LPCSTR pFileName,
			LPCSTR pFunctionName,
			LPCSTR pProfile,
			ID3DBlob** ppBlob);
	};

}