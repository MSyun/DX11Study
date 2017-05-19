#include	"ResourceManager.h"
#include	"../../Utility/System/SystemUtility.h"
#include	"../../Debug/Debug.h"
#include	<typeinfo>


namespace MSLib {

	template<class T>
	ResourceManager<T>::ResourceManager() :
		m_bHelper(true)
	{
		Debug::Log("ResourceManager<" + string(typeid(T).name()) + "> ���쐬");
		m_MapResources.clear();
		SetHelper(m_bHelper);
	}


	template<class T>
	ResourceManager<T>::~ResourceManager() {
		Debug::Log("ResourceManager<" + string(typeid(T).name()) + "> ���폜");
		if (!m_bHelper)	return;

		auto it = m_MapResources.begin();

		// �S�v�f�폜
		while (it != m_MapResources.end()) {
			SAFE_DELETE(it->second);
//			it->second.reset();
			++it;
		}

		m_MapResources.clear();
	}


	/*									//
	//				�쐬				//
	//									*/
	template<class T>
	T* ResourceManager<T>::Create(const std::string& name) {
//	std::shared_ptr<T> ResourceManager<T>::Create(const std::string& name) {
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
//		shared_ptr<T> ptr = make_shared<T>(resource);
//		m_MapResources.insert(pair<string, std::shared_ptr<T>>(name, ptr));

		return resource;
//		return ptr;
	}


	/*									//
	//				�폜				//
	//									*/
	template<class T>
	bool ResourceManager<T>::Delete(const std::string& name) {
		auto it = m_MapResources.find(name);

		// �o�^�m�F
		if (it == m_MapResources.end()) {
			Debug::Log("���\�[�X : " + name + " �͓o�^����Ă��Ȃ����ߍ폜�ł��܂���");
			return false;
		}

		// �폜
		it->second->Delete();
		SAFE_DELETE(it->second);
//		if (it->second->use_count() > 1) {
//			Debug::Log("���\�[�X : " + name + " �͎Q�Ƃ���Ă��邽�ߍ폜�ł��܂���");
//			return false;
//		}
//		it->second->reset();

		m_MapResources.erase(name);

		return true;
	}


	/*									//
	//				�擾				//
	//									*/
	template<class T>
	T* ResourceManager<T>::Get(const std::string& name) {
//	std::shared_ptr<T> ResourceManager<T>::Get(const std::string& name) {
		auto it = m_MapResources.find(name);

		if (it == m_MapResources.end()) {
			return Create(name);
		}

		return it->second;
	}


	/*									//
	//			�⏕�@�\�ݒ�			//
	//									*/
	template<class T>
	void ResourceManager<T>::SetHelper(bool helper) {
		string swit = (helper ? "ON" : "OFF");
		Debug::Log("ResourceManager<" + string(typeid(T).name()) + ">�̕⏕�@�\ �F " + swit);

		m_bHelper = helper;
	}


	/*									//
	//			�}�l�[�W���̎擾		//
	//									*/
	template<class T>
	inline ResourceManager<T>* GetResourceManager() {
		return ResourceManager<T>::Instance();
	}

}