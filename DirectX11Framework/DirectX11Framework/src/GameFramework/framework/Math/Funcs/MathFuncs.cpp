// �v�Z�p�֐��Q
// 2016. 4.16	:	�v���O�����쐬
// author		:	SyunMizuno


#include	"MathFuncs.h"
#include	<math.h>




/*									//
//				����				//
//									*/
float Vec3Dot(const Vector3* pL, const Vector3* pR) {
	if (!pL || !pR)	return 0.0f;
	return pL->x * pR->x + pL->y * pR->y + pL->z * pR->z;
}


/*									//
//				�O��				//
//									*/
void Vec3Cross(Vector3* pOut, const Vector3* pL, const Vector3* pR) {
	if (!pOut || !pL || !pR)	return;
	Vector3 v;
	v.x = pL->y * pR->z - pL->z * pR->y;
	v.y = pL->z * pR->x - pL->x * pR->z;
	v.z = pL->x * pR->y - pL->y * pR->x;
	*pOut = v;
}



/*									//
//			�P�ʍs��̐���			//
//									*/
void MatrixIdentity(Matrix4x4* pMat) {
	if (!pMat)	return;

	for (int x = 0; x < 4; ++x) {
		for (int y = 0; y < 4; ++y) {
			pMat->m[y][x] = (x == y);
		}
	}
}


/*									//
//				�s��̏�Z			//
//									*/
void MatrixMultiply(
	Matrix4x4* pMat,
	const Matrix4x4* pL,
	const Matrix4x4* pR)
{
	if (!pMat || !pL || !pR)	return;
	Matrix4x4 m;
	for (int y = 0; y < 4; ++ y) {
		for (int x = 0; x < 4; ++x) {
			m.m[y][x] = 0;
			for (int k = 0; k < 4; ++ k) {
				m.m[y][x] += pL->m[y][k] * pR->m[k][x];
			}
		}
	}
	*pMat = m;

}


/*									//
//		���[���hX����]�s�񐶐�		//
//									*/
void MatrixRotationX(Matrix4x4* pMat, float Angle) {
	if (!pMat)	return;
	MatrixIdentity(pMat);
	float fCos = cosf(Angle);
	float fSin = sinf(Angle);
	pMat->_22 = pMat->_33 = fCos;
	pMat->_23 = fSin;
	pMat->_32 = -fSin;
}


/*									//
//		���[���hY����]�s�񐶐�		//
//									*/
void MatrixRotationY(Matrix4x4* pMat, float Angle) {
	if (!pMat)	return;
	MatrixIdentity(pMat);
	float fCos = cosf(Angle);
	float fSin = sinf(Angle);
	pMat->_11 = pMat->_33 = fCos;
	pMat->_13 = -fSin;
	pMat->_31 = fSin;
}


/*									//
//		���[���hZ����]�s�񐶐�		//
//									*/
void MatrixRotationZ(Matrix4x4* pMat, float Angle) {
	if (!pMat)	return;
	MatrixIdentity(pMat);
	float fCos = cosf(Angle);
	float fSin = sinf(Angle);
	pMat->_11 = pMat->_22 = fCos;
	pMat->_12 = fSin;
	pMat->_21 = -fSin;
}


/*									//
//		���[���h3����]�s�񐶐�		//
//									*/
void MatrixRotationYawPitchRoll(
	Matrix4x4* pMat, 
	float Yaw,
	float Pitch,
	float Roll)
{
	if (!pMat)	return;
	MatrixRotationY(pMat, Yaw);
	Matrix4x4 m;
	MatrixRotationX(&m, Pitch);
	MatrixMultiply(pMat, pMat, &m);
	MatrixRotationZ(&m, Roll);
	MatrixMultiply(pMat, pMat, &m);
}


/*									//
//	���[���h�s�񕽍s�ړ��s�񐶐�	//
//									*/
void MatrixTranslation(
	Matrix4x4* pMat,
	float X,
	float Y,
	float Z)
{
	if (!pMat)	return;
	MatrixIdentity(pMat);
	pMat->_41 = X;
	pMat->_42 = Y;
	pMat->_43 = Z;
}


/*									//
//			�g��E�k���s�񐶐�		//
//									*/
void MatrixScaling(
	Matrix4x4* pMat,
	float X,
	float Y,
	float Z)
{
	if (!pMat)	return;
	MatrixIdentity(pMat);
	pMat->_11 = X;
	pMat->_22 = Y;
	pMat->_33 = Z;
}


/*									//
//			�]�u�s�񐶐�			//
//									*/
void MatrixTranspose(Matrix4x4* pOut, const Matrix4x4* pM) {
	Matrix4x4 m;
	for (int x = 0; x < 4; ++ x) {
		for (int y = 0; y < 4; ++ y) {
			m.m[x][y] = pM->m[y][x];
		}
	}
	*pOut = m;
}


