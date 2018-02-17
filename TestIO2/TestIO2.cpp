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

bool is_voyelle(char c)		// Helper pour l'exercice 3 : on vérifie si le char passé est une voyelle
{
	for (const char w : "aeiouy")
		if (c == w)return true;
	return false;

}

bool is_saisievalide(char c)		// Helper pour l'exercice 3 : on vérifie si le char passé est une voyelle
{
	for (const char w : "0123456789xABCDEFabcdef")
		if (c == w)return true;
	return false;

}

int str_to_int(string s, char manipulator)
{
	istringstream is{ s };
	int i;
	
	switch (manipulator)
	{
	case 'H':
		is >> hex >> i;
		break;
	
	case 'O':
		is >> oct >> i;
		break;

	default:
		break;
	}
	
	if (!is) error("La saisie est erronée !");
	
	return i;
}



int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		// 1. Chapitre 11.7
		// ****************
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
			
		
		// 2. The drill = page 407
		// ***********************
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

		for (int i=0;i<5;++i) cout << setw(10) <<nom[i]<<"|"<<setw(10)<< prenom[i] << "|" << setw(10) << mobile[i] << "|" << setw(30) << email[i] << "|" << '\n';
		
		cout << "------------------------------------------------------------------------------------------------------------------------------------------------\n\n";

		*/
		// ***************************************************************************************************************************************************************************************
		// 3. Exercices pages 408 et 409
		// ***************************************************************************************************************************************************************************************

		// Exo 1 : lowercase d'un fichier vers un autre
		// ------------------------------------------------
		// Ouverture en lecture du fichier mydata.txt
		string filename1 = "mydata.txt";
		ifstream ist1{ filename1 };
		ist1.exceptions(ist1.exceptions() | ios_base::badbit);
		if (!ist1)error("Impossible d'ouvrir le fichier ", filename1);

		// Création d'un fichier pour écriture
		string filename2 = "mydata_lower.txt";
		ofstream ost2{ filename2 };
		ost2.exceptions(ost2.exceptions() | ios_base::badbit);
		if (!ost2)error("Impossible d'ouvrir le fichier ", filename2);

		static const int taille_max = 500;						// Nombre de caractères max d'un enregistrement
		char str[taille_max] = "";

		while (!ist1.eof()) {									// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			ist1.getline(&str[0], taille_max, '\n');			// On lit un nb de caractères max MAIS on s'arrête dès que l'on rencontre un NEWLINE
			
			for (char& x:str) x= tolower(x);					// On transforme chaque caractère de la chaîne lue en minuscules : tolower ne fonctionne que sur un char
			ost2 << str << "\n";								// On écrit la chaîne "minusculisée" dans le nouveau fichier
		}
		ist1.close();	// Fermeture du fichier
		ost2.close();	// Fermeture du fichier
				
		// ***********************************************************************************************************************************************************************************************

		// Exo 2 : lecture d'un fichier et recherche d'un mot et de son numéro de ligne
		// ----------------------------------------------------------------------------
		// Ouverture en lecture du fichier
		string filename3 = "Using static Analysis_ACM_fev2010.txt";
		ifstream ist3{ filename3 };
		ist1.exceptions(ist3.exceptions() | ios_base::badbit);
		if (!ist3)error("Impossible d'ouvrir le fichier ", filename3);

		static const int taille_max3 = 500;						// Nombre de caractères max d'une ligne
		char str3[taille_max3] = "";
		string findWord = "important";							// On cherche ce mot dans le fichier
		int numeroLigne = 1;									// On initialise le numéro de ligne
		int totalOccurences = 0;

		while (!ist3.eof()) {									// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			ist3.getline(&str3[0], taille_max3, '\n');			// On lit un nb de caractères max MAIS on s'arrête dès que l'on rencontre un NEWLINE

			stringstream ss { str3 };							// On met la chaîne dans un flux de caractères pour mieux la traiter
			int occurence = 0;
			for (string s; ss >> s;)
				if (s == findWord) ++occurence;					// Chaque mot est extrait et le compteur incrémenté si le mot correspond au mot recherché
			
			if (occurence) cout << "Le mot '"<<findWord + "' apparait " << occurence << " fois à la ligne " << numeroLigne << " du fichier\n";
			totalOccurences += occurence;
			++numeroLigne;

		}
		cout << "Le mot '" << findWord + "' apparait donc " << totalOccurences << " fois dans le fichier !\n";
		
		ist3.close();	// Fermeture du fichier
		
		// ***********************************************************************************************************************************************************************************************
		
		// Exo 3 : suppression des voyelles d'un fichier vers un autre
		// -----------------------------------------------------------
		// Ouverture en lecture du fichier mydata.txt
		string filename4 = "Using static Analysis_ACM_fev2010.txt";
		ifstream ist4{ filename4 };
		ist4.exceptions(ist4.exceptions() | ios_base::badbit);
		if (!ist4)error("Impossible d'ouvrir le fichier ", filename4);

		// Création d'un fichier pour écriture
		string filename5 = "sans_voyelles.txt";
		ofstream ost5{ filename5 };
		ost5.exceptions(ost5.exceptions() | ios_base::badbit);
		if (!ost5)error("Impossible d'ouvrir le fichier ", filename5);

		static const int taille_max4 = 500;						// Nombre de caractères max d'un enregistrement
		
		while (!ist4.eof()) {									// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			char str4[taille_max4] = "";						// IMPORTANT : on vide bien cette chaîne-buffer avant chaque lecture
			ist4.getline(&str4[0], taille_max4, '\n');			// On lit un nb de caractères max MAIS on s'arrête dès que l'on rencontre un NEWLINE

			for (char& x : str4) if(is_voyelle(x))x=' ';		// On supprime toute voyelle trouvée
			ost5 << str4 << "\n";								// On écrit la chaîne "sans voyelles" dans le nouveau fichier
		}
		ist4.close();	// Fermeture du fichier
		ost5.close();	// Fermeture du fichier

		// ***********************************************************************************************************************************************************************************************

		// Exo 4 : saisies de nombres (dec, oct ou hex) et conversion en dec
		// -----------------------------------------------------------------
		
		string nombre_saisi{};
		cout <<"Saisis un nombre décimal ou octal (précédé d'un 0) ou hexadécimal (précédé de 0x) :\n";
		
		while (cin>>nombre_saisi) {
			for (char& x : nombre_saisi) if (!is_saisievalide(x))error("Le nombre saisi contient un caractère qui n'appartient pas aux systèmes décimal, hexadécimal ou octal !\n"); // Vérification de la saisie
			
			if (nombre_saisi.substr(0, 2) == "0x") {
				cout << "Le nombre hexadécimal " << nombre_saisi << " correspond à " << dec << str_to_int(nombre_saisi,'H') << " en décimal\n";			// Le nb saisi est HEX
			}
			
			else if (nombre_saisi.substr(0, 1) == "0") {
				int nbOct = stoi(nombre_saisi.substr(2, nombre_saisi.size() - 2));
				cout << "Le nombre octal " << nombre_saisi << " correspond à " << dec << str_to_int(nombre_saisi,'O') << " en décimal\n";			// Le nb saisi est OCTAL
			}
			
			else cout<<"Le nombre saisi est décimal, donc pas de conversion nécessaire\n";

		}
		
		// ***********************************************************************************************************************************************************************************************

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
