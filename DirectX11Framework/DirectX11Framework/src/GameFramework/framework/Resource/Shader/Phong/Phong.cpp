// Phongシェーダ
// 2017.05.12	: プログラム作成
// author		: SyunMizuno


#include	"Phong.h"
#include	"../../../Utility/System/SystemUtility.h"


namespace MSLib {
	namespace ShaderCollection {

		Phong::Phong() :
			m_pFrameBuff(nullptr),
			m_pMatBuff(nullptr),
			m_pLightBuff(nullptr),
			m_pMeshBuff(nullptr)
		{
		}

		Phong::~Phong() {
			Delete();
		}

		bool Phong::Create() {
			m_pVShader = new VertexShader("Phong.hlsl", "VS", "vs_5_0");
			m_pPShader = new PixelShader("Phong.hlsl", "PS", "ps_5_0");

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

		void Phong::Delete() {
			SAFE_DELETE(m_pMeshBuff);
			SAFE_DELETE(m_pLightBuff);
			SAFE_DELETE(m_pMatBuff);
			SAFE_DELETE(m_pFrameBuff);
		}

		void Phong::Begin() {
			m_pVShader->Begin();
			m_pPShader->Begin();
		}

		void Phong::End() {
			m_pVShader->End();
			m_pPShader->End();
		}

		ShaderCollection::ConstantBufferFrame* Phong::GetBuffFrame() {
			return m_pFrameBuff;
		}
		ShaderCollection::ConstantBufferMaterial* Phong::GetBuffMat() {
			return m_pMatBuff;
		}
		ShaderCollection::ConstantBufferLight* Phong::GetBuffLight() {
			return m_pLightBuff;
		}
		ShaderCollection::ConstantBufferMesh* Phong::GetBuffMesh() {
			return m_pMeshBuff;
		}

		inline Phong* GetPhong() {
			return Phong::Instance();
		}

	}
}