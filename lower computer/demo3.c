#include "C8051F020.h"
#include "absacc.h"
#include "data_define_demo3.c"
#include "Init_Device.c"

void  delay(void)									//��ʱ����
{
  uint  i;												//����ѭ�����Ʊ���
  for(i=0;i<TIMER;i++) i=i ; 			//�ղ���ѭ���ȴ�
}

void  INIT(void)									//��ʼ������
{ 
  Init_Device();									//�����豸���ú��� 
  DPH = 0xFF;											//���ʮλ�����ʾ 
  DPL = 0xFF;											//�����λ�����ʾ 
  DPZ = 0xFF;											//���С��λ�����ʾ
	DPN = 0xFF;											//���δ��λ�����ʾ 
}


uchar ADCacc(void)								//���ݲɼ�����
{
  uchar  x;												//���������Ž��
  ADC = 0;												//����A/Dת��
  delay();												//������ʱ�����ȴ�ת������
  x = ADC;												//��ȡA/Dת�����
  return x;												//�����¶����ݲɼ����
}

uint  Temperature(uchar x)				//�¶ȼ��㺯��
{
  long int  y;										//���������ż�����
	y=x;
  y = y*1000/255;									//��������10�����¶���ֵ
	if(y>999) y=999;
  return y;												//��������10�����¶���ֵ
}

void display(uint x)							//�¶���ʾ����
{
  uchar  y;												//���������ż�����
  y = x/100;											//��ȡ�¶���ֵ��λ
  DPH = table2[y]; 	 							//�¶���ֵ��λ��DPH
  y = (x/10)%10;									//��ȡ�¶���ֵʮλ
  y = table3[y]&0xFB;							//DPL��������С����
  DPL = y;												//�¶���ֵʮλ��DPL
  y = x%10;												//��ȡ�¶���ֵ��λ
  DPZ = table4[y];								//�¶���ֵ��λ��DPZ
}

void main(void)
{ 
  uchar  a;
  uint   b;
  INIT();													//�豸��ʼ��
  while(1)												//��ѭ��
  {
    a = ADCacc();									//�¶����ݲɼ�
    b = Temperature(a);						//�¶���ֵ����
    display(b);	  								//�¶���ֵ��ʾ
    for(a=0;a<20;a++) delay;			//�ȴ�0.5��
  }
}