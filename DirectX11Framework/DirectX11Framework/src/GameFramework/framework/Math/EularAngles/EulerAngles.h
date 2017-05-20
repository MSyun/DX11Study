// �I�C���[�p
// 2016. 5. 5	:	�v���O�����쐬
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

		// �P��������(���ׂ�0��ݒ肷��)
		void identity() { pitch = bank = heading = 0.0f; }

		// �����I�C���[�p��3�g�����肷��
		void canonize();

		// �l�������I�C���[�p�`���ɕϊ�����
		// ���͂����l�����́A���̖��O�������悤�ɃI�u�W�F�N�g��Ԃ��犵����ԁA
		// �܂��́A������Ԃ���I�u�W�F�N�g��Ԃւ̉�]�����s������̂Ƃ���
		void fromObjectToInertialQuaternion(const Quaternion& q);
		void fromInertialToObjectQuaternion(const Quaternion& q);

		// ���W�ϊ��s����I�C���[�p�`���ɕϊ�����
		// ���͂����s��́A���ꂪ�����悤�ɃI�u�W�F�N�g��Ԃ��烏�[���h��ԁA
		// ���[���h��Ԃ���I�u�W�F�N�g��Ԃւ̍��W�ϊ������s������̂Ƃ���
		// ���̍s��́A�������Ă�����̂Ƃ���
		void fromObjectToWorldMatrix(const Matrix4x3& m);
		void fromWorldToObjectMatrix(const Matrix4x3& m);

		// ��]�s����I�C���[�p�`���ɕϊ�����
		void fromRotationMatrix(const RotationMatrix& m);
	};

	extern const EulerAngles kEularAnglesIdentity;

};