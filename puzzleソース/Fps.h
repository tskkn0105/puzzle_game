#ifndef FPS_H
#define FPS_H


class FPS
{
private:
	int time_kazu;	//�t���[�����w���ꏊ
	double fps;     //fps
	int frame_time[60];//�t���[���b�̊i�[�ꏊ
	int start_time;//�n�߂̎���

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