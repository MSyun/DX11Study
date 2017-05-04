//	�R���C�_�[
// 2016. 5.17	�v���O�����쐬
// Author		SyunMizuno



#include	"Collision.h"
#include	<math.h>
#include	"../Utility/Math/MathUtility.h"
#include	"../Graphic/Graphics.h"

/*
	memo	:
			
*/

static bool bDraw = false;


struct VERTEX_XYZ_COL{
	FLOAT x, y, z;
	Color color;
};


#define FVF_XYZ_COLOR		( D3DFVF_XYZ | D3DFVF_DIFFUSE )


void ChangeDrawCollider() {
	bDraw ^= true;
}



/*									//
//					�X�V			//
//									*/
// ��
void UpdateCollision(Sphere& sphere, Matrix& world) {
	sphere.p = Point3(world._41, world._42, world._43);
	for (int i = 0; i < 3; i ++) {
		Vector3 axis = world.m[i];
		Vec3Normalize(&axis, &axis);
		sphere.p += axis * sphere.p_d.e[i];
	}
}
// AABB
void UpdateCollision(Aabb& aabb, Matrix& world) {
	aabb.p = Point3(world._41, world._42, world._43);
	for (int i = 0; i < 3; i ++) {
		Vector3 axis = world.m[i];
		Vec3Normalize(&axis, &axis);
		aabb.p += axis * aabb.p_d.e[i];
	}
}
// OBB
void UpdateCollision(Obb& obb, Matrix& world) {
	obb.axis[0] = Vector3(world._11, world._12, world._13);
	obb.axis[1] = Vector3(world._21, world._22, world._23);
	obb.axis[2] = Vector3(world._31, world._32, world._33);
	obb.p = Point3(world._41, world._42, world._43);

	for (int i = 0; i < 3; i ++) {
		Vec3Normalize(&obb.axis[i], &obb.axis[i]);
		obb.p += obb.axis[i] * obb.p_d.e[i];
	}
}
// �J�v�Z��
void UpdateCollision(Capsule& capsule, Matrix& world) {
	capsule.p = Point3(world._41, world._42, world._43);

	for (int i = 0; i < 3; i ++) {
		capsule.axis[i] = Vector3(world.m[i][0], world.m[i][1], world.m[i][2]);
		Vec3Normalize(&capsule.axis[i], &capsule.axis[i]);
	}

	// �����̒[���쐬
	capsule.a = capsule.axis[capsule.Direction] * (capsule.h / 2.0f);
	capsule.b = -capsule.axis[capsule.Direction] * (capsule.h / 2.0f);

	capsule.a += capsule.p + capsule.p_d;
	capsule.b += capsule.p + capsule.p_d;
}




