// リソースマネージャー
// 2017.04.24	: プログラム作成
// 2017.05.19	: スマートポインタ実装
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

		/* 作成
		// name		: 作成したいファイル名
		// return	: 生成したインスタンス
		*/
		std::shared_ptr<T> Create(const std::string& name);

		/* 削除
		// name		: 削除したいファイル名
		// return	: true. 成功、 false. 失敗
		*/
		bool Delete(const std::string& name);

		/* 取得
		// name		: 取得したいファイル名
		// return	: 生成したインスタンス
		*/
		std::shared_ptr<T> Get(const std::string& name);
	};

	template<class T>
	inline ResourceManager<T>* GetResourceManager();

}

#include	"ResourceManager.inl"