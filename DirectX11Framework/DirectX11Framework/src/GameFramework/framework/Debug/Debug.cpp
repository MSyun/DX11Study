#include	"Debug.h"
#include	<tchar.h>




/*									//
//			コンストラクタ			//
//									*/
Debug::Debug() {

}


/*									//
//			デストラクタ			//
//									*/
Debug::~Debug() {
}


#pragma region Log
/*									//
//		エディター上にログを表示	//
//									*/
void Debug::Log(const string& message) {
	string st(message);
	st += "\n";
	OutputDebugString(st.c_str());
}
void Debug::Log(const Vector2& val) {
	string st = "( " +
		to_string(val.x) + ", " +
		to_string(val.y) +
		" )\n";
	OutputDebugString(st.c_str());
}
void Debug::Log(const Vector3& val) {
	string st =  "( " +
		to_string(val.x) + ", " +
		to_string(val.y) + ", " +
		to_string(val.z) +
		" )\n";
	OutputDebugString(st.c_str());
}
void Debug::Log(const Vector4& val) {
	string st = "( " +
		to_string(val.x) + ", " +
		to_string(val.y) + ", " +
		to_string(val.z) + ", " +
		to_string(val.w) +
		" )\n";
	OutputDebugString(st.c_str());
}
void Debug::Log(const Quaternion& qua) {
	string st = "( " +
		to_string(qua.x) + ", " +
		to_string(qua.y) + ", " +
		to_string(qua.z) + ", " +
		to_string(qua.w) +
		" )\n";
	OutputDebugString(st.c_str());
}
#pragma endregion


/*									//
//			エラーログの表示		//
//									*/
// エディターがここで止まるのでF10で場所を確認してください
void Debug::LogError(const string& message) {
#ifdef _DEBUG
	string st(message);
	st = "Error : " + st;
	Log(st);
	DebugBreak();
#endif // DEBUG
}


/*									//
//			デバイスロスト			//
//									*/
HRESULT Debug::InvalidateDeviceObjects() {
	return S_OK;
}


/*									//
//			デバイスリセット		//
//									*/
HRESULT Debug::RestoreDeviceObjects() {
	return S_OK;
}