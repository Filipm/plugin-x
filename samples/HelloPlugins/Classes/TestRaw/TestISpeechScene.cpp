/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "TestISpeechScene.h"
#include "HelloWorldScene.h"
#include "Configs.h"

using namespace cocos2d;
using namespace cocos2d::plugin;

enum {
    TAG_READ_TEXT = 0
};

typedef struct tagEventMenuItem {
    std::string id;
    int tag;
}EventMenuItem;

static EventMenuItem s_EventMenuItem[] = {
    {"Read-text",        TAG_READ_TEXT}
};

Scene* TestISpeech::scene()
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    TestISpeech *layer = TestISpeech::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestISpeech::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    _pluginAnalytics = NULL;
    loadPlugins();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    Point posBR = Point(origin.x + visibleSize.width, origin.y);

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    MenuItemFont *pBackItem = MenuItemFont::create("Back", CC_CALLBACK_1(TestISpeech::menuBackCallback, this));
    Size backSize = pBackItem->getContentSize();
    pBackItem->setPosition(posBR + Point(- backSize.width / 2, backSize.height / 2));

    // create menu, it's an autorelease object
    Menu* pMenu = Menu::create(pBackItem, NULL);
    pMenu->setPosition( Point::ZERO );
    this->addChild(pMenu, 1);

    float yPos = 0;
    for (int i = 0; i < sizeof(s_EventMenuItem)/sizeof(s_EventMenuItem[0]); i++) {
        LabelTTF* label = LabelTTF::create(s_EventMenuItem[i].id.c_str(), "Arial", 24);
        MenuItemLabel* pMenuItem = MenuItemLabel::create(label, CC_CALLBACK_1(TestISpeech::eventMenuCallback, this));
        pMenu->addChild(pMenuItem, 0, s_EventMenuItem[i].tag);
        yPos = visibleSize.height - 35*i - 100;
        pMenuItem->setPosition( Point(visibleSize.width / 2, yPos));
    }

    std::string strName = _pluginAnalytics->getPluginName();
    std::string strVer = _pluginAnalytics->getSDKVersion();
    char ret[256] = { 0 };
    sprintf(ret, "Plugin : %s, Ver : %s", strName.c_str(), strVer.c_str());
    LabelTTF* pLabel = LabelTTF::create(ret, "Arial", 18, Size(visibleSize.width, 0), TextHAlignment::CENTER);
    pLabel->setPosition(Point(visibleSize.width / 2, yPos - 80));
    addChild(pLabel);

    return true;
}

void TestISpeech::onExit()
{
    unloadPlugins();
}

void TestISpeech::eventMenuCallback(Object* pSender)
{
    MenuItemLabel* pMenuItem = (MenuItemLabel*)pSender;

    switch (pMenuItem->getTag())
    {
    case TAG_READ_TEXT:
        {
			PluginParam* paramLanguage = new PluginParam ( "usenglishfemale" );
			PluginParam* paramText = new PluginParam ( "Hello iSpeech test here. Please leave message" );

			pPluginISpeech->callFuncWithParam ( "setVoiceType", paramLanguage, NULL );
			int result = pPluginISpeech->callIntFuncWithParam ( "speak", paramText, NULL );

			CCLog ( "Result code %d", result );

			CC_SAFE_DELETE ( paramLanguage );
			CC_SAFE_DELETE ( paramText );
        }
        break;
    default:
        break;
    }
}

void TestISpeech::loadPlugins()
{
	_plugin = PluginManager::getInstance()->loadPlugin ( "ISpeech" );
	assert ( pPluginISpeech );
}

void TestISpeech::unloadPlugins()
{
    if (NULL != _plugin) {
        _plugin->stopSession();

        std::string pluginName = _plugin->getPluginName();
        PluginManager::getInstance()->unloadPlugin(pluginName.c_str());
        _plugin = NULL;
    }
}

void TestISpeech::menuBackCallback(Object* pSender)
{
    Scene* newScene = HelloWorld::scene();
    Director::getInstance()->replaceScene(newScene);
}
