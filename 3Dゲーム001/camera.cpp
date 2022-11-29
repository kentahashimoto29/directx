#include "main.h"
#include "camera.h"
#include "input.h"
#include "model.h"

//グローバル変数
Camera g_camera;                  //カメラの情報
float g_cameraDistance;           //視点と注視点の距離

//==============================================
//カメラの初期化処理
//==============================================
void InitCamera(void)
{
	g_camera.posV = D3DXVECTOR3(0.0f, 40.0f, -150.0f);
	g_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//対角線の長さを算出
	g_cameraDistance = sqrtf(g_camera.posV.y * g_camera.posV.y + g_camera.posV.z * g_camera.posV.z);

	//g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y) * g_cameraDistance;
	//g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y) * g_cameraDistance;

	//g_camera.posV.y = g_camera.posR.y - cosf(g_camera.rot.x) * g_cameraDistance;
	//g_camera.posV.z = g_camera.posR.z - sinf(g_camera.rot.x) * g_cameraDistance;
}

//==============================================
//カメラの終了処理
//==============================================
void UninitCamera(void)
{

}

//カメラの更新処理
void UpdateCamera(void)
{
	MODEL pModel = GetModel();

	g_camera.posR = pModel.g_posModel;
	g_camera.posV = D3DXVECTOR3(pModel.g_posModel.x, pModel.g_posModel.y + 40.0f, pModel.g_posModel.z - 150.0f);

	if (GetKeyboardPress(DIK_LEFT) == true)
	{
		g_camera.posR.x += sinf(D3DX_PI * -0.5f + g_camera.rot.y) * 0.5f;
		g_camera.posR.z += cosf(D3DX_PI * -0.5f + g_camera.rot.y) * 0.5f;
		g_camera.posV.x += sinf(D3DX_PI * -0.5f + g_camera.rot.y) * 0.5f;
		g_camera.posV.z += cosf(D3DX_PI * -0.5f + g_camera.rot.y) * 0.5f;
	}

	else if (GetKeyboardPress(DIK_RIGHT) == true)
	{
		g_camera.posR.x += sinf(D3DX_PI * 0.5f + g_camera.rot.y) * 0.5f;
		g_camera.posR.z += cosf(D3DX_PI * 0.5f + g_camera.rot.y) * 0.5f;
		g_camera.posV.x += sinf(D3DX_PI * 0.5f + g_camera.rot.y) * 0.5f;
		g_camera.posV.z += cosf(D3DX_PI * 0.5f + g_camera.rot.y) * 0.5f;
	}

	else if (GetKeyboardPress(DIK_UP) == true)
	{
		g_camera.posR.x += sinf(D3DX_PI * 0.0f + g_camera.rot.y) * 0.5f;
		g_camera.posR.z += cosf(D3DX_PI * 0.0f + g_camera.rot.y) * 0.5f;
		g_camera.posV.x += sinf(D3DX_PI * 0.0f + g_camera.rot.y) * 0.5f;
		g_camera.posV.z += cosf(D3DX_PI * 0.0f + g_camera.rot.y) * 0.5f;
	}

	else if (GetKeyboardPress(DIK_DOWN) == true)
	{
		g_camera.posR.x += sinf(D3DX_PI * 1.0f + g_camera.rot.y) * 0.5f;
		g_camera.posR.z += cosf(D3DX_PI * 1.0f + g_camera.rot.y) * 0.5f;
		g_camera.posV.x += sinf(D3DX_PI * 1.0f + g_camera.rot.y) * 0.5f;
		g_camera.posV.z += cosf(D3DX_PI * 1.0f + g_camera.rot.y) * 0.5f;
	}

	if (GetKeyboardPress(DIK_J) == true)
	{
		g_camera.rot.y += 0.01f;
	}

	else if (GetKeyboardPress(DIK_L) == true)
	{
		g_camera.rot.y -= 0.01f;
	}

	if (GetKeyboardPress(DIK_U) == true)
	{
		g_camera.rot.y -= 0.01f;
	}

	else if (GetKeyboardPress(DIK_O) == true)
	{
		g_camera.rot.y += 0.01f;
	}

	if (GetKeyboardPress(DIK_Q) == true)
	{
		g_camera.rot.x += 0.01f;
	}

	else if (GetKeyboardPress(DIK_Z) == true)
	{
		g_camera.rot.x -= 0.01f;
	}

	if (GetKeyboardPress(DIK_E) == true)
	{
		g_camera.rot.x += 0.01f;
	}

	else if (GetKeyboardPress(DIK_C) == true)
	{
		g_camera.rot.x -= 0.01f;
	}

	if (GetKeyboardPress(DIK_J) == true || GetKeyboardPress(DIK_L) == true)
	{
		g_camera.posV.x = g_camera.posR.x + sinf(g_camera.rot.y - D3DX_PI) * g_cameraDistance;
		g_camera.posV.z = g_camera.posR.z + cosf(g_camera.rot.y - D3DX_PI) * g_cameraDistance;
	}

	if (GetKeyboardPress(DIK_U) == true || GetKeyboardPress(DIK_O) == true)
	{
		g_camera.posR.x = g_camera.posV.x - sinf(g_camera.rot.y + D3DX_PI) * g_cameraDistance;
		g_camera.posR.z = g_camera.posV.z - cosf(g_camera.rot.y + D3DX_PI) * g_cameraDistance;
	}

	if (GetKeyboardPress(DIK_Q) == true || GetKeyboardPress(DIK_Z) == true)
	{
		g_camera.posV.y = g_camera.posR.y + cosf(g_camera.rot.x) * g_cameraDistance;
		g_camera.posV.z = g_camera.posR.z + sinf(g_camera.rot.x) * g_cameraDistance;
	}

	if (GetKeyboardPress(DIK_E) == true || GetKeyboardPress(DIK_C) == true)
	{
		g_camera.posR.y = g_camera.posV.y - cosf(g_camera.rot.x) * g_cameraDistance;
		g_camera.posR.z = g_camera.posV.z - sinf(g_camera.rot.x) * g_cameraDistance;
	}

	//カメラの補正
	if (g_camera.rot.y > D3DX_PI)
	{
		g_camera.rot.y = -D3DX_PI;
	}

	else if (g_camera.rot.y < -D3DX_PI)
	{
		g_camera.rot.y = D3DX_PI;
	}

	if (g_camera.rot.x > D3DX_PI)
	{
		g_camera.rot.x = -D3DX_PI;
	}

	else if (g_camera.rot.x < -D3DX_PI)
	{
		g_camera.rot.x = D3DX_PI;
	}
}

//==============================================
//カメラの設定処理
//==============================================
void Setcamera(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&g_camera.mtxProjection);

	//プロジェクションマトリックスを作成
	D3DXMatrixPerspectiveFovLH(&g_camera.mtxProjection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		1000.0f);

		//プロジェクションマトリックスの設定
		pDevice->SetTransform(D3DTS_PROJECTION, &g_camera.mtxProjection);

		//ビューマトリックスの初期化
		D3DXMatrixIdentity(&g_camera.mtxView);

		//ビューマトリックスの作成
		D3DXMatrixLookAtLH(&g_camera.mtxView,
			&g_camera.posV,
			&g_camera.posR,
			&g_camera.vecU);

		//ビューマトリックスの設定
		pDevice->SetTransform(D3DTS_VIEW, &g_camera.mtxView);
}

//==============================================
//カメラの設定
//==============================================
Camera GetCamera(void)
{
	return g_camera;
}