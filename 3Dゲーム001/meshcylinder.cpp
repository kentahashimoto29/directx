#include "main.h"
#include "meshcylinder.h"

//�}�N����`
#define NUM_MESHCYLINDER					(8)

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshCylinder = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshCylinder = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshCylinder = NULL;				//�C���f�N�X�o�b�t�@�ւ̃|�C���^
MESHFIELD g_MeshCylinder[NUM_MESHCYLINDER];
float MeshCylinderDistance;

//==============================================
//�t�B�[���h�̏���������
//==============================================
void InitMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\tsuti000.jpg",
		&g_pTextureMeshCylinder);

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 18,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshCylinder,
		NULL);

	MeshCylinderDistance = 500.0f;

	g_MeshCylinder[0].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[0].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[1].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[1].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[2].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[2].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[3].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[3].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[4].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[4].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[5].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[5].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[6].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[6].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[7].g_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_MeshCylinder[7].g_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshCylinder->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos3D = D3DXVECTOR3(cosf(D3DX_PI) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[1].pos3D = D3DXVECTOR3(cosf(D3DX_PI / 4 * 3) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[2].pos3D = D3DXVECTOR3(cosf(D3DX_PI / 2) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[3].pos3D = D3DXVECTOR3(cosf(D3DX_PI / 4) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[4].pos3D = D3DXVECTOR3(cosf(D3DX_PI * 0) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[5].pos3D = D3DXVECTOR3(cosf(-D3DX_PI / 4 * 3) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[6].pos3D = D3DXVECTOR3(cosf(-D3DX_PI / 2) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[7].pos3D = D3DXVECTOR3(cosf(-D3DX_PI / 4) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[8].pos3D = D3DXVECTOR3(cosf(-D3DX_PI * 0) * MeshCylinderDistance, 500.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[9].pos3D = D3DXVECTOR3(cosf(D3DX_PI) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[10].pos3D = D3DXVECTOR3(cosf(D3DX_PI / 4 * 3) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[11].pos3D = D3DXVECTOR3(cosf(D3DX_PI / 2) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[12].pos3D = D3DXVECTOR3(cosf(D3DX_PI / 4) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[13].pos3D = D3DXVECTOR3(cosf(D3DX_PI * 0) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[14].pos3D = D3DXVECTOR3(cosf(-D3DX_PI / 4 * 3) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[15].pos3D = D3DXVECTOR3(cosf(-D3DX_PI / 2) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[16].pos3D = D3DXVECTOR3(cosf(-D3DX_PI / 4) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);
	pVtx[17].pos3D = D3DXVECTOR3(cosf(-D3DX_PI * 0) * MeshCylinderDistance, 0.0f, sinf(D3DX_PI) * MeshCylinderDistance);

	for (int nCntField = 0; nCntField < 18; nCntField++)
	{
		pVtx[nCntField].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCntField].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[nCntField].tex3D = D3DXVECTOR2(0.0f, 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshCylinder->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 18,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshCylinder,
		NULL);

	WORD *pIdx;					//�C���f�b�N�X���ւ̃|�C���^

								//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��ւ̃|�C���^���擾
	g_pIdxBuffMeshCylinder->Lock(0, 0, (void**)&pIdx, 0);

	//���_�ԍ��f�[�^�̐ݒ�
	pIdx[0] = 3;
	pIdx[1] = 0;
	pIdx[2] = 4;
	pIdx[3] = 1;
	pIdx[4] = 5;
	pIdx[5] = 2;
	pIdx[6] = 2;
	pIdx[7] = 6;
	pIdx[8] = 6;
	pIdx[9] = 3;
	pIdx[10] = 7;
	pIdx[11] = 4;
	pIdx[12] = 8;
	pIdx[13] = 5;

	//�C���f�b�N�X�o�b�t�@���A�����b�N
	g_pIdxBuffMeshCylinder->Unlock();
}

//==============================================
//�t�B�[���h�̏I������
//==============================================
void UninitMeshCylinder(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshCylinder != NULL)
	{
		g_pTextureMeshCylinder->Release();
		g_pTextureMeshCylinder = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshCylinder != NULL)
	{
		g_pVtxBuffMeshCylinder->Release();
		g_pVtxBuffMeshCylinder = NULL;
	}

}

//==============================================
//�t�B�[���h�̍X�V����
//==============================================
void UpdateMeshCylinder(void)
{

}

//==============================================
//�t�B�[���h�̕`�揈��
//==============================================
void DrawMeshCylinder(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;    //�v�Z�p�}�g���b�N�X

	for (int nCntField = 0; nCntField < NUM_MESHCYLINDER; nCntField++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_MeshCylinder[nCntField].g_mtxWorld);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshCylinder[nCntField].g_rot.y, g_MeshCylinder[nCntField].g_rot.x, g_MeshCylinder[nCntField].g_rot.z);

		D3DXMatrixMultiply(&g_MeshCylinder[nCntField].g_mtxWorld, &g_MeshCylinder[nCntField].g_mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_MeshCylinder[nCntField].g_pos.x, g_MeshCylinder[nCntField].g_pos.y, g_MeshCylinder[nCntField].g_pos.z);

		D3DXMatrixMultiply(&g_MeshCylinder[nCntField].g_mtxWorld, &g_MeshCylinder[nCntField].g_mtxWorld, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_MeshCylinder[nCntField].g_mtxWorld);

		//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMeshCylinder, 0, sizeof(VERTEX_3D));

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffMeshCylinder);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshCylinder);

		//�|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,
			0,
			0,
			9,
			0,
			12);
	}
}

//MESHFIELD GetMeshfield(void)
//{
//	return g_Field[0];
//}