//
//  MainGameScene.cpp
//  CellPhone_Pang
//
//  Created by Min on 12. 11. 7..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

#include "MainGameScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include <math.h>

using namespace cocos2d;

int pan[7][7] = { 0, };
int pan1[7][7] = { 0, };
int resetSw = 0;
int Score = 0;
bool Start = false;
CCMenu *BlockPan;
CCSprite *Pannel;
CCMenuItem *block[7][7] = { 0, };
CCSize winSize;
CCSprite *TimeBar;
CCLabelTTF *ScoreTTF, *TimeTTF, *StartCountTTF;
int t, st = 3;

Scene *MainGameScene::scene()
{
	CCScene *scene = CCScene::create();
	MainGameScene *layer = MainGameScene::create();

	scene->addChild(layer);

	return scene;
}

bool MainGameScene::init()
{
	winSize = CCDirector::sharedDirector()->getWinSize();
	if (!CCLayer::init())
	{
		return false;
	}

	CCSprite *BackGround;
	BackGround = CCSprite::create("background.png");
	BackGround->setPosition(ccp(winSize.width / 2, winSize.height / 2));

	this->addChild(BackGround);

	ScoreTTF = CCLabelTTF::create("1", "fonts/Marker Felt.ttf", 32);
	ScoreTTF->setPosition(ccp(300, 400));
	ScoreTTF->setColor(ccColor3B(ccc3(0, 0, 0)));
	this->addChild(ScoreTTF);

	RefreshBlock();
	this->BlockSet();

	this->schedule(schedule_selector(MainGameScene::ScoreSet), 0.01);
	this->schedule(schedule_selector(MainGameScene::BlockCrashTest), 0.2);
	this->schedule(schedule_selector(MainGameScene::TimeCheck), 0.5);


	this->schedule(schedule_selector(MainGameScene::StartCount), 1);

	//cout << "Start\n";

	return true;
}

void MainGameScene::CrashAnim(CCPoint pos)
{

	// 애니메이팅이 들어 있는 그림파일을 텍스쳐로 로드
	CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("attackeffect.png");

	// CCSpriteFrame을 만드는데 텍스쳐 파일 속의 애니메이션(각각의 그림)을 Rect로 뜯어서 SpriteFrame에 삽입
	CCSpriteFrame *frame0 = CCSpriteFrame::createWithTexture(texture, CCRectMake(60 * 0, 60 * 0, 60, 60));
	CCSpriteFrame *frame1 = CCSpriteFrame::createWithTexture(texture, CCRectMake(60 * 1, 60 * 0, 60, 60));
	CCSpriteFrame *frame2 = CCSpriteFrame::createWithTexture(texture, CCRectMake(60 * 2, 60 * 0, 60, 60));
	CCSpriteFrame *frame3 = CCSpriteFrame::createWithTexture(texture, CCRectMake(60 * 3, 60 * 0, 60, 60));
	CCSpriteFrame *frame4 = CCSpriteFrame::createWithTexture(texture, CCRectMake(60 * 4, 60 * 0, 60, 60));


	//CCSpriteFrame을 만드는데 텍스쳐 파일 속의 애니메이션(각각의 그림)을 Rect로 뜯어서 SpriteFrame에 삽입
	CCSprite* sprite = CCSprite::createWithSpriteFrame(frame0);
	sprite->setPosition(pos);
	addChild(sprite);

	CCAnimation* animation = CCAnimation::create();
	animation->CCAnimation::setDelayPerUnit(0.1);
	animation->addSpriteFrame(frame0);
	animation->addSpriteFrame(frame1);
	animation->addSpriteFrame(frame2);
	animation->addSpriteFrame(frame3);
	animation->addSpriteFrame(frame4);

	CCAnimate *animate = CCAnimate::create(animation);
	animate->setDuration(0.2);

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(MainGameScene::SpriteAnimateFinished, this));

	//액션을 실행!
	sprite->runAction(CCSequence::create(animate, actionDone, NULL));
}

void MainGameScene::SpriteAnimateFinished(cocos2d::Ref* sender)
{
	CCSprite *pSprite = (CCSprite*)sender;
	this->removeChild(pSprite, true);
}

