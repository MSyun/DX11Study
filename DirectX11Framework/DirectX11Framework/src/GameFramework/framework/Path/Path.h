// �p�X�֘A
// 2017.05.12	: �v���O�����쐬
// author		: SyunMizuno



#pragma once


#include	<string>
using namespace std;


namespace Path {

	/* �f�B���N�g���𒊏o
	// path		: �t�@�C����
	// return	: �f�B���N�g��
	*/
	string GetDirectoryName(const string& path);

	/* �g���q�𒊏o
	// path		: �t�@�C����
	// return	: �g���q
	*/
	string GetExtension(const string& path);

}