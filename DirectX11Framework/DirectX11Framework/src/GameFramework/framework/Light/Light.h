// ���C�g�N���X
// 2016. 5. 5	:	�v���O�����쐬
// author		:	SyunMizuno


#pragma once


#include	"../Convert/Convert.h"
#include	"../Object/3DObject/Object3D.h"





class Light	:	public	Object3D {
public:
	typedef enum _eLIGHT_COLOR {
		LIGHT_DIFFUSE,
		LIGHT_AMBIENT,
		LIGHT_SPECULAR,
	} LIGHT_COLOR;

protected:
#pragma region variable

	float	m_fLookLength;
	Matrix	m_mtxView;
	Matrix	m_mtxProj;
	float	m_fFovy;		// ����p
	float	m_fAspect;		// ����p
	float	m_fNear;		// �O���N���b�v
	float	m_fFar;			// ����N���b�v

	Color	m_Diffuse;		// �g�U���ˌ�
	Color	m_Ambient;		// ����
	Color	m_Specular;		// ���ʔ��ˌ�

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
	void SetColor(LIGHT_COLOR type, float r, float g, float b, float a);
	void SetColor(LIGHT_COLOR type, float col);
	void SetColor(LIGHT_COLOR type, const Color& col);

	/* �����x�N�g���̎擾 */
	Vector3 GetDirection3();
	Vector4 GetDirection4();

	/* �r���[�s��̎擾 */
	Matrix GetView() const;

	/* �v���W�F�N�V�����s��̎擾 */
	Matrix GetProj() const;

	/* ���C�g�̐F�̎擾 */
	Color GetColor(LIGHT_COLOR type) const;
};