void MainGameScene::StartCount(float delta)
{
	if (Start == false && winSize.width / 2 - (t * 5) >= (-160)){
		this->removeChild(StartCountTTF, true);
		char buf[100] = { 0, };
		sprintf(buf, "%d", st);
		StartCountTTF = CCLabelTTF::create(buf, "fonts/Marker Felt.ttf", 30);
		StartCountTTF->setColor(ccColor3B(ccc3(0, 0, 0)));
		StartCountTTF->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(StartCountTTF);
	}
	if (st == 0){
		Start = true;
		this->removeChild(StartCountTTF, true);
	}
	st--;
}

void MainGameScene::BlockSet()
{

	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++){
			switch (pan[i][j]) {
			case 1:
				block[i][j] = MenuItemImage::create("1.png",
					"1.png", CC_CALLBACK_1(MainGameScene::BlockTouch, this));
				break;
			case 2:
				block[i][j] = MenuItemImage::create("2.png",
					"2.png", CC_CALLBACK_1(MainGameScene::BlockTouch, this));
				break;
			case 3:
				block[i][j] = MenuItemImage::create("3.png",
					"3.png", CC_CALLBACK_1(MainGameScene::BlockTouch, this));
				break;
			case 4:
				block[i][j] = MenuItemImage::create("4.png",
					"4.png", CC_CALLBACK_1(MainGameScene::BlockTouch, this));
				break;
			case 5:
				block[i][j] = MenuItemImage::create("5.png",
					"5.png", CC_CALLBACK_1(MainGameScene::BlockTouch, this));
				break;
			case 6:
				block[i][j] = MenuItemImage::create("6.png",
					"6.png", CC_CALLBACK_1(MainGameScene::BlockTouch, this));
				break;

			default:
				break;
			}
		}
	}

	BlockPan = CCMenu::create();

	BlockPan->setPosition(ccp(0, 0));

	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++){
			block[i][j]->setPosition(Vec2((winSize.width / 7) * (j + 1) - 20, 400 - i * 50));
		}
	}

	int c = 1;
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++){
			block[i][j]->setTag(c);
			c++;
		}
	}

	c = 1;
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++){
			BlockPan->addChild(block[i][j], c);
			c++;
		}
	}

	this->addChild(BlockPan);
}

void MainGameScene::ScoreSet(float delta)
{
	this->removeChild(ScoreTTF, true);
	char buf[100] = { 0, };
	sprintf(buf, "%d", Score);

	ScoreTTF = CCLabelTTF::create(buf, "", 30);
	if (Score<100){
		ScoreTTF->setPosition(ccp(310, 450));
	}
	else if (Score<1000){
		ScoreTTF->setPosition(ccp(290, 450));
	}
	else if (Score<10000){
		ScoreTTF->setPosition(ccp(280, 450));
	}
	else if (Score<100000){ //설마 있을까?
		ScoreTTF->setPosition(ccp(270, 450));
	}
	ScoreTTF->setColor(ccColor3B(ccc3(0, 0, 0)));
	this->addChild(ScoreTTF);
}

void BlockCrash(int y, int x, int a)
{
	pan[y][x] = 0;
	if (pan[y + 1][x] == a&&y != 6){
		pan1[y][x] = pan[y][x];
		BlockCrash(y + 1, x, a);
	}
	if (pan[y - 1][x] == a&&y != 0){
		pan1[y][x] = pan[y][x];
		BlockCrash(y - 1, x, a);
	}
	if (pan[y][x + 1] == a&&x != 6){
		pan1[y][x] = pan[y][x];
		BlockCrash(y, x + 1, a);
	}
	if (pan[y][x - 1] == a&&x != 0){
		pan1[y][x] = pan[y][x];
		BlockCrash(y, x - 1, a);
	}
}

void MainGameScene::BlockCrashGo(int blockcode)
{
	int i, j;

	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++){
			if (pan[i][j] == 0){
				block[i][j]->setVisible(false);
			}
		}
	}

	for (i = 0; i<7; i++){
		for (j = 0; j<7; j++){
			if (pan[i][j] == 0){
				Score += 50;
				pan[i][j] = 9;
			}
		}
	}

}

void MainGameScene::AnimSet()
{
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 7; j++){
			if (pan[i][j] == 0){
				CrashAnim(ccp((winSize.width / 7) * (j+1) - 20, 400 - 50 * i));
			}
		}
	}
}

