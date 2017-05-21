// シェーダメッシュ用コンスタントバッファー
// 2017.05.16	: プログラム作成
// author		: SyunMizuno

#pragma once


#include	"../Base/ConstantBuffer.h"


namespace MSLib {
	namespace ShaderCollection {

		struct MESH_CONSTANT_BUFFER {
			Matrix	World;
			Matrix	WVP;
		};

		class ConstantBufferMesh : public	ConstantBuffer {
		private:
			MESH_CONSTANT_BUFFER m_mesh;

		public:
			ConstantBufferMesh(int resourceNum);
			virtual ~ConstantBufferMesh();

			void Set() override;

			void World(const Matrix& world);
			void WVP(const Matrix& wvp);

			virtual bool Create() override;
		};

	}
}