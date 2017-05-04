//////////////////////////////////////////////////////////////
// SaveManagerBase �N���X
// 2016. 9. 24	�v���O�����쐬
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#pragma once


#include	"../Obj/SaveObjBase.h"
#include	<string>
#include	<vector>
#include	<fstream>

using namespace std;


class	ISaveObjBase;
struct	DATARECORD;

enum SAVE_FLAG {
	SAVE_OK,
	LOAD_OK,
	NO_SAVEFILE,
	CONNECT_OK,
};

#define	NO_ELEM		(-1)
#define	TYPE_END	(0)		// �I��
#define	TYPE_LOCAL	(1)		// ���[�J��
#define	TYPE_PTR	(2)		// �|�C���^
#define	TYPE_MEM	(3)		// �������u���b�N
#define	TYPE_BASE	(4)		// �e�N���X�f�[�^


#define	DATA_END										{	TYPE_END,	0,											0										}
#define	DATA_LOCAL( CLASSNAME, MEMBERNAME )				{	TYPE_LOCAL,	((__int64)&((CLASSNAME*)0)->MEMBERNAME),	sizeof( ((CLASSNAME*)0)->MEMBERNAME )	}
#define	DATA_PTR( CLASSNAME, MEMBERNAME )				{	TYPE_PTR,	((__int64)&((CLASSNAME*)0)->MEMBERNAME),	sizeof(int)								}
#define	DATA_MEM( CLASSNAME, POINTERNAME, SIZENAME )	{	TYPE_MEM,	((__int64)&((CLASSNAME*)0)->POINTERNAME),	((__int64)&((CLASSNAME*)0)->SIZENAME)	}
#define	DATA_BASE( TABLEPTR )							{	TYPE_BASE,	((__int64)TABLEPTR),						0										}


class	SaveManagerBase {
protected:
#pragma region variable

	vector<ISaveObjBase*>	m_ObjList;
	fstream	m_fs;

#pragma endregion

public:
#pragma region method

	SaveManagerBase(void) {};
	virtual ~SaveManagerBase(void) {};

	/////////////////////////////////////////////////////////
	// �O�Ŏg�p����̂͂�������
	int Save(const string filename);		// �Z�[�u
	int Load(const string filename);		// ���[�h
	void AddSaveData(ISaveObjBase* pobj);	// �Z�[�u�I�u�W�F�N�g�ǉ�
	/////////////////////////////////////////////////////////

	int Write(DATARECORD* list, ISaveObjBase* pobj);
	int Read(DATARECORD* list, ISaveObjBase* pobj);
	int ConnectPtr(DATARECORD* list, ISaveObjBase* pobj);	// �I�u�W�F�N�g�̃|�C���^������

#pragma endregion

protected:
#pragma region conceal method

	int LoadSkip();									// �ǂݍ��݃f�[�^��1�X�L�b�v
	int ElemFromPtr(void* pos);						// �|�C���^��v�f�ԍ��ɕϊ�
	virtual ISaveObjBase* CreateObj(int classID);	// �I�u�W�F�N�g����

#pragma endregion
};