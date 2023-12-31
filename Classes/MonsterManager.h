
#ifndef __CarrotFantasy__MonsterManager__
#define __CarrotFantasy__MonsterManager__

// �������������ͷ�ļ�
#include "PublicDefine.h"

// ǰ������ʵ����
class Entity;

// ����һ������������࣬�̳���������
class MonsterManager : public Ref
{
public:

    // ʹ�ú궨�崴��һ���������������ľ�̬������ʵ�ֵ���ģʽ
    CREATE_INSTANCE_FUNC(MonsterManager);

    // ʹ�ú궨������һ���������������ľ�̬�������ͷ��ڴ�
    DESTROY_INSTANCE_FUNC();

    // ����һ���麯��������һ�������������������ã�����������еĹ������
    virtual MonsterVec& getMonsterVec();

    // ����һ���麯��������һ����Ա����ָ�룬������һ���������󣬽���һ��ָ��ʵ�����ָ�룬�޷���ֵ�����������������ӵ�����
    virtual void setFuncAddMonsterToLayer(const std::function<void(Entity*)>& rFuncAddMonsterToLayer);

    // ����һ���麯��������������е����й������
    virtual void clearManager();

    // ����һ���麯����������й������ı���������״̬
    virtual void clearBeAtkLockState();

protected:

    // �����������Ϊ��Ԫ�࣬���Է��ʹ��������˽�г�Ա
    friend class MonsterBase;

    // ����һ���麯�������������Ϸ�����ı�־��������һ��ָ���������͵�ָ��
    virtual void openCheckGameEnd(Ref* pSender);

    // ����һ���麯�������һ��������󵽹������У�������һ��ָ���������ָ��
    virtual void addMonster(MonsterBase* pBullet);

    // ����һ���麯������ʼ������������
    virtual bool init();

    // ����һ���麯����ע����������¼������յ�֪ͨʱ��������Ӧ�ĺ���
    virtual void registerDeadEvent();

    // ����һ���麯�����ӹ��������Ƴ�һ��������󣬲�����һ��ָ���������͵�ָ��
    virtual void removeMonsterFromManager(Ref* pMonster);

private:

    // ����һ��ָ���������������ָ�룬��ʼΪnullptr������������еĹ������
    MonsterVec* _pMonsterVec = nullptr;

    // ����һ����Ա����ָ�룬������һ��ָ��ʵ�����ָ�룬�޷���ֵ�����������������ӵ�����
    std::function<void(Entity*)> _funcAddMonsterToLayer;

    // ����һ���������͵ĳ�Ա��������ʾ�Ƿ��������Ϸ�����ı�־����ʼΪfalse
    bool _bIsOpenCheckGameEnd = false;

private:

    // �����������Ĺ��캯��
    MonsterManager();

    // ��������������������
    virtual ~MonsterManager();

    // ɾ����������Ŀ������캯������ֹ���󱻸���
    MonsterManager(const MonsterManager&) = delete;

    // ɾ����������ĸ�ֵ��������غ�������ֹ���󱻸�ֵ
    MonsterManager& operator=(const MonsterManager&) = delete;

};


#endif /* defined(__CarrotFantasy__MonsterManager__) */
