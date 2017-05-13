// パス関連
// 2017.05.12	: プログラム作成
// author		: SyunMizuno


#include	"Path.h"




string Path::GetDirectoryName(const string& path) {
	size_t pos1;

	pos1 = path.rfind('\\');
	if (pos1 != string::npos) {
		return path.substr(0, pos1 + 1);
	}

	pos1 = path.rfind('/');
	if (pos1 != string::npos) {
		return path.substr(0, pos1 + 1);
	}

	return "";
}


/*									//
//			拡張子を抽出			//
//									*/
string Path::GetExtension(const string& path) {
	string ext;
	size_t pos1 = path.rfind('.');
	if (pos1 != string::npos) {
		ext = path.substr(pos1 + 1, path.size() - pos1);
		string::iterator itr = ext.begin();
		while (itr != ext.end()) {
			*itr = tolower(*itr);
			itr++;
		}
		itr = ext.end() - 1;
		while (itr != ext.begin()) {
			if (*itr == 0 || *itr == 32) {
				ext.erase(itr--);
			} else {
				itr--;
			}
		}
	}

	return ext;
}