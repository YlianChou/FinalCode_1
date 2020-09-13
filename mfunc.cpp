#include"mfunc.h"
#include"printFunc.h"
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
//��ȡ��Ȧ��Ϣ 
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
		cout << "�޼�¼" << endl;
		return;
	}
	int times, outpigs, bpig, lpig, wpig;
	double sellprice, money;
	while (read>>times) {
		if (read.eof()) break;
		read >> outpigs >> sellprice >> bpig >> lpig >> wpig>>money;
		cout << "��" << times / 4 + 1 << "��";
		cout << "��" << (times % 4 + 1) << "�γ�Ȧ��\n";
		cout << "     ��Ȧ������" << outpigs << "     ������棺��" << sellprice << endl;
		cout << "     �������������" << endl;
		cout << "                  ������:     " << setw(5)<<bpig << endl;
		cout << "                  С��������  " <<setw(5)<<lpig << endl;
		cout << "                  ��׻�������" << setw(5)<<wpig<< endl;
		cout<< "      ����" << money << endl;
		cout << "-----------------------------------------------------------\n";
	}
	read.close();
}
//������ 
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
//�������������� 
void buyPigs(int bpig, int lpig, int wpig, PigSty pigStys[]) {
	//С�ڻ��Ƿ���С��Ȧ �� 
	int average = allPigsNum / 100 + 1;
	while (bpig--) {
		for (int i = 0; i < 100; i++) {
			if (pigStys[i].isAllBlack() == 1 && pigStys[i].getTot() <=average) {
				pigStys[i].insert(1);
				break;
			}
			if (pigStys[i].getHead() == NULL) {
				pigStys[i].insert(1);
				pigStys[i].setisBlackSty(1);
				break;
			}
		}
	}
	//ƽ������	
	while (1) {
		for (int i = 0; i < 100; i++) {
			if (pigStys[i].isAllBlack() == 0) {
				if (lpig > 0 && pigStys[i].getTot() <= average) {
					pigStys[i].insert(2);
					lpig--;
				}
				if (wpig > 0 && pigStys[i].getTot() <= average) {
					pigStys[i].insert(3);
					wpig--;
				}
			}
		}
		if (lpig == 0 && wpig == 0)break;
	}
}

