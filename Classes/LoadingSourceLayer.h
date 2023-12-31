#ifndef __CarrotFantasy__LoadingSourceLayer__ //���û�ж���__CarrotFantasy__LoadingSourceLayer__�꣬��ֹͷ�ļ��ظ�����
#define __CarrotFantasy__LoadingSourceLayer__ //����__CarrotFantasy__LoadingSourceLayer__��

#include "PublicDefine.h" //�������������ͷ�ļ�

class LoadingSourceLayer : public Layer //����һ���࣬�̳���Layer�࣬������ʾ������Դ�Ĳ�
{
public:

    CREATE_FUNC(LoadingSourceLayer); //ʹ�ú궨��һ���������������ڴ�������

    virtual void setFuncShowMenuPanel(const std::function<void()>& rFuncShowMenuPanel); //����һ���麯��������������ʾ�˵����ĺ���������Ϊһ���������������

protected:

    virtual void onEnter()override; //����һ���麯���������ڲ����ʱִ�У����Ǹ����ͬ������

    virtual bool init(); //����һ���麯�������ڳ�ʼ�����󣬷���һ������ֵ

    virtual void loadSource(); //����һ���麯�������ڼ�����Դ���Ӿ���֡�����л�ȡͼƬ

protected:

    std::function<void()> _funShowMenuPanel; //����һ�������������͵ĳ�Ա���������ڴ洢��ʾ�˵����ĺ���

    Label* _pLoadingTitle = nullptr; //����һ��ָ���ǩ��ָ�룬���ڴ洢���ر��⣬��ʼֵΪnullptr
};

#endif /* defined(__CarrotFantasy__LoadingSourceLayer__) */ //������������
