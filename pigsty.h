#pragma once
#include<iostream>
using namespace std;
struct pig {
	int species;
	int breedDay;
	int breedMon;
	double weight;
	int number;
	int isDead;
	pig* next;
};
//��Ȧ�� 
class PigSty {
private:
	int thisSty_tot;
	pig* head;
	int isBlack;
	int state;
public:
	PigSty();
	void print();  //��ӡ 
	void addOnePig(pig* p); //����� 
	void searchpig(int number); //����һ����Ȧ���ĳֻ�� 
	void sellpig();
	void insert(int species);
	double getPrice();   //��ü۸�

	int getSpecies(int i);
	int getBreedMon(int i);
	int getBreedDay(int i);

	double getWeight(int i);

	void clearStys();
	//   int getallpig(pigjuan pjuan[]);
	void setisBlackPig(int i);
	//��ȡС������ 
	int get_BlackNum();
	//��ȡС������ 
	int get_SflowerNum();
	//��ȡ������ 
	int get_BflowerNum();
	//��ȡ������ 
	int getTot();
	//�ж��Ƿ�ΪС�� 
	int isBlackPig();
	void save(ofstream& savefile);
	//��ȡ��Ȧͷָ��               
	pig* getHead();
	//ˢ�µڶ������� 
	void next(int nexttime);
	//���Ҹø���Ȧĳ���ط���û���� 
	bool havePig(int number);
	// 
	int getState(); 
	void setisDead(int num);
	void Pro50();
	void Pro15();
	void setState();
	void deleteOne(int j);
};

