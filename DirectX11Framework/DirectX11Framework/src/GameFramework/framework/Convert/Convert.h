//////////////////////////////////////////////////////////////
// �ϊ�
// 2016. 8.3	�v���O�����쐬
// Author		SyunMizuno
//////////////////////////////////////////////////////////////

#pragma once


#define	DX11

#if defined(_DEBUG) && !defined(NEW)
#define new		::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif



#ifdef DX9
#include	<d3dx9.h>
#include	<d3d9.h>
#pragma comment ( lib, "d3d9.lib" )		// �`�揈���ɕK�v
#pragma comment ( lib, "d3dx9.lib" )	// [d3d9.lib]�̊g�����C�u����
#pragma comment ( lib, "dxguid.lib" )	// DirectX�R���|�[�l���g�g�p�ɕK�v

	typedef	D3DXMATRIX		Matrix;
	typedef	D3DXVECTOR2		Point2;
	typedef	D3DXVECTOR3		Point3;
	typedef	D3DXVECTOR4		Point4;
	typedef	D3DXVECTOR2		Vector2;
	typedef	D3DXVECTOR3		Vector3;
	typedef	D3DXVECTOR4		Vector4;
	typedef D3DXQUATERNION	Quaternion;
	typedef	D3DXCOLOR		Color;

#endif

#ifdef DX11
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dCompiler.lib")

#pragma warning( disable : 4005 )


#include	"../Math/Vector/Vector2/Vector2.h"
#include	"../Math/Vector/Vector3/Vector3.h"
#include	"../Math/Vector/Vector4/Vector4.h"
#include	"../Math/Matrix/Matrix4x4/Matrix4x4.h"
#include	"../Math/Funcs/MathFuncs.h"
#include	"../Math/Quaternion/Quaternion.h"

#endif

