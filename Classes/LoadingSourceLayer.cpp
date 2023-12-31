#include "LoadingSourceLayer.h" //包含加载资源层的头文件

/* 定义一个初始化函数，用于创建对象，返回一个布尔值 */
bool LoadingSourceLayer::init()
{
    bool bRet = false; //定义一个布尔变量，用于存储返回值，初始值为false

    do
    {
        CC_BREAK_IF(!Layer::init()); //调用父类的初始化函数，如果失败，跳出循环
        auto pProgressBarBg = Sprite::create("loading/fight_blood_top.png"); //创建一个精灵，使用loading/fight_blood_top.png图片，表示进度条的背景
        pProgressBarBg->setPosition(465, 50); //将精灵的位置设置为(465, 50)
        addChild(pProgressBarBg); //将精灵添加到当前层中
        pProgressBarBg->setScaleX(1.4f); //将精灵的横向缩放比例设置为1.4f

        auto pProgressBar = ProgressTimer::create(Sprite::create("loading/fight_blood_bg.png")); //创建一个进度计时器，使用Sprite::create("loading/fight_blood_bg.png")创建一个精灵，表示进度条的前景
        pProgressBar->setType(ProgressTimer::Type::BAR); //设置进度计时器的类型为条形
        pProgressBar->setName("progressBar"); //设置进度计时器的名称为"progressBar"
        pProgressBar->setMidpoint(Vec2::ANCHOR_MIDDLE_LEFT); //设置进度计时器的中点为左中
        pProgressBar->setBarChangeRate(Vec2::ANCHOR_BOTTOM_RIGHT); //设置进度计时器的变化率为右下
        pProgressBar->setPercentage(100); //设置进度计时器的百分比为100
        pProgressBar->setPosition(465, 50); //将进度计时器的位置设置为(465, 50)
        addChild(pProgressBar); //将进度计时器添加到当前层中
        pProgressBar->setScaleX(1.4f); //将进度计时器的横向缩放比例设置为1.4f

        _pLoadingTitle = Label::createWithSystemFont("loading", "Arial", 20); //创建一个标签，使用系统字体，文字为"loading"，字体为"Arial"，字号为20
        addChild(_pLoadingTitle); //将标签添加到当前层中
        _pLoadingTitle->setPosition(Vec2(410, 70)); //将标签的位置设置为(410, 70)
        _pLoadingTitle->setAnchorPoint(Vec2(0, 0.5)); //将标签的锚点设置为(0, 0.5)

        bRet = true; //将返回值设为true
    } while (0); //循环条件为0，表示只执行一次

    return bRet; //返回返回值
}

/* 定义一个加载资源的函数，用于异步加载所有资源，添加到精灵帧缓存中 */
void LoadingSourceLayer::loadSource()
{

    auto pDirector = Director::getInstance(); //获取导演的实例，赋值给一个指针变量
    static auto tIndex = 0; //定义一个静态的整数变量，用于存储加载的资源索引，初始值为0
    for (auto& iterSourceFile : ALLSOURCE) //遍历所有资源的向量，每个元素为一个字符串，表示资源文件的名称，使用引用避免拷贝
        pDirector->getInstance()->getTextureCache()->addImageAsync(iterSourceFile + PHOTOPOSTFIX, [&](Texture2D* pTexture) //调用导演的实例的纹理缓存的异步添加图片的函数，参数为图片文件的名称，拼接资源文件的名称和图片后缀，和一个回调函数，参数为一个指向纹理的指针
            {
                SpriteFrameCache::getInstance()->addSpriteFramesWithFile(iterSourceFile + PLISTPOSTFIX, pTexture); //调用精灵帧缓存的实例的添加精灵帧的函数，参数为plist文件的名称，拼接资源文件的名称和plist后缀，和纹理指针
                ++tIndex; //将资源索引加1
                auto tPercentage = tIndex * 1.0f / ALLSOURCE.size() * 100; //计算加载的百分比，赋值给一个浮点变量
                (dynamic_cast<ProgressTimer*>(getChildByName("progressBar")))->setPercentage(tPercentage); //根据名称获取子节点，强制类型转换为进度计时器，然后设置其百分比为加载的百分比
                _pLoadingTitle->setString(StringUtils::format("Loading %.f%%", tPercentage)); //使用字符串工具类，格式化字符串，设置标签的文字为加载的百分比
                if (tIndex == ALLSOURCE.size()) _funShowMenuPanel(); //如果资源索引等于所有资源的大小，表示加载完成，调用显示菜单面板的函数

            });
}

/* 定义一个设置显示菜单面板的函数，用于传递一个函数对象，参数为一个函数对象的引用 */
void LoadingSourceLayer::setFuncShowMenuPanel(const std::function<void()>& rFuncShowMenuPanel)
{
    _funShowMenuPanel = rFuncShowMenuPanel; //将成员变量赋值为函数对象的引用
}

/* 定义一个进入函数，用于在层进入时执行 */
void LoadingSourceLayer::onEnter()
{
    Layer::onEnter(); //调用父类的进入函数
    loadSource(); //调用加载资源的函数
}

