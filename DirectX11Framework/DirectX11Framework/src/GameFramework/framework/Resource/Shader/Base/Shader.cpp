// シェーダ
// 2017.05.12	: プログラム作成
// author		: SyunMizuno


#include	"Shader.h"
#include	<tchar.h>
#include	<D3DX11.h>
#include	"../../../Utility/System/SystemUtility.h"
#include	"../../../Debug/Debug.h"
#include	"../../../Graphic/Graphics.h"



Shader::Shader() :
	m_pVS(nullptr),
	m_pPS(nullptr),
	m_pBuffer(nullptr),
	m_pMatBuff(nullptr)
{

}

Shader::~Shader() {
	Delete();
}

bool Shader::Create(const string name) {
	m_pVS = new ShaderCollection::VertexShader(
		name.c_str(),
		"VS",
		"vs_5_0");

	m_pPS = new ShaderCollection::PixelShader(
		name.c_str(),
		"PS",
		"ps_5_0");

	m_pBuffer = new ShaderCollection::Buffer::ConstantBuffer;
	m_pMatBuff = new ShaderCollection::Buffer::ConstantBufferMaterial;

	m_pBuffer->Create();
	m_pMatBuff->Create();

	return true;
}

void Shader::Delete() {
	SAFE_DELETE(m_pMatBuff);
	SAFE_DELETE(m_pBuffer);
	SAFE_DELETE(m_pPS);
	SAFE_DELETE(m_pVS);
}

void Shader::Begin() {
	m_pVS->Begin();
	m_pPS->Begin();
}

void Shader::End() {
	m_pVS->End();
	m_pPS->End();
}

ShaderCollection::Buffer::ConstantBuffer* Shader::GetBuffer() {
	return m_pBuffer;
}

ShaderCollection::Buffer::ConstantBufferMaterial* Shader::GetBuffMat() {
	return m_pMatBuff;
}


namespace ShaderCollection {
	/*									//
	//	シェーダファイルからブロブの生成//
	//									*/
	bool CompileFromFileToBlob(
		LPCSTR pFileName,
		LPCSTR pFunctionName,
		LPCSTR pProfile,
		ID3DBlob** ppBlob)
	{
		ID3DBlob* pErrors = nullptr;
		HRESULT hr = D3DX11CompileFromFile(
			pFileName,
			nullptr,
			nullptr,
			pFunctionName,
			pProfile,
			0,
			0,
			nullptr,
			ppBlob,
			&pErrors,
			nullptr);
		if (FAILED(hr)) {
			Debug::LogError((LPCTSTR)pErrors->GetBufferPointer());
			return false;
		}
		SAFE_RELEASE(pErrors);

		return true;
	}
}