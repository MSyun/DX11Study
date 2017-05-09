// �Q�[���pDirectX11
// 2016. 5.10	:	�v���O�����쐬
// author		:	SyunMizuno


#include	"CheckScene.h"
#include	"../GameFramework/framework/Graphic/Graphics.h"
#include	"../GameFramework/framework/Convert/Convert.h"
#include	<d3dcompiler.h>
#include	<tchar.h>
#include	"../GameFramework/framework/Time/Time.h"

struct SimpleVertex {
	Point3 Pos;
	Vector3 Normal;
	Vector2 Tex;
};

struct SIMPLESHADER_CONSTANT_BUFFER {
	Matrix	mWorld;
	Matrix	mWVP;
	Vector4	vLightDir;
	Vector4	vDiffuse;
	Vector4	vEye;
};




CheckScene::CheckScene() :
	m_pVertexLayout(NULL),
	m_pVertexShader(NULL),
	m_pPixelShader(NULL),
	m_pConstantBuffer(NULL),
	m_pVertexBuffer(NULL)
{
}

CheckScene::~CheckScene() {

}

bool CheckScene::Init() {
	CreateShader();
	CreatePolygon();

	return true;
}

void CheckScene::Release() {
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pLight);

	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVertexLayout);
}

void CheckScene::Update() {

}

void CheckScene::Draw() {
	auto context = Graphics::GetDevice();

	Matrix mWorld;
	// ���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	static float an = 0.0f;
	an += Time::GetDeltaTime();
	MatrixRotationY(&mWorld, an);

	// �J����
	m_pCamera->Set();
	Vector3 pos = m_pCamera->GetTransform()->GetPos();

	// �g�p����V�F�[�_�̓o�^
	context->VSSetShader(m_pVertexShader, NULL, 0);
	context->PSSetShader(m_pPixelShader, NULL, 0);
	// �V�F�[�_�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	SIMPLESHADER_CONSTANT_BUFFER cb;
	HRESULT hr;
	hr = context->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		cb.mWorld = mWorld;
		MatrixTranspose(&cb.mWorld, &cb.mWorld);
		// ���[���h�A�J�����A�ˉe�s���n��
		Matrix m = mWorld * m_pCamera->GetView() * m_pCamera->GetProj();
		MatrixTranspose(&m, &m);
		cb.mWVP = m;
		// �J���[��n��
		cb.vDiffuse = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		// ���C�g�x�N�g����n��
		cb.vLightDir = m_pLight->GetDirection4();
		// �J�����̈ʒu�i���_�j���V�F�[�_�ɓn��
		cb.vEye = Vector4(pos.x, pos.y, pos.z, 0.0f);

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		context->Unmap(m_pConstantBuffer, 0);
	}
	// ���̃R���X�^���g�o�b�t�@�[���g���V�F�[�_�̓o�^
	context->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	context->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	// ���_�C���v�b�g���C�A�E�g���Z�b�g
	context->IASetInputLayout(m_pVertexLayout);
	// �v���~�e�B�u�E�g�|���W�[���Z�b�g
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���\���V�F�[�_�ɓn��
	auto samp = m_pTexture->GetSample();
	auto tex = m_pTexture->GetTexture();
	context->PSSetSamplers(0, 1, &samp);
	context->PSSetShaderResources(0, 1, &tex);

	// �v���~�e�B�u�������_�����O
	context->Draw(4, 0);
}

void CheckScene::CreateShader() {
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	ID3D11Device* device = IResource::GetDevice();

	// �u���u����o�[�e�b�N�X�V�F�[�_�쐬
	HRESULT hr;
	hr = D3DX11CompileFromFile(
		"Phong.hlsl",
		NULL,
		NULL,
		"VS",
		"vs_5_0",
		0,
		0,
		NULL,
		&pCompiledShader,
		&pErrors,
		NULL);
	if (FAILED(hr)) {
		MessageBox(0, (LPCTSTR)pErrors->GetBufferPointer(), _T("ERROR"), MB_OK);
		return;
	}
	SAFE_RELEASE(pErrors);

	hr = device->CreateVertexShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL,
		&m_pVertexShader);
	if (FAILED(hr)) {
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, "�o�[�e�b�N�X�V�F�[�_�쐬���s", NULL, MB_OK);
		return;
	}

	// ���_�C���v�b�g���C�A�E�g���`
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	// ���_�C���v�b�g���C�A�E�g���쐬
	hr = device->CreateInputLayout(
		layout,
		numElements,
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		&m_pVertexLayout);
	if (FAILED(hr))	return;

	// �u���u����s�N�Z���V�F�[�_�쐬
	hr = D3DX11CompileFromFile(
		"Phong.hlsl",
		NULL,
		NULL,
		"PS",
		"ps_5_0",
		0,
		0,
		NULL,
		&pCompiledShader,
		&pErrors,
		NULL);
	if (FAILED(hr)) {
		MessageBox(0, (LPCTSTR)pErrors->GetBufferPointer(), _T("ERROR"), MB_OK);
		return;
	}
	SAFE_RELEASE(pErrors);
	hr = device->CreatePixelShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL,
		&m_pPixelShader);
	if (FAILED(hr)) {
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, (LPCTSTR)pErrors->GetBufferPointer(), NULL, MB_OK);
		return;
	}
	SAFE_RELEASE(pCompiledShader);

	// �R���X�^���g�o�b�t�@�\�쐬
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SIMPLESHADER_CONSTANT_BUFFER);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	hr = device->CreateBuffer(&cb, NULL, &m_pConstantBuffer);
	if (FAILED(hr))	return;
}

void CheckScene::CreatePolygon() {
	HRESULT hr;
	ID3D11Device* device = IResource::GetDevice();

	// �o�[�e�b�N�X�o�b�t�@�[�쐬
	SimpleVertex vertices[] = {
		Vector3(-0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0, 1),
		Vector3(-0.5f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(0, 0),
		Vector3(0.5f, -0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1, 1),
		Vector3(0.5f, 0.5f, 0.0f), Vector3(0.0f, 0.0f, -1.0f), Vector2(1, 0),
	};
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimpleVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	hr = device->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);
	if (FAILED(hr))	return;

	// �o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	Graphics::GetDevice()->IASetVertexBuffers(
		0,
		1,
		&m_pVertexBuffer,
		&stride,
		&offset);

	m_pTexture = GetResourceManager<Texture>()->Create("data/Texture/Sprite.jpg");
	m_pCamera = NEW Camera;
	m_pCamera->GetTransform()->SetPos(0.0f, 1.0f, -2.0f);
	m_pCamera->GetTransform()->Rotate(-25.0f, 0.0f, 0.0f);
	//	m_pMesh = GetResourceManager<Mesh>()->Create("data/Mesh/x-wing.fbx");
	m_pLight = NEW Light;
	m_pLight->GetTransform()->SetPos(0.0f, 1.0f, -2.0f);
	m_pLight->GetTransform()->Rotate(-20.0f, 0.0f, 0.0f);
}