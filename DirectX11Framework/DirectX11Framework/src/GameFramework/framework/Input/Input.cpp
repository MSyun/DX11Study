//
// DirectInput �N���X����
//
// 2016. 9.20	�@�\�g��
// �ύX��		Syun Mizuno

#include "Input.h"
#include <math.h>
#include	"../Math/Funcs/MathFuncs.h"
#include	"../Utility/System/SystemUtility.h"


#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dinput8.lib")

// �ÓI�����o�ϐ�
LPDIRECTINPUT8			Input::m_pDI = NULL;					// DirectInput8 �I�u�W�F�N�g
LPDIRECTINPUTDEVICE8	Input::m_pDIDeviceKey = NULL;			// DirectInputDevice8 �I�u�W�F�N�g
BYTE					Input::m_diKeyState[MAX_KEY] = {0};	// �L�[�{�[�h���擾�o�b�t�@
BYTE					Input::m_diPrevKeyState[MAX_KEY] = {0};// ���O�̃L�[�{�[�h���
LPDIRECTINPUTDEVICE8	Input::m_pDIDeviceMouse = NULL;		// DirectInputDevice8 �I�u�W�F�N�g
DIMOUSESTATE			Input::m_diMouseState = {0};			// �}�E�X���擾�o�b�t�@
DIMOUSESTATE			Input::m_diPrevMouseState = {0};		// ���O�̃}�E�X���
LPDIRECTINPUTDEVICE8	Input::m_pDIDeviceJoy[MAX_JOY] = {0};	// DirectInputDevice8 �I�u�W�F�N�g
DIJOYSTATE				Input::m_diJoyState[MAX_JOY] = {0};	// �W���C�X�e�B�b�N���擾�o�b�t�@
DIJOYSTATE				Input::m_diPrevJoyState[MAX_JOY] = {0};// ���O�̃W���C�X�e�B�b�N���
int						Input::m_nJoy = 0;						// �W���C�X�e�B�b�N�ڑ���
TCHAR					g_szTitle[] = _T("Input");



/*									//
//	�W���C�X�e�B�b�N�₢���킹�p	//
//	�R�[���o�b�N�֐�				*/
BOOL CALLBACK Input::EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef) {
	DIDEVCAPS diDevCaps;			// �f�o�C�X���

	// �W���C�X�e�B�b�N�p�f�o�C�X�I�u�W�F�N�g���쐬
	HRESULT hr = m_pDI->CreateDevice(lpddi->guidInstance, &m_pDIDeviceJoy[m_nJoy], NULL);
	if (FAILED(hr))
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	// �W���C�X�e�B�b�N�̔\�͂𒲂ׂ�
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hr = m_pDIDeviceJoy[m_nJoy]->GetCapabilities(&diDevCaps);
	if (FAILED(hr)) {
		SAFE_RELEASE(m_pDIDeviceJoy[m_nJoy]);
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	}
	if (++m_nJoy < MAX_JOY)
		return DIENUM_CONTINUE;		// �񋓂𑱂���
	return DIENUM_STOP;		// �K�v���������̂ŗ񋓂��I������
}


/*									//
//			�R���X�g���N�^			//
//									*/
Input::Input(void) {
}


/*									//
//			�f�X�g���N�^			//
//									*/
Input::~Input(void) {
}


