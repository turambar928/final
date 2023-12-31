// SceneBase.cpp

#include "SceneBase.h"

// ��������Դ���غ�ж��
void SceneBase::sourceManager(const std::vector<std::string>& rSourceNameVec, const bool& rBLoad) {
    // ��ȡ����֡����ʵ��
    auto pSpriteFrameCache = SpriteFrameCache::getInstance();

    // �����������Դ��������
    for (auto& iterSourceName : rSourceNameVec) {
        // �����Ҫ������Դ
        if (rBLoad) {
            // ʹ�þ���֡�������ͼƬ���ϺͶ���
            pSpriteFrameCache->addSpriteFramesWithFile(iterSourceName + PLISTPOSTFIX, iterSourceName + PHOTOPOSTFIX);
        }
        else {
            // ����Ӿ���֡�������Ƴ�ָ����ͼƬ���ϺͶ���
            pSpriteFrameCache->removeSpriteFramesFromFile(iterSourceName + PLISTPOSTFIX);
        }
    }
}
