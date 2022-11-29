#ifndef _BULLET_H_
#define _BULLET_H_

//弾の構造体の定義
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 vecToPos;				//
	D3DXVECTOR3 move;					//移動量
	D3DXVECTOR3 rot;					//向き
	D3DXMATRIX g_mtxWorldBullet;		//ワールドマトリックス
	int nLife;							//寿命
	bool bUse;							//使用しているかどうか
}Bullet;

//プロトタイプ宣言
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
Bullet GetBullet(void);

#endif