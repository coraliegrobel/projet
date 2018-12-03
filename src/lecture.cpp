#include <iostream>
#include "lecture.h"
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;


const int A(0);
const int T(1);
const int G(2);
const int C(3);


Lecture::Lecture(std::string matrix_file_name,std::string fastafile, std::string _nameOutput, case_one _calcul)
:matrix_file(matrix_file_name), fasta_file(fastafile), outputFile(_nameOutput)
{
	calcul=&_calcul;
	matrix=dl_matrix(matrix_file);
	Motif_size=matrix.size();
	calcul->set_Length(Motif_size);
}

Lecture::Lecture(std::string fastafile, std::string _nameOutput)
:fasta_file(fastafile), outputFile(_nameOutput)
{
	calcul=nullptr;
}

std::vector<vector<double>> Lecture::getMatrix() const
{
	return matrix;
}

std::string Lecture::getOutputFile() const
{
	return outputFile;
}

//Lis le fichier matrice fourni et le stock en vector<vector<double>>
std::vector<vector<double>> Lecture::dl_matrix(std::string file_name)
{
	std::vector<vector<double>> new_matrix;
    std::ifstream ifs(file_name);
    std::string tempstr;
    double tempdouble;
    char delimiter;

    while (std::getline(ifs, tempstr)) {
        std::istringstream iss(tempstr);
        std::vector<double> tempv;
        while (iss >> tempdouble) {
            tempv.push_back(tempdouble);
            iss >> delimiter;
        }
        new_matrix.push_back(tempv);
    }
    return new_matrix;
}

void Lecture::readFile(){
  char c;
  string name_chromosome;
  calcul->calcul_logarithme(matrix);
  std::ifstream fastafile(fasta_file.c_str());
	std::ofstream outputfile(outputFile, std::ofstream::out);
  if(fastafile.is_open()){
  	while(fastafile.get(c)){
      if(c != '\n' and c != EOF){ //ignore les endl
		  c=toupper(c); //convertir minuscule en majuscule
		  if(c=='>'){ //we dont want the char ">" in the title -> ">" inditacates a new title
			std::cout<<"<"<<std::endl;
			getline(fastafile, name_chromosome);
			calcul->set_name_chromosome(name_chromosome);
			calcul->set_Position_zero();
		  }
		  else{
			calcul->add_base(c, outputfile);
		  }
      }
  	}
  }
	outputfile.close();
}


std::vector<std::vector<int>> Lecture::find_motif_with_position(){ //positions is a vector with all positions, need to be in order
	std::vector<std::vector<int>> return_vector;
	std::string motif;
	char c;
	std::vector<std::pair<int,int>> positions;//safes all the positions of the current chromosome
	std::string current_name; //the current name of the chromosome we are testing
	size_t last_position; //remembers the position when we start reading a motif (for the case if we have one motif from Position 20-30 and another from 25-35)
	int current_position(0); //position on the sequence
	size_t vector_position(0); //position in the vector<pair>
	std::ifstream myfile(fasta_file.c_str());
	if(myfile.is_open()){
		while(myfile.get(c)){
			if(c != '\n' and c != EOF){ //ignore les endl
				if(c=='>'){
					getline(myfile, current_name); //extract the title
					positions=getPositions(current_name); //get all the positions of the chromosome
					current_position=0; //we have to put our current position back to zero
					vector_position=0; //as we have a new vector of pairs we restart at zero
				}
				if(not positions.empty()){
					if(current_position==positions[vector_position].first){
						last_position=myfile.tellg(); //returns the position of the iterator in myfile. so we can jump back after adding all the bases
					}
					if(current_position>=positions[vector_position].first and current_position<positions[vector_position].second){ //at the moment we add all the bases including the first and the last
						c=toupper(c); //convertir minuscule en majuscule
						motif.push_back(c);
					}
					if(current_position==positions[vector_position].second){
std::cout<<"motif :"<<motif<<std::endl;
						return_vector.push_back(convertir_en_int(motif));
						motif.clear();
						if(vector_position!=(positions.size()-1)){ //if next startposition is smaller than last stop position I jump
							vector_position++; //we now need the next pair of positions
							if((positions[vector_position-1].second>positions[vector_position].first)){
								myfile.seekg(last_position); //jump back to the last position
								size_t x(vector_position-1);
								current_position=positions[x].first;
							}
						}
					}
					current_position++;
				}
		   }
		}
	}
	return return_vector;
}


std::vector<std::pair<int,int>> Lecture::getPositions(std::string name_chromosome_case2){ //return the positions of a chromosome
	std::vector<std::pair<int,int>> return_vector;
	auto Ibe=Motif_Positions.equal_range(name_chromosome_case2);

	for(auto I=Ibe.first; I!=Ibe.second; I++){
		return_vector.push_back(I->second);
	}

	std::sort(return_vector.begin(), return_vector.end()); //sort the positions after the first element. small to  big
	for(size_t t(0); t<return_vector.size();t++){
	}
	return return_vector;
}


std::vector<int> Lecture::convertir_en_int(string motif)
{
	size_t length(motif.size());
	std::vector<int>result;
	for (size_t i(0);i<length;++i){
		switch (motif[i]){
			case 'N' : result.push_back(4);
			break;
			case 'A' : result.push_back(0);
			break;
			case 'C' : result.push_back(1);
			break;
			case 'G' : result.push_back(2);
			break;
			case 'T' : result.push_back(3);
			break;
			case 'a' : result.push_back(0);
			break;
			case 'c' : result.push_back(1);
			break;
			case 'g' : result.push_back(2);
			break;
			case 't' : result.push_back(3);
			break;
			default :  result.push_back(4);
			break; //
		}
	}
	return result;
}


void Lecture::set_multimap(std::multimap<string, pair<int,int>> map)
{
	Motif_Positions=map;
}


void Lecture::write_matrix(vector<array<double, 4>> matrix_to_write) {
	ofstream file(outputFile, ofstream::out);
	if (file.is_open()){
	size_t size_matrix(matrix_to_write.size());
	for (size_t i(0); i < size_matrix ; ++i) {
		for (size_t j(0); j < 4 ; ++j) { //borne 4 car nombre de colonnes pour chaque ligne (nucléotide)
			file << matrix_to_write[i][j] << " " ;
		}
		file << std::endl;
	}
	}else {
		throw runtime_error("File Matrix cannot be opened");
	}
	file.close();
}
