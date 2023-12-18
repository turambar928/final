#include"AppDelegate.h"
#include "SysMenu.h"
#include"Adventurelayer.h"
#include"setting.h"
USING_NS_CC;

Scene* SysMenu::createScene()
{
    return SysMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SysMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    //可以添加一个全局的if语句来控制声音的开启与关闭
    winSize= Director::getInstance()->getVisibleSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();      //获取当前区域可见度的大小，存于Size中，包括长和宽
    Vec2 origin = Director::getInstance()->getVisibleOrigin();      //获取当前设备可见区域的原点位置，存与origin中，包含x，y
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
   /* auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(SysMenu::menuCloseCallback, this));             //生成菜单的函数

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;   //三个部分组成，可视区域的左下角位0，0位置（也就是origin.x和y的值）
          //visiblesize是窗口的大小，closeitem获取的是按钮的大小，用按钮的中点来对其想x，y坐标
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/

    

    //生成三个选项按钮
    Sprite* adventurenormal = Sprite::create("picture/adventure_normal.png");
    Sprite* bossnormal = Sprite::create("picture/boss_normal.png");
    Sprite* monsternormal = Sprite::create("picture/monster_normal.png");

    Sprite* adventureselected = Sprite::create("picture/adventure_selected.png");
    Sprite* bossselected = Sprite::create("picture/boss_selected.png");
    Sprite* monsterselected = Sprite::create("picture/monster_selected.png");   

    MenuItemSprite* adventure = MenuItemSprite::create(adventurenormal, adventureselected, CC_CALLBACK_1(SysMenu::onadventure, this));
    MenuItemSprite* boss = MenuItemSprite::create(bossnormal, bossselected, CC_CALLBACK_1(SysMenu::menuCloseCallback, this));
    MenuItemSprite* monster = MenuItemSprite::create(monsternormal, monsterselected, CC_CALLBACK_1(SysMenu::menuCloseCallback, this));
    adventure->setScale(2);
    boss->setScale(2);
    monster->setScale(2);
    
    Menu*menu1 = Menu::create(adventure, boss, monster, NULL);
    menu1->alignItemsHorizontallyWithPadding(40);  //横盘排列，同时中间间隔为40
    menu1->setPosition(Vec2(visibleSize.width / 4+330, visibleSize.height / 4-100)); 
    this->addChild(menu1, 1);
     
    //生成左右两边的按钮
    Sprite* settingnormal = Sprite::create("picture/setting_normal.png");
    Sprite* questionnormal = Sprite::create("picture/question_normal.png");

    Sprite* settingselected = Sprite::create("picture/setting_selected.png");
    Sprite* questionselected = Sprite::create("picture/question_selected.png");

    MenuItemSprite* setting = MenuItemSprite::create(settingnormal, settingselected, CC_CALLBACK_1(SysMenu::onsetting, this));
    MenuItemSprite* question = MenuItemSprite::create(questionnormal, questionselected, CC_CALLBACK_1(SysMenu::menuCloseCallback, this));
    setting->setScale(2);
    question->setScale(2);
    Menu* menu2 = Menu::create(setting,question, NULL);
    menu2->alignItemsHorizontallyWithPadding(visibleSize.width / 2+30);  //横盘排列，同时中间间隔为40
    menu2->setPosition(Vec2(visibleSize.width / 4 + 370, visibleSize.height / 4+100 ));
    this->addChild(menu2, 2);
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello Carrot", "fonts/Marker Felt.ttf", 48);     //输出内容+字体+大小
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
            origin.y + visibleSize.height  - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
    //窗口大小1353,908
    // add "HelloWorld" splash screen"      
    //放置最底层的背景图
    auto sprite = Sprite::create("picture/mainscene.png");//在picture文件夹中的图片，若是想要访问，需要添加picture/   。
    if (sprite == nullptr)
    {
        problemLoading("'mainscene.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);     //让图片的左下角与0 0对齐
        //sprite->setPosition()功能类似
        sprite->setScale(1.6);           //图片放大1.6倍
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);     //放在最底层
    }

    //放左边的一片叶子
    auto sprite_leftleaf = Sprite::create("picture/leaf1.png");
    if (sprite_leftleaf == nullptr)           //传输图片错误
    {
        problemLoading("'leaf1.png'");
    }
    else
    {
        sprite_leftleaf->setPosition(Vec2(origin.x + visibleSize.width / 2-60, 
            origin.y + visibleSize.height - 3*sprite_leftleaf->getContentSize().height+10));
        sprite_leftleaf->setScale(1.9);          
        // add the sprite as a child to this layer
        this->addChild(sprite_leftleaf, 2);
    }
    //放右间的叶子
    auto sprite_rightleaf = Sprite::create("picture/leaf2.png");
    if (sprite_rightleaf == nullptr)           //传输图片错误
    {
        problemLoading("'leaf2.png'");
    }
    else
    {
        sprite_rightleaf->setPosition(Vec2(origin.x + visibleSize.width / 2 + 80+60,
            origin.y + visibleSize.height - 3 * sprite_rightleaf->getContentSize().height));
        sprite_rightleaf->setScale(1.9);
        // add the sprite as a child to this layer
        this->addChild(sprite_rightleaf, 2);
    }
    //中间叶子
    auto sprite_midleaf = Sprite::create("picture/leaf3.png");
    if (sprite_midleaf == nullptr)           //传输图片错误
    {
        problemLoading("'leaf3.png'");
    }
    else
    {
        sprite_midleaf->setPosition(Vec2(origin.x + visibleSize.width / 2+30, 
            origin.y + visibleSize.height - 3 * sprite_midleaf->getContentSize().height+80));
        sprite_midleaf->setScale(2.1);
        // add the sprite as a child to this layer
        this->addChild(sprite_midleaf, 3);
    }
    //萝卜身体部分
    auto carrot_body = Sprite::create("picture/mainscene-car.png");
    if (carrot_body == nullptr)           //传输图片错误
    {
        problemLoading("'mainscene-car.png'");
    }
    else
    {
        carrot_body->setPosition(Vec2(origin.x + visibleSize.width / 2 + 45, 
            origin.y + visibleSize.height/2 +carrot_body->getContentSize().height/2+30));
        carrot_body->setScale(2.3);
        // add the sprite as a child to this layer
        this->addChild(carrot_body, 4); 
    }
    //标题
    auto mainscene_title = Sprite::create("picture/mainscene1-title.png");
    if (mainscene_title == nullptr)           //传输图片错误
    {
        problemLoading("'mainscene1-title.png'");
    }
    else
    {
        mainscene_title->setPosition(Vec2(origin.x + visibleSize.width / 2 + 45,
            origin.y + visibleSize.height / 2 - mainscene_title->getContentSize().height / 2 + 60));
        mainscene_title->setScale(2.3);
        // add the sprite as a child to this layer
        this->addChild(mainscene_title, 5);
    }
    //蝙蝠
    auto mainscene_bat = Sprite::create("picture/mainscene1-bat.png");
    if (mainscene_bat == nullptr)           //传输图片错误
    {
        problemLoading("'mainscene1-bat.png'");
    }
    else
    {
        mainscene_bat->setPosition(Vec2(origin.x + visibleSize.width / 4 -45,
            origin.y +3* visibleSize.height / 4 - mainscene_bat->getContentSize().height / 2 + 60));
        mainscene_bat->setScale(2.0);
        // add the sprite as a child to this layer
        this->addChild(mainscene_bat, 2);
    }
    this->schedule(CC_SCHEDULE_SELECTOR(SysMenu::update),0.1/10);
    //会飘动的
    mainscene_monster = Sprite::create("picture/mainscene1-monster.png");
    if (mainscene_monster == nullptr)           //传输图片错误
    {
        problemLoading("'mainscene1-monster.png'");
    }
    else
    {
        mainscene_monster->setPosition(Vec2(origin.x + visibleSize.width / 4 - 45,
            origin.y + 3 * visibleSize.height / 4 + mainscene_monster->getContentSize().height + 90));
        mainscene_monster->setScale(2.0);//1-2间随机大小
        // add the sprite as a child to this layer
        this->addChild(mainscene_monster, 10);    //添加到场景上
        //Point position = Point(0, CCRANDOM_0_1() * visibleSize.height);//设置初始位置
        //mainscene_monster->setPosition(position);//放置于特定位置
       // mainscene_monster->runAction(MoveBy::create(2* CCRANDOM_0_1()+1, Point(visibleSize.width, 0)));//完成时间1-3秒，方向向右。

    }
    auto Mon1 = Sprite::create("picture/Mon1_1.png");
    Mon1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(Mon1, 20);
    auto animation = Animation::create();//创建了一个新的动画对象。
    animation->addSpriteFrameWithFile("picture/Mon1_1.png");
    animation->addSpriteFrameWithFile("picture/Mon1_2.png");//将两个图像帧添加到动画中。
    animation->setDelayPerUnit(0.5f);   //设置了每帧动画的延迟时间，即每帧动画显示0.5秒
    animation->setLoops(-1);      //设置了动画循环的次数，-1表示动画会无限循环
    animation->setRestoreOriginalFrame(true); //设置了动画播放完毕后是否恢复到第一帧
    auto animate = Animate::create(animation);
    Mon1->runAction(animate);//使其执行动画
    
    return true;

}


void SysMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    onButtonEffect();
    //Director::getInstance()->end();   //终止程序

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void SysMenu::onadventure(Ref* pSender) {
    onButtonEffect();
    Scene* scene = Adventure_layer::scene();
    Director::getInstance()->replaceScene(TransitionFade::create(2, scene));

}

void SysMenu::onsetting(Ref* pSender) {
    onButtonEffect();
    Scene* scene = setting_layer::scene();
    Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}
void SysMenu::onButtonEffect() {
    //此处可以加一个if语句，来控制什么时候让声音输出。
    auto effect_audio = AudioEngine::play2d("music/Select.mp3");
}

void SysMenu::update(float dt) {
    Vec2 a = mainscene_monster->getPosition();
    if (a.x > winSize.width) {
        Point pos = Point(60, CCRANDOM_0_1() * winSize.height);
        mainscene_monster->setPosition(pos);
    }
    else {
        mainscene_monster->setPosition(Vec2(a.x + 10, a.y));
    }
   /* if (mainscene_monster->getPosition().x > winSize.width) {
        Point pos = Point(60, CCRANDOM_0_1() * winSize.height);
        mainscene_monster->setPosition(pos);
        mainscene_monster->runAction(MoveBy::create(floor(20 * CCRANDOM_0_1()), Point(1353, 0)));//前一个参数控制运动的时间，后一个参数控制运动的距离
    }*/
}

void SysMenu::onEnter() {//这个函数在进入窗口的时候就会执行
    Scene::onEnter();
    int judgemusic = 0;
    // 检查是否正在播放背景音乐
    if (AudioEngine::getState(judgemusic) == AudioEngine::AudioState::PLAYING)
    {
        // 获取当前播放的音乐文件名
        //std::string currentMusic;

        // 检查当前播放的音乐是否是你需要的音乐
        //if (currentMusic == "BGMusic.mp3")
        //{
            // 如果不是你需要的音乐，那么停止
            
        //AudioEngine::stop(judgemusic);
        //}
    }
    else {
        auto effect_audio1 = AudioEngine::play2d("music/BGMusic.mp3", 1);
    }
}