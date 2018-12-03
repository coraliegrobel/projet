#include "case_two.h"
#include <fstream>
case_two::case_two (int l, std::string gene_seq, Lecture read){
	lenght=l;
	genome= gene_seq;
	lecteur =&read;
	initialise_matrix();
	}

void case_two::step(){
	read_bed();
	lecteur->set_multimap(bed);
	std::vector<std::vector<int>> all_seq ;
	all_seq=lecteur->find_motif_with_position();
				//affichage
						for(size_t k(0);k<all_seq.size();k++){
							std::cout<<std::endl;
							for(size_t h(0);h<all_seq[0].size();h++){
								std::cout<<all_seq[k][h]<<"	";
							}
						}
				//fin affichage
	weights(all_seq);
	divide_matrix(getNumberElements());
				//affichage
						for(size_t i(0); i<matrix.size();i++){
							std::cout<<std::endl;
							for(size_t j(0); j<matrix[0].size(); j++){
								std::cout<<matrix[i][j]<<"	";
							}
						}
					//affichage fin
		lecteur->write_matrix(matrix);
	}

void case_two::weights(std::vector<std::vector<int>> all_seq){
	std::vector<int> tmp;
	int size;
	size=all_seq.size();
	int taille;
	double weight(1);
	for (int i(0); i< size ;i++){
		tmp=all_seq[i];
		taille= tmp.size();
		if (taille!= lenght){
			weight=1/(taille -lenght+1);
			counter++;
			for (int j(lenght); j<=taille; j++){
				std::vector<int> seq;
				seq.assign (tmp.begin()+taille-j,tmp.end());
				add_matrix(seq,weight);
				tmp.pop_back();
			}
		}else{
			add_matrix(tmp,1);
			counter++;
			}
		}
					//affichage
							std::cout<<std::endl<<"matrix :"<<std::endl;
							for(size_t k(0);k<matrix.size();k++){
								std::cout<<std::endl;
								for(size_t u(0);u<matrix[0].size();u++){
									std::cout<<matrix[k][u]<<"	";
								}
							}
					//fin affichage
	}

void case_two::add_matrix(std::vector<int> seq, double weight){
	for (int j(0); j<lenght; ++j){
		if (seq[j]<=3){
			 matrix[j][seq[j]]+=weight;
		 }
	 }
	}
void case_two::initialise_matrix(){
	for (int i(0);i<lenght;++i){
		matrix.push_back({0.,0.,0.,0.});
			}
		}


void case_two::divide_matrix(int weight){
std::cout<<std::endl<<"weight :"<<weight<<std::endl;
	if(weight!=0){
		for (int i(0);i<lenght;++i){
			for (int j(0);j<4;++j){
				matrix[i][j]/=weight;
				}
			}
		}
	}

 void case_two::read_bed(){
	std::ifstream bed_file (genome);
	std::string chromo, pos, debut, fin;
	int start(0);
	while (not bed_file.eof()){
		std::getline(bed_file, pos);
		start=0;
		if(not pos.empty()){
			do{
				if (pos[0]=='	') {//est ce que le tab fonctionne
					++start;
					}else if(start==0){
						chromo+=pos[0];
						}else if(start==1){
							debut+=pos[0];
							}else if(start==2){
								fin+=pos[0];
							}
				pos.erase(pos.begin());
				}while (pos.size()> 0);
			add_bed(chromo, debut, fin);
			chromo.clear();
			debut.clear();
			fin.clear();

			}
		}
		bed_file.close();
	}

void case_two::add_bed(std::string chromo, std::string d, std::string f){
	bed.insert(std::make_pair(chromo, std::make_pair(std::stoi(d), std::stoi(f))));
	}

double const case_two::getNumberElements(){
	double result(0);
	if(not matrix.empty()){
		for(size_t k(0); k<4; k++){
			result += matrix[0][k];
		}
		return result;
	}
	return 0;
}
/*
void case_two::tri(){
	int taille (bed.size());
	for(int i(0);i<=taille;i++){
		std::vectort<std::pair<int,int>>tmp1=(bed(i).second)
		std::vector<int>tmp2=tmp1.first;
		std::vector<int>tmp3=tmp1.second;
		std::sort(tmp1.begin(), tmp1.end());
		std::sort(tmp2.begin(), tmp2.end());
		(bed(i).second).first=tmp1;
		(bed(i).second).second=tmp2;
		}
	}

void case_two::overlapping(){
	int taille (bed.size());
	int size ((bed.second).size())
	for(int j(0);i<=taille;i++){
		for(int i(0);i<size;++i){
			if ((bed(j).second)[i+1].first>(bed(j).second)[i].second){
				overlap.push_back(true);
				}else{
					overlap.push_back(false);
				}
			}
		}
	}
*/

/*
std::vector<int> case_two::iter (int start,int longueur= lenght){
std::vector<int> result;
for (inti (0);i<start+longueur;+i){
	counter++
	int c;
	if (counter>start){
		result += char
		}
	c= getchar();
	}
return result;
}
*/
/*
void case_two::compute(int debut,int weight){
	//has to iterate on the genome on the lenght only
	std::array<int, lenght> result;
	std::array<std::char, lenght> letter_code;
	if (weight!=1){
		letter_code=tmp[lenght-1];
		letter_code+=lecteur.lit(debut, lenght-1)
		}else if(overlap[counter_overlap]){
			int size_overlapped(counter-debut)
			letter_code = (tmp.end()-size,tmp.end());///////////
			letter_code+=lecteur.lit(debut+size_overlapped, lenght-size_overlapped);
			}
			//ne fonctionne pas pour les sequences plus longues
		//std::vector<int> overlaped;
		//int longueur (lenght-(counter-debut[pos]));
		//overlaped=iter(debut[pos])
		//result =(tmp.end()-overlaped.size(), tmp.end())
		//result+=overlaped
		else {
			result=iter(debut[pos])
		}
	for (int i(0);i<lenght;++i){
		switch (letter_code[i]){
			case A : result[i]=0;
			break;
			case C : result[i]=1;
			break;
			case G : result[i]=2;
			break;
			case T : result[i]=3;
			break;
			case a : result[i]=0;
			break;
			case c : result[i]=1;
			break;
			case g : result[i]=2;
			break;
			case t : result[i]=3;
			break;
			default : break; ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		}
	add_matrix(result, weight);
	tmp= result;
	++counter_overlap;
	}
	*/
