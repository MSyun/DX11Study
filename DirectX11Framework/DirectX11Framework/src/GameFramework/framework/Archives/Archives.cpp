// ファイル集約
// 2016. 5.16	:	プログラム作成
// author		:	SyunMizuno


#include	"Archives.h"


namespace MSLib {

	ArchivesCollection::ArchivesMeshBase*		Archives::m_pMeshName = nullptr;
	ArchivesCollection::ArchivesTextureBase*	Archives::m_pTexName = nullptr;
	ArchivesCollection::ArchivesSoundBase*		Archives::m_pSoundName = nullptr;
	ArchivesCollection::ArchivesTagBase*		Archives::m_pTagName = nullptr;
	ArchivesCollection::ArchivesShaderBase*		Archives::m_pShaderName = nullptr;



	Archives::Archives() {

	}

	Archives::~Archives() {
		SAFE_DELETE(m_pMeshName);
		SAFE_DELETE(m_pTexName);
		SAFE_DELETE(m_pSoundName);
		SAFE_DELETE(m_pTagName);
		SAFE_DELETE(m_pShaderName);
	}


	std::string Archives::Mesh(const std::string Name) {
		if (!m_pMeshName)	return "";

		return m_pMeshName->Find(Name);
	}
	std::string Archives::Texture(const std::string Name) {
		if (!m_pTexName)	return "";

		return m_pTexName->Find(Name);
	}
	std::string Archives::Sound(const std::string Name) {
		if (!m_pSoundName)	return "";

		return m_pSoundName->Find(Name);
	}
	unsigned char Archives::Tag(const std::string Name) {
		if (!m_pTagName)	return -1;

		return m_pTagName->Find(Name);
	}
	std::string Archives::Shader(const std::string Name) {
		if (!m_pShaderName)	return "";

		return m_pShaderName->Find(Name);
	}

};