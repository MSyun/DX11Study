// ���\�[�X�}�l�[�W���[
// 2017.04.24	: �v���O�����쐬
// 2017.05.19	: �X�}�[�g�|�C���^����
// author		: SyunMizuno

#pragma once

#include	<map>
#include	"../../Singleton/Singleton.h"
#include	<memory>


namespace MSLib {

	template<class T>
	class ResourceManager : public	Singleton<ResourceManager<T>> {
	protected:
		std::map<std::string, std::shared_ptr<T>>	m_MapResources;

	public:
		ResourceManager();

		virtual ~ResourceManager();

		/* �쐬
		// name		: �쐬�������t�@�C����
		// return	: ���������C���X�^���X
		*/
		std::shared_ptr<T> Create(const std::string& name);

		/* �폜
		// name		: �폜�������t�@�C����
		// return	: true. �����A false. ���s
		*/
		bool Delete(const std::string& name);

		/* �擾
		// name		: �擾�������t�@�C����
		// return	: ���������C���X�^���X
		*/
		std::shared_ptr<T> Get(const std::string& name);
	};

	template<class T>
	inline ResourceManager<T>* GetResourceManager();

}

#include	"ResourceManager.inl"