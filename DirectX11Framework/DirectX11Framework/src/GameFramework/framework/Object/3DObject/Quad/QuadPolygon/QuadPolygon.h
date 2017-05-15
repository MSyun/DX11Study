// �|���S�����b�V��
// 2017.05.15	: �v���O�����쐬
// author		: SyunMizuno


#pragma once


#include	"../../../../Resource/Texture/Texture.h"
#include	"../../../../Convert/Convert.h"


class QuadPolygon {
private:
	ID3D11Buffer*	m_pVertexBuffer;
	Texture*		m_pTexture;

public:
	QuadPolygon();
	virtual ~QuadPolygon();

	bool Create();

	void Delete();

	void Draw(Matrix* world);

	void SetTexture(Texture* tex);
};