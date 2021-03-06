//
// Book : Version du chapitre 11 de l'ouvrage.
// "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// Commit initial : 17/02/2018 - Using nonstandard separators = Chapitre 11.7 and "the drill" page 407
// Commit en cours : 03/03/2018 - Exos page 408-409 = Terminé
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
	bool is_whitespace(char c) noexcept;
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

bool Punct_stream::is_whitespace(char c) noexcept
{  
	for (const char w : white)
		if (c == w)return true;
	return false;

}

Punct_stream::operator bool()
{  
	return !(source.fail() || source.bad()) && buffer.good();

}

bool is_voyelle(char c)	noexcept	// Helper pour l'exercice 3 : on vérifie si le char passé est une voyelle
{
	for (const char w : "aeiouy")
		if (c == w)return true;
	return false;

}

bool is_ponctuation(char c)	noexcept	// Helper pour l'exercice 6 : on vérifie si le char passé est une ponctuation
{
	for (const char w : "“”:!()/.;,?-'<>[]{}")
		if (c == w)return true;
	return false;

}

bool is_saisievalide(char c) noexcept		// Helper pour l'exercice 4 : on vérifie si le char passé est un chiffre ou une lettre Hexa
{
	for (const char w : "0123456789xABCDEFabcdef")
		if (c == w)return true;
	return false;

}

