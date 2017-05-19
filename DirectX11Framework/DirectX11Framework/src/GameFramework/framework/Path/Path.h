// パス関連
// 2017.05.12	: プログラム作成
// author		: SyunMizuno

#pragma once


#include	<string>


namespace MSLib {
	namespace Path {

		/* ディレクトリを抽出
		// path		: パス
		// return	: ディレクトリ
		*/
		std::string GetDirectoryName(const std::string& path);

		/* 拡張子を抽出
		// path		: パス
		// return	: 拡張子
		*/
		std::string GetExtension(const std::string& path);

		/* ファイル名を抽出
		// path		: パス
		// return	: ファイル名
		*/
		std::string GetFileName(const std::string& path);

	}
}