// 4Dベクトル
// 2017. 4.16	プログラム作成
// author		SyunMizuno

#pragma once


namespace MSLib {

	typedef struct Vector4 {
	public:
		union {
			struct {
				float x, y, z, w;
			};
			struct {
				float r, g, b, a;
			};
			float e[4];
		};

	public:
		Vector4();
		Vector4(float x, float y, float z, float w);
		Vector4(const float* val);
		Vector4(const float& val);
		Vector4(const Vector4& vec);
		~Vector4() {};

		Vector4& operator +=(const Vector4& vec);
		Vector4& operator -=(const Vector4& vec);
		Vector4& operator *=(const float fDat);
		Vector4& operator /=(const float fDat);

		Vector4& operator =(const Vector4& vec);
		Vector4 operator +(const Vector4& vec) const;
		Vector4 operator -(const Vector4& vec) const;
		Vector4 operator -() const;
		Vector4 operator *(const float fDat) const;
		Vector4 operator /(const float fDat) const;
		Vector4 operator *(const Vector4& vec) const;
		Vector4 operator /(const Vector4& vec) const;

		bool operator ==(const Vector4& vec) const;
		bool operator !=(const Vector4& vec) const;

		void zero();
		void one();

		void normalize();
		Vector4 getNormalize() const;
		float length() const;
	} Vector4, Point4, Color, float4;

};