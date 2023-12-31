#ifndef __newCardDefence__SoundUtil__
#define __newCardDefence__SoundUtil__

#include "PublicDefine.h"

class SoundUtil : public Ref
{
public:
    CREATE_INSTANCE_FUNC(SoundUtil);
    DESTROY_INSTANCE_FUNC();

    void playBackgroundSound(const std::string& rSBgSound);
    void playEffect(const std::string& rSEffectSound);
    void setIsBackGroundSound(const bool& rIsSound);
    bool getIsBackGroundSound() const { return _bIsBackGroundSound; }
    void stopBackGroundSound();

protected:
    virtual bool init() { return true; }

protected:
    bool _bIsBackGroundSound = true;
    bool _bIsSoundMainBackGroundMusic = false;
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsEffectSound, IsEffectSound);

private:
    SoundUtil();
    virtual ~SoundUtil();
    SoundUtil(const SoundUtil&) = delete;
    SoundUtil& operator=(const SoundUtil&) = delete;
};


#endif /* defined(__newCardDefence__SoundUtil__) */
