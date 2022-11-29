#include "main.h"
#include "Field.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffField = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureField = NULL;					//�e�N�X�`���ւ̃|�C���^
FIELD g_Field;

//==============================================
//�t�B�[���h�̏���������
//==============================================
void InitField(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\tsuti000.jpg",
		&g_pTextureField);

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffField,
		NULL);

	g_Field.g_posField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Field.g_rotField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffField->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos3D = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	pVtx[1].pos3D = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	pVtx[2].pos3D = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[3].pos3D = D3DXVECTOR3(50.0f, 0.0f, -50.0f);

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
	g_pVtxBuffField->Unlock();
}

//==============================================
//�t�B�[���h�̏I������
//==============================================
void UninitField(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureField != NULL)
	{
		g_pTextureField->Release();
		g_pTextureField = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffField != NULL)
	{
		g_pVtxBuffField->Release();
		g_pVtxBuffField = NULL;
	}

}

//==============================================
//�t�B�[���h�̍X�V����
//==============================================
void UpdateField(void)
{

}

//==============================================
//�t�B�[���h�̕`�揈��
//==============================================
void DrawField(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;    //�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Field.g_mtxWorldField);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Field.g_rotField.y, g_Field.g_rotField.x, g_Field.g_rotField.z);

	D3DXMatrixMultiply(&g_Field.g_mtxWorldField, &g_Field.g_mtxWorldField, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Field.g_posField.x, g_Field.g_posField.y, g_Field.g_posField.z);

	D3DXMatrixMultiply(&g_Field.g_mtxWorldField, &g_Field.g_mtxWorldField, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Field.g_mtxWorldField);

	//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffField, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureField);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,                  //�v���~�e�B�u�̎��
		0,                                    //�ŏ��̒��_�C���f�b�N�X
		2);                                   //�v���~�e�B�u��
}

FIELD GetField(void)
{
	return g_Field;
}