
#ifndef __jewels__RankingMenu__
#define __jewels__RankingMenu__

#include "cocos2d.h"

class RankingMenu : public cocos2d::CCLayer
{
public:
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    CREATE_FUNC(RankingMenu);
    
private:
	void menuCloseCallback(cocos2d::Ref* Sender);
};



#endif /* defined(__jewels__RankingMenu__) */
