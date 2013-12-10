#include "GameMain.h"




///////////////���C�����[�v//////////////////////////////////////////////////

game::game() :
time(0),
end_flag(false),	//�I�������邩�ǂ����`�F�b�N
d_num(0),
gamestate(LOAD),
a(0),//��ŏ���
si(0.0)
{
#ifdef _DEBUG
	f = new FPS();	//���I��FPS�N���X���m��

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


// �v���O�����̊J�n�֐�
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpCmdLine, int nCmdShow )
{
	game *g = new game();
	g -> MAINLOOP();
	delete g;
	return 0 ;				// �\�t�g�̏I�� 
}


//���C�����[�v�̒��g
int game::MAINLOOP()
{
//	if (strcmp(lpCmdLine, "-f") != 0)
		ChangeWindowMode(TRUE);
		SetWindowSizeChangeEnableFlag(TRUE);

		SetGraphMode(640,480,16);
		//�^�C�g��
	SetWindowText("�p�Y������");
	//�E�B���h�E���[�h�̃T�C�Y�i�{���j
//	SetWindowSizeExtendRate(1.5);

	//DX���C�u�����̏���������
	if( DxLib_Init() == -1 ) return -1;
	//�`��Ώۂ𗠉�ʂɐݒ�
	SetDrawScreen(DX_SCREEN_BACK);
	//���ߐF�̐ݒ�
	SetTransColor(255,0,255);


		//���C�����[�v
	while(ProcessMessage()==0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && end_flag == false)
	{

		ClsDrawScreen();//��ʂ�����
	////�����ɂ�������//////////////////////////////////////////////////////	

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
		
	//////�����܂�///////////////////////////////////////////////////////
#ifdef _DEBUG
		f->drawFPS(0,450);	//FPS�\��
		f->Checkbar(0,0);

		ScreenFlip();		//��ʂ�؂�ւ�
		
		f->GetTime();
		
#endif
#ifndef _DEBUG
		//DrawFormatString(0,0,GetColor(255,255,255),"�����[�X��");
		ScreenFlip();
#endif

	}
	DxLib_End() ;			// �c�w���C�u�����g�p�̏I������

	return 0;
}

/**************************************************************************************************/