//	�Z��
// 2016. 7.11	�v���O�����쐬
// �Q�l�T�C�g	http://marupeke296.com/COLSmp_3D_No3_Octree.html

#pragma once


#include	<Windows.h>
#include	<vector>
#include	<list>

#include	"../Convert/Convert.h"


/*
	MEMO	:
			CCell�N���X�̃f�X�g���N�^�ł��艟�������Ă���̂ŗv����
*/


namespace MSLib {

	template <class T>
	class CCell;


	//----- ���ؓo�^�I�u�W�F�N�g
	template <class T>
	class	OBJECT_FOR_TREE {
	public:
#pragma region variable

		CCell<T>	*m_pCell;			// �o�^���
		T	*m_pObject;					// ����ΏۃI�u�W�F�N�g
		OBJECT_FOR_TREE<T>*	m_pPre;		// �O��OBJECT_FOR_TREE�\����
		OBJECT_FOR_TREE<T>*	m_pNext;	// ����			�V			
		int	m_id;

#pragma endregion

	public:
#pragma region method

		OBJECT_FOR_TREE(int id = 0) {
			m_id = id;
			m_pCell = nullptr;
			m_pObject = nullptr;
			m_pPre = nullptr;
			m_pNext = nullptr;
		}

		virtual ~OBJECT_FOR_TREE() {}

		// ��Ԃ�o�^
		void RegistCell(CCell<T>* pCell) {
			m_pCell = pCell;
		}

		// ���烊�X�g����O���
		bool Remove() {
			// ���łɈ�E���Ă��鎞�͏����I��
			if (!m_pCell)
				return false;

			// ������o�^���Ă����ԂɎ��M��ʒm
			if (!m_pCell->OnRemove(this))
				return false;

			// ��E����
			// �O��̃I�u�W�F�N�g�����т���
			if (m_pPre != nullptr) {
				m_pPre->m_pNext = m_pNext;
				m_pPre = nullptr;
			}
			if (m_pNext != nullptr) {
				m_pNext->m_pPre = m_pPre;
				m_pNext = nullptr;
			}
			m_pCell = nullptr;
			return true;
		}

		// ���̃I�u�W�F�N�g�ւ̃X�}�[�g�|�C���^���擾
		OBJECT_FOR_TREE<T>* GetNextObj() {
			return m_pNext;
		}

#pragma endregion
	};

	//----- ���`4���؋�ԊǗ��N���X
#define	CLINER4TREEMANAGER_MAXLEVEL		9
	template <class T>
	class	CLiner4TreeManager {
	protected:
#pragma region variable

		unsigned int	m_uiDim;
		CCell<T>**		ppCellAry;		// ���`��ԃ|�C���^�z��
		unsigned int	m_iPow[CLINER4TREEMANAGER_MAXLEVEL + 1];	// �ׂ��搔�l�z��
		float			m_fW;			// �̈��X����
		float			m_fH;			// �̈��Y����
		float			m_fLeft;		// �̈�̍����iX���ŏ��l�j
		float			m_fTop;			// �̈�̏㑤�iY���ŏ��l�j
		float			m_fUnit_W;		// �ŏ����x����Ԃ̕��P��
		float			m_fUnit_H;		// �ŏ����x����Ԃ̍��P��
		DWORD			m_dwCellNum;	// ��Ԃ̐�
		unsigned int	m_uiLevel;		// �ŉ��ʃ��x��

#pragma endregion

	public:
#pragma region method

		// �R���X�g���N�^
		CLiner4TreeManager() {
			m_uiLevel = 0;
			m_fW = 0.0f;
			m_fH = 0.0f;
			m_fLeft = 0.0f;
			m_fTop = 0.0f;
			m_fUnit_W = 0.0f;
			m_fUnit_H = 0.0f;
			m_dwCellNum = 0;
			ppCellAry = nullptr;
			m_uiDim = 0;
		}

		// �f�X�g���N�^
		virtual ~CLiner4TreeManager() {
			DWORD i;
			for (i = 0; i < m_dwCellNum; i ++) {
				if (ppCellAry[i] != nullptr) {
					delete ppCellAry[i];
					ppCellAry[i] = nullptr;
				}
				delete[] ppCellAry;
				ppCellAry = nullptr;
			}
		}

