// カメラ
// 2016. 4.30	:	プログラム作成
// author		:	SyunMizuno


#include	"Camera.h"
#include	"../Screen/Screen.h"


namespace MSLib {

	Camera::Camera() :
		m_fFovy(60.0f),
		m_fAspect((float)Screen::GetWidth() / (float)Screen::GetHeight()),
		m_fNear(1.0f),
		m_fFar(100.0f),
		m_fLookLength(5.0f)
	{
		GetTransform()->SetPos(0.0f, 0.0f, -5.0f);
		SetName("Camera");
	}

	Camera::~Camera() {

	}


	void Camera::Set() {
		Transform* transform = GetTransform();

		// ビューマトリクスの設定
		MatrixLookAtLH(
			&m_matView,
			&transform->GetPos(),
			&(transform->GetPos() + transform->GetForward() * m_fLookLength),
			&transform->GetUp());
		//	GetGraphics()->SetView(m_matView);

			// プロジェクションマトリクスの設定
		MatrixPerspectiveFovLH(
			&m_matProj,
			ToRadian(m_fFovy),
			m_fAspect,
			m_fNear,
			m_fFar);
		//	GetGraphics()->SetProjection(m_matProj);
	}

	void Camera::SetLookLength(float len) {
		m_fLookLength = len;
	}

	void Camera::AddLookLength(float len) {
		m_fLookLength += len;
	}

	Matrix Camera::GetView() const {
		return m_matView;
	}

	Matrix Camera::GetProj() const {
		return m_matProj;
	}

	void Camera::SetFovy(float fovy) {
		m_fFovy = fovy;
	}

	void Camera::SetAspect(float aspect) {
		m_fAspect = aspect;
	}

	void Camera::SetNear(float Near) {
		m_fNear = Near;
	}

	void Camera::SetFar(float Far) {
		m_fFar = Far;
	}

};