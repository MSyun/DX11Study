//////////////////////////////////////////////////////////////
// wave�ǂݍ��݃N���X
// 2016. 9. 5	�쐬
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#pragma once


#include	"xaudio2.h"
#include	<string>
using namespace std;

class	WaveLoader {
public:
	HRESULT Load(
		const string FileName,
		IXAudio2* Xaudio2,
		IXAudio2SourceVoice** pSource,
		BYTE** pDataAudio,
		DWORD* dwSizeAudio);

private:
	// �T�E���h�f�[�^�t�@�C���̐���
	HRESULT CreateSoundData(HANDLE& hFile, const string FileName);
	// WAVE�t�@�C���̃`�F�b�N
	HRESULT CheckWave(HANDLE hFile);
	// �t�H�[�}�b�g�`�F�b�N
	HRESULT CheckFormat(HANDLE hFile, WAVEFORMATEXTENSIBLE& wfx);
	// �I�[�f�B�I�f�[�^�ǂݍ���
	HRESULT ReadAudioData(HANDLE hFile, BYTE** pDataAudio, DWORD* dwSizeAudio);
	//----- �`�����N
	// �`�F�b�N
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	// �f�[�^�̓ǂݍ���
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
};