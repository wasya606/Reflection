#include "demoapp.h"
#include <iostream>
#include <cstring>
#include <functional>


using namespace std;
using namespace placeholders;

DemoApp::DemoApp() : currentMenuId(MAIN_MENU)
{
    menuList.push(MenuFactory::createMainMenu(bind(&DemoApp::mainMenuHandler, this, _1)));
    menuList.push(MenuFactory::createCommandsMenu(bind(&DemoApp::commandsMenuHandler, this, _1), (int)MAIN_MENU));
    menuList.push(MenuFactory::createSettingsMenu(bind(&DemoApp::settingsMenuHandler, this, _1), (int)MAIN_MENU));



    StringList availableFunctions;
    /*availableFunctions.push("void demo0()");
    availableFunctions.push("void demo1_int(int)");
    availableFunctions.push("void demo1_charPtr(char*)");
    availableFunctions.push("void demo1_doubleRRef(const double&&)");
    availableFunctions.push("void demo3_0(const int,bool&,const char *&)");
    availableFunctions.push("void demo3_1(bool,double&,const char*)");
    availableFunctions.push("void demo5(long&&,void*,const char&,const double,long double&&)");
    availableFunctions.push("void SpiTools::initSpiMaster(void*,double,bool,int)");
    availableFunctions.push("void SpiTools::sendToSpi(void*,const char*,int)");
    availableFunctions.push("void SpiTools::startReceiveFromSpi(void*,const char*,int)");*/
    menuList.push(MenuFactory::createFunctionsListMenu(bind(&DemoApp::functionsListMenuHandler, this, _1),
                                                       availableFunctions, (int)CMD_MENU));
    menuList.push(MenuFactory::createCmdListMenu(bind(&DemoApp::cmdListMenuHandler, this, _1), (int)CMD_MENU));
}

DemoApp::~DemoApp()
{

}

void DemoApp::start()
{
    bool needUpdate = true;
    do
    {
        Menu* menu = menuList[(size_t)currentMenuId];
        if (needUpdate)
            updateMenu();

        needUpdate = menu->processStep(Menu::getKey());
    }
    while (1);

}

void DemoApp::updateMenu()
{
    Menu* menu = menuList[(size_t)currentMenuId];

    Menu::clearScreen();

    cout << endl << endl << "\t" << menu->getTitle() << endl << endl;
    for (size_t i = 0; i < menu->getSize(); i++)
    {
        char* name = menu->getItem(i)->getName();
        size_t nameLen = strlen(name);
        size_t activeItem = menu->getActiveItemId();
        if (activeItem == i)
        {
            cout << "\t";
            repeatText("=", nameLen + 6);
            cout << "\t|  " << menu->getItem(i)->getName() << "  |\n";
            cout << "\t";
            repeatText("=", nameLen + 6);
        }
        else
        {
            if (activeItem != i - 1)
                cout << endl;

            cout << "\t  " << menu->getItem(i)->getName() << endl;
        }
    }
    cout << endl;
}

void DemoApp::pause()
{
    cout << "Press any key to continue...\n";
    Menu::getKey();
}

void DemoApp::repeatText(const char *text, size_t count, bool isEndl)
{
    for (size_t i = 0; i < count; i++)
        cout << text;

    if (isEndl)
        cout << endl;
}

void DemoApp::mainMenuHandler(MenuItem *item)
{
    switch (item->getId())
    {
        case 0:
        {
            goToMenu(CMD_MENU);
            break;
        }
        case 1:
        {
            goToMenu(SET_MENU);
            break;
        }
        case 2:
        {
            cout << "\t\t* REFLECTION DEMO APP *\n";
            cout << "\tDemonstrates the possibilities of reflection on C++\n\n";
            pause();
            break;
        }
        case 3:
        {
            cout << "Good by!\n";
            exit(0);
            break;
        }
        default:
            break;
    }

}

void DemoApp::commandsMenuHandler(MenuItem *item)
{
    switch (item->getId())
    {
        case 0:
        {
            pause();
            break;
        }
        case 1:
        {
            pause();
            break;
        }
        case 2:
        {
            pause();
            break;
        }
        case 3:
        {
            pause();
            break;
        }
        case 4:
        {
            goToMenu(FUNC_LIST_MENU);
            break;
        }
        case 5:
        {
            pause();
            break;
        }
        case 6:
        {
            pause();
            break;
        }
        case 7:
        {
            goBack();
            break;
        }
        default:
            break;
    }
}

void DemoApp::settingsMenuHandler(MenuItem *item)
{
    switch (item->getId())
    {
        case 0:
        {
            pause();
            break;
        }
        case 1:
        {
            pause();
            break;
        }
        case 2:
        {
            pause();
            break;
        }
        case 3:
        {
            pause();
            break;
        }
        case 4:
        {
            goBack();
            break;
        }
        default:
            break;
    }
}

void DemoApp::functionsListMenuHandler(MenuItem *item)
{
    switch (item->getId())
    {
        case 1:
        {
            goToMenu(CMD_LIST_MENU);
            break;
        }
        case 10:
        {
            goBack();
            break;
        }
        default:
        {
            pause();
            break;
        }
    }
}

void DemoApp::cmdListMenuHandler(MenuItem *item)
{
    switch (item->getId())
    {
        case 1:
        {
            goToMenu(SET_MENU, -2);
            break;
        }
        case 4:
        {
            goBack();
            break;
        }
        default:
        {
            pause();
            break;
        }
    }
}

void DemoApp::goBack()
{
    int prev = menuList[(size_t)currentMenuId]->getPrev();
    if (prev >= 0)
    {
        goToMenu((MenuID)prev, -2);
    }
}

void DemoApp::goToMain()
{
    menuList[(size_t)MAIN_MENU]->setPrev();
    currentMenuId = MAIN_MENU;
}

void DemoApp::goToMenu(MenuID nextMenuId, int prev)
{
    if (prev > -2)
    {
        MenuID prevMenu = prev == -1 ? currentMenuId : (MenuID)prev;
        menuList[(size_t)nextMenuId]->setPrev(prevMenu);
        menuList[(size_t)nextMenuId]->resetActiveItem();
    }

    currentMenuId = nextMenuId;
}
