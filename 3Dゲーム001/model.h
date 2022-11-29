#ifndef _MODEL_H_
#define _MODEL_H_

typedef struct
{
	D3DXVECTOR3 g_posModel;								//位置
	D3DXVECTOR3 g_rotModel;								//現在の向き
	D3DXVECTOR3 g_DestrotModel;							//目標の向き
	D3DXVECTOR3 g_DiffrotModel;							//現在の角度から目標の角度までの差分
	D3DXVECTOR3 g_VtxMinModel, g_VtxMaxModel;			//モデルの最大値・最小値
	D3DXMATRIX g_mtxWorldModel;							//ワールドマトリックス
}MODEL;

//プロトタイプ宣言
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
MODEL GetModel(void);

#endif