		// ���`4���ؔz����\�z����
		bool Init(unsigned int Level, float left, float top, float right, float bottom) {
			// �ݒ�ō����x���ȏ�̋�Ԃ͍��Ȃ�
			if (Level >= CLINER4TREEMANAGER_MAXLEVEL)
				return false;

			// �e���x���ł̋�Ԑ����Z�o
			int i;
			m_iPow[0] = 1;
			for (i = 1; i < CLINER4TREEMANAGER_MAXLEVEL + 1; i ++)
				m_iPow[i] = m_iPow[i - 1] * 4:

			// Level���x���i0��_�j�̔z��쐬
			m_dwCellNum = (m_iPow[Level + 1] - 1) / 3;
			ppCellAry = new CCell<T>*[m_dwCellNum];
			ZeroMemory(ppCellAry, sizeof(CCell<T>*)*m_dwCellNum);

			// �̈��o�^
			m_fLeft = left;
			m_fTop = top;
			m_fW = right - left;
			m_fH = bottom - top;
			m_fUnit_W = m_fW / (1 << Level);
			m_fUnit_H = m_fH / (1 << Level);

			m_uiLevel = level;

			return true;
		}

		// �I�u�W�F�N�g��o�^����
		bool Regist(float left, float top, float right, float bottom, OBJECT_FOR_TREE<T>* pOFT) {
			// �I�u�W�F�N�g�̋��E�͈͂���o�^���[�g���ԍ����Z�o
			DWORD Elem = GetMortonNumber(left, top, right, bottom);
			if (Elem < m_dwCellNum) {
				// ��Ԃ��Ȃ��ꍇ�͐V�K�o�^
				if (!ppCellAry[Elem])
					CreateNewCell(Elem);
				return ppCellAry[Elem]->Push(pOFT);
			}
			return false;	// �o�^���s
		}

		// �Փ˔��胊�X�g
		DWORD GetAllCollisionList(std::vector<T*> &ColVect) {
			// ���X�g�i�z��j�͕K�����������܂�
			ColVect.clear();

			// ���[�g��Ԃ̑��݂��`�F�b�N
			if (ppCellAry[0] == nullptr)
				return 0;	// ��Ԃ����݂��Ă��Ȃ�

			// ���[�g��Ԃ�����
			std::list<T*> ColStac;
			GetCollisionList(0. ColVect, ColStac);

			return (DWORD)ColVect.size();
		}

#pragma endregion

	protected:
#pragma region conceal method

		// ��ԓ��ŏՓ˃��X�g���쐬����
		bool GetCollisionList(DWORD Elem, std::vector<T*> &ColVect, std::list<T*> &ColStac) {
			std::list<T*>::iterator it;
			// �@��ԓ��̃I�u�W�F�N�g���m�̏Փ˃��X�g�쐬
			OBJECT_FOR_TREE<T>* pOFT1 = ppCellAry[Elem]->GetFirstObj();
			while (pOFT1) {
				OBJECT_FOR_TREE<T>* pOFT2 = pOFT1->m_pNext;
				while (pOFT2) {
					// �Փ˃��X�g�쐬
					ColVect.push_back(pOFT1->m_pObject);
					ColVect.push_back(pOFT2->m_pObject);
					pOFT2 = pOFT2->m_pNext;
				}
				// �A�Փ˃X�^�b�N�Ƃ̏Փ˃��X�g�쐬
				for (it = ColStac.begin(); it != ColStac.end(); it ++) {
					ColVect.push_back(pOFT1->m_pObject);
					ColVect.push_back(*it);
				}
				pOFT1 = pOFT1->m_pNext;
			}

			bool ChildFlg = false;
			// �B�q��ԂɈړ�
			DWORD ObjNum = 0;
			DWORD i, NextElem;
			for (i = 0; i < 4; i ++) {
				NextElem = Elem * 4 + 1 + i;
				if (NextElem < m_dwCellNum && ppCellAry[Elem * 4 + 1 + i]) {
					if (!ChildFlg) {
						// �C�o�^�I�u�W�F�N�g���X�^�b�N�ɒǉ�
						pOFT1 = ppCellAry[Elem]->GetFirstObj();
						while (pOFT1) {
							ColStac.push_back(pOFT1->m_pObject);
							ObjNum++;
							pOFT1 = pOFT1->m_pNext;
						}
					}
					ChildFlg = true;
					GetCollisionList(Elem * 4 + 1 + i, ColVect, ColStac);	// �q��Ԃ�
				}
			}

			// �D�X�^�b�N����I�u�W�F�N�g���O��
			if (ChildFlg) {
				for (i = 0; i < ObjNum; i ++) {
					ColStac.pop_back();
				}
			}

			return true;
		}

		// ��Ԃ𐶐�
		bool CreateNewCell(DWORD Elem) {
			// �����̗v�f�ԍ�
			while (!ppCellAry[Elem]) {
				// �w��̗v�f�ԍ��ɋ�Ԃ�V�K���H��
				ppCellAry[Elem] = new CCell<T>;

				// �e��ԂɃW�����v
				Elem = (Elem - 1) >> 2;
				if (Elem >= m_dwCellNum) break;
			}
			return true;
		}

