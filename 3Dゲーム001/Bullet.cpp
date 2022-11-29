#include "main.h"
#include "Bullet.h"
#include "shadow.h"

//マクロ定義
#define MAX_BULLET					(128)					//弾の最大数
#define HEIGHT_BULLET				(3.0f)					//弾の縦幅
#define WIDTH_BULLET				(3.0f)					//弾の横幅

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;					//テクスチャへのポインタ
Bullet g_Bullet[MAX_BULLET];

//==============================================
//弾の初期化処理
//==============================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_Bullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].nLife = 0;
		g_Bullet[nCntBullet].bUse = false;
	}

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D *pVtx;
	
	//頂点バッファをロック
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].nor3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].nor3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].nor3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].nor3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//頂点カラーの設定
		pVtx[0].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[0].tex3D = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex3D = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex3D = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex3D = D3DXVECTOR2(0.0f, 0.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//==============================================
//弾の終了処理
//==============================================
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//==============================================
//弾の更新処理
//==============================================
void UpdateBullet(void)
{
	int nCntBullet;
	SHADOW pShadow = GetShadow();
	VERTEX_3D *pVtx;					//頂点情報へのポインタ

	//頂点バッファをロックする
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{//弾が使用されていない

			//頂点座標の設定
			pVtx[0].pos3D = D3DXVECTOR3(- WIDTH_BULLET, + HEIGHT_BULLET, 0.0f);
			pVtx[1].pos3D = D3DXVECTOR3(+ WIDTH_BULLET, + HEIGHT_BULLET, 0.0f);
			pVtx[2].pos3D = D3DXVECTOR3(- WIDTH_BULLET, - HEIGHT_BULLET, 0.0f);
			pVtx[3].pos3D = D3DXVECTOR3(+ WIDTH_BULLET, - HEIGHT_BULLET, 0.0f);

			g_Bullet[nCntBullet].pos.x += g_Bullet[nCntBullet].move.x;
			g_Bullet[nCntBullet].pos.z += g_Bullet[nCntBullet].move.z;

			g_Bullet[nCntBullet].nLife--;

			if (g_Bullet[nCntBullet].nLife <= 0)
			{
				if (pShadow.Shadowtype == TYPESHADOW_BULLET)
				{
					pShadow.bUseShadow = false;
				}

				g_Bullet[nCntBullet].bUse = false;						//使用していない状態にする
			}
		}
		pVtx += 4;                      //該当の位置まで進める
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//==============================================
//弾の描画処理
//==============================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	D3DXMATRIX mtxTrans;		//計算用マトリックス
	D3DXMATRIX mtxView;			//ビューマトリックス取得

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{
			//ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Bullet[nCntBullet].g_mtxWorldBullet);

			//ビューマトリックスを取得
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//ポリゴンをカメラに対して正面に向ける
			D3DXMatrixInverse(&g_Bullet[nCntBullet].g_mtxWorldBullet, NULL, &mtxView);			//逆行列を求める
			g_Bullet[nCntBullet].g_mtxWorldBullet._41 = 0.0f;
			g_Bullet[nCntBullet].g_mtxWorldBullet._42 = 0.0f;
			g_Bullet[nCntBullet].g_mtxWorldBullet._43 = 0.0f;

			//位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCntBullet].pos.x, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_Bullet[nCntBullet].g_mtxWorldBullet, &g_Bullet[nCntBullet].g_mtxWorldBullet, &mtxTrans);

			//Zテストを無効にする
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCntBullet].g_mtxWorldBullet);

			//頂点バッファをデータストリーム設定
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);

			//テクスチャの設定
			pDevice->SetTexture(0, g_pTextureBullet);

			//ポリゴンの描画
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,				//プリミティブの種類
				nCntBullet * 4,						//最初の頂点インデックス
				2);									//プリミティブ数
		}
	}

	//Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//==============================================
//弾の設定
//==============================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == false)
		{//弾が使用されていない

			g_Bullet[nCntBullet].pos = D3DXVECTOR3(pos.x, pos.y + 3.0f, pos.z);
			g_Bullet[nCntBullet].rot = rot;
			g_Bullet[nCntBullet].move = D3DXVECTOR3(sinf(g_Bullet[nCntBullet].rot.y + D3DX_PI) * 1.5f, 0.0f, cosf(g_Bullet[nCntBullet].rot.y + D3DX_PI) * 1.5f);

			VERTEX_3D *pVtx;         //頂点情報へのポインタ

			//頂点バッファをロックする
			g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntBullet * 4);                      //該当の位置まで進める

			//頂点座標の設定
  			pVtx[0].pos3D = D3DXVECTOR3(-WIDTH_BULLET, +HEIGHT_BULLET, 0.0f);
		 	pVtx[1].pos3D = D3DXVECTOR3(+WIDTH_BULLET, +HEIGHT_BULLET, 0.0f);
			pVtx[2].pos3D = D3DXVECTOR3(-WIDTH_BULLET, -HEIGHT_BULLET, 0.0f);
			pVtx[3].pos3D = D3DXVECTOR3(+WIDTH_BULLET, -HEIGHT_BULLET, 0.0f);

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
			g_pVtxBuffBullet->Unlock();

			g_Bullet[nCntBullet].nLife = 100;
			g_Bullet[nCntBullet].bUse = true;               //使用している状態にする
			break;
		}
	}
}

Bullet GetBullet(void)
{
	return g_Bullet[0];
}