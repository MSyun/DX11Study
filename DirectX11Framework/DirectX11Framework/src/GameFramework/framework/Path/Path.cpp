// �p�X�֘A
// 2017.05.12	: �v���O�����쐬
// author		: SyunMizuno


#include	"Path.h"


namespace MSLib {
	namespace Path {

		/*									//
		//		�f�B���N�g���𒊏o			//
		//									*/
		std::string GetDirectoryName(const std::string& path) {
			size_t pos1;

			pos1 = path.rfind('\\');
			if (pos1 != std::string::npos) {
				return path.substr(0, pos1 + 1);
			}

			pos1 = path.rfind('/');
			if (pos1 != std::string::npos) {
				return path.substr(0, pos1 + 1);
			}

			return "";
		}


		/*									//
		//			�g���q�𒊏o			//
		//									*/
		std::string GetExtension(const std::string& path) {
			std::string ext;
			size_t pos1 = path.rfind('.');
			if (pos1 != std::string::npos) {
				ext = path.substr(pos1 + 1, path.size() - pos1);
				auto itr = ext.begin();
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


		/*									//
		//			�t�@�C�����𒊏o		//
		//									*/
		std::string GetFileName(const std::string& path) {
			size_t pos1;

			pos1 = path.rfind('\\');
			if (pos1 != std::string::npos) {
				return path.substr(pos1 + 1, path.size() - pos1 - 1);
			}

			pos1 = path.rfind('/');
			if (pos1 != std::string::npos) {
				return path.substr(pos1 + 1, path.size() - pos1 - 1);
			}

			return path;
		}

	}
}