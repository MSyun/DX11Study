// TGAテクスチャファイル
// 2017.05.12	: プログラム作成
// author		: SyunMizuno



#pragma once


typedef struct _TGAImage {
	unsigned sizeX, sizeY;	// ピクセルサイズ
	unsigned char* data;	// ピクセルデータ
	unsigned type;			// ピクセルバイト長
	unsigned pixelDepth;	// ピクセルビット長
	unsigned alphaDepth;	// αチャンネルビット長
} TGAImage;

TGAImage* LoadTGA(const char* pszFName);