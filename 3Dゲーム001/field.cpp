#include "main.h"
#include "Field.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;				//頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;					//テクスチャへのポインタ
FIELD g_Field;

//==============================================
//フィールドの初期化処理
//==============================================
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\tsuti000.jpg",
		&g_pTextureField);

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);

	g_Field.g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Field.g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos3D = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	pVtx[1].pos3D = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	pVtx[2].pos3D = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[3].pos3D = D3DXVECTOR3(50.0f, 0.0f, -50.0f);

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
	g_pVtxBuffField->Unlock();
}

//==============================================
//フィールドの終了処理
//==============================================
void UninitField(void)
{
	//テクスチャの破棄
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}

}

//==============================================
//フィールドの更新処理
//==============================================
void UpdateField(void)
{

}

//==============================================
//フィールドの描画処理
//==============================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;    //計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Field.g_mtxWorldField);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Field.g_rotField.y, g_Field.g_rotField.x, g_Field.g_rotField.z);

	D3DXMatrixMultiply(&g_Field.g_mtxWorldField, &g_Field.g_mtxWorldField, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Field.g_posField.x, g_Field.g_posField.y, g_Field.g_posField.z);

	D3DXMatrixMultiply(&g_Field.g_mtxWorldField, &g_Field.g_mtxWorldField, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Field.g_mtxWorldField);

	//頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureField);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,                  //プリミティブの種類
		0,                                    //最初の頂点インデックス
		2);                                   //プリミティブ数
}

FIELD GetField(void)
{
	return g_Field;
}