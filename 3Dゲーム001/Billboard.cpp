#include "main.h"
#include "Billboard.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBillboard = NULL;          //���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureBillboard = NULL;         //�e�N�X�`���ւ̃|�C���^
D3DXVECTOR3 g_posBillboard;
D3DXMATRIX g_mtxWorldBillboard;

//==============================================
//�r���{�[�h�̏���������
//==============================================
void InitBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\iwa000.png",
		&g_pTextureBillboard);

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBillboard,
		NULL);

	g_posBillboard = D3DXVECTOR3(0.0f, 10.0f, 0.0f);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffBillboard->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos3D = D3DXVECTOR3(-10.0f, 10.0f, 0.0f);
	pVtx[1].pos3D = D3DXVECTOR3(10.0f, 10.0f, 0.0f);
	pVtx[2].pos3D = D3DXVECTOR3(-10.0f, -10.0f, 0.0f);
	pVtx[3].pos3D = D3DXVECTOR3(10.0f, -10.0f, 0.0f);

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
	g_pVtxBuffBillboard->Unlock();
}

//==============================================
//�r���{�[�h�̏I������
//==============================================
void UninitBillboard(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBillboard != NULL)
	{
		g_pTextureBillboard->Release();
		g_pTextureBillboard = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBillboard != NULL)
	{
		g_pVtxBuffBillboard->Release();
		g_pVtxBuffBillboard = NULL;
	}
}

//==============================================
//�r���{�[�h�̍X�V����
//==============================================
void UpdateBillboard(void)
{

}

//==============================================
//�r���{�[�h�̕`�揈��
//==============================================
void DrawBillboard(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxTrans;    //�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxView;     //�r���[�}�g���b�N�X�擾

    //���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_mtxWorldBillboard);

	//�r���[�}�g���b�N�X���擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����ɑ΂��Đ��ʂɌ�����
	D3DXMatrixInverse(&g_mtxWorldBillboard, NULL, &mtxView);           //�t�s������߂�
	g_mtxWorldBillboard._41 = 0.0f;
	g_mtxWorldBillboard._42 = 0.0f;
	g_mtxWorldBillboard._43 = 0.0f;

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_posBillboard.x, g_posBillboard.y, g_posBillboard.z);
	D3DXMatrixMultiply(&g_mtxWorldBillboard, &g_mtxWorldBillboard, &mtxTrans);

	//Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBillboard);

	//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBillboard, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBillboard);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,                  //�v���~�e�B�u�̎��
		0,                                    //�ŏ��̒��_�C���f�b�N�X
		2);                                   //�v���~�e�B�u��

    //Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}