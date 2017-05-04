//////////////////////////////////////////////////////////////
// CSaveObjBase �N���X
// 2016. 9. 24	�v���O�����쐬
// 2016. 9. 27	�R�����g�ǉ�
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#include	"SaveManagerBase.h"
#include	"../Factory/SaveFactory.h"


/*
	memo	:
			���t�@�N�^�����O�K�{
*/


/*									//
//		�Z�[�u�I�u�W�F�N�g��o�^	//
//									*/
void SaveManagerBase::AddSaveData(ISaveObjBase* pobj) {
	// ���ԃ`�F�b�N
	if (!pobj)	return;

	// �o�^
	m_ObjList.push_back(pobj);
}


/*									//
//				�Z�[�u				//
//									*/
int SaveManagerBase::Save(const string filename) {
	// �Z�[�u�t�@�C���I�[�v��
	m_fs.open(filename.c_str(), ios_base::out | ios_base::binary);
	if (!m_fs.is_open())
		return 0;

	// �f�[�^�̏�������
	for (auto it = m_ObjList.begin(); it != m_ObjList.end(); it ++)
		(*it)->Save(this);

	m_fs.close();

	return SAVE_OK;	// �Z�[�u����
}


/*									//
//				���[�h				//
//									*/
int SaveManagerBase::Load(const string filename ) {
	// �Z�[�u�t�@�C���I�[�v��
	m_fs.open( filename.c_str(), ios_base::in | ios_base::binary );
	if( !m_fs.is_open() )
		return NO_SAVEFILE;

	while( !m_fs.eof() ) {
		// �f�[�^�̓ǂݍ���
		// �N���XID�̎擾
		int ClassID;
		m_fs.read( (char*)&ClassID, sizeof(int) );

		// �ǂݍ��ݎ��ɃG���[���N�����ꍇ�̓��[�h���I������
		if( m_fs.fail() != 0 )	break;

		// �w��N���XID�̃I�u�W�F�N�g�𐶐����ĕێ�
		ISaveObjBase* pobj = CreateObj( ClassID );
		AddSaveData( pobj );

		// �I�u�W�F�N�g�������ꍇ�̓f�[�^���΂�
		if( !pobj ) { LoadSkip(); continue; }

		// �I�u�W�F�N�g�����[�h
		pobj->Load( this );
	}

	for( auto it = m_ObjList.begin(); it != m_ObjList.end(); it ++ ) {
		// �I�u�W�F�N�g�̃|�C���^���Ȃ���
		if( *it )
			(*it)->ConnectPtr( this );
	}

	m_fs.close();

	return LOAD_OK;	// ���[�h����
}


/*									//
//			�ǂݍ��݃f�[�^��		//
//		1�I�u�W�F�N�g���X�L�b�v		*/
int SaveManagerBase::LoadSkip() {
	int type, size;
	while (!m_fs.eof()) {
		m_fs.read((char*)&type, sizeof(char));	// �f�[�^�^�C�v
		if (type == TYPE_END)
			break;
		m_fs.read((char*)&size, sizeof(int));		// �f�[�^�T�C�Y
		m_fs.ignore(size);							// �T�C�Y���f�[�^���΂�
	}

	return 1;
}


/*									//
//			�t�@�N�g���֐�			//
//		�i�����͌p�����邱�ƑO��j	*/
ISaveObjBase* SaveManagerBase::CreateObj(int classID) {
	return SaveFactory::Create(classID);	// �w��̃N���X���Ȃ�
}


