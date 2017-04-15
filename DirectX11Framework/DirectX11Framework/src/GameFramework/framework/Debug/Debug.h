// Direct3D�f�o�b�O�t�H���g�N���X�錾��
// �쐬��		:	SyunMizuno
// 2015.11.28	:	�v���O�����쐬
// 2016. 1. 2	:	InvalidateDeviceObjects,RestoreDeviceObjects��ǉ�
// 2016.12.31	:	Log�֐��ǉ�
// 2017. 3.26	:	����������.cpp�ֈړ�
//  HP    : http://www.h6.dion.ne.jp/~game296o/index.html

#pragma once

#pragma warning( disable : 4996 )

#include	<d3dx9.h>
#include	<string>
#include	<stdlib.h>
#include	"../Convert/Convert.h"


/*
	memo:
		_stprintf��Unicode,ANCI�̗��Ή��A�L�\
		�C���^�[�t�F�[�X����鎖
*/


using namespace std;


class Debug {
public:
#pragma region method

	Debug();
	~Debug();

#pragma region Log
	// �G�f�B�^�[��Ƀ��O��\��
	static void Log(const string& message);
	static void Log(const Vector2& val);
	static void Log(const Vector3& val);
	static void Log(const Vector4& val);
	static void Log(const Quaternion& qua);
#pragma endregion

	// �G���[���O�̕\��
	// �G�f�B�^�[�������Ŏ~�܂�̂�F10�ŏꏊ���m�F���Ă�������
	static void LogError(const string& message);

	// �f�o�C�X���X�g
	static HRESULT InvalidateDeviceObjects();

	// �f�o�C�X���Z�b�g
	static HRESULT RestoreDeviceObjects();

#pragma endregion
};