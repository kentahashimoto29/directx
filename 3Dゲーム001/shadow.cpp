#include "main.h"
#include "shadow.h"
#include "model.h"
#include "field.h"
#include "Bullet.h"

//マクロ定義
#define MAX_SHADOW					(256)					//影の最大数
#define HEIGHT_SHADOWPLAYER			(14.0f)					//プレイヤーの影の縦幅
#define WIDTH_SHADOWPLAYER			(7.0f)					//プレイヤーの影の横幅
#define HEIGHT_SHADOWBULLET			(3.0f)					//弾の影の縦幅
#define WIDTH_SHADOWBULLET			(3.0f)					//弾の影の横幅

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;			//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;					//テクスチャへのポインタ
SHADOW g_Shadow[MAX_SHADOW];

//==============================================
//影の初期化処理
//==============================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_Shadow[nCntShadow].g_posShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].g_rotShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].bUseShadow = false;
		g_Shadow[nCntShadow].Shadowtype = TYPESHADOW_NOME;
	}

	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//頂点座標の設定
		pVtx[0].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex3D = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex3D = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex3D = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex3D = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffShadow->Unlock();
}

//==============================================
//影の終了処理
//==============================================
void UninitShadow(void)
{
	//テクスチャの破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

}

//==============================================
//影の更新処理
//==============================================
void UpdateShadow(void)
{
	MODEL pModel = GetModel();
	FIELD pField = GetField();
	Bullet pBullet = GetBullet();

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUseShadow == true)
		{//弾が使用されている
			if (g_Shadow[nCntShadow].Shadowtype == TYPESHADOW_PLAYER)
			{
				g_Shadow[nCntShadow].g_posShadow = pModel.g_posModel;
				g_Shadow[nCntShadow].g_posShadow.y = pField.g_posField.y;
				g_Shadow[nCntShadow].g_rotShadow = pModel.g_rotModel;
			}

			else if (g_Shadow[nCntShadow].Shadowtype == TYPESHADOW_BULLET)
			{
				g_Shadow[nCntShadow].g_posShadow = pBullet.pos;
				g_Shadow[nCntShadow].g_posShadow.y = pField.g_posField.y;
			}
		}
 	}
}

