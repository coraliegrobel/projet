#ifndef _CASE_ONE_HPP_
#define _CASE_ONE_HPP_
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

/*!
 * Description of case_one class:
 * This class is used for calculations needed in both cases:
 * (Scores, Probability of nucleotides at a certain position, Comparison with threshold)
 */

class case_one {

public :

	/*! Constructors */
	case_one ();
	case_one(int seuil);
	~case_one() {}

	/*! Calculates the forward strand score taking a sequence of nucleotides of the motif's size */
	double calculate_score_forward(const std::string& nucleotide) const;

	/*! Calculates the reverse strand score taking a sequence of nucleotides of the motif's size */
	double calculate_score_reverse(const std::string& nucleotide) const;

	/*! For each sequence of motif's size:
	 * Calculates the score by calling functions for forward and reverse strands,
	 * Checks if superior to the threshold,
	 * If so, calls write_in_file function of Lecture class to write the output
	 */
	void add_base(char c, std::ofstream& file);
	
	/// function that calculates the matrix in log2  

	void calcul_logarithme(const std::vector<std::vector<double>>& matrix) ;
		/*!
		 function that writes the output file for case 1
		 */
		void write_in_file(double sequenceScore, bool direction, std::ofstream& file);

		void set_name_chromosome(std::string name);

		void set_Position_zero();

		void set_Length(size_t l);

private:

	size_t Motif_size;
	/*! Threshold given by user for case 1 */
	int threshold;
	/*! Attributes of Calcul class */
	std::string Motif;
	/*! File (empty) chosen by user to write the output for case 1 */
	std::string output_file;
	/*! For the first case, tells us on which position we are when reading the fastafiles */
	int Position;
	/*!
	Name of the current name_chromosome
	*/
	std::string name_chromosome;
	///matrix in log2
	std::vector<std::vector<double>> m;
	///matrix reverse in log2
	std::vector<std::vector<double>> m_reverse;
};

#endif
