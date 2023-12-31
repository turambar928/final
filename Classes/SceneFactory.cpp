#include "SceneFactory.h"
#include "WelcomeScene.h"
#include "PageSelectScene.h"
#include "LevelSelectScene.h"
#include "GameSettingScene.h"
#include "LoadingScene.h"
#include "HelpScene.h"

// SceneFactory 类的成员函数，根据传入的场景类型创建相应的场景对象
Scene* SceneFactory::createScene(const SceneType& rEnSceneType) {
    Scene* pScene = nullptr;  // 初始化场景指针为 nullptr

    // 根据传入的场景类型执行不同的场景创建操作
    switch (rEnSceneType) {
    case en_WelcomeScene:  // 如果是欢迎场景类型
        pScene = WelcomeScene::create();  // 创建欢迎场景对象
        break;
    case en_GameHelpScene:  // 如果是游戏帮助场景类型
        pScene = HelpScene::create();  // 创建游戏帮助场景对象
        break;
    case en_PageSelectScene:  // 如果是页面选择场景类型
        pScene = PageSelectScene::create();  // 创建页面选择场景对象
        break;
    case en_LevelSelectScene:  // 如果是关卡选择场景类型
        pScene = LevelSelectScene::create();  // 创建关卡选择场景对象
        break;
    case en_GameSettingScene:  // 如果是游戏设置场景类型
        pScene = GameSettingScene::create();  // 创建游戏设置场景对象
        break;
    case en_GameScene:  // 如果是游戏场景类型
        pScene = LoadingScene::create();  // 创建加载场景对象
        break;
    default:
        break;
    }

    return pScene;  // 返回创建的场景对象指针
}