//==============================================
//影の描画処理
//==============================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;    //計算用マトリックス

	//減算合成の設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUseShadow == true)
		{//弾が使用されている

			if (g_Shadow[nCntShadow].Shadowtype == TYPESHADOW_PLAYER)
			{	//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Shadow[nCntShadow].g_mtxWorldShadow);

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].g_rotShadow.y, g_Shadow[nCntShadow].g_rotShadow.x, g_Shadow[nCntShadow].g_rotShadow.z);

				D3DXMatrixMultiply(&g_Shadow[nCntShadow].g_mtxWorldShadow, &g_Shadow[nCntShadow].g_mtxWorldShadow, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].g_posShadow.x, g_Shadow[nCntShadow].g_posShadow.y, g_Shadow[nCntShadow].g_posShadow.z);

				D3DXMatrixMultiply(&g_Shadow[nCntShadow].g_mtxWorldShadow, &g_Shadow[nCntShadow].g_mtxWorldShadow, &mtxTrans);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].g_mtxWorldShadow);

				//頂点バッファをデータストリーム設定
				pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

				//頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureShadow);

				//ポリゴンの描画
				pDevice->DrawPrimitive(
					D3DPT_TRIANGLESTRIP,					//プリミティブの種類
					nCntShadow * 4,							//最初の頂点インデックス
					2);										//プリミティブ数
			}

			else if (g_Shadow[nCntShadow].Shadowtype == TYPESHADOW_BULLET)
			{	//ワールドマトリックスの初期化
				D3DXMatrixIdentity(&g_Shadow[nCntShadow].g_mtxWorldShadow);

				//向きを反映
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].g_rotShadow.y, g_Shadow[nCntShadow].g_rotShadow.x, g_Shadow[nCntShadow].g_rotShadow.z);

				D3DXMatrixMultiply(&g_Shadow[nCntShadow].g_mtxWorldShadow, &g_Shadow[nCntShadow].g_mtxWorldShadow, &mtxRot);

				//位置を反映
				D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].g_posShadow.x, g_Shadow[nCntShadow].g_posShadow.y, g_Shadow[nCntShadow].g_posShadow.z);

				D3DXMatrixMultiply(&g_Shadow[nCntShadow].g_mtxWorldShadow, &g_Shadow[nCntShadow].g_mtxWorldShadow, &mtxTrans);

				//ワールドマトリックスの設定
				pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].g_mtxWorldShadow);

				//頂点バッファをデータストリーム設定
				pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

				//頂点フォーマットの設定
				pDevice->SetFVF(FVF_VERTEX_3D);

				//テクスチャの設定
				pDevice->SetTexture(0, g_pTextureShadow);

				//ポリゴンの描画
				pDevice->DrawPrimitive(
					D3DPT_TRIANGLESTRIP,					//プリミティブの種類
					nCntShadow * 4,							//最初の頂点インデックス
					2);										//プリミティブ数
			}
		}
	}

   //通常の合成に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void SetShadow(TYPESHADOW type, bool bUseShadow)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUseShadow == false)
		{//弾が使用されていない

			if (type == TYPESHADOW_PLAYER)
			{
				VERTEX_3D *pVtx;         //頂点情報へのポインタ

										 //頂点バッファをロックする
				g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

				pVtx += (nCntShadow * 4);                      //該当の位置まで進める

															   //頂点座標の設定
				pVtx[0].pos3D = D3DXVECTOR3(-WIDTH_SHADOWPLAYER, 0.0f, HEIGHT_SHADOWPLAYER);
				pVtx[1].pos3D = D3DXVECTOR3(WIDTH_SHADOWPLAYER, 0.0f, HEIGHT_SHADOWPLAYER);
				pVtx[2].pos3D = D3DXVECTOR3(-WIDTH_SHADOWPLAYER, 0.0f, -HEIGHT_SHADOWPLAYER);
				pVtx[3].pos3D = D3DXVECTOR3(WIDTH_SHADOWPLAYER, 0.0f, -HEIGHT_SHADOWPLAYER);

				pVtx[0].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[1].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[2].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[3].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//頂点カラーの設定
				pVtx[0].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);

				//テクスチャ座標の設定
				pVtx[0].tex3D = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex3D = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex3D = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex3D = D3DXVECTOR2(1.0f, 1.0f);

				//頂点バッファをアンロックする
				g_pVtxBuffShadow->Unlock();

				g_Shadow[nCntShadow].Shadowtype = TYPESHADOW_PLAYER;
				g_Shadow[nCntShadow].bUseShadow = bUseShadow;               //使用している状態にする
				break;
			}

			else if (type == TYPESHADOW_BULLET)
			{
				VERTEX_3D *pVtx;         //頂点情報へのポインタ

										 //頂点バッファをロックする
				g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

				pVtx += (nCntShadow * 4);                      //該当の位置まで進める

															   //頂点座標の設定
				pVtx[0].pos3D = D3DXVECTOR3(-WIDTH_SHADOWBULLET, 0.0f, HEIGHT_SHADOWBULLET);
				pVtx[1].pos3D = D3DXVECTOR3(WIDTH_SHADOWBULLET, 0.0f, HEIGHT_SHADOWBULLET);
				pVtx[2].pos3D = D3DXVECTOR3(-WIDTH_SHADOWBULLET, 0.0f, -HEIGHT_SHADOWBULLET);
				pVtx[3].pos3D = D3DXVECTOR3(WIDTH_SHADOWBULLET, 0.0f, -HEIGHT_SHADOWBULLET);

				pVtx[0].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[1].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[2].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[3].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				//頂点カラーの設定
				pVtx[0].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);

				//テクスチャ座標の設定
				pVtx[0].tex3D = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex3D = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[2].tex3D = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[3].tex3D = D3DXVECTOR2(1.0f, 1.0f);

				//頂点バッファをアンロックする
				g_pVtxBuffShadow->Unlock();

				g_Shadow[nCntShadow].Shadowtype = TYPESHADOW_BULLET;
				g_Shadow[nCntShadow].bUseShadow = bUseShadow;               //使用している状態にする
				break;
			}
		}
	}
}

SHADOW GetShadow(void)
{
	return g_Shadow[0];
}