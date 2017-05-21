// カメラ
// 2016. 4.30	:	プログラム作成
// author		:	SyunMizuno


#include	"Camera.h"
#include	"../Screen/Screen.h"

#include	"Manager/CameraManager.h"

namespace MSLib {

	Camera::Camera() :
		m_fFovy(60.0f),
		m_fAspect((float)Screen::GetWidth() / (float)Screen::GetHeight()),
		m_fNear(1.0f),
		m_fFar(100.0f),
		m_fLookLength(5.0f),
		m_pSky(nullptr)
	{
		GetCameraManager()->Add(this);

		GetTransform()->SetPos(0.0f, 0.0f, -5.0f);
		SetName("Camera");
//		CreateSky();
	}

	Camera::~Camera() {
		GetCameraManager()->Delete(this);
		DeleteSky();
	}

	void Camera::Update() {
		Object3D::Update();

		if (m_pSky)
			m_pSky->GetTransform()->SetPos(GetTransform()->GetPos());
	}


	void Camera::Set() {
		Transform* transform = GetTransform();

		// ビューマトリクスの設定
		MatrixLookAtLH(
			&m_matView,
			&transform->GetPos(),
			&(transform->GetPos() + transform->GetForward() * m_fLookLength),
			&transform->GetUp());

			// プロジェクションマトリクスの設定
		MatrixPerspectiveFovLH(
			&m_matProj,
			ToRadian(m_fFovy),
			m_fAspect,
			m_fNear,
			m_fFar);
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

	void Camera::CreateSky() {
		if (!m_pSky)
			m_pSky = new Skydome;
	}

	void Camera::DeleteSky() {
		SAFE_DELETE(m_pSky);
	}

};