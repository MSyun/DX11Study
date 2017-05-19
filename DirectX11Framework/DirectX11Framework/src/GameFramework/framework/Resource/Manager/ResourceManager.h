// リソースマネージャー
// 2017.04.24	: プログラム作成
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

		// 削除補助機能
		bool m_bHelper;

	public:
		ResourceManager();

		virtual ~ResourceManager();

		/* 作成
		// name		: 作成したいファイル名
		// return	: 生成したインスタンス
		*/
		T* Create(const std::string& name);
//		std::shared_ptr<T>* Create(const std::string& name);

		/* 削除
		// name		: 削除したいファイル名
		// return	: true. 成功、 false. 失敗
		*/
		bool Delete(const std::string& name);

		/* 取得
		// name		: 取得したいファイル名
		// return	: 生成したインスタンス
		*/
		T* Get(const std::string& name);
//		std::shared_ptr<T>* Get(const std::string& name);

		/* 補助機能設定
		// helper	: 補助機能 ON : OFF
		*/
		void SetHelper(bool helper);
	};

	template<class T>
	inline ResourceManager<T>* GetResourceManager();

}

#include	"ResourceManager.inl"