#include "std_lib_facilities.h"

//konstans valtozok
constexpr char number = '8';
constexpr char quit = 'q';
constexpr char print = ';';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char square_root = '@';
constexpr char pow_root = 'p';
const string powkey = "pow";
const string declkey = "let";
const string sqrtkey = "sqrt";
const string quitkey = "exit";

double expression();

//fuggveny string es double ertekek vannak benne
class Variable {
public:
	string name;
	double value;
};

vector<Variable> var_table;


bool is_declared(string var){ 
	for (const auto& v : var_table)//ismetelten vegig megyunk a vektoron
		if (v.name == var) return true; // ha a talalunk egy valtozo nevet, ami ugyan az amit atadtunk parameterul, vagyis amit keresunk
	return false;
}

//vissza ad egy erteket ez is
double define_name (string var, double val){ //bekeri a valtozo nevet, majd erteket
	if (is_declared(var)) error(var, " declared twice");//hibakezeles, definialva van e a nev, hasznaljuk e mar? ha igen hiba
	var_table.push_back(Variable{var,val});//a vektor vegere tesszuk az elkeszitett erteket, (Variable{var, val}- ez elkesziti az erteket)
	return val;
}

//itt oldjuk meg hogy a valtozo erteket hasznalni tudjuk
double get_value(string s){
	for(const auto& v : var_table) //vegig megyunk vektoron
		if (v.name == s) return v.value; //hogyha megtalaltuk visszaterituk a a keresett erteket
	error("get: undefined variable", s); //hiba ha nincs meg
	return -1;
}

//beallitjuk a valtozo erteket, megadjuk neki
void set_value(string s, double d){
	for (auto& v : var_table) //vegig megyunk a vektoron
		if(v.name == s){ // megtalaltuk amit keresunk
			v.value = d; //erteke aminek keresunk az a d-ben van
			return; // azert kell ide ez, hogy ne menjen vegig a vektoron ha megtalaljuk hamarabb
		}
		error("set: undefined variable", s); //hibakezeles
}

//ittvannak a konstruktor fuggvenyek
class Token{
public:
	char kind;
	double value;
	string name;
	Token(): kind(0) {}
	Token(char ch): kind(ch), value(0) {} //1 karakterbol all
	Token(char ch, double val): kind(ch), value(val) {} //1 karakterbol es egy double ertekbol all
	Token(char ch, string n): kind(ch), name(n) {} // 1 karakterbol es 1 stringbol all
};

class Token_stream {
public:
	//fuggvenyek, melyeket meghivunk
	Token_stream();
	Token get();
	void putback(Token t); //t tipusu karaktert teszunk vissza
	void ignore(char c); // c tipusu karaktert torlunk
private:
	bool full; 
	Token buffer; //1 db tokent tudunk bele tenni
};

//token streamen beluli fuggveny, melyet meghivunk
Token_stream::Token_stream() :full(false), buffer(0) {} //megnezzuk, hogy van e benne mar ertek amit mar kivettunk az eredeti szambol

//token streamen beluli fuggveny
void Token_stream::putback(Token t){
	if (full) error("putback() into full buffer");// hibakezeles ha mar van benne ertek, nem lenne szabad
	buffer = t; //t az az ertek amit vissza akarunk tenni
	full = true;
}

