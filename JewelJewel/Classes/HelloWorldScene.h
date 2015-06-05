#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
//#include "GameData.h"

USING_NS_CC;

class HelloWorld : public cocos2d::LayerColor
{
private :
	int stage = 1;
	int selectTag[2];
	int selectCount = 0;
	int stringIndex = 8 + (stage - 1) * 2;
	int selectX = 0;
	int alphabatArray[100];

	bool gameOut = false;

	Layer *LableLayer;

	float countT = 0;
	std::string buffer;
	std::ostringstream ss;

	Label *alphabat[100];
	Label *TimeCount;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	Sprite *castSprite2 = Sprite::create("selectside.png");

public :

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	void settingString();
	void endGame();
	void settingRandom();
	void update(float delta);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
