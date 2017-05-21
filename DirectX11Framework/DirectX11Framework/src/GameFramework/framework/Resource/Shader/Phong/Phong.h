// Phong�V�F�[�_
// 2017.05.12	: �v���O�����쐬
// author		: SyunMizuno


#pragma once


#include	"../Technique/Technique.h"
#include	"../ConstantBuffer/Frame/ConstantBufferFrame.h"
#include	"../ConstantBuffer/Light/ConstantBufferLight.h"
#include	"../ConstantBuffer/Material/ConstantBufferMaterial.h"
#include	"../ConstantBuffer/Mesh/ConstantBufferMesh.h"

///////////////////////////////////////
// �ꎞ�I
#include	"../../../Singleton/Singleton.h"


namespace MSLib {
	namespace ShaderCollection {

		class Phong : public	Singleton<Phong> {
		private:
			PixelShader* m_pPShader;
			VertexShader* m_pVShader;
			ConstantBufferFrame* m_pFrameBuff;
			ConstantBufferMaterial* m_pMatBuff;
			ConstantBufferLight* m_pLightBuff;
			ConstantBufferMesh* m_pMeshBuff;

		public:
			Phong();
			virtual ~Phong();

			bool Create();
			void Delete();

			void Begin();
			void End();

			ConstantBufferFrame* GetBuffFrame();
			ConstantBufferMaterial* GetBuffMat();
			ConstantBufferLight* GetBuffLight();
			ConstantBufferMesh* GetBuffMesh();
		};

		inline Phong* GetPhong();

	}
}