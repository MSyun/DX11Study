// �I�u�W�F�N�g3D�N���X
// 2016. 5. 1	�v���O�����쐬
// Author		SyunMizuno



#include	"Object3D.h"
#include	"../../Utility/System/SystemUtility.h"



/*									//
//			�R���X�g���N�^			//
//									*/
Object3D::Object3D() :
	m_pTransform(NULL)
{
	m_pTransform = new Transform(this);
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

	vector<Transform*>* childs = m_pTransform->GetChilds();
	for (auto it = childs->begin(); it != childs->end(); ++it) {
		(*it)->GetGameObject()->DrawAll();
	}
}
void Object3D::LateDrawAll() {
	if (!GetActive())	return;

	LateDraw();

	vector<Transform*>* childs = m_pTransform->GetChilds();
	for (auto it = childs->begin(); it != childs->end(); ++it) {
		(*it)->GetGameObject()->LateDrawAll();
	}
}


/*									//
//				�폜�ʒm			//
//									*/
void Object3D::Destroy() {
	Object::Destroy();
	m_pTransform->Destroy();
}