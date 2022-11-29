#include "main.h"
#include "Bullet.h"
#include "shadow.h"

//�}�N����`
#define MAX_BULLET					(128)					//�e�̍ő吔
#define HEIGHT_BULLET				(3.0f)					//�e�̏c��
#define WIDTH_BULLET				(3.0f)					//�e�̉���

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;					//�e�N�X�`���ւ̃|�C���^
Bullet g_Bullet[MAX_BULLET];

//==============================================
//�e�̏���������
//==============================================
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\bullet000.png",
		&g_pTextureBullet);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_Bullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Bullet[nCntBullet].nLife = 0;
		g_Bullet[nCntBullet].bUse = false;
	}

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_BULLET,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);

	VERTEX_3D *pVtx;
	
	//���_�o�b�t�@�����b�N
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		pVtx[0].nor3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].nor3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].nor3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].nor3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex3D = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex3D = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex3D = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[3].tex3D = D3DXVECTOR2(0.0f, 0.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//==============================================
//�e�̏I������
//==============================================
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//==============================================
//�e�̍X�V����
//==============================================
void UpdateBullet(void)
{
	int nCntBullet;
	SHADOW pShadow = GetShadow();
	VERTEX_3D *pVtx;					//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N����
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă��Ȃ�

			//���_���W�̐ݒ�
			pVtx[0].pos3D = D3DXVECTOR3(- WIDTH_BULLET, + HEIGHT_BULLET, 0.0f);
			pVtx[1].pos3D = D3DXVECTOR3(+ WIDTH_BULLET, + HEIGHT_BULLET, 0.0f);
			pVtx[2].pos3D = D3DXVECTOR3(- WIDTH_BULLET, - HEIGHT_BULLET, 0.0f);
			pVtx[3].pos3D = D3DXVECTOR3(+ WIDTH_BULLET, - HEIGHT_BULLET, 0.0f);

			g_Bullet[nCntBullet].pos.x += g_Bullet[nCntBullet].move.x;
			g_Bullet[nCntBullet].pos.z += g_Bullet[nCntBullet].move.z;

			g_Bullet[nCntBullet].nLife--;

			if (g_Bullet[nCntBullet].nLife <= 0)
			{
				if (pShadow.Shadowtype == TYPESHADOW_BULLET)
				{
					pShadow.bUseShadow = false;
				}

				g_Bullet[nCntBullet].bUse = false;						//�g�p���Ă��Ȃ���Ԃɂ���
			}
		}
		pVtx += 4;                      //�Y���̈ʒu�܂Ői�߂�
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//==============================================
//�e�̕`�揈��
//==============================================
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxTrans;		//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;			//�r���[�}�g���b�N�X�擾

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_Bullet[nCntBullet].g_mtxWorldBullet);

			//�r���[�}�g���b�N�X���擾
			pDevice->GetTransform(D3DTS_VIEW, &mtxView);

			//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
			D3DXMatrixInverse(&g_Bullet[nCntBullet].g_mtxWorldBullet, NULL, &mtxView);			//�t�s������߂�
			g_Bullet[nCntBullet].g_mtxWorldBullet._41 = 0.0f;
			g_Bullet[nCntBullet].g_mtxWorldBullet._42 = 0.0f;
			g_Bullet[nCntBullet].g_mtxWorldBullet._43 = 0.0f;

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_Bullet[nCntBullet].pos.x, g_Bullet[nCntBullet].pos.y, g_Bullet[nCntBullet].pos.z);
			D3DXMatrixMultiply(&g_Bullet[nCntBullet].g_mtxWorldBullet, &g_Bullet[nCntBullet].g_mtxWorldBullet, &mtxTrans);

			//Z�e�X�g�𖳌��ɂ���
			pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
			pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

			//���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_Bullet[nCntBullet].g_mtxWorldBullet);

			//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_3D));

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_pTextureBullet);

			//�|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
				nCntBullet * 4,						//�ŏ��̒��_�C���f�b�N�X
				2);									//�v���~�e�B�u��
		}
	}

	//Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//==============================================
//�e�̐ݒ�
//==============================================
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_Bullet[nCntBullet].bUse == false)
		{//�e���g�p����Ă��Ȃ�

			g_Bullet[nCntBullet].pos = D3DXVECTOR3(pos.x, pos.y + 3.0f, pos.z);
			g_Bullet[nCntBullet].rot = rot;
			g_Bullet[nCntBullet].move = D3DXVECTOR3(sinf(g_Bullet[nCntBullet].rot.y + D3DX_PI) * 1.5f, 0.0f, cosf(g_Bullet[nCntBullet].rot.y + D3DX_PI) * 1.5f);

			VERTEX_3D *pVtx;         //���_���ւ̃|�C���^

			//���_�o�b�t�@�����b�N����
			g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += (nCntBullet * 4);                      //�Y���̈ʒu�܂Ői�߂�

			//���_���W�̐ݒ�
  			pVtx[0].pos3D = D3DXVECTOR3(-WIDTH_BULLET, +HEIGHT_BULLET, 0.0f);
		 	pVtx[1].pos3D = D3DXVECTOR3(+WIDTH_BULLET, +HEIGHT_BULLET, 0.0f);
			pVtx[2].pos3D = D3DXVECTOR3(-WIDTH_BULLET, -HEIGHT_BULLET, 0.0f);
			pVtx[3].pos3D = D3DXVECTOR3(+WIDTH_BULLET, -HEIGHT_BULLET, 0.0f);

 			pVtx[0].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

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

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffBullet->Unlock();

			g_Bullet[nCntBullet].nLife = 100;
			g_Bullet[nCntBullet].bUse = true;               //�g�p���Ă����Ԃɂ���
			break;
		}
	}
}

Bullet GetBullet(void)
{
	return g_Bullet[0];
}