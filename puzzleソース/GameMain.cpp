#include "GameMain.h"




///////////////メインループ//////////////////////////////////////////////////

game::game() :
time(0),
end_flag(false),	//終了させるかどうかチェック
d_num(0),
gamestate(LOAD),
a(0),//後で消せ
si(0.0)
{
#ifdef _DEBUG
	f = new FPS();	//動的にFPSクラスを確保

#endif

}

game::~game()
{
	bl1[0].del_p();
	d_bl1[0].del_p();
	delete st;
	delete [] bl1;
	delete [] bl2;
	delete [] d_bl1;
	delete [] d_bl2;
	delete cur1;
	delete cur2;
#ifdef _DEBUG
	delete f;

#endif
}


// プログラムの開始関数
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	game *g = new game();
	g -> MAINLOOP();
	delete g;
	return 0 ;				// ソフトの終了 
}


//メインループの中身
int game::MAINLOOP()
{
//	if (strcmp(lpCmdLine, "-f") != 0)
		ChangeWindowMode(TRUE);
		SetWindowSizeChangeEnableFlag(TRUE);

		SetGraphMode(640,480,16);
		//タイトル
	SetWindowText("パズルくん");
	//ウィンドウモードのサイズ（倍率）
//	SetWindowSizeExtendRate(1.5);

	//DXライブラリの初期化処理
	if( DxLib_Init() == -1 ) return -1;
	//描画対象を裏画面に設定
	SetDrawScreen(DX_SCREEN_BACK);
	//透過色の設定
	SetTransColor(255,0,255);


		//メインループ
	while(ProcessMessage()==0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && end_flag == false)
	{

		ClsDrawScreen();//画面を消去
	////ここにかきこむ//////////////////////////////////////////////////////	

		ps1.pad(1);
		ps2.pad(2);

		switch(gamestate)
		{
		case LOAD:		 gameLoad();		break;

		case TITLE:		 gameTitle();		break;

		case MENU:		 gameMenu();		break;

		case CHOICE:	 gameChoice();		break;

		case AREA:		 gameArea();		break;

		case BATTLE1:	 gameBattle1();		break;

		case BATTLE2:	 gameBattle2();		break;

		case BATTLE3:	 gameBattle3();		break;

		case CONTINUE:	 gameContinue();	break;

		case GAMEOVER:	 gameGameover();	break;

		case RANKING:	 gameRanking();		break;

		case RANK_ENTRY: gameRank_entry();	break;

		case OPTION:	 gameOption();		break;

		case TUTORIAL:	 gameTutorial();	break;
		}
		
	//////ここまで///////////////////////////////////////////////////////
#ifdef _DEBUG
		f->drawFPS(0,450);	//FPS表示
		f->Checkbar(0,0);

		ScreenFlip();		//画面を切り替え
		
		f->GetTime();
		
#endif
#ifndef _DEBUG
		//DrawFormatString(0,0,GetColor(255,255,255),"リリースよ");
		ScreenFlip();
#endif

	}
	DxLib_End() ;			// ＤＸライブラリ使用の終了処理

	return 0;
}

/**************************************************************************************************/