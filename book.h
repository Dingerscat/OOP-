
#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Book {
public:

	int ID;				//编号  

	string b_name;		//书名 

	string b_author;	//作者名

	int c_num;			//分类号

	string Publishing_unit;		//出版单位

	string Publishing_time;		//出版时间

	double price;		//价格

	string exist_state;			//存在状态 

public:
	//默认构造函数
	Book() {
		ID = 0;
		c_num = 0;
		price = 0;
	};
	//有参构造函数 
	Book(int i_ID, string i_b_name, string i_b_author, int i_c_num, string i_Publishing_unit, string i_Publishing_time, double i_price, string i_exist_state);

};


Book::Book(int i_ID, string i_b_name, string i_b_author, int i_c_num, string i_Publishing_unit, string i_Publishing_time, double i_price, string i_exist_state) {
	this->ID = i_ID;
	this->b_name = i_b_name;
	this->b_author = i_b_author;
	this->c_num = i_c_num;
	this->Publishing_unit = i_Publishing_unit;
	this->Publishing_time = i_Publishing_time;
	this->price = i_price;
	this->exist_state = i_exist_state;
}

