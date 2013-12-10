#include "DxLib.h"
#include "Fps.h"


FPS::FPS() :		//初期化子リスト
time_kazu(0),
fps(0.0),
green(GetColor(0,255,0)){ start_time = 0; }

FPS::~FPS(){}



//FPSの処理
void FPS::drawFPS(int x,int y)
{
	frame_time[time_kazu%60] = GetNowCount() - start_time;	//ここで一フレームの時間を図る
	start_time = GetNowCount();								//ここから数え始める

	if(time_kazu%60 == 59)
	{
		fps = 0.0;
		for(int i=0;i<60;i++)
		{
			fps += (double)frame_time[i];
		}
		fps /= 60.0;
	}
	DrawFormatString(x,y,GetColor(255,0,0),"%2.2f FPS",1000.0/fps);

	time_kazu++;
}

void FPS::Checkbar(int x,int y)
{
	int length;
	int size = 20;

	length = (int)((GetNowHiPerformanceCount() - hi_start_time)*640/16666);

	DrawBox(x,y,length,size,green,true);
	DrawFormatString(x,y+size+5,GetColor(255,0,0),"%4d ％",length*100/640+15);
}

void FPS::GetTime()
{ hi_start_time = GetNowHiPerformanceCount(); }