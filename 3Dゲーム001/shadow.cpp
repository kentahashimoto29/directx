#include "main.h"
#include "shadow.h"
#include "model.h"
#include "field.h"
#include "Bullet.h"

//�}�N����`
#define MAX_SHADOW					(256)					//�e�̍ő吔
#define HEIGHT_SHADOWPLAYER			(14.0f)					//�v���C���[�̉e�̏c��
#define WIDTH_SHADOWPLAYER			(7.0f)					//�v���C���[�̉e�̉���
#define HEIGHT_SHADOWBULLET			(3.0f)					//�e�̉e�̏c��
#define WIDTH_SHADOWBULLET			(3.0f)					//�e�̉e�̉���

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL;			//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureShadow = NULL;					//�e�N�X�`���ւ̃|�C���^
SHADOW g_Shadow[MAX_SHADOW];

//==============================================
//�e�̏���������
//==============================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\shadow000.jpg",
		&g_pTextureShadow);

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		g_Shadow[nCntShadow].g_posShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].g_rotShadow = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Shadow[nCntShadow].bUseShadow = false;
		g_Shadow[nCntShadow].Shadowtype = TYPESHADOW_NOME;
	}

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos3D = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffShadow->Unlock();
}

//==============================================
//�e�̏I������
//==============================================
void UninitShadow(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}

}

//==============================================
//�e�̍X�V����
//==============================================
void UpdateShadow(void)
{
	MODEL pModel = GetModel();
	FIELD pField = GetField();
	Bullet pBullet = GetBullet();

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUseShadow == true)
		{//�e���g�p����Ă���
			if (g_Shadow[nCntShadow].Shadowtype == TYPESHADOW_PLAYER)
			{
				g_Shadow[nCntShadow].g_posShadow = pModel.g_posModel;
				g_Shadow[nCntShadow].g_posShadow.y = pField.g_posField.y;
				g_Shadow[nCntShadow].g_rotShadow = pModel.g_rotModel;
			}

			else if (g_Shadow[nCntShadow].Shadowtype == TYPESHADOW_BULLET)
			{
				g_Shadow[nCntShadow].g_posShadow = pBullet.pos;
				g_Shadow[nCntShadow].g_posShadow.y = pField.g_posField.y;
			}
		}
 	}
}

//==============================================
//�e�̕`�揈��
//==============================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;    //�v�Z�p�}�g���b�N�X

	//���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUseShadow == true)
		{//�e���g�p����Ă���

			if (g_Shadow[nCntShadow].Shadowtype == TYPESHADOW_PLAYER)
			{	//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Shadow[nCntShadow].g_mtxWorldShadow);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].g_rotShadow.y, g_Shadow[nCntShadow].g_rotShadow.x, g_Shadow[nCntShadow].g_rotShadow.z);

				D3DXMatrixMultiply(&g_Shadow[nCntShadow].g_mtxWorldShadow, &g_Shadow[nCntShadow].g_mtxWorldShadow, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].g_posShadow.x, g_Shadow[nCntShadow].g_posShadow.y, g_Shadow[nCntShadow].g_posShadow.z);

				D3DXMatrixMultiply(&g_Shadow[nCntShadow].g_mtxWorldShadow, &g_Shadow[nCntShadow].g_mtxWorldShadow, &mtxTrans);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].g_mtxWorldShadow);

				//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
				pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

				//���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureShadow);

				//�|���S���̕`��
				pDevice->DrawPrimitive(
					D3DPT_TRIANGLESTRIP,					//�v���~�e�B�u�̎��
					nCntShadow * 4,							//�ŏ��̒��_�C���f�b�N�X
					2);										//�v���~�e�B�u��
			}

			else if (g_Shadow[nCntShadow].Shadowtype == TYPESHADOW_BULLET)
			{	//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_Shadow[nCntShadow].g_mtxWorldShadow);

				//�����𔽉f
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].g_rotShadow.y, g_Shadow[nCntShadow].g_rotShadow.x, g_Shadow[nCntShadow].g_rotShadow.z);

				D3DXMatrixMultiply(&g_Shadow[nCntShadow].g_mtxWorldShadow, &g_Shadow[nCntShadow].g_mtxWorldShadow, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].g_posShadow.x, g_Shadow[nCntShadow].g_posShadow.y, g_Shadow[nCntShadow].g_posShadow.z);

				D3DXMatrixMultiply(&g_Shadow[nCntShadow].g_mtxWorldShadow, &g_Shadow[nCntShadow].g_mtxWorldShadow, &mtxTrans);

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].g_mtxWorldShadow);

				//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
				pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

				//���_�t�H�[�}�b�g�̐ݒ�
				pDevice->SetFVF(FVF_VERTEX_3D);

				//�e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureShadow);

				//�|���S���̕`��
				pDevice->DrawPrimitive(
					D3DPT_TRIANGLESTRIP,					//�v���~�e�B�u�̎��
					nCntShadow * 4,							//�ŏ��̒��_�C���f�b�N�X
					2);										//�v���~�e�B�u��
			}
		}
	}

   //�ʏ�̍����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

