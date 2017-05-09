// ���\�[�X�}�l�[�W���[
// 2017.04.24	: �v���O�����쐬
// author		: SyunMizuno


#pragma once

#include	<map>
using namespace std;
#include	"../../Singleton/Singleton.h"


template<class T>
class ResourceManager	:	public	Singleton<ResourceManager<T>> {
protected:
#pragma region variable

	// ���\�[�X�}�b�v
	map<string, T*>	m_MapResources;

	// �폜�⏕�@�\
	bool m_bHelper;

#pragma endregion

public:
#pragma region method

	ResourceManager();

	virtual ~ResourceManager();

	/* �쐬
	// name		: �쐬�������t�@�C����
	// return	: ���������C���X�^���X
	*/
	T* Create(const string name);

	/* �폜
	// name		: �폜�������t�@�C����
	// return	: true. �����A false. ���s
	*/
	bool Delete(const string name);

	/* �擾
	// name		: �擾�������t�@�C����
	// return	: ���������C���X�^���X
	*/
	T* Get(const string name);

	/* �⏕�@�\�ݒ�
	// helper	: �⏕�@�\ ON : OFF
	*/
	void SetHelper(bool helper);

#pragma endregion
};

template<class T>
inline ResourceManager<T>* GetResourceManager();


#include	"ResourceManager.inl"