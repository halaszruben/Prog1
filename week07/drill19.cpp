#include "../std_lib_facilities.h"

template <typename T >
struct S 
{

	S(T value) : val(value) {}

	T& get();
	const T& get() const;

	S& operator=(const T& elem);

private:
	T val;

};

template<typename T>
T& S<T>::get()
{
	return val;
}

template<typename T>
const T& S<T>::get() 
const{
	return val;
}

template<typename T>
S<T>& S<T>::operator=(const T& elem)
{
	val=elem;
	return *this;
}

template<typename T>
void read_val(T& v)
{
	cin >> v;
}

template<typename T>
ostream& operator<<(ostream& os, vector<T> v)
{
	  os << "{ ";
    for (auto i : v)
        os << i << ", ";
    os << '}';

    return os;
}

template <typename T>
istream& operator>>(istream& is, vector<T>& v) {
    char elemek;
    is >> elemek;

    if (elemek != '{') {
        is.unget();
        return is;
    }

    for (T val; is >> val;) {
        v.push_back(val);

        is.get(elemek);
        if (elemek != ',')
            break;
    }

    return is;
}


int main()
{
	S<int> int_type {10};
	S<double> double_type {34.23};
	S<char> char_type {'f'};
	S<string> string_type {"keey"};
	S<vector<int>> vector_int_type {{1,2,3,4,5}};

/*
	cout << int_type.val << endl;
	cout << double_type.val << endl;
	cout << char_type.val << endl;
	cout << string_type.val << endl;
	for ( auto elem : vector_int_type.val )
		cout << elem << ' ';
	cout << endl;
*/

	cout<< "\tLegelso kiiratas \n";
	cout << int_type.get() << endl;
	cout << double_type.get() << endl;
	cout << char_type.get() << endl;
	cout << string_type.get() << endl;
	for (auto elem : vector_int_type.get())
		cout<< elem << ' ';
	cout << endl;

	//set utan
	cout << "\tSet utanni kiiratas \n";
	int_type.operator=(7);
	double_type.operator=(0.1);
	char_type.operator=('b');
	string_type.operator=("ooooo");

	cout << int_type.get() << endl;
	cout << double_type.get() << endl;
	cout << char_type.get() << endl;
	cout << string_type.get() << endl;


	cout << "\tRead value utanni kiiratas: \n"
	<< "\tint, double, char, string\n"
	<< "\tint vectornal {_,_,_,_,} formatum\n";

	int i;
	read_val(i);
	S<int> int_type_2 {i};

	double d;
	read_val(d);
	S<double> double_type_2 {d};

	char c;
	read_val(c);
	S<char> char_type_2 {c};

	string s;
	read_val(s);
	S<string> string_type_2 {s};

	vector<int> v;
	read_val(v);
	S<vector<int>> vector_int_type_2 {v};

	cout<< endl;
	cout << int_type_2.get() << endl;
	cout << double_type_2.get() << endl;
	cout << char_type_2.get() << endl;
	cout << string_type_2.get() << endl;
	cout << vector_int_type_2.get() << endl;

	return 0;
}