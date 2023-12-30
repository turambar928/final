#include "TowerManager.h"
#include "TowerBase.h"

/**
 * @brief TowerManager类的单例实例
 */
TowerManager *TowerManager::_gInstance;

/**
 * @brief TowerManager类的构造函数
 */
TowerManager::TowerManager() {
}

/**
 * @brief TowerManager类的析构函数
 */
TowerManager::~TowerManager() {
    // 释放塔向量的内存
    CC_SAFE_DELETE(_pTowerVec);
}

/**
 * @brief 初始化TowerManager对象
 * @return 初始化是否成功
 */
bool TowerManager::init() {
    bool bRet = false;
    do {
        // 创建塔向量并注册塔死亡事件
        _pTowerVec = new Vector<TowerBase *>();
        registerTowerDeadEvent();
        bRet = true;
    } while (0);

    return bRet;
}

/**
 * @brief 获取TowerBase指针向量的引用
 * @return TowerBase指针向量的引用
 */
Vector<TowerBase *> &TowerManager::getTowerVec() {
    return *_pTowerVec;
}

/**
 * @brief 将塔添加到塔向量中并执行回调函数
 * @param pTower 要添加的塔指针
 */
void TowerManager::addTower(TowerBase *pTower) {
    // 如果塔向量存在，则将塔添加到向量中
    if (_pTowerVec)
        _pTowerVec->pushBack(pTower);
    
    // 执行添加塔到层的回调函数
    _funcAddTowerToLayer(pTower);
}

/**
 * @brief 设置TowerManager的回调函数，用于添加塔到层中
 * @param rFuncAddEntityLayer 回调函数
 */
void TowerManager::setFuncAddTowerLayer(const std::function<void(Entity*)>& rFuncAddEntityLayer) {
    _funcAddTowerToLayer = rFuncAddEntityLayer;
}

/**
 * @brief 注册塔死亡事件的观察者
 */
void TowerManager::registerTowerDeadEvent() {
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(TowerManager::removeTowerFromManager), "TowerDead", nullptr);
}

/**
 * @brief 从塔管理器中移除塔的方法，通过塔死亡事件调用
 * @param pTower 死亡的塔对象
 */
void TowerManager::removeTowerFromManager(Ref* pTower) {
    // 如果塔向量为空或者没有塔，则直接返回
    if (!(_pTowerVec && _pTowerVec->size()))
        return;

    // 从塔向量中移除指定塔对象
    _pTowerVec->eraseObject(reinterpret_cast<TowerBase*>(pTower));
}

/**
 * @brief 清空塔管理器中的所有塔
 */
void TowerManager::clearManager() {
    _pTowerVec->clear();
}

/**
 * @brief 获取当前玩家的金币数量
 * @return 当前金币数量
 */
int TowerManager::getMoney() {
    return _funcCheckMoney();
}

/**
 * @brief 设置TowerManager的回调函数，用于检查金币数量
 * @param rFuncCheckMoney 回调函数
 */
void TowerManager::setFuncCheckMoney(const std::function<int()>& rFuncCheckMoney) {
    _funcCheckMoney = rFuncCheckMoney;
}
