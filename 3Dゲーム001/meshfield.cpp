#include "main.h"
#include "meshfield.h"

//マクロ定義
#define NUM_MESHFIELD					(4)

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;					//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;				//インデクスバッファへのポインタ
MESHFIELD g_Field[NUM_MESHFIELD];
float nCntTexX = 1.0f, nCntTexY = 0.0f;

//==============================================
//フィールドの初期化処理
//==============================================
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\tsuti000.jpg",
		&g_pTextureMeshfield);

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 14,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	g_Field[0].g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Field[0].g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Field[1].g_posMeshfield = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	g_Field[1].g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Field[2].g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	g_Field[2].g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Field[3].g_posMeshfield = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	g_Field[3].g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos3D = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	pVtx[1].pos3D = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	pVtx[2].pos3D = D3DXVECTOR3(150.0f, 0.0f, 50.0f);
	pVtx[3].pos3D = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[4].pos3D = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	pVtx[5].pos3D = D3DXVECTOR3(150.0f, 0.0f, -50.0f);
	pVtx[6].pos3D = D3DXVECTOR3(-50.0f, 0.0f, -150.0f);
	pVtx[7].pos3D = D3DXVECTOR3(50.0f, 0.0f, -150.0f);
	pVtx[8].pos3D = D3DXVECTOR3(150.0f, 0.0f, -150.0f);

	for (int nCntField = 0; nCntField < 9; nCntField++)
	{
		pVtx[nCntField].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[nCntField].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	pVtx[0].tex3D = D3DXVECTOR2(nCntTexX, nCntTexY);

	//テクスチャ座標の設定
	for (int nCntMeshField1 = 0; nCntMeshField1 < 3; nCntMeshField1++)
	{
		for (int nCntMeshField2 = 1; nCntMeshField2 < 4; nCntMeshField2++)
		{
			if (nCntMeshField2 == 1)
			{
				nCntTexY += 1.0f;
			}

			else if (nCntMeshField2 == 2)
			{
				if (nCntTexX == 1.0f)
				{
					nCntTexX = 0.0f;
				}

				else if (nCntTexX == 0.0f)
				{
					nCntTexX = 1.0f;
				}

				if (nCntTexY == 1.0f)
				{
					nCntTexY = 0.0f;
				}

				else if (nCntTexY == 0.0f)
				{
					nCntTexY = 1.0f;
				}
			}

			pVtx[nCntMeshField2 + 3 * nCntMeshField1].tex3D = D3DXVECTOR2(nCntTexX, nCntTexY);
		}
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMeshfield->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	WORD *pIdx;					//インデックス情報へのポインタ

	//インデックスバッファをロックし、頂点番号へのポインタを取得
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	//頂点番号データの設定
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//インデックスバッファをアンロック
	g_pIdxBuffMeshField->Unlock();
}

//==============================================
//フィールドの終了処理
//==============================================
void UninitMeshfield(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

}

//==============================================
//フィールドの更新処理
//==============================================
void UpdateMeshfield(void)
{

}

//==============================================
//フィールドの描画処理
//==============================================
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;    //計算用マトリックス

	for (int nCntField = 0; nCntField < NUM_MESHFIELD; nCntField++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_Field[nCntField].g_mtxWorldMeshfield);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Field[nCntField].g_rotMeshfield.y, g_Field[nCntField].g_rotMeshfield.x, g_Field[nCntField].g_rotMeshfield.z);

		D3DXMatrixMultiply(&g_Field[nCntField].g_mtxWorldMeshfield, &g_Field[nCntField].g_mtxWorldMeshfield, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_Field[nCntField].g_posMeshfield.x, g_Field[nCntField].g_posMeshfield.y, g_Field[nCntField].g_posMeshfield.z);

		D3DXMatrixMultiply(&g_Field[nCntField].g_mtxWorldMeshfield, &g_Field[nCntField].g_mtxWorldMeshfield, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_Field[nCntField].g_mtxWorldMeshfield);

		//頂点バッファをデータストリーム設定
		pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

		//インデックスバッファをデータストリームに設定
		pDevice->SetIndices(g_pIdxBuffMeshField);

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMeshfield);

		//ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 
			0,
			0,
			9,
			0,
			12);
	}
}

MESHFIELD GetMeshfield(void)
{
	return g_Field[0];
}