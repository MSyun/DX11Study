// オイラー角
// 2016. 5. 5	:	プログラム作成
// author		:	SyunMizuno


#pragma once


namespace MSLib {

	class Matrix4x3;
	struct Quaternion;
	class RotationMatrix;


	class EulerAngles {
	public:
		float	heading;
		float	pitch;
		float	bank;

	public:
		EulerAngles() {}

		EulerAngles(float h, float p, float b) :
			heading(h), pitch(p), bank(b) {}

		// 恒等化する(すべて0を設定する)
		void identity() { pitch = bank = heading = 0.0f; }

		// 正準オイラー角の3つ組を決定する
		void canonize();

		// 四元数をオイラー角形式に変換する
		// 入力される四元数は、その名前が示すようにオブジェクト空間から慣性空間、
		// または、慣性空間からオブジェクト空間への回転を実行するものとする
		void fromObjectToInertialQuaternion(const Quaternion& q);
		void fromInertialToObjectQuaternion(const Quaternion& q);

		// 座標変換行列をオイラー角形式に変換する
		// 入力される行列は、それが示すようにオブジェクト空間からワールド空間、
		// ワールド空間からオブジェクト空間への座標変換を実行するものとする
		// この行列は、直交しているものとする
		void fromObjectToWorldMatrix(const Matrix4x3& m);
		void fromWorldToObjectMatrix(const Matrix4x3& m);

		// 回転行列をオイラー角形式に変換する
		void fromRotationMatrix(const RotationMatrix& m);
	};

	extern const EulerAngles kEularAnglesIdentity;

};