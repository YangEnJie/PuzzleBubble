#include "AppDelegate.h"
//#include "HelloWorldScene.h"
#include "StartScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::createWithRect("Puzzle_Bubble", Rect(0, 0, 540, 960));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(540, 960, ResolutionPolicy::FIXED_WIDTH);

	director->getOpenGLView()->setFrameZoomFactor(0.5f);
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    FileUtils::getInstance()->addSearchPath("res");

	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/bgm.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Ending.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Fuhuo.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Guoguan.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Click.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Clock.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Remove.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Hit.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/Bomb.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/start.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("Music/end.mp3");

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
	auto scene = StartLayer::scene();
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
