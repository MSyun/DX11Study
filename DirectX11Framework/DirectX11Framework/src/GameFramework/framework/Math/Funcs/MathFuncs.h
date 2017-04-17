// �v�Z�p�֐��Q
// 2016. 4.16	:	�v���O�����쐬
// author		:	SyunMizuno


#pragma once


#include	"../Matrix/Matrix4x4/Matrix4x4.h"
#include	"../Vector/Vector2/Vector2.h"
#include	"../Vector/Vector3/Vector3.h"
#include	"../Vector/Vector4/Vector4.h"



/* ����
// pL	: ���Ӓl
// pR	: �E�Ӓl
*/
float Vec3Dot(const Vector3* pL, const Vector3* pR);

/* �O��
// pOut	: �i�[�����x�N�g��
// pL	: ���Ӓl
// pR	: �E�Ӓl
*/
void Vec3Cross(Vector3* pOut, const Vector3* pL, const Vector3* pR);


/* �P�ʍs��̐���
// pMat	: �������錳�̍s��
*/
void MatrixIdentity(Matrix4x4* pMat);

/* �s��̏�Z
// pMat	: �i�[�������s��
// pL	: ���Ӓl
// pR	: �E�Ӓl
*/
void MatrixMultiply(
	Matrix4x4* pMat,
	const Matrix4x4* pL,
	const Matrix4x4* pR);

/* ���[���hX����]�s�񐶐�
// pMat		: �i�[�������s��
// Angle	: ��]�p�x
*/
void MatrixRotationX(Matrix4x4* pMat, float Angle);

/* ���[���hY����]�s�񐶐�
// pMat		: �i�[�������s��
// Angle	: ��]�p�x
*/
void MatrixRotationY(Matrix4x4* pMat, float Angle);

/* ���[���hZ����]�s�񐶐�
// pMat		: �i�[�������s��
// Angle	: ��]�p�x
*/
void MatrixRotationZ(Matrix4x4* pMat, float Angle);

/* ���[���h3����]�s�񐶐�
// pMat		: �i�[�������s��
// Yaw		: Y����]�p�x
// Pitch	: X����]�p�x
// Roll		: Z����]�p�x
*/
void MatrixRotationYawPitchRoll(
	Matrix4x4* pMat,
	float Yaw,
	float Pitch,
	float Roll);

/* ���[���h�����s�ړ��s�񐶐�
// pMat	: �i�[�������s��
// X	: X���ړ���
// Y	: Y���ړ���
// Z	: Z���ړ���
*/
void MatrixTranslation(Matrix4x4* pMat, float X, float Y, float Z);

/* �g��E�k���s�񐶐�
// pMat	: �i�[�������s��
// X	: X���g�嗦
// Y	: Y���g�嗦
// Z	: Z���g�嗦
*/
void MatrixScaling(Matrix4x4* pMat, float X, float Y, float Z);

/* �]�u�s��̐���
// pOut	: �i�[�������s��
// pM	: �]�u�������s��
*/
void MatrixTranspose(Matrix4x4* pOut, const Matrix4x4* pM);

/* ������W�n�r���[�s��쐬
// pOut	: �i�[�������s��
// pEye	: ���_
// pAt	: �J�����̒����_
// pUp	: �����
*/
void MatrixLookAtLH(
	Matrix4x4* pOut,
	const Vector3* pEye,
	const Vector3* pAt,
	const Vector3* pUp);

/* �E����W�n�r���[�s��쐬
// pOut	: �i�[�������s��
// pEye	: ���_
// pAt	: �J�����̒����_
// pUp	: �����
*/
void MatrixLookAtRH(
	Matrix4x4* pOut,
	const Vector3* pEye,
	const Vector3* pAt,
	const Vector3* pUp);

/* ������W�n�p�[�X�y�N�e�B�u�s��쐬
// pOut		: ���Z���ʂ̍s��
// fovY		: y�����ւ̎���i���W�A���P�ʁj
// Aspect	: �A�X�y�N�g��
// zn		: �j�A�N���b�v
// zf		: �t�@�[�N���b�v
*/
void MatrixPerspectiveFovLH(
	Matrix4x4* pOut,
	float fovY,
	float Aspect,
	float zn,
	float zf);

/* �C�ӎ���]�s�񐶐�
// pMat		: �i�[�������s��
// pV		: �C�ӂ̎�
// Angle	: ��]�p�x
*/
void MatrixRotationAxis(
	Matrix4x4* pMat,
	Vector3* pV,
	float Angle);
