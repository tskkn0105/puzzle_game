#ifndef FPS_H
#define FPS_H


class FPS
{
private:
	int time_kazu;	//フレームを指す場所
	double fps;     //fps
	int frame_time[60];//フレーム秒の格納場所
	int start_time;//始めの時間

	unsigned long long int hi_start_time;
	int green;
public:
	FPS();
	~FPS();
	void GetTime();
	void drawFPS(int x,int y);
	void Checkbar(int x,int y);

};

#endif