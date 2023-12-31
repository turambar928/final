// 防止头文件重复包含
#ifndef __CarrotFantasy__NumSprite__
#define __CarrotFantasy__NumSprite__

// 包含公共定义的头文件
#include "PublicDefine.h"

// 定义一个数字精灵的类
class NumSprite
{

public:

    // 定义一个静态函数，根据给定的数字和图片，创建一个数字节点对象，返回一个指向节点对象的指针
    static Node* createNum(const std::string& rSNum, const std::string& rSImage);
};

// 结束头文件的定义
#endif /* defined(__CarrotFantasy__NumSprite__) */
