// 包含怪物基类的头文件
#include "MonsterBase.h"
// 包含怪物管理器的头文件
#include "MonsterManager.h"
// 包含移动控制器基类的头文件
#include "MoveControllerBase.h"
// 包含声音工具的头文件
#include "SoundUtil.h"

// 初始化怪物对象的函数，参数是怪物的ID
bool MonsterBase::init(const int& rIId)
{
    // 定义一个返回值，初始为false
    bool bRet = false;

    // 使用do-while循环进行初始化操作
    do
    {
        // 如果受害者实体基类的初始化失败，就跳出循环
        CC_BREAK_IF(!VictimEntityBase::init(rIId, MONSTERCSVFILE));
        // 如果动态属性接口的初始化失败，就跳出循环
        CC_BREAK_IF(!DynamicPropertyInterFace::init(rIId, MONSTERCSVFILE));
        // 设置怪物的朝向为左
        _bIsLeft = true;
        // 创建怪物的动画
        createAnimation();
        // 执行怪物的动作，参数是动画的延迟时间
        doAction(0.15f);
        // 创建一个移动控制器对象，参数是怪物对象本身
        _pMoveController = MoveControllerBase::create(this);
        // 将怪物对象添加到怪物管理器中
        MonsterManager::getInstance()->addMonster(this);
        // 设置返回值为true，表示初始化成功
        bRet = true;
    }
    // 如果循环条件为0，就结束循环
    while (0);
    // 返回初始化结果
    return  bRet;
}

// 创建怪物对象的静态函数，参数是怪物的ID
MonsterBase* MonsterBase::create(const int& rIId)
{
    // 创建一个怪物对象，使用new关键字分配内存
    auto pMonster = new MonsterBase();
    // 如果怪物对象不为空，且初始化成功
    if (pMonster && pMonster->init(rIId)) {
        // 将怪物对象的引用计数加一，防止被自动释放
        pMonster->autorelease();
        // 返回怪物对象的指针
        return pMonster;
    }
    // 如果怪物对象为空，或者初始化失败
    // 使用CC_SAFE_DELETE宏安全地删除怪物对象，释放内存
    CC_SAFE_DELETE(pMonster);
    // 返回空指针
    return nullptr;
}

// 定义怪物受伤的动作，暂时为空
void MonsterBase::behurtAction()
{

}

// 创建怪物的动画的函数
void MonsterBase::createAnimation()
{
    // 定义一个字符串向量，用来存放动画帧的文件名
    std::vector<std::string> tAniamtionFiles;
    // 使用for循环遍历动画帧的数量
    for (int i = 1; i <= _IAnimationFrameCount; i++)
        // 将每一帧的文件名拼接后，添加到字符串向量中
        tAniamtionFiles.push_back(_sModelName + StringUtils::format("%d.png", i));
    // 调用动态实体基类的函数，根据字符串向量创建动画对象
    createDynamicEntityAnimation(tAniamtionFiles);
}

// 执行怪物的动作的函数，参数是动画的延迟时间
void MonsterBase::doAction(const float& rDt)
{
    // 设置动画对象的每帧延迟时间
    _pAnimation->setDelayPerUnit(rDt);
    // 获取怪物的精灵对象，让它执行动画对象的动作
    getSprite()->runAction(Animate::create(_pAnimation));
}

// 定义怪物死亡的动作，参数是死亡时的图片文件名
void MonsterBase::deadAction(const std::string& rSDeadImageFile)
{
    // 调用怪物发出声音的函数
    MonsterSound();
    // 发送一个通知，告诉其他对象怪物已经死亡，参数是怪物对象本身
    NOTIFY->postNotification("MonsterDead", this);
    // 获取怪物的精灵对象，移除它的所有子节点，参数是是否清理内存
    getSprite()->removeAllChildrenWithCleanup(true);
    // 获取怪物的移动控制器对象，停止它的所有动作
    _pMoveController->stopAllActions();
    // 调用受害者实体基类的死亡动作函数
    VictimEntityBase::deadAction();
}

// 定义怪物发出声音的函数
void MonsterBase::MonsterSound()
{
    // 生成一个1到3之间的随机数，用来选择不同的声音文件
    int fFigure = rand() % 3 + 1;
    // 如果怪物的名字中包含"land"，表示是陆地怪物
    if (_sName.find("land") != std::string::npos)
    {
        // 调用声音工具的函数，播放对应的声音文件，参数是文件名
        SoundUtil::getInstance()->playEffect(MONSTERMUSIC + StringUtils::format("Land11%d.mp3", fFigure));
    }
    // 如果怪物的名字中包含"fly"，表示是飞行怪物
    else if (_sName.find("fly") != std::string::npos)
    {
        // 调用声音工具的函数，播放对应的声音文件，参数是文件名
        SoundUtil::getInstance()->playEffect(MONSTERMUSIC + StringUtils::format("Fat14%d.mp3", fFigure));
    }
    // 如果怪物的名字中包含"fat"，表示是肥胖怪物
    else if (_sName.find("fat") != std::string::npos)
    {
        // 调用声音工具的函数，播放对应的声音文件，参数是文件名
        SoundUtil::getInstance()->playEffect(MONSTERMUSIC + StringUtils::format("Fat14%d.mp3", fFigure));
    }
    // 如果怪物的名字都不包含上述字符串，表示是大Boss
    else
    {
        // 调用声音工具的函数，播放对应的声音文件，参数是文件名
        SoundUtil::getInstance()->playEffect(MONSTERMUSIC + "BigBoss.mp3");
    }
}

// 设置怪物的最大速度的函数，参数是速度值
void MonsterBase::setMaxSpeed(const int& iSpeed)
{
    // 调用动态属性接口的函数，设置怪物的速度属性
    setISpeed(iSpeed);
    // 调用移动控制器对象的函数，设置怪物的移动速度
    _pMoveController->setIMonsterSpeed(iSpeed);
}
