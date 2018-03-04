/**  @details:
 *   This is a solution for implementation of Reflection using C++11
 *   Task:
 *   1. Provide ability of registering a pointer on function as command with a some name like as:
 *      ...
 *      void func1(int, double, char*, bool);
 *      void func2(void*, int, bool);
 *      ...
 *      ReflectionClass reflectionObj;
 *      reflectionObj.registerCommand("cmd1", &func1);
 *      reflectionObj.registerCommand("cmd2", &func2);
 *      ...
 *   2. Provide ability to call a registered function from string like to run command:
 *      ...
 *      reflectionObj.runCommand("cmd1 111 222.222 param3 true");
 *      reflectionObj.runCommand("cmd2 0x7a70 222 false");
 *      ...
 *
 *   @author: Vasyl Dykyi
 */
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "src/DemoApp/cmd_functions.h"
#include "src/Common/common.h"
#include "src/Settings/Impl/settingsimpl.h"
#include "src/DemoApp/demoapp.h"
#include "src/Reflection/Interface/reflection.h"
#include "src/Reflection/Interface/reflectionfactory.h"
#include "Logger/Interface/logger.h"

using namespace std;
using namespace Common;

void test();

void initSettings();

Reflection* reflection = ReflectionFactory::getReflection();

int main()
{   
    initSettings();

    test();

    //DemoApp demoApp;
    //demoApp.start();

    return 0;
}

void test()
{

    reflection->registerCommand("SpiInit", &CmdFunc::SpiTools::initSpiMaster);
    reflection->registerCommand("SpiWriteStr", &CmdFunc::SpiTools::sendToSpi);
    reflection->registerCommand("SpiRead", &CmdFunc::SpiTools::startReceiveFromSpi);

    reflection->registerCommand("TEST_0", &CmdFunc::test0);
    reflection->registerCommand("TEST_1", &CmdFunc::test1);
    reflection->registerCommand("TEST_1", &CmdFunc::test0);


    cout << endl << endl;

    reflection->runCommand("SpiInit 0xc1558d88 8.523 true 0x2ff");
    reflection->runCommand("SpiWriteStr 0xc1108d88 abcdefdata 10");
    reflection->runCommand("SpiRead 0x1c108d88 /usr/var/spi/0x1c108d88/received.dat 10");

    reflection->runCommand("TEST_0 145");

    reflection->runCommand("TEST_1 111111111111111111 0x2222F -333333 444444 True '5' 606.606 This_is_parameter_7 888.987");
    reflection->runCommand("Test_4");

    cout << "\n\n\n";

    delete reflection;

}

void initSettings()
{
    SettingsImpl settings;

    settings.addBitField("bit_f_1");
    settings.setBit("bit_f_1", BIT_3, true);
    settings.setBit("bit_f_1", BIT_5, true);

    settings.addField<double>("d_f_1", 5.85);

    settings.addBitField(VALIDATION_SET, ERRORS_ENABLED | ERRORS_TO_CONSOLE | WARNINGS_ENABLED | WARNINGS_TO_CONSOLE);

    Logger::debug("BIT_0") << settings.getBit("bit_f_1", BIT_0);
    Logger::debug("BIT_3") << settings.getBit("bit_f_1", BIT_3);
    Logger::debug("BIT_5") << settings.getBit("bit_f_1", BIT_5);
    Logger::debug("double: ") << settings.getValue<double>("d_f_1");

    Logger::debug("VALIDATION_SET: ") << settings.getBits(VALIDATION_SET);

    //Register settings groups
    //Settings::registerSettingsFlagsGroup(SettingsID::SETTINGS_LOGGING);
    //Settings::registerSettingsFlagsGroup(SettingsID::SETTINGS_VALIDATION);

    //Register commands for manage settings
    //reflection->registerCommand("SET_SETTINGS_FLAG", &Settings::setSettingsFlag);

    //Execute scenario with settings manage commands
    //reflection->executeScenario("settings-dafault.rfl");
}
