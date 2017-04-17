#include	"MathUtility.h"



// [min, max]�͈͓̔��܂�n���N�����v
float Clamp(float val, float min, float max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}
int Clamp(int val, int min, int max) {
	if (val < min) return min;
	if (val > max) return max;
	return val;
}


// 2�̃x�N�g������AB�̂Ȃ��p�x�Ƃ����߂�
//float AngleOf2Vector(Vector3 A, Vector3 B) {
//	// ���x�N�g���̒�����0���Ɠ������o�Ȃ��̂Œ���
//
//	// �x�N�g��A��B�̒������v�Z����
//	float length_A = D3DXVec3Length(&A);
//	float length_B = D3DXVec3Length(&B);
//
//	// ���ςƃx�N�g���������g����cos�Ƃ����߂�
//	float cos_sita = D3DXVec3Dot(&A, &B) / (length_A * length_B);
//
//	// cos�Ƃ���Ƃ����߂�
//	float sita = acosf(cos_sita);
//
//	// ���W�A������ 0 �` 180 �̊p�x�łق����ꍇ�̓R�����g���O��
//	sita = sita * 180.0f / D3DX_PI;
//
//	return sita;
//}


//////////////////////////////////
 // �ǂ���x�N�g��
 //
 // out : ���K���ǂ���x�N�g���i�߂�l�j
 // front : �i�s�x�N�g��
 // normal: �Փ˓_�ł̖@���x�N�g��
 //
//Vector3* WallScratchVector(
//	const Vector3& front,
//	const Vector3& normal)
//{
//	Vector3 normal_n;
//	Vector3 out;
//	D3DXVec3Normalize(&normal_n, &normal);
//	return D3DXVec3Normalize(&out, &(front - D3DXVec3Dot(&front, &normal_n) * normal_n));
//}

// �x�W�G�Ȑ�
Vector2 Bezier(
	Vector2& p0,
	Vector2& p1,
	Vector2& p2,
	Vector2& p3,
	float t)
{
	Vector2 point;
	float rt1 = (1 - t);
	float rt2 = rt1 * rt1;
	float t2 = t * t;
	float a, b, c, d;
	a = rt1 * rt2;
	b = 3.0f * rt2 * t;
	c = 3.0f * rt1 * t2;
	d = t * t2;
	point.x =
		a * p0.x +
		b * p1.x +
		c * p2.x +
		d * p3.x;
	point.y =
		a * p0.y +
		b * p1.y +
		c * p2.y +
		d * p3.y;
	return point;
}

// Catmull-Rom�X�v���C���Ȑ�
//Vector3 CatmullRom(
//	Vector3& p0,
//	Vector3& p1,
//	Vector3& p2,
//	Vector3& p3,
//	float t)		// 0.0f �` 1.0f
//{
//	// ����
//	Vector3	v0 = 0.5f * (p2 - p0);
//	Vector3	v1 = 0.5f * (p3 - p1);
//	float	t2 = t * t;
//	float	t3 = t2 * t;
//	return	((p1 - p2)*2.0f + v0 + v1) * t3 +
//		((p2 - p1)*3.0f - 2.0f*v0 - v1) * t2 +
//		v0 * t + p1;
//}