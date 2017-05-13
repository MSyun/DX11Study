// メッシュ
// 2017.05.12	: プログラム作成
// author		: SyunMizuno


#pragma once

#include	"../Base/IResource.h"
#include	"Pmd/Pmd.h"

// 緊急の一時的
#include	"../../Camera/Camera.h"
#include	"../../Light/Light.h"


class Mesh	:	public	IResource {
private:
	struct SimpleVertex {
		Point3 Pos;
		Vector3 Normal;
		Vector2 Tex;
	};


	Pmd*	m_pMeshData;
	SimpleVertex* m_pVertex;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;

	ID3D11Buffer*		m_pConstantBuffer;

public:
	Mesh();
	virtual ~Mesh();

	bool Create(const string fileName) override;
	void Delete() override;

	void Draw(Camera* camera, Light* light);

private:
	void LoadTexture(const string& fileName);
};