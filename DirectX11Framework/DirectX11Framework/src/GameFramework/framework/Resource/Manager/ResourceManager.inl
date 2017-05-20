
#include	"../../Utility/System/SystemUtility.h"
#include	"../../Debug/Debug.h"
#include	<typeinfo>


namespace MSLib {

	template<class T>
	ResourceManager<T>::ResourceManager() {
		Debug::Log("ResourceManager<" + string(typeid(T).name()) + "> ���쐬");
		m_MapResources.clear();
	}


	template<class T>
	ResourceManager<T>::~ResourceManager() {
		Debug::Log("ResourceManager<" + std::string(typeid(T).name()) + "> ���폜");

		auto it = m_MapResources.begin();

		// �S�v�f�폜
		while (it != m_MapResources.end()) {
			it->second.reset();
			++it;
		}

		m_MapResources.clear();
	}


	/*									//
	//				�쐬				//
	//									*/
	template<class T>
	std::shared_ptr<T> ResourceManager<T>::Create(const std::string& name) {
		if (name.empty()) {
			Debug::LogError("�t�@�C����������܂���");
		}

		// �o�^�ς݂��m�F
		auto it = m_MapResources.find(name);
		if (m_MapResources.end() != it) {
			Debug::Log("���\�[�X : " + name + " �͊��ɍ쐬�ς݂ł�");
			return it->second;
		}

		std::shared_ptr<T> ptr(new T);
		if(!ptr->Create(name)) {
			Debug::LogError("���\�[�X : " + name + " �̍쐬�Ɏ��s���܂���");
			ptr.reset();
		}

		// �o�^
		Debug::Log(std::string(typeid(T).name()) + " : " + name + " ���쐬");
		m_MapResources.insert(std::pair<std::string, std::shared_ptr<T>>(name, ptr));

		return ptr;
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
		if (it->second->use_count() > 1) {
			Debug::Log("���\�[�X : " + name + " �͎Q�Ƃ���Ă��邽�ߍ폜�ł��܂���");
			return false;
		}
		it->second->reset();

		m_MapResources.erase(name);

		return true;
	}


	/*									//
	//				�擾				//
	//									*/
	template<class T>
	std::shared_ptr<T> ResourceManager<T>::Get(const std::string& name) {
		auto it = m_MapResources.find(name);

		if (it == m_MapResources.end()) {
			return Create(name);
		}

		return it->second;
	}


	/*									//
	//			�}�l�[�W���̎擾		//
	//									*/
	template<class T>
	inline ResourceManager<T>* GetResourceManager() {
		return ResourceManager<T>::Instance();
	}

}