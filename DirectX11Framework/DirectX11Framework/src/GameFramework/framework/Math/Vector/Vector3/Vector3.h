// 3Dベクトル
// 2017. 1.29	プログラム作成
// author		SyunMizuno

#pragma once


namespace MSLib {

	typedef struct Vector3 {
	public:
		union {
			struct {
				float x, y, z;
			};
			struct {
				float r, g, b;
			};
			float e[3];
		};

	public:
		Vector3() {};
		Vector3(float x, float y, float z);
		Vector3(const float* val);
		Vector3(const float& val);
		Vector3(const Vector3& vec);
		~Vector3() {};

		Vector3& operator +=(const Vector3& vec);
		Vector3& operator -=(const Vector3& vec);
		Vector3& operator *=(const float fDat);
		Vector3& operator /=(const float fDat);

		Vector3& operator =(const Vector3& vec);
		Vector3 operator +(const Vector3& vec) const;
		Vector3 operator -(const Vector3& vec) const;
		Vector3 operator -() const;
		Vector3 operator *(const float fDat) const;
		Vector3 operator /(const float fDat) const;
		Vector3 operator *(const Vector3& vec) const;
		Vector3 operator /(const Vector3& vec) const;

		bool operator ==(const Vector3& vec) const;
		bool operator !=(const Vector3& vec) const;

		void zero();
		void one();

		void normalize();
		Vector3 getNormalize() const;
		float length() const;
	} Vector3, Point3, float3;

};