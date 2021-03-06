// オイラー角
// 2016. 5. 5	:	プログラム作成
// author		:	SyunMizuno


#include	"EulerAngles.h"
#include	"../Quaternion/Quaternion.h"


namespace MSLib {

	// 恒等オイラー角のグローバルな定数
	// ところで、このオブジェクトが（他のオブジェクトに対して）いつ作られるのか正確には
	// 分からない場合がある
	// このため、このオブジェクトは、初期化される前に参照可能である
	// しかしながら、ほとんどの実装では、他のオブジェクトが作成される前のプログラムの
	// スタートアップ時に何らかの方法で0に初期化される

	const EulerAngles kEularAnglesIdentity(0.0f, 0.0f, 0.0f);



	// オイラー角の3つ組を正準値に設定する
	// これは、このオイラー角の3D空間での方向の表現としての意味は変更しないが
	// 子の角度が各速度などの他の目的用であれば、この操作は有効ではなくなる
	void EulerAngles::canonize() {
		// 最初に、ピッチを範囲 -π．．．πにラップする
	//	pitch = wrap
	}

};