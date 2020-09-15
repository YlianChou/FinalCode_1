#include"mfunc.h"
#include"printFunc.h"
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<iomanip>
//#include<string.h>
using namespace std;
void RequireSell() {
	ifstream read;
	read.open("Eachsale.txt");
	if (!read) {
		cout << "���ļ�ʧ��";
		exit(0);
	}
	char flag;
	read >> flag;
	if (flag == '#') {
		cout << "���޳�Ȧ��¼" << endl;
		return;
	}
	int times, outpigs, Bpig, SFpig, BFpig;
	double sellprice, money;
	while (read>>times) {
		if (read.eof()) break;
		read >> outpigs >> sellprice >> Bpig >> SFpig >> BFpig>>money;
		cout << "��" << times / 4 + 1 << "��";
		cout << "��" << (times % 4 + 1) << "�γ�Ȧ��\n";
		cout << "     ��Ȧ������" << outpigs << "     ������棺��" << sellprice << endl;
		cout << "     �������������" << endl;
		cout << "                  ������:     " << setw(5)<<Bpig << endl;
		cout << "                  С��������  " <<setw(5)<<SFpig << endl;
		cout << "                  ��׻�������" << setw(5)<<BFpig<< endl;
		cout<< "      ����" << money << endl;
		cout << "-----------------------------------------------------------\n";
	}
	read.close();
}
 
void saveInfo() {
	ofstream save;
	save.open("Info.txt");
	if (!save) {
		cout << "���ļ�ʧ�ܣ�"; exit(0);
	}
	else {
		save << allPigsNum << "   " << TotMoney << "   " << MonthCount << "   " << DayCount << "   " << sell_Times_Count << endl;
		cout << "������Ϸ����ɹ����˳���Ϸ�밴0��������Ϸ�밴1��" << endl;
		save.close();
	}
}
//����������ȥ����Ϣ 
void save_SoldInfo(int outpignum, double sellprice, int bpig, int lpig, int wpig,double money) {
	ifstream testin;
	testin.open("Eachsale.txt");
	char flag;
	testin >> flag;
	if (flag == '#') {
		testin.close();
		ofstream testout;
		testout.open("Eachsale.txt");
		testout << '$';
		testout.close();
	}
	else testin.close();
	ofstream save("Eachsale.txt", ios::app);
	save << sell_Times_Count << endl;
	save << outpignum << "   " << sellprice << "    " << bpig << "   " << lpig << "   " << wpig <<"  "<<money << endl;
	save.close();
}
//
bool is_all_BstyFull(PigSty* stys) {
	int bj = 0; int cnt = 0;
	for (int i = 0; i < 100; i++) {
		if (stys[i].isAllBlack() == 1) bj++;
	}
	for (int i = 0; i < 100; i++) {
		if (stys[i].isAllBlack() && stys[i].get_BlackNum()== 10)
			cnt++;
	}
	if (cnt == bj) return 1;
	else return 0;
}

