#include "main.h"
#include "Billboard.h"

//グローバル変数
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;          //頂点バッファへのポインタ
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;         //テクスチャへのポインタ
D3DXVECTOR3 g_posBillboard;
D3DXMATRIX g_mtxWorldBillboard;

//==============================================
//ビルボードの初期化処理
//==============================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\iwa000.png",
		&g_pTextureBillboard);

	//頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	g_posBillboard = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	VERTEX_3D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos3D = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
	pVtx[1].pos3D = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	pVtx[2].pos3D = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
	pVtx[3].pos3D = D3DXVECTOR3(10.0f, -10.0f, 0.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//==============================================
//ビルボードの終了処理
//==============================================
void UninitBillboard(void)
{
	//テクスチャの破棄
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//==============================================
//ビルボードの更新処理
//==============================================
void UpdateBillboard(void)
{

}

//==============================================
//ビルボードの描画処理
//==============================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	D3DXMATRIX mtxTrans;    //計算用マトリックス
	D3DXMATRIX mtxView;     //ビューマトリックス取得

    //ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	//ビューマトリックスを取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラに対して正面に向ける
	D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);           //逆行列を求める
	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posBillboard.x, g_posBillboard.y, g_posBillboard.z);
	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

	//Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

	//頂点バッファをデータストリーム設定
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBillboard);

	//ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,                  //プリミティブの種類
		0,                                    //最初の頂点インデックス
		2);                                   //プリミティブ数

    //Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}