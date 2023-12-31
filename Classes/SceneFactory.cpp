#include "SceneFactory.h"
#include "WelcomeScene.h"
#include "PageSelectScene.h"
#include "LevelSelectScene.h"
#include "GameSettingScene.h"
#include "LoadingScene.h"
#include "HelpScene.h"

// SceneFactory ��ĳ�Ա���������ݴ���ĳ������ʹ�����Ӧ�ĳ�������
Scene* SceneFactory::createScene(const SceneType& rEnSceneType) {
    Scene* pScene = nullptr;  // ��ʼ������ָ��Ϊ nullptr

    // ���ݴ���ĳ�������ִ�в�ͬ�ĳ�����������
    switch (rEnSceneType) {
    case en_WelcomeScene:  // ����ǻ�ӭ��������
        pScene = WelcomeScene::create();  // ������ӭ��������
        break;
    case en_GameHelpScene:  // �������Ϸ������������
        pScene = HelpScene::create();  // ������Ϸ������������
        break;
    case en_PageSelectScene:  // �����ҳ��ѡ�񳡾�����
        pScene = PageSelectScene::create();  // ����ҳ��ѡ�񳡾�����
        break;
    case en_LevelSelectScene:  // ����ǹؿ�ѡ�񳡾�����
        pScene = LevelSelectScene::create();  // �����ؿ�ѡ�񳡾�����
        break;
    case en_GameSettingScene:  // �������Ϸ���ó�������
        pScene = GameSettingScene::create();  // ������Ϸ���ó�������
        break;
    case en_GameScene:  // �������Ϸ��������
        pScene = LoadingScene::create();  // �������س�������
        break;
    default:
        break;
    }

    return pScene;  // ���ش����ĳ�������ָ��
}
