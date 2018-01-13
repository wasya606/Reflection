TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.cpp \
    src/Common/common.cpp \
    src/Reflection/Impl/commandmanager.cpp \
    src/Reflection/Impl/typetools.cpp \
    src/Logger/Impl/loggerImpl.cpp \
    src/Settings/Impl/settingsimpl.cpp \
    src/DemoApp/Menu/menu.cpp \
    src/DemoApp/demoapp.cpp \
    src/DemoApp/Menu/menuitem.cpp \
    src/DemoApp/Menu/menufactory.cpp \
    src/Reflection/Impl/internaltypes.cpp \
    src/DemoApp/demofunctions.cpp \
    src/Reflection/Impl/functioninfo.cpp \
    src/Reflection/Impl/tempstorage.cpp \
    src/Common/nameencoder.cpp

HEADERS += \
    src/Common/common.h \
    src/Reflection/Impl/commandmanager.h \
    src/Reflection/Impl/typetools.h \
    src/Reflection/Interface/reflection.h \
    src/Logger/Impl/loggerImpl.h \
    src/Logger/Interface/logger.h \
    src/Settings/Impl/settingsimpl.h \
    src/Settings/Interface/settings.h \
    src/Reflection/Interface/reflectionfactory.h \
    src/DemoApp/Menu/menu.h \
    src/DemoApp/demoapp.h \
    src/DemoApp/Menu/menuitem.h \
    src/DemoApp/cmd_functions.h \
    src/DemoApp/Menu/menufactory.h \
    src/Reflection/Impl/internaltypes.h \
    src/DemoApp/demofunctions.h \
    src/Reflection/Impl/functioninfo.h \
    src/Reflection/Impl/functiondata.hpp \
    src/Reflection/Impl/tempstorage.h \
    src/Common/nameencoder.h
