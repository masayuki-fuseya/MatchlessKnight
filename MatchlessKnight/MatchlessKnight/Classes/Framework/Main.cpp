//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	Main.cpp
//!
//!	@brief	�v���W�F�N�g�̃G���g���[�|�C���g
//!
//!	@date	2017/12/26
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "MyGame.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace std;
using namespace DirectX;


//**********************************************************************
//!	@brief		�G���g���[�|�C���g
//!
//!	@param[in]	�C���X�^���X�n���h��
//!	@param[in]	�C���X�^���X
//!	@param[in]	�R�}���h���C��
//!	@param[in]	�E�B���h�E�̍ŏ����A�ő剻�A�ʏ�\�����w�肷�邽�߂̃t���O
//!
//!	@return		0:����I��
//!	@return		1:�ُ�I��
//**********************************************************************
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    if (!XMVerifyCPUSupport())
        return 1;
	// COM���C�u����������������
    if (FAILED(CoInitializeEx(nullptr, COINITBASE_MULTITHREADED)))
        return 1;

	// �E�B���h�E�T�C�Y
	int width = 1024;
	int height = 768;

	// MyGame�𐶐�����
	MyGame myGame(width, height);
	// �Q�[�����X�V����
	MSG msg = myGame.Run();

	// Com���C�u�������I����������
    CoUninitialize();

    return (int) msg.wParam;
}
