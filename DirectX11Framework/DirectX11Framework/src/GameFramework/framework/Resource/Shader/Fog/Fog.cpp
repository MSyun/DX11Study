// Fogシェーダ
// 2017.05.21	: プログラム作成
// author		: SyunMizuno


#include	"Fog.h"
#include	"../../../Utility/System/SystemUtility.h"



namespace MSLib {
	namespace ShaderCollection {

		Fog::Fog() :
			m_pFrameBuff(nullptr),
			m_pMatBuff(nullptr),
			m_pLightBuff(nullptr),
			m_pMeshBuff(nullptr)
		{
		}

		Fog::~Fog() {
			Delete();
		}

		bool Fog::Create() {
			m_pVShader = new VertexShader("Fog.hlsl", "VS", "vs_5_0");
			m_pPShader = new PixelShader("Fog.hlsl", "PS", "ps_5_0");

			m_pFrameBuff = new ShaderCollection::ConstantBufferFogFrame(0);
			m_pMatBuff = new ShaderCollection::ConstantBufferMaterial(2);
			m_pLightBuff = new ShaderCollection::ConstantBufferLight(3);
			m_pMeshBuff = new ShaderCollection::ConstantBufferMesh(1);

			m_pFrameBuff->Create();
			m_pMatBuff->Create();
			m_pLightBuff->Create();
			m_pMeshBuff->Create();

			return true;
		}

		void Fog::Delete() {
			SAFE_DELETE(m_pMeshBuff);
			SAFE_DELETE(m_pLightBuff);
			SAFE_DELETE(m_pMatBuff);
			SAFE_DELETE(m_pFrameBuff);
		}

		void Fog::Begin() {
			m_pVShader->Begin();
			m_pPShader->Begin();
		}

		void Fog::End() {
			m_pVShader->End();
			m_pPShader->End();
		}

		ShaderCollection::ConstantBufferFogFrame* Fog::GetBuffFrame() {
			return m_pFrameBuff;
		}
		ShaderCollection::ConstantBufferMaterial* Fog::GetBuffMat() {
			return m_pMatBuff;
		}
		ShaderCollection::ConstantBufferLight* Fog::GetBuffLight() {
			return m_pLightBuff;
		}
		ShaderCollection::ConstantBufferMesh* Fog::GetBuffMesh() {
			return m_pMeshBuff;
		}

		inline Fog* GetFog() {
			return Fog::Instance();
		}

	}
}