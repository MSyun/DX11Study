// アーカイブ用インターフェース
// 2016. 5.16	:	プログラム作成
// author		:	SyunMizuno


#pragma once


#include	<map>
#include	<string>
using namespace std;


namespace ArchivesCollection {

	template<typename T>
	class IArchivesType {
	protected:
		map<string, T>	m_Archives;

	public:
		IArchivesType();
		virtual ~IArchivesType();

		/* 検索
		// name		: 検索名
		// return	: 成果物
		*/
		T Find(const string name);

	protected:
		virtual void Create() = 0 {}

		/* 追加
		// key		: 検索キー
		// regist	: 追加
		*/
		void Add(string key, T regist);
	};

#include	"IArchivesType.inl"

}