void StartfromLast(PigSty*Stys) {
	ifstream getinfo;
	getinfo.open("Info.txt");   
	getinfo >> allPigsNum >> TotMoney >> MonthCount >> DayCount >> sell_Times_Count;
	getinfo.close();
	ifstream read; 
	read.open("isFirstGame.txt");
	if (!read) {
		cout << "��ȡ����ʧ�ܣ�";
		exit(0);
	}
	int t, cntnum;
	pig* p;
	read >> t;
	for (int i = 0; i < 100; i++) {
		read >> cntnum;  
		for (int j = 0; j < cntnum; j++) {
			p = new pig;
			p->number = j;     
			read >> p->species;   
			if (p->species == '$') {     
				delete p;
				break;
			}
			else read >> p->weight >> p->breedMon >> p->breedDay; 
			Stys[i].addOnePig(p);  
		}
	}
	read.close();
}
//��ʼ����Ȧ 
void StartNew(PigSty* Stys) {
	allPigsNum = 1000;
	TotMoney = 500000;
	MonthCount = 0;
	DayCount = 0;
	sell_Times_Count = 0;
	ofstream f;
	f.open("isFirstGame.txt");//�ļ� 
	f << 0; 
	f.close(); 
	f.open("Eachsale.txt"); //�� 
	f << '#'; 
	f.close(); 
	pig* p;
	int count = 1000;       //�����ʼ����1000ͷ�� 
	while (count--) {
		p = new pig;
		p->species = rand() % 3 + 1;  //�����ʼ��
		p->weight = double(rand() % 31 + 20);  
		p->breedMon = 0;
		p->breedDay = 0;
		p->isDead = 0;
		int i = rand() % 100;
		if (p->species == 1 && (Stys[i].isAllBlack() == 1 || Stys[i].getHead() == NULL) && Stys[i].getTot() < 10) {
			p->number = Stys[i].getTot();
			Stys[i].addOnePig(p);  
			Stys[i].setisBlackSty(1);  
			continue;
		}
		else if (p->species != 1 && Stys[i].isAllBlack() == 0 && Stys[i].getTot() < 10) {
			p->number = Stys[i].getTot();
			Stys[i].addOnePig(p);   
			continue;
		}
		else count++;
		delete p;
	}
	for (int i = 0; i < 100; i++)
		Stys[i].setState();
}
void savefile(PigSty*pigStys) {
	ofstream savefile;
	savefile.open("isFirstGame.txt");
	if (!savefile) {
		cout << "���ļ�ʧ�ܣ�";
		exit(0);
	}
	savefile << 1 << endl;
	for (int i = 0; i < 100; i++) {
		pigStys[i].save(savefile);
	}
	savefile.close();
} 
int getAllPigs(PigSty* pigStys) {
	int allPigs = 0;
	for (int i = 0; i < 100; i++) {
		allPigs += pigStys[i].getTot();
	}
	return allPigs;
}
void statistic(PigSty* pigStys)
{
	int blackTot = 0; double Bget150 = 0; int Blt30 = 0; int Bm3_6 = 0; int Bm7_12 = 0;
	int sflowerTot = 0; double SFget150 = 0;  int SFlt30 = 0; int SFm3_6 = 0; int SFm7_12 = 0;
	int bflowerTot = 0;  double BFget150 = 0; int BFlt30 = 0; int BFm3_6 = 0; int BFm7_12 = 0;
	for (int i = 0; i < 100; i++)
	{
		pig* p = pigStys[i].getHead();
		while (p)
		{
			if (p->species == 1)
			{
				blackTot++;
				if (p->weight >= 150)	Bget150++;  //���ش���150 
				if (p->breedDay < 30)   Blt30++;    //����ʱ��С��1���� 
				if (p->breedMon >= 3 && p->breedMon < 7) Bm3_6++;  //����ʱ��3-6���� 
				if (p->breedMon >= 7) Bm7_12++;	  //����ʱ����ڰ��� 
			}
			else if (p->species == 2)
			{
				sflowerTot++;
				if (p->weight >= 150)	SFget150++;  //���ش���150 
				if (p->breedDay < 30)   SFlt30++;    //����ʱ��С��1���� 
				if (p->breedMon >= 3 && p->breedMon < 7) SFm3_6++;  //����ʱ��3-6���� 
				if (p->breedMon >= 7) SFm7_12++;	  //����ʱ����ڰ��� 

			}
			else if (p->species == 3)
			{
				bflowerTot++;
				if (p->weight >= 150)	BFget150++;  //���ش���150 
				if (p->breedDay < 30)   BFlt30++;    //����ʱ��С��1���� 
				if (p->breedMon >= 3 && p->breedMon < 7) BFm3_6++;  //����ʱ��3-6���� 
				if (p->breedMon >= 7) BFm7_12++;	  //����ʱ����ڰ��� 	

			}
			p = p->next;
		}
	}
	cout << "���������������ֳ������£�" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "    ������������" << blackTot + sflowerTot + bflowerTot << " ͷ" << endl;
	cout << "    ����" << endl;
	cout << "         ������    " << blackTot << " ͷ" << endl;
	cout << "         ���أ�    " << endl;
	cout << "                   " << "��150��:  " << blackTot - Bget150 << " ͷ" << endl;
	cout << "                   " << "��150� " << Bget150 << " ͷ" << endl;
	cout << "         ����ʱ��: " << endl;
	cout << "                   " << "��1���£� " << Blt30 << " ͷ" << endl;
	cout << "                   " << "3-6���£� " << Bm3_6 << " ͷ" << endl;
	cout << "                   " << "�ݰ��� :  " << Bm7_12 << " ͷ" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "    С����" << endl;
	cout << "         ������    " << sflowerTot << " ͷ" << endl;
	cout << "         ���أ�    " << endl;
	cout << "                   " << "��150��:  " << sflowerTot - SFget150 << " ͷ" << endl;
	cout << "                   " << "��150� " << SFget150 << " ͷ" << endl;
	cout << "         ����ʱ��: " << endl;
	cout << "                   " << "��1���£� " << SFlt30 << " ͷ" << endl;
	cout << "                   " << "3-6���£� " << SFm3_6 << " ͷ" << endl;
	cout << "                   " << "�ݰ��� :  " << SFm7_12 << " ͷ" << endl;
	cout << "---------------------------------------------------------" << endl;
	cout << "    �󻨰���" << endl;
	cout << "         ������    " << bflowerTot << " ͷ" << endl;
	cout << "         ���أ�    " << endl;
	cout << "                   " << "��150��:  " << bflowerTot - BFget150 << " ͷ" << endl;
	cout << "                   " << "��150� " << BFget150 << " ͷ" << endl;
	cout << "         ����ʱ��: " << endl;
	cout << "                   " << "��1���£� " << BFlt30 << " ͷ" << endl;
	cout << "                   " << "3-6���£� " << BFm3_6 << " ͷ" << endl;
	cout << "                   " << "�ݰ��� :  " << BFm7_12 << " ͷ" << endl;
	cout << "---------------------------------------------------------" << endl;
}
void RequireOneSty(PigSty*Stys)
{
	int styNum;
	cout << "��������Ҫ��ѯ����Ȧ��ţ�";
	while (1) {
		int i = rightNum();
		if (i < 1 || i>100) {
			cout << "�������������������Ȧ���" << endl;
			continue;
		}
		else {
			styNum = i; break;
		}
	}
	cout << "------------------------------------------------------------------" << endl;
	cout << "����Ȧ��������     " << "��������           " << "С��������         " << "��׻�������       " << endl;
	cout << ' ' << left << setw(20) << Stys[styNum].getTot() << left << setw(20) << Stys[styNum].get_BlackNum() << left << setw(20) << Stys[styNum].get_SflowerNum() << left << setw(20) << Stys[styNum].get_BflowerNum() << "\n\n";
	cout << "------------------------------------------------------------------" << endl;
}
void RequireOnePig(PigSty*Stys)
{
	int styNum, pigNum;
	cout << "��������Ȧ�ţ�";
	while (1) {
		int i = rightNum();
		if (i < 1 || i>100) {
			cout << "�������������������ȷ��Ȧ���" << endl;
			continue;
		}
		else {
			styNum = i; 
			if (Stys[styNum].getTot() != 0) break;
			else {
				cout << "��Ǹ������ȦΪ����Ȧ�����������룺"; continue;
			}
		}
	}
	cout << "����Ȧ����" << Stys[styNum].getTot() << "ͷ�� , �������ѯ��� �� ";
	while (1) {
		int i = rightNum();
		if (i < 1 || i>10) {
			cout << "�������������������ȷ����" << endl;
			continue;
		}
		else {
			pigNum = i;
			if (Stys[styNum].getHead() != NULL) break;
			else {
				cout << "��Ǹ������ȦΪ����Ȧ�����������룺"; continue;
			}
		}
	}
	cout <<"��ѯ�����"<< endl;
	cout << "���Ʒ��            |            ����/kg               |         ����ʱ��" << endl;
	if (Stys[styNum].getSpecies(pigNum) == 1)   cout << " ����    " << "                         ";
	if (Stys[styNum].getSpecies(pigNum) == 2)   cout << " С����  " << "                         ";
	if (Stys[styNum].getSpecies(pigNum) == 3)	cout << "��׻��� " << "                         ";
	cout << Stys[styNum].getWeight(pigNum) << "                              ";
	int month = Stys[styNum].getBreedMon(pigNum), day = Stys[styNum].getBreedDay(pigNum);
	while (day >= 30) {
		day -= 30;
		month++;
	}
	if (month > 0)cout << month << "��";
	cout << day << "��\n\n";
}
void RequireAllPigs(PigSty*Stys) {
	for (int i = 0; i < 100; i++) {
		cout << "=============================================================" << endl;
		cout << i << "��Ȧ:" << endl;
		Stys[i].print();
		if (i == 99) cout << "======================��ѯ����===============================" << endl;
	}
}
void OutPigs(PigSty* Stys) {
	double sellprice = 0;
	for (int i = 0; i < 100; i++) {
		sellprice += Stys[i].getPrice();
	}
	int temp = getAllPigs(Stys), outpignum = allPigsNum - temp;
	allPigsNum = temp;
	cout << endl;
	cout << "���γ�Ȧ���� " << outpignum << "ͷ    �ܼ�:" << sellprice << "Ԫ\n";
	TotMoney += sellprice;
	int blackpig = 0, empSty = 0, FlowerPigCnt = 0;

	for (int i = 0; i < 100; i++) {
		if (Stys[i].getHead() == NULL) { empSty++; continue; }
		else {
			if (Stys[i].get_BlackNum())   blackpig += 10 - Stys[i].get_BlackNum();
			else FlowerPigCnt += 10 - Stys[i].getTot();
		}	
	}
	int rem = empSty * 10 + FlowerPigCnt + blackpig;
	cout << "��Ȧ����Ȧ��λ��Ϣ:\n";
	cout << "              ---------------------------\n";
	cout << "              | ��Ȧ�ܿ�λ��     "<<setw(5) << rem <<"  |"<< endl;
	cout << "              | δ������Ȧ��λ�� "<<setw(5)<< blackpig << "  |" << endl;
	cout << "              | δ������Ȧ��λ:  " << setw(5) << FlowerPigCnt << "  |" << endl;
	cout << "              | ����Ȧ�ܸ�����   " <<setw(5)<< empSty << "  |" << endl;
	cout << "              ---------------------------\n";
	int Bpig, SFpig, BFpig;
	printBuyPrice();
	cout << "�밴Ʒ�����뱾�ι������������\n";
	cout << "����������";  cin.get();
	while (1) {
		while (1) {
			int i = rightNum();
			if (i < 1 || i>1000) {
				cout << "�����������������" << endl;
				continue;
			}
			else {
				Bpig = i; break;
			}
		}
		cout << "\nС����������";
		while (1) {
			int i = rightNum();
			if (i < 1 || i>1000) {
				cout << "�����������������" << endl;
				continue;
			}
			else {
				SFpig = i; break;
			}
		}
		cout << "\n�󻨰���������";
		while (1) {
			int i = rightNum();
			if (i < 1 || i>1000) {
				cout << "�����������������" << endl;
				continue;
			}
			else {
				BFpig = i; break;
			}
		}
		int tmp = empSty - (Bpig - blackpig) / 10;
		if ((Bpig - blackpig) % 10 != 0)    tmp--;
		if ((Bpig > blackpig + empSty * 10) || (SFpig > empSty * 10 + FlowerPigCnt) || (BFpig > empSty * 10 + FlowerPigCnt) || (SFpig + BFpig > empSty * 10 + FlowerPigCnt) || ((BFpig + SFpig + Bpig) > rem))
		{
			cout << "��������ָ��������Ȧ�������������������룺\n"; continue;
		}
		else if (TotMoney < (1500 * Bpig + 1300 * SFpig + 1000 * BFpig)) {
			cout << "���㣬����������\n"; continue;
		}

		else if ((tmp * 10 + FlowerPigCnt < SFpig + BFpig) || Bpig > blackpig + 10 * empSty) {
			cout << "������޷����������Ȧ�����������룺\n";
			continue;
		}
		else if (TotMoney >= 5000000) {
			cout << "������������������ϲ��ͨ������׬�����������������������" << endl;
			exit(0);
		}
		else break;
	}
	TotMoney -= (1500 * Bpig + 1300 * SFpig + 1000 * BFpig);
	allPigsNum += Bpig + SFpig + BFpig;
	buyPigs(Bpig, SFpig, BFpig, Stys);
	cout << "����ɹ������������������� " << allPigsNum << endl;
	cout << "�밴���������" << endl;
	save_SoldInfo(outpignum, sellprice, Bpig, SFpig, BFpig, TotMoney);
	sell_Times_Count++;
	while (DayCount >= 30) {
		DayCount -= 30;
		MonthCount++;
	}
	MonthCount -= 3;
	cin.get();
	cin.get();
	Menu_initial();
}
void buyPigs(int Bpig, int SFpig, int BFpig, PigSty*pigStys) {
	while (Bpig--) {
		for (int i = 0; i < 100; i++) {
			if (pigStys[i].isAllBlack() == 1 && pigStys[i].getTot() < 10) {
				pigStys[i].insert(1);
				break;
			}
			if ((is_all_BstyFull(pigStys)) && pigStys[i].getHead() == NULL) {
				pigStys[i].insert(1);
				pigStys[i].setisBlackSty(1);
				break;
			}
		}
	}
	int fl = 0; int allb = 0;
	for (int i = 0; i < 100; i++)
	{
		if (pigStys[i].getHead() == 0) fl++;
		else {
			if (pigStys[i].isAllBlack() == 0)  fl++;
			else allb += pigStys[i].get_BlackNum();
		}
	}
	int bjuan = 0;
	for (int i = 0; i < 100; i++)
		if (pigStys[i].isAllBlack() == 1)  bjuan++;
	/*cout << "������ĺ���������" << allb << endl;
	cout << "����������ĸ�����" << allPigsNum - allb << endl;
	cout << "����������Ȧ��" << fl << " " << endl;
	cout << "��������ռ�е�Ȧ" << bjuan << " " << endl;*/
	int average = (allPigsNum - allb) / fl+1 ;
	//cout << "����Ȧ������10֮ǰƽ�� " << average << endl;
	if (average > 10) average = 10;
	
	while (1) {
		for (int i = 0; i < 100; i++) {
			if (pigStys[i].isAllBlack() == 0) {
				if (SFpig > 0 && (pigStys[i].getTot() < average || pigStys[i].getHead() == NULL)) {
					pigStys[i].insert(2);
					SFpig--;
				//	cout << "С��" << SFpig << endl;
				}
				if (BFpig > 0 && (pigStys[i].getTot() < average || pigStys[i].getHead() == NULL)) {
					pigStys[i].insert(3);
					BFpig--;
				//	cout << "�󻨣�" << BFpig << endl;
				}

			}
		}
		if (SFpig == 0 && BFpig == 0)	break;
	}
}

int rightNum(){
	string str;
	/*getline(cin, str);*/
	cin >> str;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] < '0' || str[i]>'9') return -1;
	}
	int out = 0;
	for (int i = 0; i < str.size(); i++) {
		int tmp = str[i] - '0';
		out = out * 10 + tmp;
	}
	if (out < 0) return -1;
	else 
	   return out;
}
