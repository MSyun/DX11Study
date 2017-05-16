//////////////////////////////////////////////////////////////
// �T�E���h�x�[�X�N���X
// 2016. 9.26	�N���X�쐬
// �쐬��		SyunMizuno
//////////////////////////////////////////////////////////////



#include	"SoundBase.h"
#include	"Wave/WaveLoader.h"

#include	"../Save/Factory/SaveFactory.h"
#include	"../Debug/Debug.h"



DATARECORD SoundBase::m_DataRecord[] =
{
	DATA_LOCAL(SoundBase, m_fVolum),
	DATA_END,
};


/*									//
//			�R���X�g���N�^			//
//									*/
SoundBase::SoundBase() :
	m_fVolum(1.0f)
{
	m_mapSound.clear();
}


/*									//
//			�f�X�g���N�^			//
//									*/
SoundBase::~SoundBase() {
	for (auto it = m_mapSound.begin(); it != m_mapSound.end(); ++ it) {
		Release(it->second);
	}
	m_mapSound.clear();
}


/*									//
//				�ǂݍ���			//
//									*/
HRESULT SoundBase::Load(
	const string filename,
	const string name,
	IXAudio2* pXaudio2)
{
	//----- �o�^�ς݂��m�F
	if (m_mapSound.end() != m_mapSound.find(name)) {
		Debug::Log("�T�E���h��" + name + "�͂��łɐ�������Ă��܂�");
		return E_FAIL;
	}

	HRESULT hr;
	WaveLoader Wave;

	_tSound* Sound = new _tSound;
	Sound->pDataAudio = NULL;
	Sound->pSource = NULL;

	//----- Wave�ǂݍ���
	hr = Wave.Load(
		filename,
		pXaudio2,
		&Sound->pSource,
		&Sound->pDataAudio,
		&Sound->dwSizeAudio);
	if (hr != S_OK) {
		Debug::LogError("�T�E���h��" + name + "�̐����Ɏ��s���܂���");
		Release(Sound);
		return hr;
	}

	//----- �T�E���h�̓o�^
	Sound->pSource->SetVolume(m_fVolum);
	m_mapSound.insert(pair< string, _tSound* >(name, Sound));

	return S_OK;
}


/*									//
//				�폜				//
//									*/
void SoundBase::Delete(const string name) {
	//----- ������
	auto it = m_mapSound.find(name);

	// �o�^�m�F
	if (it == m_mapSound.end()) {
		Debug::Log("�T�E���h��" + name + "�͓o�^����Ă��Ȃ����ߍ폜�ł��܂���");
		return;
	}

	Release(it->second);

	m_mapSound.erase(name);
}


/*									//
//				�Đ�				//
//									*/
HRESULT SoundBase::Play(const string name, int loop) {
	//----- �o�^�ς݊m�F
	auto it = m_mapSound.find(name);

	// �o�^����Ă��Ȃ��ꍇ
	if (it == m_mapSound.end()) {
		Debug::LogError("�T�E���h��" + name + "�͓o�^����Ă��܂���");
		return E_FAIL;
	}

	//----- ��Ԏ擾
	XAUDIO2_VOICE_STATE xa2state;
	it->second->pSource->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0) {
		// �ꎞ��~
		it->second->pSource->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		it->second->pSource->FlushSourceBuffers();
	}

	//----- �l�̐ݒ�
	XAUDIO2_BUFFER buffer;
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = it->second->dwSizeAudio;
	buffer.pAudioData = it->second->pDataAudio;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = loop;

	// �I�[�f�B�I�o�b�t�@�̓o�^
	it->second->pSource->SubmitSourceBuffer(&buffer);

	// �Đ�
	it->second->pSource->Start(0);

	return S_OK;
}


/*									//
//				��~				//
//									*/
void SoundBase::Stop(const string name) {
	//----- �o�^�ς݊m�F
	auto it = m_mapSound.find(name);

	// �o�^����Ă��Ȃ��ꍇ
	if (it == m_mapSound.end()) {
		Debug::Log("�T�E���h��" + name + "�͓o�^����Ă��Ȃ����ߒ�~�ł��܂���");
		return;
	}

	XAUDIO2_VOICE_STATE xa2state;

	//----- ��Ԏ擾
	it->second->pSource->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0) {
		// �ꎞ��~
		it->second->pSource->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		it->second->pSource->FlushSourceBuffers();
	}
}


/*									//
//				�S��~				//
//									*/
void SoundBase::Stop() {
	for (auto it = m_mapSound.begin(); it != m_mapSound.end(); ++ it) {
		if (it->second->pSource) {
			it->second->pSource->Stop(0);
		}
	}
}


/*									//
//				���ʐݒ�			//
//									*/
void SoundBase::SetVolum(float volum) {
	m_fVolum = volum;

	for (auto it = m_mapSound.begin(); it != m_mapSound.end(); ++ it) {
		it->second->pSource->SetVolume(volum);
	}
}


/*									//
//				���ʎ擾			//
//									*/
float SoundBase::GetVolum() {
	return m_fVolum;
}


/*									//
//				�N���XID			//
//									*/
int SoundBase::GetClassID() {
//	return _SAVE_FACTORY::SAVE_FACT_SOUND;
	return 0;
}


/*									//
//			�w��T�E���h���J��		//
//									*/
void SoundBase::Release(_tSound* sound) {
	// �m�F
	if (!sound)	return;

	// �I�[�f�B�I�f�[�^�̉��
	if (sound->pDataAudio) {
		delete[] sound->pDataAudio;
		sound->pDataAudio = NULL;
	}

	// �\�[�X�{�C�X�̔p��
	if (sound->pSource) {
		// �ꎞ��~
		sound->pSource->Stop(0);

		sound->pSource->DestroyVoice();
		sound->pSource = NULL;
	}

	delete sound;
	sound = NULL;
}