//---------------------------------------------------------------------------------------------
// Autor: Vasyl Dykyy
// Definitions of functions for registration as commands
//---------------------------------------------------------------------------------------------

#ifndef CMD_FUNCTIONS_H
#define CMD_FUNCTIONS_H
#include <iostream>
#include <typeinfo>
using namespace std;

namespace CmdFunc {

struct ParTest
{
    int a = 34;
    double b = 3.2;
    void* c;
};

void test0(int& arg0)
{
    cout << "~~~~    Test#0    ~~~~\n";
    cout << "arg0: " << arg0 << endl;
    //cout << "arg1: " << arg1 << endl;
    cout << "~~~~~~   end     ~~~~~\n";
}

void test1(const long long int&& a0, void* a1, const int a2, const unsigned int& a3, bool& a4, ParTest a5, const double a6, const char*& a7, long double a8)
{
    cout << "~~~~    Test#1    ~~~~\n";
    cout << "arg0: " << a0 << endl;
    cout << "arg1: " << a1 << endl;
    cout << "arg2: " << a2 << endl;
    cout << "arg3: " << a3 << endl;
    cout << "arg4: " << a4 << endl;
    cout << "arg5: " << a5.a << endl;
    cout << "arg6: " << a6 << endl;
    cout << "arg7: " << a7 << endl;
    cout << "arg8: " << a8 << endl;
    cout << "~~~~~~   end     ~~~~~\n";
}

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
    static void initSpiMaster(void* confRegAddr, double freq, bool clkPolarity, int chipSelect)
    {
        cout << "\n~~~~~  Initializing SPI ~~~~~\n";
        cout << "CONREG register address: " << confRegAddr << endl;
        cout << "Clock frequency: " << freq << " MHz\n";
        cout << "Clock polarity is: " << (clkPolarity ? "HIGH" : "LOW") << endl;
        cout << "Establish communication with the slave device #: " << chipSelect << endl;
        cout << "~~~~~ SUCCESS!!! ~~~~~\n\n";
    }

    /**
     * @brief sendToSpi - Write data to TX register for send to slave device
     * @param txRegAddr - Address of TX register(TXDATA)
     * @param txData - Bytes array of sended data
     * @param dataLength - Length of sended data
     */
    static void sendToSpi(void* txRegAddr, const char* txData, int dataLength)
    {
        cout << "\n~~~~~  Send data to SPI ~~~~~\n";
        cout << "TXDATA register address: " << txRegAddr << endl;
        cout << "Sended data: " << txData << endl;
        cout << "Data length: " << dataLength << endl;
        cout << "~~~~~ SUCCESS!!! ~~~~~\n\n";
    }

    /**
     * @brief receiveFromSpi - Received data from RX register even when got a new data and append it to file outFileUrl
     * @param rxRegAddr - Address of RX register(RXDATA)
     * @param outFileUrl - URL to store received data
     * @param bufferSize - Size of buffer
     */
    static void startReceiveFromSpi(void* rxRegAddr, const char* outFileUrl, int bufferSize)
    {
        cout << "\n~~~~~  Start receiving data from SPI ~~~~~\n";
        cout << "RXDATA register address: " << rxRegAddr << endl;
        cout << "Out file URL: " << outFileUrl << endl;
        cout << "Buffer length: " << bufferSize << endl;
        cout << "~~~~~ All received data will be stored in " << outFileUrl << " ~~~~~\n\n";
    }
};
}
#endif // CMD_FUNCTIONS_H
