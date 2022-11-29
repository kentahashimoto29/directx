#include "main.h"
#include "model.h"
#include "input.h"
#include "camera.h"
#include "Bullet.h"
#include "shadow.h"

//マクロ定義
#define COMPARIZON_MIN								(100.0f)
#define COMPARIZON_MAX								(-100.0f)

//グローバル変数宣言
LPD3DXMESH g_pMeshModel = NULL;						//メッシュへのポインタ
LPD3DXBUFFER g_pBuffMatModel = NULL;				//マテリアルへのポインタ
DWORD g_dwNumMatModel = 0;							//マテリアルの数
MODEL g_Model;

//==============================================
//モデルの初期化処理
//==============================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nNumVtx;				//頂点数
	DWORD dwSizeFVF;			//頂点フォーマットのサイズ
	BYTE *pVtxBuff;				//頂点バッファへのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	g_Model.g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Model.g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//Xファイルの読み込み
	D3DXLoadMeshFromX("data\\MODEL\\car000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_dwNumMatModel,
		&g_pMeshModel);

	g_Model.g_VtxMinModel = D3DXVECTOR3(COMPARIZON_MIN, COMPARIZON_MIN, COMPARIZON_MIN);
	g_Model.g_VtxMaxModel = D3DXVECTOR3(COMPARIZON_MAX, COMPARIZON_MAX, COMPARIZON_MAX);

	//頂点数を取得
	nNumVtx = g_pMeshModel->GetNumVertices();

	//頂点フォーマットのサイズを取得
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//頂点バッファをロック
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY,(void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;					//頂点座標の代入

		if (g_Model.g_VtxMinModel.x > vtx.x)
		{
			g_Model.g_VtxMinModel.x = vtx.x;
		}

		else if (g_Model.g_VtxMaxModel.x < vtx.x)
		{
			g_Model.g_VtxMaxModel.x = vtx.x;
		}

		if (g_Model.g_VtxMinModel.y > vtx.y)
		{
			g_Model.g_VtxMinModel.y = vtx.y;
		}

		else if (g_Model.g_VtxMaxModel.y < vtx.y)
		{
			g_Model.g_VtxMaxModel.y = vtx.y;
		}

		if (g_Model.g_VtxMinModel.z > vtx.z)
		{
			g_Model.g_VtxMinModel.z = vtx.z;
		}

		else if (g_Model.g_VtxMaxModel.z < vtx.z)
		{
			g_Model.g_VtxMaxModel.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;					//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	g_pMeshModel->UnlockVertexBuffer();

	SetShadow(TYPESHADOW_PLAYER, true);
}

//==============================================
//モデルの終了処理
//==============================================
void UninitModel(void)
{

}

//==============================================
//モデルの更新処理
//==============================================
void UpdateModel(void)
{
	Camera pCamera;

	pCamera = GetCamera();

	if (GetKeyboardPress(DIK_A) == true)
	{
		g_Model.g_posModel.x += sinf(D3DX_PI * -0.5f + pCamera.rot.y);
		g_Model.g_posModel.z += cosf(D3DX_PI * -0.5f + pCamera.rot.y);

		g_Model.g_DestrotModel.y = D3DX_PI * 0.5f + pCamera.rot.y;
	}

	else if (GetKeyboardPress(DIK_D) == true)
	{
		g_Model.g_posModel.x += sinf(D3DX_PI * 0.5f + pCamera.rot.y);
		g_Model.g_posModel.z += cosf(D3DX_PI * 0.5f + pCamera.rot.y);

		g_Model.g_DestrotModel.y = D3DX_PI * -0.5f + pCamera.rot.y;
	}

	else if (GetKeyboardPress(DIK_W) == true)
	{
		g_Model.g_posModel.x += sinf(D3DX_PI * 0.0f + pCamera.rot.y);
		g_Model.g_posModel.z += cosf(D3DX_PI * 0.0f + pCamera.rot.y);

		g_Model.g_DestrotModel.y = D3DX_PI * 1.0f + pCamera.rot.y;
	}

	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_Model.g_posModel.x += sinf(D3DX_PI * 1.0f + pCamera.rot.y);
		g_Model.g_posModel.z += cosf(D3DX_PI * 1.0f + pCamera.rot.y);

		g_Model.g_DestrotModel.y = D3DX_PI * 0.0f + pCamera.rot.y;
	}

	g_Model.g_DiffrotModel.y = g_Model.g_DestrotModel.y - g_Model.g_rotModel.y;

	//カメラの補正
	if (g_Model.g_DiffrotModel.y > D3DX_PI)
	{
		g_Model.g_DiffrotModel.y += -D3DX_PI * 2;
	}

	else if (g_Model.g_DiffrotModel.y < -D3DX_PI)
	{
		g_Model.g_DiffrotModel.y += D3DX_PI * 2;
	}

	g_Model.g_rotModel.y += g_Model.g_DiffrotModel.y * 0.1f;

	//モデルの補正
	if (g_Model.g_rotModel.y > D3DX_PI)
	{
		g_Model.g_rotModel.y = -D3DX_PI;
	}

	else if (g_Model.g_rotModel.y < -D3DX_PI)
	{
		g_Model.g_rotModel.y = D3DX_PI;
	}

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		SetBullet(g_Model.g_posModel, g_Model.g_rotModel, 100);
		SetShadow(TYPESHADOW_BULLET, true);
	}
}

//==============================================
//モデルの描画処理
//==============================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;                //
	D3DMATERIAL9 matDef;                        //
	D3DXMATERIAL *pMat;                         //

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_Model.g_mtxWorldModel);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.g_rotModel.y, g_Model.g_rotModel.x, g_Model.g_rotModel.z);

	D3DXMatrixMultiply(&g_Model.g_mtxWorldModel, &g_Model.g_mtxWorldModel, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_Model.g_posModel.x, g_Model.g_posModel.y, g_Model.g_posModel.z);

	D3DXMatrixMultiply(&g_Model.g_mtxWorldModel, &g_Model.g_mtxWorldModel, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_Model.g_mtxWorldModel);

	//現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//モデル(パーツ)も描画
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//保存していたマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

MODEL GetModel(void)
{
	return g_Model;
}