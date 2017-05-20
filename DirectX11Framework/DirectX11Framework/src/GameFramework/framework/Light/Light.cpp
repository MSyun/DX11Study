// ���C�g�N���X
// 2016. 5. 5	:	�v���O�����쐬
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
	//				�ݒ�				//
	//									*/
	void Light::Set() {
		CreateView();
		CreateProj();
	}


	/*									//
	//			�r���[�s��쐬			//
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
	//		�v���W�F�N�V�����s��쐬	//
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
	//		�����_�܂ł̋�����ݒ�		//
	//									*/
	void Light::SetLookLength(const float _len) {
		m_fLookLength = _len;
	}


	/*									//
	//			����p��ݒ�			//
	//									*/
	void Light::SetFovy(const float _fovy) {
		m_fFovy = _fovy;
	}


	/*									//
	//			�A�X�y�N�g���ݒ�		//
	//									*/
	void Light::SetAspect(const float _aspect) {
		m_fAspect = _aspect;
	}


	/*									//
	//			�O���N���b�v��ݒ�		//
	//									*/
	void Light::SetNear(const float _near) {
		m_fNear = _near;
	}


	/*									//
	//			����N���b�v��ݒ�		//
	//									*/
	void Light::SetFar(const float _far) {
		m_fFar = _far;
	}


	/*									//
	//				�F��ݒ�			//
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
	//		�����_�܂ł̃x�N�g��		//
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
	//			�r���[�s����擾		//
	//									*/
	Matrix Light::GetView() const {
		return m_mtxView;
	}


	/*									//
	//	�v���W�F�N�V�����s����擾		//
	//									*/
	Matrix Light::GetProj() const {
		return m_mtxProj;
	}


	/*									//
	//				�F���擾			//
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