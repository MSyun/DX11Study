// Fog�V�F�[�_
// 2017.05.21	: �v���O�����쐬
// author		: SyunMizuno


#pragma once


#include	"../Technique/Technique.h"
#include	"../ConstantBuffer/FogFrame/ConstantBufferFogFrame.h"
#include	"../ConstantBuffer/Light/ConstantBufferLight.h"
#include	"../ConstantBuffer/Material/ConstantBufferMaterial.h"
#include	"../ConstantBuffer/Mesh/ConstantBufferMesh.h"

//////////////////////////////////////////////////
// �ꎞ�I
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