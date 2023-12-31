// ��ֹͷ�ļ��ظ�����
#ifndef __CarrotFantasy__PageViewLayer__
#define __CarrotFantasy__PageViewLayer__

// ����PublicDefineͷ�ļ�������һЩ�����ĺ�����Ͷ���
#include "PublicDefine.h"
// ����ui/UIPageViewͷ�ļ�������PageView��Ķ���
#include "ui/UIPageView.h"
// ʹ��ui�����ռ䣬�������PageView��
using namespace ui;

// ����һ��PageViewLayer�࣬�̳���Layer�࣬������ʾ�ؿ��Ļ�����ͼ�Ĳ�
class PageViewLayer : public Layer
{
public:

    // ����һ�������������������ͷ��ڴ�
    virtual ~PageViewLayer();

    // ����һ���꣬���ڴ���PageViewLayer����
    CREATE_FUNC(PageViewLayer);

    // ����һ���麯�������ڷ�ҳ����������Ϊһ������ֵ����ʾ��������ҷ�ҳ
    virtual void pageTurn(const bool& rBLeft);

protected:

    // ����һ���麯�������ڳ�ʼ��PageViewLayer���󣬷���һ������ֵ
    virtual bool init();

    // ����һ���麯������������ҳ���־��״̬������Ϊһ������ֵ����ʾҳ�������
    virtual void setPageFlag(const int& rIIndex);

    // ����һ���麯�������ڴ����ؿ��Ļ�����ͼ
    virtual void createThemePageView();

    // ����һ���麯�������ڴ���ҳ���־�İ�ť
    virtual void createThemeFlags();

    // ����һ���麯�������ڼ��ر���ͼƬ�ͱ���
    virtual void loadBg();

private:

    // ����һ��PageView���͵�ָ�룬����ָ����ʾ�ؿ��Ļ�����ͼ�Ķ���
    PageView* _pPageView = nullptr;

    // ����һ�����ͱ��������ڼ�¼��ǰҳ�������
    int _iPageIndex = 0;

    // ����һ��Vector<MenuItemSprite*>���͵�ָ�룬����ָ��洢ҳ���־�ľ���˵��������
    Vector<MenuItemSprite*>* _pPageFlagVec = nullptr;
};

// ����ͷ�ļ��Ķ���
#endif /* defined(__CarrotFantasy__PageViewLayer__) */
