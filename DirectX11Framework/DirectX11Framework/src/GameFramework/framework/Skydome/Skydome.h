// �X�J�C�h�[��
// 2017.05.21	: �v���O�����쐬
// author		: SyunMizuno


#pragma once


#include	"../Object/3DObject/Object3D.h"


namespace MSLib {

	class Skydome : public	Object3D {
	public:
		Skydome();
		virtual ~Skydome();

	private:
		void Update() override;
		void Draw() override;
	};

}