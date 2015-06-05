#include "HelloWorldScene.h"

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255))) //RGBA
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	selectTag[0] = 0;
	selectTag[1] = 0;
    
	/*
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/
	
	settingRandom();
	settingString();

	auto castSprite = Sprite::create("side.png");
	castSprite->setPosition(Vec2(visibleSize.width / 2,
								 visibleSize.height / 2));
	this->addChild(castSprite);

	castSprite2->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height / 2));
	this->addChild(castSprite2);
	castSprite2->setVisible(false);

	auto RightButton = MenuItemImage::create(
		"button1.png",
		"button1Select.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	RightButton->setTag(1);

	RightButton->setPosition(Vec2(
		origin.x + visibleSize.width - 16 - RightButton->getContentSize().width / 2,
		origin.y + 16 + RightButton->getContentSize().height / 2));

	auto LeftButton = MenuItemImage::create(
		"button2.png",
		"button2Select.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	LeftButton->setTag(2);

	LeftButton->setPosition(Vec2(
		origin.x + 16 + LeftButton->getContentSize().width / 2,
		origin.y + 16 + LeftButton->getContentSize().height / 2));

	auto SelectButton = MenuItemImage::create(
		"SelectButton.png",
		"SelectButtons.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	SelectButton->setTag(3);

	SelectButton->setPosition(Vec2(
		visibleSize.width / 2,
		16 + LeftButton->getContentSize().height / 2));

	auto menu = Menu::create(RightButton, LeftButton, SelectButton, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	TimeCount = Label::createWithTTF("0.0", "fonts/Marker Felt.ttf", 36);
	TimeCount->setTextColor(Color4B(0, 0, 0, 255));
	TimeCount->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 24));
	this->addChild(TimeCount, 1);
    
	this->schedule(schedule_selector(HelloWorld::update), 0.1);

    return true;
}

void HelloWorld::settingRandom(){
	int index = 0, rindex, tmp;

	srand((unsigned)time(NULL));
	for (int i = 0; i<stringIndex; i++) {
		alphabatArray[i] = i + 1;
	}

	while (index < stringIndex) {
		rindex = rand() % stringIndex;
		tmp = alphabatArray[index];
		alphabatArray[index] = alphabatArray[rindex];
		alphabatArray[rindex] = tmp;

		index++;
	}
}

void HelloWorld::settingString(){

	for (int i = 0; i<stringIndex; i++) {
		switch (alphabatArray[i])
		{
		case 1: alphabat[i] = Label::createWithTTF("A", "fonts/Marker Felt.ttf", 48); break;
		case 2: alphabat[i] = Label::createWithTTF("B", "fonts/Marker Felt.ttf", 48); break;
		case 3: alphabat[i] = Label::createWithTTF("C", "fonts/Marker Felt.ttf", 48); break;
		case 4: alphabat[i] = Label::createWithTTF("D", "fonts/Marker Felt.ttf", 48); break;
		case 5: alphabat[i] = Label::createWithTTF("E", "fonts/Marker Felt.ttf", 48); break;
		case 6: alphabat[i] = Label::createWithTTF("F", "fonts/Marker Felt.ttf", 48); break;
		case 7: alphabat[i] = Label::createWithTTF("G", "fonts/Marker Felt.ttf", 48); break;
		case 8: alphabat[i] = Label::createWithTTF("H", "fonts/Marker Felt.ttf", 48); break;
		case 9: alphabat[i] = Label::createWithTTF("I", "fonts/Marker Felt.ttf", 48); break;
		case 10: alphabat[i] = Label::createWithTTF("J", "fonts/Marker Felt.ttf", 48); break;
		case 11: alphabat[i] = Label::createWithTTF("K", "fonts/Marker Felt.ttf", 48); break;
		case 12: alphabat[i] = Label::createWithTTF("L", "fonts/Marker Felt.ttf", 48); break;
		case 13: alphabat[i] = Label::createWithTTF("M", "fonts/Marker Felt.ttf", 48); break;
		case 14: alphabat[i] = Label::createWithTTF("N", "fonts/Marker Felt.ttf", 48); break;
		case 15: alphabat[i] = Label::createWithTTF("O", "fonts/Marker Felt.ttf", 48); break;
		case 16: alphabat[i] = Label::createWithTTF("P", "fonts/Marker Felt.ttf", 48); break;
		case 17: alphabat[i] = Label::createWithTTF("Q", "fonts/Marker Felt.ttf", 48); break;
		case 18: alphabat[i] = Label::createWithTTF("R", "fonts/Marker Felt.ttf", 48); break;
		case 19: alphabat[i] = Label::createWithTTF("S", "fonts/Marker Felt.ttf", 48); break;
		case 20: alphabat[i] = Label::createWithTTF("T", "fonts/Marker Felt.ttf", 48); break;
		case 21: alphabat[i] = Label::createWithTTF("U", "fonts/Marker Felt.ttf", 48); break;
		case 22: alphabat[i] = Label::createWithTTF("V", "fonts/Marker Felt.ttf", 48); break;
		case 23: alphabat[i] = Label::createWithTTF("W", "fonts/Marker Felt.ttf", 48); break;
		case 24: alphabat[i] = Label::createWithTTF("X", "fonts/Marker Felt.ttf", 48); break;
		case 25: alphabat[i] = Label::createWithTTF("Y", "fonts/Marker Felt.ttf", 48); break;
		case 26: alphabat[i] = Label::createWithTTF("Z", "fonts/Marker Felt.ttf", 48); break;

		default:
			break;
		}

		alphabat[i]->setTextColor(Color4B(0, 0, 0, 255));

		alphabat[i]->setPosition(Vec2(visibleSize.width / 2 + i * 48 - selectX*48,
			visibleSize.height / 2));
	}

	for (int i = 0; i < stringIndex; i++){
		this->addChild(alphabat[i], 1);
	}
}


void HelloWorld::update(float delta){
	if (!gameOut){
		countT += delta;

		countT = ((int)(countT * pow(10.0, 1))) / pow(10.0, 1);

		ss << countT;

		buffer = ss.str();
		TimeCount->setString(buffer);
		ss.str("");
	}
	else {
		countT += delta;
		if (countT >= 2){
			auto newScene = HelloWorld::createScene();
			Director::getInstance()->replaceScene(newScene);
		}
		
	}
}

void HelloWorld::endGame(){
	int count = 0;

	for (int i = 0; i <stringIndex;i++){
		if (alphabatArray[i] > alphabatArray[i-1] && i > 0){
			count++;
		}
	}

	if (count >= stringIndex - 1){
		gameOut = true;
		countT = 0;
		/*
		CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif*/
	}
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	CCMenuItem* pTempItem = (CCMenuItem*)pSender;
	int tag = pTempItem->getTag();

	switch (tag)
	{
	case 1:
		if (selectX < stringIndex - 1){
			for (int i = 0; i < stringIndex; i++) {
				alphabat[i]->setPosition(Vec2(alphabat[i]->getPositionX() - 48,
					visibleSize.height / 2));
			}
			castSprite2->setPosition(Vec2(castSprite2->getPositionX() - 48,
				visibleSize.height / 2));
			selectX++;
		}
		break;

	case 2:
		if (selectX > 0){
			for (int i = 0; i < stringIndex; i++) {
				alphabat[i]->setPosition(Vec2(alphabat[i]->getPositionX() + 48,
					visibleSize.height / 2));
			}
			castSprite2->setPosition(Vec2(castSprite2->getPositionX() + 48,
				visibleSize.height / 2));
			selectX--;
		}
		break;

	case 3:
		selectTag[selectCount] = selectX;
		selectCount++;
		castSprite2->setVisible(true);
		castSprite2->setPosition(Vec2(visibleSize.width / 2,//alphabat[selectTag[0] + 1]->getPositionX() - 48,
			visibleSize.height / 2));

		if (selectCount == 2){
			int tmp = alphabatArray[selectTag[0]];
			alphabatArray[selectTag[0]] = alphabatArray[selectTag[1]];
			alphabatArray[selectTag[1]] = tmp;

			for (int i = 0; i < stringIndex; i++){
				this->removeChild(alphabat[i], 1);
			}

			settingString();
			selectCount = 0;
			castSprite2->setVisible(false);
			endGame();
		}


	default:
		break;
	}
	

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
