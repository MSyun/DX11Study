#pragma once


#include	"../../Utility/System/SystemUtility.h"
#include	"../../Debug/Debug.h"
#include	<typeinfo>



template<class T>
ResourceManager<T>::ResourceManager() :
	m_bHelper(true)
{
	m_MapResources.clear();
	SetHelper(m_bHelper);
}


template<class T>
ResourceManager<T>::~ResourceManager() {
	if (!m_bHelper)	return;

	map<string, T*>::iterator it = m_MapResources.begin();

	// �S�v�f�폜
	while (it != m_MapResources.end()) {
		SAFE_DELETE(it->second);
		++it;
	}

	m_MapResources.clear();
}


template<class T>
T* ResourceManager<T>::Create(const string name) {
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


template<class T>
bool ResourceManager<T>::Delete(const string name) {
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


template<class T>
T* ResourceManager<T>::Get(const string name) {
	// ����
	auto it = m_MapResources.find(name);

	if (it == m_MapResources.end()) {
		return Create(name);
	}

	return it->second;
}


template<class T>
void ResourceManager<T>::SetHelper(bool helper) {
	const type_info& id = typeid(T);
	string swit = (helper ? "ON" : "OFF");
	Debug::Log("ResourceManager<" + string(typeid(T).name()) + ">�̕⏕�@�\ �F " + swit);

	m_bHelper = helper;
}


template<class T>
inline ResourceManager<T>* GetResourceManager() {
	return ResourceManager<T>::Instance();
}