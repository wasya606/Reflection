#ifndef DEMOAPP_H
#define DEMOAPP_H
#include "src/Common/common.h"
#include "Menu/menufactory.h"
#include <list>
#include "demofunctions.h"

class DemoApp
{
public:
    DemoApp();
    ~DemoApp();

    void start();


//Menu handlers
private:
    void mainMenuHandler(MenuItem* item);
    void commandsMenuHandler(MenuItem* item);
    void settingsMenuHandler(MenuItem* item);
    void functionsListMenuHandler(MenuItem* item);
    void cmdListMenuHandler(MenuItem* item);

private:
    enum MenuID
    {
        MAIN_MENU = 0,
        CMD_MENU = 1,
        SET_MENU = 2,
        FUNC_LIST_MENU = 3,
        CMD_LIST_MENU = 4
    };

private:
    void goToMenu(MenuID nextMenuId, int prev = -1);
    void goBack();
    void goToMain();
    void updateMenu();
    void pause();
    void repeatText(const char* text, size_t count, bool isEndl = true);

private:
    List<Menu*> menuList;
    MenuID currentMenuId;


};

#endif // DEMOAPP_H
