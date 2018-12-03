#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <string>
#include "case_one.hpp"
#include "case_two.h"
#include "lecture.h"



TEST(motifsTest, forwardCalcul) {
	case_one calcul;
	std::vector<std::vector<double>> matrice;

    matrice= { {0.9913,0.0019,0.0044,0.0024}, {0.0045,0.0031,0.9611,0.0313}, {0.0032,0.9915,0.0019,0.0034},
				{0.8917,0.0019,0.0089,0.0975}, {0.6241,0.2510,0.0059,0.1187}, {0.7289,0.1045,0.0116,0.1550},
				{0.3048,0.4911,0.0045,0.19969} };

	std::string seq="AGCTCTC";
	double g_res(4.84);
	calcul.calcul_logarithme(matrice);
	double score_seq= calcul.calculate_score_forward(seq);
	EXPECT_NEAR(g_res,score_seq,0.1);

}

TEST(motifsTest, reverseCalcul) {
	case_one calcul;
	std::vector<std::vector<double>> matrice;

	matrice= { {0.9913,0.0019,0.0044,0.0024}, {0.0045,0.0031,0.9611,0.0313}, {0.0032,0.9915,0.0019,0.0034},
				{0.8917,0.0019,0.0089,0.0975}, {0.6241,0.2510,0.0059,0.1187}, {0.7289,0.1045,0.0116,0.1550},
				{0.3048,0.4911,0.0045,0.19969} };

	std::string seq="GATTTCT";
	double g_res(1.08);
	calcul.calcul_logarithme(matrice);
	double score_seq=calcul.calculate_score_reverse(seq);
	EXPECT_NEAR(g_res, score_seq, 0.1);

}

TEST(motifsTest, lectureMatrice) {

	std::vector<std::vector<double>> matrice_fichier;
	case_one fake_calc(0);

	matrice_fichier= { {0.991265586410457,0.00188241672188422,0.00438979579543401,0.00246220107222457},
						{0.00454038913318475,0.00308716342389013,0.961116800192759,0.0312556472501656},
						{0.00319260279955123,0.991529060968172,0.00188243089596181,0.0033959053363151},
						{0.891738449490994,0.00188241672188422,0.00883982892596831,0.0975393048611529},
						{0.624171736642371,0.251091801698693,0.00595596650804169,0.118780495150895},
						{0.728886814047346,0.10454942473345,0.0115881573399193,0.154975603879284},
						{0.304793385940606,0.491122522739594,0.00446509246430938,0.199618998855491} };

	Lecture matrice("DBP.mat", "", "", fake_calc);

	std::vector<std::vector<double>> test_matrix=matrice.getMatrix();

	EXPECT_EQ(matrice_fichier, test_matrix);

}


TEST(motifsTest, conversionInt) {
	Lecture lec;
	std::string motif_to_try = "NAggTcCaNNtG";
	std::string motif_to_compare = "NAggTcCaNNtG";
	std::vector<int> conversion_to_try;
	std::vector<int> conversion_to_compare;
	conversion_to_compare = { 4, 0, 2, 2, 3, 1, 1, 0, 4, 4, 3, 2 };
	conversion_to_try = lec.convertir_en_int(motif_to_try);
	EXPECT_EQ(conversion_to_try, conversion_to_compare);
}


TEST(motifsTest, outputCaseOne) {
	
	std::ifstream original_ifs("output.txt");
	
	case_one _calcul(0.0); 
	Lecture lecture("DBP.mat","promoters.fasta","output1.txt", _calcul);
	
	lecture.readFile();
	
	std::ifstream expected_ifs("output1.txt");
	
	while ((!original_ifs.eof()) and (!expected_ifs.eof())) { 

        std::string line;
        std::string line2;
        
        getline(original_ifs,line);
        getline(expected_ifs,line2);

       EXPECT_EQ(line,line2);

    }
                        
    original_ifs.close();
    expected_ifs.close();

}




/*Case_two two(3,bed_test);

std::vector<std::vector<int>>all_seq {{0,1,2},{3,0,1},{3,1,2,0,2}}

std::vector<std::array <double, 4>> fake_matrix {{1/3,1/9,1/9,4/9},
												 {4/9,4/9,1/9,0},
												 {1/9,1/3,5/9,0}}


TEST(case_twoTest, read)
{
	read_bed();
	std::multimap<int,std::pair<int,int>> multimap;
	multimap= two.getMultimap;
	EXPECT_EQ (multimap.size, 867);//a voir en fonction du fichier bed donne

	for (int i(0);i<23;i++){//a voir en fonction du fichier bed
		EXPECT_FALSE (multimap[i].second==std::make_pair(0.,0.);
	}
}

TEST (case_twoTest, write)
{
	weights(all_seq);
	std::vector<std::array <double, 4>> matrix;
	matrix= two.getMatrix();
	for (int i(0), i<3, i++){
		for (int j(0);j<4;++j){
			EXPECT_EQ(matrix[i][j],fake_matrix[i][j]);
		}
	}

}*/


/*
TEST(motifsTest, BED){


}*/


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
