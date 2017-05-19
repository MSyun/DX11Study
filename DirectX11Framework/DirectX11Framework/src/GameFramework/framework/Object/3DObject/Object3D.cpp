// �I�u�W�F�N�g3D�N���X
// 2016. 5. 1	�v���O�����쐬
// Author		SyunMizuno



#include	"Object3D.h"
#include	"../../Utility/System/SystemUtility.h"
#include	"Manager/Object3DManager.h"

namespace MSLib {

	/*									//
	//			�R���X�g���N�^			//
	//									*/
	Object3D::Object3D() :
		m_pTransform(nullptr),
		m_pMesh(nullptr)
	{
		m_pTransform = new Transform(this);
		GetObject3DManager()->Add(this);
	}


	/*									//
	//			�f�X�g���N�^			//
	//									*/
	Object3D::~Object3D() {
		SAFE_DELETE(m_pTransform);
	}


	/*									//
	//				�S�X�V				//
	//									*/
	void Object3D::UpdateAll() {
		if (!GetActive())
			return;

		Object::UpdateAll();
		if (GetOperate())
			Input();
		Update();

		vector<Transform*>* childs = m_pTransform->GetChilds();
		for (auto it = childs->begin(); it != childs->end(); ++it) {
			(*it)->GetGameObject()->UpdateAll();
		}
	}
	void Object3D::LateUpdateAll() {
		if (!GetActive())
			return;

		LateUpdate();

		vector<Transform*>* childs = m_pTransform->GetChilds();
		for (auto it = childs->begin(); it != childs->end(); ++it) {
			(*it)->GetGameObject()->LateUpdateAll();
		}
	}


	/*									//
	//				�S�`��				//
	//									*/
	void Object3D::DrawAll() {
		if (!GetActive())	return;

		Draw();
		if (m_pMesh)		m_pMesh->Draw(&m_pTransform->GetWorld(), Mesh::CHECK_NOALPHA);

		vector<Transform*>* childs = m_pTransform->GetChilds();
		for (auto it = childs->begin(); it != childs->end(); ++it) {
			(*it)->GetGameObject()->DrawAll();
		}
	}
	void Object3D::LateDrawAll() {
		if (!GetActive())	return;

		LateDraw();
		if (m_pMesh)		m_pMesh->Draw(&m_pTransform->GetWorld(), Mesh::CHECK_ALPHA);

		vector<Transform*>* childs = m_pTransform->GetChilds();
		for (auto it = childs->begin(); it != childs->end(); ++it) {
			(*it)->GetGameObject()->LateDrawAll();
		}
	}


#pragma region Mesh
	void Object3D::CreateMesh(string name) {
		DeleteMesh();
		shared_ptr<Mesh> ptr(new Mesh);

		ptr->Create(name);
		m_pMesh = ptr;
	}
	void Object3D::DeleteMesh() {
		m_pMesh.reset();
	}
	void Object3D::SetModel(shared_ptr<Mesh> mesh) {
		m_pMesh = mesh;
	}
#pragma endregion


	/*									//
	//				�폜�ʒm			//
	//									*/
	void Object3D::Destroy() {
		Object::Destroy();
		m_pTransform->Destroy();
	}

};