/*									//
//			�f�[�^��������			//
//									*/
int SaveManagerBase::Write(DATARECORD* list, ISaveObjBase* pobj) {
	// �N���XID�̏�������
	int ID = pobj->GetClassID();
	m_fs.write((char*)&ID, sizeof(int));

	while (list->type != TYPE_END) {
		// �f�[�^�̈ʒu���Z�o
//		char* pos = (char*)pobj + list->offset;
		char* pos;
		int Elem;
		void* p;
		char* sizepos;
		int size;
		char* pmem;

		// �f�[�^�^�C�v�ƃT�C�Y�̏�������
		m_fs.write((char*)&list->type, sizeof(char));	// �f�[�^�^�C�v
//		m_fs.write( (char*)&list->size, sizeof(int) );	// �f�[�^�T�C�Y

		switch (list->type) {
			// �ʏ�ϐ�
		case TYPE_LOCAL:
			pos = (char*)pobj + list->offset;
			m_fs.write((char*)&list->size, sizeof(int));	// �f�[�^�T�C�Y
			m_fs.write((char*)pos, list->size);			// �f�[�^�{��
			break;

			// �|�C���^�ϐ�
		case TYPE_PTR:
			pos = (char*)pobj + list->offset;
			m_fs.write((char*)&list->size, sizeof(int));	// �f�[�^�T�C�Y
			p = (void*)*(__int64*)pos;
			Elem = ElemFromPtr(p);		// �|�C���^��v�f�ԍ��ɕϊ�
			m_fs.write((char*)&Elem, list->size);	// �f�[�^�{��
			break;

		case TYPE_MEM:
			pos = (char*)pobj + list->offset;
			sizepos = (char*)pobj + list->size;
			size = *(int*)(sizepos);
			m_fs.write((char*)&size, sizeof(int));	// �f�[�^�T�C�Y
			pmem = (char*)(*(int*)(pos));
			m_fs.write(pmem, size);
			break;

		case TYPE_BASE:
			Write((DATARECORD*)(list->offset), pobj);
			break;
		};

		// ���̃��X�g��
		list++;
	}

	// �Z�p���[�^��1�͂���
	char sep = TYPE_END;
	m_fs.write((char*)&sep, sizeof(char));

	return SAVE_OK;
}


/*									//
//			�f�[�^�ǂݍ���			//
//									*/
int SaveManagerBase::Read(DATARECORD* list, ISaveObjBase* pobj) {
	while (list->type != TYPE_END) {
		// �ϐ��錾
		char *pos, *tmp;

		// �f�[�^�^�C�v���擾
		int type = 0, size = 0;
		m_fs.read((char*)&type, sizeof(char));

		switch (type) {
			// �ʏ�ϐ�
			// �|�C���^�ϐ�
		case TYPE_LOCAL:
		case TYPE_PTR:
			pos = (char*)pobj + list->offset;		// �I�u�W�F�N�g�������o�ϐ��̕ۑ��ʒu���Z�o
			m_fs.read((char*)&size, sizeof(int));	// �f�[�^�T�C�Y�擾
			m_fs.read(pos, list->size);			// �f�[�^�{��
			break;

			// �������u���b�N
		case TYPE_MEM:
			pos = (char*)pobj + list->offset;		// �I�u�W�F�N�g�������o�ϐ��̕ۑ��ʒu���Z�o
			m_fs.read((char*)&size, sizeof(int));	// �f�[�^�T�C�Y�擾
			// �T�C�Y���̃��������m��
			// pos�̐�͔C�ӂ̃|�C���^�ϐ��Ȃ̂�tmp�|�C���^�ƒu��
			// tmp��������Ƀf�[�^�𗬂�����
			// pos->tmp->[Data]
			tmp = new char[size];
			m_fs.read(tmp, size);
			*(int*)(pos) = (int)tmp;
			break;

			// �e�N���X�̃����o�ϐ�
		case TYPE_BASE:
			Read((DATARECORD*)(list->offset), pobj);
			break;
		};

		// ���̃��X�g��
		list++;
	}

	// �Z�p���[�g���΂�
	m_fs.ignore(sizeof(char));

	return LOAD_OK;
}


/*									//
//		�|�C���^��v�f�ԍ��ɕϊ�	//
//									*/
int SaveManagerBase::ElemFromPtr(void* pos) {
	int elem = 0;
	for (auto it = m_ObjList.begin(); it != m_ObjList.end(); it ++) {
		void* objptr = (void*)(*it);

		// �C���X�^���X����
		if (objptr == pos)
			return elem;

		elem ++;
	}

	return NO_ELEM;
}


/*									//
//	�I�u�W�F�N�g�̃|�C���^������	//
//									*/
int SaveManagerBase::ConnectPtr(DATARECORD* list, ISaveObjBase* pobj) {
	// �f�[�^�^�C�v���|�C���^���������ɂ͎w�肳��Ă���
	// �z��v�f�̃I�u�W�F�N�g�|�C���^��ϐ��ɗ�������
	while (list->type != TYPE_END) {
		if (list->type == TYPE_PTR) {
			// �ϐ��̃A�h���X���Z�o
			int* pos = (int*)((char*)pobj + list->offset);

			// �ϐ��Ɋi�[����Ă���v�f�ԍ����|�C���^�ɕϊ�
			int ObjID = *pos;
			if (ObjID != NO_ELEM) {
				*pos = (int)(m_ObjList[ObjID]);
			} else {
				*pos = NULL;
			}
		}

		list++;
	}

	return CONNECT_OK;
}