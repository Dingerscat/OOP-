#pragma once
#include<iostream>
#include"Borrower.h"
#include<fstream>		//文件流
#include<vector>
#include<string>
using namespace std;

class ReaderManager {
public:
	//读者管理子菜单
	int show_menu();

	//为借书人办理注册。
	void Borrower_registe();

	//借书人信息浏览
	void print_borrower();

	//已有借书人信息读入功能(信息用文件保存)
	void read_f();

	//借书人信息的注销（删除）
	void Borrower_delete();

	//借书人信息修改
	void Borrower_update();

	//查询功能
	void query();

	//借书人信息保存功能
	void save();

	//去重
	bool check_repeat(int number);

	vector<Borrower> Vborrower; //存放借书人的信息

};


//读者管理子菜单
int ReaderManager::show_menu() {
	cout << endl;
	cout << "|					【读者管理子菜单】				|" << endl << endl;
	cout << "|					1:读者注册(添加读者信息到文件)(完成注册后自动读入到容器)		" << endl;
	cout << "|					2:读者信息浏览(容器中信息打印)		" << endl;
	cout << "|					3:读者信息注销(删除后自动保存到文件)	" << endl;
	cout << "|					4:读者信息查询					" << endl;
	cout << "|					5:读者信息修改(修改后自动保存到文件) " << endl;
	cout << "|					0:返回上级菜单					" << endl;

	int r_choice;
	cout << "请输入你的选择: ";
	cin >> r_choice;

	system("cls");

	return r_choice;
}

//为借书人办理注册。
void ReaderManager::Borrower_registe() {
	cout << "注册新成员！" << endl;

	ofstream ofs;

	ofs.open("Borrower.txt", ios::out | ios::app);

	if (!ofs.is_open()) {
		cout << "文件打开失败！" << endl;
	}

	string errorTip = "学号重复，请重新输入！";

	int number;
	string name;
	string sex;
	int t_number;

	cout << "请输入学号:" << endl;
	while (true)
	{
		cin >> number;
		bool ret = this->check_repeat(number);
		if (ret) {//有重复
			cout << errorTip << endl;
		}
		else {
			break;
		}
	}

	cout << "请输入姓名：" << endl;
	cin >> name;
	cout << "请输入性别：" << endl;
	cin >> sex;
	cout << "请输入可借书数量：" << endl;
	cin >> t_number;


	ofs << number << " " << name << " " << sex << " " << t_number << endl;

	cout << "写入文件成功!" << endl;
	//加载到文件后自动更新到容器
	this->read_f();

	system("pause");
	system("cls");

	ofs.close();

	return;
}

void ReaderManager::print_borrower() {

	this->read_f();
	cout << "打印信息" << endl;
	for (vector<Borrower>::iterator it = Vborrower.begin(); it != Vborrower.end(); it++) {
		cout << "借书人的学号是：" << (*it).s_number << "  姓名： " << (*it).s_name << "  性别  " << (*it).gender << "  可借书总量为  :" << (*it).total_bookborrow << endl;
	}
	system("pause");
}
//已有借书人信息读入功能(信息用文件保存)
void ReaderManager::read_f() {

	//读取文件的信息
	ifstream ifs;

	ifs.open("Borrower.txt", ios::in);

	if (!ifs.is_open()) {
		cout << "文件打开失败!" << endl;
		return;
	}

	//容器清零先
	Vborrower.clear();

	Borrower bw;

	while (ifs >> bw.s_number && ifs >> bw.s_name && ifs >> bw.gender && ifs >> bw.total_bookborrow) {
		Vborrower.push_back(bw);
	}


	ifs.close();

	cout << "借书人信息已成功读取到容器" << endl;

	return;
}

//借书人信息的注销（删除）
void ReaderManager::Borrower_delete() {
	int rm_choice;
	cout << "请输入想要删除借书人的学号：" << endl;
	cin >> rm_choice;


	for (vector<Borrower>::iterator it = Vborrower.begin(); it != Vborrower.end();) {
		if (it->s_number == rm_choice) {
			it = Vborrower.erase(it);
			cout << "删除成功！" << endl;
			this->save();	//删除后自动保存
			return;
		}
		else {
			++it;
		}
	}
	cout << "未找到此书，删除失败!" << endl;
	return;
}

