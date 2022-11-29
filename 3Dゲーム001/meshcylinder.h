#ifndef _MESHCYLINDER_H_
#define _MESHCYLINDER_H_

typedef struct
{
	D3DXVECTOR3 g_pos;
	D3DXVECTOR3 g_rot;
	D3DXMATRIX g_mtxWorld;
}MESHFIELD;

//プロトタイプ宣言
void InitMeshCylinder(void);
void UninitMeshCylinder(void);
void UpdateMeshCylinder(void);
void DrawMeshCylinder(void);
//MESHFIELD GetMeshfield(void);

#endif
