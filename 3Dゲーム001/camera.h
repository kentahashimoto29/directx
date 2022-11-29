#ifndef _CAMERA_H_
#define _CAMERA_H_

//カメラの構造体
typedef struct
{
	D3DXVECTOR3 posV;                  //視点
	D3DXVECTOR3 posR;                  //注視点
	D3DXVECTOR3 vecU;                  //上方向のベクトル
	D3DXVECTOR3 rot;                   //向き
	D3DXMATRIX mtxProjection;          //プロジェクションマトリックス
	D3DXMATRIX mtxView;                //ビューマトリックス
}Camera;

//プロトタイプ宣言
void InitCamera(void);
void UninitCamera(void);
void UpdateCamera(void);
void Setcamera(void);
Camera GetCamera(void);

#endif