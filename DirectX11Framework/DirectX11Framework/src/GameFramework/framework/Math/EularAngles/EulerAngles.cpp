// �I�C���[�p
// 2016. 5. 5	:	�v���O�����쐬
// author		:	SyunMizuno


#include	"EulerAngles.h"
#include	"../Quaternion/Quaternion.h"




// �P���I�C���[�p�̃O���[�o���Ȓ萔
// �Ƃ���ŁA���̃I�u�W�F�N�g���i���̃I�u�W�F�N�g�ɑ΂��āj�������̂����m�ɂ�
// ������Ȃ��ꍇ������
// ���̂��߁A���̃I�u�W�F�N�g�́A�����������O�ɎQ�Ɖ\�ł���
// �������Ȃ���A�قƂ�ǂ̎����ł́A���̃I�u�W�F�N�g���쐬�����O�̃v���O������
// �X�^�[�g�A�b�v���ɉ��炩�̕��@��0�ɏ����������

const EulerAngles kEularAnglesIdentity(0.0f, 0.0f, 0.0f);



// �I�C���[�p��3�g�𐳏��l�ɐݒ肷��
// ����́A���̃I�C���[�p��3D��Ԃł̕����̕\���Ƃ��Ă̈Ӗ��͕ύX���Ȃ���
// �q�̊p�x���e���x�Ȃǂ̑��̖ړI�p�ł���΁A���̑���͗L���ł͂Ȃ��Ȃ�
void EulerAngles::canonize() {
	// �ŏ��ɁA�s�b�`��͈� -�΁D�D�D�΂Ƀ��b�v����
//	pitch = wrap
}