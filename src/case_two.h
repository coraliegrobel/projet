#include <vector>
#include <array>
#include <string>
#include <map>
#include "lecture.h"

/*!
 * this class has for role to read the bed file and extract position of
 * sequence we are searching for, call the class Lecture to iter on the genome.
 * once this is done this class gets the sequences from Lecture and add
 * them on a matrix taking into account the size of the sequence and the
 * number of sequences added.
 !*/

class case_two{
private:

int lenght;
int counter;
std::string genome;
std::multimap<std::string,std::pair<int,int>> bed;
Lecture *lecteur;
std::vector<std::array <double, 4>> matrix;

public:
///constructor
case_two (int l, std::string gene_seq, Lecture read);
///will be repeated once to call all necessary functions
void step();
/*!takes in parameter a vector with all sequence found calculates their weight and trocats them if necessary !*/
void weights(std::vector<std::vector<int>> all_seq);
///adds the sequence found to the matrix adding the weight, a==0, t==1,c==2, g==3
void add_matrix(std::vector<int>, double weight);
///divides the whole matrix by the number of sequences added
void divide_matrix(int weight);
///takes in parameter the chromosome, start and end and adds them to the multimap
void add_bed(std::string chromo, std::string d, std::string f);
///reads the bed file and calls add bed with the right parameter
void read_bed();
///pretty self explanatory
void initialise_matrix();
///useful getters for the test
std::multimap<std::string,std::pair<int,int>> getMultimap() {return bed;}
/*!
Calculates the number of motifs added to the matrix
*/
double const getNumberElements();
std::vector<std::array <double, 4>> getMatrix() {return matrix;}

~case_two() {}
};
