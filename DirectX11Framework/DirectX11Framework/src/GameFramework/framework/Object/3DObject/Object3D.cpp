// オブジェクト3Dクラス
// 2016. 5. 1	プログラム作成
// Author		SyunMizuno



#include	"Object3D.h"
#include	"../../Utility/System/SystemUtility.h"



/*									//
//			コンストラクタ			//
//									*/
Object3D::Object3D() :
	m_pTransform(NULL)
{
	m_pTransform = new Transform(this);
}


/*									//
//			デストラクタ			//
//									*/
Object3D::~Object3D() {
	SAFE_DELETE(m_pTransform);
}


/*									//
//				全更新				//
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
//				全描画				//
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
//				削除通知			//
//									*/
void Object3D::Destroy() {
	Object::Destroy();
	m_pTransform->Destroy();
}