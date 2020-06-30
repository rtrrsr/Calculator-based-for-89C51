#include "reg52.h"		//???
//???
#define uint unsigned int
#define ulongint unsigned long int
#define uchar unsigned char
//74LS138??????
sbit LS_WEA = P1^0;
sbit LS_WEB = P1^1;
sbit LS_WEC = P1^2;

uchar code smg_duan[11]={	
		0x3f,  //  0
		0x06,  //  1
		0x5b,  //  2
		0x4f,  //  3
		0x66,  //  4
		0x6d,  //  5
		0x7d,  //  6
		0x07,  //  7
		0x7f,  //  8
		0x6f,  //  9
		0x00,  //  ??
};		//?? ????
uchar display[8]={
		0x00,  //  ??
		0x00,  //  ??
		0x00,  //  ??
		0x00,  //  ??
		0x00,  //  ??
		0x00,  //  ??
		0x00,  //  ??
		0x00,  //  ??
};		//???????????????
//????
uint key_x;		//?????,????????
uint key_xy;	//?????
uint key_a;		//???????a
uint key_b;		//???????b
ulongint key_output;		//?????
//????
void slow_delay(uint a);		//?? T=a(ms)
void smg_display();		//??????????,??????138???
uint key();		//??????
//???
void main()
{
	P0 = 0x00;
	while(1)
	{
		key_a = key();

	}
}
//????
//?? T=a(ms)
void slow_delay(uint a)
{
	uint b;
	for (; a > 0; a--)
		for (b = 124; b > 0; b--);
}
//??????????,??????138???
void smg_display()
{
	uchar i;
	for(i = 0; i < 8; i++)
	{
		switch(i)
		{
			case(0):
				LS_WEA = 1; LS_WEB = 1; LS_WEC = 1;		//ABC=000,Y7~Y0=1111 1110,??
			break;
			case(1):
				LS_WEA = 0; LS_WEB = 1; LS_WEC = 1;		//ABC=100,Y7~Y0=1111 1101,??
			break;
			case(2):
				LS_WEA = 1; LS_WEB = 0; LS_WEC = 1;		//ABC=010,Y7~Y0=1111 1011,??
			break;
			case(3):
				LS_WEA = 0; LS_WEB = 0; LS_WEC = 1;		//ABC=110,Y7~Y0=1111 0111,??
			break;
			case(4):
				LS_WEA = 1; LS_WEB = 1; LS_WEC = 0;		//ABC=001,Y7~Y0=1110 1111,??
			break;
			case(5):
				LS_WEA = 0; LS_WEB = 1; LS_WEC = 0;		//ABC=101,Y7~Y0=1101 1111,???
			break;
			case(6):
				LS_WEA = 1; LS_WEB = 0; LS_WEC = 0;		//ABC=011,Y7~Y0=1011 1111,???
			break;
			case(7):
				LS_WEA = 0; LS_WEB = 0; LS_WEC = 0;		//ABC=111,Y7~Y0=0111 1111,???
			break;
		}
		P0 = display[i];		//??
		slow_delay(1);		//??
		P0 = 0x00;		//??
	}
}
//??????
uint key()
{
	uint keynum_x;		//x???
	uint keynum_y;		//y???
	static char Cycle_count;		//????,??????,?????0
	do
	{
		P2 = 0x0f;		//x????,y????
		if(P2 != 0x0f)
		{
			P2 = 0x0f;		//??y????????
			switch(P2)
			{
				case 0x07:keynum_y = 1; break;		//y1??????
				case 0x0b:keynum_y = 2; break;		//y2??????
				case 0x0d:keynum_y = 3; break;		//y3??????
				case 0x0e:keynum_y = 4; break;		//y4??????
			}
			P2 = 0xf0;		//??x????????
			switch(P2)
			{
				case 0xe0:keynum_x = 1; break;		//x1??????
				case 0xd0:keynum_x = 2; break;		//x2??????
				case 0xb0:keynum_x = 3; break;		//x3??????
				case 0x70:keynum_x = 4; break;		//x4??????
			}
			if(keynum_y == 1 && keynum_x == 1)
				key_x = 0;		//??????????(1,1)???,????????0
			if(keynum_y == 1 && keynum_x == 2)
				key_x = 1;		//??????????(1,2)???,????????1
			if(keynum_y == 1 && keynum_x == 3)
				key_x = 2;		//??????????(1,3)???,????????2
			if(keynum_y == 1 && keynum_x == 4)
				key_x = 10;		//??????????(1,4)???,????????10,????10??�+�
			if(keynum_y == 2 && keynum_x == 1)
				key_x = 3;		//??????????(2,1)???,????????3
			if(keynum_y == 2 && keynum_x == 2)
				key_x = 4;		//??????????(2,2)???,????????4
			if(keynum_y == 2 && keynum_x == 3)
				key_x = 5;		//??????????(2,3)???,????????5
			if(keynum_y == 2 && keynum_x == 4)
				key_x = 11;		//??????????(2,4)???,????????11,????11??�-�
			if(keynum_y == 3 && keynum_x == 1)
				key_x = 6;		//??????????(3,1)???,????????6
			if(keynum_y == 3 && keynum_x == 2)
				key_x = 7;		//??????????(3,2)???,????????7
			if(keynum_y == 3 && keynum_x == 3)
				key_x = 8;		//??????????(3,3)???,????????8
			if(keynum_y == 3 && keynum_x == 4)
				key_x = 12;		//??????????(3,4)???,????????12,????12??�*�
			if(keynum_y == 4 && keynum_x == 1)
				key_x = 9;		//??????????(4,1)???,????????9
			if(keynum_y == 4 && keynum_x == 2)
				key_x = 15;		//??????????(4,2)???,????????15,????15??�??�
			if(keynum_y == 4 && keynum_x == 3)
				key_x = 14;		//??????????(4,3)???,????????14,????14??�??�
			if(keynum_y == 4 && keynum_x == 4)
				key_x = 13;		//??????????(4,4)???,????????13,????11??�/�
			Cycle_count = Cycle_count + 1;
		}
		if(Cycle_count == 1 && key_x != 10 && key_x != 11 && key_x != 12 && key_x != 13 && key_x != 14 && key_x != 15)
			{
				key_xy = key_x;		//????????1??
				display[0] = smg_duan[key_xy];		//??
				smg_display();		////????1??????
			}
		if(Cycle_count == 2 && key_x != 10 && key_x != 11 && key_x != 12 && key_x != 13 && key_x != 14 && key_x != 15)
			{
				key_xy = 10 * key_xy + key_x;		//??2?????2??
				display[1] = smg_duan[key_xy / 10];		//2?????
				display[0] = smg_duan[key_xy % 10];		//2?????
				smg_display();		//????2??????
			}
		if(Cycle_count == 3 && key_x != 10 && key_x != 11 && key_x != 12 && key_x != 13 && key_x != 14 && key_x != 15)
			{
				key_xy = 10 * key_xy + key_x;		//??3?????3??
				display[2] = smg_duan[key_xy / 100];		//3?????
				display[1] = smg_duan[key_xy / 10 % 10];		//3?????
				display[0] = smg_duan[key_xy % 100 % 10];		//3?????
				smg_display();		//????3??????
			}
		if(Cycle_count == 4 && key_x != 10 && key_x != 11 && key_x != 12 && key_x != 13 && key_x != 14 && key_x != 15)
			{
				key_xy = 10 * key_xy + key_x;		//??4?????4??
				display[2] = smg_duan[key_xy / 1000];		//4?????
				display[1] = smg_duan[key_xy / 100 % 10];		//4?????
				display[0] = smg_duan[key_xy % 1000 % 100 / 10];		//4?????
				display[0] = smg_duan[key_xy % 1000 % 100 % 10];		//4?????
				smg_display();		//????4??????
			}
	}while(key_x != 10 || key_x != 11 || key_x != 12 || key_x != 13 || key_x != 14 || key_x != 15);
	//????????????,??????,???????
	return key_xy;
}
