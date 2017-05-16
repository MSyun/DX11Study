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

using namespace std;


class	SoundBase : public	ISaveObjBase {
protected:
#pragma region struct

	// �T�E���h�\����
	struct _tSound {
		IXAudio2SourceVoice*	pSource;
		BYTE*					pDataAudio;
		DWORD					dwSizeAudio;
	};

#pragma endregion

#pragma region variable

	// �T�E���h
	map< string, _tSound* >	m_mapSound;

	// ����
	float	m_fVolum;

	// �Z�[�u�I�u�W�F�N�g
	static DATARECORD m_DataRecord[];

#pragma endregion

public:
#pragma region method

	SoundBase();
	virtual ~SoundBase();

	// �ǂݍ���
	HRESULT Load(
		const string	FileName,
		const string	name,
		IXAudio2*		ppXaudio2);
	void Delete(const string name);					// �폜
	HRESULT Play(const string name, int loop = 0);	// �Đ�
	void Stop(const string name);					// ��~
	void Stop();									// �S��~
	void SetVolum(float volum);						// �{�����[���ݒ�
	float GetVolum();								// �{�����[���擾

	// �Z�[�u�f�[�^
	virtual DATARECORD* GetDataRecord() { return m_DataRecord; }
	virtual int GetClassID();

#pragma endregion

protected:
	// ���
	void Release(_tSound* sound);
};