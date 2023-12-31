#ifndef __CarrotFantasy__HpSlot__
#define __CarrotFantasy__HpSlot__

#include "PublicDefine.h"
class VictimEntityBase;

// Ѫ���࣬�̳���Node
class HpSlot : public Node
{
public:

    // ���������������ͷ���Դ
    virtual ~HpSlot();

    // ��̬��������������HpSlotʵ��
    static HpSlot* create(VictimEntityBase* pVictimEntity);

    // ����Ѫ���ķ���
    virtual void setHp(const int& rIHp);

    // ��ȡ���ݳߴ�ķ���
    virtual const Size& getContentSize() const;


protected:

    // ��ʼ�������������ܺ���ʵ��
    virtual bool init(VictimEntityBase* pVictimEntity);

private:

    // �ܺ���ʵ���ָ��
    VictimEntityBase* _pVictimEntity = nullptr;

public:

    // Ѫ�۵Ľ�����
    ProgressTimer* _pHpSlot = nullptr;

    // ���Ѫ��ֵ
    int _iHpMax = 0;
};

#endif /* defined(__CarrotFantasy__HpSlot__) */
