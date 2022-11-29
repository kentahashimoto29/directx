#ifndef _MODEL_H_
#define _MODEL_H_

typedef struct
{
	D3DXVECTOR3 g_posModel;								//�ʒu
	D3DXVECTOR3 g_rotModel;								//���݂̌���
	D3DXVECTOR3 g_DestrotModel;							//�ڕW�̌���
	D3DXVECTOR3 g_DiffrotModel;							//���݂̊p�x����ڕW�̊p�x�܂ł̍���
	D3DXVECTOR3 g_VtxMinModel, g_VtxMaxModel;			//���f���̍ő�l�E�ŏ��l
	D3DXMATRIX g_mtxWorldModel;							//���[���h�}�g���b�N�X
}MODEL;

//�v���g�^�C�v�錾
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
MODEL GetModel(void);

#endif
