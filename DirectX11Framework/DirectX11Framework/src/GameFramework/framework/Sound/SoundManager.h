//////////////////////////////////////////////////////////////
// �T�E���h�}�l�[�W���N���X
// 2016. 9.26	�N���X�쐬
// 2016. 9.27	�Z�[�u�֐��擾
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#pragma once


#include	"SoundBase.h"
#include	"../Singleton/Singleton.h"
#include	"../Save/Obj/SaveObjBase.h"


/*
	memo	:
			�Z�[�u�֐��͌p����ō쐬�����ق����ǂ�����
			���̏ꍇ�x�[�X�ɏ��������Ă�����p������Ƃ��ɃV���O���g�����g�p���邱��
*/


typedef enum {
	SOUND_BGM = 0,
	SOUND_SE,
	SOUND_VOICE,
	SOUND_MAX,
} _SOUND_TYPE;


class	SoundManager : public	Singleton<SoundManager>, public	ISaveObjBase {
public:
#pragma region method

	SoundManager();
	virtual ~SoundManager();

	HRESULT Init(HWND hWnd);
	HRESULT Load(
		_SOUND_TYPE type,
		const TCHAR* filename,
		const TCHAR* name);
	void Delete(_SOUND_TYPE type, const TCHAR* name);
	HRESULT Play(
		_SOUND_TYPE type,
		const TCHAR* name,
		int loop = 0);
	void Stop(_SOUND_TYPE type);
	void Stop(_SOUND_TYPE type, const TCHAR* name);
	void SetVolum(_SOUND_TYPE type, float volum);
	float GetVolum(_SOUND_TYPE type);

	// �Z�[�u
	void Save();

	// �Z�[�u�f�[�^
	virtual DATARECORD* GetDataRecord() { return m_DataRecord; }
	virtual int GetClassID();

#pragma endregion

protected:
#pragma region variable

	IXAudio2*				m_pXaudio2;			// �C���^�[�t�F�[�X
	IXAudio2MasteringVoice*	m_pMasteringVoice;	// �}�X�^�[�{�C�X

	// �T�E���h
	SoundBase*	m_pBGM;
	SoundBase*	m_pSE;
	SoundBase*	m_pVoice;

	// �Z�[�u�I�u�W�F�N�g
	static DATARECORD m_DataRecord[];

#pragma endregion

#pragma region conceal method

	// �T�E���h�^�C�v
	SoundBase* CheckSound(_SOUND_TYPE type);
	void Release();

#pragma endregion
};

inline SoundManager* GetSoundManager() {
	return SoundManager::Instance();
}