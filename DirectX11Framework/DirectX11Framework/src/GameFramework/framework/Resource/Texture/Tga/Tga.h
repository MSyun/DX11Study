// TGA�e�N�X�`���t�@�C��
// 2017.05.12	: �v���O�����쐬
// author		: SyunMizuno



#pragma once


typedef struct _TGAImage {
	unsigned sizeX, sizeY;	// �s�N�Z���T�C�Y
	unsigned char* data;	// �s�N�Z���f�[�^
	unsigned type;			// �s�N�Z���o�C�g��
	unsigned pixelDepth;	// �s�N�Z���r�b�g��
	unsigned alphaDepth;	// ���`�����l���r�b�g��
} TGAImage;

TGAImage* LoadTGA(const char* pszFName);