void SetShadow(TYPESHADOW type, bool bUseShadow)
{
	int nCntShadow;

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUseShadow == false)
		{//�e���g�p����Ă��Ȃ�

			if (type == TYPESHADOW_PLAYER)
			{
				VERTEX_3D *pVtx;         //���_���ւ̃|�C���^

										 //���_�o�b�t�@�����b�N����
				g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

				pVtx += (nCntShadow * 4);                      //�Y���̈ʒu�܂Ői�߂�

															   //���_���W�̐ݒ�
				pVtx[0].pos3D = D3DXVECTOR3(-WIDTH_SHADOWPLAYER, 0.0f, HEIGHT_SHADOWPLAYER);
				pVtx[1].pos3D = D3DXVECTOR3(WIDTH_SHADOWPLAYER, 0.0f, HEIGHT_SHADOWPLAYER);
				pVtx[2].pos3D = D3DXVECTOR3(-WIDTH_SHADOWPLAYER, 0.0f, -HEIGHT_SHADOWPLAYER);
				pVtx[3].pos3D = D3DXVECTOR3(WIDTH_SHADOWPLAYER, 0.0f, -HEIGHT_SHADOWPLAYER);

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
				g_pVtxBuffShadow->Unlock();

				g_Shadow[nCntShadow].Shadowtype = TYPESHADOW_PLAYER;
				g_Shadow[nCntShadow].bUseShadow = bUseShadow;               //�g�p���Ă����Ԃɂ���
				break;
			}

			else if (type == TYPESHADOW_BULLET)
			{
				VERTEX_3D *pVtx;         //���_���ւ̃|�C���^

										 //���_�o�b�t�@�����b�N����
				g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

				pVtx += (nCntShadow * 4);                      //�Y���̈ʒu�܂Ői�߂�

															   //���_���W�̐ݒ�
				pVtx[0].pos3D = D3DXVECTOR3(-WIDTH_SHADOWBULLET, 0.0f, HEIGHT_SHADOWBULLET);
				pVtx[1].pos3D = D3DXVECTOR3(WIDTH_SHADOWBULLET, 0.0f, HEIGHT_SHADOWBULLET);
				pVtx[2].pos3D = D3DXVECTOR3(-WIDTH_SHADOWBULLET, 0.0f, -HEIGHT_SHADOWBULLET);
				pVtx[3].pos3D = D3DXVECTOR3(WIDTH_SHADOWBULLET, 0.0f, -HEIGHT_SHADOWBULLET);

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
				g_pVtxBuffShadow->Unlock();

				g_Shadow[nCntShadow].Shadowtype = TYPESHADOW_BULLET;
				g_Shadow[nCntShadow].bUseShadow = bUseShadow;               //�g�p���Ă����Ԃɂ���
				break;
			}
		}
	}
}

SHADOW GetShadow(void)
{
	return g_Shadow[0];
}