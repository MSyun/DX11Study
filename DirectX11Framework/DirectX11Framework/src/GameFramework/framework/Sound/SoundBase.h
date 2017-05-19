//////////////////////////////////////////////////////////////
// �T�E���h�x�[�X�N���X
// 2016. 9.26	�N���X�쐬
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#pragma once


#include	<Windows.h>
#include	"xaudio2.h"
#include	<map>
#include	<string>
#include	"../Save/Obj/SaveObjBase.h"


namespace MSLib {
	namespace Sound {

		class	SoundBase : public	ISaveObjBase {
		protected:
			// �T�E���h�\����
			struct _tSound {
				IXAudio2SourceVoice*	pSource;
				BYTE*					pDataAudio;
				DWORD					dwSizeAudio;
			};

			// �T�E���h
			std::map< std::string, _tSound* >	m_mapSound;

			// ����
			float	m_fVolum;

			// �Z�[�u�I�u�W�F�N�g
			static DATARECORD m_DataRecord[];

		public:
			SoundBase();
			virtual ~SoundBase();

			// �ǂݍ���
			HRESULT Load(
				const std::string	FileName,
				const std::string	name,
				IXAudio2*		ppXaudio2);
			void Delete(const std::string name);					// �폜
			HRESULT Play(const std::string name, int loop = 0);	// �Đ�
			void Stop(const std::string name);					// ��~
			void Stop();									// �S��~
			void SetVolum(float volum);						// �{�����[���ݒ�
			float GetVolum();								// �{�����[���擾

			// �Z�[�u�f�[�^
			virtual DATARECORD* GetDataRecord() { return m_DataRecord; }
			virtual int GetClassID();

		protected:
			// ���
			void Release(_tSound* sound);
		};

	}
}