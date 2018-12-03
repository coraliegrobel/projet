#include <gtest/gtest.h>
#include <vector>
#include <array>
#include "case_two.h"

Case_two two(3,bed_test);

std::vector<std::vector<int>>all_seq {{0,1,2},
									 {3,0,1},
									 {3,1,2,0,2}}
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
	
}

