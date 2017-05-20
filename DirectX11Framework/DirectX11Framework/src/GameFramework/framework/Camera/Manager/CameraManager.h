// �J�����}�l�[�W���[
// 2017.05.15	: �v���O�����쐬
// author		: SyunMizuno

#pragma once


#include	<vector>
#include	<string>
#include	"../Camera.h"
#include	"../../Singleton/Singleton.h"


namespace MSLib {

	class CameraManager : public	Singleton<CameraManager> {
	protected:
		std::vector<Camera*>	m_aCamera;

		std::string m_CurCameraName;

	public:
		CameraManager();
		virtual ~CameraManager();

		/* �ǉ�
		// camera	: �ǉ��������J����
		*/
		void Add(Camera* camera);

		/* �폜
		// camera	:	�폜����J����
		// return	:	true. �����Afalse. ���s
		*/
		bool Delete(Camera* camera);

		/* �擾
		// Name	:	�擾����J�����̖��O
		// return	:	�Ή������J�����̃C���X�^���X
		*/
		Camera* Get(const std::string& Name);

		/* �Z�b�g
		// Name	:	�ݒ肷��J�����̖��O
		// return	:	true. �����Afalse. ���s
		*/
		bool Set(const std::string& Name);

		/* �Ō�Ɏg�p�������̂��擾
		// return	:	�Ή������J�����̃C���X�^���X
		*/
		Camera* CurrentCamera();
	};

	CameraManager* GetCameraManager();

};