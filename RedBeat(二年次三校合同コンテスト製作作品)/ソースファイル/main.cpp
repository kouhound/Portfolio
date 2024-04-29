#include<windows.h>//windowsの利用
#include<stdio.h>//sprintfの利用
#include"DirectX.h"//DirectXの利用
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
//プロトタイプ宣言
LRESULT CALLBACK WndProc(
	HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam
);
DWORD Before, now;
int WINAPI WinMain(
	//WindowsOSが一つ一つのプログラムを識別するための番号
	HINSTANCE hInstance,
	//互換性のために残された引数
	HINSTANCE hPrevInstance,
	//コマンドライン引数
	//プログラムを実行する際に渡される引数
	LPSTR lpCmdLine,
	//ウィンドウの表示方法
	int nCmdshow)
{

	/*int bt1,bt2,bt3;
	bt1=MessageBox(NULL,
	"1～4部？", "ジョジョネイター", MB_ICONINFORMATION|MB_YESNO);
	if(bt1==IDYES)
	{
		bt2 = MessageBox(NULL,
			"波紋が使える？", "ジョジョネイター", MB_ICONINFORMATION | MB_YESNO);



		if (bt2 == IDYES)
		{
			bt3 = MessageBox(NULL,
				"「何をするだァーッ」と言った？", "ジョジョネイター", MB_ICONINFORMATION | MB_YESNO);
			if (bt3 == IDYES)
			{
				MessageBox(NULL,
					"君が探しているのは\nジョナサン・ジョースターだね", "ジョジョネイター", MB_ICONINFORMATION | MB_OK);

			}
			if (bt3 == IDNO)
			{
				MessageBox(NULL,
					"君が探しているのは\nジョセフ・ジョースターだね", "ジョジョネイター", MB_ICONINFORMATION | MB_OK);

			}

		}
		if (bt2 == IDNO)
		{
			bt3 = MessageBox(NULL,
				"時止めが可能？", "ジョジョネイター", MB_ICONINFORMATION | MB_YESNO);
			if (bt3 == IDYES)
			{
				MessageBox(NULL,
					"君が探しているのは\n空条承太郎だね", "ジョジョネイター", MB_ICONINFORMATION | MB_OK);

			}
			if (bt3 == IDNO)
			{
				MessageBox(NULL,
					"君が探しているのは\n東方仗助だね", "ジョジョネイター", MB_ICONINFORMATION | MB_OK);

			}


		}



	}
	if (bt1 == IDNO)
	{
		bt2 = MessageBox(NULL,
			"すでにアニメが出ている？", "ジョジョネイター", MB_ICONINFORMATION | MB_YESNO);



		if (bt2 == IDYES)
		{
			bt3 = MessageBox(NULL,
				"親が吸血鬼？", "ジョジョネイター", MB_ICONINFORMATION | MB_YESNO);


			if (bt3 == IDYES)
			{
				 MessageBox(NULL,
					"君が探しているのは\nジョルノ・ジョバァーナだね", "ジョジョネイター", MB_ICONINFORMATION | MB_OK);

			}
			if (bt3 == IDNO)
			{
				 MessageBox(NULL,
					"君が探しているのは\n空条徐倫だね", "ジョジョネイター", MB_ICONINFORMATION | MB_OK);

			}




		}
		if (bt2 == IDNO)
		{
			bt3 = MessageBox(NULL,
				"レースに参加してる？", "ジョジョネイター", MB_ICONINFORMATION | MB_YESNO);

			if (bt3 == IDYES)
			{
				MessageBox(NULL,
					"君が探しているのは\nジョニィ・ジョースターだね", "ジョジョネイター", MB_ICONINFORMATION | MB_OK);

			}
			if (bt3 == IDNO)
			{
				MessageBox(NULL,
					"君が探しているのは\n東方定助だね", "ジョジョネイター", MB_ICONINFORMATION | MB_OK);

			}


		}
	}*/


	//ウィンドウクラス情報
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));
	//紐づいてるアプリケーション
	wcex.hInstance = hInstance;
	//ウィンドウクラスに設定する名称
	wcex.lpszClassName = "Class Name";
	wcex.lpfnWndProc = WndProc;
	wcex.style = CS_CLASSDC;
	wcex.cbSize = sizeof(WNDCLASSEX);
	//タスクバーやアプリケーション左上のアイコンを決定
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcex.hIconSm = wcex.hIcon;
	//マウスカーソルの見た目の設定
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//ウィンドウの背景
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//ウィンドウ情報の登録
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL,
			"ウィンドウクラスの登録に失敗", "エラー", MB_ICONINFORMATION | MB_OK);
		return 0;
	}
	//ウィンドウの作成
	//ウィンドウの作成が成功すると
	//ウィンドウハンドルするための番号が戻り値で帰る
	//表示されるウィンドウはタイトルバーを含めた高さになる
	//AdjustWindowRectEX()を使うと正しい大きさを計算できる
	HWND hWnd;
	hWnd = CreateWindowEx(
		//ウィンドウの外観動作の指定
		WS_EX_OVERLAPPEDWINDOW,
		//紐づけるウィンドウクラス情報
		wcex.lpszClassName,
		//ウィンドウのタイトル
		"game",
		//ウィンドウの外観動作の設定
		WS_CAPTION | WS_SYSMENU,
		//ウィンドウを表示する位置
		//Windowsにお任せしていい感じの位置に
		CW_USEDEFAULT, CW_USEDEFAULT,
		//ウィンドウのサイズ        
		960, 540, HWND_DESKTOP,

		NULL, hInstance, NULL);
	//ウィンドウが作成できないとき
	if (hWnd == NULL)
	{

		MessageBox(NULL, "ウインドウの作成に失敗", "エラー", MB_OK);
		return 0;
	}
	//ボタンの作成
	//CreateWindow関数のクラスに特定のワードを指定すると事前に準備されているウィンドウ（メニュー）が表示される
	/*CreateWindow
	(
		"Button", "PUSH!"
		, WS_CHILD | WS_VISIBLE
		//BS_XXX　ボタンスタイル、ボタン専用設定
		|BS_AUTOCHECKBOX,
		0,0,300,200,
		hWnd,NULL,hInstance,NULL
		);
	CreateWindow
	("edit","", WS_CHILD | WS_VISIBLE
		|ES_MULTILINE//複数行
		|ES_AUTOHSCROLL//水平に入力し続ける
		|ES_AUTOVSCROLL//垂直に入力し続ける
		,	0, 200, 300, 200, hWnd, NULL, hInstance, NULL);*/
		//ウィンドウの表示
	ShowWindow(hWnd, nCmdshow);
	UpdateWindow(hWnd);
	//DirectXの初期化
	HRESULT hr;
	hr = InitDirectX(960, 540, hWnd, false);
	if (FAILED(hr)) {
		MessageBox(hWnd, "DirectXの初期化に失敗", "ERROR", MB_ICONINFORMATION | MB_OK);
		return 0;
	}
	InitGeometory(960, 540);
	//サウンド初期化
	hr = InitSound();

	if (FAILED(hr)) {
		MessageBox(hWnd, "サウンドの初期化に失敗", "ERROR", MB_ICONINFORMATION | MB_OK);
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
			MessageBox(hWnd, "タイトルの初期化に失敗", "ERROR", MB_ICONINFORMATION | MB_OK);
			return 0;
		}
		break;
	case(GAME):
		//Gameの初期化
		hr = initgame();
		if (FAILED(hr)) {
			MessageBox(hWnd, "ゲームの初期化に失敗", "ERROR", MB_ICONINFORMATION | MB_OK);
			return 0;
		}



		break;
	default:
		break;

	}
	//メッセージループ
	MSG message;
	FPS fps;
	int count = 0;



	while (1)
	{

		//メッセージがあるか確認
		if (PeekMessage(&message, NULL, 0, 0, PM_NOREMOVE))
		{
			//メッセージ取得
			//WM_QUITのみ取得できないと判定される
			if (!GetMessage(&message, NULL, 0, 0))
			{
				//WM_QUITが届いた時だけ終了
				break;
			}
			else
			{
				//とどいためっせーじをWiddowsに転送
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




				//メッセージがないときにゲームの処理を優先
				//FPSの更新チェック
				if (fps.Ischeck()) {
					//更新処理
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

					//描画処理
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
	//終了処理
	
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
		//case WM_COMMAND://メニューが動作
		//	MessageBox(hWnd, "おされた", "確認", MB_ICONINFORMATION | MB_OK);
		//	break;
		/*case WM_MOUSEMOVE:
		{
			//マウス座標の情報はlParamに格納
			//4バイトに上位２バイト＝Y座標　下位２バイト＝X座標と格納
			//正しいデータを引き出すにはビット演算が必要
			WORD x = LOWORD(lParam);
			WORD y = HIWORD(lParam);
			char text[256];
			sprintf(text, "X:%d\nY=%d", x, y);
			MessageBox(hWnd, text, "確認", MB_ICONINFORMATION | MB_OK);
		}
		break;*/
	case WM_KEYDOWN://キー入力7

		//wParamにキーの情報が格納されている
		//キーの定義はVK_XXX
		if (wParam == VK_ESCAPE)
		{
			if (MessageBox(hWnd, "終了しますか？", "確認", MB_ICONINFORMATION | MB_YESNO) == IDYES)
			{
				//ウィンドウを破棄
				DestroyWindow(hWnd);
			}
		}

		break;
	case WM_CLOSE://ウィンドウを削除しようとしている
		if (MessageBox(hWnd, "終了しますか？", "確認", MB_ICONINFORMATION | MB_YESNO) == IDNO)
		{
			//ウィンドウ削除をキャンセル
			//さいごのDefWindowProcを呼び出さなければ処理が上書きされる
			return 0;
		}
		break;

	case WM_DESTROY://ウィンドウ削除
		//WM_QUITを送信
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