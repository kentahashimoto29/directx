#include "main.h"
#include "wall.h"
#include "Bullet.h"
#include "model.h"

#define NUM_WALL                                 (4)               //壁の総数

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;			//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;				//テクスチャへのポインタ
WALL g_Wall[NUM_WALL];

//==============================================
//壁の初期化処理
//==============================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\wall.jpg",
		&g_pTextureWall);

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUM_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	g_Wall[0].posWall = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	g_Wall[1].posWall = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	g_Wall[2].posWall = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	g_Wall[3].posWall = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	g_Wall[0].rotWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Wall[1].rotWall = D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f);
	g_Wall[2].rotWall = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Wall[3].rotWall = D3DXVECTOR3(0.0f, D3DX_PI * 3 / 2, 0.0f);

	g_Wall[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	g_Wall[1].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	g_Wall[2].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	g_Wall[3].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		if (nCntWall >= 3)
		{
			g_Wall[nCntWall].vecLine = D3DXVECTOR3(g_Wall[0].pos.x - g_Wall[nCntWall].pos.x, 0.0f, g_Wall[0].pos.z - g_Wall[nCntWall].pos.z);
		}

		else
		{
			g_Wall[nCntWall].vecLine = D3DXVECTOR3(g_Wall[nCntWall + 1].pos.x - g_Wall[nCntWall].pos.x, 0.0f, g_Wall[nCntWall + 1].pos.z - g_Wall[nCntWall].pos.z);
		}
	}

	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		//頂点座標の設定
		pVtx[0].pos3D = D3DXVECTOR3(-150.0f, 300.0f, 150.0f);
		pVtx[1].pos3D = D3DXVECTOR3(150.0f, 300.0f, 150.0f);
		pVtx[2].pos3D = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);
		pVtx[3].pos3D = D3DXVECTOR3(150.0f, 0.0f, 150.0f);

		//法線ベクトル
		pVtx[0].nor3D = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor3D = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor3D = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor3D = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

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
	g_pVtxBuffWall->Unlock();
}

//==============================================
//壁の終了処理
//==============================================
void UninitWall(void)
{
	//テクスチャの破棄
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

}

//==============================================
//壁の更新処理
//==============================================
void UpdateWall(void)
{
	Bullet pBullet = GetBullet();
	MODEL pModel = GetModel();

	if (pModel.g_posModel.z - pModel.g_VtxMinModel.z >= g_Wall[0].posWall.z)
	{
		pModel.g_posModel.z = g_Wall[0].posWall.z + pModel.g_VtxMinModel.z;
	}

	//for (int nCntWall = 0; nCntWall < 2; nCntWall++)
	//{
	//pBullet.vecToPos = D3DXVECTOR3(pBullet.pos.x - g_Wall[nCntWall].pos.x, 0.0f, pBullet.pos.z - g_Wall[nCntWall].pos.z);

	//	if (g_Wall[nCntWall].vecLine.z * pBullet.vecToPos.x - g_Wall[nCntWall].vecLine.x * pBullet.vecToPos.z <= 0.0f)
	//	{
	//		pBullet.bUse = false;						//使用していない状態にする
	//	}
	//}

}

//==============================================
//壁の描画処理
//==============================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;    //計算用マトリックス


	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorldWall);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rotWall.y, g_Wall[nCntWall].rotWall.x, g_Wall[nCntWall].rotWall.z);

		D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorldWall, &g_Wall[nCntWall].mtxWorldWall, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].posWall.x, g_Wall[nCntWall].posWall.y, g_Wall[nCntWall].posWall.z);

		D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorldWall, &g_Wall[nCntWall].mtxWorldWall, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorldWall);

		//頂点バッファをデータストリーム設定
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureWall);

		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,					//プリミティブの種類
			nCntWall * 4,							//最初の頂点インデックス
			2);										//プリミティブ数
	}
}