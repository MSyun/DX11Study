///////////////////////////////////////////////////////////////
// �V�[���t�F�[�h�x�[�X�N���X
// author		SyunMizuno
// 2016. 1. 27	�v���O�����쐬
///////////////////////////////////////////////////////////////

#include	"SceneFadeBase.h"
#include	"../../Resource/Manager/ResourceManager.h"
#include	"../../Time/Time.h"
#include	"../../Utility/System/SystemUtility.h"
//#include	"../../../Archives/Archives.h"
#include	"../../Debug/Debug.h"


/*									//
//			�R���X�g���N�^			//
//									*/
SceneFadeBase::SceneFadeBase(
//	IDirect3DDevice9* _Dev,
	bool _awake,
	int _width,
	int _height,
	float _time) :
	m_fAlpha(0.0f),
	m_vSize((float)_width, (float)_height),
	m_bExe(false),
	m_bIn(true),
	m_fTime(_time),
//	m_pDevice(_Dev),
//	m_pSprite(NULL),
	m_bChange(true)
{
	if (_awake)
		this->OnAwake();
}


/*									//
//				������				//
//									*/
bool SceneFadeBase::Init() {
//	m_pSprite = new Sprite;
//	m_pSprite->SetTexture(GetTexManager()->Get(Archives::Texture("Fade/Default")));
//	RectTransform* rectTransform = m_pSprite->GetRectTransform();
//	rectTransform->SetSize(m_vSize);
//	rectTransform->SetPos(m_vSize.x / 2.f, m_vSize.y / 2.f, 0.f);
//	m_pSprite->DontDestroyOnLoad();
//	m_pSprite->SetActive(false);
//	m_pSprite->SetName("SceneFadeTexture");

	//m_onBeginFadeIn = new CPPEvent<>;
	//m_onEndFadeIn = new CPPEvent<>;
	//m_onBeginFadeOut = new CPPEvent<>;
	//m_onEndFadeOut = new CPPEvent<>;

	return ReStart();
}


/*									//
//			�A�E�F�C�N				//
//									*/
void SceneFadeBase::OnAwake() {
	m_bIn = false;
	m_fAlpha = 1.0f;
	m_bChange = false;
}


/*									//
//				���				//
//									*/
void SceneFadeBase::Release() {
//	SAFE_DELETE(m_pSprite);
	//SAFE_DELETE(m_onBeginFadeIn);
	//SAFE_DELETE(m_onEndFadeIn);
	//SAFE_DELETE(m_onBeginFadeOut);
	//SAFE_DELETE(m_onEndFadeOut);

//	GetTexManager()->Delete(Archives::Texture("Fade/Default"));
}


/*									//
//				�ύX���H			//
//									*/
bool SceneFadeBase::Change() {
	if (m_bChange) {
		m_bChange = false;
		return true;
	}
	return false;
}


/*									//
//				�X�V				//
//									*/
void SceneFadeBase::Update() {
	if (m_bExe) {
		if (!m_bIn)
			FadeOut();
		else
			FadeIn();
	}
}


/*									//
//				�`��				//
//									*/
void SceneFadeBase::Draw() {
//	m_pSprite->DrawAll();
}


/*									//
//				�ď�����			//
//									*/
bool SceneFadeBase::ReStart() {
	return true;
}


/*									//
//				���s				//
//									*/
void SceneFadeBase::Exe(void) {
	if (m_bExe)	return;

	m_bExe = true;
}


/*									//
//			�t�F�[�h�C������		//
//									*/
void SceneFadeBase::FadeIn() {
	if (m_fAlpha >= 1.0f) {
		Debug::Log("FadeIn�J�n");
		//m_onBeginFadeIn->Invoke();
		//m_onBeginFadeIn->RemoveAllListener();
	}

	m_fAlpha -= (Time::GetDeltaTime() / m_fTime);
	if (m_fAlpha <= 0.f) {
		m_fAlpha = 0.f;
		m_bExe = false;
		m_bIn ^= true;
		Debug::Log("FadeIn�I��");
		//m_onEndFadeIn->Invoke();
		//m_onEndFadeIn->RemoveAllListener();
	}

//	if (m_pSprite) {
//		m_pSprite->SetColor(Color(0.f, 0.f, 0.f, m_fAlpha));
//		m_pSprite->UpdateAll();
//	}
}


/*									//
//			�t�F�[�h�A�E�g����		//
//									*/
void SceneFadeBase::FadeOut() {
	if (m_fAlpha <= 0.0f) {
		Debug::Log("FadeOut�J�n");
		//m_onBeginFadeOut->Invoke();
		//m_onBeginFadeOut->RemoveAllListener();
	}

	m_fAlpha += (Time::GetDeltaTime() / m_fTime);
	if (m_fAlpha >= 1.f) {
		m_fAlpha = 1.f;
		m_bIn ^= true;
		m_bChange = true;
		Debug::Log("FadeOut�I��");
		//m_onEndFadeOut->Invoke();
		//m_onEndFadeOut->RemoveAllListener();
	}

//	if (m_pSprite) {
//		m_pSprite->SetColor(Color(0.f, 0.f, 0.f, m_fAlpha));
//		m_pSprite->UpdateAll();
//	}
}


/*									//
//			�T�C�Y�̐ݒ�			//
//									*/
void SceneFadeBase::SetSize(int x, int y) {
	m_vSize.x = (float)x;
	m_vSize.y = (float)y;

//	if (!m_pSprite)	return;

//	m_pSprite->GetRectTransform()->SetSize(m_vSize.x, m_vSize.y);
}