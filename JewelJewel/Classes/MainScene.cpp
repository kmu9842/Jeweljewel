//
//  MainScene.cpp
//  jewels
//
//  Created by Min on 12. 11. 15..
//
//

#include "MainScene.h"
#include "RankingMenu.h"
USING_NS_CC; //using namespace cocos2d

Scene *MainScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MainScene::init()
{
	CCSize winSize = Director::getInstance()->getVisibleSize();
	if (!CCLayer::init())
	{
		return false;
	}
	auto BackGround = Sprite::create("backg.png");
	BackGround->setPosition(ccp(winSize.width / 2, winSize.height / 2)); //위치지정
	this->addChild(BackGround);

	CCMenu *MenuMain = CCMenu::create(NULL); //메뉴생성
	CCMenu *MenuMain1 = CCMenu::create(NULL); //메뉴생성
	CCMenu *MenuMain2 = CCMenu::create(NULL); //메뉴생성

	//메뉴아이템 추가
	CCMenuItem *item1 = CCMenuItemImage::create("start.png",
		"start.png",
		this,
		menu_selector(MainScene::menuCloseCallback));
	CCMenuItem *item2 = CCMenuItemImage::create("rank.png",
		"rank.png",
		this,
		menu_selector(MainScene::RankCloseCallback));

	CCMenuItem *item3 = CCMenuItemImage::create("create.png",
		"create.png",
		this,
		menu_selector(MainScene::CreaterMenuCallback));


	MenuMain->addChild(item1, 1); //메뉴에 아이템 붙이기
	MenuMain1->addChild(item2, 2);
	MenuMain2->addChild(item3, 3);

	MenuMain->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 20));
	MenuMain1->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 90));
	MenuMain2->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 160));

	this->addChild(MenuMain, 1);
	this->addChild(MenuMain1, 2);
	this->addChild(MenuMain2, 3);//메뉴를 레이어에 추가

	CCUserDefault* user = CCUserDefault::sharedUserDefault();
	int SaveSw = CCUserDefault::sharedUserDefault()->getIntegerForKey("SaveMake");
	if (SaveSw == 0){
		user->setIntegerForKey("SaveMake", 1);
		user->setIntegerForKey("Rank1", 0);
		user->setIntegerForKey("Rank2", 0);
		user->setIntegerForKey("Rank3", 0);
		user->setIntegerForKey("Rank4", 0);
		user->setIntegerForKey("Rank5", 0);
	}

	return true;
}

//메뉴 효과
void MainScene::menuCloseCallback(CCObject* pSender)
{
	CCScene *gScene = MainGameScene::scene();
	CCDirector::sharedDirector()->replaceScene(gScene);
}

void MainScene::CreaterMenuCallback(CCObject* pSender)
{
	/*CCScene *cScene = CreaterMenu::scene();
	CCDirector::sharedDirector()->replaceScene(cScene);*/
}

void MainScene::RankCloseCallback(CCObject* pSender)
{
	CCScene *rScene = RankingMenu::scene();
	CCDirector::sharedDirector()->replaceScene(rScene);
}
