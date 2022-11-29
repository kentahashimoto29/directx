#ifndef _SHADOW_H_
#define _SHADOW_H_

typedef enum
{
	TYPESHADOW_NOME = 0,
	TYPESHADOW_PLAYER,				//プレイヤーの影
	TYPESHADOW_BULLET				//弾の影
}TYPESHADOW;

typedef struct
{
	D3DXVECTOR3 g_posShadow;
	D3DXVECTOR3 g_rotShadow;
	D3DXMATRIX g_mtxWorldShadow;
	TYPESHADOW Shadowtype;
	bool bUseShadow;
}SHADOW;

//プロトタイプ宣言
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);
void SetShadow(TYPESHADOW type, bool bUseShadow);
SHADOW GetShadow(void);

#endif
