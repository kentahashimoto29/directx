#ifndef _BULLET_H_
#define _BULLET_H_

//�e�̍\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;					//�ʒu
	D3DXVECTOR3 vecToPos;				//
	D3DXVECTOR3 move;					//�ړ���
	D3DXVECTOR3 rot;					//����
	D3DXMATRIX g_mtxWorldBullet;		//���[���h�}�g���b�N�X
	int nLife;							//����
	bool bUse;							//�g�p���Ă��邩�ǂ���
}Bullet;

//�v���g�^�C�v�錾
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);
Bullet GetBullet(void);

#endif