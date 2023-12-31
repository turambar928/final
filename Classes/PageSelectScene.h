// ��ֹͷ�ļ��ظ�����
#ifndef __newCardDefence__PageSelectScene__
#define __newCardDefence__PageSelectScene__

// ����PublicDefineͷ�ļ�������һЩ�����ĺ�����Ͷ���
#include "PublicDefine.h"

// ����һ��PageSelectScene�࣬�̳���Scene�࣬������ʾ��ѡ��ؿ��ĳ���
class PageSelectScene : public Scene
{
public:

    // ����һ���꣬���ڴ���PageSelectScene����
    CREATE_FUNC(PageSelectScene);

    // ����һ�������������������ͷ��ڴ�
    virtual ~PageSelectScene();

protected:

    // ����һ���麯�������ڳ�ʼ��PageSelectScene���󣬷���һ������ֵ
    virtual bool init();

    // ����һ���麯�������ڽ��볡��ʱ�Ĳ������޷���ֵ
    virtual void onEnter()override;

private:

    // ����һ��Layer���͵�ָ�룬����ָ����ʾ�ؿ��Ļ�����ͼ�Ĳ�
    Layer* _pPageViewLayer = nullptr;

    // ����һ��Layer���͵�ָ�룬����ָ����ʾ�˵����Ĳ�
    Layer* _pMenuPanelLayer = nullptr;

    // ����һ��Layer���͵�ָ�룬����ָ����ʾ��ҳ��ť�Ĳ�
    Layer* _pPageTurningLayer = nullptr;

};

// ����ͷ�ļ��Ķ���
#endif /* defined(__newCardDefence__LevelSelectScene__) */
