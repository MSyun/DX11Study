// 4x4�s��
// 2017. 4.16	�v���O�����쐬
// author		SyunMizuno


#pragma once



class Matrix4x4 {
public:
	union {
		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;
		};
		float m[4][4];
		float e[16];
	};

public:
	Matrix4x4();
	Matrix4x4(const float fDat);
	Matrix4x4(const Matrix4x4& mat);
	Matrix4x4(
		float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44);
	~Matrix4x4();

	Matrix4x4& operator += (const Matrix4x4& mat);
	Matrix4x4& operator -= (const Matrix4x4& mat);
	Matrix4x4& operator *= (const Matrix4x4& mat);
	Matrix4x4& operator *= (const float fDat);
	Matrix4x4& operator /= (const float fDat);

	Matrix4x4 operator + () const;
	Matrix4x4 operator - () const;

	Matrix4x4 operator + (const Matrix4x4& mat) const;
	Matrix4x4 operator - (const Matrix4x4& mat) const;
	Matrix4x4 operator * (const Matrix4x4& mat) const;
	Matrix4x4 operator * (const float fDat) const;
	Matrix4x4 operator / (const float fDat) const;

	bool operator == (const Matrix4x4& mat) const;
	bool operator != (const Matrix4x4& mat) const;
};

using Matrix = Matrix4x4;
using Matrix44 = Matrix4x4;