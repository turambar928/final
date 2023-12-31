// 包含怪物管理器的头文件
#include "MonsterManager.h"
// 包含怪物基类的头文件
#include "MonsterBase.h"
// 包含游戏管理器的头文件
#include "GameManager.h"

// 定义一个指向怪物管理器的静态指针，用来实现单例模式
MonsterManager* MonsterManager::_gInstance;

// 定义怪物管理器的构造函数
MonsterManager::MonsterManager()
{
}

// 定义一个清除被攻击锁定状态的函数，遍历所有的怪物对象，将它们的攻击目标设置为false
void MonsterManager::clearBeAtkLockState()
{
    for (auto& iterMonster : *_pMonsterVec)
    {
        iterMonster->setAtkTarget(false);
    }
}

// 定义怪物管理器的析构函数
MonsterManager::~MonsterManager()
{
    // 使用CC_SAFE_DELETE宏安全地删除怪物对象的向量，释放内存
    CC_SAFE_DELETE(_pMonsterVec);
}

// 定义怪物管理器的初始化函数
bool MonsterManager::init()
{
    // 定义一个布尔类型的返回值，初始为false
    bool bRet = false;
    // 使用do-while循环，方便跳出
    do
    {
        // 创建一个新的怪物对象的向量，赋值给成员变量
        _pMonsterVec = new Vector<MonsterBase*>;
        // 调用注册死亡事件的函数
        registerDeadEvent();
        // 设置返回值为true，表示初始化成功
        bRet = true;
    }
    // 如果循环条件为0，就结束循环
    while (0);

    // 返回初始化结果
    return bRet;
}

// 定义一个获取怪物对象的向量的函数，返回成员变量的引用
Vector<MonsterBase*>& MonsterManager::getMonsterVec()
{
    return *_pMonsterVec;
}

// 定义一个添加怪物对象的函数，参数是一个指向怪物基类的指针
void MonsterManager::addMonster(MonsterBase* pMonster)
{
    // 如果成员变量不为空，就将参数指向的怪物对象添加到向量中
    if (_pMonsterVec) _pMonsterVec->pushBack(pMonster);
    // 调用成员函数指针，将参数指向的怪物对象添加到层中
    _funcAddMonsterToLayer(pMonster);
}

// 定义一个设置成员函数指针的函数，参数是一个函数对象，接受一个指向实体类的指针，无返回值
void MonsterManager::setFuncAddMonsterToLayer(const std::function<void(Entity*)>& rFuncAddMonsterToLayer)
{
    // 将参数赋值给成员函数指针
    _funcAddMonsterToLayer = rFuncAddMonsterToLayer;
}

// 定义一个注册死亡事件的函数
void MonsterManager::registerDeadEvent()
{
    // 调用通知中心的函数，添加一个观察者，当收到名为MonsterDead的通知时，调用从管理器中移除怪物的函数，不传递任何数据
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(MonsterManager::removeMonsterFromManager), "MonsterDead", nullptr);
    // 调用通知中心的函数，添加一个观察者，当收到名为openCheckGameEnd的通知时，调用开启检查游戏结束的函数，不传递任何数据
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(MonsterManager::openCheckGameEnd), "openCheckGameEnd", nullptr);
}

// 定义一个从管理器中移除怪物的函数，参数是一个指向引用类型的指针
void MonsterManager::removeMonsterFromManager(Ref* pMonster)
{
    // 如果成员变量为空或者向量的大小为0，就直接返回
    if (!(_pMonsterVec && _pMonsterVec->size())) return;
    // 将参数转换为一个指向怪物基类的指针，然后从向量中删除该对象
    _pMonsterVec->eraseObject(reinterpret_cast<MonsterBase*>(pMonster));

    // 如果成员变量表示开启检查游戏结束为真
    if (_bIsOpenCheckGameEnd)
    {
        // 如果向量的大小为0，表示所有的怪物都死亡
        if (!_pMonsterVec->size())
        {
            // 定义一个自动类型的变量，表示游戏胜利的枚举值
            auto tEnGameWin = en_GameWin;
            // 如果游戏管理器的函数获取胡萝卜的生命值大于等于1，就发送一个名为gameEnd的通知，传递游戏胜利的枚举值的指针
            if (GameManager::getInstance()->getICarrotHp() >= 1) NOTIFY->postNotification("gameEnd", reinterpret_cast<Ref*>(&tEnGameWin));
            // 将成员变量表示开启检查游戏结束设置为false
            _bIsOpenCheckGameEnd = false;
        }
    }
}

// 定义一个清除管理器的函数
void MonsterManager::clearManager()
{
    // 调用向量的函数，清除所有的怪物对象
    _pMonsterVec->clear();
}

// 定义一个开启检查游戏结束的函数，参数是一个指向引用类型的指针
void MonsterManager::openCheckGameEnd(cocos2d::Ref* pSender)
{
    // 将成员变量表示开启检查游戏结束设置为true
    _bIsOpenCheckGameEnd = true;
}
