//
//  GeneticEvolution.hpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/06.
//
//

#ifndef GeneticEvolution_hpp
#define GeneticEvolution_hpp

template <typename T>
class CGeneticEvolutionBase {
	
public:
	CGeneticEvolutionBase()
	: pSpecies(NULL)
	, pScore(NULL)
	, m_GenMax(0)
	, m_CurrentGen(0)
	, m_NumSpecies(0)
	{
	}
	virtual ~CGeneticEvolutionBase(){
		if (pScore) {
			free(pScore);
			pScore = NULL;
		}
		if (pSpecies) {
			free(pSpecies);
			pSpecies = NULL;
		}
	}
	
	void Initialize(int nSpeciesNum, int nGenMax) {
		
		m_NumSpecies = nSpeciesNum;
		m_GenMax = nGenMax;
		m_CurrentGen = 0;
		
		if (!pScore) pScore = new double[nSpeciesNum];
		if (!pSpecies) pSpecies = new T[nSpeciesNum];
		assert(pSpecies);
		assert(pScore);
		
		memset(pScore, 0, sizeof(pScore));
		memset(pSpecies, 0, sizeof(pSpecies));
	};
	
	virtual void Reset(){ Initialize(m_NumSpecies, m_GenMax); };					// 最初期化.

	
	// 実装必須関数.
public:
	virtual void GenerateFirstGen() = 0;	// 初代の誕生.
	virtual void Evaluate() = 0;			// スコア評価.
	virtual void Mutate() = 0;				// 突然変異.
	virtual void Crossover() = 0;			// 選択&交叉.
	// virtual void GenerateNextGen() = 0;		// 次世代の誕生.
	virtual bool IsFinishEvolve() = 0;		// 進化の終わり.

public:
	void DoEvolution () {
		
		// 第一世代の誕生.
		GenerateFirstGen();
		
		// 適性評価.
		m_CurrentGen = 0;
		//
		while ( m_CurrentGen < m_GenMax ) {
			
			// 評価
			Evaluate();
			if ( IsFinishEvolve() ) break;
		
			// 選択
			Crossover();
			Mutate();
		
		}
		
	}
	
	int GetCurrentGen(){ return m_CurrentGen; }
	T*	GetCurrentSpecies( int index ) {
		if ( 0 <= index && index < m_NumSpecies )
			return &pSpecies[index];
		else
			return NULL;
	}

	double GetMaxScore() {
		
		double ret = 0.0;
		
		for (int i = 0; i < m_NumSpecies; ++i) {
			if (GetSrore(i) > ret) {
				ret = GetSrore(i);
			}
		}
		return ret;
	}
	
	
	double GetSrore( int index )
	{
		if (0 <= index && index < m_NumSpecies) {
			return pScore[index];
		}
		return 0.0;
	}

protected:
	int		m_GenMax;		// 最大世代数.
	int		m_CurrentGen;	// 現在の世代数.
	int		m_NumSpecies;	// 種類.
	double* pScore;			// スコア.
	T*		pSpecies;		// 種.
};

struct Flower {
	int temperature;
	int water;
	int sunlight;
	int nutrient;
	int beneficalInsect;
	int harmfulInsect;
};


class FlowerEvolution : public CGeneticEvolutionBase<Flower> {

public:
	FlowerEvolution();
	~FlowerEvolution();
	
	virtual void GenerateFirstGen();	// 初代の誕生.
	virtual void Evaluate();			// スコア評価.
	virtual void Mutate();				// 突然変異.
	virtual void Crossover();			// 選択&交叉.
	// virtual void GenerateNextGen();		// 次世代の誕生.
	virtual bool IsFinishEvolve();		// 進化の終わり.
	
};
#endif /* GeneticEvolution_hpp */
