// �|���S���I�u�W�F�N�g
// 2017.05.15	: �v���O�����쐬
// author		: SyunMizuno

#include	"Quad.h"
#include	"../../../Debug/Debug.h"


Quad::Quad() :
	m_pPolygon(nullptr)
{
	m_pPolygon = new QuadPolygon;
	if (!m_pPolygon->Create())
		Debug::LogError("�|���S���̍쐬�Ɏ��s���܂���");
}

Quad::~Quad() {
	SAFE_DELETE(m_pPolygon);
}

void Quad::Init() {
	Object3D::Init();
}

void Quad::Update() {
	Object3D::Update();
}

void Quad::LateUpdate() {
	Object3D::LateUpdate();
}

void Quad::Draw() {
	Object3D::Draw();
}

void Quad::LateDraw() {
	Object3D::LateDraw();

	m_pPolygon->Draw(&m_pTransform->GetWorld());
}

QuadPolygon* Quad::GetPolygon() const {
	return m_pPolygon;
}