		// ���W�����Ԕԍ����Z�o
		DWORD GetMortonNumber(float left, float top, float right, float bottom) {
			// �ŏ����x���ɂ�����e���ʒu���Z�o
			DWORD LT = GetPointElem(left, top);
			DWORD RB = GetPointElem(right, bottom);

			// ��Ԕԍ��������Z����
			// �ŏ�ʋ�؂肩�珊�����x�����Z�o
			DWORD Def = RB ^ LT;
			unsigned int HiLevel = 0;
			unsigned int i;
			for (i = 0; i < m_uiLevel; i ++) {
				DWORD Check = (Def >> (i * 2)) & 0x3;
				if (Check != 0)
					HiLevel = i + 1;
			}
			DWORD SpaceNum = RB >> (HiLevel * 2);
			DWORD AddNum = (m_iPow[m_uiLevel - HiLevel] - 1) / 3;
			SpaceNum += AddNum;

			if (SpaceNum > m_dwCellNum)
				return 0xffffffff;

			return SpaceNum;
		}

		// �r�b�g�����֐�
		DWORD BitSeparate32(DWORD n) {
			n = (n | (n << 8)) & 0x00ff00ff;	// 0000 0000 abcd efgh
			n = (n | (n << 4)) & 0x0f0f0f0f;	// 0000 abcd 0000 efgh
			n = (n | (n << 2)) & 0x33333333;	// 00ab 00cd 00ef 00gh
			return (n | (n << 1)) & 0x55555555;	// 0a0b 0c0d 0e0f 0g0h
		}

		// 2D���[�g����Ԕԍ��Z�o�֐�
		WORD Get2DMortonNumber(WORD x, WORD y) {
			return (WORD)(BitSeparate32(x) | (BitSeparate32(y) << 1));
		}

		// ���W�����`4���ؗv�f�ԍ��ϊ��֐�
		DWORD GetPointElem(float pos_x, float pos_y) {
			return Get2DMortonNumber(
				(WORD)((pos_x - m_fLeft) / m_fUnit_W),
				(WORD)((pos_y - m_fTop) / m_fUnit_H));
		}

#pragma endregion
	};


	//----- ���`8���؋�ԊǗ��N���X
#define	CLINER8TREEMANAGER_MAXLEVEL		7
	template <class T>
	class	CLiner8TreeManager {
	protected:
#pragma region variable

		unsigned int	m_uiDim;
		CCell<T>**		ppCellAry;		// ���`��ԃ|�C���^�z��
		unsigned int	m_iPow[CLINER8TREEMANAGER_MAXLEVEL + 1];	// �ׂ��搔�l�z��
		Vector3			m_vW;			// �̈�̕�
		Vector3			m_vRgnMin;		// �̈�̍ŏ��l
		Vector3			m_vRgnMax;		// �̈�̍ő�l
		Vector3			m_vUnit;		// �ŏ��̈�̕ӂ̒���
		DWORD			m_dwCellNum;	// ��Ԃ̐�
		unsigned int	m_uiLevel;		// �ŉ��ʃ��x��

#pragma endregion

	public:
#pragma region method

		// �R���X�g���N�^
		CLiner8TreeManager() {
			m_uiDim = 0;
			ppCellAry = nullptr;
			m_vW.x = m_vW.y = m_vW.z = 1.0f;
			m_vRgnMin.x = m_vRgnMin.y = m_vRgnMin.z = 0.0f;
			m_vRgnMax.x = m_vRgnMax.y = m_vRgnMax.z = 1.0f;
			m_vUnit.x = m_vUnit.y = m_vUnit.z = 1.0f;
			m_dwCellNum = 0;
			m_uiLevel = 0;
		}

		// �f�X�g���N�^
		virtual ~CLiner8TreeManager() {
			for (DWORD i = 0; i < m_dwCellNum; i ++) {
				if (ppCellAry[i] != nullptr) {
					delete ppCellAry[i];
					ppCellAry[i] = nullptr;
				}
			}
			delete[] ppCellAry;
			ppCellAry = nullptr;
		}

