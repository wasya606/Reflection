#include "menu.h"
#include <cstring>
#include <stdio.h>
#include "../../Logger/Interface/logger.h"

#ifdef _WIN32
    #include <conio.h>
    int Menu::getKey()
    {
        return getch();
    }

    void Menu::clearScreen()
    {
        system("cls");
    }
#else
    #include <termios.h>
    #include <unistd.h>

    int Menu::getKey()
    {
        struct termios oldt, newt;
        int ch;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

        return ch;
    }

    void Menu::clearScreen()
    {
        std::cout << "\033[2J\033[1;1H";
    }
#endif


Menu::Menu(const char *title, MenuHandler handler, int prev) : activeItemId(0), size(0)
{
    this->prev = prev;
    this->title = new char[strlen(title) + 1];
    strcpy(this->title, title);
    this->handler = handler;
}

Menu::~Menu()
{
    Logger::debug() << "Menu destructor";
    if (title != nullptr)
    {
        delete[] title;
    }

    for (size_t i = 0; i < items.getSize(); i++)
    {
        if (items[i] != nullptr)
            delete items[i];
    }
}

void Menu::pushItem(const char *name)
{
    items.push(new MenuItem(size, name));
    size++;
}

char* Menu::getTitle()
{
    return title;
}

int Menu::getPrev()
{
    return prev;
}

void Menu::setPrev(int prev)
{
    this->prev = prev;
}

size_t Menu::getSize()
{
    return size;
}

MenuItem *Menu::getItem(size_t id)
{
    return items[id];
}

size_t Menu::getActiveItemId()
{
    return activeItemId;
}

void Menu::resetActiveItem()
{
    activeItemId = 0;
}

bool Menu::processStep(int keyCode)
{
    bool result = true;
    if (keyCode == 0 || keyCode == 224 || (keyCode == 27 && getKey() == 91))
    {
        int input = getKey();
        if (input == 72 || input == 65)
        {
            doStepUp();
        }
        else if (input == 80 || input == 66)
        {
            doStepDown();
        }
    }
    else if (keyCode == 13 || keyCode == 10)
    {
        handler(getItem(activeItemId));
    }
    else
    {
        result = false;
    }

    return result;

}

void Menu::doStepUp()
{
    if (activeItemId > 0)
    {
        activeItemId--;
    }
    else
    {
        activeItemId = size - 1;
    }
}

void Menu::doStepDown()
{
    if (activeItemId < size - 1)
    {
        activeItemId++;
    }
    else
    {
        activeItemId = 0;
    }

}
