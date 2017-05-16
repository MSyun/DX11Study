// �A�[�J�C�u�p�C���^�[�t�F�[�X
// 2016. 5.16	:	�v���O�����쐬
// author		:	SyunMizuno


#pragma once


#include	<map>
#include	<string>
using namespace std;


namespace ArchivesCollection {

	template<typename T>
	class IArchivesType {
	protected:
		map<string, T>	m_Archives;

	public:
		IArchivesType();
		virtual ~IArchivesType();

		/* ����
		// name		: ������
		// return	: ���ʕ�
		*/
		T Find(const string name);

	protected:
		virtual void Create() = 0 {}

		/* �ǉ�
		// key		: �����L�[
		// regist	: �ǉ�
		*/
		void Add(string key, T regist);
	};

#include	"IArchivesType.inl"

}