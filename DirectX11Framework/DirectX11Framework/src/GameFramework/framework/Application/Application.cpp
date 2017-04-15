//////////////////////////////////////////////////////////////
// 2016. 2. 7	�v���O�����쐬
// �쐬��		SyunMizuno
//////////////////////////////////////////////////////////////


#include	"Application.h"
#include	"../Screen/Screen.h"
#include	<tchar.h>
#include	<string>
using namespace std;

Application* pApp = NULL;

const LPCTSTR g_szClassName = _T("ClassName");

HWND Application::m_hWnd = NULL;


/*									//
//			�R���X�g���N�^			//
//									*/
Application::Application(
	int width,
	int height,
	bool bwnd)
{
	pApp = this;
	Screen::SetSize(width, height);
	Screen::SetFullScreen(!bwnd);
}


/*									//
//			�f�X�g���N�^			//
//									*/
Application::~Application() {
}


/*									//
//			�v���V�[�W��			//
//									*/
LRESULT CALLBACK Application::WndProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	return pApp->LocalWindowProc(hWnd, uMsg, wParam, lParam);
}


/*									//
//		���[�J���v���V�[�W��		//
//									*/
LRESULT Application::LocalWindowProc(
	HWND	hWnd,
	UINT	uMsg,
	WPARAM	wParam,
	LPARAM	lParam)
{
	// �f�t�H���g�ł͏I���̂�
	switch (uMsg) {
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	default:
		return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}

	return 0;
}


/*									//
//				���s				//
//									*/
int Application::Run(HINSTANCE _hInstance) {
	if (!_hInstance)	return false;
	m_hInstance = _hInstance;

	if (!RegistWndClass())	return false;
	if (!CreateMainWnd())	return false;
	if (!Initialize())		return false;

	Loop();

	ReleaseApp();

	return true;
}


/*									//
//		�E�C���h�E�N���X�̓o�^		//
//									*/
// <return> true. ���� : false. ���s
bool Application::RegistWndClass() {
	PreWndClass();

	if( !RegisterClassEx( &m_WndClassEx ) ) {
		MessageBox( NULL, _T("Call to RegisterClassEx failed!"), _T("�E�C���h�E�N���X�̍쐬�Ɏ��s"), NULL );
		return false;
	}

	return true;
}


/*									//
//		�E�C���h�E�N���X�̕ύX		//
//									*/
void Application::PreWndClass() {
	m_WndClassEx.cbSize			= sizeof( WNDCLASSEX );				// �\���̂̃T�C�Y
	m_WndClassEx.style			= CS_HREDRAW | CS_VREDRAW;			// �E�C���h�E�N���X�̃X�^�C��
	m_WndClassEx.lpfnWndProc	= pApp->WndProc;					// �E�C���h�E�v���V�[�W�����w��
	m_WndClassEx.cbClsExtra		= 0;								// �g���p
	m_WndClassEx.cbWndExtra		= 0;								// �g���p
	m_WndClassEx.hInstance		= m_hInstance;						// �C���X�^���X�n���h��
	m_WndClassEx.hIcon			= NULL;								// �A�C�R���̃n���h��
	m_WndClassEx.hCursor		= LoadCursor( NULL, IDC_ARROW );	// �J�[�\���̃n���h��
	m_WndClassEx.hbrBackground	= (HBRUSH)( COLOR_WINDOW + 1 );		// �w�i�u���V�̃n���h��
	m_WndClassEx.lpszMenuName	= NULL;								// ���j���[
	m_WndClassEx.lpszClassName	= g_szClassName;					// �E�C���h�E�N���X�̖��O
	m_WndClassEx.hIconSm		= NULL;								// �������A�C�R���̃n���h��
}


/*									//
//		���C���E�C���h�E�̍쐬		//
//									*/
// <return> true. ���� : false. ���s
bool Application::CreateMainWnd() {
	m_cs.hInstance = m_hInstance;
	m_cs.lpszClass = g_szClassName;

	PreMainWnd();

	m_hWnd = CreateWindowEx(
		m_cs.dwExStyle,
		m_cs.lpszClass,
		m_cs.lpszName,
		m_cs.style,
		m_cs.x,
		m_cs.y,
		m_cs.cx,
		m_cs.cy,
		m_cs.hwndParent,
		m_cs.hMenu,
		m_cs.hInstance,
		m_cs.lpCreateParams);

	if (!m_hWnd) {
		MessageBox(
			NULL,
			_T("Call to CreateWindow failed!"),
			_T("�E�C���h�E�n���h���̍쐬�Ɏ��s"),
			NULL);
		return false;
	}

	return true;
}


/*									//
//		���C���E�C���h�E�̕ύX		//
//									*/
void Application::PreMainWnd() {
	RECT	rcRect;						// ��ʒ������W�擾�p

	HWND hWnd = GetDesktopWindow();		// �f�X�N�g�b�v�̃n���h�����擾
	GetWindowRect( hWnd, &rcRect );		// �f�X�N�g�b�v�̋�`���擾

	int width = Screen::GetWidth();
	int height = Screen::GetHeight();

	m_cs.dwExStyle		= 0;										// �E�C���h�E�̊g���X�^�C��
	m_cs.lpszName		= _T("Base");									// �E�C���h�E��
	m_cs.style			= WS_OVERLAPPEDWINDOW;						// Windows�X�^�C��
	m_cs.x				= (int)(rcRect.right * 0.5 - width * 0.5);		// ��
	m_cs.y				= (int)(rcRect.bottom * 0.5 - height * 0.5);		// ��
	m_cs.cx				= (width + GetSystemMetrics(SM_CXDLGFRAME) * 2 );
	m_cs.cy				= (height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION));
	m_cs.hwndParent		= NULL;			// �V�����E�C���h�E�����L����E�C���h�E
	m_cs.hMenu			= NULL;			// �V�����E�C���h�E���g�p���郁�j���[
	m_cs.lpCreateParams	= NULL;			// �E�C���h�E���쐬���邽�߂Ɏg�p����|�C���^
}


/*									//
//		�A�v���P�[�V�����̏�����	//
//									*/
bool Application::Initialize() {
	if (!ShowWindow(m_hWnd, SW_SHOWNORMAL))
		return false;
	if (!UpdateWindow(m_hWnd))
		return false;

	return true;
}


/*									//
//			���b�Z�[�W���[�v		//
//									*/
void Application::Loop() {
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


/*									//
//		�A�v���P�[�V�����I������	//
//									*/
void Application::ReleaseApp() {
	UnregisterClass(g_szClassName, m_WndClassEx.hInstance);
}