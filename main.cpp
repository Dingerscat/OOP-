#pragma once
#include<iostream>
using namespace std;
#include"BookManager.h"				//图书管理
#include"ReaderManager.h"			//借书人管理
#include"Borrower_relationship.h"		//借阅关系管理
#include"GlobalFile.h"		//全局文件

void B_M(BookManager& bm) {

	system("cls");
	switch (bm.show_menu()) {
	case 1:
		bm.newbook_add();

		break;
	case 2:
		bm.print_book();

		break;
	case 3:
		bm.delete_book();

		break;
	case 4:
		bm.query();

		break;


	}
}

void R_M(ReaderManager& rm) {
	system("cls");
	switch (rm.show_menu()) {
	case 1:
		rm.Borrower_registe();

		break;
	case 2:
		rm.print_borrower();

		break;
	case 3:
		rm.Borrower_delete();

		break;
	case 4:
		rm.query();

		break;
	case 5:
		rm.Borrower_update();

		break;

	}
}

void B_R(Borrower_relationship& br, BookManager& bm, ReaderManager& rm) {
	system("cls");

	switch (br.show_menu()) {
	case 1:


		if (br.assign(rm)) {	//通过rm对象使用其vector<Borrower> Vborrower查看txt文件中是否有会员信息
			cout << "该人为会员!" << endl;
		}
		else {
			cout << "该人非会员!" << endl;
		}

		break;
	case 2:

		br.to_borrow(rm, bm);

		break;
	case 3:

		br.return_book(rm, bm);

		break;
	case 4:

		br.print_relation();

		break;

	}
}

int main() {
	int choice;
	BookManager bm;
	ReaderManager rm;
	Borrower_relationship br;

	while (true) {
		cout << "\t\t|--------------------------------------------------" << endl;
		cout << "\t\t|				【欢迎来到图书信息管理系统】				" << endl;
		cout << "\t\t|				1:图书管理							" << endl;
		cout << "\t\t|				2:读者管理							" << endl;
		cout << "\t\t|				3:借阅关系管理						" << endl;
		cout << "\t\t|				0:退出系统							" << endl;


		cout << "请输入你的选择：";
		cin >> choice;					//接受用户的选择 

		switch (choice) {					//根据用户不同选择，实现不同的接口 
		case 1:		//图书管理 
			B_M(bm);
			break;
		case 2:		//读者管理 
			R_M(rm);
			break;
		case 3:		//借阅关系管理 
			B_R(br, bm, rm);
			break;
		case 0:		//退出系统 
			cout << "------欢迎下一次的使用！-----" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "您的输入有误，请重新输入!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}
