// �ʒu�A��]�A�X�P�[��������
// 2017. 1. 2	�v���O�����쐬
// author		SyunMizuno

#pragma once


#include	"../framework/Convert/Convert.h"
#include	<vector>
using namespace std;


namespace MSLib {

	class Object;

	class Transform {
	private:
#pragma region variable

		Object*	m_pObject;

		Matrix	m_matWorld;
		Matrix	m_matLocal;

		Transform* m_pParent;			// �e
		vector<Transform*> m_Childs;	// �q

#pragma endregion

	public:
#pragma region method

		Transform(Object* object = NULL);
		virtual ~Transform();

#pragma region Matrix
		// ���[���h�s��擾
		Matrix& GetWorld();
		// ���[�J���s��擾
		Matrix& GetLocal();
		// ���[���h�s��ݒ�
		void SetWorld(const Matrix& _world);
		// ���[�J���s��ݒ�
		void SetLocal(const Matrix& _local);
		// Z�x�N�g���擾
		Vector3 GetForward();
		// Y�x�N�g���擾
		Vector3 GetUp();
		// X�x�N�g���擾
		Vector3 GetRight();
#pragma endregion

#pragma region Position
		// ���W�擾
		Point3 GetPos() const;
		// ���W�擾�i���[�J��
		Point3 GetLocalPos() const;
		// ���W�ݒ�
		void SetPos(const Point3& pos);
		void SetPos(float x, float y, float z);
		void SetLocalPos(const Point3& pos);
		void SetLocalPos(float x, float y, float z);
		// ���ړ�
		void Translate(const Vector3& vec, Transform* relativeTo = NULL);
		void Translate(float x, float y, float z, Transform* relativeTo = NULL);
#pragma endregion

#pragma region Rotate
		// ��]
		void Rotate(Vector3 eularAngles, bool World = false);
		void Rotate(float xAngle, float yAngle, float zAngle, bool World = false);
		// �I�C���[�p
		void SetEularAngles(Vector3 eularAngles);
		void SetEularAngles(float xAngle, float yAngle, float zAngle);
#pragma endregion

#pragma region Scale
		// �g�嗦�擾�i���[���h
		Vector3 GetScale() const;
		// �g�嗦�擾�i���[�J��
		Vector3 GetLocalScale() const;
		// �g�嗦�ݒ�
		void SetScale(const Vector3& scale);
		// �g�嗦�ݒ�
		void SetScale(float x, float y, float z);
#pragma endregion

		// �����_�ݒ�
		void LookAt(Transform* target, const Vector3 worldUp = Vector3(0.0f, 1.0f, 0.0f));
		void LookAt(Point3& target, const Vector3 worldUp = Vector3(0.0f, 1.0f, 0.0f));

		// �O����ɉ�]
		void FowardBaseRotate(Transform* target, float angle);

		Object* GetGameObject() { return m_pObject; }

#pragma region Parent
		// �e�̊m�F
		bool CheckParent() { return m_pParent == NULL ? false : true; }
		// �e�ݒ�
		void SetParent(Transform* parent);
		// �e���
		void RemoveParent();
#pragma endregion

#pragma region Child
		//----- ������͊O�ł͌Ăяo���Ȃ���
		// �q�ݒ�
		void SetChild(Transform* child);
		// �q���
		void RemoveChild(Transform* child);
		// �X�V
		void UpdateChilds(const Matrix& world);
		// �q�̎擾
		vector<Transform*>* GetChilds() {
			return &m_Childs;
		}
#pragma endregion

		// �폜
		void Destroy();

		// ����
		Transform* Find(const string name);

#pragma endregion

	private:
#pragma region conceal method

		// ���[�J���s��̃��Z�b�g
		void ReSetLocal();
		// ���[���h�s��̃��Z�b�g
		void ReSetWorld();

#pragma region Position
		// ���[�J�����ړ�
		void TranslateLocal(const Vector3& vec, Transform* relativeTo);
		void TranslateLocal(float x, float y, float z, Transform* relativeTo);
		// ���[���h���ړ�
		void TranslateWorld(const Vector3& vec);
		void TranslateWorld(float x, float y, float z);
#pragma endregion

#pragma region Rotate
		// ���[���h����]
		void RotateWorld(float xAngle, float yAngle, float zAngle);
		// ���[�J������]
		void RotateLocal(float xAngle, float yAngle, float zAngle);
#pragma endregion

#pragma endregion
	};

}