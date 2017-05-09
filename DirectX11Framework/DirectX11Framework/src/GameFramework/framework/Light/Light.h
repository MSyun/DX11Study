// ���C�g�N���X
// 2016. 5. 5	:	�v���O�����쐬
// author		:	SyunMizuno


#pragma once


#include	"../Convert/Convert.h"
#include	"../Object/3DObject/Object3D.h"


class Light	:	public	Object3D {
protected:
#pragma region variable

	float	m_fLookLength;
	Matrix	m_mtxView;
	Matrix	m_mtxProj;
	float	m_fFovy;		// ����p
	float	m_fAspect;		// ����p
	float	m_fNear;		// �O���N���b�v
	float	m_fFar;			// ����N���b�v

	Color	m_vColor;		// ���C�g�̐F

#pragma endregion

public:
	Light();
	virtual ~Light();

	/* �r���[�s��쐬 */
	void CreateView();

	/* �v���W�F�N�V�����s��쐬 */
	void CreateProj();

	/* �ݒ� */
	void Set();

	/* �����_�܂ł̋�����ݒ�
	// _len	; ����
	*/
	void SetLookLength(const float _len);

	/* ����p�̐ݒ�
	// _fovy	: ����p
	*/
	void SetFovy(const float _fovy);

	/* �A�X�y�N�g��̐ݒ�
	// _aspect	; �A�X�y�N�g��
	*/
	void SetAspect(const float _aspect);

	/* �O���N���b�v�̐ݒ�
	// _near	: �O���N���b�v
	*/
	void SetNear(const float _near);

	/* ����N���b�v�̐ݒ�
	// _far	: ����N���b�v
	*/
	void SetFar(const float _far);

	/* ���C�g�̐F�̐ݒ�
	*/
	void SetColor(float r, float g, float b, float a);
	void SetColor(float col);
	void SetColor(const Color& col);

	/* �����x�N�g���̎擾 */
	Vector3 GetDirection3();
	Vector4 GetDirection4();

	/* �r���[�s��̎擾 */
	Matrix GetView() const;

	/* �v���W�F�N�V�����s��̎擾 */
	Matrix GetProj() const;

	/* ���C�g�̐F�̎擾 */
	Color GetColor() const;
};