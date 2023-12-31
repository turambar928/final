#ifndef __CarrotFantasy__HpSlot__
#define __CarrotFantasy__HpSlot__

#include "PublicDefine.h"
class VictimEntityBase;

// 血槽类，继承自Node
class HpSlot : public Node
{
public:

    // 析构函数，用于释放资源
    virtual ~HpSlot();

    // 静态工厂方法，创建HpSlot实例
    static HpSlot* create(VictimEntityBase* pVictimEntity);

    // 设置血量的方法
    virtual void setHp(const int& rIHp);

    // 获取内容尺寸的方法
    virtual const Size& getContentSize() const;


protected:

    // 初始化方法，传入受害者实体
    virtual bool init(VictimEntityBase* pVictimEntity);

private:

    // 受害者实体的指针
    VictimEntityBase* _pVictimEntity = nullptr;

public:

    // 血槽的进度条
    ProgressTimer* _pHpSlot = nullptr;

    // 最大血量值
    int _iHpMax = 0;
};

#endif /* defined(__CarrotFantasy__HpSlot__) */
