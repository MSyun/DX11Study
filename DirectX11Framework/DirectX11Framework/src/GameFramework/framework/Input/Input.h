//
// DirectInput クラス定義
//
#pragma once

#include <windows.h>
#include <tchar.h>
#define DIRECTINPUT_VERSION 0x0800	// DirectX8 を明示
#include <dinput.h>					// DirectInput 関連のヘッダ


namespace MSLib {

	//-------- キーボード関係
#define MAX_KEY			256			// キー数

//-------- ジョイスティック関係
#define JOY_X			0			// Ｘ軸
#define JOY_Y			1			// Ｙ軸

//-------- マウス関係
#define MOUSE_X			0			// Ｘ軸
#define MOUSE_Y			1			// Ｙ軸
#define MOUSE_Z			2			// Ｚ軸

//-------- ゲームパッド関係
#define MAX_JOY			4			// 最大認識接続数
#define JOY_MIN_X		-32768		// Ｘ軸最小値
#define JOY_MAX_X		32767		// Ｘ軸最大値
#define JOY_MIN_Y		-32768		// Ｙ軸最小値
#define JOY_MAX_Y		32767		// Ｙ軸最大値

#define	JOY_MOVE_NON	0.3			// 軸の遊び値(0.0f 〜 1.0f

	class Input {
	private:
		static LPDIRECTINPUT8		m_pDI;						// DirectInput8 オブジェクト
		static LPDIRECTINPUTDEVICE8	m_pDIDeviceKey;				// DirectInputDevice8 オブジェクト
		static BYTE					m_diKeyState[MAX_KEY];		// キーボード情報取得バッファ
		static BYTE					m_diPrevKeyState[MAX_KEY];	// 直前のキーボード情報
		static LPDIRECTINPUTDEVICE8	m_pDIDeviceMouse;			// DirectInputDevice8 オブジェクト
		static DIMOUSESTATE			m_diMouseState;				// マウス情報取得バッファ
		static DIMOUSESTATE			m_diPrevMouseState;			// 直前のマウス情報
		static LPDIRECTINPUTDEVICE8	m_pDIDeviceJoy[MAX_JOY];	// DirectInputDevice8 オブジェクト
		static DIJOYSTATE			m_diJoyState[MAX_JOY];		// ジョイスティック情報取得バッファ
		static DIJOYSTATE			m_diPrevJoyState[MAX_JOY];	// 直前のジョイスティック情報
		static int					m_nJoy;						// ジョイスティック接続数


	public:
		Input(void);
		virtual ~Input(void);

		static void Init(HWND hWnd);
		static void Fin(void);
		static void Update(void);

		//----- キーボード
		static bool	GetKeyPress(int nKey);
		static int	GetKeyPressButton();
		static bool	GetKeyTrigger(int nKey);
		static int	GetKeyTriggerButton();
		static bool	GetKeyRelease(int nKey);

		//----- パッド
		static int		GetNumJoystick(void);
		static bool		GetJoyPress(int nJoy, int nButton);
		static int		GetJoyPressButton(int nJoy);
		static bool		GetJoyTrigger(int nJoy, int nButton);
		static int		GetJoyTriggerButton(int nJoy);
		static bool		GetJoyRelease(int nJoy, int nButton);
		static float	GetJoyAxisPress(int nJoy, int nAxis);
		static float	GetJoyAxisTrigger(int nJoy, int nAxis);
		static float	GetJoyAxisDegree(int nJoy);
		static int		GetJoyCross(int nJoy, int nPov = 0);

		//----- マウス
		static bool GetMousePress(int nButton);
		static bool GetMouseTrigger(int nButton);
		static bool GetMouseRelease(int nButton);
		static long GetMouseAxis(int nAxis);

	private:
		static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

		// 軸が動いたか判定（PS4コントローラ等に使えるよ
		static bool CheckMoveAxis(int nJoy);
		static long Vec2Distance(long X, long Y);
	};

};