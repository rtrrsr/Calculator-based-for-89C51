//ͷ�ļ�
#include <reg52.h>
#include <ctype.h>		//isdigit()����
#include <stdlib.h>		//atol()����
//�궨��
#define uint unsigned int
#define uchar unsigned char
#define ulint unsigned long
//λ����
sbit LS_WEA = P1^0;
sbit LS_WEB = P1^1;
sbit LS_WEC = P1^2;		//74HC138������λ����
sbit LED = P1^3;		//LED
sbit BUZZER = P1^4;		//������
//ȫ�ֱ���
uchar handle_x[9], handle_y[9];		//���̷����ַ�������飬���ڴ�ż��̷��ص��ַ�
uchar code display[] = {
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
		0x00   //  ȫ��
};//�ַ���������ֶ�
uchar display_cache[] = {
				10,
				10,
				10,
				10,
				10,
				10,
				10,
				10,
				10,
};//��ʾ����
//��������
void delay(uint z);			  //��ʱ����
ulint operation(ulint operand_xx,ulint operand_yy,uchar operator_z);
//���㣬��������x��������y�����뺯��������������
uchar keyscan();					//����ɨ�����'@','#'�ֱ��ʾ�����û�а�������
void cache(ulint input);	//������������ʾ����
void smg_display();				//��ʾ�������������λѡ��ʾ����������ܼ�138������
//������
void main()
{
	ulint operand_x, operand_y, final_result;	//������x��������y�����ս��
	uchar ckey, a = 0, b = 0;		//ckey=���̷����ַ���a��b��ֵΪ�㣬ͨ��ѭ��ʵ�ֽ�������������ַ�����ʽ����������ַ��������
	uchar operator;					    //�����
	uchar c, judge_operand_xy = 0;	//ѭ�����־��c���������ж���judge_operand_xy
init:								//goto��䶨λ��ǩ
	cache(0);					//��ʼ����ʾ����
	smg_display();
	final_result = 0;
	a = b = 0;
	judge_operand_xy = 0;			//��ʼ��
	for(c = 0; c < 9; c++)
	{
		handle_x[c] = '\0';
		handle_y[c] = '\0';
	}								//???
	while(1)
	{
		ckey = keyscan();			//��ʼ��
		if(ckey != '#')				//������̱�����
		{
			if(isdigit(ckey))		//isdigit����,������Ϊ���������֣��򷵻�TRUE(��),���򷵻�NULL(0)
			{
				switch(judge_operand_xy)
				{
					case 0:
							handle_x[a] = ckey;			//�����̷����ַ���������̷����ַ��������
							handle_x[a+1] = '\0';		//�ַ�'\0' : ASCII��Ϊ0,��ʾһ���ַ�������
							operand_x = atol(handle_x);	//atol()����,�����̷����ַ���������е��ַ���ת���ɳ�������
							a++;
							cache(operand_x);			//��������x������ʾ����
							smg_display();				//��ʾ
							break;
					case 1:
							handle_y[b] = ckey;			//�����̷����ַ���������̷����ַ��������
							handle_y[b+1] = '\0';		//�ַ�'\0' : ASCII��Ϊ0����ʾһ���ַ�������
							operand_y = atol(handle_y);	//atol()����,�����̷����ַ���������е��ַ���ת���ɳ�������
							b++;
							cache(operand_y);			//��������y������ʾ����
							smg_display();				//��ʾ
							break;
					default:break;
				}
			}
			else if(ckey == '+' || ckey == '-' || ckey== '*' || ckey == '/')	//������̷����ַ�Ϊ'+','-','*','/'
			{
				judge_operand_xy = 1;//������ж���=1,���ݸ�switch()������׼��Ϊ������y��ֵ
				operator = ckey;		 //���������
				cache(0);					   //�����ʾ����
				display_cache[8] = 10;		//��ʾ����Ϊ��
				smg_display();				//��ʾ
			}
			else if(ckey == '=')		//������������ַ�Ϊ'='
			{
				final_result = operation(operand_x,operand_y,operator);	//�������ս��
				cache(final_result);		//�����ս��������ʾ����
				smg_display();				//��ʾ
				while(1)					//��������ȴ����㰴������
				{
					ckey = keyscan();
					if(ckey == '@')			//��������������
						goto init;			//��ʼ��ת
					else					//��������û������
						{
							cache(final_result);
							smg_display();		//������ʾ���
						}
				}
			}
			else if(ckey == '@')		//������������ַ�Ϊ����
			{
				goto init;			//��ת
			}
		}
		smg_display();				//�������û�����£�����ʾ��ʼֵ
	}
}
//�Ӻ���
//��ʱ����
void delay(uint z)
{
	uint x, y;
	for(x = z; x > 0; x--)
		for(y = 120; y > 0; y--);
}
//���㣬��������x��������y�����뺯��������������
ulint operation(ulint operand_xx,ulint operand_yy,uchar operator_z)
{
	ulint results;
	switch(operator_z)		//�жϷ���
	{
		case '+' : results = operand_xx + operand_yy;	break;
		case '-' : results = operand_xx - operand_yy;	break;
		case '*' : results = operand_xx * operand_yy;	break;
		case '/' : results = operand_xx / operand_yy;	break;
		default :  break;
	}
	return results;
}
//����ɨ�����'@','#'�ֱ��ʾ�����û�а�������
uchar keyscan()
{
	uchar skey;                     //����ֵ��Ǳ���
//ɨ����̵�1��
	P2 = 0x7f;						//��1��Ϊ0
	if((P2 & 0x0f) != 0x0f)	    //�а�������
	{
		delay(3);		            //ȥ������ʱ
		if((P2 & 0x0f) != 0x0f)	//���а�������
		{
			LED = 0;				//����LED
			BUZZER = 0;			//��������
			switch(P2)			//ʶ�𰸼�����ֵ
			{
				case 0x77: skey = '7'; break;	//0111 0111 1��1��
				case 0x7b: skey = '8'; break;	//0111 1011 1��2��
				case 0x7d: skey = '9'; break;	//0111 1101 1��3��
				case 0x7e: skey = '/'; break;	//0111 1110 1��4��
				default:   skey = '#';			  //û�а�������
			}
			while((P2 & 0x0f) != 0x0f) //�ȴ������ɿ�
				;
			LED = 1;			//Ϩ��LED
			BUZZER = 1;		//��������
		}
	}
//ɨ����̵�2��
	P2 = 0xbf;			  //��2��Ϊ0
	if((P2 & 0x0f) != 0x0f)
	{
		delay(3);
		if((P2 & 0x0f) != 0x0f)
		{
			LED = 0;				//����LED
			BUZZER = 0;			//��������
			switch(P2)
			{
				case 0xb7: skey = '4'; break;	//1011 0111 2��1��
				case 0xbb: skey = '5'; break;	//1011 1011 2��2��
				case 0xbd: skey = '6'; break;	//1011 1101 2��3��
				case 0xbe: skey = '*'; break;	//1011 1110 2��4��
				default:   skey = '#';			  //û�а�������
			}
			while((P2 & 0x0f) != 0x0f) //�ȴ������ɿ�
				;
			LED = 1;			//Ϩ��LED
			BUZZER = 1;		//��������
		}
	}
//ɨ����̵�3��
	P2 = 0xdf;				//��3��Ϊ0
	if((P2 & 0x0f) != 0x0f)
	{
		delay(3);
		if((P2 & 0x0f) != 0x0f)
		{
			LED = 0;				//����LED
			BUZZER = 0;			//��������
			switch(P2)
			{
				case 0xd7: skey = '1'; break;	//1101 0111 3��1��
				case 0xdb: skey = '2'; break;	//1101 1011 3��2��
				case 0xdd: skey = '3'; break;	//1101 1101 3��3��
				case 0xde: skey = '-'; break;	//1101 1110 3��4��
				default:   skey = '#';			  //û�а�������
			}
			while((P2 & 0x0f) != 0x0f) //�ȴ������ɿ�
				;
			LED = 1;			//Ϩ��LED
			BUZZER = 1;		//��������
		}
	}
//ɨ�����4��
	P2 = 0xef;				//��4��Ϊ0
	if((P2 & 0x0f) != 0x0f)
	{
		delay(3);
		if((P2 & 0x0f) != 0x0f)
		{
			LED = 0;				//����LED
			BUZZER = 0;			//��������
			switch(P2)
			{
				case 0xe7: skey = '@'; break;	//1110 0111 4��1��
				case 0xeb: skey = '0'; break;	//1110 1011 4��2��
				case 0xed: skey = '='; break;	//1110 1101 4��3��
				case 0xee: skey = '+'; break;	//1110 1110 4��4��
				default:   skey = '#';			  //û�а�������
			}
			while((P2 & 0x0f) != 0x0f) //�ȴ������ɿ�
				;
			LED = 1;			//Ϩ��LED
			BUZZER = 1;		//��������
		}
	}
	return skey;
}
//������������ʾ����
void cache(ulint input)
{
	uchar i;
	if(input == 0)
	{
		display_cache[0] = 0;				//�������Ϊ0����0������ʾ����
		i = 1;
	}
	else
		for(i = 0; input > 0; i++)
		{
			display_cache[i] = input % 10;	//ȡ����������λ��������ʾ����
			input = input / 10;				//������������λ
		}
	for( ; i < 8; i++)
		display_cache[i] = 10;			//�������������ʾλ��ȫ��״̬���뻺��
}
//��ʾ�������������λѡ��ʾ����������ܼ�138������
void smg_display(void)
{
	uchar i;
	for(i = 0; i < 8; i++)
	{
		switch(i)										//λѡ
		{
			case(0):
				LS_WEA = 1; LS_WEB = 1; LS_WEC = 1;		//ABC=000,Y7~Y0=1111 1110,��λ
			break;
			case(1):
				LS_WEA = 0; LS_WEB = 1; LS_WEC = 1;		//ABC=100,Y7~Y0=1111 1101,ʮλ
			break;
			case(2):
				LS_WEA = 1; LS_WEB = 0; LS_WEC = 1;		//ABC=010,Y7~Y0=1111 1011,��λ
			break;
			case(3):
				LS_WEA = 0; LS_WEB = 0; LS_WEC = 1;		//ABC=110,Y7~Y0=1111 0111,ǧλ
			break;
			case(4):
				LS_WEA = 1; LS_WEB = 1; LS_WEC = 0;		//ABC=001,Y7~Y0=1110 1111,��λ
			break;
			case(5):
				LS_WEA = 0; LS_WEB = 1; LS_WEC = 0;		//ABC=101,Y7~Y0=1101 1111,ʮ��λ
			break;
			case(6):
				LS_WEA = 1; LS_WEB = 0; LS_WEC = 0;	  //ABC=011,Y7~Y0=1011 1111,����λ
			break;
			case(7):
				LS_WEA = 0; LS_WEB = 0; LS_WEC = 0;		//ABC=111,Y7~Y0=0111 1111,ǧ��λ
			break;
		}
		P3=display[display_cache[i]];	//��ʾ����������ʾ
		delay(3);										  //��ʱ
		P3 = 0x00;										//����
	}
}