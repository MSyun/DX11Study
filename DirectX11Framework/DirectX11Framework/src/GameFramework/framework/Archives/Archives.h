// ファイル集約
// 2016. 5.16	:	プログラム作成
// author		:	SyunMizuno


#pragma once


#include	"Mesh/ArchivesMeshBase.h"
#include	"Texture/ArchivesTextureBase.h"
#include	"Sound/ArchivesSoundBase.h"
#include	"Tag/ArchivesTagBase.h"
#include	"Shader/ArchivesShaderBase.h"
#include	"../Utility/System/SystemUtility.h"


namespace MSLib {

	class Archives {
	private:
		static ArchivesCollection::ArchivesMeshBase*	m_pMeshName;
		static ArchivesCollection::ArchivesTextureBase*	m_pTexName;
		static ArchivesCollection::ArchivesSoundBase*	m_pSoundName;
		static ArchivesCollection::ArchivesTagBase*		m_pTagName;
		static ArchivesCollection::ArchivesShaderBase*	m_pShaderName;

	public:
		Archives();
		virtual ~Archives();

		template<class T>static void MeshCreate() {
			SAFE_DELETE(m_pMeshName);
			m_pMeshName = new T;
		}
		template<class T>static void TexCreate() {
			SAFE_DELETE(m_pTexName);
			m_pTexName = new T;
		}
		template<class T>static void SoundCreate() {
			SAFE_DELETE(m_pSoundName);
			m_pSoundName = new T;
		}
		template<class T>static void TagCreate() {
			SAFE_DELETE(m_pTagName);
			m_pTagName = new T;
		}
		template<class T>static void ShaderCreate() {
			SAFE_DELETE(m_pShaderName);
			m_pShaderName = new T;
		}

		static std::string Mesh(const std::string Name);
		static std::string Texture(const std::string Name);
		static std::string Sound(const std::string Name);
		static unsigned char Tag(const std::string Name);
		static std::string Shader(const std::string Name);
	};

};