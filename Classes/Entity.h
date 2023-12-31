#ifndef __newCardDefence__Entity__
#define __newCardDefence__Entity__

#include "PublicDefine.h"

class Entity:public Node
{
public:
    
    virtual ~Entity();

public:
	static unsigned long ID;

	unsigned int getmID();

    virtual bool init(const int &rId, const std::string &rSCsvFileName);
    
    virtual const Size &getContentSize()const;
   
    virtual void doDead()final;
    
   
    virtual void bindSprite(Sprite *pSprite);
    virtual Sprite *getSprite();
    
   
    virtual Rect getBoundingBox()const;
    
    
protected:
    
    virtual void deadAction(const std::string &rSDeadImageFile = "");

   
    virtual void initProperty(const int &rId, const std::string &rSCsvFileName);
   
    CC_SYNTHESIZE_PASS_BY_REF(int, _iId, IId);
    
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _sName, SName);
    
    CC_SYNTHESIZE_PASS_BY_REF(std::string, _sModelName, SModelName);
    
    CC_SYNTHESIZE_PASS_BY_REF(int, _iValue, IValue);
    
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsDead, IsDead);
    
    CC_SYNTHESIZE_PASS_BY_REF(int, _IAnimationFrameCount, AnimationFrameCount);
    
    CC_SYNTHESIZE_PASS_BY_REF(int, _iLevel, ILevel);
private:
    
    Sprite *_pSprite = nullptr;

	unsigned long _myID;
    
};

#endif
