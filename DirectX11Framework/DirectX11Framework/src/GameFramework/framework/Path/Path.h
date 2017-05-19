// �p�X�֘A
// 2017.05.12	: �v���O�����쐬
// author		: SyunMizuno

#pragma once


#include	<string>


namespace MSLib {
	namespace Path {

		/* �f�B���N�g���𒊏o
		// path		: �p�X
		// return	: �f�B���N�g��
		*/
		std::string GetDirectoryName(const std::string& path);

		/* �g���q�𒊏o
		// path		: �p�X
		// return	: �g���q
		*/
		std::string GetExtension(const std::string& path);

		/* �t�@�C�����𒊏o
		// path		: �p�X
		// return	: �t�@�C����
		*/
		std::string GetFileName(const std::string& path);

	}
}