void StartfromLast(PigSty Stys[]) {
	ifstream getinfo;
	getinfo.open("Info.txt");   
	getinfo >> allPigsNum >> TotMoney >> MonthCount >> DayCount >> sell_Times_Count;
	getinfo.close();
	ifstream read; 
	read.open("isFirstGame.txt");
	if (!read) {
		cout << "��ȡ���������ʧ�ܣ�";
		exit(0);
	}
	int t, cntnum;
	pig* p;
	read >> t;
	for (int i = 0; i < 100; i++) {
		read >> cntnum;  //��ȡÿ����Ȧ����  
		for (int j = 0; j < cntnum; j++) {
			p = new pig;
			p->number = j;     //ÿͷ���� 
			read >> p->species;   //����Ʒ�� 
			if (p->species == '$') {     //�������$���˳� 
				delete p;
				break;
			}
			else read >> p->weight >> p->breedMon >> p->breedDay;  //���� ���أ��·ݣ����� 
			Stys[i].addOnePig(p);  //������ӵ����� 
		}
	}
	read.close();
}
//��ʼ����Ȧ 
void StartNew(PigSty Stys[]) {
	allPigsNum = 1000;
	TotMoney = 300000;
	MonthCount = 0;
	DayCount = 0;
	sell_Times_Count = 0;
	ofstream f;
	f.open("isFirstGame.txt");//�ļ� 
	f << 0; //���ļ�����д��0 ��д��ʱ����Ҫ����ļ�һ�����ڣ������ھ���Ŀ¼�����Զ�����һ�� 
	f.close(); //�ر��ļ� 
	f.open("Eachsale.txt"); //�� 
	f << '#'; //д��# 
	f.close(); //�ر��ļ� 
	pig* p;
	int count = 1000;       //�����ʼ����1000ͷ�� 
	while (count--) {
		p = new pig;
		p->species = rand() % 3 + 1;  //�����ʼ��Ʒ�� 
		p->weight = double(rand() % 31 + 20);  //�����ʼ������ 
		p->breedMon = 0;
		p->breedDay = 0;
		p->isDead = 0;
		int i = rand() % 100;
		if (p->species == 1 && (Stys[i].isAllBlack() == 1 || Stys[i].getHead() == NULL) && Stys[i].getTot() < 10) {
			p->number = Stys[i].getTot();
			Stys[i].addOnePig(p);  //���������Ȧ 
			Stys[i].setisBlackSty(1);  //������Ϊ��Ȧ 
			continue;
		}
		//������� С�ڣ��������Ȧȫ�ǻ���    ��û���� 
		else if (p->species != 1 && Stys[i].isAllBlack() == 0 && Stys[i].getTot() < 10) {//<10???
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

//�ѳ�����������ļ����� 
void savefile(PigSty pigStys[]) {
	ofstream savefile;
	savefile.open("isFirstGame.txt");
	if (!savefile) {
		cout << "���ļ�ʧ�ܣ�";
		exit(0);
	}
	savefile << 1 << endl;//���ļ�����д��1 
	for (int i = 0; i < 100; i++) {
		pigStys[i].save(savefile);
	}
	savefile.close();
}


//���100����Ȧ������ 
int getAllPigs(PigSty pigStys[]) {
	int allPigs = 0;
	for (int i = 0; i < 100; i++) {
		allPigs += pigStys[i].getTot();
	}
	return allPigs;
}

void statistic(PigSty pigStys[])
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
void RequireOneSty(PigSty Stys[])
{
	int styNum;
	cout << "��������Ҫ��ѯ����Ȧ��ţ�";
	cin >> styNum;
	while (1)
	{
		if (styNum >= 0 && styNum < 100) break;
		else
		{
			cout << "�����������������룺 ";
			cin >> styNum;
		}
	}
	cout << "------------------------------------------------------------------" << endl;
	cout << "����Ȧ��������     " << "��������           " << "С��������         " << "��׻�������       " << endl;
	cout << ' ' << left << setw(20) << Stys[styNum].getTot() << left << setw(20) << Stys[styNum].get_BlackNum() << left << setw(20) << Stys[styNum].get_SflowerNum() << left << setw(20) << Stys[styNum].get_BflowerNum() << "\n\n";
	cout << "------------------------------------------------------------------" << endl;
}
void RequireOnePig(PigSty Stys[])
{
	int styNum, pigNum;
	cout << "��������Ȧ�ţ�";
	cin >> styNum;
	while (1) {
		if (styNum >= 0 && styNum < 100)
		{
			if (Stys[styNum].getTot() != 0) break;
			else
			{
				cout << "����ȦΪ����Ȧ�����������룺";
				cin >> styNum;
			}
		}
		else { cout << "����������������룺"; cin >> styNum; }
	}
	cout << "����Ȧ����" << Stys[styNum].getTot() << "ͷ�� , �������ѯ��� �� ";
	cin >> pigNum;
	while (1) {

		if (Stys[styNum].havePig(pigNum)) 
			break;
		else
		{
			if (pigNum < 0 || pigNum>9)
				cout << "����������������룺";
			else
				cout << "�����ڱ��Ϊ"<<pigNum<<"��������������" << endl;
			cin >> pigNum;
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
	cout << "-----------------------------------------------------" << endl;
	cout << "���γ�Ȧ���� " << outpignum << "ͷ    �ܼ�:" << sellprice << "Ԫ\n";
	cout << "-----------------------------------------------------" << endl;
	TotMoney += sellprice;
	int blackpig = 0, empSty = 0, FlowerPigCnt = 0;
	for (int i = 0; i < 100; i++) {
		if (Stys[i].getTot() == 0) { empSty++; continue; }
		if (Stys[i].get_BlackNum())   blackpig += 10 - Stys[i].get_BlackNum();
		else FlowerPigCnt += 10 - Stys[i].getTot();
	}
	int bpig, lpig, wpig;
	printBuyPrice();
	cout << "���������뱾�ι���ĺ���С�����󻨰�������";
	cin >> bpig >> lpig >> wpig;
	//tmp����δ���ĺ���Ȧ�������˿���Ȧ��ʣ�����Ȧ��װ�Ļ�������
	int tmp = (empSty - (bpig - blackpig) / 10) * 10;
	while (1) {
		if (bpig > blackpig + empSty * 10 || lpig > empSty * 10 + FlowerPigCnt || wpig > empSty * 10 + FlowerPigCnt || lpig + wpig > empSty * 10 + FlowerPigCnt)
			cout << "���������������������������룺\n";
		else if (TotMoney < (1500 * bpig + 1300 * lpig + 1000 * wpig))
			cout << "���㣬����������\n";
		else if ((tmp < lpig + wpig) && bpig > blackpig)
			cout << "������ϲ������������������ܻ��������������룺\n";
		else if (TotMoney >= 5000000) {
			cout << "������������������ϲ��ͨ������׬�����������������������" << endl;
			exit(0);
		}
		else break;
		cin >> bpig >> lpig >> wpig;
	}
	TotMoney -= (1500 * bpig + 1300 * lpig + 1000 * wpig);
	allPigsNum += bpig + lpig + wpig;
	buyPigs(bpig, lpig, wpig, Stys);
	cout << "����ɹ������������������� " << allPigsNum << endl;
	save_SoldInfo(outpignum, sellprice, bpig, lpig, wpig, TotMoney);
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