/*									//
//				������				//
//									*/
void Input::Init(HWND hWnd) {
	HINSTANCE hInst = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

	// DirectInput�I�u�W�F�N�g�̍쐬
	HRESULT hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDI, NULL);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInput �I�u�W�F�N�g�̍쐬�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//******** �L�[�{�[�h�p
	// DirectInputDevice�I�u�W�F�N�g�̍쐬
	hr = m_pDI->CreateDevice(GUID_SysKeyboard, &m_pDIDeviceKey, NULL);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInputDevice �I�u�W�F�N�g�̍쐬�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_pDIDeviceKey->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInput �Ńf�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	// �������x���̐ݒ�
	hr = m_pDIDeviceKey->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInput�ŋ������x���̐ݒ�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	// �f�o�C�X�ւ̓��͐���J�n
	hr = m_pDIDeviceKey->Acquire();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInput �Ńf�o�C�X�ւ̓��͐���J�n�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//******** �}�E�X�p
	// DirectInputDevice�I�u�W�F�N�g�̍쐬
	hr = m_pDI->CreateDevice(GUID_SysMouse, &m_pDIDeviceMouse, NULL);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInputDevice �I�u�W�F�N�g�̍쐬�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	// �f�[�^�t�H�[�}�b�g�̐ݒ�
	hr = m_pDIDeviceMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInput �Ńf�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	// �������x���̐ݒ�
	hr = m_pDIDeviceMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInput�ŋ������x���̐ݒ�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD dipdw;
	dipdw.diph.dwSize		= sizeof(dipdw);
	dipdw.diph.dwHeaderSize	= sizeof(dipdw.diph);
	dipdw.diph.dwObj		= 0;
	dipdw.diph.dwHow		= DIPH_DEVICE;
	dipdw.dwData			= DIPROPAXISMODE_REL;	// ���Βl���[�h�ɐݒ�
	m_pDIDeviceMouse->SetProperty(DIPROP_AXISMODE, &dipdw.diph);

	// �f�o�C�X�ւ̓��͐���J�n
	hr = m_pDIDeviceMouse->Acquire();
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInput �Ńf�o�C�X�ւ̓��͐���J�n�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	//******** �W���C�X�e�B�b�N�p
	// DirectInputDevice�I�u�W�F�N�g�̍쐬
	m_nJoy = 0;
	hr = m_pDI->EnumDevices(DI8DEVCLASS_GAMECTRL, EnumJoyCallback, NULL, DIEDFL_ATTACHEDONLY);
	if (FAILED(hr)) {
		MessageBox(hWnd, _T("DirectInputDevice �I�u�W�F�N�g�̍쐬�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
		return;
	}

	for (int i = 0; i < m_nJoy; i++) {
		// �f�[�^�t�H�[�}�b�g�̐ݒ�
		hr = m_pDIDeviceJoy[i]->SetDataFormat(&c_dfDIJoystick);
		if (FAILED(hr)) {
			MessageBox(hWnd, _T("DirectInput �Ńf�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}

		// �������x���̐ݒ�
		hr = m_pDIDeviceJoy[i]->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
		if (FAILED(hr)) {
			MessageBox(hWnd, _T("DirectInput�ŋ������x���̐ݒ�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}

		// �f�o�C�X�̐ݒ�
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwObj = DIJOFS_X;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_X;
		diprg.lMax       = JOY_MAX_X;
		m_pDIDeviceJoy[i]->SetProperty(DIPROP_RANGE, &diprg.diph);	// �w�����͈̔͂��w��
		diprg.diph.dwObj = DIJOFS_Y;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_Y;
		diprg.lMax       = JOY_MAX_Y;
		m_pDIDeviceJoy[i]->SetProperty(DIPROP_RANGE, &diprg.diph);	// �x�����͈̔͂��w��

		// �f�o�C�X�ւ̓��͐���J�n
		hr = m_pDIDeviceJoy[i]->Acquire();
		if (FAILED(hr)) {
			MessageBox(hWnd, _T("DirectInput �Ńf�o�C�X�ւ̓��͐���J�n�Ɏ��s���܂����I"), g_szTitle, MB_OK | MB_ICONSTOP);
			return;
		}
	}
}


/*									//
//				���				//
//									*/
void Input::Fin(void) {
	for (int i = 0; i < m_nJoy; i++) {
		if (m_pDIDeviceJoy[i])
			m_pDIDeviceJoy[i]->Unacquire();	// ���͂��I��
		SAFE_RELEASE(m_pDIDeviceJoy[i]);	// DirectInputDevice8 �I�u�W�F�N�g�̉��
	}
	if (m_pDIDeviceKey)
		m_pDIDeviceKey->Unacquire();		// ���͂��I��
	SAFE_RELEASE(m_pDIDeviceKey);			// DirectInputDevice8 �I�u�W�F�N�g�̉��
	if (m_pDIDeviceMouse)
		m_pDIDeviceMouse->Unacquire();		// ���͂��I��
	SAFE_RELEASE(m_pDIDeviceMouse);			// DirectInputDevice8 �I�u�W�F�N�g�̉��
	SAFE_RELEASE(m_pDI);					// DirectInput8 �I�u�W�F�N�g�̉��
}


/*									//
//				�X�V				//
//									*/
void Input::Update(void) {
	HRESULT hr;

	if (m_pDIDeviceKey) {
		CopyMemory(m_diPrevKeyState, m_diKeyState, MAX_KEY);
		m_pDIDeviceKey->Acquire();			// �v�����o��
		// ���݂̃L�[�{�[�h�̏�Ԃ��擾
		hr = m_pDIDeviceKey->GetDeviceState(MAX_KEY, &m_diKeyState);
		if (hr == DIERR_INPUTLOST)
			m_pDIDeviceKey->Acquire();		// �ēx�A�v�����o��
	}
	if (m_pDIDeviceMouse) {
		m_diPrevMouseState = m_diMouseState;
		m_pDIDeviceMouse->Acquire();		// �v�����o��
		// ���݂̃}�E�X�̏�Ԃ��擾
		hr = m_pDIDeviceMouse->GetDeviceState(sizeof(m_diMouseState), &m_diMouseState);
		if (hr == DIERR_INPUTLOST)
			m_pDIDeviceMouse->Acquire();	// �ēx�A�v�����o��
	}
	for (int i = 0; i < m_nJoy; i++) {
		m_diPrevJoyState[i] = m_diJoyState[i];

		m_pDIDeviceJoy[i]->Acquire();		// �v�����o��
		m_pDIDeviceJoy[i]->Poll();			// �f�o�C�X��̃|�[�����O�ΏۃI�u�W�F�N�g����f�[�^���擾
		// ���݂̃W���C�X�e�B�b�N�̏�Ԃ��擾
		hr = m_pDIDeviceJoy[i]->GetDeviceState(sizeof(m_diJoyState[0]), &m_diJoyState[i]);
		if (hr == DIERR_INPUTLOST)
			m_pDIDeviceJoy[i]->Acquire();	// �ēx�A�v�����o��
	}
}


//-------------------------------------------------------------------------------
// �L�[�{�[�h
/*									//
//		�L�[�̉�����Ԃ��擾		//
//									*/
bool Input::GetKeyPress(int nKey) {
	if (nKey < 0 || nKey >= MAX_KEY) return false;
	return (m_diKeyState[nKey] & 0x80) != 0;
}


/*									//
//		�L�[�̃g���K��Ԃ��擾		//
//									*/
bool Input::GetKeyTrigger(int nKey) {
	if (nKey < 0 || nKey >= MAX_KEY) return false;
	return (m_diPrevKeyState[nKey] & 0x80) == 0 &&
		(m_diKeyState[nKey] & 0x80) != 0;
}


/*									//
//		�L�[�̉����ԍ����擾		//
//									*/
int Input::GetKeyPressButton() {
	for( int i = 0; i < MAX_KEY; i ++ ) {
		if( m_diKeyState[i] & 0x80 )
			return i;
	}

	// ���͖���
	return -1;
}


/*									//
//		�L�[�̃g���K�ԍ����擾		//
//									*/
int Input::GetKeyTriggerButton() {
	for( int i = 0; i < MAX_KEY; i ++ ) {
		if( (m_diPrevKeyState[i] & 0x80) == 0 &&
			(m_diKeyState[i] & 0x80) != 0)
			return i;
	}

	// ���͖���
	return -1;
}


/*									//
//		�L�[�̃����[�X��Ԃ��擾	//
//									*/
bool Input::GetKeyRelease(int nKey) {
	if (nKey < 0 || nKey >= MAX_KEY) return false;
	return (m_diPrevKeyState[nKey] & 0x80) != 0 &&
		(m_diKeyState[nKey] & 0x80) == 0;
}


//-------------------------------------------------------------------------------
// �W���C�X�e�B�b�N
/*									//
//				�ڑ����擾			//
//									*/
int Input::GetNumJoystick(void) {
	return m_nJoy;
}


/*									//
//		�{�^���̉�����Ԏ擾		//
//									*/
bool Input::GetJoyPress(int nJoy, int nButton) {
	if (nJoy < 0 || nJoy >= m_nJoy) return false;
	if (nButton < 0 || nButton >= 32) return false;
	return (m_diJoyState[nJoy].rgbButtons[nButton] & 0x80) != 0;
}


/*									//
//		�{�^���̃g���K��Ԏ擾		//
//									*/
bool Input::GetJoyTrigger(int nJoy, int nButton) {
	if (nJoy < 0 || nJoy >= m_nJoy) return false;
	if (nButton < 0 || nButton >= 32) return false;
	return (m_diPrevJoyState[nJoy].rgbButtons[nButton] & 0x80) == 0 &&
		(m_diJoyState[nJoy].rgbButtons[nButton] & 0x80) != 0;
}


/*									//
//		�{�^���̃����[�X��Ԏ擾	//
//									*/
bool Input::GetJoyRelease(int nJoy, int nButton) {
	if (nJoy < 0 || nJoy >= m_nJoy) return false;
	if (nButton < 0 || nButton >= 32) return false;
	return (m_diPrevJoyState[nJoy].rgbButtons[nButton] & 0x80) != 0 &&
		(m_diJoyState[nJoy].rgbButtons[nButton] & 0x80) == 0;
}


/*									//
//		�{�^���̉����ԍ��擾		//
//									*/
int Input::GetJoyPressButton(int nJoy) {
	if( nJoy < 0 || nJoy >= m_nJoy )	return -1;

	for( int i = 0; i < 32; i ++ ) {
		if( ( m_diJoyState[nJoy].rgbButtons[i] & 0x80 ) != 0 ) {
			return i;
		}
	}
	return -1;
}


/*									//
//		�{�^���̃g���K�ԍ��擾		//
//									*/
int Input::GetJoyTriggerButton(int nJoy) {
	if( nJoy < 0 || nJoy >= m_nJoy )	return -1;

	for( int i = 0; i < 32; i ++ ) {
		if( ( m_diPrevJoyState[nJoy].rgbButtons[i] & 0x80 ) == 0 &&
			( m_diJoyState[nJoy].rgbButtons[i] & 0x80 ) != 0 )
		{
			return i;
		}
	}
	return -1;
}


/*									//
//			���̉�����Ԏ擾		//
//									*/
float Input::GetJoyAxisPress(int nJoy, int nAxis) {
	// ���݊m�F
	if (nJoy < 0 || nJoy >= m_nJoy) return 0.0f;

	switch (nAxis) {
	case JOY_X:
		// ���t���[���`�F�b�N
		if( abs(m_diJoyState[nJoy].lX) < JOY_MAX_X * JOY_MOVE_NON )
			return 0.0f;
		// ���E�`�F�b�N
		if (m_diJoyState[nJoy].lX < 0)	return -1.0f;
		else							return 1.0f;

	case JOY_Y:
		// ���t���[���`�F�b�N
		if( abs(m_diJoyState[nJoy].lY) < JOY_MAX_Y * JOY_MOVE_NON )
			return 0.0f;
		// �㉺�`�F�b�N
		if (m_diJoyState[nJoy].lY < 0)	return -1.0f;
		else							return 1.0f;

	default:
		break;
	}
	return 0.0f;
}


/*									//
//		���̃g���K�[��Ԏ擾		//
//									*/
float Input::GetJoyAxisTrigger(int nJoy, int nAxis) {
	// ���݊m�F
	if (nJoy < 0 || nJoy >= m_nJoy) return 0.0f;

	switch( nAxis ) {
	case JOY_X:
		// �O�t���[���`�F�b�N
		if( abs(m_diPrevJoyState[nJoy].lX) >= JOY_MAX_X * JOY_MOVE_NON )
			return 0.0f;
		// ���t���[���`�F�b�N
		if( abs(m_diJoyState[nJoy].lX) < JOY_MAX_X * JOY_MOVE_NON )
			return 0.0f;
		// ���E�`�F�b�N
		if (m_diJoyState[nJoy].lX < 0) {
			return -1.0f;
		} else {
			return 1.0f;
		}
	case JOY_Y:
		// �O�t���[���`�F�b�N
		if( abs(m_diPrevJoyState[nJoy].lY) >= JOY_MAX_Y * JOY_MOVE_NON )
			return 0.0f;
		// ���t���[���`�F�b�N
		if( abs(m_diJoyState[nJoy].lY) < JOY_MAX_Y * JOY_MOVE_NON )
			return 0.0f;
		// �㉺�`�F�b�N
		if (m_diJoyState[nJoy].lY < 0) {
			return -1.0f;
		} else {
			return 1.0f;
		}
	default:
		break;
	}
	return 0.0f;
}


/*									//
//			���̌X�������擾		//
//		(�E���玞�v����+,�t��-	*/
float Input::GetJoyAxisDegree( int nJoy ) {
	// ��O�m�F
	if (nJoy < 0 || nJoy >= m_nJoy) return -1000.0f;

	float X = (float)m_diJoyState[nJoy].lX;
	float Y = (float)m_diJoyState[nJoy].lY;

	// ����m�F
	if( !CheckMoveAxis(nJoy) )	return -1000.0f;

	// �p�x���o
	float rad = atan2f( Y, X );
	return ToDegree(rad);
}


/*									//
//			�\���L�[��Ԏ擾		//
//			(�ォ�玞�v����+		*/
int Input::GetJoyCross( int nJoy, int nPov ) {
	return m_diJoyState[nJoy].rgdwPOV[nPov] == -1 ? -1 : m_diJoyState[nJoy].rgdwPOV[nPov] / 100;
}


/*									//
//			����������������		//
//	PS4�R���g���[�����Ɏg�����		*/
bool Input::CheckMoveAxis( int nJoy ) {
	// ���̈ړ����������߂�
	long distance = Vec2Distance( m_diJoyState[nJoy].lX, m_diJoyState[nJoy].lY );

	// ���苗��
	long move = Vec2Distance( JOY_MAX_X, JOY_MAX_Y );
	move = (long)(move * JOY_MOVE_NON);

	return move <= distance;
}


/*									//
//		2D�x�N�g���Ԃ̒������擾	//
//									*/
long Input::Vec2Distance( long X, long Y ) {
	return (long)sqrtl(X * X + Y * Y);
}


//-------------------------------------------------------------------------------
// �}�E�X
/*									//
//		�{�^���̉�����Ԏ擾		//
//									*/
bool Input::GetMousePress(int nButton) {
	if (nButton < 0 || nButton >= 4) return false;
	return (m_diMouseState.rgbButtons[nButton] & 0x80) != 0;
}


/*									//
//		�{�^���̃g���K��Ԏ擾		//
//									*/
bool Input::GetMouseTrigger(int nButton) {
	if (nButton < 0 || nButton >= 4) return false;
	return (m_diPrevMouseState.rgbButtons[nButton] & 0x80) == 0 &&
		(m_diMouseState.rgbButtons[nButton] & 0x80) != 0;
}


/*									//
//		�{�^���̃����[�X��Ԏ擾	//
//									*/
bool Input::GetMouseRelease(int nButton) {
	if (nButton < 0 || nButton >= 4) return false;
	return (m_diPrevMouseState.rgbButtons[nButton] & 0x80) != 0 &&
		(m_diMouseState.rgbButtons[nButton] & 0x80) == 0;
}


/*									//
//				�ω��ʎ擾			//
//									*/
long Input::GetMouseAxis(int nAxis) {
	switch (nAxis) {
	case MOUSE_X:
		return m_diMouseState.lX;
	case MOUSE_Y:
		return m_diMouseState.lY;
	case MOUSE_Z:
		return m_diMouseState.lZ;
	}
	return 0L;
}