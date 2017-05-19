// メッシュ
// 2017.05.12	: プログラム作成
// author		: SyunMizuno

#pragma once

#include	"../Base/IResource.h"
#include	"Pmd/Pmd.h"
#include	<vector>


namespace MSLib {

	class Mesh : public	IResource {
	public:
		typedef enum {
			CHECK_ALL = 0,
			CHECK_ALPHA,
			CHECK_NOALPHA,
		} _eAlphaCheck;

	private:
		struct SimpleVertex {
			Point3 Pos;
			Vector3 Normal;
			Vector2 Tex;
		};

		Pmd*	m_pMeshData;
		SimpleVertex* m_pVertex;
		ID3D11Buffer* m_pVertexBuffer;
		std::vector<ID3D11Buffer*> m_vecIndexBuffer;

	public:
		Mesh();
		virtual ~Mesh();

		bool Create(const std::string& name) override;
		void Delete() override;

		void Draw(Matrix* mat, _eAlphaCheck type = CHECK_ALL);

	private:
		void LoadTexture(const std::string& fileName);
		bool CreateVertex();
		bool CreateIndex();
		bool CheckAlpha(_eAlphaCheck type, float alpha);
	};

}