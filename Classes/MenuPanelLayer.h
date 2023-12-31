#ifndef __CarrotFantasy__MenuPanelLayer__ //���û�ж���__CarrotFantasy__MenuPanelLayer__�꣬��ֹͷ�ļ��ظ�����
#define __CarrotFantasy__MenuPanelLayer__ //����__CarrotFantasy__MenuPanelLayer__��

#include "PublicDefine.h" //�������������ͷ�ļ�

class PageViewLayer; //����һ���࣬��ʾ��ҳ��ͼ��

class MenuPanelLayer :public Layer //����һ���࣬�̳���Layer�࣬������ʾ�˵����
{
public:

    CREATE_FUNC(MenuPanelLayer); //ʹ�ú궨��һ���������������ڴ�������

    virtual void setPageTurnFunc(const std::function<void(const bool&)>& rFuncPageTurn); //����һ���麯�����������÷�ҳ�ĺ���������Ϊһ��������������ã���ʾ��ҳ�ĺ���

protected:

    virtual bool init(); //����һ���麯�������ڳ�ʼ�����󣬷���һ������ֵ

    virtual void createItemPanel(); //����һ���麯�������ڴ�����Ŀ��壬��ʾ�˵���

private:

    std::function<void(const bool&)> _funcPageTurn; //����һ�������������͵ĳ�Ա���������ڴ洢��ҳ�ĺ���

};


#endif /* defined(__CarrotFantasy__MenuPanelLayer__) */ //������������
