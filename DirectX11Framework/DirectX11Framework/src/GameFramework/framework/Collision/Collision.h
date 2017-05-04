//	�����蔻��
// 2016. 5.17	�v���O�����쐬
// 2016. 7. 9	AABB�ǉ�
// Author		SyunMizuno

#pragma once


#include	"../Convert/Convert.h"


//#define	DefaultColor	Color(0, 255, 255, 255)
const Color DefaultColor = Color(0.0f, 255.0f, 255.0f, 255.0f);


/*
	MEMO	:
			���W�덷	�F	�ŏ��Ɍ덷��o�^���邱�Ƃŏ�Ɍ덷�𔽉f���Ă����
*/

#pragma region Type

// ��
struct Sphere {
	Point3	p;		// ���W
	Point3	p_d;	// ���W�덷
	float	r;		// ���a
	Sphere() : p(0.0f, 0.0f, 0.0f), p_d(0.0f, 0.0f, 0.0f), r(1.0f) {}
};

// AABB
struct Aabb {
	Point3	p;		// ���W
	Point3	p_d;	// ���W�덷
	float	r[3];	// ���a
	Aabb() : p(0.0f, 0.0f, 0.0f), p_d(0.0f, 0.0f, 0.0f) {}
};

// OBB
struct Obb {
	Point3	p;			// ���W
	Point3	p_d;		// ���W�덷
	Vector3	axis[3];	// ���[�J���x�N�g��
	float	r[3];		// ���a
	Obb() : p(0.0f, 0.0f, 0.0f), p_d(0.0f, 0.0f, 0.0f) {}
};

typedef enum {
	X_AXIS = 0,
	Y_AXIS,
	Z_AXIS,
} _AXIS;

// �J�v�Z��
struct Capsule {
	Point3	p;		// ���W
	Point3	p_d;	// ���W�덷
	float	r;		// ���a
	float	h;		// ����
	Point3	a;		// ���ԕ��̐����̊J�n�_
	Point3	b;		// ���ԕ��̐����̏I���_
	_AXIS	Direction;	// ����
	Vector3	axis[3];
	Capsule() : a(0.0f, 0.0f, 0.0f), b(0.0f, 0.0f, 0.0f),
		p(0.0f, 0.0f, 0.0f), p_d(0.0f, 0.0f, 0.0f),
		r(1.0f), h(3.0f),
		Direction(Y_AXIS) {}
};

// �Ђ��`
struct Lozenge {
	Point3	p;			// ���_
	Point3	p_d;		// ���W�덷
	Vector3	axis[2];	// �����`��2�̎��ƂȂ��
	float	r;			// ���a
};

#pragma endregion


#pragma region Update

void UpdateCollision(Sphere& sphere, Matrix& world);
void UpdateCollision(Aabb& aabb, Matrix& world);
void UpdateCollision(Obb& obb, Matrix& world);
void UpdateCollision(Capsule& capsule, Matrix& world);

#pragma endregion


#pragma region Check

// �� vs ��
bool CheckCollision(Sphere& sphere1, Sphere& sphere2);
// AABB vs AABB
bool CheckCollision(Aabb& aabb1, Aabb& aabb2);
// OBB vs OBB
bool CheckCollision(Obb& obb1, Obb& obb2);
// �� vs �J�v�Z��
bool CheckCollision(Sphere& sphere, Capsule& capsule);
bool CheckCollision(Capsule& capsule, Sphere& sphere);
// �� vs AABB
bool CheckCollision(Sphere& sphere, Aabb& aabb, Point3& p);
bool CheckCollision(Sphere& sphere, Aabb& aabb);
bool CheckCollision(Aabb& aabb, Sphere& sphere);
// �� vs OBB
bool CheckCollision(Sphere& sphere, Obb& obb, Point3& p);
bool CheckCollision(Sphere& sphere, Obb& obb);
bool CheckCollision(Obb& obb, Sphere& sphere);
// �J�v�Z�� vs �J�v�Z��
bool CheckCollision(Capsule& capsule1, Capsule& capsule2);

#pragma endregion


#pragma region Draw

void DrawCollision(Sphere& sphere, const Color& Color = DefaultColor);
void DrawCollision(Aabb& aabb, const Color& Color = DefaultColor);
void DrawCollision(Obb& obb, const Color& Color = DefaultColor);
void DrawCollision(Capsule& capsule, const Color& Color = DefaultColor);

#pragma endregion

//	�������̐������瓊�e���������Z�o
float LenSegOnSeparateAxis(
	Vector3 *Sep,
	Vector3 *e1,
	Vector3 *e2,
	Vector3 *e3 = 0);
// �_c�Ɛ���ab�̊Ԃ̋����̕�����Ԃ�
float SqDistPointSegment(Point3& a, Point3& b, Point3& c);
// �_p��AABB b�̊Ԃ̋����̕�����Ԃ�
float SqDistPointAABB(Point3& p, Aabb& b);
// �_p��OBB b�̊Ԃ̋����̕�����Ԃ�
float SqDistPointOBB(Point3& p, Obb& b);
// 2�̐����̍ŋߐړ_
float ClosestPtSegmentSegment(
	Point3& p1, Point3& q1,
	Point3& p2, Point3& q2,
	float& s, float& t,
	Point3& c1, Point3& c2);
// ����ab����ѓ_c�ɑ΂��āAab��̍ŋߐړ_d��Ԃ�
void ClosestPtPointSegment(Point3 c, Point3 a, Point3 b, float& t, Point3& d);
// �_p�ɑ΂��āAAABB b�̏�������͒��ɂ���p�̍ŋߐړ_q��Ԃ�
void ClosestPtPointAABB(Point3& p, Aabb& b, Point3& q);
// �_p�ɑ΂��āAOBB b�̏�������͒��ɂ���p�̍ŋߐړ_q��Ԃ�
void ClosestPtPointOBB(Point3& p, Obb& b, Point3& q);


void ChangeDrawCollider();