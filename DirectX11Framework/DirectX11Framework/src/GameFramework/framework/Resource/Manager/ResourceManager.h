// ���\�[�X�}�l�[�W���[
// 2017.04.24	: �v���O�����쐬
// author		: SyunMizuno


#pragma once

#include	"../Base/IResource.h"
#include	<map>
#include	"../../Utility/System/SystemUtility.h"
#include	"../../Debug/Debug.h"
#include	<typeinfo>
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

	/* �R���X�g���N�^ */
	ResourceManager() :
		m_bHelper(true)
	{
		m_MapResources.clear();
		SetHelper(m_bHelper);
	}

	/* �f�X�g���N�^ */
	virtual ~ResourceManager() {
		if (!m_bHelper)	return;

		map<string, T*>::iterator it = m_MapResources.begin();

		// �S�v�f�폜
		while (it != m_MapResources.end()) {
			SAFE_DELETE(it->second);
			++it;
		}

		m_MapResources.clear();
	}

	/* �쐬
	// name		: �쐬�������t�@�C����
	// return	: ���������C���X�^���X
	*/
	T* Create(const string name) {
		if (name.empty()) {
			Debug::LogError("�t�@�C����������܂���");
			return nullptr;
		}

		// �o�^�ς݂��m�F
		if (m_MapResources.end() != m_MapResources.find(name)) {
			Debug::Log("���\�[�X : " + name + " �͊��ɍ쐬�ς݂ł�");
			return Get(name);
		}

		T* resource = new T;
		if (!resource->Create(name)) {
			Debug::LogError("���\�[�X : " + name + " �̍쐬�Ɏ��s���܂���");
			SAFE_DELETE(resource);
			return nullptr;
		}

		// �o�^
		Debug::Log(string(typeid(T).name()) + " : " + name + " ���쐬");
		m_MapResources.insert(pair<string, T*>(name, resource));

		return resource;
	}

	/* �폜
	// name		: �폜�������t�@�C����
	// return	: true. �����A false. ���s
	*/
	bool Delete(const string name) {
		// ����
		auto it = m_MapResources.find(name);

		// �o�^�m�F
		if (it == m_MapResources.end()) {
			Debug::Log("���\�[�X : " + name + " �͓o�^����Ă��Ȃ����ߍ폜�ł��܂���");
			return false;
		}

		// �폜
		it->second->Delete();
		SAFE_DELETE(it->second);

		m_MapResources.erase(name)

		return true;
	}

	/* �擾
	// name		: �擾�������t�@�C����
	// return	: ���������C���X�^���X
	*/
	T* Get(const string name) {
		// ����
		auto it = m_MapResources.find(name);

		if (it == m_MapResources.end()) {
			return Create(name);
		}

		return it->second;
	}

	/* �⏕�@�\�ݒ�
	// helper	: �⏕�@�\ ON : OFF
	*/
	void SetHelper(bool helper) {
		const type_info& id = typeid(T);
		string swit = (helper ? "ON" : "OFF");
		Debug::Log("ResourceManager<" + string(typeid(T).name()) + ">�̕⏕�@�\ �F " + swit);

		m_bHelper = helper;
	}

#pragma endregion
};


template<class T>
inline ResourceManager<T>* GetResourceManager() {
	return ResourceManager<T>::Instance();
}