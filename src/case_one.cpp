#include "case_one.hpp"
#include <cmath>
#include <string>
#include <algorithm>

case_one::case_one()
{}

case_one::case_one(int seuil)
:threshold(seuil), Position(0)
{
	m.empty();
	m_reverse.empty();
}

void case_one::calcul_logarithme(const std::vector<std::vector<double>>& matrix) 
{

	m=matrix;
	unsigned int size(m.size());
	for(unsigned int i(0);i<size;++i){
		for(unsigned int j(0);j< m[i].size();++j){
			m[i][j]= 2+ log2(m[i][j]);
		}
	}
	m_reverse=m;
	std::reverse(m_reverse.begin(), m_reverse.end());
}



double case_one::calculate_score_forward(const std::string& nucleotide) const
{
	double score(0);
	unsigned int t(m.size());

	for(unsigned int k(0); k < t ; ++k){

		switch(nucleotide[k]){

			case ('A') : score+=m[k][0];
			break;
			case ('C') : score+= m[k][1];
			break;
			case ('G') : score+= m[k][2];
			break;
			case ('T') : score+=m[k][3];
			break;
			case ('N') : score+=0;
			break;
			default		: score+=0;
			break;
		}
	}
	return score;
}


double case_one::calculate_score_reverse(const std::string& nucleotide)const
{
	double score(0);	
	unsigned int t(m_reverse.size());

	//for(unsigned int k(m.size()); k>0 ; --k){
	for (unsigned int k(0); k < t ; ++k){
		switch(nucleotide[k]){

			case ('A') : score+=m_reverse[k][3];
			break;
			case ('C') : score+=m_reverse[k][3];
			break;
			case ('G') : score+= m_reverse[k][1];
			break;
			case ('T') : score+=m_reverse[k][0];
			break;
			case ('N') : score+=0;
			break;
			default : score+=0;
			break;
		}
	}
	return score;
}


void case_one::add_base(char c,std::ofstream& file)
{
	double score_forward(0);
	double score_reverse(0);
	if(Motif.size()==Motif_size){
		score_forward = calculate_score_forward(Motif);
		score_reverse = calculate_score_reverse(Motif);
		Position++;
		if (score_forward > threshold){
		write_in_file(score_forward, true, file); //fonction qui écrit dans le fichier
			score_forward = 0;
		}

		if (score_reverse > threshold) {
			write_in_file(score_reverse, false, file);
			score_reverse = 0;
		}

		Motif.erase(Motif.begin()); //enleve le premier element
		Motif.push_back(c); //ajoute c sur la dernière position

	} else {
		Position++;
		Motif.push_back(c);
	}
}



void case_one::write_in_file(double sequenceScore, bool direction, std::ofstream& file) {
	if (file.is_open()){
		file << name_chromosome;//attribut nom du chromosome en cours
		file << " " << Position - Motif_size;//attribut position dans la séquence (toujours donnée sur le brin forward)
		if (direction) {
			file << " + "; //brin forward
		} else {
			file << " - " ;//brin reverse
		}

		file << Motif; //motif (CHANGER NOM)
		file << " " << sequenceScore << '\n'; //score du motif
	}else {
		throw std::runtime_error("File for output cannot be opened");
	}
}

void case_one::set_name_chromosome(std::string name){
	name_chromosome=name;
}

void case_one::set_Position_zero(){
	Motif.clear();
	Position=0;
}

void case_one::set_Length(size_t l){
	Motif_size=l;
}
