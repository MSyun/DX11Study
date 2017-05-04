//////////////////////////////////////////////////////////////
// CSaveObjBase �N���X
// 2016. 9. 24	�v���O�����쐬
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#pragma once

#include	"../Manager/SaveManagerBase.h"


// �Z�[�u�f�[�^�I�t�Z�b�g�\����
struct DATARECORD {
	char	type;	// �f�[�^�^�C�v
	int		offset;	// �I�t�Z�b�g�l
	int		size;	// �T�C�Y
};


class	SaveManagerBase;

class	ISaveObjBase {
	friend class SaveManagerBase;

public:
	virtual DATARECORD* GetDataRecord() = 0;	// �f�[�^�z����擾
	virtual int GetClassID() = 0;				// �N���XID���擾

protected:
	virtual int Save(SaveManagerBase* mgr);
	virtual int Load(SaveManagerBase* mgr);
	int ConnectPtr(SaveManagerBase* mgr);
};