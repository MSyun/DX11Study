// シェーダメッシュ用コンスタントバッファー
// 2017.05.16	: プログラム作成
// author		: SyunMizuno


#include	"ConstantBufferMesh.h"
#include	"../../../../Graphic/Graphics.h"


namespace MSLib {
	namespace ShaderCollection {
		namespace Buffer {

			ConstantBufferMesh::ConstantBufferMesh() :
				ConstantBuffer(1)
			{
			}

			ConstantBufferMesh::~ConstantBufferMesh()
			{
			}

			void ConstantBufferMesh::EndPass() {
				auto context = Graphics::GetDevice();
				memcpy_s(pData.pData, pData.RowPitch, (void*)(&m_mesh), sizeof(m_mesh));
				context->Unmap(m_pBuffer, 0);

				context->VSSetConstantBuffers(m_ResourceNumber, 1, &m_pBuffer);
				context->PSSetConstantBuffers(m_ResourceNumber, 1, &m_pBuffer);
			}

			void ConstantBufferMesh::World(const Matrix& world) {
				m_mesh.World = world;
			}

			void ConstantBufferMesh::WVP(const Matrix& wvp) {
				m_mesh.WVP = wvp;
			}

			bool ConstantBufferMesh::Create() {
				if (!CreateConstantBuffer(
					&m_pBuffer,
					sizeof(MESH_CONSTANT_BUFFER)))
					return false;

				return true;
			}

		}
	}
}