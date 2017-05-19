// �J����
// 2016. 4.30	:	�v���O�����쐬
// author		:	SyunMizuno

#pragma once

#include	"../Object/3DObject/Object3D.h"
#include	"../Convert/Convert.h"


namespace MSLib {

	class Camera : public	Object3D {
	protected:
		// �r���[�֌W
		Matrix	m_matView;		// 
		float	m_fLookLength;	// �����_�܂ł̋���

		// �v���W�F�N�V�����֌W
		Matrix	m_matProj;		// �v���W�F�N�V����
		float	m_fFovy;		// ����p
		float	m_fAspect;		// �A�X�y�N�g��
		float	m_fNear;		// �O���N���b�v
		float	m_fFar;			// ����N���b�v

	public:
		/* �R���X�g���N�^ */
		Camera();

		/* �f�X�g���N�^ */
		virtual ~Camera();

		/* �J�����̐ݒ� */
		void Set();

		/* �����_�̋�����ݒ�
		// len	: �ݒ肷�钷��
		*/
		void SetLookLength(float len);
		void AddLookLength(float len);

		/* �r���[�s��̎擾 */
		Matrix GetView() const;

		/* �v���W�F�N�V�����s��̎擾 */
		Matrix GetProj() const;

		/* ����p�̐ݒ�
		// Fovy	: �ݒ肵��������p
		*/
		void SetFovy(float fovy);

		/* �A�X�y�N�g��̐ݒ�
		// Aspect	: �ݒ肵�����A�X�y�N�g��̐ݒ�
		*/
		void SetAspect(float aspect);

		/* �j�A�N���b�v�̐ݒ�
		// Near	: �ݒ肵�����j�A�N���b�v
		*/
		void SetNear(float Near);

		/* �t�@�[�N���b�v�̐ݒ�
		// Far	: �ݒ肵�����t�@�[�N���b�v
		*/
		void SetFar(float Far);
	};

};