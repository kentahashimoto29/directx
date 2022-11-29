#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

typedef struct
{
	D3DXVECTOR3 g_posMeshfield;
	D3DXVECTOR3 g_rotMeshfield;
	D3DXMATRIX g_mtxWorldMeshfield;
}MESHFIELD;

//プロトタイプ宣言
void InitMeshfield(void);
void UninitMeshfield(void);
void UpdateMeshfield(void);
void DrawMeshfield(void);
MESHFIELD GetMeshfield(void);

#endif
