// ���b�V��
// 2017.05.12	: �v���O�����쐬
// author		: SyunMizuno


#pragma once

#include	"../Base/IResource.h"
#include	"Pmd/Pmd.h"

// �ً}�̈ꎞ�I
#include	"../../Camera/Camera.h"
#include	"../../Light/Light.h"
#include	"../Shader/Base/Shader.h"


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

public:
	Mesh();
	virtual ~Mesh();

	bool Create(const string fileName) override;
	void Delete() override;

	// ��ł����̋@�\���O��
	void Draw(Camera* camera, Light* light, Shader* shader);

private:
	void LoadTexture(const string& fileName);
	bool CreateVertex();
	bool CreateIndex();
};