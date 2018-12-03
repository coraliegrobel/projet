#ifndef _LECTURE_H_
#define _LECTURE_H_
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include "case_one.hpp"

/*!
 * Description of the Lecture class:
 * This class allows to open, read and write in files used in programm when running
*/

class Lecture {

public:

	/*! Constructors */
	Lecture (std::string matrix_file_name, std::string fastafile, std::string _nameOutput, case_one _calcul);
	Lecture (std::string fastafile, std::string _nameOutput); //for the case two
  Lecture () {}
  ~Lecture() {}

	/*! Reads the fastafile for case 1 where we test for every position if the protein can bind.
	The idea is to:
	* - Iterate over every character
	* - Call with every character that stands for a base the fonction add_base() (case_one class)
	* In order to calculate the value for the current Motif */
	void readFile();

	/*! After bedfile is read and all the start and stop positions of the motifs are saved in the mulitmap Motif_Positions (attribute)
	* Is used for case 2 where we have to calculate the matrix
	* Returns a vector containing all the Motifs found in genome based on bed file informations
	* The motifs are in form of vector<int> instead of string,
	* Due to later computations needs */
	std::vector<std::vector<int>> find_motif_with_position();


	/*! Takes as an argument the name of a chromosome (string)
	* Returns a vector of pairs:
	* - First element of pair is the start position of a motif given
	* - Second element of pair is the stop position of a motif given*/
	std::vector<std::pair<int,int>> getPositions(std::string name_chromosome);

	/*! Allows us to convert a motif in form of string into a vector of int
	* Makes later computations easier */
	std::vector<int> convertir_en_int(std::string motif);

	/*! Setter function: sets the Multimap Motif_Positions (attribute) */
	void set_multimap(std::multimap<std::string, std::pair<int,int>> map);

	/*! Downloads the matrix contained in the "DBP.mat" file,
	* Saves it in a vector<vector<double>>, attribute called matrix,
	* Saves it to use it for later computations */
	std::vector<std::vector<double>> dl_matrix(std::string file_name);

	/*! Getter function: gets the matrix for later computations */
	std::vector<std::vector<double>> getMatrix() const;

	/*! Getter function: gets the output file for later computations (case 1) */
	std::string getOutputFile() const;

	/*!
	 function that writes the matrix file (output) for case 2
	 */
	void write_matrix(std::vector<std::array<double, 4>> matrix_to_write);



private:

	case_one *calcul;

  /*! Name of the matrix_file is saved as a string*/
  std::string matrix_file;

	/*! Name of the fastafile is saved in form of string */
	std::string fasta_file;

  std::string outputFile;

	/*! Name of the chromosome which we are currently reading */
	std::string name_chromosome_case2;


	/*! Motif sequence when identified for case 1*/
	std::string Motif;

	/*! Number of nucleotides of a motif (= length of the motif)
	* Is equal to matrix.size() in case 1;
	* Is given by user in case 2 */
	int Motif_size;


	/*! The multimap allows us to safe all the start and stop positions of a bed file
	* The key is the name of the chromosome (string);
	* The value is a pair<int, int>;
	* The first element of the pair saves the start position, the second element saves the stop position
	*/
	std::multimap<std::string, std::pair<int,int>> Motif_Positions;

	/*! Vector of vector of double that contains the matrix given in matrix_file in case 1;
	* Or the matrix computated in case 2 */
	std::vector<std::vector<double>> matrix;




};

#endif
