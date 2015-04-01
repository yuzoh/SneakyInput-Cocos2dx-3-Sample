#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    mLabel = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    mLabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - mLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(mLabel, 1);

    // add "HelloWorld" splash screen"
    mSprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    mSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(mSprite, 0);
    
    
    mJoystick = new SneakyJoystick();
    mJoystick->initWithRect(Rect( 0, 0, 75.0f, 75.0f));
    mJoystick->autorelease();
    mJoystick->setAutoCenter(true);
    mJoystick->setHasDeadzone(true);
    mJoystick->setDeadRadius(20.0f);
    
    mSkinjoystick = SneakyJoystickSkinnedBase::create();
    mSkinjoystick->setBackgroundSprite(CCSprite::create("joystick1.png"));
    mSkinjoystick->setThumbSprite(CCSprite::create("joystick2.png"));
    mSkinjoystick->setJoystick(mJoystick);
    mSkinjoystick->setPosition(Vec2( visibleSize.width / 2 , visibleSize.height / 5));
    
    this->addChild(mSkinjoystick,10);
    this->scheduleUpdate();
    
    return true;
}

void HelloWorld::update(float delta){
    Vec2 pos = mSprite->getPosition();
    pos.add(mJoystick->getVelocity());
    mSprite->setPosition(pos);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
