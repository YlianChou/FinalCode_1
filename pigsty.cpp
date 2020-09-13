#include<iostream>
#include<fstream>
#include"pigsty.h"
#include<time.h>
#include<iomanip>
using namespace std;
//����
PigSty::PigSty() {
	thisSty_tot = 0;
	isBlack = 0;
	state = 0;
	head = NULL;
}
int PigSty::get_BlackNum() {
	int count = 0;
	for (int i = 0; i < thisSty_tot; i++) {
		if (getSpecies(i) == 1)
			count++;
	}
	return count;
}
int PigSty::get_SflowerNum() {
	int count = 0;
	for (int i = 0; i < thisSty_tot; i++) {
		if (getSpecies(i) == 2)
			count++;
	}
	return count;
}
int PigSty::get_BflowerNum() {
	int count = 0;
	for (int i = 0; i < thisSty_tot; i++) {
		if (getSpecies(i) == 3)
			count++;
	}
	return count;
}
int PigSty::getTot() {
	return thisSty_tot;
}
int PigSty::isAllBlack() {
	return isBlack;
}          
pig* PigSty::getHead() {
	return head;
}
void PigSty::addOnePig(pig* p) {
	thisSty_tot++;
	p->next = NULL;
	if (head == NULL) {
		head = p;
	}
	else {
		pig* p1 = head;
		while (p1->next) {
			p1 = p1->next;
		}
		p1->next = p;
	}
}
int PigSty::getSpecies(int i) {
	pig* p = head;


	for (int j = 0; j < i && p; j++) {
		if (p->number == i) break;////�Ķ�1,����Ҳ��
		p = p->next;
	}
	return p->species;
}
double PigSty::getWeight(int i) {
	pig* p = head;
	for (int j = 0; j < i && p; j++) {
		if (p->number == i) break;
		p = p->next;
	}
	return p->weight;
}
int PigSty::getBreedMon(int i) {
	pig* p = head;
	for (int j = 0; j < i && p; j++) {
		if (p->number == i) break;
		p = p->next;
	}
	return p->breedMon;
}
int PigSty::getBreedDay(int i) {
	pig* p = head;
	for (int j = 0; j < i && p; j++) {
		if (p->number == i) break;
		p = p->next;
	}
	return p->breedDay;
}
////////////////////////////////////////////////
//double PigSty::getPrice() {
//	double sellprice = 0;
//	if (head == NULL)
//		return 0;
//	pig* p = head;
//	pig* p1 = p;
//	while (p) {
//		int bmon = p->breedMon;
//		int bday = p->breedDay;
//		if (bday >= 30) {
//			bday -= 30;
//			bmon++;
//		}
//		if (bmon >= 12 || p->weight > 75) {
//			if (p->species == 1) {
//				sellprice += 30 * p->weight;
//			}
//			if (p->species == 2) {
//				sellprice += 14 * p->weight;
//			}
//			if (p->species == 3) {
//				sellprice += 12 * p->weight;
//			}
//			if (p == head) {
//				if (thisSty_tot == 1) {
//					thisSty_tot--;
//					head = NULL;
//					delete p;
//                    setisBlackPig(0);
//					return sellprice;
//				}
//				else {
//					head = p->next;
//					p1 = head;
//					thisSty_tot--;
//					delete p;
//					p = head;
//				}
//			}
//			else {
//				p1->next = p->next;
//				delete p;
//				thisSty_tot--;
//			}
//		}
//		else p1 = p;
//		p = p1->next;
//	}
//	return sellprice;
//}
////////////////////////////////////////////////////////////////////////////////
double PigSty::getPrice() {
	double sellprice = 0;
	if (head == NULL)
		return 0;
	int month, day, flag = 0;
	pig* p = head, * p1 = p;
	//����ѭ���ж�ÿͷ�� 
	while (p) {
		month = p->breedMon;
		day = p->breedDay;
		while (day >= 30) {
			day -= 30;
			month++;
		}
		//�·ݴ���12���������ش���75kg 
		if (month >= 12 || p->weight > 75) {
			if (thisSty_tot == 1) {
				setisBlackPig(0);
				head = NULL;
				delete p;
				thisSty_tot--;
				break;
			}
			//������ֻʣһͷ����Ҫ����������ͷ�ָ�룬Ҫ����
			if (p->species == 1) {
				sellprice += 30 * p->weight;
			}
			if (p->species == 2) {
				sellprice += 14 * p->weight;
			}
			if (p->species == 3) {
				sellprice += 12 * p->weight;
			}
			p1->next = p->next;
			delete p;
			p = p1->next;
			thisSty_tot--;
			continue;
		}
		else if (flag == 0) {
			flag = 1;
			head = p;
		}
		p1 = p;
		p = p1->next;
	}
	return sellprice;  //��øø���Ȧ�����ܼ� 
}
//����������ļ� 
void PigSty::save(ofstream& savefile) {

	if (head == NULL) {
		savefile << '$' << endl;
		return;
	}
	else {
		pig* p = head;
		int i = 0;
		savefile << thisSty_tot << endl;//���ļ�д��ø���Ȧ���� ������ 
		while (p) {
			savefile << getSpecies(i) << "   " << getWeight(i) << "   " << getBreedMon(i) << "   " << getBreedDay(i) << endl;
			//�������ļ�д��Ʒ�֣����أ��·ݣ����� 
			i++;
			p = p->next;
		}
	}
}
//��ѯ�ø���Ȧ����Ϣ 
void PigSty::print() {
	if (thisSty_tot == 0) {
		cout << "    ���ԣ�����Ȧ " << endl;
		return;
	}
	if (isBlack == 1) {
		cout << "    ���ԣ�����Ȧ " <<"������ "<< thisSty_tot<<" ͷ"<<endl;
	}
	else
		cout << "    ���ԣ�����Ȧ " << "������ " << thisSty_tot << " ͷ"<< endl;
	pig* p = head;
	while (p) {
		int month = p->breedMon;
		int day = p->breedDay;
		while (day >= 30) {
			day -= 30;
			month++;
		}
		int i = p->number;
		cout <<"    "<< i << "����";
		if (p->species == 1)cout << "����     ";
		if (p->species == 2)cout << "С����   ";
		if (p->species == 3)cout << "��׻��� ";
		cout<<"����:"<<setw(5)<< p->weight << "Kg  ";
		cout << "����ʱ��:  " << month << "��" << day << "��" << endl;
		p = p->next;
	}
}
//ˢ�µڶ������� 
void PigSty::next(int nexttime) {
	//srand((unsigned)time(NULL));
	pig* p = head;
	while (p) {
		p->weight += (double)(rand() % 12) * nexttime / 10;
		if (nexttime == 1)	p->breedDay++;
		else p->breedMon++;
		p = p->next;  //���� 
	}
}