/*									//
//		������W�n�r���[�s��쐬	//
//									*/
void MatrixLookAtLH(
	Matrix4x4* pOut,
	const Vector3* pEye,
	const Vector3* pAt,
	const Vector3* pUp)
{
	Vector3 xAxis, yAxis, zAxis;
	zAxis = *pAt - *pEye;
	zAxis.normalize();
	Vec3Cross(&xAxis, pUp, &zAxis);
	xAxis.normalize();
	Vec3Cross(&yAxis, &zAxis, &xAxis);

	pOut->_11 = xAxis.x;
	pOut->_12 = yAxis.x;
	pOut->_13 = zAxis.x;
	pOut->_14 = 0.0f;
	pOut->_21 = xAxis.y;
	pOut->_22 = yAxis.y;
	pOut->_23 = zAxis.y;
	pOut->_24 = 0.0f;
	pOut->_31 = xAxis.z;
	pOut->_32 = yAxis.z;
	pOut->_33 = zAxis.z;
	pOut->_34 = 0.0f;
	pOut->_41 = -Vec3Dot(&xAxis, pEye);
	pOut->_42 = -Vec3Dot(&yAxis, pEye);
	pOut->_43 = -Vec3Dot(&zAxis, pEye);
	pOut->_44 = 1.0f;
}


/*									//
//		������W�n�r���[�s��쐬	//
//									*/
void MatrixLookAtRH(
	Matrix4x4* pOut,
	const Vector3* pEye,
	const Vector3* pAt,
	const Vector3* pUp)
{
	Vector3 xAxis, yAxis, zAxis;
	zAxis = *pEye - *pAt;
	zAxis.normalize();
	Vec3Cross(&xAxis, pUp, &zAxis);
	xAxis.normalize();
	Vec3Cross(&yAxis, &zAxis, &xAxis);

	pOut->_11 = xAxis.x;
	pOut->_12 = yAxis.x;
	pOut->_13 = zAxis.x;
	pOut->_14 = 0.0f;
	pOut->_21 = xAxis.y;
	pOut->_22 = yAxis.y;
	pOut->_23 = zAxis.y;
	pOut->_24 = 0.0f;
	pOut->_31 = xAxis.z;
	pOut->_32 = yAxis.z;
	pOut->_33 = zAxis.z;
	pOut->_34 = 0.0f;
	pOut->_41 = -Vec3Dot(&xAxis, pEye);
	pOut->_42 = -Vec3Dot(&yAxis, pEye);
	pOut->_43 = -Vec3Dot(&zAxis, pEye);
	pOut->_44 = 1.0f;
}


/*									//
//������W�n�p�[�X�y�N�e�B�u�s��쐬//
//									*/
void MatrixPerspectiveFovLH(
	Matrix4x4* pOut,
	float fovY,
	float Aspect,
	float zn,
	float zf)
{
	float h, w;
	h = 1.0f / tanf(fovY / 2.0f);
	w = h / Aspect;
	pOut->_11 = w;
	pOut->_12 = 0.0f;
	pOut->_13 = 0.0f;
	pOut->_14 = 0.0f;
	pOut->_21 = 0.0f;
	pOut->_22 = h;
	pOut->_23 = 0.0f;
	pOut->_24 = 0.0f;
	pOut->_31 = 0.0f;
	pOut->_32 = 0.0f;
	pOut->_33 = zf / (zf - zn);
	pOut->_34 = 1.0f;
	pOut->_41 = 0.0f;
	pOut->_42 = 0.0f;
	pOut->_43 = -zn * zf / (zf - zn);
	pOut->_44 = 0.0f;
}


/*									//
//			�C�ӎ���]�s�񐶐�		//
//									*/
void MatrixRotationAxis(
	Matrix4x4* pMat,
	Vector3* pV,
	float Angle)
{
	if (!pMat || !pV)	return;
	float& x = pV->x;
	float& y = pV->y;
	float& z = pV->z;
	float s = sinf(Angle);
	float c = cosf(Angle);
	float omc = 1.0f - c;
	pMat->_11 = c + omc * x * x;
	pMat->_12 = omc * x * y + s * z;
	pMat->_13 = omc * x * z - s * y;
	pMat->_14 = 0.0f;
	pMat->_21 = omc * x * y - s * z;
	pMat->_22 = c + omc * y * y;
	pMat->_23 = omc * y * z + s * x;
	pMat->_24 = 0.0f;
	pMat->_31 = omc * x * z + s * y;
	pMat->_32 = omc * y * z - s * x;
	pMat->_33 = c + omc * z * z;
	pMat->_34 = 0.0f;
	pMat->_41 = 0.0f;
	pMat->_42 = 0.0f;
	pMat->_43 = 0.0f;
	pMat->_44 = 1.0f;
}