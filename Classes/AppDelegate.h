#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"
#include "MainMenu.h"

USING_NS_CC;

/**
@brief    The cocos2d Application.
Private inheritance here hides part of interface from Director.
*/
class  AppDelegate : private Application
{
public:

    AppDelegate();
    ~AppDelegate() override;

    void initGLContextAttrs() override;

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    bool applicationDidFinishLaunching() override;

    /**
    @brief  Called when the application moves to the background
    @param  the pointer of the application
    */
    void applicationDidEnterBackground() override;

    /**
    @brief  Called when the application reenters the foreground
    @param  the pointer of the application
    */
    void applicationWillEnterForeground() override;
};

#endif // _APP_DELEGATE_H_

