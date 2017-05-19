// ���\�[�X�}�l�[�W���[
// 2017.04.24	: �v���O�����쐬
// author		: SyunMizuno

#pragma once

#include	<map>
#include	"../../Singleton/Singleton.h"
#include	<memory>


namespace MSLib {

	template<class T>
	class ResourceManager : public	Singleton<ResourceManager<T>> {
	protected:
		std::map<std::string, T*>	m_MapResources;
//		std::map<std::string, std::shared_ptr<T>>	m_MapResources;

		// �폜�⏕�@�\
		bool m_bHelper;

	public:
		ResourceManager();

		virtual ~ResourceManager();

		/* �쐬
		// name		: �쐬�������t�@�C����
		// return	: ���������C���X�^���X
		*/
		T* Create(const std::string& name);
//		std::shared_ptr<T>* Create(const std::string& name);

		/* �폜
		// name		: �폜�������t�@�C����
		// return	: true. �����A false. ���s
		*/
		bool Delete(const std::string& name);

		/* �擾
		// name		: �擾�������t�@�C����
		// return	: ���������C���X�^���X
		*/
		T* Get(const std::string& name);
//		std::shared_ptr<T>* Get(const std::string& name);

		/* �⏕�@�\�ݒ�
		// helper	: �⏕�@�\ ON : OFF
		*/
		void SetHelper(bool helper);
	};

	template<class T>
	inline ResourceManager<T>* GetResourceManager();

}

#include	"ResourceManager.inl"