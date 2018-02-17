//
// Book : Version du chapitre 11 de l'ouvrage.
// "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// Commit initial : 17/02/2018 
// Commit en cours : Using nonstandard separators = Chapitre 11.7 and "the drill" page 407
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

// Librairie indispensable sous Windows et VC++
#include "stdafx.h"


// Librairie restreinte fournie par BS
#include "std_lib_facilities.h"

class Punct_stream {  

public:
	Punct_stream(istream& is):source{is},sensitive{true} { }
	void whitespace(const string& s) { white = s; }
	void add_white(char c) { white += c; }
	bool is_whitespace(char c);
	void case_sensitive(bool b) noexcept { sensitive=b; }
	bool is_case_sensitive() noexcept { return sensitive; }
	Punct_stream& operator>>(string& s);
	operator bool();

private:
	istream & source;
	istringstream buffer;
	string white;
	bool sensitive;
	
};

Punct_stream& Punct_stream::operator>>(string& s)
{  
	while (!(buffer>>s)) {
		if (buffer.bad() || !source.good()) return *this;
		buffer.clear();

		string line;
		getline(source, line);

		for (char& ch : line)
			if (is_whitespace(ch))
				ch = ' ';
			else if (!sensitive)
				ch = tolower(ch);

		buffer.str(line);

	}

return *this;

}

bool Punct_stream::is_whitespace(char c)
{  
	for (const char w : white)
		if (c == w)return true;
	return false;

}

Punct_stream::operator bool()
{  
	return !(source.fail() || source.bad()) && buffer.good();

}



int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		// Chapitre 11.7
		// *************
		/*
		Punct_stream ps { cin };
		ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~");
		ps.case_sensitive(false);

		cout << "Merci de rentrer des mots:\n";
		vector<string>vs;
		for (string word; ps >> word;)
			vs.push_back(word);

		sort(vs.begin(), vs.end());
		for (int unsigned i = 0; i < vs.size(); ++i)
			if (i == 0 || vs[i] != vs[i - 1]) cout << vs[i] << '\n';
			*/
		
		// The drill = page 407
		// ********************
		int birth_year = 1966;
		int age = 51;
		cout << showbase<<birth_year << '\t' << hex << birth_year << '\t' << oct<<birth_year << '\n';
		
		cout << dec<<age<< "\n\n";

		int a, b, c, d;
		cout << "Tests de lecture de caractère en dec (a), oct (b) et hex (c et d):\n";
		cin >> a >> oct >> b >> hex >> c >> d;
		cout << a << '\t' << b << '\t' << c << '\t' << d<<'\n';

		double nb = 1234567.89;
		cout << nb << "\t(defaultfloat)\n" << fixed << nb << "\t(fixed)\n" << scientific << nb << "\t(scientific)\n\n";
		
		vector <string> nom{"Tonic","Barberi","Prim","Soldat","Daniaux"};
		vector <string> prenom{"André","Kevin","Grégoire","Natacha","Thierry"};
		vector <string> mobile{"0678787898","0678787876","0645342345","0678787676","0678988786"};
		vector <string> email{"coco@gmail.com","mongrosloulou@gmail.com","magaldane@gmail.com" ,"Jesuispetit@gmail.com" ,"hellomagrandduduche@gmail.com" };

		for (int i=0;i<5;++i) {
			cout << setw(10) <<nom[i]<<"|"<<setw(10)<< prenom[i] << "|" << setw(10) << mobile[i] << "|" << setw(30) << email[i] << "|" << '\n';
		
		}

		keep_window_open();

		return 0;
	}
	/*
	catch (XXXXXXX::Invalid&)
	{
	cerr << "error: ???????????????????? ! \n";
	keep_window_open("q");	// For some Windows(tm) setup
	return 1;
	}
	*/

	catch (runtime_error& e)
	{	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("q");	// For some Windows(tm) setups
	}
}
