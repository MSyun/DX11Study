// �J�����}�l�[�W���[
// 2017.05.15	: �v���O�����쐬
// author		: SyunMizuno


#pragma once


#include	<map>
#include	<string>
#include	"../Camera.h"
#include	"../../Singleton/Singleton.h"


class CameraManager	:	public	Singleton<CameraManager> {
protected:
	map<string, Camera*>	m_MapCamera;
	bool	m_bHelper;

	string m_CurCameraName;

public:
	CameraManager();
	virtual ~CameraManager();

	/* �쐬
	// Name	:	��������J�����̖��O
	// return	: ���������J�����̃I�u�W�F�N�g
	*/
	Camera* Create(const string Name);

	/* �폜
	// Name	:	�폜����J�����̖��O
	// return	:	true. �����Afalse. ���s
	*/
	bool Delete(const string Name);

	/* �擾
	// Name	:	�擾����J�����̖��O
	// return	:	�Ή������J�����̃C���X�^���X
	*/
	Camera* Get(const string Name);

	/* �Z�b�g
	// Name	:	�ݒ肷��J�����̖��O
	// return	:	true. �����Afalse. ���s
	*/
	bool Set(const string Name);

	/* �Ō�Ɏg�p�������̂��擾
	// return	:	�Ή������J�����̃C���X�^���X
	*/
	Camera* CurrentCamera();

	/* �Ǘ��I�u�W�F�N�g�������ō폜���邩�ݒ� */
	void SetHelper(bool helper);
};

CameraManager* GetCameraManager();