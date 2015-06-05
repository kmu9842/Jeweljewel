//
//  MainScene.h
//  jewels
//
//  Created by Min on 12. 11. 15..
//
//

#ifndef __jewels__MainScene__
#define __jewels__MainScene__

#include <iostream>
#include "cocos2d.h"
#include "MainGameScene.h"

class MainScene : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
	static cocos2d::Scene* createScene();

    
    CREATE_FUNC(MainScene);
    
private:
	void CreaterMenuCallback(cocos2d::Ref* pSender);
	void menuCloseCallback(cocos2d::Ref* pSender);
	void RankCloseCallback(cocos2d::Ref* pSender);
};
#endif /* defined(__jewels__MainScene__) */