//���Ҹø���Ȧĳ���ط���û���� 
bool PigSty::havePig(int number) {
	pig* p = head;
	while (p) {
		if (p->number == number)
			return true;
		else
			p = p->next;
	}
	return false;
}

//��Ȧȫ�����
void PigSty::clearStys() {
	if (head == NULL) {
		return;
	}
	else {
		pig* p = head;
		pig* p1 = p;
		thisSty_tot = 0;
		setisBlackPig(0);
		head = NULL;
		while (p) {
			p1 = p;
			p = p->next;
			delete p1;
		}
		delete p;
	}
}
//�������У�����Ʒ�ֲ������� 
void PigSty::insert(int species) {
	pig* p = new pig;
	p->species = species;
	p->weight = double(rand() % 30 + 20);
	p->breedMon = 0;
	p->breedDay = 0;
	//��Ȧ
	if (head == NULL) {
		p->number = 0;
		p->next = NULL;
		head = p;
		thisSty_tot++;
		return;
	}
	//�ʼ��λ��û�з�
	if (head->number != 0) {
		p->number = 0;
		p->next = head;
		head = p;
		thisSty_tot++;
		return;
	}
	else {
		pig* p1 = head, * p2 = p1;
		int k = 0;
		while (p1->number == k && p1->next) {
			k++;
			p2 = p1;
			p1 = p1->next;
		}
		if (p1->next == NULL&&(thisSty_tot>p1->number)) {
			p->number = thisSty_tot;
			p->next = NULL;
			p1->next = p;
		}
		else {
			p->number = k;
			p2->next = p;
			p->next = p1;
		}
		thisSty_tot++;
	}
}
void PigSty::setisBlackPig(int i) {
	isBlack = i;
}