int str_to_int(string s, char manipulator) noexcept	// Helper pour l'exercice 4 : on se sert de la méthode 'integer input' de la page 383 pour transformer un string en int EN FONCTION du mode Dec, Hex ou Octal
{
	istringstream is{ s };
	int i{};
	
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

vector<string>split(const string& s)	// helper function exo 10
{
	
	vector<string>vs{};
	
	for (unsigned int i=0;i<size(s);++i){
		
		vs.push_back(s.substr(i, 1));	// On extrait chaque sous-chaîne et on la pousse dans le vecteur
		vs.push_back(" ");				// Puis, on pousse un espace de séparation
	}

	return vs;

}

vector<string>split1(const string& s,const string& w)	// helper function exo 11
{

	vector<string>vs{};

	for (unsigned int i = 0; i<size(s); ++i) {

		vs.push_back(s.substr(i, 1));	// On extrait chaque sous-chaîne et on la pousse dans le vecteur
		vs.push_back(w);				// Puis, on pousse la string w
	}

	return vs;

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
				
		string str{};
		while (!ist1.eof()) {									// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			getline(ist1, str);									// On lit une ligne terminée par un NEWLINE

			for (char& x : str) x = tolower(x);					// On transforme chaque caractère de la chaîne lue en minuscules : tolower ne fonctionne que sur un char
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

		string str3{};
		string findWord = "important";							// On cherche ce mot dans le fichier
		int numeroLigne = 1;									// On initialise le numéro de ligne
		int totalOccurences = 0;

		while (!ist3.eof()) {									// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			getline(ist3,str3);									// On lit une ligne terminée par un NEWLINE

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
		// Ouverture en lecture du fichier 
		string filename4 = "Using static Analysis_ACM_fev2010.txt";
		ifstream ist4{ filename4 };
		ist4.exceptions(ist4.exceptions() | ios_base::badbit);
		if (!ist4)error("Impossible d'ouvrir le fichier ", filename4);

		// Création d'un fichier pour écriture
		string filename5 = "sans_voyelles.txt";
		ofstream ost5{ filename5 };
		ost5.exceptions(ost5.exceptions() | ios_base::badbit);
		if (!ost5)error("Impossible d'ouvrir le fichier ", filename5);

		string str4{};
		while (!ist4.eof()) {									// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			getline(ist4,str4);									// On lit une ligne terminée par un NEWLINE

			for (char& x : str4) if(is_voyelle(x))x=' ';		// On remplace toute voyelle trouvée par un espace
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
			for (const char& x : nombre_saisi) if (!is_saisievalide(x))error("Le nombre saisi contient un caractère qui n'appartient pas aux systèmes décimal, hexadécimal ou octal !\n"); // Vérification de la saisie
			
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

		// Exo 5 : saisie d'une chaîne = on affiche la classification de chaque caractère de la chaine, suivant celle définie en 11.6 
		// --------------------------------------------------------------------------------------------------------------------------

		string chaine_saisie{};
		cout << "Saisis une chaine de caractères :\n";

		while (cin >> chaine_saisie) {
						
			for (const char& c : chaine_saisie) {	// On extrait chaque caractère de la chaîne saisie et on l'analyse
				cout << c << " : ";
			
				if (isspace(c))cout << " espace ";
				if (isalpha(c))cout << " lettre ";
				if (isdigit(c))cout << " chiffre ";
				if (isxdigit(c))cout << " nombre hexa ";
				if (isupper(c))cout << " majuscule ";
				if (islower(c))cout << " minuscule ";
				if (iscntrl(c))cout << " caractère_de_contrôle ";
				if (isprint(c))cout << " caractère_imprimable ";
				
				cout << endl;
			
			}
			cout << endl<<"Nouvelle saisie :\n";
		}
		
		// ***********************************************************************************************************************************************************************************************

		// Exo 6 : remplacer les ponctuations par des espaces dans un fichier texte 
		// ------------------------------------------------------------------------

		// Ouverture en lecture du fichier
		string filename6 = "Using static Analysis_ACM_fev2010.txt";
		ifstream ist6{ filename6 };
		ist6.exceptions(ist6.exceptions() | ios_base::badbit);
		if (!ist6)error("Impossible d'ouvrir le fichier ", filename6);

		// Création d'un fichier pour écriture
		string filename7 = "sans_ponctuations.txt";
		ofstream ost7{ filename7 };
		ost7.exceptions(ost7.exceptions() | ios_base::badbit);
		if (!ost7)error("Impossible d'ouvrir le fichier ", filename7);

		string str6{};
		while (!ist6.eof()) {									// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			getline(ist6,str6);									// On lit une ligne terminée par un NEWLINE

			for (char& x : str6) if(is_ponctuation(x))x=' ';	// On remplace toute ponctuation trouvée par un espace
			ost7 << str6 << "\n";								// On écrit la chaîne "sans ponctuation" dans le nouveau fichier
		}
		ist6.close();	// Fermeture du fichier
		ost7.close();	// Fermeture du fichier

		// **********************************************************************************************************************************************************************************************
		

		// Exo 7&8 : remplacer les contractions don't par do not, can't par cannot... conversion en minuscules... dictionnaire
		// On repart du fichier "sans_ponctuations.txt" créé à l'exercice 6 afin d'avoir un traitement des mots sans doublons plus juste
		// -----------------------------------------------------------------------------------------------------------------------------

		// Ouverture en lecture du fichier
		string filename6b = "sans_ponctuations.txt";
		ifstream ist6b{ filename6b };
		ist6b.exceptions(ist6b.exceptions() | ios_base::badbit);
		if (!ist6b)error("Impossible d'ouvrir le fichier ", filename6b);

		// Création d'un fichier pour écriture
		string filename7b = "sans_contractions.txt";
		ofstream ost7b{ filename7b };
		ost7b.exceptions(ost7b.exceptions() | ios_base::badbit);
		if (!ost7b)error("Impossible d'ouvrir le fichier ", filename7b);

		string str6b{};
		vector <string> dico{};
		while (!ist6b.eof()) {									// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			getline(ist6b,str6b);								// On lit une ligne terminée par un NEWLINE

			// Transformation 1 : on remplace "can’t" par "cannot"
			const string::size_type t1 = str6b.rfind("can’t");
			if (t1 != string::npos)str6b.replace(t1, 5, "cannot");

			// Transformation 2 : on remplace "won’t" par "will not"
			const string::size_type t2 = str6b.rfind("won’t");
			if (t2 != string::npos)str6b.replace(t2, 5, "will not");

			// Transformation 3 : on remplace "n’t" par " not" (cela fonctionne pour do/does/should/is/did)
			const string::size_type t3 = str6b.rfind("n’t");
			if (t3 != string::npos)str6b.replace(t3, 3, " not");
			
			// Transformation 4 : on remplace "’ll" par " will"
			const string::size_type t4 = str6b.rfind("’ll");
			if (t4 != string::npos)str6b.replace(t4, 3, " will");

			// Transformation finale : tout en minuscules
			for (char& x : str6b) x=tolower(x);

			// Ecriture de chaque mot dans le vecteur créé
			stringstream ss{ str6b };							// On met la chaîne dans un flux de caractères pour mieux la traiter
			for (string s; ss >> s;)dico.push_back(s);
						
			ost7b << str6b << "\n";								// On écrit la chaîne modifiée dans le nouveau fichier
		}
		ist6b.close();	// Fermeture du fichier
		ost7b.close();	// Fermeture du fichier

		// On trie le vecteur dans l'ordre lexicographique et on écrit le dictionnaire à l'écran SANS doublons
		double nbmots_sansdoublons = 0;	// Le type est bien double, sinon la division de deux types différents pour le ratio donne 0... A CREUSER.
		sort(dico.begin(), dico.end());
		
		cout << "Le fichier contient initialement " << dico.size() << " mots" << endl<<endl;
		
		for (unsigned int i = 0; i < dico.size(); ++i)
			if (i == 0 || dico[i] != dico[i - 1]) {
				cout << dico[i] << endl;
				++nbmots_sansdoublons;
			}
		
		cout << endl<<"Au final, il ne reste que " << nbmots_sansdoublons << " mots sans doublons, soit seulement "<<trunc((nbmots_sansdoublons / dico.size()) * 100)<<" %" << endl;

		// ******************************************************************************************************************************************************************************************
		

		// Exo 9 : conversion d'un fichier texte en binaire...
		// ---------------------------------------------------

		// Ouverture en lecture du fichier
		string filename8 = "sans_ponctuations.txt";
		ifstream ist8{ filename8 };
		ist8.exceptions(ist8.exceptions() | ios_base::badbit);
		if (!ist8)error("Impossible d'ouvrir le fichier ", filename8);

		// Création d'un fichier pour écriture en binaire
		string filename9 = "sans_contractions.bin";
		ofstream ost9{ filename9,ios_base::binary };
		ost9.exceptions(ost9.exceptions() | ios_base::badbit);
		if (!ost9)error("Impossible d'ouvrir le fichier ", filename9);

		// Lecture d'une ligne dans le fichier texte puis écriture en binaire dans le fichier cible
		char c{};
		while (!ist8.eof()) {									// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			c=ist8.get();										// On lit un caractère

			ost9.write(as_bytes(c),sizeof(int));				// Ecriture en binaire au format 4-bytes int (page 392)
			
		}
		cout << "Conversion du fichier sans_ponctuations.txt en binaire" << endl;
		ist8.close();	// Fermeture du fichier
		ost9.close();	// Fermeture du fichier

		// ... et inversement
		// ------------------
		
		// Ouverture en lecture du fichier binaire
		string filename8b = "sans_contractions.bin";
		ifstream ist8b{ filename8b,ios_base::binary };
		ist8b.exceptions(ist8b.exceptions() | ios_base::badbit);
		if (!ist8b)error("Impossible d'ouvrir le fichier ", filename8b);

		// Création d'un fichier pour écriture en texte
		string filename9b = "sans_contractions1.txt";
		ofstream ost9b{ filename9b };
		ost9b.exceptions(ost9b.exceptions() | ios_base::badbit);
		if (!ost9b)error("Impossible d'ouvrir le fichier ", filename9b);

		// Lecture du fichier binaire puis écriture en texte dans le fichier cible
		int x = 0;
		while (!ist8b.eof()) {									// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux octets
			ist8b.read(as_bytes(x),sizeof(int));				// Lecture d'un octet

			ost9b << static_cast<char>(x);									// On écrit le caractère

		}
		cout << "Conversion du fichier sans_ponctuations.bin en texte" << endl;	// Note : le fichier texte reconstitué à partir du fichier binaire a la même taille que le fichier .txt initial
		ist8b.close();	// Fermeture du fichier
		ost9b.close();	// Fermeture du fichier
		

		// ******************************************************************************************************************************************************************************************


		// Exo 10&11 : fonctions vecteur
		// -----------------------------
		vector<string>vs{};
		vector<string>vs1{};
		
		vs = split("Mamanestpartieàlapiscine");

		for (string x : vs)
			cout << x;
		cout << endl;

		vs1 = split1("Mamanestpartieàlapiscine"," -");

		for (string x : vs1)
			cout << x;
		cout << endl;
		

		// ***********************************************************************************************************************************************************************************************

		// Exo 12 : reverse the order of characters in a text file
		// -----------------------------------------------------------
		// Ouverture en lecture du fichier 
		string filename12 = "test12.txt";
		ifstream ist12{ filename12 };
		ist12.exceptions(ist12.exceptions() | ios_base::badbit);
		if (!ist12)error("Impossible d'ouvrir le fichier ", filename12);

		// Création d'un fichier pour écriture
		string filename12b = "test12_inverse.txt";
		ofstream ost12b{ filename12b };
		ost12b.exceptions(ost12b.exceptions() | ios_base::badbit);
		if (!ost12b)error("Impossible d'ouvrir le fichier ", filename12b);

		char c{};
		vector<char>inverse{};
		auto it = inverse.begin();									// on se positionne au début du vecteur
		
		while (!ist12.eof()) {										// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			c = ist12.get();										// On lit un caractère...
			if (c!=-1)it = inverse.insert(it,c);					// ... et on l'insère au début du vecteur MAIS en testant qu'il est différent de -1 qui représente le dernier caractère du fichier
			
		}

		for (char x : inverse)
			ost12b << x;											// On écrit chaque caractère du vecteur "inversé" dans le fichier destination
			
		ist12.close();	// Fermeture du fichier
		ost12b.close();	// Fermeture du fichier
		

		// ***********************************************************************************************************************************************************************************************

		// Exo 13 : reverse the order of words in a text file
		// -----------------------------------------------------------
		// Ouverture en lecture du fichier 
		string filename13 = "test13.txt";
		ifstream ist13{ filename13 };
		ist13.exceptions(ist13.exceptions() | ios_base::badbit);
		if (!ist13)error("Impossible d'ouvrir le fichier ", filename13);

		// Création d'un fichier pour écriture
		string filename13b = "test13_inverse.txt";
		ofstream ost13b{ filename13b };
		ost13b.exceptions(ost13b.exceptions() | ios_base::badbit);
		if (!ost13b)error("Impossible d'ouvrir le fichier ", filename13b);

		string words{};
		vector<string>inverseWords{};
		auto it1 = inverseWords.begin();							// on se positionne au début du vecteur
		
		while (!ist13.eof()) {										// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			getline(ist13, words);									// On lit une chaîne entière composée de mots
			
			stringstream ss{ words };								// On met la chaîne dans un flux de caractères pour mieux la traiter
			for (string s; ss >> s;)
				it1 = inverseWords.insert(it1,s);					// On insère chaque mot trouvé au début du vecteur 
			
		}

		for (string x : inverseWords)
			ost13b << x << " ";											// On écrit chaque mot du vecteur "inversé" dans le fichier destination en rajoutant un espace pour les délimiter
			
		ist13.close();	// Fermeture du fichier
		ost13b.close();	// Fermeture du fichier

		// ***********************************************************************************************************************************************************************************************

		// Exo 14 : on lit chaque caractère d'un fichier et on affiche sa classification, suivant celle définie en 11.6 
		// --------------------------------------------------------------------------------------------------------------------------

		// Ouverture en lecture du fichier 
		string filename14 = "Using static Analysis_ACM_fev2010.txt";
		ifstream ist14{ filename14 };
		ist14.exceptions(ist14.exceptions() | ios_base::badbit);
		if (!ist14)error("Impossible d'ouvrir le fichier ", filename14);

		// Définition de la classification
		vector <string>class_char{"espace","lettre","chiffre","nombre hexa","majuscule","minuscule","caractère de contrôle","caractère imprimable","NON TESTABLE (ASCII>127)"};
		vector <int>nb_class_char{0,0,0,0,0,0,0,0,0};
		
		char c{};
		int nb_char_total = 0;
		
		while (!ist14.eof()) {
			c = ist14.get();							// On lit un caractère
			++nb_char_total;

			if (c>=0 && c<=127)							// Sans ce test, les fonctions ci-dessous génèrent une exception
			
			{
				if (isspace(c))++nb_class_char[0];		// espace
				if (isalpha(c))++nb_class_char[1];		// lettre
				if (isdigit(c))++nb_class_char[2];		// chiffre
				if (isxdigit(c))++nb_class_char[3];		// nb hexa
				if (isupper(c))++nb_class_char[4];		// majuscule
				if (islower(c))++nb_class_char[5];		// minuscule
				if (iscntrl(c))++nb_class_char[6];		// caractère_de_contrôle
				if (isprint(c))++nb_class_char[7];		// caractère_imprimable
			}
			
			else 
				++nb_class_char[8];						// caractère NON TESTABLE avec les fonctions décrites en pages 397 et 398
		
			
		}

		for (unsigned int i = 0; i < size(class_char); ++i)
			cout << "Type '" << setw(25)<<class_char[i] << "' : " << nb_class_char[i] << " occurences trouvées" << endl;

		cout << endl<<"Le fichier contenait " << nb_char_total << " caractères à tester" << endl<<endl;
		*/
		
		// ***********************************************************************************************************************************************************************************************

		// Exos 15&16 : on lit un fichier de nombres, on les trie et on les affiche avec leur nombre d'occurences si > 1
		// -------------------------------------------------------------------------------------------------------------

		// Ouverture en lecture du fichier 
		string filename15 = "bourse1.txt";
		ifstream ist15{ filename15 };
		ist15.exceptions(ist15.exceptions() | ios_base::badbit);
		if (!ist15)error("Impossible d'ouvrir le fichier ", filename15);

		string str15{};
		vector <int> numbers{};
		
		while (!ist15.eof()) {									// Tant que la fin du fichier n'est pas atteinte, on continue à extraire de nouveaux enregistrements
			getline(ist15, str15);								// On lit une ligne terminée par un NEWLINE
			numbers.push_back(stoi(str15));						// On stocke le nouvel int dans le vecteur
		
		}
		
		ist15.close();											// Fermeture du fichier

		sort(numbers.begin(), numbers.end());					// tri du vecteur
		
		for (int unsigned i = 0; i < numbers.size(); ++i) {
						
			int nb_doublons = 1;
			while (i > 0 && numbers[i] == numbers[i - 1]) {		// On repère les doublons
				++nb_doublons;
				++i;
			}

			cout << setw(7)<<numbers[i];						// On affiche chaque occurence et, éventuellement, le nombre de doublons
			if (nb_doublons > 1) cout << setw(3)<<nb_doublons<<" doublons";
			cout << endl;
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
