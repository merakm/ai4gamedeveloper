//
//  GeneticEvolution.cpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/06.
//
//

#include "GeneticEvolution.hpp"
#define BASE_CLASS CGeneticEvolutionBase<Flower>

int GetIntRandom( int min, int max ) {
	
	return arc4random()%(max  - min) + min;
}

std::vector<int> make_rand_array_select(const size_t size, int rand_min, int rand_max){

	if(rand_min > rand_max) std::swap(rand_min, rand_max);
	const size_t max_min_diff = static_cast<size_t>(rand_max - rand_min + 1);
	if(max_min_diff < size) throw std::runtime_error("引数が異常です");
	
	std::vector<int> tmp, ret;
	tmp.reserve(max_min_diff);
	ret.reserve(max_min_diff);
	
	for(int i = rand_min; i <= rand_max; ++i)tmp.push_back(i);
	
	for(size_t cnt = 0; cnt < size; ++cnt){
		int rand = GetIntRandom(0, max_min_diff - cnt );
		ret.push_back(tmp[rand]);
		tmp.erase(tmp.begin() + rand);
	}
	
	return std::move(ret);
}

FlowerEvolution::FlowerEvolution( )
: BASE_CLASS()
{	
}

FlowerEvolution::~FlowerEvolution()
{
}


void FlowerEvolution::GenerateFirstGen() {

	for (int i = 0; i < m_NumSpecies; ++i) {
		// srand((unsigned int)time(NULL) + i);
		// int randNum = rand()%100;
		pSpecies[i].sunlight = GetIntRandom(0, 100);
		pSpecies[i].temperature = GetIntRandom(0, 100);
		pSpecies[i].water = GetIntRandom(0, 100);
		pSpecies[i].beneficalInsect = GetIntRandom(0, 100);
		pSpecies[i].nutrient = GetIntRandom(0, 100);
		pSpecies[i].harmfulInsect = GetIntRandom(0, 100);
		
		pScore[i] = 0.0;
	}
	m_CurrentGen = 0;
	
}

void FlowerEvolution::Evaluate() {
	
	for (int i = 0; i < m_NumSpecies; ++i) {
		pScore[i] =
		(double)(
				 pSpecies[i].sunlight
				 + pSpecies[i].temperature
				 + pSpecies[i].water
				 + pSpecies[i].beneficalInsect
				 + pSpecies[i].nutrient
				 - pSpecies[i].harmfulInsect
				 );
	}
	
}