void MainGameScene::BlockTouch(cocos2d::Ref* pSender)
{
	CCMenuItem *item = (CCMenuItem *)pSender;
	int blockid = 0;
	blockid = item->getTag();
	//cout << (blockid-1)/7 << " " << (blockid-1)%7 << "\n";

	if (pan[(blockid - 1) / 7][(blockid - 1) % 7]<0 && winSize.width / 2 - (t * 5) >= (-160) && Start){
		BlockCrash((blockid - 1) / 7, (blockid - 1) % 7, pan[(blockid - 1) / 7][(blockid - 1) % 7]);
		AnimSet();
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("balls_break2.ogg");

		BlockCrashGo(blockid);
		//cout << Score << "\n";
	}
	else if (t<65){
		t += 3;
	}
}

void MainGameScene::BlockCrashTest(float delta)
{
	resetSw = 0;
	do {
		//ㅣ자 패턴
		for (int i = 1; i<6; i++){
			for (int j = 0; j<7; j++){
				if (abs(pan[i - 1][j]) == abs(pan[i][j]) && abs(pan[i][j]) == abs(pan[i + 1][j]) && pan[i][j] != 0 && pan[i][j] != 9){
					if (pan[i - 1][j]>0) pan[i - 1][j] *= -1;
					if (pan[i][j]>0) pan[i][j] *= -1;
					if (pan[i + 1][j]>0) pan[i + 1][j] *= -1;
					resetSw = 1;
				}
			}
		}

		//ㅡ자 패턴
		for (int i = 0; i<7; i++){
			for (int j = 1; j<6; j++){
				if (abs(pan[i][j - 1]) == abs(pan[i][j]) && abs(pan[i][j]) == abs(pan[i][j + 1]) && pan[i][j] != 0 && pan[i][j] != 9){
					if (pan[i][j - 1]>0) pan[i][j - 1] *= -1;
					if (pan[i][j]>0) pan[i][j] *= -1;
					if (pan[i][j + 1]>0) pan[i][j + 1] *= -1;
					resetSw = 1;
				}
			}
		}

		//거꾸로 기역자 패턴
		for (int i = 0; i<6; i++){
			for (int j = 0; j<6; j++){
				if (abs(pan[i][j + 1]) == abs(pan[i][j]) && abs(pan[i][j]) == abs(pan[i + 1][j]) && pan[i][j] != 0 && pan[i][j] != 9){
					if (pan[i][j + 1]>0)
						pan[i][j + 1] *= -1;
					if (pan[i][j]>0)
						pan[i][j] *= -1;
					if (pan[i + 1][j]>0)
						pan[i + 1][j] *= -1;
					resetSw = 1;
				}
			}
		}

		//ㄱ자 패턴
		for (int i = 0; i<6; i++){
			for (int j = 1; j<7; j++){
				if (abs(pan[i][j - 1]) == abs(pan[i][j]) && abs(pan[i][j]) == abs(pan[i + 1][j]) && pan[i][j] != 0 && pan[i][j] != 9){
					if (pan[i][j - 1]>0) pan[i][j - 1] *= -1;
					if (pan[i][j]>0) pan[i][j] *= -1;
					if (pan[i + 1][j]>0) pan[i + 1][j] *= -1;
					resetSw = 1;
				}
			}
		}

		//ㄴ자 패턴
		for (int i = 1; i<7; i++){
			for (int j = 0; j<6; j++){
				if (abs(pan[i][j + 1]) == abs(pan[i][j]) && abs(pan[i][j]) == abs(pan[i - 1][j]) && pan[i][j] != 0
					&& pan[i][j] != 9){
					if (pan[i][j + 1]>0) pan[i][j + 1] *= -1;
					if (pan[i][j]>0) pan[i][j] *= -1;
					if (pan[i - 1][j]>0) pan[i - 1][j] *= -1;
					resetSw = 1;
				}
			}
		}

		//거꾸로 ㄴ자 패턴
		for (int i = 1; i<7; i++){
			for (int j = 1; j<7; j++){
				if (abs(pan[i][j - 1]) == abs(pan[i][j]) && abs(pan[i][j]) == abs(pan[i - 1][j]) && pan[i][j] != 0
					&& pan[i][j] != 9){
					if (pan[i][j - 1]>0) pan[i][j - 1] *= -1;
					if (pan[i][j]>0) pan[i][j] *= -1;
					if (pan[i - 1][j]>0) pan[i - 1][j] *= -1;
					resetSw = 1;
				}
			}
		}
		if (resetSw == 0){
			RefreshBlock();
			this->removeChild(BlockPan, true);
			BlockPan = CCMenu::create(NULL);
			Score += 100;
			BlockSet();
		}
		else {
			for (int i = 0; i<7; i++){
				for (int j = 0; j<7; j++){
					if (pan[i][j + 1] <= 0){
						//cout << pan[i][j] << " ";
					}
					else {
						//cout << pan[i][j] << "  ";
					}
				}
				//cout << "\n";
			}
			//cout << "\n";
		}
	} while (resetSw == 0);
}

