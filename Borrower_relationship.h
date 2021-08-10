#pragma once
#include<iostream>
#include<vector>
#include"Relation.h"
#include<fstream>
#include<string>
using namespace std;

class Borrower_relationship {
public:
	//借阅关系管理子菜单
	int show_menu();

	//登录模块（判断是否会员）
	bool assign(ReaderManager& rm);

	//读入借阅关系（读文件）
	void read_f();

	//办理借书手续（非注册会员不能借书）
	void to_borrow(ReaderManager& rm, BookManager& bm);

	//办理还书手续
	void return_book(ReaderManager& rm, BookManager& bm);

	//查看当前所有借阅关系
	void print_relation();

	//删除借阅关系
	void delete_relation(int number);

	//保存借阅关系
	void save();

	vector<B_Book>V_b_book;	//vector borrower and book;
};


//借阅关系管理子菜单
int Borrower_relationship::show_menu() {
	cout << endl;
	cout << "|					【图书管理子菜单】					" << endl;
	cout << "|					1:判断某人是否会员					" << endl;
	cout << "|					2:办理借书手续（非注册会员不能借书，成功借书后自动保存）	" << endl;
	cout << "|					3:办理还书手续 (成功还书后自动保存)					" << endl;
	cout << "|					4:查看当前所有的借阅关系			" << endl;
	cout << "|					0:返回上级菜单					" << endl;

	int choice;
	cout << "请输入你的选择: ";
	cin >> choice;

	system("cls");

	return choice;
}

//登录模块（判断是否会员）
bool Borrower_relationship::assign(ReaderManager& rm) {
	int br_number;
	rm.read_f();	//Borrower.txt读入到vector<Borrower> Vborrower容器

	cout << "请输入登录学号: ";
	cin >> br_number;

	for (vector<Borrower> ::iterator it = rm.Vborrower.begin(); it != rm.Vborrower.end(); it++) {
		if (it->s_number == br_number) {
			return true;
		}
	}
	return false;
}

//读入借阅关系（读文件）
void Borrower_relationship::read_f() {

	//读取文件信息
	ifstream ifs;

	ifs.open("Relation.txt", ios::in);

	if (!ifs.is_open()) {
		cout << "文件打开失败!" << endl;
	}

	B_Book bbk;

	//容器清零先
	V_b_book.clear();


	while (ifs >> bbk.borrower_number && ifs >> bbk.borrower_name && ifs >> bbk.book_name) {
		V_b_book.push_back(bbk);
	}

	ifs.close();

	cout << "借阅关系文件已经成功读取到容器" << endl;

	return;
}

//办理借书手续（非注册会员不能借书）
void Borrower_relationship::to_borrow(ReaderManager& rm, BookManager& bm) {
	int br_number;
	string br_name;
	string br_book;
	string br_state = "wait";
	string br_stated = "borrowed";

	ofstream ofs;
	ofs.open("Relation.txt", ios::out | ios::app);

	rm.read_f();	//Borrower.txt读入到vector<Borrower> Vborrower容器
	bm.read_f();	//Book.txt读入到vector<Book>Vbook 容器

	cout << "请输入登录学号: ";
	cin >> br_number;

	for (vector<Borrower> ::iterator it = rm.Vborrower.begin(); it != rm.Vborrower.end(); it++) {
		if (it->s_number == br_number) {
			cout << "该学生在注册表存在!" << endl;
			cout << "输入学号为" << it->s_number << "的学生想要借书的书名: " << endl;
			cin >> br_book;

			for (vector<Book>::iterator itbook = bm.Vbook.begin(); itbook != bm.Vbook.end(); itbook++) {

				//在容器中找到该书且该书的状态为wait

				//如果找到该书且该书的状态为wait便执行操作
				if (strcmp(br_book.c_str(), (*itbook).b_name.c_str()) == 0 && strcmp(br_state.c_str(), (*itbook).exist_state.c_str()) == 0) {
					//具体借书流程 :将借阅关系写入到文件，借书人的可借书数量-1，被借书的书状态改为borrowed;

					//借阅关系写入文件
					ofs << it->s_number << " " << it->s_name << " " << itbook->b_name << endl;
					cout << "借阅关系写入文件成功!" << endl;
					ofs.close();

					//借书人的可借书数量-1
					it->total_bookborrow--;
					rm.save();

					//被借书的书状态改为borrowed
					itbook->exist_state = br_stated;
					
					bm.save();

					cout << "借书成功！" << endl;
					return;

				}

			}


		}


	}
	cout << "该学生非图书馆会员，无法借书!" << endl;
	return;
}

//办理还书手续
void Borrower_relationship::return_book(ReaderManager& rm, BookManager& bm) {
	int br_number;
	string br_book;
	string br_state = "wait";
	string br_stated = "borrowed";

	rm.read_f();	//Borrower.txt读入到vector<Borrower> Vborrower容器
	bm.read_f();	//Book.txt读入到vector<Book>Vbook 容器
	this->read_f();

	cout << "请输入登录学号: ";
	cin >> br_number;

	for (vector<Borrower> ::iterator it = rm.Vborrower.begin(); it != rm.Vborrower.end(); it++) {
		if (it->s_number == br_number) {


			cout << "输入要归还的书名:" << endl;
			cin >> br_book;

			//书改成wait
			for (vector<Book>::iterator itbook = bm.Vbook.begin(); itbook != bm.Vbook.end(); it++) {
				if (strcmp(br_book.c_str(), (*itbook).b_name.c_str()) == 0 && strcmp(br_stated.c_str(), (*itbook).exist_state.c_str()) == 0) {

					//被借书的书状态改为wait
					itbook->exist_state = br_state;
					bm.save();


					//借书人的可借书数量+1
					it->total_bookborrow++;
					rm.save();

					//删除借阅信息
					this->delete_relation(br_number);

					cout << "还书成功！" << endl;
					return;
				}
			}


		}
	}
	cout << "注册表中没有该学生，请检查！" << endl;
	return;
}

//删除借阅关系
void Borrower_relationship::delete_relation(int number) {


	for (vector<B_Book>::iterator it = V_b_book.begin(); it != V_b_book.end();) {
		if (it->borrower_number == number) {
			it = V_b_book.erase(it);
			cout << "删除成功！" << endl;
			this->save();	//删除后自动保存
		}
		else {
			++it;
		}
	}
	cout << "未找到此借阅关系，删除失败!" << endl;
	return;
}


//查看当前所有借阅关系
void Borrower_relationship::print_relation() {
	this->read_f();

	for (vector<B_Book>::iterator it = V_b_book.begin(); it != V_b_book.end(); it++) {
		cout << "借书人学号：" << it->borrower_number << "借书人姓名：" << it->borrower_name << "所借书籍: " << it->book_name << endl;
	}
	system("pause");
	return;
}

//保存借阅关系
void Borrower_relationship::save() {
	ofstream ofs;

	ofs.open("Relation.txt", ios::out);

	if (!ofs.is_open()) {
		cout << "文件打开失败！" << endl;
	}
	for (vector<B_Book>::iterator it = V_b_book.begin(); it != V_b_book.end(); it++) {
		ofs << it->borrower_number << " " << it->borrower_name << " " << it->book_name << endl;
	}

	ofs.close();
	cout << "借阅关系信息已经成功保存到文件" << endl;
	return;
}
