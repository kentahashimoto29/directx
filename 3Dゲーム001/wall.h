#ifndef _WALL_H_
#define _WALL_H_

typedef struct
{
	D3DXVECTOR3 posWall;
	D3DXVECTOR3 rotWall;
	D3DXVECTOR3 pos;
	D3DXMATRIX mtxWorldWall;
	D3DXVECTOR3 vecLine;
}WALL;

//�v���g�^�C�v�錾
void InitWall(void);
void UninitWall(void);
void UpdateWall(void);
void DrawWall(void);

#endif
