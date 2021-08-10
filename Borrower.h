#pragma once
#pragma once
#include<string>
using namespace std;
class Borrower {
public:
	int s_number;			//学号 

	string s_name;				//姓名 

	string gender; 				//性别 

	int total_bookborrow;		//可借书总数 、

	string borrowed_book;		//当前借的书

	//默认构造函数 
	Borrower() {
		s_number = 0;
		total_bookborrow = 0;
	};

	//有参构造函数
	Borrower(int i_s_number, string i_s_name, string i_gender, int i_total_bookborrow) {
		this->s_number = i_s_number;
		this->s_name = i_s_name;
		this->gender = i_gender;
		this->total_bookborrow = i_total_bookborrow;
	};


};
