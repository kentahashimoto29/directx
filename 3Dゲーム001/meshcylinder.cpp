#include "main.h"
#include "meshcylinder.h"

//マクロ定義
#define NUM_MESHCYLINDER					(8)

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;					//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;				//インデクスバッファへのポインタ
MESHFIELD g_MeshCylinder[NUM_MESHCYLINDER];
float MeshCylinderDistance;

//==============================================
//フィールドの初期化処理
//==============================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\tsuti000.jpg",
		&g_pTextureMeshCylinder);

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 18,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	MeshCylinderDistance = 500.0f;

	g_MeshCylinder[0].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[0].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[1].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[1].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[2].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[2].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[3].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[3].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[4].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[4].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[5].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[5].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[6].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[6].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[7].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[7].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos3D = D3DXVECTOR3(cosf(D3DX_PI) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[1].pos3D = D3DXVECTOR3(cosf(D3DX_PI / 4 * 3) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[2].pos3D = D3DXVECTOR3(cosf(D3DX_PI / 2) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[3].pos3D = D3DXVECTOR3(cosf(D3DX_PI / 4) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[4].pos3D = D3DXVECTOR3(cosf(D3DX_PI * 0) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[5].pos3D = D3DXVECTOR3(cosf(-D3DX_PI / 4 * 3) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[6].pos3D = D3DXVECTOR3(cosf(-D3DX_PI / 2) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[7].pos3D = D3DXVECTOR3(cosf(-D3DX_PI / 4) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[8].pos3D = D3DXVECTOR3(cosf(-D3DX_PI * 0) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[9].pos3D = D3DXVECTOR3(cosf(D3DX_PI) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[10].pos3D = D3DXVECTOR3(cosf(D3DX_PI / 4 * 3) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[11].pos3D = D3DXVECTOR3(cosf(D3DX_PI / 2) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[12].pos3D = D3DXVECTOR3(cosf(D3DX_PI / 4) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[13].pos3D = D3DXVECTOR3(cosf(D3DX_PI * 0) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[14].pos3D = D3DXVECTOR3(cosf(-D3DX_PI / 4 * 3) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[15].pos3D = D3DXVECTOR3(cosf(-D3DX_PI / 2) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[16].pos3D = D3DXVECTOR3(cosf(-D3DX_PI / 4) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[17].pos3D = D3DXVECTOR3(cosf(-D3DX_PI * 0) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);

	for (int nCntField = 0; nCntField < 18; nCntField++)
	{
		pVtx[nCntField].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの設定
		pVtx[nCntField].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);

		//テクスチャ座標の設定
		pVtx[nCntField].tex3D = D3DXVECTOR2(0.0f, 0.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMeshCylinder->Unlock();

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 18,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);

	WORD *pIdx;					//インデックス情報へのポインタ

								//インデックスバッファをロックし、頂点番号へのポインタを取得
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffMeshCylinder->Unlock();
}

//==============================================
//フィールドの終了処理
//==============================================
void UninitMeshCylinder(void)
{
	//テクスチャの破棄
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

}

//==============================================
//フィールドの更新処理
//==============================================
void UpdateMeshCylinder(void)
{

}

//==============================================
//フィールドの描画処理
//==============================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;    //計算用マトリックス

	for (int nCntField = 0; nCntField < NUM_MESHCYLINDER; nCntField++)
	{
		//ワールドマトリックスの初期化
		D3DXMatrixIdentity(&g_MeshCylinder[nCntField].g_mtxWorld);

		//向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshCylinder[nCntField].g_rot.y, g_MeshCylinder[nCntField].g_rot.x, g_MeshCylinder[nCntField].g_rot.z);

		D3DXMatrixMultiply(&g_MeshCylinder[nCntField].g_mtxWorld, &g_MeshCylinder[nCntField].g_mtxWorld, &mtxRot);

		//位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_MeshCylinder[nCntField].g_pos.x, g_MeshCylinder[nCntField].g_pos.y, g_MeshCylinder[nCntField].g_pos.z);

		D3DXMatrixMultiply(&g_MeshCylinder[nCntField].g_mtxWorld, &g_MeshCylinder[nCntField].g_mtxWorld, &mtxTrans);

		//ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshCylinder[nCntField].g_mtxWorld);

		//頂点バッファをデータストリーム設定
		pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

		//インデックスバッファをデータストリームに設定
		pDevice->SetIndices(g_pIdxBuffMeshCylinder);

		//頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureMeshCylinder);

		//ポリゴンの描画
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			9,
			0,
			12);
	}
}

//MESHFIELD GetMeshfield(void)
//{
//	return g_Field[0];
//}