#include "main.h"
#include "model.h"
#include "input.h"
#include "camera.h"
#include "Bullet.h"
#include "shadow.h"

//�}�N����`
#define COMPARIZON_MIN								(100.0f)
#define COMPARIZON_MAX								(-100.0f)

//�O���[�o���ϐ��錾
LPD3DXMESH g_pMeshModel = NULL;						//���b�V���ւ̃|�C���^
LPD3DXBUFFER g_pBuffMatModel = NULL;				//�}�e���A���ւ̃|�C���^
DWORD g_dwNumMatModel = 0;							//�}�e���A���̐�
MODEL g_Model;

//==============================================
//���f���̏���������
//==============================================
void InitModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nNumVtx;				//���_��
	DWORD dwSizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;				//���_�o�b�t�@�ւ̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_Model.g_posModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Model.g_rotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX("data\\MODEL\\car000.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel,
		NULL,
		&g_dwNumMatModel,
		&g_pMeshModel);

	g_Model.g_VtxMinModel = D3DXVECTOR3(COMPARIZON_MIN, COMPARIZON_MIN, COMPARIZON_MIN);
	g_Model.g_VtxMaxModel = D3DXVECTOR3(COMPARIZON_MAX, COMPARIZON_MAX, COMPARIZON_MAX);

	//���_�����擾
	nNumVtx = g_pMeshModel->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	dwSizeFVF = D3DXGetFVFVertexSize(g_pMeshModel->GetFVF());

	//���_�o�b�t�@�����b�N
	g_pMeshModel->LockVertexBuffer(D3DLOCK_READONLY,(void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;					//���_���W�̑��

		if (g_Model.g_VtxMinModel.x > vtx.x)
		{
			g_Model.g_VtxMinModel.x = vtx.x;
		}

		else if (g_Model.g_VtxMaxModel.x < vtx.x)
		{
			g_Model.g_VtxMaxModel.x = vtx.x;
		}

		if (g_Model.g_VtxMinModel.y > vtx.y)
		{
			g_Model.g_VtxMinModel.y = vtx.y;
		}

		else if (g_Model.g_VtxMaxModel.y < vtx.y)
		{
			g_Model.g_VtxMaxModel.y = vtx.y;
		}

		if (g_Model.g_VtxMinModel.z > vtx.z)
		{
			g_Model.g_VtxMinModel.z = vtx.z;
		}

		else if (g_Model.g_VtxMaxModel.z < vtx.z)
		{
			g_Model.g_VtxMaxModel.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;					//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	//���_�o�b�t�@���A�����b�N
	g_pMeshModel->UnlockVertexBuffer();

	SetShadow(TYPESHADOW_PLAYER, true);
}

//==============================================
//���f���̏I������
//==============================================
void UninitModel(void)
{

}

//==============================================
//���f���̍X�V����
//==============================================
void UpdateModel(void)
{
	Camera pCamera;

	pCamera = GetCamera();

	if (GetKeyboardPress(DIK_A) == true)
	{
		g_Model.g_posModel.x += sinf(D3DX_PI * -0.5f + pCamera.rot.y);
		g_Model.g_posModel.z += cosf(D3DX_PI * -0.5f + pCamera.rot.y);

		g_Model.g_DestrotModel.y = D3DX_PI * 0.5f + pCamera.rot.y;
	}

	else if (GetKeyboardPress(DIK_D) == true)
	{
		g_Model.g_posModel.x += sinf(D3DX_PI * 0.5f + pCamera.rot.y);
		g_Model.g_posModel.z += cosf(D3DX_PI * 0.5f + pCamera.rot.y);

		g_Model.g_DestrotModel.y = D3DX_PI * -0.5f + pCamera.rot.y;
	}

	else if (GetKeyboardPress(DIK_W) == true)
	{
		g_Model.g_posModel.x += sinf(D3DX_PI * 0.0f + pCamera.rot.y);
		g_Model.g_posModel.z += cosf(D3DX_PI * 0.0f + pCamera.rot.y);

		g_Model.g_DestrotModel.y = D3DX_PI * 1.0f + pCamera.rot.y;
	}

	else if (GetKeyboardPress(DIK_S) == true)
	{
		g_Model.g_posModel.x += sinf(D3DX_PI * 1.0f + pCamera.rot.y);
		g_Model.g_posModel.z += cosf(D3DX_PI * 1.0f + pCamera.rot.y);

		g_Model.g_DestrotModel.y = D3DX_PI * 0.0f + pCamera.rot.y;
	}

	g_Model.g_DiffrotModel.y = g_Model.g_DestrotModel.y - g_Model.g_rotModel.y;

	//�J�����̕␳
	if (g_Model.g_DiffrotModel.y > D3DX_PI)
	{
		g_Model.g_DiffrotModel.y += -D3DX_PI * 2;
	}

	else if (g_Model.g_DiffrotModel.y < -D3DX_PI)
	{
		g_Model.g_DiffrotModel.y += D3DX_PI * 2;
	}

	g_Model.g_rotModel.y += g_Model.g_DiffrotModel.y * 0.1f;

	//���f���̕␳
	if (g_Model.g_rotModel.y > D3DX_PI)
	{
		g_Model.g_rotModel.y = -D3DX_PI;
	}

	else if (g_Model.g_rotModel.y < -D3DX_PI)
	{
		g_Model.g_rotModel.y = D3DX_PI;
	}

	if (GetKeyboardTrigger(DIK_SPACE) == true)
	{
		SetBullet(g_Model.g_posModel, g_Model.g_rotModel, 100);
		SetShadow(TYPESHADOW_BULLET, true);
	}
}

//==============================================
//���f���̕`�揈��
//==============================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;                //
	D3DMATERIAL9 matDef;                        //
	D3DXMATERIAL *pMat;                         //

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_Model.g_mtxWorldModel);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Model.g_rotModel.y, g_Model.g_rotModel.x, g_Model.g_rotModel.z);

	D3DXMatrixMultiply(&g_Model.g_mtxWorldModel, &g_Model.g_mtxWorldModel, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_Model.g_posModel.x, g_Model.g_posModel.y, g_Model.g_posModel.z);

	D3DXMatrixMultiply(&g_Model.g_mtxWorldModel, &g_Model.g_mtxWorldModel, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_Model.g_mtxWorldModel);

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_dwNumMatModel; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//���f��(�p�[�c)���`��
		g_pMeshModel->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

MODEL GetModel(void)
{
	return g_Model;
}