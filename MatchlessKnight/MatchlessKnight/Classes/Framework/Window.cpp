//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�
//!	@file	Window.cpp
//!
//!	@brief	�E�B���h�E�N���X�̃\�[�X�t�@�C��
//!
//!	@date	2017/12/26
//!
//!	@author	Masayuki Fuseya
//�߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁߁�

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "Window.h"
#include "MasaboLib.h"
#include "Game.h"

// �l�[���X�y�[�X�̏ȗ� ====================================================
using namespace DirectX;


//**********************************************************************
//!	@brief		�R���X�g���N�^
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		�Ȃ�
//**********************************************************************
Window::Window()
{
	// �C���X�^���g�n���h�����擾����
	m_hInstance = ::GetModuleHandle(NULL);

	// �X�^�[�g�A�b�v���
	STARTUPINFO si{};

	// STARTUPINFO�\���̂̓��e���擾����
	m_nCmdShow = si.dwFlags & STARTF_USESHOWWINDOW ? si.wShowWindow : SW_SHOWDEFAULT;
}



//**********************************************************************
//!	@brief		����������
//!
//!	@param[in]	�Q�[���̃^�C�g��
//!	@param[in]	�E�B���h�E�̉���
//!	@param[in]	�E�B���h�E�̍���
//!
//!	@return		�Ȃ�
//**********************************************************************
void Window::Initialize(const wchar_t* gameTitle, int width, int height)
{
	// �N���X��o�^����
	if (!RegisterWindowClass())
	{
		return;
	}

	// �E�B���h�E�𐶐�����
	if (!CreateGameWindow(gameTitle, width, height))
	{
		return;
	}

	ShowWindow(m_hWnd, m_nCmdShow);
}



//**********************************************************************
//!	@brief		�E�B���h�E�v���V�[�W��
//!
//!	@param[in]	�E�B���h�E�n���h��
//!	@param[in]	���b�Z�[�W�R�[�h
//!	@param[in]	���b�Z�[�W�̒ǉ����
//!	@param[in]	���b�Z�[�W�̒ǉ����
//!
//!	@return		�Ȃ�
//**********************************************************************
LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	static bool in_sizemove = false;
	static bool in_suspend = false;
	static bool minimized = false;
	static bool fullscreen = false;

	auto game = reinterpret_cast<Game*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_SIZE:
		if (wParam == SIZE_MINIMIZED)
		{
			if (!minimized)
			{
				minimized = true;
				if (!in_suspend && game)
					game->OnSuspending();
				in_suspend = true;
			}
		}
		else if (minimized)
		{
			minimized = false;
			if (in_suspend && game)
				game->OnResuming();
			in_suspend = false;
		}
		else if (!in_sizemove && game)
		{
			game->OnWindowSizeChanged(LOWORD(lParam), HIWORD(lParam));
		}
		break;

	case WM_ENTERSIZEMOVE:
		in_sizemove = true;
		break;

	case WM_EXITSIZEMOVE:
		in_sizemove = false;
		if (game)
		{
			RECT rc;
			GetClientRect(hWnd, &rc);

			game->OnWindowSizeChanged(rc.right - rc.left, rc.bottom - rc.top);
		}
		break;

	case WM_GETMINMAXINFO:
	{
		auto info = reinterpret_cast<MINMAXINFO*>(lParam);
		info->ptMinTrackSize.x = 320;
		info->ptMinTrackSize.y = 200;
	}
		break;

	case WM_ACTIVATEAPP:
		Mouse::ProcessMessage(message, wParam, lParam);
		if (game)
		{
			if (wParam)
			{
				game->OnActivated();
			}
			else
			{
				game->OnDeactivated();
			}
		}
		break;

	case WM_POWERBROADCAST:
		switch (wParam)
		{
		case PBT_APMQUERYSUSPEND:
			if (!in_suspend && game)
				game->OnSuspending();
			in_suspend = true;
			return TRUE;

		case PBT_APMRESUMESUSPEND:
			if (!minimized)
			{
				if (in_suspend && game)
					game->OnResuming();
				in_suspend = false;
			}
			return TRUE;
		}
		break;

	case WM_DESTROY:
		game->Exit();
		break;

	case WM_SYSKEYDOWN:
		if (wParam == VK_RETURN && (lParam & 0x60000000) == 0x20000000)
		{
			// �ÓT�I�� ALT+ENTER �t���X�N���[�� �g�O������������
			if (fullscreen)
			{
				SetWindowLongPtr(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
				SetWindowLongPtr(hWnd, GWL_EXSTYLE, 0);

				int width = 800;
				int height = 600;
				if (game)
					game->GetDefaultSize(width, height);

				ShowWindow(hWnd, SW_SHOWNORMAL);
				SetWindowPos(hWnd, HWND_TOP, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
			}
			else
			{
				SetWindowLongPtr(hWnd, GWL_STYLE, 0);
				SetWindowLongPtr(hWnd, GWL_EXSTYLE, WS_EX_TOPMOST);
				SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
				ShowWindow(hWnd, SW_SHOWMAXIMIZED);
			}

			fullscreen = !fullscreen;
		}
		break;

	case WM_MENUCHAR:
		// ���j���[���A�N�e�B�u�Ń��[�U�[���j�[���j�b�N�܂��̓A�N�Z�����[�^�L�[�Ɉ�v���Ȃ��L�[��
		// �������ꍇ�ł������𖳎����G���[�r�[�v��炳�Ȃ�
		return MAKELRESULT(0, MNC_CLOSE);

	// �}�E�X�֘A���b�Z�[�W
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Mouse::ProcessMessage(message, wParam, lParam);
		break;

	// �L�[�{�[�h�֘A���b�Z�[�W
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(message, wParam, lParam);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}



//**********************************************************************
//!	@brief		�N���X��o�^����
//!
//!	@param[in]	�Ȃ�
//!
//!	@return		true	����
//!	@return		false	���s
//**********************************************************************
bool Window::RegisterWindowClass()
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = m_hInstance;
	wcex.hIcon = LoadIcon(m_hInstance, L"IDI_ICON");
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"DirectXWindowClass";
	wcex.hIconSm = LoadIcon(wcex.hInstance, L"IDI_ICON");

	// �N���X��o�^����
	if (!RegisterClassEx(&wcex))
	{
		// �o�^�ł��Ȃ�����
		MessageBox(m_hWnd, L"RegisterClassEx Failed", NULL, MB_OK);
		return false;
	}

	return true;
}



//**********************************************************************
//!	@brief		�E�B���h�E�𐶐�����
//!
//!	@param[in]	�Q�[���̃^�C�g��
//!	@param[in]	�E�B���h�E�̉���
//!	@param[in]	�E�B���h�E�̍���
//!
//!	@return		true	����
//!	@return		false	���s
//**********************************************************************
bool Window::CreateGameWindow(const wchar_t* gameTitle, int width, int height)
{
	RECT rc;
	rc.top = 0;
	rc.left = 0;
	rc.right = static_cast<LONG>(width);
	rc.bottom = static_cast<LONG>(height);

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	// �E�B���h�E�𐶐�����
	HWND hWnd = CreateWindowEx(0, L"DirectXWindowClass", gameTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, m_hInstance, nullptr);

	if (!hWnd)
	{
		// �����ł��Ȃ�����
		MessageBox(m_hWnd, L"CreateWindowEx Failed", NULL, MB_OK);
		return false;
	}

	m_hWnd = hWnd;

	MasaboLib::Graphics::GetInstance()->SetHWnd(m_hWnd);

	return true;
}
