#pragma once
#include"pigsty.h"
#include<iostream>
using namespace std;
extern double TotMoney;
extern int MonthCount;
extern int DayCount;
extern int sell_Times_Count;
extern int allPigsNum;
void RequireSell();//��ȡ��Ȧ��Ϣ 
void saveInfo();  //��������������������·� 

//����������ȥ����Ϣ 
void save_SoldInfo(int outpignum, double sellprice, int bpig, int lpig, int wpig,double money);
//�������������� 
void buyPigs(int bpig, int lpig, int wpig, PigSty pjuan[]);
//�������У�����Ʒ�ֲ������� 
void StartfromLast(PigSty pjuan[]);
//��ʼ����Ȧ 
void StartNew(PigSty pjuan[]);
//�ѳ�����������ļ����� 
void savefile(PigSty pjuan[]);
//��ʼ�� 
void Menu_initial();
//���100����Ȧ������ 
int getAllPigs(PigSty pjuan[]);
//�������
void statistic(PigSty pjuan[]);
//
void RequireOneSty(PigSty Stys[]);
//
void RequireOnePig(PigSty Stys[]);

int NotallDead(PigSty* Stys);

int epd(PigSty* Stys,int i,int j);

void RequireAllPigs(PigSty*Stys);

void isolate(PigSty* Stys,int i,int j);

void OutPigs(PigSty* Stys);

