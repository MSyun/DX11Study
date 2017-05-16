// ファイル集約
// 2016. 5.16	:	プログラム作成
// author		:	SyunMizuno


#include	"Archives.h"


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


string Archives::Mesh(const string Name) {
	if (!m_pMeshName)	return "";

	return m_pMeshName->Find(Name);
}
string Archives::Texture(const string Name) {
	if (!m_pTexName)	return "";

	return m_pTexName->Find(Name);
}
string Archives::Sound(const string Name) {
	if (!m_pSoundName)	return "";

	return m_pSoundName->Find(Name);
}
unsigned char Archives::Tag(const string Name) {
	if (!m_pTagName)	return -1;

	return m_pTagName->Find(Name);
}
string Archives::Shader(const string Name) {
	if (!m_pShaderName)	return "";

	return m_pShaderName->Find(Name);
}