		// ���`4���ؔz����\�z����
		bool Init(unsigned int Level, Vector3& Min, Vector3& Max) {
			// �ݒ�ō����x���ȏ�̋�Ԃ͍��Ȃ�
			if (Level >= CLINER8TREEMANAGER_MAXLEVEL)
				return false;

			// �e���x���ł̋�Ԑ����Z�o
			int i;
			m_iPow[0] = 1;
			for (i = 1; i < CLINER8TREEMANAGER_MAXLEVEL + 1; i ++)
				m_iPow[i] = m_iPow[i - 1] * 8;

			// Level���x���i0��_�j�̔z��쐬
			m_dwCellNum = (m_iPow[Level + 1] - 1) / 7;
			ppCellAry = new CCell<T>*[m_dwCellNum];
			ZeroMemory(ppCellAry, sizeof(CCell<T>*)*m_dwCellNum);

			// �̈��o�^
			m_vRgnMin = Min;
			m_vRgnMax = Max;
			m_vW = m_vRgnMax - m_vRgnMin;
			m_vUnit = m_vW / ((float)(1 << Level));

			m_uiLevel = Level;

			return true;
		}

		// �I�u�W�F�N�g��o�^����
		bool Regist(Vector3* Min, Vector3* Max, OBJECT_FOR_TREE<T>* pOFT) {
			// �I�u�W�F�N�g�̋��E�͈͂���o�^���[�g���ԍ����Z�o
			DWORD Elem = GetMortonNumber(Min, Max);
			if (Elem < m_dwCellNum) {
				// ��Ԃ��Ȃ��ꍇ�͐V�K�o�^
				if (!ppCellAry[Elem])
					CreateNewCell(Elem);
				return ppCellAry[Elem]->Push(pOFT);
			}
			return false;	// �o�^���s
		}

		// �Փ˔��胊�X�g
		DWORD GetAllCollisionList(std::vector<T> &ColVect) {
			// ���X�g�i�z��j�͕K�����������܂�
			ColVect.clear();

			// ���[�g��Ԃ̑��݂��`�F�b�N
			if (!ppCellAry[0])
				return 0;	// ��Ԃ����݂��Ă��Ȃ�

			// ���[�g��Ԃ�����
			std::list<T> ColStac;
			GetCollisionList(0, ColVect, ColStac);

			return (DWORD)ColVect.size();
		}

#pragma endregion

	protected:
#pragma region conceal method

		// ��ԓ��ŏՓ˃��X�g���쐬����
		bool GetCollisionList(DWORD Elem, std::vector<T> &ColVect, std::list<T> &ColStac) {
			std::list<T>::iterator it;
			// �@��ԓ��̃I�u�W�F�N�g���m�̏Փ˃��X�g�쐬
			OBJECT_FOR_TREE<T>* pOFT1 = ppCellAry[Elem]->GetFirstObj();
			while (pOFT1) {
				OBJECT_FOR_TREE<T>* pOFT2 = pOFT1->m_pNext;
				while (pOFT2) {
					// �Փ˃��X�g�쐬
					if (pOFT1->m_pObject != nullptr)
						ColVect.push_back(*pOFT1->m_pObject);
					if (pOFT2->m_pObject != nullptr)
						ColVect.push_back(*pOFT2->m_pObject);
					pOFT2 = pOFT2->m_pNext;
				}
				// �A�Փ˃X�^�b�N�Ƃ̏Փ˃��X�g�쐬
				for (it = ColStac.begin(); it != ColStac.end(); it ++) {
					ColVect.push_back(*pOFT1->m_pObject);
					ColVect.push_back(*it);
				}
				pOFT1 = pOFT1->m_pNext;
			}

			bool ChildFlg = false;
			// �B�q��ԂɈړ�
			DWORD ObjNum = 0;
			DWORD i, NextElem;
			for (i = 0; i < 8; i ++) {
				NextElem = Elem * 8 + 1 + i;
				if (NextElem < m_dwCellNum && ppCellAry[Elem * 8 + 1 + i]) {
					if (!ChildFlg) {
						// �C�o�^�I�u�W�F�N�g���X�^�b�N�ɒǉ�
						pOFT1 = ppCellAry[Elem]->GetFirstObj();
						while (pOFT1) {
							ColStac.push_back(*pOFT1->m_pObject);
							ObjNum++;
							pOFT1 = pOFT1->m_pNext;
						}
					}
					ChildFlg = true;
					GetCollisionList(Elem * 8 + 1 + i, ColVect, ColStac);	// �q��Ԃ�
				}
			}

			// �D�X�^�b�N����I�u�W�F�N�g���O��
			if (ChildFlg) {
				for (i = 0; i < ObjNum; i ++) {
					ColStac.pop_back();
				}
			}

			return true;
		}

