#ifndef __CarrotFantasy__BarrierManager__
#define __CarrotFantasy__BarrierManager__

#include "PublicDefine.h"

class Entity;

class BarrierManager: public Ref
{
public:

    CREATE_INSTANCE_FUNC(BarrierManager);//�Զ���ĺ꣬����һ����̬��Ա����������һ�� BarrierManager ����ĵ���
    
    DESTROY_INSTANCE_FUNC();//���Զ���ĺ꣬����һ����̬��Ա�������������� BarrierManager ����ĵ��������ͷ��ڴ�ռ䡣
    
    BarrierVec &getBarrierVec();//��ȡһ�� BarrierVec ���͵�����
    
    virtual void setFuncAddBarrierToLayer(const std::function<void (Entity*)> &rFuncAddBarrierToLayer);//���ϰ��������ӵ���Ϸ����
    
    virtual void clearBeAtkLockState();//��������ϰ���ı���������״̬����ֹ�ϰ��ﱻ��ι�����
    
    virtual void clearManager();//����������е������ϰ������
protected:
    
    friend class BarrierBase;
    
    virtual void addBarrier(BarrierBase *pBarrier);//����ϰ������
    
    virtual bool init();//��ʼ��
    
    virtual void registerBarrierDeadEvent();//����ʱ��
    
    virtual void removeBarrierFromManager(Ref *pBarrier);//�ӹ��������Ƴ�
    
private:
    
    BarrierVec *_pBarrierVec = nullptr;
    
    std::function<void (Entity*)> _funcAddBarrierToLayer;//���ϰ��������ӵ���Ϸ����
    
private:
    
    BarrierManager();
    
    virtual ~BarrierManager();
    
    BarrierManager(const BarrierManager &) = delete;
    //�������캯�������ڴ���һ�� BarrierManager ����ĸ�����������һ�� BarrierManager ���͵�������Ϊ����������ɾ������ʾ���ܱ�ʹ�ã�����Ϊ�˷�ֹ���ֶ�� BarrierManager ����������
    
    BarrierManager &operator=(const BarrierManager &) = delete;
    //����һ����ֵ����������ڽ�һ�� BarrierManager �����ֵ������һ�� BarrierManager ����������һ�� BarrierManager ���͵�������Ϊ������
    //������һ�� BarrierManager ���͵����ã���ʾ��ֵ��Ķ�������ɾ������ʾ���ܱ�ʹ�ã�����Ϊ�˷�ֹ���ֶ�� BarrierManager ����������
};

#endif 
