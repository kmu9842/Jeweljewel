#include "RankingMenu.h"
#include "MainScene.h"

USING_NS_CC;

CCScene *RankingMenu::scene()
{
	CCScene *scene = CCScene::create();
	RankingMenu *layer = RankingMenu::create();

	scene->addChild(layer);

	return scene;
}

bool RankingMenu::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	CCSprite *BackGround = CCSprite::create("backg.png");
	BackGround->setPosition(ccp(winSize.width / 2, winSize.height / 2)); //위치지정
	this->addChild(BackGround);

	CCMenu *MenuMain = CCMenu::create(NULL); //메뉴생성

	//메뉴아이템 추가
	CCMenuItem *item1 = CCMenuItemImage::create("back.png",
		"back.png",
		this,
		menu_selector(RankingMenu::menuCloseCallback));

	MenuMain->addChild(item1, 1); //메뉴에 아이템 붙이기
	MenuMain->setPosition(ccp(winSize.width - 50, 50));
	this->addChild(MenuMain, 1); //메뉴를 레이어에 추가

	CCLabelTTF *title = CCLabelTTF::create("Rank", "fonts/Marker Felt.ttf", 42);
	title->setColor(ccc3(0, 0, 0));
	title->setPosition(ccp(winSize.width / 2, winSize.height / 2 + 20));
	this->addChild(title);

	CCLabelTTF *a = CCLabelTTF::create("1", "fonts/Marker Felt.ttf", 32);
	a->setColor(ccc3(0, 0, 0));
	a->setPosition(ccp(winSize.width / 2 - 64, winSize.height / 2 - 30));
	this->addChild(a);

	int RankScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("Rank1");
	char buf1[100] = { 0, };
	sprintf(buf1, "%d", RankScore);
	CCLabelTTF *Rank1 = CCLabelTTF::create(buf1, "fonts/Marker Felt.ttf", 32);
	Rank1->setColor(ccc3(0, 0, 0));
	Rank1->setPosition(ccp(winSize.width / 2 + 64, winSize.height / 2 - 30));
	this->addChild(Rank1);

	CCLabelTTF *b = CCLabelTTF::create("2", "fonts/Marker Felt.ttf", 32);
	b->setColor(ccc3(0, 0, 0));
	b->setPosition(ccp(winSize.width / 2 - 64, winSize.height / 2 - 60));
	this->addChild(b);

	RankScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("Rank2");
	char buf2[100] = { 0, };
	sprintf(buf2, "%d", RankScore);
	CCLabelTTF *Rank2 = CCLabelTTF::create(buf2, "fonts/Marker Felt.ttf", 32);
	Rank2->setColor(ccc3(0, 0, 0));
	Rank2->setPosition(ccp(winSize.width / 2 + 64, winSize.height / 2 - 60));
	this->addChild(Rank2);

	CCLabelTTF *c = CCLabelTTF::create("3", "fonts/Marker Felt.ttf", 32);
	c->setColor(ccc3(0, 0, 0));
	c->setPosition(ccp(winSize.width / 2 - 64, winSize.height / 2 - 90));
	this->addChild(c);

	RankScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("Rank3");
	char buf3[100] = { 0, };
	CCLabelTTF *Rank3 = CCLabelTTF::create(buf3, "fonts/Marker Felt.ttf", 32);
	Rank3->setColor(ccc3(0, 0, 0));
	Rank3->setPosition(ccp(winSize.width / 2 + 64, winSize.height / 2 - 90));
	this->addChild(Rank3);

	return true;
}

void RankingMenu::menuCloseCallback(CCObject* pSender)
{
	CCScene *mScene = MainScene::createScene();
	CCDirector::sharedDirector()->replaceScene(mScene);
}
