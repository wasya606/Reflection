#include "menuitem.h"
#include <cstring>
#include "../../Logger/Interface/logger.h"

MenuItem::MenuItem(const size_t id, const char *name)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
    this->id = id;
}

MenuItem::~MenuItem()
{
    Logger::debug() << "MenuItem destructor";
    if (name != nullptr)
    {
        delete[] name;
    }
}

char* MenuItem::getName()
{
    return name;
}

size_t MenuItem::getId()
{
    return id;
}
