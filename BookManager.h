#pragma once
#include<iostream>
#include"Book.h"
#include<fstream>		//文件流
#include<vector>
#include<string>
using namespace std;

class BookManager {
public:
	//图书管理子菜单
	int show_menu();

	//新进图书添加
	void newbook_add();

	//已有图书信息读入（从txt文件读入）
	void read_f();

	//图书信息浏览
	void print_book();

	//图书信息的删除
	void delete_book();

	//图书信息查询
	void query();

	//保存
	void save();

	//去重
	bool check_repeat(int id);

	vector<Book> Vbook;
};


// 图书管理子菜单
int BookManager::show_menu() {
	cout << endl;
	cout << "|					【图书管理子菜单】				|" << endl << endl;
	cout << "|					1:新进图书添加(添加到文件)(完成注册后自动读入到容器)				" << endl;
	cout << "|					2:图书信息浏览(容器中信息打印)		|" << endl;
	cout << "|					3:图书信息删除(删除后自动保存到文件)	|" << endl;
	cout << "|					4:图书信息查询					|" << endl;
	cout << "|					0:返回上级菜单					|" << endl;

	int b_choice;
	cout << "请输入你的选择: ";
	cin >> b_choice;

	system("cls");

	return b_choice;
}
//新进图书添加
void BookManager::newbook_add() {
	cout << "添加新的图书" << endl;

	ofstream ofs;

	ofs.open("Book.txt", ios::out | ios::app);//写文件并且追加的写入文件

	if (!ofs.is_open()) {
		cout << "文件打开失败！" << endl;
	}

	string errorTip = "ID号重复，请重新输入！";

	int fID;				//编号  
	string fb_name;		//书名 
	string fb_author;	//作者名
	int fc_num;			//分类号
	string fPublishing_unit;		//出版单位
	string fPublishing_time;		//出版时间
	double fprice;		//价格
	string fexist_state;			//存在状态 

	cout << "请输入书的编号： " << endl;

	while (true)
	{
		cin >> fID;
		bool ret = this->check_repeat(fID);
		if (ret) {//有重复
			cout << errorTip << endl;
		}
		else {
			break;
		}
	}

	cout << "请输入书名： " << endl;
	cin >> fb_name;
	cout << "请输入作者名： " << endl;
	cin >> fb_author;
	cout << "请输入书的分类号： " << endl;
	cin >> fc_num;
	cout << "请输入书的出版单位： " << endl;
	cin >> fPublishing_unit;
	cout << "请输入书的出版时间： " << endl;
	cin >> fPublishing_time;
	cout << "请输入书的价格： " << endl;
	cin >> fprice;
	cout << "请输入书的存在状态：(wait or borrowed) " << endl;
	cin >> fexist_state;

	ofs << fID << " " << fb_name << " " << fb_author << " " << fc_num << " " << fPublishing_unit << " " << fPublishing_time << " " << fprice << " " << fexist_state << endl;

	cout << "写入文件成功!" << endl;
	this->read_f();

	system("pause");
	system("cls");

	ofs.close();

	return;
}

//已有图书信息读入（读入到容器）
void BookManager::read_f() {

	//读取文件的信息
	ifstream ifs;

	ifs.open("Book.txt", ios::in);

	if (!ifs.is_open()) {
		cout << "文件打开失败!" << endl;
		return;
	}

	//容器清零先
	Vbook.clear();

	Book bk;

	while (ifs >> bk.ID && ifs >> bk.b_name && ifs >> bk.b_author && ifs >> bk.c_num && ifs >> bk.Publishing_unit && ifs >> bk.Publishing_time && ifs >> bk.price && ifs >> bk.exist_state) {
		Vbook.push_back(bk);
	}


	ifs.close();

	cout << "图书信息已成功读取到容器" << endl;

	return;

}


//图书信息浏览
void BookManager::print_book() {
	this->read_f();
	cout << "打印信息" << endl;
	for (vector<Book>::iterator it = Vbook.begin(); it != Vbook.end(); it++) {
		cout << "书的ID号是：" << (*it).ID << "  书名： " << (*it).b_name << "  作者名  " << (*it).b_author <<"  书的分类号:" <<(*it).c_num<<"  出版单位:"<<(*it).Publishing_unit<<"  出版时间："<<(*it).Publishing_time<<"  价格："<<(*it).price<< "当前状态  :" << (*it).exist_state << endl;
	}
	system("pause");
}

//图书信息的删除
void BookManager::delete_book() {
	this->read_f();
	int b_d_choice;
	cout << "请输入想要删除书本的ID号：" << endl;
	cin >> b_d_choice;

	for (vector<Book>::iterator it = Vbook.begin(); it != Vbook.end();) {
		if (it->ID == b_d_choice) {
			it = Vbook.erase(it);
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

//图书信息查询
void BookManager::query() {
	this->read_f();
	int b_choice;
	int s_id;
	string s_name;
	system("cls");
	cout << "|     1:按照书本编号查询     |" << endl;
	cout << "|     2:按照书本名字查询     |" << endl;
	cout << "请输入你的选择：";
	cin >> b_choice;
	switch (b_choice) {
	case 1:

		cout << "请输入想要查找书本的编号:";
		cin >> s_id;

		for (vector<Book>::iterator it = Vbook.begin(); it != Vbook.end(); it++) {
			if (s_id == it->ID) {
				cout << "书本主要信息如下：" << endl;
				cout << "书本编号: " << it->ID << "    书本名字：   " << it->b_name << "   书本出版社：   " << it->Publishing_unit << "   书本价格：   " << it->price << endl;
				return;
			}
		}
		cout << "未找到该书！" << endl;

		break;
	case 2:
		cout << "请输入想要查找书本的名字:";
		cin >> s_name;
		for (vector<Book>::iterator it = Vbook.begin(); it != Vbook.end(); it++) {
			if (strcmp(s_name.c_str(), (it->b_name).c_str()) == 0) {
				cout << "书本主要信息如下：" << endl;
				cout << "书本编号: " << it->ID << "    书本名字：   " << it->b_name << "   书本出版社：   " << it->Publishing_unit << "   书本价格：   " << it->price << endl;
				return;
			}
		}

		break;
		cout << "未找到该书！" << endl;
	}
	return;
}


//保存:把当前容器的数据保存到文件中去
void BookManager::save() {

	ofstream ofs;

	ofs.open("Book.txt", ios::out);

	if (!ofs.is_open()) {
		cout << "文件打开失败！" << endl;
	}

	for (vector<Book>::iterator it = Vbook.begin(); it != Vbook.end(); it++) {
		ofs << it->ID << " " << it->b_name << " " << it->b_author << " " << it->c_num << " " << it->Publishing_unit << " " << it->Publishing_time <<" " << it->price << " " << it->exist_state << endl;
	}

	ofs.close();
	cout << "书籍信息已经成功保存到文件" << endl;
	return;
}

//去重
bool BookManager::check_repeat(int id) {
	for (vector<Book>::iterator it = Vbook.begin(); it != Vbook.end(); it++) {
		if (id == it->ID) {
			return true;
		}
	}
	return false;
}
