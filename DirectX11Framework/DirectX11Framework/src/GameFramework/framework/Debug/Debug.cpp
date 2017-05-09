#include	"Debug.h"
#include	<tchar.h>




/*									//
//			�R���X�g���N�^			//
//									*/
Debug::Debug() {

}


/*									//
//			�f�X�g���N�^			//
//									*/
Debug::~Debug() {
}


#pragma region Log
/*									//
//		�G�f�B�^�[��Ƀ��O��\��	//
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
//			�G���[���O�̕\��		//
//									*/
// �G�f�B�^�[�������Ŏ~�܂�̂�F10�ŏꏊ���m�F���Ă�������
void Debug::LogError(const string& message) {
#ifdef _DEBUG
	string st(message);
	st = "Error : " + st;
	Log(st);
	DebugBreak();
#endif // DEBUG
}


/*									//
//			�f�o�C�X���X�g			//
//									*/
HRESULT Debug::InvalidateDeviceObjects() {
	return S_OK;
}


/*									//
//			�f�o�C�X���Z�b�g		//
//									*/
HRESULT Debug::RestoreDeviceObjects() {
	return S_OK;
}