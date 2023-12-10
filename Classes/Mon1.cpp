#include "cocos2d.h"
#include "Mon1.h"
#include "AudioEngine.h"

USING_NS_CC;

bool Mon1::is_run_frame = false; // 已经初始化  构造函数不用

//构造函数，调用init（）函数，然后加载两个init动画
Mon1::Mon1() {
	//类属性的初始化
	this->Mon_init();
	this->init_mon_move_animation();
	this->init_mon_die_animation();
	sprite = Sprite::create();
	sprite->setScale(1.6f);
	is_run_frame = true;
	//执行调度器
	this->scheduleUpdate();

}

void Mon1::update(float update_time) {
	time_count += update_time;

	//auto move_sound = AudioEngine::play2d("Music/.ogg", true);//没有
	//auto eat_sound = AudioEngine::play2d("Music/chomp.ogg", true);
	if (is_dead) {
		this->unscheduleUpdate();
		removeFromParent();
	}
} //调度函数  参数调度时间间隔

void Mon1::mon_init() {
	this->mon_id = -1; // 编号 
	this->blood = 10;	// 血量
	this->time_count = 0.0;// 时间计时器  统计使用精灵 到结束
	this->attack_num = 1; //攻击值
	this->move_rate = 0; // 移速 相对于移动时间
	this->mon_type = MonType::Mon_typel; //僵尸类型
	this->is_move = false;//是否处于行走状态
	this->is_dead = false;//是否已经死亡
}// 变量初始化

void Mon1::init_mon_move_animation() {
	//auto Mon1 = Sprite::create("picture/Mon1_1.png");
	//Mon1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	//this->addChild(Mon1, 20);
	//auto animation = Animation::create();//创建了一个新的动画对象。
	//animation->addSpriteFrameWithFile("picture/Mon1_1.png");
	//animation->addSpriteFrameWithFile("picture/Mon1_2.png");//将两个图像帧添加到动画中。
	//animation->setDelayPerUnit(0.5f);   //设置了每帧动画的延迟时间，即每帧动画显示0.5秒
	//animation->setLoops(-1);      //设置了动画循环的次数，-1表示动画会无限循环
	//animation->setRestoreOriginalFrame(true); //设置了动画播放完毕后是否恢复到第一帧
	//mon_move_animate = Animate::create(animation);
	//Mon1->runAction(animate);//使其执行动画
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ZomBies/NomalZombie/ZombieMove/Zombie_default.plist");
	mon_move = getAnimation("pciture/Mon1_%d.png", 2); // 调用加载图片
	auto animation1 = Animation::createWithSpriteFrames(mon_move, 1.0 / 5); // 缓存时间 约小则加载越快  
	mon_move_animate = Animate::create(animation1);

}

void Mon1::init_mon_die_animation() { //死亡动画
	mon_die = getAnimation("pciture/Mondie%d.png", 6); // 调用加载图片
	auto animation1 = Animation::createWithSpriteFrames(mon_die, 1.0 / 5); // 缓存时间 约小则加载越快  
	mon_die_animate = Animate::create(animation1);
}



Vector<SpriteFrame*> Mon1::getAnimation(const char* format, int count) {
	Vector<SpriteFrame*> animFrames;
	auto director = Director::getInstance();//获取了Director类的实例
	auto textureCache = director->getTextureCache();//这行代码获取了纹理缓存的实例
	char str[100];
	for (int i = 1; i <= count; i++) {
		sprintf(str, format, i);//将string按format形式赋初值，将其中%d部分用i代替
		auto texture = textureCache->addImage(str); //从文件系统中加载图片，并将其添加到纹理缓存中
		Size imageSize = texture->getContentSize(); //代码获取了纹理的大小。
		float spriteWidth = imageSize.width;
		float spriteHeight = imageSize.height;
		auto frame = SpriteFrame::create(str, Rect(0, 0, spriteWidth, spriteHeight)); // spriteWidth 和 spriteHeight 需要你根据实际的精灵帧大小进行设置
		animFrames.pushBack(frame);
	}
	return animFrames;
}