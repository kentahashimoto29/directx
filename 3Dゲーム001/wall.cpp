#include "main.h"
#include "wall.h"
#include "Bullet.h"
#include "model.h"

#define NUM_WALL                                 (4)               //�ǂ̑���

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWall = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureWall = NULL;				//�e�N�X�`���ւ̃|�C���^
WALL g_Wall[NUM_WALL];

//==============================================
//�ǂ̏���������
//==============================================
void InitWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\wall.jpg",
		&g_pTextureWall);

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUM_WALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWall,
		NULL);

	g_Wall[0].posWall = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	g_Wall[1].posWall = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	g_Wall[2].posWall = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	g_Wall[3].posWall = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	g_Wall[0].rotWall = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Wall[1].rotWall = D3DXVECTOR3(0.0f, D3DX_PI / 2, 0.0f);
	g_Wall[2].rotWall = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	g_Wall[3].rotWall = D3DXVECTOR3(0.0f, D3DX_PI * 3 / 2, 0.0f);

	g_Wall[0].pos = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	g_Wall[1].pos = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	g_Wall[2].pos = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	g_Wall[3].pos = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		if (nCntWall >= 3)
		{
			g_Wall[nCntWall].vecLine = D3DXVECTOR3(g_Wall[0].pos.x - g_Wall[nCntWall].pos.x, 0.0f, g_Wall[0].pos.z - g_Wall[nCntWall].pos.z);
		}

		else
		{
			g_Wall[nCntWall].vecLine = D3DXVECTOR3(g_Wall[nCntWall + 1].pos.x - g_Wall[nCntWall].pos.x, 0.0f, g_Wall[nCntWall + 1].pos.z - g_Wall[nCntWall].pos.z);
		}
	}

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffWall->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos3D = D3DXVECTOR3(-150.0f, 300.0f, 150.0f);
		pVtx[1].pos3D = D3DXVECTOR3(150.0f, 300.0f, 150.0f);
		pVtx[2].pos3D = D3DXVECTOR3(-150.0f, 0.0f, 150.0f);
		pVtx[3].pos3D = D3DXVECTOR3(150.0f, 0.0f, 150.0f);

		//�@���x�N�g��
		pVtx[0].nor3D = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor3D = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor3D = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor3D = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex3D = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex3D = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex3D = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex3D = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffWall->Unlock();
}

//==============================================
//�ǂ̏I������
//==============================================
void UninitWall(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureWall != NULL)
	{
		g_pTextureWall->Release();
		g_pTextureWall = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffWall != NULL)
	{
		g_pVtxBuffWall->Release();
		g_pVtxBuffWall = NULL;
	}

}

//==============================================
//�ǂ̍X�V����
//==============================================
void UpdateWall(void)
{
	Bullet pBullet = GetBullet();
	MODEL pModel = GetModel();

	if (pModel.g_posModel.z - pModel.g_VtxMinModel.z >= g_Wall[0].posWall.z)
	{
		pModel.g_posModel.z = g_Wall[0].posWall.z + pModel.g_VtxMinModel.z;
	}

	//for (int nCntWall = 0; nCntWall < 2; nCntWall++)
	//{
	//pBullet.vecToPos = D3DXVECTOR3(pBullet.pos.x - g_Wall[nCntWall].pos.x, 0.0f, pBullet.pos.z - g_Wall[nCntWall].pos.z);

	//	if (g_Wall[nCntWall].vecLine.z * pBullet.vecToPos.x - g_Wall[nCntWall].vecLine.x * pBullet.vecToPos.z <= 0.0f)
	//	{
	//		pBullet.bUse = false;						//�g�p���Ă��Ȃ���Ԃɂ���
	//	}
	//}

}

//==============================================
//�ǂ̕`�揈��
//==============================================
void DrawWall(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;    //�v�Z�p�}�g���b�N�X


	for (int nCntWall = 0; nCntWall < NUM_WALL; nCntWall++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Wall[nCntWall].mtxWorldWall);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Wall[nCntWall].rotWall.y, g_Wall[nCntWall].rotWall.x, g_Wall[nCntWall].rotWall.z);

		D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorldWall, &g_Wall[nCntWall].mtxWorldWall, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Wall[nCntWall].posWall.x, g_Wall[nCntWall].posWall.y, g_Wall[nCntWall].posWall.z);

		D3DXMatrixMultiply(&g_Wall[nCntWall].mtxWorldWall, &g_Wall[nCntWall].mtxWorldWall, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Wall[nCntWall].mtxWorldWall);

		//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffWall, 0, sizeof(VERTEX_3D));

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureWall);

		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,					//�v���~�e�B�u�̎��
			nCntWall * 4,							//�ŏ��̒��_�C���f�b�N�X
			2);										//�v���~�e�B�u��
	}
}