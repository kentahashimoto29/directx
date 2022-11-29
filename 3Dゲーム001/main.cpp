//========================================================
//
//ウインドウの生成等
//Author 橋本賢太
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

//マクロ定義
#define CLASS_NAME           "WindowClass"                         //ウインドウクラスの名前
#define WINDOW_NAME          "ポリゴンの描画処理"                  //ウインドウの名前
#define ID_BUTTON_FINISH     (101)                                 //終了ボタンのID

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//グローバル変数
LPDIRECT3D9 g_pD3D = NULL;                          //Direct3Dオブジェクトへのポインタ
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;              //Direct3Dデバイスへのポインタ
LPD3DXFONT g_pFont = NULL;                          //フォントへのポインタ

//=======================================
//メイン関数
//=======================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),                                   //WNDCLASSEXのメモリサイズ
		CS_CLASSDC,                                           //ウインドウのスタイル
		WindowProc,                                           //ウインドウプロシージャ
		0,                                                    //0にする
		0,                                                    //0にする
		hInstance,                                            //インスタンスハンドル
		LoadIcon(NULL, IDI_APPLICATION),                      //タスクバーのアイコン
		LoadCursor(NULL, IDC_ARROW),                          //マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),                           //クライアント領域の背景色
		NULL,                                                 //メニューバー
		CLASS_NAME,                                           //ウインドウクラスの名前
		LoadIcon(NULL, IDI_APPLICATION)                       //ファイルアイコン
	};
	HWND hWnd;                                                //ウインドウハンドル
	MSG msg;                                                  //メッセージを格納する変数

	RECT rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};        //画面サイズの構造体

	//ウインドウクラスの登録
	RegisterClassEx(&wcex);

	//
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウインドウを生成
	hWnd = CreateWindowEx(
		0,                                //拡張ウインドウスタイル
		CLASS_NAME,                       //ウインドウクラスの名前
		WINDOW_NAME,                      //ウインドウの名前
		WS_OVERLAPPEDWINDOW,              //ウインドウスタイル
		CW_USEDEFAULT,                    //ウインドウの左上X座標
		CW_USEDEFAULT,                    //ウインドウの左上Y座標
		(rect.right-rect.left),           //ウインドウの幅
		(rect.bottom - rect.top),         //ウインドウの高さ
		NULL,                             //親ウインドウのハンドル
		NULL,                             //メニューハンドルまたは子ウインドウID
		hInstance,                        //インスタンスハンドル
		NULL);                            //ウインドウ作成データ
										  //ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, TRUE)))
	{//初期化処理が失敗した場合
		return -1;
	}

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windousの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}

			else
			{
				//メッセージの設定
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}
		}

		else
		{//DirectXの処理
			//更新処理
			Update();

			//描画処理
			Draw();
		}
	}

	//終了処理
	Uninit();

	//ウインドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//ウインドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;                                                      //返り値を格納

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:             //キー押下にメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:          //[ESC]キーが押された
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
			break;
		}

	case WM_COMMAND:                  //コマンド発行のメッセージ
		if (LOWORD(wParam) == ID_BUTTON_FINISH)
		{//終了ボタンが押された
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

			if (nID == IDYES)
			{
				//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
				DestroyWindow(hWnd);
			}
		}
		break;

	case WM_CLOSE:           //閉じるボタン押下のメッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{
			//ウィンドウを破棄する(WM_DESTROYメッセージを送る)
			DestroyWindow(hWnd);
		}

		else
		{
			return 0;       //ウィンドウを終了しないようにする
		}
		break;

	case WM_LBUTTONDOWN:           //マウス左クリック
								   //対象ウィンドウにフォーカスを合わせる
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//初期化処理
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;                         //ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;                  //プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));        //パラメータのゼロクリア

	d3dpp.BackBufferWidth = SCREEN_WIDTH;                           //ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;                         //ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;                          //バックバッファの形式
	d3dpp.BackBufferCount = 1;                                      //バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;                       //ダブルバッファの切り替え
	d3dpp.EnableAutoDepthStencil = TRUE;                            //デプスバッファとスランシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;                      //デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow;                                       //ウインドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;     //リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;       //インターバル

	//Direct3Dデバイスの生成
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

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//デバッグ表示フォントの生成
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

	//キーボードの初期化処理
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//ポリゴンの初期化処理
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

//終了処理
void Uninit(void)
{
	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	//Direct3Dオブジェクト
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	//ポリゴンの終了処理
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

//更新処理
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

//描画処理
void Draw(void)
{
	//画面クリア(バックバッファとZバッファのクリア)
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合
		Setcamera();
			
		//ポリゴンの描画処理
		DrawMeshfield();
		/*DrawField();*/
		DrawBullet();
		DrawShadow();
		DrawModel();
		DrawBillboard();
		DrawWall();

		//描画終了
		g_pD3DDevice->EndScene();
	}

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}