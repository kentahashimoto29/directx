#ifndef _FIELD_H_
#define _FIELD_H_

typedef struct
{
	D3DXVECTOR3 g_posField;
	D3DXVECTOR3 g_rotField;
	D3DXMATRIX g_mtxWorldField;
}FIELD;

//プロトタイプ宣言
void InitField(void);
void UninitField(void);
void UpdateField(void);
void DrawField(void);
FIELD GetField(void);

#endif