Token Token_stream::get(){
	//kiuritjuk az erteket amit eltaroltuk
	if (full){ // ha mar tele van
		full = false;
		return buffer; //visszaadjuk az erteket ami a bufferben van
	}
	//olvassuk a bemenetet, mi talalhato benne
	char ch;
	cin >> ch; //kivesz 1 db karaktert, es majd
	// megnezzuk hogyha kifejezesek vannak benne, vagyis + - stb...
	switch (ch){
		case print:
		case quit:
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '=':
		case ',':
			return Token(ch); //meghivjuk a konstruktor fuggvnyeket, mely egybol felismeri, hogy 1 karakterrol van szo es lekezeli
		//megnezzuk, hogyha ertekek vannak benne, ami lehet egesz vagy tizedes szam, ertek is
		case '.':
		case '0': case '1': case '2': case '3': case '4':
    	case '5': case '6': case '7': case '8': case '9':
    	{
    		cin.putback (ch); //a karaktert amit fentebb kivett visszateszi az erteket pl 23 -fentebb kivette 2 maradt 3 majd visszatette a 2-ot es 23 kaptunk
    		double val;
    		cin >> val; //mar egyben kitudjuk olvasni a kert erteke
    		return Token(number, val); //meghivjuk a konstruktor fuggvenyt, mely lekezeli
    	}
    	// hogy mukodjon #-re is a deklaracio
    	case '#':
   			return Token(let);
    	//szoveget kezelunk itt pl: valtozo 
    	default: 
    	{
    		if (isalpha(ch)){ //betu-e amit olvasunk
    			string s;
    			s += ch;
    			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s+=ch; //olvassuk a karaktereket sorban, majd nezzuk hogy szam e vagy betu
    			cin.putback(ch); //mindig 1-nel tobbet olvas legyen az ' ' vagy '=' es vissza kell tenni
    			if (s == declkey) return Token{let}; //ha let tipusu akkor kell deklaralni
    			else if (s == sqrtkey) return Token{square_root}; //hogyha gyokvonas meghivjuk a token square root fuggvenyt, ami a primaryben van
    			else if (s == powkey) return Token{pow_root}; //hogyha hatvanyozas meghivjuk a token pow_root fuggvenyt, ami a primaryben van
    			else if (s == quitkey) return Token{quit};
    			else if (is_declared(s)) //deklaralva van e mar a valtozo?
    				return Token(number, get_value(s)); //ha deklaralva van visszateriti az erteket
    			return Token{name,s}; //deklaralni kell a valtozot es azt adja vissza
    		}
    		error("Bad token");
    	}
	}
	return 0;
}

//torlunk a hatralevo kifejezesbol
void Token_stream::ignore(char c){
	//kiuritsuk a buffert ne legyen benne semmi
	if (full && c == buffer.kind){
		full = false;
		return;
	}
	full = false;

	char ch = 0;
	while (cin>>ch) //olvassuk karakterenkent az ertekeket/bemenetet meg ';'-ig nem erunk
		if (ch==c) return; //kiuritjuk ha ';' erunk
}

Token_stream ts; //ha tokent akarunk elkerni akkor a ts-re vonatkoztatunk vagyis ts.get

//kitorli a rossz kifejezeseket
void clean_up_mess(){
	ts.ignore(print);
}


//ez a fuggveny szamolja ki a hatvanyozast
double calc_pow()
{	
	Token t = ts.get();
	if(t.kind != '(') error("'(' expected");
	double d = expression();

	t=ts.get();
	if(t.kind != ',') error("',' expected");
	double i = expression();

	t=ts.get();
	if(t.kind != ')') error("')' expected");

	return pow(d, i);
}

//ebben a fuggvenyben szamolom ki a gyokvonast
double calc_sqrt()
{
	char ch;
	if(cin.get(ch) && ch != '(') error("'(' expected"); //kerjuk a kovetkezo erteket es ha az nem egyenlo '(' hiba
	cin.putback(ch); //itt is egynel tobbet olvastunk es azt visszatesszuk
	double d = expression(); //zarojelen belul kifejezes lesz es azt az expression fuggveny kezeli le amit majd elment d-ben, vagyis magyarul kiertekeli es visszateriti az erteket
	if(d < 0) error("sqrt negative value"); //hibakezeles negativ ertek nem lehet
	return sqrt(d); //benne van a headerben onnan elerheto az sqrt, vagyis a d-ben kiertekelt erteknek kiszamoljuk a negyzetgyoket es visszaadjuk
} 

//Primary fuggveny amely a zarojelek helyes hasznalataval foglalkozik illetve a negativ ertekekkel
double primary(){

	Token t = ts.get();
	switch (t.kind) // az operator tipusat nezzuk meg
	{ 
		case '(':
		{
			double d = expression(); //meghivjuk az expression fuggvenyt es kezdodik elolrol a folyamat
			t = ts.get(); //bekerjuk a kovetkezo erteket
			if (t.kind != ')') error ("')' expected"); //ha a kovetkezo ertek nem ')' akk hiba
			return d;
		}
		case number: //hogyha 1 szam es nem ()
			return t.value;
		case '-':
			return - primary(); //visszaadja a negativ erteket es nem pedig szamol
		case '+':
			return primary();
		case square_root: //negyzetgyokvonas PL: sqrt(9)=3, sqrt(4+12) sqrt(x+2)
			//azert kezeljuk le primaryben, hogy az expressionnel az ertek belsejet kitudjuk ertekelni
			return calc_sqrt();
		case pow_root: //hatvanyozas
			return calc_pow();
		default:
			error("primary expected");
	}
	return -1;
}