//借书人信息修改
void ReaderManager::Borrower_update() {
	this->read_f();

	int update_choice;

	int update_number;
	string update_name;
	string update_sex;
	int update_bnumber;

	cout << "|     1:按照借书人学号查找并修改     |" << endl;
	cout << "|     2:按照借书人名字查找并修改     |" << endl;
	cout << "请输入你的选择：";
	cin >> update_choice;

	switch (update_choice)
	{
	case 1:

		cout << "请输入你要查找并修改借书人的学号：" << endl;
		cin >> update_number;
		for (vector<Borrower>::iterator it = Vborrower.begin(); it != Vborrower.end(); it++) {
			if (it->s_number == update_number) {
				cout << "已找到要修改的借书人!" << endl;
				cout << "学号: " << it->s_number << "    性名：   " << it->s_name << "   性别：   " << it->gender << "   总共可借书数量：   " << it->total_bookborrow << endl;


				cout << "-----1:需要修改学号-----" << endl;
				cout << "-----2:需要修改姓名-----" << endl;
				cout << "-----3:需要修改性别-----" << endl;
				cout << "-----4:需要修改可借书数量-----" << endl;
				cout << endl << "请输入你要修改的数据!" << endl;

				cin >> update_choice;
				switch (update_choice) {
				case 1:
					cout << "请输入需要修改的学号: ";
					cin >> update_number;
					it->s_number = update_number;
					cout << "修改成功，自动保存到文件!" << endl;
					this->save();
					break;
				case 2:
					cout << "请输入需要修改的姓名: ";
					cin >> update_name;
					it->s_name = update_name;
					cout << "修改成功，自动保存到文件!" << endl;
					this->save();
					break;
				case 3:
					cout << "请输入需要修改的性别: ";
					cin >> update_sex;
					it->gender = update_sex;
					cout << "修改成功，自动保存到文件!" << endl;
					this->save();
					break;
				case 4:
					cout << "请输入需要修改的借书数量: ";
					cin >> update_bnumber;
					it->total_bookborrow = update_bnumber;
					cout << "修改成功，自动保存到文件!" << endl;
					this->save();
					break;

				}
			}
		}
		break;
	case 2:
		cout << "请输入你要查找并修改借书人的姓名：" << endl;
		cin >> update_name;
		for (vector<Borrower>::iterator it = Vborrower.begin(); it != Vborrower.end(); it++) {
			if (strcmp((it->s_name).c_str(), update_name.c_str()) == 0) {
				cout << "已找到要修改的借书人!" << endl;
				cout << "学号: " << it->s_number << "    性名：   " << it->s_name << "   性别：   " << it->gender << "   总共可借书数量：   " << it->total_bookborrow << endl;


				cout << "-----1:需要修改学号-----" << endl;
				cout << "-----2:需要修改姓名-----" << endl;
				cout << "-----3:需要修改性别-----" << endl;
				cout << "-----4:需要修改可借书数量-----" << endl;
				cout << endl << "请输入你要修改的数据!" << endl;

				cin >> update_choice;
				switch (update_choice) {
				case 1:
					cout << "请输入需要修改的学号: ";
					cin >> update_number;
					it->s_number = update_number;
					cout << "修改成功，自动保存到文件!" << endl;
					this->save();
					break;
				case 2:
					cout << "请输入需要修改的姓名: ";
					cin >> update_name;
					it->s_name = update_name;
					cout << "修改成功，自动保存到文件!" << endl;
					this->save();
					break;
				case 3:
					cout << "请输入需要修改的性别: ";
					cin >> update_sex;
					it->gender = update_sex;
					cout << "修改成功，自动保存到文件!" << endl;
					this->save();
					break;
				case 4:
					cout << "请输入需要修改的借书数量: ";
					cin >> update_bnumber;
					it->total_bookborrow = update_bnumber;
					cout << "修改成功，自动保存到文件!" << endl;
					this->save();
					break;
				}
			}
		}

		break;

	}

	return;
}

//查询功能
void ReaderManager::query() {
	this->read_f();
	int r_choice;
	int r_number;
	string r_name;
	system("cls");
	cout << "|     1:按照借书人学号查询     |" << endl;
	cout << "|     2:按照借书人名字查询     |" << endl;
	cout << "请输入你的选择：";
	cin >> r_choice;
	switch (r_choice) {
	case 1:

		cout << "请输入想要查找借书人的学号:";
		cin >> r_number;

		for (vector<Borrower>::iterator it = Vborrower.begin(); it != Vborrower.end(); it++) {
			if (r_number == it->s_number) {
				cout << "借书人主要信息如下：" << endl;
				cout << "学号: " << it->s_number << "    性名：   " << it->s_name << "   性别：   " << it->gender << "   总共可借书数量：   " << it->total_bookborrow << endl;
				return;
			}

		}
		cout << "未找到该人" << endl;
		break;
	case 2:
		cout << "请输入想要查找借书人的名字:";
		cin >> r_name;
		for (vector<Borrower>::iterator it = Vborrower.begin(); it != Vborrower.end(); it++) {
			if (strcmp(r_name.c_str(), (it->s_name).c_str()) == 0) {
				cout << "借书人主要信息如下：" << endl;
				cout << "学号: " << it->s_number << "    性名：   " << it->s_name << "   性别：   " << it->gender << "   总共可借书数量：   " << it->total_bookborrow << endl;
				return;
			}
		}
		cout << "未找到该人" << endl;
		break;

	}
	return;
}

//借书人信息保存功能
void ReaderManager::save() {
	ofstream ofs;

	ofs.open("Borrower.txt", ios::out);

	if (!ofs.is_open()) {
		cout << "文件打开失败！" << endl;
	}

	for (vector<Borrower>::iterator it = Vborrower.begin(); it != Vborrower.end(); it++) {
		ofs << it->s_number << " " << it->s_name << " " << it->gender << " " << it->total_bookborrow << endl;
	}

	ofs.close();
	cout << "借书人信息已经成功保存到文件" << endl;
	return;
}

//去重
bool ReaderManager::check_repeat(int number) {

	for (vector<Borrower>::iterator it = Vborrower.begin(); it != Vborrower.end(); it++) {
		if (number == it->s_number) {
			return true;
		}
	}
	return false;
}
