#ifndef MENUITEM_H
#define MENUITEM_H
#include <functional>

class MenuItem
{
public:
    MenuItem(const size_t id, const char *name);
    ~MenuItem();

    char* getName();
    size_t getId();

private:
    size_t id;
    char *name;
};

#endif // MENUITEM_H
