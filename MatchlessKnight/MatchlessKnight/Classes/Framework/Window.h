//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	Window.h
//!
//!	@brief	�E�B���h�E�N���X�̃w�b�_�t�@�C��
//!
//!	@date	2017/12/26
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#ifndef  WINDOW
#define  WINDOW

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <Windows.h>


class Window
{
private:
	// �E�B���h�E�n���h��
	HWND m_hWnd;
	// �C���X�^���X�n���h��
	HINSTANCE m_hInstance;
	int m_nCmdShow;
public:
	Window();

	// �N���X��o�^���E�B���h�E�𐶐�����
	void Initialize(const wchar_t* gameTitle, int width, int height);

	// �E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	// �N���X��o�^����
	bool RegisterWindowClass();
	// �E�B���h�E�𐶐�����
	bool CreateGameWindow(const wchar_t* gameTitle, int width, int height);
};

#endif	// WINDOW
