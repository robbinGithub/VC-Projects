#ifndef __GOBALS_H__
#define __GOBALS_H__

typedef struct _TRAFFIC_ENTRY_
{
	double value;
	BOOL connected;
} TRAFFICENTRY;

//����ͼ�еľ��ο��
#define PLOTGRANULATRITY 2		

//���ݶ�ʱ���ĸ�������
#define NETUPDATESPEED	1000	
//�����������
#define GRIDUPDATESPEED 50		

//����ʱ����ID
#define GRIDTIMER		1		
//���ݶ�ʱ����ID
#define NETTIMER		2		

//��x������������	
#define GRIDXRESOLUTION	10		
//��y������������
#define GRIDYRESOLUTION	10		

//��x���������������Ĺ����ٶ�
#define GRIDSCROLLXSPEED -1		
//��y���������������Ĺ����ٶ�
#define GRIDSCROLLYSPEED 0		

#endif