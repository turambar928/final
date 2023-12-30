// ��ֹͷ�ļ��ظ�����
#ifndef __CarrotFantasy__MonsterBase__
#define __CarrotFantasy__MonsterBase__

// �����ܺ���ʵ������ͷ�ļ�
#include "VictimEntityBase.h"
// ������̬���Խӿڵ�ͷ�ļ�
#include "DynamicPropertyInterFace.h"

// ǰ�������ƶ�����������
class MoveControllerBase;

// ����һ��������࣬�̳����ܺ���ʵ�����Ͷ�̬���Խӿ�
class MonsterBase : public VictimEntityBase, public DynamicPropertyInterFace
{
    // �������﹤����Ϊ��Ԫ�࣬���Է���˽�г�Ա
    friend class MonsterFactory;

public:

    // ʹ�þ�̬��������һ��������󣬲����ǹ����ID
    static MonsterBase* create(const int& rIId);

    // ���ù��������ٶȣ��������ٶ�ֵ
    void setMaxSpeed(const int& iSpeed);

protected:

    // ��д�ܺ���ʵ������������������������������ʱ��ͼƬ�ļ���
    virtual void deadAction(const std::string& rSDeadImageFile = "")override;

    // �������Ķ��������������Ƕ������ӳ�ʱ��
    virtual void doAction(const float& rDt);

    // ��ʼ���������ĺ����������ǹ����ID
    virtual bool init(const int& rIId);

    // ����������˵Ķ�����������ʱΪ��
    virtual void behurtAction();

    // ��������Ķ����ĺ���
    virtual void createAnimation();

    // ������﷢�������ĺ���
    virtual void MonsterSound();

    // ʹ�ú궨�������Ͷ���һ���������͵ĳ�Ա��������ʾ����ĳ����Ƿ�Ϊ��
    CC_SYNTHESIZE_PASS_BY_REF(bool, _bIsLeft, IsLeft);

    // ����һ��ָ���ƶ������������ָ�룬�������ƹ�����ƶ�
    MoveControllerBase* _pMoveController = nullptr;
};

// ����ͷ�ļ��Ķ���
#endif /* defined(__CarrotFantasy__MonsterBase__) */
