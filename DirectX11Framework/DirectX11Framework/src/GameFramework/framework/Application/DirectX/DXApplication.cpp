//////////////////////////////////////////////////////////////
// 2016. 2. 7	�v���O�����쐬
// author		SyunMizuno
//////////////////////////////////////////////////////////////

#include	<tchar.h>
#include	"DXApplication.h"
#include	"../../Screen/Screen.h"


/*									//
//			�R���X�g���N�^			//
//									*/
DXApplication::DXApplication(int width, int height, bool bwnd) :
	Application(width, height, bwnd),
	m_pDXObj(NULL)
{}


/*									//
//			�f�X�g���N�^			//
//									*/
DXApplication::~DXApplication() {
}


/*									//
//				�ύX				//
//									*/
void DXApplication::PreMainWnd() {
	RECT	rcRect;						// ��ʒ������W�擾�p

	HWND hwnd;
	hwnd = GetDesktopWindow();		// �f�X�N�g�b�v�̃n���h�����擾
	GetWindowRect(hwnd, &rcRect );	// �f�X�N�g�b�v�̋�`���擾
	SetHWND(hwnd);

	int width = Screen::GetWidth();
	int height = Screen::GetHeight();

	m_cs.dwExStyle		= 0;
	m_cs.lpszName		= _T("Aimaze");
	m_cs.style			= !Screen::GetFullScreen() ? WS_OVERLAPPEDWINDOW | WS_VISIBLE : WS_POPUP | WS_VISIBLE;
	m_cs.x				= rcRect.right / 2 - width / 2;
	m_cs.y				= rcRect.bottom / 2 - height / 2;
	m_cs.cx				= (width + GetSystemMetrics(SM_CXDLGFRAME) * 2 );
	m_cs.cy				= (height + GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION));
	m_cs.hwndParent		= NULL;
	m_cs.hMenu			= NULL;
	m_cs.lpCreateParams	= NULL;
}


/*									//
//		�A�v���P�[�V�����̏�����	//
//									*/
// <return> true. ���� : false. ���s
bool DXApplication::Initialize() {
	if (m_pDXObj) {
		if (FAILED(m_pDXObj->Init()))
			return false;
	}

	// �E�C���h�E�\��
	if (!Application::Initialize())
		return false;

	return true;
}


/*									//
//			���b�Z�[�W���[�v		//
//									*/
void DXApplication::Loop() {
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	if (!m_pDXObj)
		return;

	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			if (FAILED(m_pDXObj->Step()))
				break;
		}
	}
}


/*									//
//		�A�v���P�[�V�����I������	//
//									*/
void DXApplication::ReleaseApp() {
	if (m_pDXObj) {
		delete m_pDXObj;
		m_pDXObj = NULL;
	}

	Application::ReleaseApp();
}


/*									//
//		�E�C���h�E�v���V�[�W��		//
//									*/
LRESULT DXApplication::LocalWindowProc(
	HWND	hWnd,
	UINT	msg,
	WPARAM	wParam,
	LPARAM	lParam)
{
	// �f�t�H���g�ł͏I���̂�
	switch (msg) {
		//----- �L�[���͊֌W
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

		//----- Alt + ����L�[
	case WM_SYSKEYDOWN:
		switch (wParam) {
		case VK_RETURN:	// Alt + Enter�������Ɛ؂�ւ�
//			m_pDXObj->ChangeDisplayMode();
			break;

		case VK_SHIFT:
			//			m_pSnap->Snap( "Snap.png", m_bWindow );

		default:
			break;
		}

		//----- �T�C�Y�ύX
	case WM_SIZE:
		//if (m_D3Dpp.Windowed != TRUE)
		//	break;

		//if (!m_pD3DDevice || wParam == SIZE_MINIMIZED)
		//	break;
		//m_D3Dpp.BackBufferWidth  = LOWORD(lParam);
		//m_D3Dpp.BackBufferHeight = HIWORD(lParam);
		//if(m_bDeviceLost)
		//	break;
		//if (wParam == SIZE_MAXIMIZED || wParam == SIZE_RESTORED)
		//	ChangeWindowSize();
		break;

		//----- �f�X�g���`�C
	case WM_DESTROY:
		// DirectX Graphics�̏I������
		PostQuitMessage(0);
		m_hWnd = NULL;
		break;


	case WM_ACTIVATE:
		//		m_bActive = (LOWORD(wParam) != 0 );
		break;

	default:
		return Application::LocalWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
	return 0;
}