void MainGameScene::RefreshBlock()
{
	srand(time(NULL));

	for (int i = 0; i<7; i++){
		for (int j = 0; j<7; j++){
			pan[i][j] = rand() % 6 + 1;
			//cout << pan[i][j] << "  ";
		}
		//cout << "\n";
	}
	//cout << "\n";
}

void MainGameScene::TimeCheck(float delta) //게임시간은 60초 + 5초의 보너스타임
{
	if (Start){
		this->removeChild(TimeBar, true);
		if (t<65){
			t += 1;
		}
		TimeBar = CCSprite::create("timebar.png");
		TimeBar->setPosition(ccp(winSize.width / 2 - (t * 5), 35));
		this->addChild(TimeBar);

		this->removeChild(TimeTTF, true);
		char buf[100] = { 0, };
		int te;
		te = 65 - t;
		sprintf(buf, "%d", te);

		TimeTTF = CCLabelTTF::create(buf, "", 20);
		TimeTTF->setPosition(ccp(160, 35));
		TimeTTF->setColor(ccColor3B(ccc3(0, 0, 0)));
		this->addChild(TimeTTF);

		if (winSize.width / 2 - (t * 5)<(-160)){
			//cout << "GameSet\n";
			Start = false;
			CCUserDefault *user = CCUserDefault::sharedUserDefault();
			int Rank1 = 0, Rank2 = 0, Rank3 = 0, Rank4 = 0, Rank5 = 0;
			Rank1 = CCUserDefault::sharedUserDefault()->getIntegerForKey("Rank1");
			Rank2 = CCUserDefault::sharedUserDefault()->getIntegerForKey("Rank2");
			Rank3 = CCUserDefault::sharedUserDefault()->getIntegerForKey("Rank3");
			Rank4 = CCUserDefault::sharedUserDefault()->getIntegerForKey("Rank4");
			Rank5 = CCUserDefault::sharedUserDefault()->getIntegerForKey("Rank5");

			int i;
			for (i = 0; i<5; i++) {
				if (Score >= Rank1){
					user->setIntegerForKey("Rank2", Rank1);
					user->setIntegerForKey("Rank3", Rank2);
					user->setIntegerForKey("Rank4", Rank3);
					user->setIntegerForKey("Rank5", Rank4);
					user->setIntegerForKey("Rank1", Score);
				}
				else if (Score >= Rank2){
					user->setIntegerForKey("Rank3", Rank2);
					user->setIntegerForKey("Rank4", Rank3);
					user->setIntegerForKey("Rank5", Rank4);
					user->setIntegerForKey("Rank2", Score);
				}
				else if (Score >= Rank3){
					user->setIntegerForKey("Rank4", Rank3);
					user->setIntegerForKey("Rank5", Rank4);
					user->setIntegerForKey("Rank3", Score);
				}
				else if (Score >= Rank4){
					user->setIntegerForKey("Rank5", Rank4);
					user->setIntegerForKey("Rank4", Score);
				}
				else if (Score >= Rank5){
					user->setIntegerForKey("Rank5", Score);
				}
			}
		}
	}
	else if (st <= -4){
		this->removeChild(Pannel, true);
		Pannel = CCSprite::create("timeup.png");
		Pannel->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		this->addChild(Pannel);

		CCMenu *MenuMain = CCMenu::create(NULL); //메뉴생성

		//메뉴아이템 추가
		CCMenuItem *item1 = CCMenuItemImage::create("back.png",
			"back.png", this, menu_selector(MainGameScene::CloseCallback));
		MenuMain->setPosition(ccp(winSize.width / 2, winSize.height / 2 - 40));

		MenuMain->addChild(item1, 1); //메뉴에 아이템 붙이기
		this->addChild(MenuMain, 1); //메뉴를 레이어에 추가
	}
}

void MainGameScene::CloseCallback(cocos2d::Ref* pSender)
{
	t = 1;
	st = 3;
	//score=NULL;
	CCScene *gScene = MainScene::createScene();
	CCDirector::sharedDirector()->replaceScene(gScene);
}
