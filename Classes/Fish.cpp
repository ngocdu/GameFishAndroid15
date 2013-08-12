//
//  Fish.cpp
//  GameFish
//
//  Created by MinhNT on 13/08/05.
//
//

#include "Fish.h"
// Fish *obj = new Fish("a",1);
Fish::Fish()
{
    
}

Fish::Fish(string _ten, int _diem)
{
    this->_name = _ten;
    this->_point = _diem;
    
}

void Fish::diChuyen() {
    CCSize winsize = CCDirector::sharedDirector()->getWinSize();
    float maxY=this->getPosition().y + this->getContentSize().height*2;
    float minY=this->getPosition().y - this->getContentSize().height*2;
    int rangeY=maxY-minY;
    float actualY=(rand() % rangeY ) + minY;
    
    int maxX=winsize.width + this->getContentSize().width ;
    int minX= -this->getContentSize().width ;
    int rangeX=maxX - minX;
    float actualX=(rand() % rangeX ) + minX;
    float x= this->getPosition().x;
    float y= this->getPosition().y;
    float khoangcach= sqrtf( powf(((rand() % rangeX ) + minX - x ),2) + powf(((rand() % rangeY ) + minY - y ),2) );
    int time= khoangcach / this->getVanToc();
    CCPoint p1=CCPoint((rand() % rangeX ) + minX,(rand() % rangeY ) + minY);
    CCPoint p11=CCPoint(p1.x + (rand() % 25) -15 , p1.y + (rand() % 5));
    CCPoint p2=CCPoint((rand() % rangeX ) + minX,(rand() % rangeY ) + minY);
    CCPoint p22=CCPoint(p2.x + (rand() % 25) -15 , p2.y + (rand() % 5));
    CCPoint p3=CCPoint((rand() % rangeX ) + minX,(rand() % rangeY ) + minY);
    CCPoint p33=CCPoint(p3.x + (rand() % 25)-15 , p3.y + (rand() % 5));
    CCPoint p4=CCPoint((rand() % rangeX ) + minX,(rand() % rangeY ) + minY);
    CCPoint p44=CCPoint(p4.x + (rand() % 25)-15 , p4.y + (rand() % 5));
    CCPoint p5=CCPoint((rand() % rangeX ) + minX,(rand() % rangeY ) + minY);
    CCPoint p55=CCPoint(p5.x + (rand() % 25)-15 , p5.y + (rand() % 5));
    CCPoint p6=CCPoint((rand() % rangeX ) + minX,(rand() % rangeY ) + minY);
    CCPoint p66=CCPoint(p6.x + (rand() % 25)-15 , p6.y + (rand() % 5));
    
    
    CCMoveTo* move1=CCMoveTo::create(ccpDistance(this->getPosition(),p1)/this->getVanToc(),p1);
    CCMoveTo* move11=CCMoveTo::create(0.6,p11);
    CCMoveTo* move2=CCMoveTo::create(ccpDistance(p1,p2)/this->getVanToc(),p2);
    CCMoveTo* move22=CCMoveTo::create(0.6,p22);
    CCMoveTo* move3=CCMoveTo::create(ccpDistance(p2,p3)/this->getVanToc(),p3);
    CCMoveTo* move33=CCMoveTo::create(0.6,p33);
    CCMoveTo* move4=CCMoveTo::create(ccpDistance(p3,p4)/this->getVanToc(),p4);
    CCMoveTo* move44=CCMoveTo::create(0.6,p44);
    CCMoveTo* move5=CCMoveTo::create(ccpDistance(p4,p5)/this->getVanToc(),p5);
    CCMoveTo* move55=CCMoveTo::create(0.6,p55);
    CCMoveTo* move6=CCMoveTo::create(ccpDistance(p5,p6)/this->getVanToc(),p6);
    CCMoveTo* move66=CCMoveTo::create(0.6,p66);
    
    CCSequence* action=(CCSequence*)CCSequence::create(move1,move11,move2,move22,move3,move33,move4,move44,move5,move55,move6,move66,NULL);
    
    
    CCRepeatForever * repeate=CCRepeatForever::create(action);
    this->runAction(repeate);
}
void Fish::boiDung() {
    string name = this->getName();
    CCAnimation *anim=CCAnimation::create();
    for (int i = 1; i <= this->getNumberImage(); i++) {
        char strname[20] = {0};
        sprintf(strname, "%i", i);
        string file_name;
        if (this->getNumberImage() <= 4) {
            file_name = name+"_"+strname+".png";
        }else file_name = name+"_boidung_"+strname+".png";
        anim->addSpriteFrameWithFileName(file_name.c_str());
    }
    anim->setDelayPerUnit(2.8f / 19.0f);
    anim->setRestoreOriginalFrame(true);
    CCAnimate * animet=CCAnimate::create(anim);
    CCRepeatForever * rep=CCRepeatForever::create(animet);
    rep->setTag(123456);
    this->runAction(rep);
}
void Fish::dopMoi() {
    this->stopAllActions();
    string name = this->getName();
    CCAnimation *anim=CCAnimation::create();
    for (int i = 1; i <= this->getNumberImage(); i++) {
        char strname[20] = {0};
        sprintf(strname, "%i", i);
        string file_name = name+"_dopmoi_"+strname+".png";
        anim->addSpriteFrameWithFileName(file_name.c_str());
    }
    anim->setDelayPerUnit(2.8f / 49.0f);
    anim->setRestoreOriginalFrame(true);
    CCAnimate * animet=CCAnimate::create(anim);
    CCCallFuncN *start = CCCallFuncN::create(this,callfuncN_selector(Fish::startBoiDung));
    CCSequence * sq = CCSequence::create(animet, start, NULL);
    this->runAction(sq);
}
void Fish::startBoiDung(cocos2d::CCNode *node) {
    Fish * fish = (Fish*)node;
    fish->boiDung();
    if (this->getIsPlayer() == false) {
        fish->diChuyen();
    }
}
