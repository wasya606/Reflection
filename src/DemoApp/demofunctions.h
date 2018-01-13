#ifndef DEMOFUNCTIONS_H
#define DEMOFUNCTIONS_H
#include <iostream>
namespace DemoFunctions {

//---------------   Global functions examples  -------------------

/**
 * @brief demo0 - demo function without parameters
 */
void demo0();

/**
 * @brief demo1_int - demo function with int parameter
 */
void demo1_int(int arg0);

/**
 * @brief demo1_charPtr - demo function with char* parameter
 */
void demo1_charPtr(char* arg0);

/**
 * @brief demo1_doubleRRef - demo function with double&& parameter
 */
void demo1_doubleRRef(const double&& arg0);


/**
 * @brief demo3_0 - demo function with three parameters
 * @param arg0 - const int
 * @param arg1 - bool&
 * @param arg2 - const char*&
 */
void demo3_0(const int arg0, bool& arg1, const char*& arg2);


/**
 * @brief demo3 - demo function with three parameters
 * @param arg0 - bool
 * @param arg1 - double
 * @param arg2 - const char*
 */
void demo3_1(bool arg0, double& arg1, const char* arg2);


/**
 * @brief demo5 - demo function with five parameters
 * @param arg0 - long&&
 * @param arg1 - void*
 * @param arg2 - const char&
 * @param arg3 - const double
 * @param arg4 - long double&&
 */
void demo5(long&& arg0, void* arg1, const char& arg2, const double arg3, long double&& arg4);

//-----------------   Static members functions examples ---------------------

class SpiTools
{

public:
    /**
     * @brief initSpiMaster - Performs initalization of SPI port in Master mode
     * @param confRegAddr - Address of config register(CONREG)
     * @param clkFreq - Clock frequency in MHz
     * @param clkPolarity - Polarity of clock signal(true - active on high level, false - active on low level)
     * @param chipSelect - Pin number for select needed Slave device
     */
    static void initSpiMaster(void* confRegAddr, double freq, bool clkPolarity, int chipSelect);

    /**
     * @brief sendToSpi - Write data to TX register for send to slave device
     * @param txRegAddr - Address of TX register(TXDATA)
     * @param txData - Bytes array of sended data
     * @param dataLength - Length of sended data
     */
    static void sendToSpi(void* txRegAddr, const char* txData, int dataLength);

    /**
     * @brief receiveFromSpi - Received data from RX register even when got a new data and append it to file outFileUrl
     * @param rxRegAddr - Address of RX register(RXDATA)
     * @param outFileUrl - URL to store received data
     * @param bufferSize - Size of buffer
     */
    static void startReceiveFromSpi(void* rxRegAddr, const char* outFileUrl, int bufferSize);
};

}
#endif // DEMOFUNCTIONS_H
