#include<windows.h>//windows�̗��p
#include<stdio.h>//sprintf�̗��p
#include"DirectX.h"//DirectX�̗��p
#include"Game.h"
#include"title.h"
#include"FPS.h"
#include "Keyboard.h"
#include"Sound.h"
#include"Geometory.h"
#include "scene.h"
static scene g_CurSC;
static scene g_NextSC;
#pragma comment(lib,"winmm.lib")

#include <wchar.h>
//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(
	HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam
);
DWORD Before, now;
int WINAPI WinMain(
	//WindowsOS�����̃v���O���������ʂ��邽�߂̔ԍ�
	HINSTANCE hInstance,
	//�݊����̂��߂Ɏc���ꂽ����
	HINSTANCE hPrevInstance,
	//�R�}���h���C������
	//�v���O���������s����ۂɓn��������
	LPSTR lpCmdLine,
	//�E�B���h�E�̕\�����@
	int nCmdshow)
{

	/*int bt1,bt2,bt3;
	bt1=MessageBox(NULL,
	"1�`4���H", "�W���W���l�C�^�[", MB_ICONINFORMATION|MB_YESNO);
	if(bt1==IDYES)
	{
		bt2 = MessageBox(NULL,
			"�g�䂪�g����H", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_YESNO);



		if (bt2 == IDYES)
		{
			bt3 = MessageBox(NULL,
				"�u�������邾�@�[�b�v�ƌ������H", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_YESNO);
			if (bt3 == IDYES)
			{
				MessageBox(NULL,
					"�N���T���Ă���̂�\n�W���i�T���E�W���[�X�^�[����", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_OK);

			}
			if (bt3 == IDNO)
			{
				MessageBox(NULL,
					"�N���T���Ă���̂�\n�W���Z�t�E�W���[�X�^�[����", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_OK);

			}

		}
		if (bt2 == IDNO)
		{
			bt3 = MessageBox(NULL,
				"���~�߂��\�H", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_YESNO);
			if (bt3 == IDYES)
			{
				MessageBox(NULL,
					"�N���T���Ă���̂�\n��������Y����", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_OK);

			}
			if (bt3 == IDNO)
			{
				MessageBox(NULL,
					"�N���T���Ă���̂�\n������������", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_OK);

			}


		}



	}
	if (bt1 == IDNO)
	{
		bt2 = MessageBox(NULL,
			"���łɃA�j�����o�Ă���H", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_YESNO);



		if (bt2 == IDYES)
		{
			bt3 = MessageBox(NULL,
				"�e���z���S�H", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_YESNO);


			if (bt3 == IDYES)
			{
				 MessageBox(NULL,
					"�N���T���Ă���̂�\n�W�����m�E�W���o�@�[�i����", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_OK);

			}
			if (bt3 == IDNO)
			{
				 MessageBox(NULL,
					"�N���T���Ă���̂�\n������ς���", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_OK);

			}




		}
		if (bt2 == IDNO)
		{
			bt3 = MessageBox(NULL,
				"���[�X�ɎQ�����Ă�H", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_YESNO);

			if (bt3 == IDYES)
			{
				MessageBox(NULL,
					"�N���T���Ă���̂�\n�W���j�B�E�W���[�X�^�[����", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_OK);

			}
			if (bt3 == IDNO)
			{
				MessageBox(NULL,
					"�N���T���Ă���̂�\n�����菕����", "�W���W���l�C�^�[", MB_ICONINFORMATION | MB_OK);

			}


		}
	}*/


	//�E�B���h�E�N���X���
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	//�R�Â��Ă�A�v���P�[�V����
	wcex.hInstance = hInstance;
	//�E�B���h�E�N���X�ɐݒ肷�閼��
	wcex.lpszClassName = "Class Name";
	wcex.lpfnWndProc = WndProc;
	wcex.style = CS_CLASSDC;
	wcex.cbSize = sizeof(WNDCLASSEX);
	//�^�X�N�o�[��A�v���P�[�V��������̃A�C�R��������
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	//�}�E�X�J�[�\���̌����ڂ̐ݒ�
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//�E�B���h�E�̔w�i
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//�E�B���h�E���̓o�^
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			"�E�B���h�E�N���X�̓o�^�Ɏ��s", "�G���[", MB_ICONINFORMATION | MB_OK);
		return 0;
	}
	//�E�B���h�E�̍쐬
	//�E�B���h�E�̍쐬�����������
	//�E�B���h�E�n���h�����邽�߂̔ԍ����߂�l�ŋA��
	//�\�������E�B���h�E�̓^�C�g���o�[���܂߂������ɂȂ�
	//AdjustWindowRectEX()���g���Ɛ������傫�����v�Z�ł���
	HWND hWnd;
	hWnd = CreateWindowEx(
		//�E�B���h�E�̊O�ϓ���̎w��
		WS_EX_OVERLAPPEDWINDOW,
		//�R�Â���E�B���h�E�N���X���
		wcex.lpszClassName,
		//�E�B���h�E�̃^�C�g��
		"game",
		//�E�B���h�E�̊O�ϓ���̐ݒ�
		WS_CAPTION | WS_SYSMENU,
		//�E�B���h�E��\������ʒu
		//Windows�ɂ��C�����Ă��������̈ʒu��
		CW_USEDEFAULT, CW_USEDEFAULT,
		//�E�B���h�E�̃T�C�Y        
		960, 540, HWND_DESKTOP,

		NULL, hInstance, NULL);
	//�E�B���h�E���쐬�ł��Ȃ��Ƃ�
	if (hWnd == NULL)
	{

		MessageBox(NULL, "�E�C���h�E�̍쐬�Ɏ��s", "�G���[", MB_OK);
		return 0;
	}
	//�{�^���̍쐬
	//CreateWindow�֐��̃N���X�ɓ���̃��[�h���w�肷��Ǝ��O�ɏ�������Ă���E�B���h�E�i���j���[�j���\�������
	/*CreateWindow
	(
		"Button", "PUSH!"
		, WS_CHILD | WS_VISIBLE
		//BS_XXX�@�{�^���X�^�C���A�{�^����p�ݒ�
		|BS_AUTOCHECKBOX,
		0,0,300,200,
		hWnd,NULL,hInstance,NULL
		);
	CreateWindow
	("edit","", WS_CHILD | WS_VISIBLE
		|ES_MULTILINE//�����s
		|ES_AUTOHSCROLL//�����ɓ��͂�������
		|ES_AUTOVSCROLL//�����ɓ��͂�������
		,	0, 200, 300, 200, hWnd, NULL, hInstance, NULL);*/
		//�E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdshow);
	UpdateWindow(hWnd);
	//DirectX�̏�����
	HRESULT hr;
	hr = InitDirectX(960, 540, hWnd, false);
	if (FAILED(hr)) {
		MessageBox(hWnd, "DirectX�̏������Ɏ��s", "ERROR", MB_ICONINFORMATION | MB_OK);
		return 0;
	}
	InitGeometory(960, 540);
	//�T�E���h������
	hr = InitSound();

	if (FAILED(hr)) {
		MessageBox(hWnd, "�T�E���h�̏������Ɏ��s", "ERROR", MB_ICONINFORMATION | MB_OK);
		return 0;
	}

	WCHAR wcText[256];

	timeBeginPeriod(1);
	Before = timeGetTime();


	g_CurSC = g_NextSC =TITLE;
	switch (g_CurSC)
	{
	case(TITLE):
		hr = inittitle();
		if (FAILED(hr)) {
			MessageBox(hWnd, "�^�C�g���̏������Ɏ��s", "ERROR", MB_ICONINFORMATION | MB_OK);
			return 0;
		}
		break;
	case(GAME):
		//Game�̏�����
		hr = initgame();
		if (FAILED(hr)) {
			MessageBox(hWnd, "�Q�[���̏������Ɏ��s", "ERROR", MB_ICONINFORMATION | MB_OK);
			return 0;
		}



		break;
	default:
		break;

	}
	//���b�Z�[�W���[�v
	MSG message;
	FPS fps;
	int count = 0;



	while (1)
	{

		//���b�Z�[�W�����邩�m�F
		if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE))
		{
			//���b�Z�[�W�擾
			//WM_QUIT�̂ݎ擾�ł��Ȃ��Ɣ��肳���
			if (!GetMessage(&message, NULL, 0, 0))
			{
				//WM_QUIT���͂����������I��
				break;
			}
			else
			{
				//�Ƃǂ����߂����[����Widdows�ɓ]��
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{


			now = timeGetTime();
			UpdateTime(now - Before);

			if (fps.Ischeckms())
			{


				//for (int i = 0; i < BULLET_NUM; i++)
				//{

				//	CheckNote(i);

				//}

			}




				//���b�Z�[�W���Ȃ��Ƃ��ɃQ�[���̏�����D��
				//FPS�̍X�V�`�F�b�N
				if (fps.Ischeck()) {
					//�X�V����
					KeyboardUpdate();
					switch (g_CurSC)
					{

					case(TITLE):
						updatetitle();
						break;
					case(GAME):


						updategame();

						for (int i = 0; i < BULLET_NUM; i++)
						{

							CheckNote(i);

						}
						break;
					default:
						break;
					}

					//�`�揈��
					BeginDirectX();
					switch (g_CurSC)
					{

					case(TITLE):
						drawtitle();
						break;
					case(GAME):
						drawgame();
						break;
					default:
						break;
					}


					EndDirectX();

				}
			



		}
		//count++;
	}
	//�I������
	
	switch (g_CurSC)
	{

	case(TITLE):
		uninittitle();
		break;
	case(GAME):
		uninitgame();
		break;
	default:
		break;
	}

	UninitSound();
	UninitGeometory();
	UninitDirectX();
	return 0;
}
LRESULT CALLBACK WndProc(
	HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam
) {
	switch (message)
	{
		//case WM_COMMAND://���j���[������
		//	MessageBox(hWnd, "�����ꂽ", "�m�F", MB_ICONINFORMATION | MB_OK);
		//	break;
		/*case WM_MOUSEMOVE:
		{
			//�}�E�X���W�̏���lParam�Ɋi�[
			//4�o�C�g�ɏ�ʂQ�o�C�g��Y���W�@���ʂQ�o�C�g��X���W�Ɗi�[
			//�������f�[�^�������o���ɂ̓r�b�g���Z���K�v
			WORD x = LOWORD(lParam);
			WORD y = HIWORD(lParam);
			char text[256];
			sprintf(text, "X:%d\nY=%d", x, y);
			MessageBox(hWnd, text, "�m�F", MB_ICONINFORMATION | MB_OK);
		}
		break;*/
	case WM_KEYDOWN://�L�[����7

		//wParam�ɃL�[�̏�񂪊i�[����Ă���
		//�L�[�̒�`��VK_XXX
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(hWnd, "�I�����܂����H", "�m�F", MB_ICONINFORMATION | MB_YESNO) == IDYES)
			{
				//�E�B���h�E��j��
				DestroyWindow(hWnd);
			}
		}

		break;
	case WM_CLOSE://�E�B���h�E���폜���悤�Ƃ��Ă���
		if (MessageBox(hWnd, "�I�����܂����H", "�m�F", MB_ICONINFORMATION | MB_YESNO) == IDNO)
		{
			//�E�B���h�E�폜���L�����Z��
			//��������DefWindowProc���Ăяo���Ȃ���Ώ������㏑�������
			return 0;
		}
		break;

	case WM_DESTROY://�E�B���h�E�폜
		//WM_QUIT�𑗐M
		PostQuitMessage(0);
		break;

	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
scene getCursvene()
{
	return g_CurSC;
}

scene getNextscene()
{
	return g_NextSC;
}

void StartSC(scene next)
{
	g_NextSC = next;
	SetSC();
}



void SetSC()
{
	switch (g_CurSC)
	{
	case(TITLE):
		uninittitle();
		break;
	case(GAME):
		uninitgame();
		break;
	default:
		break;
	}
	g_CurSC = g_NextSC;
	switch (g_CurSC)
	{
	case(TITLE):
		inittitle();
		break;
	case(GAME):
		Before = timeGetTime();
		initgame();
		break;
	default:
		break;
	}
}