// 板ポリゴンメッシュ
// 2017.05.15	: プログラム作成
// author		: SyunMizuno

#pragma once


#include	"../../../../Resource/Texture/Texture.h"
#include	"../../../../Convert/Convert.h"

namespace MSLib {

	class QuadPolygon {
	private:
		ID3D11Buffer*	m_pVertexBuffer;
		Texture*		m_pTexture;

		Vector3 m_Diffuse;
		float m_Alpha;
		Vector3 m_Ambient;
		Vector3 m_Emissive;
		Vector3 m_Specular;
		float m_Shininess;

	public:
		QuadPolygon();
		virtual ~QuadPolygon();

		bool Create();

		void Delete();

		void Draw(Matrix* world);

		void SetTexture(Texture* tex);
	};

};