// シェーダ
// 2017.05.12	: プログラム作成
// author		: SyunMizuno


#include	"Shader.h"
#include	<tchar.h>
#include	<D3DX11.h>
#include	"../../../Utility/System/SystemUtility.h"
#include	"../../../Debug/Debug.h"
#include	"../../../Graphic/Graphics.h"


namespace MSLib {

	Shader::Shader() :
		m_pVS(nullptr),
		m_pPS(nullptr),
		m_pFrameBuff(nullptr),
		m_pMatBuff(nullptr),
		m_pLightBuff(nullptr),
		m_pMeshBuff(nullptr)
	{

	}

	Shader::~Shader() {
		Delete();
	}

	bool Shader::Create(const std::string& name) {
		m_pVS = new ShaderCollection::VertexShader(
			name.c_str(),
			"VS",
			"vs_5_0");

		m_pPS = new ShaderCollection::PixelShader(
			name.c_str(),
			"PS",
			"ps_5_0");

		m_pFrameBuff = new ShaderCollection::ConstantBufferFrame(0);
		m_pMatBuff = new ShaderCollection::ConstantBufferMaterial(2);
		m_pLightBuff = new ShaderCollection::ConstantBufferLight(3);
		m_pMeshBuff = new ShaderCollection::ConstantBufferMesh(1);

		m_pFrameBuff->Create();
		m_pMatBuff->Create();
		m_pLightBuff->Create();
		m_pMeshBuff->Create();

		return true;
	}

	void Shader::Delete() {
		SAFE_DELETE(m_pMeshBuff);
		SAFE_DELETE(m_pLightBuff);
		SAFE_DELETE(m_pMatBuff);
		SAFE_DELETE(m_pFrameBuff);
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

	ShaderCollection::ConstantBufferFrame* Shader::GetBuffFrame() {
		return m_pFrameBuff;
	}

	ShaderCollection::ConstantBufferMaterial* Shader::GetBuffMat() {
		return m_pMatBuff;
	}

	ShaderCollection::ConstantBufferLight* Shader::GetBuffLight() {
		return m_pLightBuff;
	}

	ShaderCollection::ConstantBufferMesh* Shader::GetBuffMesh() {
		return m_pMeshBuff;
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

}