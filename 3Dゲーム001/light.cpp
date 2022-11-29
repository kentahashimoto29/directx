#include "main.h"
#include "light.h"

//�O���[�o���ϐ��錾
D3DLIGHT9 g_light[2];                   //���C�g�̏��

//==============================================
//���C�g�̏���������
//==============================================
void InitLight(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	pDevice = GetDevice();

	D3DXVECTOR3 vecDir;              //�ݒ�p�����x�N�g��

	//���C�g�̏����N���A����
	ZeroMemory(&g_light, sizeof(D3DLIGHT9));

	//���C�g�̎�ނ�ݒ�
	g_light[0].Type = D3DLIGHT_DIRECTIONAL;
	g_light[1].Type = D3DLIGHT_DIRECTIONAL;

	//���C�g�̊g�U����ݒ�
	g_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_light[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�̕�����ݒ�
	vecDir = D3DXVECTOR3(0.1f, -0.2f, 0.1f);
	D3DXVec3Normalize(&vecDir, &vecDir);             //�x�N�g���𐳋K������
	g_light[0].Direction = vecDir;

	vecDir = D3DXVECTOR3(-0.1f, -0.2f, -0.1f);
	D3DXVec3Normalize(&vecDir, &vecDir);             //�x�N�g���𐳋K������
	g_light[1].Direction = vecDir;

	//���C�g��ݒ肷��
	pDevice->SetLight(0, &g_light[0]);
	pDevice->SetLight(1, &g_light[1]);

	//���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
}

//==============================================
//���C�g�̏I������
//==============================================
void UninitLight(void)
{

}
//==============================================
//���C�g�̍X�V����
//==============================================
void UpdateLight(void)
{

}