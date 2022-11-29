#include "main.h"
#include "light.h"

//グローバル変数宣言
D3DLIGHT9 g_light[2];                   //ライトの情報

//==============================================
//ライトの初期化処理
//==============================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	D3DXVECTOR3 vecDir;              //設定用方向ベクトル

	//ライトの情報をクリアする
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	//ライトの種類を設定
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;

	//ライトの拡散光を設定
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトの方向を設定
	vecDir = D3DXVECTOR3(0.1f, -0.2f, 0.1f);
	D3DXVec3Normalize(&vecDir, &vecDir);             //ベクトルを正規化する
	g_light[0].Direction = vecDir;

	vecDir = D3DXVECTOR3(-0.1f, -0.2f, -0.1f);
	D3DXVec3Normalize(&vecDir, &vecDir);             //ベクトルを正規化する
	g_light[1].Direction = vecDir;

	//ライトを設定する
	pDevice->SetLight(0, &g_light[0]);
	pDevice->SetLight(1, &g_light[1]);

	//ライトを有効にする
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
}

//==============================================
//ライトの終了処理
//==============================================
void UninitLight(void)
{

}
//==============================================
//ライトの更新処理
//==============================================
void UpdateLight(void)
{

}