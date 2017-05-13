// パス関連
// 2017.05.12	: プログラム作成
// author		: SyunMizuno



#pragma once


#include	<string>
using namespace std;


namespace Path {

	/* ディレクトリを抽出
	// path		: ファイル名
	// return	: ディレクトリ
	*/
	string GetDirectoryName(const string& path);

	/* 拡張子を抽出
	// path		: ファイル名
	// return	: 拡張子
	*/
	string GetExtension(const string& path);

}