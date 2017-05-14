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



class Shader	:	public	IResource {
private:
	ShaderCollection::VertexShader* m_pVS;
	ShaderCollection::PixelShader* m_pPS;
	ShaderCollection::Buffer::ConstantBuffer* m_pBuffer;
	ShaderCollection::Buffer::ConstantBufferMaterial* m_pMatBuff;

public:
	Shader();
	virtual ~Shader();

	bool Create(const string name) override;
	void Delete() override;

	void Begin();
	void End();

	ShaderCollection::Buffer::ConstantBuffer* GetBuffer();
	ShaderCollection::Buffer::ConstantBufferMaterial* GetBuffMat();
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