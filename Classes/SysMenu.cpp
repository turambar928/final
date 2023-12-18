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

    //�������һ��ȫ�ֵ�if��������������Ŀ�����ر�
    winSize= Director::getInstance()->getVisibleSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();      //��ȡ��ǰ����ɼ��ȵĴ�С������Size�У��������Ϳ�
    Vec2 origin = Director::getInstance()->getVisibleOrigin();      //��ȡ��ǰ�豸�ɼ������ԭ��λ�ã�����origin�У�����x��y
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
   /* auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(SysMenu::menuCloseCallback, this));             //���ɲ˵��ĺ���

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;   //����������ɣ�������������½�λ0��0λ�ã�Ҳ����origin.x��y��ֵ��
          //visiblesize�Ǵ��ڵĴ�С��closeitem��ȡ���ǰ�ť�Ĵ�С���ð�ť���е���������x��y����
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);*/

    

    //��������ѡ�ť
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
    menu1->alignItemsHorizontallyWithPadding(40);  //�������У�ͬʱ�м���Ϊ40
    menu1->setPosition(Vec2(visibleSize.width / 4+330, visibleSize.height / 4-100)); 
    this->addChild(menu1, 1);
     
    //�����������ߵİ�ť
    Sprite* settingnormal = Sprite::create("picture/setting_normal.png");
    Sprite* questionnormal = Sprite::create("picture/question_normal.png");

    Sprite* settingselected = Sprite::create("picture/setting_selected.png");
    Sprite* questionselected = Sprite::create("picture/question_selected.png");

    MenuItemSprite* setting = MenuItemSprite::create(settingnormal, settingselected, CC_CALLBACK_1(SysMenu::onsetting, this));
    MenuItemSprite* question = MenuItemSprite::create(questionnormal, questionselected, CC_CALLBACK_1(SysMenu::menuCloseCallback, this));
    setting->setScale(2);
    question->setScale(2);
    Menu* menu2 = Menu::create(setting,question, NULL);
    menu2->alignItemsHorizontallyWithPadding(visibleSize.width / 2+30);  //�������У�ͬʱ�м���Ϊ40
    menu2->setPosition(Vec2(visibleSize.width / 4 + 370, visibleSize.height / 4+100 ));
    this->addChild(menu2, 2);
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello Carrot", "fonts/Marker Felt.ttf", 48);     //�������+����+��С
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
    //���ڴ�С1353,908
    // add "HelloWorld" splash screen"      
    //������ײ�ı���ͼ
    auto sprite = Sprite::create("picture/mainscene.png");//��picture�ļ����е�ͼƬ��������Ҫ���ʣ���Ҫ���picture/   ��
    if (sprite == nullptr)
    {
        problemLoading("'mainscene.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);     //��ͼƬ�����½���0 0����
        //sprite->setPosition()��������
        sprite->setScale(1.6);           //ͼƬ�Ŵ�1.6��
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);     //������ײ�
    }

    //����ߵ�һƬҶ��
    auto sprite_leftleaf = Sprite::create("picture/leaf1.png");
    if (sprite_leftleaf == nullptr)           //����ͼƬ����
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
    //���Ҽ��Ҷ��
    auto sprite_rightleaf = Sprite::create("picture/leaf2.png");
    if (sprite_rightleaf == nullptr)           //����ͼƬ����
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
    //�м�Ҷ��
    auto sprite_midleaf = Sprite::create("picture/leaf3.png");
    if (sprite_midleaf == nullptr)           //����ͼƬ����
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
    //�ܲ����岿��
    auto carrot_body = Sprite::create("picture/mainscene-car.png");
    if (carrot_body == nullptr)           //����ͼƬ����
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
    //����
    auto mainscene_title = Sprite::create("picture/mainscene1-title.png");
    if (mainscene_title == nullptr)           //����ͼƬ����
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
    //����
    auto mainscene_bat = Sprite::create("picture/mainscene1-bat.png");
    if (mainscene_bat == nullptr)           //����ͼƬ����
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
    //��Ʈ����
    mainscene_monster = Sprite::create("picture/mainscene1-monster.png");
    if (mainscene_monster == nullptr)           //����ͼƬ����
    {
        problemLoading("'mainscene1-monster.png'");
    }
    else
    {
        mainscene_monster->setPosition(Vec2(origin.x + visibleSize.width / 4 - 45,
            origin.y + 3 * visibleSize.height / 4 + mainscene_monster->getContentSize().height + 90));
        mainscene_monster->setScale(2.0);//1-2�������С
        // add the sprite as a child to this layer
        this->addChild(mainscene_monster, 10);    //��ӵ�������
        //Point position = Point(0, CCRANDOM_0_1() * visibleSize.height);//���ó�ʼλ��
        //mainscene_monster->setPosition(position);//�������ض�λ��
       // mainscene_monster->runAction(MoveBy::create(2* CCRANDOM_0_1()+1, Point(visibleSize.width, 0)));//���ʱ��1-3�룬�������ҡ�

    }
    auto Mon1 = Sprite::create("picture/Mon1_1.png");
    Mon1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(Mon1, 20);
    auto animation = Animation::create();//������һ���µĶ�������
    animation->addSpriteFrameWithFile("picture/Mon1_1.png");
    animation->addSpriteFrameWithFile("picture/Mon1_2.png");//������ͼ��֡��ӵ������С�
    animation->setDelayPerUnit(0.5f);   //������ÿ֡�������ӳ�ʱ�䣬��ÿ֡������ʾ0.5��
    animation->setLoops(-1);      //�����˶���ѭ���Ĵ�����-1��ʾ����������ѭ��
    animation->setRestoreOriginalFrame(true); //�����˶���������Ϻ��Ƿ�ָ�����һ֡
    auto animate = Animate::create(animation);
    Mon1->runAction(animate);//ʹ��ִ�ж���
    
    return true;

}


void SysMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    onButtonEffect();
    //Director::getInstance()->end();   //��ֹ����

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
    //�˴����Լ�һ��if��䣬������ʲôʱ�������������
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
        mainscene_monster->runAction(MoveBy::create(floor(20 * CCRANDOM_0_1()), Point(1353, 0)));//ǰһ�����������˶���ʱ�䣬��һ�����������˶��ľ���
    }*/
}

void SysMenu::onEnter() {//��������ڽ��봰�ڵ�ʱ��ͻ�ִ��
    Scene::onEnter();
    int judgemusic = 0;
    // ����Ƿ����ڲ��ű�������
    if (AudioEngine::getState(judgemusic) == AudioEngine::AudioState::PLAYING)
    {
        // ��ȡ��ǰ���ŵ������ļ���
        //std::string currentMusic;

        // ��鵱ǰ���ŵ������Ƿ�������Ҫ������
        //if (currentMusic == "BGMusic.mp3")
        //{
            // �����������Ҫ�����֣���ôֹͣ
            
        //AudioEngine::stop(judgemusic);
        //}
    }
    else {
        auto effect_audio1 = AudioEngine::play2d("music/BGMusic.mp3", 1);
    }
}