		// ��Ԃ𐶐�
		bool CreateNewCell(DWORD Elem) {
			// �����̗v�f�ԍ�
			while (!ppCellAry[Elem]) {
				// �w��̗v�f�ԍ��ɋ�Ԃ�V�K���H��
				ppCellAry[Elem] = new CCell<T>;

				// �e��ԂɃW�����v
				Elem = (Elem - 1) >> 3;
				if (Elem >= m_dwCellNum) break;
			}
			return true;
		}

		// ���W�����Ԕԍ����Z�o
		DWORD GetMortonNumber(Vector3* Min, Vector3* Max) {
			// �ŏ����x���ɂ�����e���ʒu���Z�o
			DWORD LT = GetPointElem(*Min);
			DWORD RB = GetPointElem(*Max);

			// ��Ԕԍ��������Z����
			// �ŏ�ʋ�؂肩�珊�����x�����Z�o
			DWORD Def = RB ^ LT;
			unsigned int HiLevel = 1;
			unsigned int i;
			for (i = 0; i < m_uiLevel; i ++) {
				DWORD Check = (Def >> (i * 3)) & 0x7;
				if (Check != 0)
					HiLevel = i + 1;
			}
			DWORD SpaceNum = RB >> (HiLevel * 3);
			DWORD AddNum = (m_iPow[m_uiLevel - HiLevel] - 1) / 7;
			SpaceNum += AddNum;

			if (SpaceNum > m_dwCellNum)
				return 0xffffffff;

			return SpaceNum;
		}

		// �r�b�g�����֐�
		DWORD BitSeparateFor3D(BYTE n) {
			DWORD s = n;
			s = (s | (s << 8)) & 0x0000f00f;
			s = (s | (s << 4)) & 0x000c30c3;
			s = (s | (s << 2)) & 0x00249249;
			return s;
		}

		// 3D���[�g����Ԕԍ��Z�o�֐�
		DWORD Get3DMortonNumber(BYTE x, BYTE y, BYTE z) {
			return BitSeparateFor3D(x) | BitSeparateFor3D(y) << 1 | BitSeparateFor3D(z) << 2;
		}

		// ���W�����`8���ؗv�f�ԍ��ϊ��֐�
		DWORD GetPointElem(Vector3& p) {
			return Get3DMortonNumber(
				(BYTE)((p.x - m_vRgnMin.x) / m_vUnit.x),
				(BYTE)((p.y - m_vRgnMin.y) / m_vUnit.y),
				(BYTE)((p.z - m_vRgnMin.z) / m_vUnit.z));
		}

#pragma endregion
	};


	//----- ��ԃN���X
	template <class T>
	class	CCell {
	protected:
		OBJECT_FOR_TREE<T>*	m_pLatest;	// �ŐVOFT�ւ̃|�C���^

	public:
#pragma region method

		// �R���X�g���N�^
		CCell() {
			ZeroMemory(&m_pLatest, sizeof(m_pLatest));
			//		m_pLatest = NULL;
		}

		// �f�X�g���N�^
		virtual ~CCell() {
			// �����őS������
	//		if( m_pLatest )
	//			ResetLink(m_pLatest);
		}

		// �����N��S�ă��Z�b�g
		void ResetLink(OBJECT_FOR_TREE<T>* pOFT) {
			//		if (pOFT == 0xDDDDDDDD)	return;
			if (pOFT->m_pNext)
				ResetLink(pOFT->m_pNext);
			pOFT->m_pNext = nullptr;
		}

		// OFT���v�b�V��
		bool Push(OBJECT_FOR_TREE<T>* pOFT) {
			if (!pOFT)					return false;	// �C���X�^���X��������
			if (pOFT->m_pCell == this)	return false;	// 2�d�o�^�`�F�b�N
			if (!m_pLatest) {
				m_pLatest = pOFT;	// ��ԂɐV�K�o�^
			} else {
				// �ŐVOFT�I�u�W�F�N�g���X�V
				pOFT->m_pNext = m_pLatest;
				m_pLatest->m_pPre = pOFT;
				m_pLatest = pOFT;
			}
			pOFT->RegistCell(this);	// ��Ԃ�o�^
			return true;
		}

		OBJECT_FOR_TREE<T>* GetFirstObj() {
			return m_pLatest;
		}

		// �폜�����I�u�W�F�N�g���`�F�b�N
		bool OnRemove(OBJECT_FOR_TREE<T>* pRemoveObj) {
			// ��ԑO�������I�u�W�F�N�g���m�F
			if (m_pLatest == pRemoveObj) {
				// ���̃I�u�W�F�N�g�ɑ}���ւ�
				if (m_pLatest)
					m_pLatest = m_pLatest->GetNextObj();
			}
			return true;
		}

#pragma endregion
	};

};