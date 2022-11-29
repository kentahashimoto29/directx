//========================================================
//
//�E�C���h�E�̐�����
//Author ���{����
//
//========================================================
#include "main.h"
#include "meshfield.h"
#include "field.h"
#include "camera.h"
#include "light.h"
#include "input.h"
#include "model.h"
#include "shadow.h"
#include "Billboard.h"
#include "wall.h"
#include "Bullet.h"

//�}�N����`
#define CLASS_NAME           "WindowClass"                         //�E�C���h�E�N���X�̖��O
#define WINDOW_NAME          "�|���S���̕`�揈��"                  //�E�C���h�E�̖��O
#define ID_BUTTON_FINISH     (101)                                 //�I���{�^����ID

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//�O���[�o���ϐ�
LPDIRECT3D9 g_pD3D = NULL;                          //Direct3D�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;              //Direct3D�f�o�C�X�ւ̃|�C���^
LPD3DXFONT g_pFont = NULL;                          //�t�H���g�ւ̃|�C���^

//=======================================
//���C���֐�
//=======================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),                                   //WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,                                           //�E�C���h�E�̃X�^�C��
		WindowProc,                                           //�E�C���h�E�v���V�[�W��
		0,                                                    //0�ɂ���
		0,                                                    //0�ɂ���
		hInstance,                                            //�C���X�^���X�n���h��
		LoadIcon(NULL, IDI_APPLICATION),                      //�^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL, IDC_ARROW),                          //�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),                           //�N���C�A���g�̈�̔w�i�F
		NULL,                                                 //���j���[�o�[
		CLASS_NAME,                                           //�E�C���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION)                       //�t�@�C���A�C�R��
	};
	HWND hWnd;                                                //�E�C���h�E�n���h��
	MSG msg;                                                  //���b�Z�[�W���i�[����ϐ�

	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};        //��ʃT�C�Y�̍\����

	//�E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�C���h�E�𐶐�
	hWnd = CreateWindowEx(
		0,                                //�g���E�C���h�E�X�^�C��
		CLASS_NAME,                       //�E�C���h�E�N���X�̖��O
		WINDOW_NAME,                      //�E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,              //�E�C���h�E�X�^�C��
		CW_USEDEFAULT,                    //�E�C���h�E�̍���X���W
		CW_USEDEFAULT,                    //�E�C���h�E�̍���Y���W
		(rect.right-rect.left),           //�E�C���h�E�̕�
		(rect.bottom - rect.top),         //�E�C���h�E�̍���
		NULL,                             //�e�E�C���h�E�̃n���h��
		NULL,                             //���j���[�n���h���܂��͎q�E�C���h�EID
		hInstance,                        //�C���X�^���X�n���h��
		NULL);                            //�E�C���h�E�쐬�f�[�^
										  //�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//����������
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//���������������s�����ꍇ
		return -1;
	}

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windous�̏���
			if (msg.message == WM_QUIT)
			{
				break;
			}

			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}
		}

		else
		{//DirectX�̏���
			//�X�V����
			Update();

			//�`�揈��
			Draw();
		}
	}

	//�I������
	Uninit();

	//�E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//�E�C���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;                                                      //�Ԃ�l���i�[

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:             //�L�[�����Ƀ��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:          //[ESC]�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
			break;
		}

	case WM_COMMAND:                  //�R�}���h���s�̃��b�Z�[�W
		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{//�I���{�^���������ꂽ
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
				DestroyWindow(hWnd);
			}
		}
		break;

	case WM_CLOSE:           //����{�^�������̃��b�Z�[�W
		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO);

		if (nID == IDYES)
		{
			//�E�B���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)
			DestroyWindow(hWnd);
		}

		else
		{
			return 0;       //�E�B���h�E���I�����Ȃ��悤�ɂ���
		}
		break;

	case WM_LBUTTONDOWN:           //�}�E�X���N���b�N
								   //�ΏۃE�B���h�E�Ƀt�H�[�J�X�����킹��
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//����������
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;                         //�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;                  //�v���[���e�[�V�����p�����[�^

	//Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//�f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));        //�p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = SCREEN_WIDTH;                           //�Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                         //�Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;                          //�o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;                                      //�o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                       //�_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;                            //�f�v�X�o�b�t�@�ƃX�����V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                      //�f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;                                       //�E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;     //���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;       //�C���^�[�o��

	//Direct3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�f�o�b�O�\���t�H���g�̐���
	D3DXCreateFont(g_pD3DDevice,
		18,
		0,
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&g_pFont);

	//�L�[�{�[�h�̏���������
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�|���S���̏���������
	InitMeshfield();
	InitField();
	InitCamera();
	InitLight();
	InitBullet();
	InitShadow();
	InitModel();
	InitBillboard();
	InitWall();

	return S_OK;
}

//�I������
void Uninit(void)
{
	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3D�I�u�W�F�N�g
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//�|���S���̏I������
	UninitMeshfield();
	UninitField();
	UninitCamera();
	UninitLight();
	UninitBullet();
	UninitShadow();
	UninitModel();;
	UninitKeyboard();
	UninitBillboard();
	UninitWall();
}

//�X�V����
void Update(void)
{
	UpdateMeshfield();
	UpdateField();
	UpdateCamera();
	UpdateLight();
	UpdateBullet();
	UpdateShadow();
	UpdateModel();
	UpdateKeyboard();
	UpdateBillboard();
	UpdateWall();
}

//�`�揈��
void Draw(void)
{
	//��ʃN���A(�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A)
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ
		Setcamera();
			
		//�|���S���̕`�揈��
		DrawMeshfield();
		/*DrawField();*/
		DrawBullet();
		DrawShadow();
		DrawModel();
		DrawBillboard();
		DrawWall();

		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}