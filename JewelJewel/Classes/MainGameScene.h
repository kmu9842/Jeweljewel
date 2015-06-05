//
//  MainGameScene.h
//  Jeweljewel
//
//  Created by Min on 12. 11. 14..
//  Copyright (c) 2012년 __MyCompanyName__. All rights reserved.
//

#ifndef jewels_MainGameScene_h
#define jewels_MainGameScene_h

#include "cocos2d.h"

class MainGameScene : public cocos2d::CCLayer
{
public:
	virtual bool init();

	static cocos2d::CCScene* scene();

	CREATE_FUNC(MainGameScene);

private:

	void RefreshBlock();
	void BlockTouch(cocos2d::Ref*  pSender);
	void CloseCallback(cocos2d::Ref*  pSender);
	void BlockSet();
	void BlockCrashGo(int blockcode);

	void CrashAnim(cocos2d::CCPoint pos);
	void SpriteAnimateFinished(cocos2d::Ref* sender);
	void AnimSet();

	void BlockCrashTest(float delta);
	void TimeCheck(float delta);
	void ScoreSet(float delta);
	void StartCount(float delta);
};


#endif
