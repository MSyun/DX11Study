// �f���Q�[�g�C���^�[�t�F�[�X
// 2016.12.30	�v���O�����쐬
// author		SyunMizuno


#pragma once


template<typename... Args>
class IDelegate {
public:
#pragma region method

	IDelegate() {}
	virtual ~IDelegate() {}

	// ���s�֐�
	virtual void Invoke(Args...) = 0;

#pragma endregion
};