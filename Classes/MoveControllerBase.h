// ��ֹͷ�ļ��ظ�����
#ifndef CarrotFantasy_MoveControllerBase_h
#define CarrotFantasy_MoveControllerBase_h

// ������������ͷ�ļ�
#include "MonsterBase.h"

// ����һ���ƶ����������࣬�̳��Խڵ���
class MoveControllerBase : public Node
{
    // �����������Ϊ��Ԫ�࣬���Է����ƶ������������˽�г�Ա
    friend class MonsterBase;
public:

    // �����ƶ�������������������������ͷ��ڴ�
    virtual ~MoveControllerBase();

    // ����һ���麯�����������������ƶ��¼���������һ���������͵ı�������ʾ�ƶ���ʱ����
    virtual void listenerMonster(float t);


private:

    // ����һ��˽�к��������ó�Ա����Ϊ����ָ��Ĺ�����󣬲�����һ��ָ���������ָ��
    void setMonster(MonsterBase* pMomster);

    // ����һ��˽�к�����ɾ���ƶ�·���ĵ�һ����
    void erasePoint();

    // ����һ���麯������ʼ���ƶ����������󣬲�����һ��ָ���������ָ�룬����һ���������͵�ֵ����ʾ�Ƿ��ʼ���ɹ�
    virtual bool init(MonsterBase* pMomster);

    // ����һ����̬����������һ���ƶ����������󣬲�����һ��ָ���������ָ�룬����һ��ָ���ƶ������������ָ��
    static MoveControllerBase* create(MonsterBase* pMomster);

    // ʹ�ú궨�������Ͷ���һ���������͵ĳ�Ա��������ʾ���������ٶȣ��Լ���Ӧ�Ļ�ȡ�����ú���
    CC_SYNTHESIZE_PASS_BY_REF(int, _iMonsterSpeed, IMonsterSpeed);

    // ����һ��˽�к����������ӵ������ͺͶ�����ʱ����������һ���������󣬲�����һ���������͵ı�������ʾ�ӵ������ͣ���һ���������͵ı�������ʾ������ʱ����������һ��ָ�򶯻������ָ��
    Animation* AnimationMaker(int iBulletType, float t);

    // �����ƶ������������˽�й��캯��
    MoveControllerBase() {}
private:

    // ����һ��ָ���������ָ�룬��ʾ�����Ĺ������
    MonsterBase* _pMonster = nullptr;

    // ����һ��ָ���ά������������ָ�룬��ʾ�ƶ�·���ĵ������
    std::vector<Vec2>* _pMapPonits;

};


#endif
