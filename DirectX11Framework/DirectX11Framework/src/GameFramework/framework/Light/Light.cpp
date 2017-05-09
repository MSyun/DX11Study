// ライトクラス
// 2016. 5. 5	:	プログラム作成
// author		:	SyunMizuno


#include	"Light.h"
#include	"../Screen/Screen.h"




/*									//
//			コンストラクタ			//
//									*/
Light::Light() :
	m_fLookLength(10.0f),
	m_fFovy(60.0f),
	m_fAspect((float)Screen::GetWidth() / (float)Screen::GetHeight()),
	m_fNear(1.0f),
	m_fFar(10.0f),
	m_vColor(1.0f, 1.0f, 1.0f, 1.0f)
{
	MatrixIdentity(&m_mtxView);
	MatrixIdentity(&m_mtxProj);

	SetName("Light");
	Transform* trans = GetTransform();
	trans->SetPos(0.0f, 10.0f, 0.0f);
	trans->Rotate(0.0f, -90.0f, 0.0f);
}


/*									//
//			デストラクタ			//
//									*/
Light::~Light() {

}


/*									//
//				設定				//
//									*/
void Light::Set() {
	CreateView();
	CreateProj();
}


/*									//
//			ビュー行列作成			//
//									*/
void Light::CreateView() {
	Transform* trans = GetTransform();
	Point3 pos = trans->GetPos();
	MatrixLookAtLH(
		&m_mtxView,
		&pos,
		&(pos + GetDirection3()),
		&trans->GetUp());
}


/*									//
//		プロジェクション行列作成	//
//									*/
void Light::CreateProj() {
	MatrixPerspectiveFovLH(
		&m_mtxProj,
		ToRadian(m_fFovy),
		m_fAspect,
		m_fNear,
		m_fFar);
}


/*									//
//		注視点までの距離を設定		//
//									*/
void Light::SetLookLength(const float _len) {
	m_fLookLength = _len;
}


/*									//
//			視野角を設定			//
//									*/
void Light::SetFovy(const float _fovy) {
	m_fFovy = _fovy;
}


/*									//
//			アスペクト比を設定		//
//									*/
void Light::SetAspect(const float _aspect) {
	m_fAspect = _aspect;
}


/*									//
//			前方クリップを設定		//
//									*/
void Light::SetNear(const float _near) {
	m_fNear = _near;
}


/*									//
//			後方クリップを設定		//
//									*/
void Light::SetFar(const float _far) {
	m_fFar = _far;
}


/*									//
//				色を設定			//
//									*/
void Light::SetColor(float r, float g, float b, float a) {
	m_vColor.r = r;
	m_vColor.g = g;
	m_vColor.b = b;
	m_vColor.a = a;
}

void Light::SetColor(float col) {
	m_vColor.r = col;
	m_vColor.g = col;
	m_vColor.b = col;
}

void Light::SetColor(const Color& col) {
	m_vColor = col;
}


/*									//
//		注視点までのベクトル		//
//									*/
Vector3 Light::GetDirection3() {
	return GetTransform()->GetForward() * m_fLookLength;
}

Vector4 Light::GetDirection4() {
	Vector3 forward = GetDirection3();
	return Vector4(
		forward.x,
		forward.y,
		forward.z,
		1.0f);
}


/*									//
//			ビュー行列を取得		//
//									*/
Matrix Light::GetView() const {
	return m_mtxView;
}


/*									//
//	プロジェクション行列を取得		//
//									*/
Matrix Light::GetProj() const {
	return m_mtxProj;
}


/*									//
//				色を取得			//
//									*/
Color Light::GetColor() const {
	return m_vColor;
}