// 包含数字精灵的头文件
#include "NumSprite.h"

// 定义数字精灵的创建函数，参数是一个字符串类型的引用，表示要显示的数字，和一个字符串类型的常量，表示要使用的图片，返回一个指向节点对象的指针
Node* NumSprite::createNum(const std::string& rSNum, const std::string& rSImage)
{
    // 创建一个精灵对象，用指定的图片，获取其大小，赋值给一个自动类型的变量
    auto tSize = Sprite::create(rSImage)->getContentSize();
    // 获取要显示的数字的长度，赋值给一个自动类型的变量
    auto tINumSize = rSNum.size();

    // 创建一个节点对象，赋值给一个自动类型的变量
    auto pNumNode = Node::create();
    // 调用节点对象的保留函数，防止被自动释放
    pNumNode->retain();

    // 使用for循环，遍历要显示的数字的每一位
    for (int i = 0; i < tINumSize; ++i)
    {
        // 将数字的第i位转换为整数，赋值给一个自动类型的变量
        auto tINum = atoi(StringUtils::format("%c", rSNum.at(i)).c_str());
        // 创建一个精灵对象，用指定的图片和矩形区域，表示要显示的数字的图像，赋值给一个自动类型的变量
        auto pNum = Sprite::create(rSImage, Rect(tSize.width / 12 * (tINum + 2), 0, tSize.width / 12, tSize.height));
        // 定义一个二维向量的变量，表示精灵对象的位置，根据数字的长度和精灵对象的大小进行偏移
        auto tPos = Vec2(pNum->getContentSize().width * i, 0);
        // 设置精灵对象的位置
        pNum->setPosition(tPos);
        // 将精灵对象添加为节点对象的子节点
        pNumNode->addChild(pNum);
    }

    // 返回节点对象的指针
    return pNumNode;
}
