// シェーダメッシュ用コンスタントバッファー
// 2017.05.16	: プログラム作成
// author		: SyunMizuno


#include	"ConstantBufferMesh.h"
#include	"../../../../Graphic/Graphics.h"


namespace MSLib {
	namespace ShaderCollection {

		ConstantBufferMesh::ConstantBufferMesh(int resourceNum) :
			ConstantBuffer(resourceNum)
		{
		}

		ConstantBufferMesh::~ConstantBufferMesh()
		{
		}

		void ConstantBufferMesh::Set() {
			auto context = Graphics::GetDevice();
			m_pBuffer->Update((void*)&m_mesh);
			auto buf = m_pBuffer->buf();

			context->VSSetConstantBuffers(m_ResourceNumber, 1, &buf);
			context->PSSetConstantBuffers(m_ResourceNumber, 1, &buf);
		}

		void ConstantBufferMesh::World(const Matrix& world) {
			m_mesh.World = world;
		}

		void ConstantBufferMesh::WVP(const Matrix& wvp) {
			m_mesh.WVP = wvp;
		}

		bool ConstantBufferMesh::Create() {
			m_pBuffer = new Buffer(sizeof(MESH_CONSTANT_BUFFER));

			return true;
		}

	}
}