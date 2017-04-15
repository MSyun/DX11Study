//	�v�Z�n�֗̕�
// 2016. 9. 5	�v���O�����쐬
// 2016. 9.15	�ǐ���ʒu�␳�ǉ�
// 2017. 2.20	�x�W�G�Ȑ��ǉ�
// Author		SyunMizuno

#pragma once

#include	"../../Convert/Convert.h"


// [min, max]�͈͓̔��܂�n���N�����v
float Clamp(float val, float min, float max);
int Clamp(int val, int min, int max);


// 2�̃x�N�g������AB�̂Ȃ��p�x�Ƃ����߂�
float AngleOf2Vector(Vector3 A, Vector3 B);


// �ǒނ�x�N�g���Z�o
//Vector3* WallScratchVector(
//	const Vector3& front,
//	const Vector3& normal);

/*	�x�W�G�Ȑ�
//	p0	: point1
//	p1	: point2
//	p2	: point3
//	p3	: point4
//	t	: 0.0f �` 1.0f
*/
Vector2 Bezier(
	Vector2& p0,
	Vector2& p1,
	Vector2& p2,
	Vector2& p3,
	float t);

/*	Catmull-Rom�X�v���C���Ȑ�
//	p0	: point1
//	p1	: point2
//	p2	: point3
//	p3	: point4
//	t	: 0.0f �` 1.0f
*/
Vector3 CatmullRom(
	Vector3& p0,
	Vector3& p1,
	Vector3& p2,
	Vector3& p3,
	float t);