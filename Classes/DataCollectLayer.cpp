#include "DataCollectLayer.h"

bool DataCollectLayer::init()
{
    //数据收集层的初始化和资源加载的功能
    bool bRet = false;
    
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        loadSource();
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void DataCollectLayer::loadSource()
{
    auto pBg = Sprite::createWithSpriteFrameName("statistics_bg.png");
    addChild(pBg);
}