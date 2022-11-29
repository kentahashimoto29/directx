#include "main.h"
#include "meshfield.h"

//�}�N����`
#define NUM_MESHFIELD					(4)

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshfield = NULL;				//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureMeshfield = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;				//�C���f�N�X�o�b�t�@�ւ̃|�C���^
MESHFIELD g_Field[NUM_MESHFIELD];
float nCntTexX = 1.0f, nCntTexY = 0.0f;

//==============================================
//�t�B�[���h�̏���������
//==============================================
void InitMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(
		pDevice,
		"data\\TEXTURE\\tsuti000.jpg",
		&g_pTextureMeshfield);

	//���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 14,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshfield,
		NULL);

	g_Field[0].g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Field[0].g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Field[1].g_posMeshfield = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	g_Field[1].g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Field[2].g_posMeshfield = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	g_Field[2].g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Field[3].g_posMeshfield = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	g_Field[3].g_rotMeshfield = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	VERTEX_3D *pVtx;

	//���_�o�b�t�@�����b�N
	g_pVtxBuffMeshfield->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos3D = D3DXVECTOR3(-50.0f, 0.0f, 50.0f);
	pVtx[1].pos3D = D3DXVECTOR3(50.0f, 0.0f, 50.0f);
	pVtx[2].pos3D = D3DXVECTOR3(150.0f, 0.0f, 50.0f);
	pVtx[3].pos3D = D3DXVECTOR3(-50.0f, 0.0f, -50.0f);
	pVtx[4].pos3D = D3DXVECTOR3(50.0f, 0.0f, -50.0f);
	pVtx[5].pos3D = D3DXVECTOR3(150.0f, 0.0f, -50.0f);
	pVtx[6].pos3D = D3DXVECTOR3(-50.0f, 0.0f, -150.0f);
	pVtx[7].pos3D = D3DXVECTOR3(50.0f, 0.0f, -150.0f);
	pVtx[8].pos3D = D3DXVECTOR3(150.0f, 0.0f, -150.0f);

	for (int nCntField = 0; nCntField < 9; nCntField++)
	{
		pVtx[nCntField].nor3D = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[nCntField].col3D = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	pVtx[0].tex3D = D3DXVECTOR2(nCntTexX, nCntTexY);

	//�e�N�X�`�����W�̐ݒ�
	for (int nCntMeshField1 = 0; nCntMeshField1 < 3; nCntMeshField1++)
	{
		for (int nCntMeshField2 = 1; nCntMeshField2 < 4; nCntMeshField2++)
		{
			if (nCntMeshField2 == 1)
			{
				nCntTexY += 1.0f;
			}

			else if (nCntMeshField2 == 2)
			{
				if (nCntTexX == 1.0f)
				{
					nCntTexX = 0.0f;
				}

				else if (nCntTexX == 0.0f)
				{
					nCntTexX = 1.0f;
				}

				if (nCntTexY == 1.0f)
				{
					nCntTexY = 0.0f;
				}

				else if (nCntTexY == 0.0f)
				{
					nCntTexY = 1.0f;
				}
			}

			pVtx[nCntMeshField2 + 3 * nCntMeshField1].tex3D = D3DXVECTOR2(nCntTexX, nCntTexY);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMeshfield->Unlock();

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * 14,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL);

	WORD *pIdx;					//�C���f�b�N�X���ւ̃|�C���^

	//�C���f�b�N�X�o�b�t�@�����b�N���A���_�ԍ��ւ̃|�C���^���擾
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

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
	g_pIdxBuffMeshField->Unlock();
}

//==============================================
//�t�B�[���h�̏I������
//==============================================
void UninitMeshfield(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureMeshfield != NULL)
	{
		g_pTextureMeshfield->Release();
		g_pTextureMeshfield = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffMeshfield != NULL)
	{
		g_pVtxBuffMeshfield->Release();
		g_pVtxBuffMeshfield = NULL;
	}

}

//==============================================
//�t�B�[���h�̍X�V����
//==============================================
void UpdateMeshfield(void)
{

}

//==============================================
//�t�B�[���h�̕`�揈��
//==============================================
void DrawMeshfield(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;    //�v�Z�p�}�g���b�N�X

	for (int nCntField = 0; nCntField < NUM_MESHFIELD; nCntField++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_Field[nCntField].g_mtxWorldMeshfield);

		//�����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Field[nCntField].g_rotMeshfield.y, g_Field[nCntField].g_rotMeshfield.x, g_Field[nCntField].g_rotMeshfield.z);

		D3DXMatrixMultiply(&g_Field[nCntField].g_mtxWorldMeshfield, &g_Field[nCntField].g_mtxWorldMeshfield, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_Field[nCntField].g_posMeshfield.x, g_Field[nCntField].g_posMeshfield.y, g_Field[nCntField].g_posMeshfield.z);

		D3DXMatrixMultiply(&g_Field[nCntField].g_mtxWorldMeshfield, &g_Field[nCntField].g_mtxWorldMeshfield, &mtxTrans);

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_Field[nCntField].g_mtxWorldMeshfield);

		//���_�o�b�t�@���f�[�^�X�g���[���ݒ�
		pDevice->SetStreamSource(0, g_pVtxBuffMeshfield, 0, sizeof(VERTEX_3D));

		//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetIndices(g_pIdxBuffMeshField);

		//���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureMeshfield);

		//�|���S���̕`��
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 
			0,
			0,
			9,
			0,
			12);
	}
}

MESHFIELD GetMeshfield(void)
{
	return g_Field[0];
}