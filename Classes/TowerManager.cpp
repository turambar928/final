#include "TowerManager.h"
#include "TowerBase.h"

/**
 * @brief TowerManager��ĵ���ʵ��
 */
TowerManager *TowerManager::_gInstance;

/**
 * @brief TowerManager��Ĺ��캯��
 */
TowerManager::TowerManager() {
}

/**
 * @brief TowerManager�����������
 */
TowerManager::~TowerManager() {
    // �ͷ����������ڴ�
    CC_SAFE_DELETE(_pTowerVec);
}

/**
 * @brief ��ʼ��TowerManager����
 * @return ��ʼ���Ƿ�ɹ�
 */
bool TowerManager::init() {
    bool bRet = false;
    do {
        // ������������ע���������¼�
        _pTowerVec = new Vector<TowerBase *>();
        registerTowerDeadEvent();
        bRet = true;
    } while (0);

    return bRet;
}

/**
 * @brief ��ȡTowerBaseָ������������
 * @return TowerBaseָ������������
 */
Vector<TowerBase *> &TowerManager::getTowerVec() {
    return *_pTowerVec;
}

/**
 * @brief ������ӵ��������в�ִ�лص�����
 * @param pTower Ҫ��ӵ���ָ��
 */
void TowerManager::addTower(TowerBase *pTower) {
    // ������������ڣ�������ӵ�������
    if (_pTowerVec)
        _pTowerVec->pushBack(pTower);
    
    // ִ�����������Ļص�����
    _funcAddTowerToLayer(pTower);
}

/**
 * @brief ����TowerManager�Ļص����������������������
 * @param rFuncAddEntityLayer �ص�����
 */
void TowerManager::setFuncAddTowerLayer(const std::function<void(Entity*)>& rFuncAddEntityLayer) {
    _funcAddTowerToLayer = rFuncAddEntityLayer;
}

/**
 * @brief ע���������¼��Ĺ۲���
 */
void TowerManager::registerTowerDeadEvent() {
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(TowerManager::removeTowerFromManager), "TowerDead", nullptr);
}

/**
 * @brief �������������Ƴ����ķ�����ͨ���������¼�����
 * @param pTower ������������
 */
void TowerManager::removeTowerFromManager(Ref* pTower) {
    // ���������Ϊ�ջ���û��������ֱ�ӷ���
    if (!(_pTowerVec && _pTowerVec->size()))
        return;

    // �����������Ƴ�ָ��������
    _pTowerVec->eraseObject(reinterpret_cast<TowerBase*>(pTower));
}

/**
 * @brief ������������е�������
 */
void TowerManager::clearManager() {
    _pTowerVec->clear();
}

/**
 * @brief ��ȡ��ǰ��ҵĽ������
 * @return ��ǰ�������
 */
int TowerManager::getMoney() {
    return _funcCheckMoney();
}

/**
 * @brief ����TowerManager�Ļص����������ڼ��������
 * @param rFuncCheckMoney �ص�����
 */
void TowerManager::setFuncCheckMoney(const std::function<int()>& rFuncCheckMoney) {
    _funcCheckMoney = rFuncCheckMoney;
}
