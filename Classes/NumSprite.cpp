// �������־����ͷ�ļ�
#include "NumSprite.h"

// �������־���Ĵ���������������һ���ַ������͵����ã���ʾҪ��ʾ�����֣���һ���ַ������͵ĳ�������ʾҪʹ�õ�ͼƬ������һ��ָ��ڵ�����ָ��
Node* NumSprite::createNum(const std::string& rSNum, const std::string& rSImage)
{
    // ����һ�����������ָ����ͼƬ����ȡ���С����ֵ��һ���Զ����͵ı���
    auto tSize = Sprite::create(rSImage)->getContentSize();
    // ��ȡҪ��ʾ�����ֵĳ��ȣ���ֵ��һ���Զ����͵ı���
    auto tINumSize = rSNum.size();

    // ����һ���ڵ���󣬸�ֵ��һ���Զ����͵ı���
    auto pNumNode = Node::create();
    // ���ýڵ����ı�����������ֹ���Զ��ͷ�
    pNumNode->retain();

    // ʹ��forѭ��������Ҫ��ʾ�����ֵ�ÿһλ
    for (int i = 0; i < tINumSize; ++i)
    {
        // �����ֵĵ�iλת��Ϊ��������ֵ��һ���Զ����͵ı���
        auto tINum = atoi(StringUtils::format("%c", rSNum.at(i)).c_str());
        // ����һ�����������ָ����ͼƬ�;������򣬱�ʾҪ��ʾ�����ֵ�ͼ�񣬸�ֵ��һ���Զ����͵ı���
        auto pNum = Sprite::create(rSImage, Rect(tSize.width / 12 * (tINum + 2), 0, tSize.width / 12, tSize.height));
        // ����һ����ά�����ı�������ʾ��������λ�ã��������ֵĳ��Ⱥ;������Ĵ�С����ƫ��
        auto tPos = Vec2(pNum->getContentSize().width * i, 0);
        // ���þ�������λ��
        pNum->setPosition(tPos);
        // ������������Ϊ�ڵ������ӽڵ�
        pNumNode->addChild(pNum);
    }

    // ���ؽڵ�����ָ��
    return pNumNode;
}
