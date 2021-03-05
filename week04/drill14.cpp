#include "std_lib_facilities.h"

class Base1 {
public:
	virtual void virtual_function() {
		cout << "Base1: virtual_function()\n"; 
	}
	
	void function() {
		cout << "Base1: function()\n";
	}

	virtual void pure_virtual_function() = 0;
};

class Derive1 : public Base1 {
public:
	void virtual_function() override {
		cout << "Derive1: virtual_function()\n";
	}
	
	void function() {
		cout << "Derive1: function()\n";
	}

	void pure_virtual_function() override {
		cout << "Derive1: pure_virtual_function()\n";
	}
	
};
 
class Derive2 : public Derive1 {
public:
	void pure_virtual_function() override {
		cout << "Derive2: pure_virtual_function()\n";
	}
};

class Base2{
public:
	virtual void pure_virtual_function() = 0;
};

class Derive21 : public Base2{
public:
	void pure_virtual_function() override{
		cout << the_string << endl;
	}
private:
	string the_string{"Drill 14!\n"};

};

class Derive22 : public Base2{
public:
	void pure_virtual_function() override{
		cout << n << endl;
	}
private:
	int n = 15;
};

void f(Base2 &p)
{
	p.pure_virtual_function();
}

int main()
{
	/*
	cout << "example: \n";
	Base1 b1;
	b1.virtual_function();
	b1.function();
	cout << endl;
	*/

	cout << "example: \n";
	Derive1 d1;
	d1.virtual_function();
	d1.function(); // ha nem lenne megirva akkor a basebol hivodna meg es onnan irna ki
	cout << endl;

	cout << "example: \n";
	Base1 &b1_reference = d1;
	b1_reference.virtual_function();
	b1_reference.function();
	cout << endl;

	// mivel egy Base1, Derive1 nem lehet absztarkt, emiatt az alabbi hivasok nem futnak le
	//cout << "example: \n";
	//b1.pure_virtual_function();
	//d1.pure_virtual_function();
	//b1_reference.pure_virtual_function();
	//cout << endl;
	

	cout << "example: \n";
	Derive2 d2;
	d2.virtual_function();
	d2.function();
	d2.pure_virtual_function();
	cout << endl;

	cout << "example: \n";
	Derive21 d21;
	Derive22 d22;
	f(d21);
	f(d22);
	cout << endl;


	return 0;
}