#include "lecture.h"
#include "case_one.hpp"
#include "case_two.h"
#include <tclap/CmdLine.h>
#include <string>
using namespace std;
using namespace TCLAP;

//pour l'instant j'ai décidé d'utiliser avec un xorArg mais à voir si ça marche
int main(int argc, char **argv) {
	CmdLine cmd("Arguments given");
	//quelle utilisation ?
	SwitchArg FindPositions("P", "FindPositions", "Given matrix and genome, the program finds the positions above the threshold wanted", false);
	SwitchArg FindMatrix("M", "FindMatrix", "Given the genome and the positions, the program finds the Position-Weight matrix", false);

	//les fichiers => bed et matrice sont soit ce que l'on lit, soit où l'on écrit selon l'utilisation
	ValueArg<string> Fastafile("F", "Genomefile", "Name of the file that contains the sequence of the genome studied", true, "NOMDÉFAUT", "string");
	ValueArg<string> Bedfile("B", "Bedfile", "Name of the bedfile containing the positions", false, "NOMDÉFAUT", "string");
	ValueArg<string> OutputFile("O", "Tabfile", "Name of the tabfile to write the positions found", true, "output", "string");
	ValueArg<string> Matrixfile("G", "Matrixfile", "Name of the tab file containing the matrix/where to write the matrix", false, "NOMDÉFAUT", "string");

	//le seuil et la longueur du motif avec xoradd
	//est-ce qu'il faut mettre des valeurs par défaut ?
	ValueArg<double> Threshold("T", "Threshold", "Minimal threshold wanted for the Find Positions use", false, 1, "double");
	ValueArg<int> Length("L", "Length", "Length of the motif wanted for the Find Matrix use", false, 1, "int");

	//on tente le cmd add => sinon exception lancée de type ArgException
	try {
		cmd.xorAdd(FindPositions, FindMatrix);
		cmd.add(Fastafile);
		cmd.xorAdd(Bedfile, Matrixfile);
		cmd.add(OutputFile);
		cmd.xorAdd(Length, Threshold);
		cmd.parse(argc, argv);
	} catch (ArgException &err) {
		cerr << "Error for argument: " << err.argId() << endl;
		return 1; //on arrête le programme
	}
/*
	int longueur=Length.getValue();
	string bed_file=Bedfile.getValue();
	double seuil=Threshold.getValue();
*/

try {
	if (FindPositions.isSet() and Threshold.isSet()) {
		case_one _calcul(Threshold.getValue());
		Lecture lecture(Matrixfile.getValue(), Fastafile.getValue(), OutputFile.getValue(), _calcul);
		lecture.readFile();
		///on fait les calculs pour le cas 1 => LANCER L'ERREUR (THROW) DANS LES FONCTIONS DES CLASSES ET LES APPELER DANS LE TRY
		/// vérifier pour les trois fichiers isOpen()
		}

		else if (FindMatrix.isSet()) {
		Lecture lecture(Fastafile.getValue(), OutputFile.getValue());
		case_two caseTwo (Length.getValue(), Bedfile.getValue(), lecture);
		caseTwo.step();
		///on fait les calculs pour le cas 2 => LANCER L'ERREUR (THROW) DANS LES FONCTIONS DES CLASSES ET LES APPELER DANS LE TRY
		/// vérifier pour les trois fichiers isOpen()
		}
	}

	catch (std::runtime_error &e) {
		cerr << "Erreur: " << e.what() << endl;
		return 1; //on arrête le programme
	}


return 0;
}

//test possible pour le tclap => refaire afficher les paramètres/regarder si ça lance bien les bonnes exceptions
//try/catch :
// - un pour les paramètres tclap (arg exception)
// - un pour l'ouverture des fichiers à lire (runtime error, include à mettre)
// - une boucle conditionnelle if avec isset() pour appeler les bonnes fonctions selon cas 1 ou cas 2
