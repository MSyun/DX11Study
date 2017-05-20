// ライトクラス
// 2016. 5. 5	:	プログラム作成
// author		:	SyunMizuno


#include	"Light.h"
#include	"../Screen/Screen.h"

#include	"Manager/LightManager.h"

namespace MSLib {

	Light::Light() :
		m_fLookLength(10.0f),
		m_fFovy(60.0f),
		m_fAspect((float)Screen::GetWidth() / (float)Screen::GetHeight()),
		m_fNear(1.0f),
		m_fFar(10.0f),
		m_Diffuse(1.0f, 1.0f, 1.0f, 1.0f),
		m_Ambient(1.0f, 1.0f, 1.0f, 1.0f),
		m_Specular(1.0f, 1.0f, 1.0f, 1.0f)
	{
		GetLightManager()->Add(this);

		MatrixIdentity(&m_mtxView);
		MatrixIdentity(&m_mtxProj);

		SetName("Light");
		Transform* trans = GetTransform();
		trans->SetPos(0.0f, 10.0f, 0.0f);
		trans->Rotate(0.0f, -90.0f, 0.0f);
	}

	Light::~Light() {
		GetLightManager()->Delete(this);
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
	void Light::SetColor(LIGHT_COLOR type, float r, float g, float b, float a) {
		switch (type) {
		case LIGHT_COLOR::LIGHT_DIFFUSE:
			m_Diffuse.r = r;
			m_Diffuse.g = g;
			m_Diffuse.b = b;
			m_Diffuse.a = a;
			break;

		case LIGHT_COLOR::LIGHT_AMBIENT:
			m_Ambient.r = r;
			m_Ambient.g = g;
			m_Ambient.b = b;
			m_Ambient.a = a;
			break;

		case LIGHT_COLOR::LIGHT_SPECULAR:
			m_Specular.r = r;
			m_Specular.g = g;
			m_Specular.b = b;
			m_Specular.a = a;
			break;
		}
	}

	void Light::SetColor(LIGHT_COLOR type, float col) {
		switch (type) {
		case LIGHT_COLOR::LIGHT_DIFFUSE:
			m_Diffuse.r = col;
			m_Diffuse.g = col;
			m_Diffuse.b = col;
			break;

		case LIGHT_COLOR::LIGHT_AMBIENT:
			m_Ambient.r = col;
			m_Ambient.g = col;
			m_Ambient.b = col;
			break;

		case LIGHT_COLOR::LIGHT_SPECULAR:
			m_Specular.r = col;
			m_Specular.g = col;
			m_Specular.b = col;
			break;
		}
	}

	void Light::SetColor(LIGHT_COLOR type, const Color& col) {
		switch (type) {
		case LIGHT_COLOR::LIGHT_DIFFUSE:
			m_Diffuse = col;
			break;

		case LIGHT_COLOR::LIGHT_AMBIENT:
			m_Ambient = col;
			break;

		case LIGHT_COLOR::LIGHT_SPECULAR:
			m_Specular = col;
			break;
		}
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
	Color Light::GetColor(LIGHT_COLOR type) const {
		Color col;
		switch (type) {
		case LIGHT_COLOR::LIGHT_DIFFUSE:
			return m_Diffuse;

		case LIGHT_COLOR::LIGHT_AMBIENT:
			return m_Ambient;

		case LIGHT_COLOR::LIGHT_SPECULAR:
			return m_Specular;
		}
		return col;
	}

};