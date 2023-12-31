// ���������������ͷ�ļ�
#include "MonsterManager.h"
// ������������ͷ�ļ�
#include "MonsterBase.h"
// ������Ϸ��������ͷ�ļ�
#include "GameManager.h"

// ����һ��ָ�����������ľ�ָ̬�룬����ʵ�ֵ���ģʽ
MonsterManager* MonsterManager::_gInstance;

// �������������Ĺ��캯��
MonsterManager::MonsterManager()
{
}

// ����һ���������������״̬�ĺ������������еĹ�����󣬽����ǵĹ���Ŀ������Ϊfalse
void MonsterManager::clearBeAtkLockState()
{
    for (auto& iterMonster : *_pMonsterVec)
    {
        iterMonster->setAtkTarget(false);
    }
}

// ����������������������
MonsterManager::~MonsterManager()
{
    // ʹ��CC_SAFE_DELETE�갲ȫ��ɾ�����������������ͷ��ڴ�
    CC_SAFE_DELETE(_pMonsterVec);
}

// �������������ĳ�ʼ������
bool MonsterManager::init()
{
    // ����һ���������͵ķ���ֵ����ʼΪfalse
    bool bRet = false;
    // ʹ��do-whileѭ������������
    do
    {
        // ����һ���µĹ���������������ֵ����Ա����
        _pMonsterVec = new Vector<MonsterBase*>;
        // ����ע�������¼��ĺ���
        registerDeadEvent();
        // ���÷���ֵΪtrue����ʾ��ʼ���ɹ�
        bRet = true;
    }
    // ���ѭ������Ϊ0���ͽ���ѭ��
    while (0);

    // ���س�ʼ�����
    return bRet;
}

// ����һ����ȡ�������������ĺ��������س�Ա����������
Vector<MonsterBase*>& MonsterManager::getMonsterVec()
{
    return *_pMonsterVec;
}

// ����һ����ӹ������ĺ�����������һ��ָ���������ָ��
void MonsterManager::addMonster(MonsterBase* pMonster)
{
    // �����Ա������Ϊ�գ��ͽ�����ָ��Ĺ��������ӵ�������
    if (_pMonsterVec) _pMonsterVec->pushBack(pMonster);
    // ���ó�Ա����ָ�룬������ָ��Ĺ��������ӵ�����
    _funcAddMonsterToLayer(pMonster);
}

// ����һ�����ó�Ա����ָ��ĺ�����������һ���������󣬽���һ��ָ��ʵ�����ָ�룬�޷���ֵ
void MonsterManager::setFuncAddMonsterToLayer(const std::function<void(Entity*)>& rFuncAddMonsterToLayer)
{
    // ��������ֵ����Ա����ָ��
    _funcAddMonsterToLayer = rFuncAddMonsterToLayer;
}

// ����һ��ע�������¼��ĺ���
void MonsterManager::registerDeadEvent()
{
    // ����֪ͨ���ĵĺ��������һ���۲��ߣ����յ���ΪMonsterDead��֪ͨʱ�����ôӹ��������Ƴ�����ĺ������������κ�����
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(MonsterManager::removeMonsterFromManager), "MonsterDead", nullptr);
    // ����֪ͨ���ĵĺ��������һ���۲��ߣ����յ���ΪopenCheckGameEnd��֪ͨʱ�����ÿ��������Ϸ�����ĺ������������κ�����
    NOTIFY->addObserver(this, CC_CALLFUNCO_SELECTOR(MonsterManager::openCheckGameEnd), "openCheckGameEnd", nullptr);
}

// ����һ���ӹ��������Ƴ�����ĺ�����������һ��ָ���������͵�ָ��
void MonsterManager::removeMonsterFromManager(Ref* pMonster)
{
    // �����Ա����Ϊ�ջ��������Ĵ�СΪ0����ֱ�ӷ���
    if (!(_pMonsterVec && _pMonsterVec->size())) return;
    // ������ת��Ϊһ��ָ���������ָ�룬Ȼ���������ɾ���ö���
    _pMonsterVec->eraseObject(reinterpret_cast<MonsterBase*>(pMonster));

    // �����Ա������ʾ���������Ϸ����Ϊ��
    if (_bIsOpenCheckGameEnd)
    {
        // ��������Ĵ�СΪ0����ʾ���еĹ��ﶼ����
        if (!_pMonsterVec->size())
        {
            // ����һ���Զ����͵ı�������ʾ��Ϸʤ����ö��ֵ
            auto tEnGameWin = en_GameWin;
            // �����Ϸ�������ĺ�����ȡ���ܲ�������ֵ���ڵ���1���ͷ���һ����ΪgameEnd��֪ͨ��������Ϸʤ����ö��ֵ��ָ��
            if (GameManager::getInstance()->getICarrotHp() >= 1) NOTIFY->postNotification("gameEnd", reinterpret_cast<Ref*>(&tEnGameWin));
            // ����Ա������ʾ���������Ϸ��������Ϊfalse
            _bIsOpenCheckGameEnd = false;
        }
    }
}

// ����һ������������ĺ���
void MonsterManager::clearManager()
{
    // ���������ĺ�����������еĹ������
    _pMonsterVec->clear();
}

// ����һ�����������Ϸ�����ĺ�����������һ��ָ���������͵�ָ��
void MonsterManager::openCheckGameEnd(cocos2d::Ref* pSender)
{
    // ����Ա������ʾ���������Ϸ��������Ϊtrue
    _bIsOpenCheckGameEnd = true;
}