/*									//
//				�����蔻��			//
//									*/
// �� vs ��
bool CheckCollision( Sphere &sphere1, Sphere &sphere2 ) {
	// ���S�Ԃ̋����̕������v�Z
	Vector3 d = sphere1.p - sphere2.p;
	float dist2 = Vec3Dot(&d,&d);
	// �������������������������a�̍��v�����������ꍇ�ɋ��͌������Ă���
	float radiusSum = sphere1.r + sphere2.r;
	return dist2 <= radiusSum * radiusSum;
}
// AABB vs AABB
bool CheckCollision(Aabb& aabb1, Aabb& aabb2 ) {
	if( fabsf(aabb1.p.e[0] - aabb2.p.e[0]) > (aabb1.r[0] + aabb2.r[0]) ) return false;
	if( fabsf(aabb1.p.e[1] - aabb2.p.e[1]) > (aabb1.r[1] + aabb2.r[1]) ) return false;
	if( fabsf(aabb1.p.e[2] - aabb2.p.e[2]) > (aabb1.r[2] + aabb2.r[2]) ) return false;
	return true;
}
// OBB vs OBB
bool CheckCollision(Obb& obb1, Obb& obb2) {
	// �e�����x�N�g���̊m��
	// (N***:�W���������x�N�g��)
	Vector3 NAe1 = obb1.axis[0], Ae1 = NAe1 * obb1.r[0];
	Vector3 NAe2 = obb1.axis[1], Ae2 = NAe2 * obb1.r[1];
	Vector3 NAe3 = obb1.axis[2], Ae3 = NAe3 * obb1.r[2];
	Vector3 NBe1 = obb2.axis[0], Be1 = NBe1 * obb2.r[0];
	Vector3 NBe2 = obb2.axis[1], Be2 = NBe2 * obb2.r[1];
	Vector3 NBe3 = obb2.axis[2], Be3 = NBe3 * obb2.r[2];
	Vector3 Interval = obb1.p - obb2.p;	// ���W�̍�

	// �������FAe1
	FLOAT rA = Vec3Length(&Ae1);
	FLOAT rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
	FLOAT L = fabsf(Vec3Dot(&Interval, &NAe1));
	if (L > rA + rB)	return false;	// �Փ˂��Ă��Ȃ�

	// �������FAe2
	rA = Vec3Length(&Ae2);
	rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
	L = fabsf(Vec3Dot(&Interval, &NAe2));
	if (L > rA + rB)	return false;	// �Փ˂��Ă��Ȃ�

	// �������FAe3
	rA = Vec3Length(&Ae3);
	rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
	L = fabsf(Vec3Dot(&Interval, &NAe3));
	if (L > rA + rB)	return false;	// �Փ˂��Ă��Ȃ�

	// �������FBe1
	rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
	rB = Vec3Length(&Be1);
	L = fabsf(Vec3Dot(&Interval, &NBe1));
	if (L > rA + rB)	return false;	// �Փ˂��Ă��Ȃ�

	// �������FBe2
	rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
	rB = Vec3Length(&Be2);
	L = fabsf(Vec3Dot(&Interval, &NBe2));
	if (L > rA + rB)	return false;	// �Փ˂��Ă��Ȃ�

	// �������FBe3
	rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
	rB = Vec3Length(&Be3);
	L = fabsf(Vec3Dot(&Interval, &NBe3));
	if (L > rA + rB)	return false;	// �Փ˂��Ă��Ȃ�

	// �������FC11
	Vector3 Cross;
	Vec3Cross(&Cross, &NAe1, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabsf(Vec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// �������FC12
	Vec3Cross(&Cross, &NAe1, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabsf(Vec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// �������FC13
	Vec3Cross(&Cross, &NAe1, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabsf(Vec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// �������FC21
	Vec3Cross(&Cross, &NAe2, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabsf(Vec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// �������FC22
	Vec3Cross(&Cross, &NAe2, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabsf(Vec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// �������FC23
	Vec3Cross(&Cross, &NAe2, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabsf(Vec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// �������FC31
	Vec3Cross(&Cross, &NAe3, &NBe1);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
	L = fabsf(Vec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// �������FC32
	Vec3Cross(&Cross, &NAe3, &NBe2);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
	L = fabsf(Vec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// �������FC33
	Vec3Cross(&Cross, &NAe3, &NBe3);
	rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
	rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
	L = fabsf(Vec3Dot(&Interval, &Cross));
	if (L > rA + rB)	return false;

	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	return true;
}
// �� vs �J�v�Z��
bool CheckCollision(Sphere& sphere, Capsule& capsule) {
	// ���̒��S�ƃJ�v�Z���̐����̊Ԃ́i���s�����j�������v�Z
	float dist2 = SqDistPointSegment(capsule.a, capsule.b, sphere.p);
	// �i���s�����j�������i���s�����j���a�̑��a�����������ꍇ�́A�Փ�
	float radius = sphere.r + capsule.r;
	return dist2 <= radius * radius;
}
bool CheckCollision(Capsule& capsule, Sphere& sphere) {
	return CheckCollision(sphere, capsule);
}
// �� vs AABB
bool CheckCollision(Sphere& sphere, Aabb& aabb, Point3& p) {
	// ���̒��S�ɑ΂���ŋߐړ_�ł���AABB��ɂ���_p��������
	ClosestPtPointAABB(sphere.p, aabb, p);

	// ����AABB����������̂́A���̒��S����_p�܂ł́i���������j������
	// �i���������j���̔��a�����������ꍇ
	Vector3 v = p - sphere.p;

	return Vec3Dot(&v, &v) <= sphere.r * sphere.r;
}
bool CheckCollision(Sphere& sphere, Aabb& aabb) {
	Point3 p;
	// ���̒��S�ɑ΂���ŋߐړ_�ł���AABB��ɂ���_p��������
	ClosestPtPointAABB(sphere.p, aabb, p);

	// ����AABB����������̂́A���̒��S����_p�܂ł́i���������j������
	// �i���������j���̔��a�����������ꍇ
	Vector3 v = p - sphere.p;

	return Vec3Dot(&v, &v) <= sphere.r * sphere.r;
}
bool CheckCollision(Aabb& aabb, Sphere& sphere) {
	return CheckCollision(sphere, aabb);
}
// �� vs OBB
bool CheckCollision(Sphere& sphere, Obb& obb, Point3& p) {
	// ���̒��S�ɑ΂���ŋߐړ_�ł���AABB��ɂ���_p��������
	ClosestPtPointOBB(sphere.p, obb, p);

	// ����AABB����������̂́A���̒��S����_p�܂ł́i���������j������
	// �i���������j���̔��a�����������ꍇ
	Vector3 v = p - sphere.p;

	return Vec3Dot(&v, &v) <= sphere.r * sphere.r;
}
bool CheckCollision(Sphere& sphere, Obb& obb) {
	Point3 p;
	// ���̒��S�ɑ΂���ŋߐړ_�ł���AABB��ɂ���_p��������
	ClosestPtPointOBB(sphere.p, obb, p);

	// ����AABB����������̂́A���̒��S����_p�܂ł́i���������j������
	// �i���������j���̔��a�����������ꍇ
	Vector3 v = p - sphere.p;

	return Vec3Dot(&v, &v) <= sphere.r * sphere.r;
}
bool CheckCollision(Obb& obb, Sphere& sphere) {
	return CheckCollision(sphere, obb);
}
// �J�v�Z�� vs �J�v�Z��
bool CheckCollision(Capsule& capsule1, Capsule& capsule2) {
	// �J�v�Z���̓����̍\���̊Ԃ́i���s�����j�������v�Z
	float s, t;
	Point3 c1, c2;
	float dist2 = ClosestPtSegmentSegment(capsule1.a, capsule1.b, capsule2.a, capsule2.b, s, t, c1, c2);

	// �i���������j�������i���s�����j���a�̑��a�����������ꍇ�́A�Փ�
	float radius = capsule1.r + capsule2.r;
	return dist2 <= radius * radius;
}


/*									//
//				�`��				//
//									*/
// ��
void DrawCollision(Sphere& sphere, const Color& Color) {
	if (!bDraw) return;

	DWORD Old;
	Matrix mat;
	MatrixIdentity(&mat);

	VERTEX_XYZ_COL VertexX[36];
	VERTEX_XYZ_COL VertexY[36];
	VERTEX_XYZ_COL VertexZ[36];
	for (int n = 0; n < 36; n++) {
		VertexX[n].x = sphere.p.x;
		VertexX[n].y = sphere.p.y + (sphere.r*cosf(ToRadian(n * 10.0f)));
		VertexX[n].z = sphere.p.z + (sphere.r*sinf(ToRadian(n * 10.0f)));
		VertexX[n].color = Color;
		VertexY[n].x = sphere.p.x + (sphere.r*sinf(ToRadian(n * 10.0f)));
		VertexY[n].y = sphere.p.y;
		VertexY[n].z = sphere.p.z + (sphere.r*cosf(ToRadian(n * 10.0f)));
		VertexY[n].color = Color;
		VertexZ[n].x = sphere.p.x + (sphere.r*sinf(ToRadian(n * 10.0f)));
		VertexZ[n].y = sphere.p.y + (sphere.r*cosf(ToRadian(n * 10.0f)));
		VertexZ[n].z = sphere.p.z;
		VertexZ[n].color = Color;
	};

	unsigned short Index[72];
	for (int n = 0, i = 0; n < 36; n++) {
		Index[i] = n;
		Index[i + 1] = n + 1;
		i += 2;
	};
	Index[71] = 0;


	//LPDIRECT3DDEVICE9 pDevice = GetGraphics()->GetDevice();
	//pDevice->SetTransform( D3DTS_WORLD, &mat);

	//pDevice->SetFVF( FVF_XYZ_COLOR );
	//pDevice->SetTexture( 0, NULL );
	//pDevice->GetRenderState( D3DRS_LIGHTING, &Old );
	//pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//pDevice->DrawIndexedPrimitiveUP( D3DPT_LINELIST, 0, 36, 36, Index, D3DFMT_INDEX16, VertexX, sizeof( VERTEX_XYZ_COL ) );
	//pDevice->DrawIndexedPrimitiveUP( D3DPT_LINELIST, 0, 36, 36, Index, D3DFMT_INDEX16, VertexY, sizeof( VERTEX_XYZ_COL ) );
	//pDevice->DrawIndexedPrimitiveUP( D3DPT_LINELIST, 0, 36, 36, Index, D3DFMT_INDEX16, VertexZ, sizeof( VERTEX_XYZ_COL ) );
	//pDevice->SetRenderState( D3DRS_LIGHTING, Old );
}
// AABB
void DrawCollision(Aabb& aabb, const Color& Color) {
	if (!bDraw) return;

	DWORD Old;
	Matrix mat;
	MatrixIdentity(&mat);

	Point3 p = Point3(aabb.p.e[0], aabb.p.e[1], aabb.p.e[2]);
	VERTEX_XYZ_COL Vertex[8] = {
		{ p.x - aabb.r[0], p.y + aabb.r[1], p.z - aabb.r[2], Color },
		{ p.x - aabb.r[0], p.y + aabb.r[1], p.z + aabb.r[2], Color },
		{ p.x + aabb.r[0], p.y + aabb.r[1], p.z + aabb.r[2], Color },
		{ p.x + aabb.r[0], p.y + aabb.r[1], p.z - aabb.r[2], Color },
		{ p.x - aabb.r[0], p.y - aabb.r[1], p.z - aabb.r[2], Color },
		{ p.x - aabb.r[0], p.y - aabb.r[1], p.z + aabb.r[2], Color },
		{ p.x + aabb.r[0], p.y - aabb.r[1], p.z + aabb.r[2], Color },
		{ p.x + aabb.r[0], p.y - aabb.r[1], p.z - aabb.r[2], Color },
	};

	unsigned short Index[24] = {
		0, 1, 1, 2, 2, 3, 3, 0,
		4, 5, 5, 6, 6, 7, 7, 4,
		0, 4, 1, 5, 2, 6, 3, 7
	};

	//LPDIRECT3DDEVICE9 pDevice = GetGraphics()->GetDevice();
	//pDevice->SetTransform( D3DTS_WORLD, &mat );

	//pDevice->SetFVF( FVF_XYZ_COLOR );
	//pDevice->SetTexture( 0, NULL );
	//pDevice->GetRenderState( D3DRS_LIGHTING, &Old );
	//pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//pDevice->DrawIndexedPrimitiveUP(
	//					D3DPT_LINELIST,
	//					0,
	//					8,
	//					12,
	//					Index,
	//					D3DFMT_INDEX16,
	//					Vertex,
	//					sizeof( VERTEX_XYZ_COL ) );
	//pDevice->SetRenderState( D3DRS_LIGHTING, Old );
}
// OBB
void DrawCollision(Obb& obb, const Color& Color) {
	if (!bDraw) return;

	DWORD Old;
	Matrix mat;
	MatrixIdentity(&mat);

	Vector3 G = obb.p
		- (obb.axis[0] * obb.r[0] * 2.0f
			+ obb.axis[1] * obb.r[1] * 2.0f
			+ obb.axis[2] * obb.r[2] * 2.0f) / 2;

	Vector3 Axis[3] = { obb.axis[0] * obb.r[0] * 2.0f,
						obb.axis[1] * obb.r[1] * 2.0f,
						obb.axis[2] * obb.r[2] * 2.0f };

	VERTEX_XYZ_COL Vertex[8] = {
		{ G.x, G.y, G.z, Color },
		{ G.x + Axis[1].x, G.y + Axis[1].y, G.z + Axis[1].z, Color },
		{ G.x + Axis[1].x + Axis[2].x, G.y + Axis[1].y + Axis[2].y, G.z + Axis[1].z + Axis[2].z, Color },
		{ G.x + Axis[2].x, G.y + Axis[2].y, G.z + Axis[2].z, Color },

		{ G.x + Axis[0].x, G.y + Axis[0].y, G.z + Axis[0].z, Color },
		{ G.x + Axis[0].x + Axis[1].x, G.y + Axis[0].y + Axis[1].y, G.z + Axis[0].z + Axis[1].z, Color },
		{ G.x + Axis[0].x + Axis[1].x + Axis[2].x, G.y + Axis[0].y + Axis[1].y + Axis[2].y, G.z + Axis[0].z + Axis[1].z + Axis[2].z, Color },
		{ G.x + Axis[0].x + Axis[2].x, G.y + Axis[0].y + Axis[2].y, G.z + Axis[0].z + Axis[2].z, Color },
	};

	unsigned short Index[24] = {
		0, 1, 1, 2, 2, 3, 3, 0,
		4, 5, 5, 6, 6, 7, 7, 4,
		0, 4, 1, 5, 2, 6, 3, 7
	};

	//LPDIRECT3DDEVICE9 pDevice = GetGraphics()->GetDevice();
	//pDevice->SetTransform( D3DTS_WORLD, &mat );

	//pDevice->SetFVF( FVF_XYZ_COLOR );
	//pDevice->SetTexture( 0, NULL );
	//pDevice->GetRenderState( D3DRS_LIGHTING, &Old );
	//pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//pDevice->DrawIndexedPrimitiveUP( D3DPT_LINELIST, 0, 8, 12, Index, D3DFMT_INDEX16, Vertex, sizeof( VERTEX_XYZ_COL ) );
	//pDevice->SetRenderState( D3DRS_LIGHTING, Old );
}
// �J�v�Z��
void DrawCollision(Capsule& capsule, const Color& Color) {
	if (!bDraw) return;

	DWORD Old;
	Matrix mat;
	MatrixIdentity(&mat);

	VERTEX_XYZ_COL VertexX1[36];
	VERTEX_XYZ_COL VertexX2[36];
	VERTEX_XYZ_COL VertexY1[36];
	VERTEX_XYZ_COL VertexY2[36];
	//VERTEX_XYZ_COL VertexY[36];
	//VERTEX_XYZ_COL VertexZ[36];
	for (int n = 0; n < 36; n++) {
		VertexX1[n].x = capsule.a.x + (capsule.r*cosf(ToRadian(n*-10.0f)));
		VertexX1[n].y = capsule.a.y;
		VertexX1[n].z = capsule.a.z + (capsule.r*sinf(ToRadian(n*-10.0f)));
		VertexX1[n].color = Color;
		VertexX2[n].x = capsule.a.x + (capsule.r*sinf(ToRadian(n * 10.0f)));
		VertexX2[n].y = capsule.a.y + (capsule.r*cosf(ToRadian(n * 10.0f)));
		VertexX2[n].z = capsule.a.z;
		VertexX2[n].color = Color;
		VertexY1[n].x = capsule.b.x + (capsule.r*cosf(ToRadian(n*-10.0f)));
		VertexY1[n].y = capsule.b.y;
		VertexY1[n].z = capsule.b.z + (capsule.r*sinf(ToRadian(n*-10.0f)));
		VertexY1[n].color = Color;
		VertexY2[n].x = capsule.b.x + (capsule.r*sinf(ToRadian(n * 10.0f)));
		VertexY2[n].y = capsule.b.y + (capsule.r*cosf(ToRadian(n * 10.0f)));
		VertexY2[n].z = capsule.b.z;
		VertexY2[n].color = Color;
		//	VertexZ[n].x = sphere.p.x+(sphere.r*sinf(D3DXToRadian(n*10)));
		//	VertexZ[n].y = sphere.p.y+(sphere.r*cosf(D3DXToRadian(n*10)));
		//	VertexZ[n].z = sphere.p.z;
		//	VertexZ[n].color = Color;
	};

	unsigned short Index[72];
	for (int n = 0, i = 0; n < 36; n++) {
		Index[i] = n;
		Index[i + 1] = n + 1;
		i += 2;
	};
	Index[71] = 0;

	//LPDIRECT3DDEVICE9 pDevice = GetGraphics()->GetDevice();
	//pDevice->SetTransform( D3DTS_WORLD, &mat);

	//pDevice->SetFVF( FVF_XYZ_COLOR );
	//pDevice->SetTexture( 0, NULL );
	//pDevice->GetRenderState( D3DRS_LIGHTING, &Old );
	//pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	//pDevice->DrawIndexedPrimitiveUP( D3DPT_LINELIST, 0, 36, 36, Index, D3DFMT_INDEX16, VertexX1, sizeof( VERTEX_XYZ_COL ) );
	//pDevice->DrawIndexedPrimitiveUP( D3DPT_LINELIST, 0, 36, 36, Index, D3DFMT_INDEX16, VertexX2, sizeof( VERTEX_XYZ_COL ) );
	//pDevice->DrawIndexedPrimitiveUP( D3DPT_LINELIST, 0, 36, 36, Index, D3DFMT_INDEX16, VertexY1, sizeof( VERTEX_XYZ_COL ) );
	//pDevice->DrawIndexedPrimitiveUP( D3DPT_LINELIST, 0, 36, 36, Index, D3DFMT_INDEX16, VertexY2, sizeof( VERTEX_XYZ_COL ) );
	////pDevice->DrawIndexedPrimitiveUP( D3DPT_LINELIST, 0, 36, 36, Index, D3DFMT_INDEX16, VertexY, sizeof( VERTEX_XYZ_COL ) );
	////pDevice->DrawIndexedPrimitiveUP( D3DPT_LINELIST, 0, 36, 36, Index, D3DFMT_INDEX16, VertexZ, sizeof( VERTEX_XYZ_COL ) );
	//pDevice->SetRenderState( D3DRS_LIGHTING, Old );
}



/*									//
//	�������̐������瓊�e���������Z�o//
//									*/
float LenSegOnSeparateAxis(
	Vector3 *Sep,
	Vector3 *e1,
	Vector3 *e2,
	Vector3 *e3)
{
	// 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
	// ������Sep�͕W��������Ă��邱��
	FLOAT r1 = fabsf(Vec3Dot(Sep, e1));
	FLOAT r2 = fabsf(Vec3Dot(Sep, e2));
	FLOAT r3 = e3 ? (fabsf(Vec3Dot(Sep, e3))) : 0;
	return r1 + r2 + r3;
}


/*									//
// �_c�Ɛ���ab�̊Ԃ̋����̕�����Ԃ�//
//									*/
float SqDistPointSegment(Point3& a, Point3& b, Point3& c) {
	Vector3 ab = b - a, ac = c - a, bc = c - b;
	float e = Vec3Dot(&ac, &ab);

	// c��ab�̊O���Ɏˉe�����ꍇ������
	if (e <= 0.0f) return Vec3Dot(&ac, &ac);
	float f = Vec3Dot(&ab, &ab);
	if (e >= f) return Vec3Dot(&bc, &bc);

	// c��ab��Ɏˉe�����ꍇ������
	return Vec3Dot(&ac, &ac) - e * e / f;
}


/*									//
// �_p��AABB b�̊Ԃ̋����̕�����Ԃ�//
//									*/
float SqDistPointAABB(Point3& p, Aabb& b) {
	float sqDist = 0.0f;
	for (int i = 0; i < 3; i ++) {
		// �e���ɑ΂��ă{�b�N�X�͈̔͂𒴂���]���ȋ������v�Z
		float v = p.e[i];
		float min = b.p.e[i] - b.r[i];
		float max = b.p.e[i] + b.r[i];
		float len = min - v;
		if (v < min) sqDist += len * len;
		len = v - max;
		if (v > max) sqDist += len * len;
	}
	return sqDist;
}


/*									//
// �_p��OBB b�̊Ԃ̋����̕�����Ԃ�	//
//									*/
float SqDistPointOBB(Point3& p, Obb& b) {
	Vector3 v = p - b.p;
	float sqDist = 0.0f;
	for (int i = 0; i < 3; i ++) {
		// �{�b�N�X�̒��S����p�܂ł̃x�N�g�����e����Ɏˉe���A���̎��ɉ�����p�̋����𓾂�
		// �{�b�N�X�͈̔͂𒴂���]���ȋ������v�Z
		float d = Vec3Dot(&v, &b.axis[i]), excess = 0.0f;
		if (d < -b.r[i])
			excess = d + b.r[i];
		else if (d > b.r[i])
			excess = d - b.r[i];
		sqDist += excess * excess;
	}
	return sqDist;
}


/*									//
//		2�̐����̍ŋߐړ_			//
//									*/
float ClosestPtSegmentSegment(
	Point3& p1, Point3& q1,
	Point3& p2, Point3& q2,
	float& s, float& t,
	Point3& c1, Point3& c2)
{
	Vector3 d1 = q1 - p1;	// ����S1�̕����x�N�g��
	Vector3 d2 = q2 - p2;	// ����S2�̕����x�N�g��
	Vector3 r = p1 - p2;
	float a = Vec3Dot(&d1, &d1);	// ����S1�̋����̕����A��ɔ�
	float e = Vec3Dot(&d2, &d2);	// ����S2�̋����̕����A��ɔ�
	float f = Vec3Dot(&d2, &r);

	// �Е����邢�͗����̐������_�ɏk�ނ��Ă��邩�ǂ����`�F�b�N
	if (a <= FLT_EPSILON && e <= FLT_EPSILON) {
		// �����̐������_�ɏk��
		s = t = 0.0f;
		c1 = p1;
		c2 = p2;
		return Vec3Dot(&(c1 - c2), &(c1 - c2));
	}
	if (a <= FLT_EPSILON) {
		// �ŏ��̐������_�ɏk��
		s = 0.0f;
		t = Clamp(f / e, 0.0f, 1.0f);	// s = 0 => t = (b * s + f) / e = f / e
	} else {
		float c = Vec3Dot(&d1, &r);
		if (e <= FLT_EPSILON) {
			// 2�Ԗڂ̐������_�ɏk��
			t = 0.0f;
			s = Clamp(-c / a, 0.0f, 1.0f);	// t = 0 => s = (b * t - c) / a = -c / a
		} else {
			// ���������ʓI�ȏk�ނ̏ꍇ���J�n
			float b = Vec3Dot(&d1, &d2);
			float denom = a * e - b * b;	// ��ɔ�
			// ���������s�łȂ��ꍇ�AL1���L2�ɑ΂���ŋߐړ_���v�Z�A������
			// ����S1�ɑ΂��ăN�����v�B�����łȂ��ꍇ�͔C��s(�����ł�0)��I��
			if (denom != 0.0f) {
				s = Clamp((b * f - c * e) / denom, 0.0f, 1.0f);
			} else s = 0.0f;
			// L2���S1(s)�ɑ΂���ŋߐړ_���ȉ���p���Čv�Z
			// t = Dot((P1 + D1 * s) - P2, D2) / Dot(D2, D2) = (b * s + f) / e
			float tnom = b * s + f;
			// t��[0,1]�̒��ɂ���ΏI���B�����łȂ����t���N�����v�As��t�̐V�����l�ɑ΂��Ĉȉ���p���čČv�Z
			// s = Dot((P2 + D2 * t) - P1, D1) / Dot(D1, D1) = (t * b - c) / a
			// ������s��[0,1]�ɑ΂��ăN�����v
			if (tnom < 0.0f) {
				t = 0.0f;
				s = Clamp(-c / a, 0.0f, 1.0f);
				//			} else if( t > 1.0f ) {
			} else if (tnom > e) {
				t = 1.0f;
				s = Clamp((b - c) / a, 0.0f, 1.0f);
			} else {
				t = tnom / e;
			}
		}
	}

	c1 = p1 + d1 * s;
	c2 = p2 + d2 * t;
	return Vec3Dot(&(c1 - c2), &(c1 - c2));
}


/*									//
//	����ab����ѓ_c�ɑ΂��āA		//
//	ab��̍ŋߐړ_d���Z�o			//
//									*/
void ClosestPtPointSegment(Point3 c, Point3 a, Point3 b, float& t, Point3& d) {
	Vector3 ab = b - a;

	// ab���c���ˉe�A������Dot(ab, ab)�ɂ�鏜�Z�͉���
	t = Vec3Dot(&(c - a), &ab);
	if (t <= 0.0f) {
		// c�͔͈�[a,b]�̊O���Aa�̑��Ɏˉe����Aa�܂ŃN�����v
		t = 0.0f;
		d = a;
	} else {
		float denom = Vec3Dot(&ab, &ab);	// denom = |ab|^2 �Ȃ̂ŏ�ɔ�
		if (t >= denom) {
			// c�͔͈�[a,b]�̊O���Ab�̑��Ɏˉe����Ab�܂ŃN�����v
			t = 1.0f;
			d = b;
		} else {
			// c�͔͈�[a,b]�̓����Ɏˉe����A���̎��܂ŏ��Z�͉���
			t = t / denom;
			d = a + (ab * t);
		}
	}
}


/*									//
//	�_p�ɑ΂��āAAABB b�̏��������	//
//	���ɂ���p�̍ŋߐړ_q���Z�o		//
//									*/
void ClosestPtPointAABB(Point3& p, Aabb& b, Point3& q) {
	// �e���W���ɑ΂��āA�_�̍��W�l���{�b�N�X�̊O���ɂ���ꍇ��
	// �{�b�N�X�܂œ_���N�����v�A�����łȂ���΂��̂܂�
	for (int i = 0; i < 3; i ++) {
		float v = p.e[i];
		float min = b.p.e[i] - b.r[i];
		float max = b.p.e[i] + b.r[i];
		if (v < min) v = min;	// v = max( v, b.min[i] )
		if (v > max) v = max;	// v = min( v, b.max[i] )
		q.e[i] = v;
	}
}


/*									//
//	�_p�ɑ΂��āAOBB b�̏��������	//
//	���ɂ���p�̍ŋߐړ_q���Z�o		//
//									*/
void ClosestPtPointOBB(Point3& p, Obb& b, Point3& q) {
	Vector3 d = p - b.p;
	// �{�b�N�X�̒��S�ɂ����錋�ʂ���J�n�A��������i�K�I�ɐi�߂�
	q = b.p;
	// �eOBB�̎��ɑ΂���
	for (int i = 0; i < 3; i ++) {
		// ...d�����̎��Ɏˉe����
		// �{�b�N�X�̒��S����d�̎��ɉ����������𓾂�
		float dist = Vec3Dot(&d, &b.axis[i]);
		// �{�b�N�X�͈̔͂����������傫���ꍇ�A�{�b�N�X�܂ŃN�����v
		if (dist > b.r[i]) dist = b.r[i];
		if (dist < -b.r[i]) dist = -b.r[i];
		// ���[���h���W�𓾂邽�߂ɂ��̋����������ɉ����Đi�߂�
		q += (b.axis[i] * dist);
	}
}