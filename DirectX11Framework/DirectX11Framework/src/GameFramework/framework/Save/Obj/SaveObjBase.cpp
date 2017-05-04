//////////////////////////////////////////////////////////////
// CSaveObjBase �N���X
// 2016. 9. 24	�v���O�����쐬
// author		SyunMizuno
//////////////////////////////////////////////////////////////


#include	"SaveObjBase.h"


/*									//
//				�Z�[�u				//
//									*/
int ISaveObjBase::Save(SaveManagerBase* mgr) {
	return mgr->Write(GetDataRecord(), this);	// ��������
}


/*									//
//				���[�h				//
//									*/
int ISaveObjBase::Load(SaveManagerBase* mgr) {
	return mgr->Read(GetDataRecord(), this);	// �ǂݍ���
}


/*									//
//			�|�C���^�ڑ�			//
//									*/
int ISaveObjBase::ConnectPtr(SaveManagerBase* mgr) {
	return mgr->ConnectPtr(GetDataRecord(), this);
}