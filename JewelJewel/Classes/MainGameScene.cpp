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
CCMenuItem *block1, *block2, *block3, *block4, *block5, *block6, *block7,
*block8, *block9, *block10, *block11, *block12, *block13, *block14,
*block15, *block16, *block17, *block18, *block19, *block20, *block21,
*block22, *block23, *block24, *block25, *block26, *block27, *block28,
*block29, *block30, *block31, *block32, *block33, *block34, *block35,
*block36, *block37, *block38, *block39, *block40, *block41, *block42,
*block43, *block44, *block45, *block46, *block47, *block48, *block49;
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
	switch (pan[0][0]) {
	case 1:
		block1 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block1 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block1 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block1 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block1 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block1 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[0][1]) {
	case 1:
		block2 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block2 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block2 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block2 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block2 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block2 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[0][2]) {
	case 1:
		block3 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block3 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block3 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block3 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block3 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block3 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[0][3]) {
	case 1:
		block4 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block4 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block4 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block4 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block4 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block4 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[0][4]) {
	case 1:
		block5 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block5 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block5 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block5 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block5 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block5 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[0][5]) {
	case 1:
		block6 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block6 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block6 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block6 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block6 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block6 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[0][6]) {
	case 1:
		block7 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block7 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block7 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block7 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block7 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block7 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}

	switch (pan[1][0]) {
	case 1:
		block8 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block8 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block8 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block8 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block8 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block8 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[1][1]) {
	case 1:
		block9 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block9 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block9 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block9 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block9 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block9 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[1][2]) {
	case 1:
		block10 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block10 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block10 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block10 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block10 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block10 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[1][3]) {
	case 1:
		block11 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block11 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block11 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block11 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block11 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block11 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[1][4]) {
	case 1:
		block12 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block12 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block12 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block12 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block12 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block12 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[1][5]) {
	case 1:
		block13 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block13 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block13 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block13 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block13 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block13 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[1][6]) {
	case 1:
		block14 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block14 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block14 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block14 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block14 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block14 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}

	switch (pan[2][0]) {
	case 1:
		block15 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block15 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block15 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block15 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block15 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block15 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[2][1]) {
	case 1:
		block16 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block16 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block16 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block16 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block16 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block16 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[2][2]) {
	case 1:
		block17 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block17 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block17 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block17 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block17 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block17 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[2][3]) {
	case 1:
		block18 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block18 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block18 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block18 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block18 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block18 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[2][4]) {
	case 1:
		block19 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block19 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block19 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block19 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block19 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block19 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[2][5]) {
	case 1:
		block20 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block20 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block20 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block20 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block20 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block20 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[2][6]) {
	case 1:
		block21 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block21 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block21 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block21 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block21 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block21 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}

	switch (pan[3][0]) {
	case 1:
		block22 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block22 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block22 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block22 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block22 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block22 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[3][1]) {
	case 1:
		block23 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block23 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block23 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block23 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block23 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block23 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[3][2]) {
	case 1:
		block24 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block24 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block24 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block24 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block24 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block24 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[3][3]) {
	case 1:
		block25 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block25 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block25 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block25 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block25 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block25 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[3][4]) {
	case 1:
		block26 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block26 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block26 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block26 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block26 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block26 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[3][5]) {
	case 1:
		block27 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block27 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block27 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block27 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block27 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block27 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[3][6]) {
	case 1:
		block28 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block28 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block28 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block28 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block28 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block28 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}

	switch (pan[4][0]) {
	case 1:
		block29 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block29 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block29 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block29 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block29 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block29 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[4][1]) {
	case 1:
		block30 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block30 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block30 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block30 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block30 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block30 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[4][2]) {
	case 1:
		block31 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block31 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block31 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block31 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block31 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block31 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[4][3]) {
	case 1:
		block32 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block32 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block32 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block32 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block32 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block32 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[4][4]) {
	case 1:
		block33 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block33 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block33 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block33 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block33 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block33 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[4][5]) {
	case 1:
		block34 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block34 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block34 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block34 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block34 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block34 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[4][6]) {
	case 1:
		block35 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block35 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block35 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block35 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block35 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block35 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}

	switch (pan[5][0]) {
	case 1:
		block36 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block36 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block36 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block36 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block36 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block36 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[5][1]) {
	case 1:
		block37 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block37 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block37 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block37 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block37 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block37 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[5][2]) {
	case 1:
		block38 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block38 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block38 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block38 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block38 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block38 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[5][3]) {
	case 1:
		block39 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block39 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block39 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block39 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block39 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block39 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[5][4]) {
	case 1:
		block40 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block40 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block40 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block40 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block40 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block40 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[5][5]) {
	case 1:
		block41 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block41 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block41 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block41 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block41 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block41 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[5][6]) {
	case 1:
		block42 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block42 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block42 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block42 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block42 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block42 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}

	switch (pan[6][0]) {
	case 1:
		block43 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block43 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block43 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block43 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block43 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block43 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[6][1]) {
	case 1:
		block44 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block44 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block44 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block44 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block44 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block44 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[6][2]) {
	case 1:
		block45 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block45 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block45 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block45 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block45 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block45 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[6][3]) {
	case 1:
		block46 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block46 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block46 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block46 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block46 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block46 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[6][4]) {
	case 1:
		block47 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block47 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block47 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block47 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block47 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block47 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[6][5]) {
	case 1:
		block48 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 2:
		block48 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 3:
		block48 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 4:
		block48 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 5:
		block48 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	case 6:
		block48 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		break;

	default:
		break;
	}
	switch (pan[6][6]) {
	case 1:
		block49 = CCMenuItemImage::create("1.png",
			"1.png", this, menu_selector(MainGameScene::BlockTouch));
		//cout << "ok\n";
		break;

	case 2:
		block49 = CCMenuItemImage::create("2.png",
			"2.png", this, menu_selector(MainGameScene::BlockTouch));
		//cout << "ok\n";
		break;

	case 3:
		block49 = CCMenuItemImage::create("3.png",
			"3.png", this, menu_selector(MainGameScene::BlockTouch));
		//cout << "ok\n";
		break;

	case 4:
		block49 = CCMenuItemImage::create("4.png",
			"4.png", this, menu_selector(MainGameScene::BlockTouch));
		//cout << "ok\n";
		break;

	case 5:
		block49 = CCMenuItemImage::create("5.png",
			"5.png", this, menu_selector(MainGameScene::BlockTouch));
		//cout << "ok\n";
		break;

	case 6:
		block49 = CCMenuItemImage::create("6.png",
			"6.png", this, menu_selector(MainGameScene::BlockTouch));
		//cout << "ok\n";
		break;

	default:
		break;
	}
	BlockPan = CCMenu::create(NULL);

	//cout << "blocksetgo\n";

	BlockPan->setPosition(ccp(0, 0));

	block1->setPosition(ccp((int)(winSize.width / 7) - 20, (int)(400)));
	block2->setPosition(ccp((int)(winSize.width / 7) * 2 - 20, (int)(400)));
	block3->setPosition(ccp((int)(winSize.width / 7) * 3 - 20, (int)(400)));
	block4->setPosition(ccp((int)(winSize.width / 7) * 4 - 20, (int)(400)));
	block5->setPosition(ccp((int)(winSize.width / 7) * 5 - 20, (int)(400)));
	block6->setPosition(ccp((int)(winSize.width / 7) * 6 - 20, (int)(400)));
	block7->setPosition(ccp((int)(winSize.width / 7) * 7 - 20, (int)(400)));

	block8->setPosition(ccp((int)(winSize.width / 7) - 20, (int)(350)));
	block9->setPosition(ccp((int)(winSize.width / 7) * 2 - 20, (int)(350)));
	block10->setPosition(ccp((int)(winSize.width / 7) * 3 - 20, (int)(350)));
	block11->setPosition(ccp((int)(winSize.width / 7) * 4 - 20, (int)(350)));
	block12->setPosition(ccp((int)(winSize.width / 7) * 5 - 20, (int)(350)));
	block13->setPosition(ccp((int)(winSize.width / 7) * 6 - 20, (int)(350)));
	block14->setPosition(ccp((int)(winSize.width / 7) * 7 - 20, (int)(350)));

	block15->setPosition(ccp((int)(winSize.width / 7) - 20, (int)(300)));
	block16->setPosition(ccp((int)(winSize.width / 7) * 2 - 20, (int)(300)));
	block17->setPosition(ccp((int)(winSize.width / 7) * 3 - 20, (int)(300)));
	block18->setPosition(ccp((int)(winSize.width / 7) * 4 - 20, (int)(300)));
	block19->setPosition(ccp((int)(winSize.width / 7) * 5 - 20, (int)(300)));
	block20->setPosition(ccp((int)(winSize.width / 7) * 6 - 20, (int)(300)));
	block21->setPosition(ccp((int)(winSize.width / 7) * 7 - 20, (int)(300)));

	block22->setPosition(ccp((int)(winSize.width / 7) - 20, (int)(250)));
	block23->setPosition(ccp((int)(winSize.width / 7) * 2 - 20, (int)(250)));
	block24->setPosition(ccp((int)(winSize.width / 7) * 3 - 20, (int)(250)));
	block25->setPosition(ccp((int)(winSize.width / 7) * 4 - 20, (int)(250)));
	block26->setPosition(ccp((int)(winSize.width / 7) * 5 - 20, (int)(250)));
	block27->setPosition(ccp((int)(winSize.width / 7) * 6 - 20, (int)(250)));
	block28->setPosition(ccp((int)(winSize.width / 7) * 7 - 20, (int)(250)));

	block29->setPosition(ccp((int)(winSize.width / 7) - 20, (int)(200)));
	block30->setPosition(ccp((int)(winSize.width / 7) * 2 - 20, (int)(200)));
	block31->setPosition(ccp((int)(winSize.width / 7) * 3 - 20, (int)(200)));
	block32->setPosition(ccp((int)(winSize.width / 7) * 4 - 20, (int)(200)));
	block33->setPosition(ccp((int)(winSize.width / 7) * 5 - 20, (int)(200)));
	block34->setPosition(ccp((int)(winSize.width / 7) * 6 - 20, (int)(200)));
	block35->setPosition(ccp((int)(winSize.width / 7) * 7 - 20, (int)(200)));

	block36->setPosition(ccp((int)(winSize.width / 7) - 20, (int)(150)));
	block37->setPosition(ccp((int)(winSize.width / 7) * 2 - 20, (int)(150)));
	block38->setPosition(ccp((int)(winSize.width / 7) * 3 - 20, (int)(150)));
	block39->setPosition(ccp((int)(winSize.width / 7) * 4 - 20, (int)(150)));
	block40->setPosition(ccp((int)(winSize.width / 7) * 5 - 20, (int)(150)));
	block41->setPosition(ccp((int)(winSize.width / 7) * 6 - 20, (int)(150)));
	block42->setPosition(ccp((int)(winSize.width / 7) * 7 - 20, (int)(150)));

	block43->setPosition(ccp((int)(winSize.width / 7) - 20, (int)(100)));
	block44->setPosition(ccp((int)(winSize.width / 7) * 2 - 20, (int)(100)));
	block45->setPosition(ccp((int)(winSize.width / 7) * 3 - 20, (int)(100)));
	block46->setPosition(ccp((int)(winSize.width / 7) * 4 - 20, (int)(100)));
	block47->setPosition(ccp((int)(winSize.width / 7) * 5 - 20, (int)(100)));
	block48->setPosition(ccp((int)(winSize.width / 7) * 6 - 20, (int)(100)));
	block49->setPosition(ccp((int)(winSize.width / 7) * 7 - 20, (int)(100)));

	block1->setTag(1);
	block2->setTag(2);
	block3->setTag(3);
	block4->setTag(4);
	block5->setTag(5);
	block6->setTag(6);
	block7->setTag(7);

	block8->setTag(8);
	block9->setTag(9);
	block10->setTag(10);
	block11->setTag(11);
	block12->setTag(12);
	block13->setTag(13);
	block14->setTag(14);

	block15->setTag(15);
	block16->setTag(16);
	block17->setTag(17);
	block18->setTag(18);
	block19->setTag(19);
	block20->setTag(20);
	block21->setTag(21);

	block22->setTag(22);
	block23->setTag(23);
	block24->setTag(24);
	block25->setTag(25);
	block26->setTag(26);
	block27->setTag(27);
	block28->setTag(28);

	block29->setTag(29);
	block30->setTag(30);
	block31->setTag(31);
	block32->setTag(32);
	block33->setTag(33);
	block34->setTag(34);
	block35->setTag(35);

	block36->setTag(36);
	block37->setTag(37);
	block38->setTag(38);
	block39->setTag(39);
	block40->setTag(40);
	block41->setTag(41);
	block42->setTag(42);

	block43->setTag(43);
	block44->setTag(44);
	block45->setTag(45);
	block46->setTag(46);
	block47->setTag(47);
	block48->setTag(48);
	block49->setTag(48);

	BlockPan->addChild(block1, 1);
	BlockPan->addChild(block2, 2);
	BlockPan->addChild(block3, 3);
	BlockPan->addChild(block4, 4);
	BlockPan->addChild(block5, 5);
	BlockPan->addChild(block6, 6);
	BlockPan->addChild(block7, 7);

	BlockPan->addChild(block8, 8);
	BlockPan->addChild(block9, 9);
	BlockPan->addChild(block10, 10);
	BlockPan->addChild(block11, 11);
	BlockPan->addChild(block12, 12);
	BlockPan->addChild(block13, 13);
	BlockPan->addChild(block14, 14);

	BlockPan->addChild(block15, 15);
	BlockPan->addChild(block16, 16);
	BlockPan->addChild(block17, 17);
	BlockPan->addChild(block18, 18);
	BlockPan->addChild(block19, 19);
	BlockPan->addChild(block20, 20);
	BlockPan->addChild(block21, 21);

	BlockPan->addChild(block22, 22);
	BlockPan->addChild(block23, 23);
	BlockPan->addChild(block24, 24);
	BlockPan->addChild(block25, 25);
	BlockPan->addChild(block26, 26);
	BlockPan->addChild(block27, 27);
	BlockPan->addChild(block28, 28);

	BlockPan->addChild(block29, 28);
	BlockPan->addChild(block30, 29);
	BlockPan->addChild(block31, 30);
	BlockPan->addChild(block32, 31);
	BlockPan->addChild(block33, 32);
	BlockPan->addChild(block34, 33);
	BlockPan->addChild(block35, 34);

	BlockPan->addChild(block36, 28);
	BlockPan->addChild(block37, 29);
	BlockPan->addChild(block38, 30);
	BlockPan->addChild(block39, 31);
	BlockPan->addChild(block40, 32);
	BlockPan->addChild(block41, 33);
	BlockPan->addChild(block42, 34);

	BlockPan->addChild(block43, 28);
	BlockPan->addChild(block44, 29);
	BlockPan->addChild(block45, 30);
	BlockPan->addChild(block46, 31);
	BlockPan->addChild(block47, 32);
	BlockPan->addChild(block48, 33);
	BlockPan->addChild(block49, 34);

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

	if (pan[0][0] == 0){
		BlockPan->removeChild(block1, true);
	}
	if (pan[0][1] == 0){
		CrashAnim(ccp(winSize.width / 7 * 2 - 20, 400));
		BlockPan->removeChild(block2, true);
	}
	if (pan[0][2] == 0){
		//CrashAnim(ccp(winSize.width/7*3-20,400));
		BlockPan->removeChild(block3, true);
	}
	if (pan[0][3] == 0){
		//CrashAnim(ccp(winSize.width/7*4-20,400));
		BlockPan->removeChild(block4, true);
	}
	if (pan[0][4] == 0){
		//CrashAnim(ccp(winSize.width/7*5-20,400));
		BlockPan->removeChild(block5, true);
	}
	if (pan[0][5] == 0){
		//CrashAnim(ccp(winSize.width/7*6-20,400));
		BlockPan->removeChild(block6, true);
	}
	if (pan[0][6] == 0){
		//CrashAnim(ccp(winSize.width/7*7-20,400));
		BlockPan->removeChild(block7, true);
	}

	if (pan[1][0] == 0){
		//CrashAnim(ccp(winSize.width/7-20,350));
		BlockPan->removeChild(block8, true);
	}
	if (pan[1][1] == 0){
		//CrashAnim(ccp(winSize.width/7*2-20,350));
		BlockPan->removeChild(block9, true);
	}
	if (pan[1][2] == 0){
		//CrashAnim(ccp(winSize.width/7*3-20,350));
		BlockPan->removeChild(block10, true);
	}
	if (pan[1][3] == 0){
		//CrashAnim(ccp(winSize.width/7*4-20,350));
		BlockPan->removeChild(block11, true);
	}
	if (pan[1][4] == 0){
		//CrashAnim(ccp(winSize.width/7*5-20,350));
		BlockPan->removeChild(block12, true);
	}
	if (pan[1][5] == 0){
		//CrashAnim(ccp(winSize.width/7*6-20,350));
		BlockPan->removeChild(block13, true);
	}
	if (pan[1][6] == 0){
		//CrashAnim(ccp(winSize.width/7*7-20,350));
		BlockPan->removeChild(block14, true);
	}

	if (pan[2][0] == 0){
		//CrashAnim(ccp(winSize.width/7-20,300));
		BlockPan->removeChild(block15, true);
	}
	if (pan[2][1] == 0){
		//CrashAnim(ccp(winSize.width/7*2-20,300));
		BlockPan->removeChild(block16, true);
	}
	if (pan[2][2] == 0){
		//CrashAnim(ccp(winSize.width/7*3-20,300));
		BlockPan->removeChild(block17, true);
	}
	if (pan[2][3] == 0){
		//CrashAnim(ccp(winSize.width/7*4-20,300));
		BlockPan->removeChild(block18, true);
	}
	if (pan[2][4] == 0){
		//CrashAnim(ccp(winSize.width/7*5-20,300));
		BlockPan->removeChild(block19, true);
	}
	if (pan[2][5] == 0){
		//CrashAnim(ccp(winSize.width/7*6-20,300));
		BlockPan->removeChild(block20, true);
	}
	if (pan[2][6] == 0){
		//CrashAnim(ccp(winSize.width/7*7-20,300));
		BlockPan->removeChild(block21, true);
	}

	if (pan[3][0] == 0){
		//CrashAnim(ccp(winSize.width/7-20,250));
		BlockPan->removeChild(block22, true);
	}
	if (pan[3][1] == 0){
		//CrashAnim(ccp(winSize.width/7*2-20,250));
		BlockPan->removeChild(block23, true);
	}
	if (pan[3][2] == 0){
		//CrashAnim(ccp(winSize.width/7*3-20,250));
		BlockPan->removeChild(block24, true);
	}
	if (pan[3][3] == 0){
		//CrashAnim(ccp(winSize.width/7*4-20,250));
		BlockPan->removeChild(block25, true);
	}
	if (pan[3][4] == 0){
		//CrashAnim(ccp(winSize.width/7*5-20,250));
		BlockPan->removeChild(block26, true);
	}
	if (pan[3][5] == 0){
		//CrashAnim(ccp(winSize.width/7*6-20,250));
		BlockPan->removeChild(block27, true);
	}
	if (pan[3][6] == 0){
		//CrashAnim(ccp(winSize.width/7*7-20,250));
		BlockPan->removeChild(block28, true);
	}

	if (pan[4][0] == 0){
		//CrashAnim(ccp(winSize.width/7-20,200));
		BlockPan->removeChild(block29, true);
	}
	if (pan[4][1] == 0){
		//CrashAnim(ccp(winSize.width/7*2-20,200));
		BlockPan->removeChild(block30, true);
	}
	if (pan[4][2] == 0){
		//CrashAnim(ccp(winSize.width/7*3-20,200));
		BlockPan->removeChild(block31, true);
	}
	if (pan[4][3] == 0){
		//CrashAnim(ccp(winSize.width/7*4-20,200));
		BlockPan->removeChild(block32, true);
	}
	if (pan[4][4] == 0){
		//CrashAnim(ccp(winSize.width/7*5-20,200));
		BlockPan->removeChild(block33, true);
	}
	if (pan[4][5] == 0){
		//CrashAnim(ccp(winSize.width/7*6-20,200));
		BlockPan->removeChild(block34, true);
	}
	if (pan[4][6] == 0){
		//CrashAnim(ccp(winSize.width/7*7-20,200));
		BlockPan->removeChild(block35, true);
	}

	if (pan[5][0] == 0){
		//CrashAnim(ccp(winSize.width/7-20,150));
		BlockPan->removeChild(block36, true);
	}
	if (pan[5][1] == 0){
		//CrashAnim(ccp(winSize.width/7*2-20,150));
		BlockPan->removeChild(block37, true);
	}
	if (pan[5][2] == 0){
		//CrashAnim(ccp(winSize.width/7*3-20,150));
		BlockPan->removeChild(block38, true);
	}
	if (pan[5][3] == 0){
		//CrashAnim(ccp(winSize.width/7*4-20,150));
		BlockPan->removeChild(block39, true);
	}
	if (pan[5][4] == 0){
		//CrashAnim(ccp(winSize.width/7*5-20,150));
		BlockPan->removeChild(block40, true);
	}
	if (pan[5][5] == 0){
		//CrashAnim(ccp(winSize.width/7*6-20,150));
		BlockPan->removeChild(block41, true);
	}
	if (pan[5][6] == 0){
		//CrashAnim(ccp(winSize.width/7*7-20,150));
		BlockPan->removeChild(block42, true);
	}

	if (pan[6][0] == 0){
		//CrashAnim(ccp(winSize.width/7-20,100));
		BlockPan->removeChild(block43, true);
	}
	if (pan[6][1] == 0){
		//CrashAnim(ccp(winSize.width/7*2-20,100));
		BlockPan->removeChild(block44, true);
	}
	if (pan[6][2] == 0){
		//CrashAnim(ccp(winSize.width/7*3-20,100));
		BlockPan->removeChild(block45, true);
	}
	if (pan[6][3] == 0){
		//CrashAnim(ccp(winSize.width/7*4-20,100));
		BlockPan->removeChild(block46, true);
	}
	if (pan[6][4] == 0){
		//CrashAnim(ccp(winSize.width/7*5-20,100));
		BlockPan->removeChild(block47, true);
	}
	if (pan[6][5] == 0){
		//CrashAnim(ccp(winSize.width/7*6-20,100));
		BlockPan->removeChild(block48, true);
	}
	if (pan[6][6] == 0){
		//CrashAnim(ccp(winSize.width/7*7-20,100));
		BlockPan->removeChild(block49, true);
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
	if (pan[0][0] == 0){
		CrashAnim(ccp(winSize.width / 7 - 20, 400));
	}
	if (pan[0][1] == 0){
		CrashAnim(ccp(winSize.width / 7 * 2 - 20, 400));
	}
	if (pan[0][2] == 0){
		CrashAnim(ccp(winSize.width / 7 * 3 - 20, 400));
	}
	if (pan[0][3] == 0){
		CrashAnim(ccp(winSize.width / 7 * 4 - 20, 400));
	}
	if (pan[0][4] == 0){
		CrashAnim(ccp(winSize.width / 7 * 5 - 20, 400));
	}
	if (pan[0][5] == 0){
		CrashAnim(ccp(winSize.width / 7 * 6 - 20, 400));
	}
	if (pan[0][6] == 0){
		CrashAnim(ccp(winSize.width / 7 * 7 - 20, 400));
	}

	if (pan[1][0] == 0){
		CrashAnim(ccp(winSize.width / 7 - 20, 350));
	}
	if (pan[1][1] == 0){
		CrashAnim(ccp(winSize.width / 7 * 2 - 20, 350));
	}
	if (pan[1][2] == 0){
		CrashAnim(ccp(winSize.width / 7 * 3 - 20, 350));
	}
	if (pan[1][3] == 0){
		CrashAnim(ccp(winSize.width / 7 * 4 - 20, 350));
	}
	if (pan[1][4] == 0){
		CrashAnim(ccp(winSize.width / 7 * 5 - 20, 350));
	}
	if (pan[1][5] == 0){
		CrashAnim(ccp(winSize.width / 7 * 6 - 20, 350));
	}
	if (pan[1][6] == 0){
		CrashAnim(ccp(winSize.width / 7 * 7 - 20, 350));
	}

	if (pan[2][0] == 0){
		CrashAnim(ccp(winSize.width / 7 - 20, 300));
	}
	if (pan[2][1] == 0){
		CrashAnim(ccp(winSize.width / 7 * 2 - 20, 300));
	}
	if (pan[2][2] == 0){
		CrashAnim(ccp(winSize.width / 7 * 3 - 20, 300));
	}
	if (pan[2][3] == 0){
		CrashAnim(ccp(winSize.width / 7 * 4 - 20, 300));
	}
	if (pan[2][4] == 0){
		CrashAnim(ccp(winSize.width / 7 * 5 - 20, 300));
	}
	if (pan[2][5] == 0){
		CrashAnim(ccp(winSize.width / 7 * 6 - 20, 300));
	}
	if (pan[2][6] == 0){
		CrashAnim(ccp(winSize.width / 7 * 7 - 20, 300));
	}

	if (pan[3][0] == 0){
		CrashAnim(ccp(winSize.width / 7 - 20, 250));
	}
	if (pan[3][1] == 0){
		CrashAnim(ccp(winSize.width / 7 * 2 - 20, 250));
	}
	if (pan[3][2] == 0){
		CrashAnim(ccp(winSize.width / 7 * 3 - 20, 250));
	}
	if (pan[3][3] == 0){
		CrashAnim(ccp(winSize.width / 7 * 4 - 20, 250));
	}
	if (pan[3][4] == 0){
		CrashAnim(ccp(winSize.width / 7 * 5 - 20, 250));
	}
	if (pan[3][5] == 0){
		CrashAnim(ccp(winSize.width / 7 * 6 - 20, 250));
	}
	if (pan[3][6] == 0){
		CrashAnim(ccp(winSize.width / 7 * 7 - 20, 250));
	}

	if (pan[4][0] == 0){
		CrashAnim(ccp(winSize.width / 7 - 20, 200));
	}
	if (pan[4][1] == 0){
		CrashAnim(ccp(winSize.width / 7 * 2 - 20, 200));
	}
	if (pan[4][2] == 0){
		CrashAnim(ccp(winSize.width / 7 * 3 - 20, 200));
	}
	if (pan[4][3] == 0){
		CrashAnim(ccp(winSize.width / 7 * 4 - 20, 200));
	}
	if (pan[4][4] == 0){
		CrashAnim(ccp(winSize.width / 7 * 5 - 20, 200));
	}
	if (pan[4][5] == 0){
		CrashAnim(ccp(winSize.width / 7 * 6 - 20, 200));
	}
	if (pan[4][6] == 0){
		CrashAnim(ccp(winSize.width / 7 * 7 - 20, 200));
	}

	if (pan[5][0] == 0){
		CrashAnim(ccp(winSize.width / 7 - 20, 150));
	}
	if (pan[5][1] == 0){
		CrashAnim(ccp(winSize.width / 7 * 2 - 20, 150));
	}
	if (pan[5][2] == 0){
		CrashAnim(ccp(winSize.width / 7 * 3 - 20, 150));
	}
	if (pan[5][3] == 0){
		CrashAnim(ccp(winSize.width / 7 * 4 - 20, 150));
	}
	if (pan[5][4] == 0){
		CrashAnim(ccp(winSize.width / 7 * 5 - 20, 150));
	}
	if (pan[5][5] == 0){
		CrashAnim(ccp(winSize.width / 7 * 6 - 20, 150));
	}
	if (pan[5][6] == 0){
		CrashAnim(ccp(winSize.width / 7 * 7 - 20, 150));
	}

	if (pan[6][0] == 0){
		CrashAnim(ccp(winSize.width / 7 - 20, 100));
	}
	if (pan[6][1] == 0){
		CrashAnim(ccp(winSize.width / 7 * 2 - 20, 100));
	}
	if (pan[6][2] == 0){
		CrashAnim(ccp(winSize.width / 7 * 3 - 20, 100));
	}
	if (pan[6][3] == 0){
		CrashAnim(ccp(winSize.width / 7 * 4 - 20, 100));
	}
	if (pan[6][4] == 0){
		CrashAnim(ccp(winSize.width / 7 * 5 - 20, 100));
	}
	if (pan[6][5] == 0){
		CrashAnim(ccp(winSize.width / 7 * 6 - 20, 100));
	}
	if (pan[6][6] == 0){
		CrashAnim(ccp(winSize.width / 7 * 7 - 20, 100));
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
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("balls_break2.ogg");
		for (int i = 0; i<7; i++){
			for (int j = 0; j<7; j++){
				if (pan[i][j + 1]<0){
					//cout << pan[i][j] << " ";
				}
				else {
					//cout << pan[i][j] << "  ";
				}
			}
			//cout << "\n";
		}
		//cout << "\n";
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