//term fuggveny, amely a * illetve / jellel tud foglalkozni
double term(){

	double left = primary();
	Token t = ts.get();
	while(true){ //mig a kifejezes vegere nem ertunk
		switch (t.kind){ // nezzuk meg mi a tipusa az operatornak?
			case '*':
				left *= primary(); //a bal erteket megszorozzuk 
				t = ts.get(); //kerjuk a kovetkezo elemet
				break;
			case '/':
			{
				double d = primary(); //elkerjuk az erteket
				if (d == 0) error ("divide by zero"); //hibakezeles 0-val nem lehet osztani
				left /= d; //a bal erteket elosztjuk a mar megkapott eredmennyel
				t = ts.get(); //kerjuk a kovetkezo elemet
				break;
			}
			case '%': //maradek osztas szamolas
			{
				double d = primary(); //elkerjuk az erteket
				if(d == 0) error ("%: divide by zero"); //hibakezeles
				left = fmod(left, d); //kiszamoljuk a kivant erteket
				t=ts.get(); //kovetkezo elem
				break;
			}
			default:
				ts.putback(t); //visszateritjuk az erteket, ha egyik sem
				return left;
		}
	}
}

//expression fuggveny, amely a '+' es a '-' foglalkozik
double expression(){

	double left = term();
	Token t = ts.get();
	while (true){  //meg a kifejezes vegere nem ertunk
		switch(t.kind){ // nezzuk meg mi a tipusa az operatornak?
			case '+':
				left += term(); // a jobb erteket adjuk hozza a termhez
				t = ts.get(); // kerjuk a kovetkezo elemet
				break;
			case '-':
				left -= term(); // a jobb ertekbol vonjuk kia termbol
				t = ts.get(); // kerjuk a kovetkezo elemet
				break;
			default:
				ts.putback(t); //visszateritjuk az erteket, ha egyik sem
				return left;
		}
	}
}

//hogyan nez ki a declaration kb, amivel foglalkozik
double declaration(){
	Token t = ts.get(); // kovetkezo token, valtozo neve
	if (t.kind != name) error("name expected in declaration"); //hibakezeles, ha nem pl: 'x= '
	string var_name = t.name; //eltaroljuk a nevet

	//azt ellenorizzuk hogy a kovetkezo ertek '='-e
	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression(); //valtozo erteke, amit atadunk expressionnek PL: x=4*2 tud ilyet, nem pedig csak x=2
	define_name(var_name, d);
	return d; //visszaadjuk az erteket
}

//kulonbseget teszunk, a deklaracios utasitas kozott es a matematikai kifejezes kozott
double statement(){
	Token t = ts.get(); //bekerjuk a tokent/erteket
	switch(t.kind){ //megnezzuk, hogy a token deklaracio-e
		case let: //hogyha let szo van elotte
			return declaration(); // meghivjuk a declaration fuggvenyt
		default:
			ts.putback(t); //visszatesszuk a tokent
			return expression(); //meghivjuk az expression figgvenyt
	}
}

//beolvas, szamolgat, dolgozik, minden innen indul kb
void calculate(){
	
	while (cin) //olvassuk a bemenetet
	try {
		Token t = ts.get(); // kerjuk a kovetkezo elemet/tokent/erteket
		while (t.kind == print) t = ts.get(); //kerjuk a kovetkezo elemet, ugyan ugy meg printig nem erunk
		if (t.kind == quit) return; //ha a beirt ertek quit tipusu akkor kilepunk
		ts.putback(t); //visszatesszuk a token_streambe az erteket
		cout << "=" << statement() << endl; //kiirjuk, majd meghivjuk a statement fuggvenyt, mert van eredmenyunk
	}//lekezelunk minden hibat
	catch (exception& e) {
		cerr << e.what() << endl;
		clean_up_mess(); //meghivjuk a clean_up_mess fuggvenyt 
	}
}

int main() 
{	try {
		define_name("k",1000);
		calculate();
		
		return 0;
	} catch (exception& e){ //hibakezeles
		cerr << e.what() << endl;
		return 1;
	} catch (...) {
		cerr << "exception\n";
		return 2;
	}
}