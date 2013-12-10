#include "PadState.h"
#include "DxLib.h"

padstate::padstate() :
up(0),
down(0),
left(0),
right(0)
{
	for(int i=0;i<10;i++)
	{
		pi[i]=i;
		input[i] = 0;
	}
	next = 0;
}

int padstate::pad(int x)
{
	
	int p;

	switch(x)
	{
	case 1:
		p = GetJoypadInputState(DX_INPUT_KEY_PAD1) ;
		break;
	case 2:
		p = GetJoypadInputState(DX_INPUT_PAD2) ;
		break;
	default:
		return -1;
	}

	if(p & PAD_INPUT_UP || up<0){up++;} else if(up>0){ up = -1; }
	if(p & PAD_INPUT_DOWN || down<0){down++;} else if(down>0){ down = -1; }
	if(p & PAD_INPUT_LEFT || left<0){left++;} else if(left>0){ left = -1; }
	if(p & PAD_INPUT_RIGHT || right<0){right++;} else if(right>0){ right = -1; }

	for(int i=0;i<10;i++)
	{
		next = pi[i];


		switch(next)
		{
		case 0:
			if(p & PAD_INPUT_A || input[i]<0){input[i]++;} else if(input[i]>0){ input[i] = -1; }
			break;
		case 1:
			if(p & PAD_INPUT_B || input[i]<0){input[i]++;} else if(input[i]>0){ input[i] = -1; }
			break;
		case 2:
			if(p & PAD_INPUT_C || input[i]<0){input[i]++;} else if(input[i]>0){ input[i] = -1; }
			break;
		case 3:
			if(p & PAD_INPUT_X || input[i]<0){input[i]++;} else if(input[i]>0){ input[i] = -1; }
			break;
		case 4:
			if(p & PAD_INPUT_Y || input[i]<0){input[i]++;} else if(input[i]>0){ input[i] = -1; }
			break;
		case 5:
			if(p & PAD_INPUT_Z || input[i]<0){input[i]++;} else if(input[i]>0){ input[i] = -1; }
			break;
		case 6:
			if(p & PAD_INPUT_L || input[i]<0){input[i]++;} else if(input[i]>0){ input[i] = -1; }
			break;
		case 7:
			if(p & PAD_INPUT_R || input[i]<0){input[i]++;} else if(input[i]>0){ input[i] = -1; }
			break;
		case 8:
			if(p & PAD_INPUT_START || input[i]<0){input[i]++;} else if(input[i]>0){ input[i] = -1; }
			break;
		case 9:
			if(p & PAD_INPUT_M || input[i]<0){input[i]++;} else if(input[i]>0){ input[i] = -1; }
			break;
		}

		
	}

	

		
	
	return 0;
}