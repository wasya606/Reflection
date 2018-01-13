#include "demofunctions.h"

void DemoFunctions::demo0()
{
    std::cout << "~~~ Invoke: void demo0() ~~~\n";
}

void DemoFunctions::demo1_int(int arg0)
{
    std::cout << "~~~ Invoke: void demo1_int(int) ~~~\n";
    std::cout << "arg0: " << arg0 << std::endl;
    std::cout << "~~~~~~~~~~\n\n";
}

void DemoFunctions::demo1_charPtr(char* arg0)
{
    std::cout << "~~~ Invoke: void demo1_charPtr(char*) ~~~\n";
    std::cout << "arg0: " << arg0 << std::endl;
    std::cout << "~~~~~~~~~~\n\n";
}

void DemoFunctions::demo1_doubleRRef(const double&& arg0)
{
    std::cout << "~~~ Invoke: void demo1_doubleRRef(const double&&) ~~~\n";
    std::cout << "arg0: " << arg0 << std::endl;
    std::cout << "~~~~~~~~~~\n\n";

}

void DemoFunctions::demo3_0(const int arg0, bool& arg1, const char*& arg2)
{
    std::cout << "~~~ Invoke: void demo3_0(const int, bool&, const char *&) ~~~\n";
    std::cout << "arg0: " << arg0 << std::endl;
    std::cout << "arg1: " << arg1 << std::endl;
    std::cout << "arg2: " << arg2 << std::endl;
    std::cout << "~~~~~~~~~~\n\n";

}

void DemoFunctions::demo3_1(bool arg0, double& arg1, const char* arg2)
{
    std::cout << "~~~ Invoke: void demo3_1(bool, double&, const char*) ~~~\n";
    std::cout << "arg0: " << arg0 << std::endl;
    std::cout << "arg1: " << arg1 << std::endl;
    std::cout << "arg2: " << arg2 << std::endl;
    std::cout << "~~~~~~~~~~\n\n";
}

void DemoFunctions::demo5(long&& arg0, void* arg1, const char& arg2, const double arg3, long double&& arg4)
{
    std::cout << "~~~ Invoke: void demo5(long&&, void*, const char&, const double, long double&&) ~~~\n";
    std::cout << "arg0: " << arg0 << std::endl;
    std::cout << "arg1: " << arg1 << std::endl;
    std::cout << "arg2: " << arg2 << std::endl;
    std::cout << "arg3: " << arg3 << std::endl;
    std::cout << "arg4: " << arg4 << std::endl;
    std::cout << "~~~~~~~~~~\n\n";
}

void DemoFunctions::SpiTools::initSpiMaster(void *confRegAddr, double freq, bool clkPolarity, int chipSelect)
{
    std::cout << "\n~~~~~  Initializing SPI ~~~~~\n";
    std::cout << "CONREG register address: " << confRegAddr << std::endl;
    std::cout << "Clock frequency: " << freq << " MHz\n";
    std::cout << "Clock polarity is: " << (clkPolarity ? "HIGH" : "LOW") << std::endl;
    std::cout << "Establish communication with the slave device #: " << chipSelect << std::endl;
    std::cout << "~~~~~ SUCCESS!!! ~~~~~\n\n";
}

void DemoFunctions::SpiTools::sendToSpi(void *txRegAddr, const char *txData, int dataLength)
{
    std::cout << "\n~~~~~  Send data to SPI ~~~~~\n";
    std::cout << "TXDATA register address: " << txRegAddr << std::endl;
    std::cout << "Sended data: " << txData << std::endl;
    std::cout << "Data length: " << dataLength << std::endl;
    std::cout << "~~~~~ SUCCESS!!! ~~~~~\n\n";
}

void DemoFunctions::SpiTools::startReceiveFromSpi(void *rxRegAddr, const char *outFileUrl, int bufferSize)
{
    std::cout << "\n~~~~~  Start receiving data from SPI ~~~~~\n";
    std::cout << "RXDATA register address: " << rxRegAddr << std::endl;
    std::cout << "Out file URL: " << outFileUrl << std::endl;
    std::cout << "Buffer length: " << bufferSize << std::endl;
    std::cout << "~~~~~ All received data will be stored in " << outFileUrl << " ~~~~~\n\n";
}