void FlowerEvolution::Crossover() {
	
	Flower* nextGen = new Flower[m_NumSpecies/2];
	
	// スコア最小を求める.
	float	minscore = 600.0;
	int		minscoreindex = -1;
	
	for (int i = 0; i < m_NumSpecies; ++i) {
		if (pScore[i] < minscore ) {
			minscore = pScore[i];
			minscoreindex = i;
		}
	}

	// スコア最大を求める.
	float	maxscore = 0.0;
	int		maxscoreindex = -1;
	for (int i = 0; i < m_NumSpecies; ++i) {
		if (pScore[i] > maxscore ) {
			maxscore = pScore[i];
			maxscoreindex = i;
		}
	}
	
	int ranking[10]; // = new int[m_NumSpecies];
	for (int i = 0; i < m_NumSpecies; ++i) {
		ranking[i] = 10;
	}
	for (int i = 0 ; i < m_NumSpecies; ++i) {
		double score = pScore[i];
		for (int j = 0; j < m_NumSpecies; ++j) {
			if (score <= pScore[j]) {
				ranking[j]--;
			}
		}
	}
	
	
	
	// 最小の個体は淘汰される.
	int nCnt = 0;
	for (int i = 0; i < m_NumSpecies && nCnt < m_NumSpecies/2; ++i) {
		if (ranking[i] < m_NumSpecies / 2 ) {
			nextGen[nCnt].sunlight			= pSpecies[i].sunlight;
			nextGen[nCnt].temperature		= pSpecies[i].temperature;
			nextGen[nCnt].water				= pSpecies[i].water;
			nextGen[nCnt].beneficalInsect	= pSpecies[i].beneficalInsect;
			nextGen[nCnt].nutrient			= pSpecies[i].nutrient;
			nextGen[nCnt].harmfulInsect		= pSpecies[i].harmfulInsect;
			nCnt++;
		}
	}
	
	// 値のシャッフル.
	std::vector<int>  randSunlight		= make_rand_array_select( m_NumSpecies/2, 0,m_NumSpecies/2-1 );
	std::vector<int>  randWater			= make_rand_array_select( m_NumSpecies/2, 0,m_NumSpecies/2-1 );
	std::vector<int>  randTemperature	= make_rand_array_select( m_NumSpecies/2, 0,m_NumSpecies/2-1 );
	std::vector<int>  randBenefit		= make_rand_array_select( m_NumSpecies/2, 0,m_NumSpecies/2-1 );
	std::vector<int>  randHurmful		= make_rand_array_select( m_NumSpecies/2, 0,m_NumSpecies/2-1 );
	std::vector<int>  randNutrient		= make_rand_array_select( m_NumSpecies/2, 0,m_NumSpecies/2-1 );
	
	for (int i = 0; i < m_NumSpecies; ++i) {
		int rand = GetIntRandom(0, m_NumSpecies/2);
		pSpecies[i].sunlight		= nextGen[rand].sunlight;
		rand = GetIntRandom(0, m_NumSpecies/2);
		pSpecies[i].temperature		= nextGen[rand].temperature;
		rand = GetIntRandom(0, m_NumSpecies/2);
		pSpecies[i].water			= nextGen[rand].water;
		rand = GetIntRandom(0, m_NumSpecies/2);
		pSpecies[i].beneficalInsect	= nextGen[rand].beneficalInsect;
		rand = GetIntRandom(0, m_NumSpecies/2);
		pSpecies[i].nutrient		= nextGen[rand].nutrient;
		rand = GetIntRandom(0, m_NumSpecies/2);
		pSpecies[i].harmfulInsect	= nextGen[rand].harmfulInsect;
	}
	
#if 0
	// 値の反映.
	for (int i = 0; i < m_NumSpecies; ++i) {
		if (maxscoreindex == i) {
			// 最大スコアの個体は残す.
			// continue;
		}
		pSpecies[i].sunlight = nextGen[i].sunlight;
		pSpecies[i].temperature = nextGen[i].temperature;
		pSpecies[i].water = nextGen[i].water ;
		pSpecies[i].beneficalInsect = nextGen[i].beneficalInsect ;
		pSpecies[i].nutrient = nextGen[i].nutrient;
		pSpecies[i].harmfulInsect = nextGen[i].harmfulInsect;

	}
#endif
	m_CurrentGen++;
	free(nextGen);
	// free(ranking);

}


void FlowerEvolution::Mutate() {
	
	for (int i = 0; i < m_NumSpecies; ++i) {
		if (GetIntRandom(0, 101) == 1) pSpecies[i].sunlight = GetIntRandom(0, 100);
		if (GetIntRandom(0, 101) == 1) pSpecies[i].temperature = GetIntRandom(0, 100);
		if (GetIntRandom(0, 101) == 1) pSpecies[i].water = GetIntRandom(0, 100);
		if (GetIntRandom(0, 101) == 1) pSpecies[i].nutrient= GetIntRandom(0, 100);
		if (GetIntRandom(0, 101) == 1) pSpecies[i].beneficalInsect = GetIntRandom(0, 100);
		if (GetIntRandom(0, 101) == 1) pSpecies[i].harmfulInsect = GetIntRandom(0, 100);
	}
	
}

bool FlowerEvolution::IsFinishEvolve() {
	
	int scoreMax = GetMaxScore();
	
	return scoreMax >= 500 || m_GenMax < m_CurrentGen;
}