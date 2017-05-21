// Fogシェーダ
// 2017.05.21	: プログラム作成
// author		: SyunMizuno


#pragma once


#include	"../Technique/Technique.h"
#include	"../ConstantBuffer/FogFrame/ConstantBufferFogFrame.h"
#include	"../ConstantBuffer/Light/ConstantBufferLight.h"
#include	"../ConstantBuffer/Material/ConstantBufferMaterial.h"
#include	"../ConstantBuffer/Mesh/ConstantBufferMesh.h"

//////////////////////////////////////////////////
// 一時的
#include	"../../../Singleton/Singleton.h"


namespace MSLib {
	namespace ShaderCollection {

		class Fog	:	public	Singleton<Fog> {
		private:
			PixelShader* m_pPShader;
			VertexShader* m_pVShader;
			ConstantBufferFogFrame* m_pFrameBuff;
			ConstantBufferMaterial* m_pMatBuff;
			ConstantBufferLight* m_pLightBuff;
			ConstantBufferMesh* m_pMeshBuff;

		public:
			Fog();
			virtual ~Fog();

			bool Create();
			void Delete();

			void Begin();
			void End();

			ConstantBufferFogFrame* GetBuffFrame();
			ConstantBufferMaterial* GetBuffMat();
			ConstantBufferLight* GetBuffLight();
			ConstantBufferMesh* GetBuffMesh();
		};

		inline Fog* GetFog();

	}
}