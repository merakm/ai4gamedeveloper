//
//  Chapter15FieldDlg.cpp
//  AI for Game Developer
//
//  Created by Kohei Kumazaki on 2017/02/06.
//
//

#include "Chapter15FieldDlg.hpp"

#define BASE_LAYER LayerBase

static const std::string btntext[Chapter15FieldDlg::eBUTTON_NUM] = {
	"Start",
	"Next",
};

Chapter15FieldDlg::Chapter15FieldDlg()
: m_bDoEvolution (false)
, m_bGenerateFirstGen(false)
{
	// memset(pBtnLabel, 0, sizeof(pBtnLabel));
}


void Chapter15FieldDlg::addinit() {
	
	LayerColor::initWithColor(Color4B(0,0,0,255));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	Vec2 titlePos(Vec2(origin.x + visibleSize.width/2,
					   origin.y + visibleSize.height - 100.f));
	// ボタン.
	for (int i = eBUTTON_START; i < eBUTTON_NUM; ++i) {
		Vec2 pos( titlePos.x, titlePos.y - 20 - 25*(i+1) );
		Label* pBtnLabel = Label::createWithTTF(btntext[i], "fonts/arial.ttf", 20);
		pBtnLabel->setTag(i);
		auto pBtn = MenuItemLabel::create(pBtnLabel, CC_CALLBACK_1(Chapter15FieldDlg::selectchapterbtn, this, i));
		
		Menu* pMenu = Menu::create(pBtn, NULL);
		pMenu->setPosition(pos);
		this->addChild(pMenu, 1);
	}
	
	// テキスト.
	for (int i = 0; i < eTEXT_NUM; ++i) {
		pText[i] = Label::createWithTTF("", "fonts/arial.ttf", 20);
		pText[i]->setPosition(titlePos + Vec2(0, (i*-50)-100));
		pText[i]->retain();
		this->addChild(pText[i]);
	}
	
	flowerEvolution.Initialize(10, 2000);
	m_maxScore = 0.0;

}

void Chapter15FieldDlg::update(float delta) {
	
	//if (m_bGenerateFirstGen) {
	if ( m_bDoEvolution ) DoEvolution();
	if (m_bGenerateFirstGen) {
		char buff[256];
		double maxscore =flowerEvolution.GetMaxScore();
		snprintf(buff, sizeof(buff), " Score : %f",  maxscore);
		pText[eTEXT_SCORE]->setString(buff);
		
		for (int i = eTEXT_GEN_INFO_START; i < eTEXT_GEN_INTO_END; ++i) {
			Flower*	pFlower = flowerEvolution.GetCurrentSpecies(i - eTEXT_GEN_INFO_START);
			snprintf(buff, sizeof(buff), " Gen %2d : %3d, %3d, %3d, %3d, %3d, %3d, %f",
					 i - eTEXT_GEN_INFO_START + 1,
					 pFlower->temperature,
					 pFlower->water,
					 pFlower->nutrient,
					 pFlower->sunlight,
					 pFlower->beneficalInsect,
					 pFlower->harmfulInsect,
					 flowerEvolution.GetSrore(i-eTEXT_GEN_INFO_START));
			pText[i]->setString(buff);
		}
		
		snprintf(buff, sizeof(buff), " Current Generation : %d", flowerEvolution.GetCurrentGen());
		pText[eTEXT_GENERATION]->setString(buff);

		snprintf(buff, sizeof(buff), " Current Generation : %d", flowerEvolution.GetCurrentGen());
		pText[eTEXT_GENERATION]->setString(buff);

		m_maxScore = fmax(m_maxScore, maxscore);
		snprintf(buff, sizeof(buff), " Max Score : %f", m_maxScore);

		pText[eTEXT_MAX_SCORE]->setString(buff);
		
	}
	BASE_LAYER::update(delta);
	
}

void Chapter15FieldDlg::DoEvolution() {
	
	if (!m_bGenerateFirstGen) {
		flowerEvolution.GenerateFirstGen();
		// 評価
		flowerEvolution.Evaluate();

		m_bGenerateFirstGen = true;
	}
	
	if (!flowerEvolution.IsFinishEvolve()) {
	
		// 選択
		flowerEvolution.Crossover();
		flowerEvolution.Mutate();
		// 評価
		flowerEvolution.Evaluate();
		
	}
	else {
		m_bDoEvolution = false;
		m_bGenerateFirstGen = false;
		flowerEvolution.Reset();
		m_maxScore = 0.0;
	}
	
}

void Chapter15FieldDlg::selectchapterbtn(cocos2d::Ref* pSender, int btnid) {

	switch (btnid) {
	case eBUTTON_EVOLVE_START:
		{
			m_bDoEvolution = !m_bDoEvolution;
		}
			break;
	case eBUTTON_NEXT:
		{
			m_bDoEvolution = false;
			DoEvolution();
		}
			break;
	default:
			break;
	}
}




