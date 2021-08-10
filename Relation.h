#pragma once
using namespace std;
#include<string>

class B_Book {
public:
	int borrower_number;
	string borrower_name;
	string book_name;

	B_Book() {
		borrower_number = 0;
	}

	B_Book(int i_number, string i_borrower, string i_book) {
		borrower_number = i_number;
		borrower_name = i_borrower;
		book_name = i_book;
	}
};
