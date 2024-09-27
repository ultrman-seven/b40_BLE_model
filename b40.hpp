#ifndef D579F3E4_81BF_49F4_ACDC_BBD3F215DFDB
#define D579F3E4_81BF_49F4_ACDC_BBD3F215DFDB

#include "wyUart.hpp"
#include "wyGpio.hpp"

#define B40_AT_setName(_b40_name) "NAME="#_b40_name
#define B40_AT_reboot() "REBOOT=1"
#define B40_AT_default() "DEFAULT=1"
#define B40_AT_ts() "TS=1"
#define B40_AT_setRole(_b40_role) "ROLE="#_b40_role
#define B40_AT_setRoleSlave() B40_AT_setRole(1)
#define B40_AT_setRoleMaster() B40_AT_setRole(2)
#define B40_AT_setScanMode(_b40_sm) "SCANMODE="#_b40_sm
#define B40_AT_setScanModeMAC() B40_AT_setScanMode(0)
#define B40_AT_setScanModeName() B40_AT_setScanMode(1)
#define B40_AT_setPeerName(_b40_name) "PEERNAME="#_b40_name
#define B40_AT_setPeerMAC(_b40_name) "PEERMAC="#_b40_name

typedef char const *const B40CfgsType;
class B40
{
private:
    GPIO::GpioPin rst;
    GPIO::GpioPin AT;

public:
    UART::Serial com;
    B40(uint8_t comNum, const char *tx = nullptr, const char *rx = nullptr, const char *rst = nullptr, const char *fun = nullptr);
    void config(B40CfgsType *cfgs, uint32_t cgfLen, const char *name = nullptr);
    void reset();
    void setName(const char *);
    void getName(char *buf, uint32_t len);
    // ~B40();
};

B40::B40(uint8_t comNum, const char *tx, const char *rx, const char *_rst, const char *fun)
    : com(UART::Serial(comNum, tx, rx, 115200)), rst(GPIO::GpioPin(_rst)), AT(GPIO::GpioPin(fun))
{
    AT = 1;
    if (rst.available())
        rst = 0;
}

#include "wySys.hpp"
void B40::config(B40CfgsType *cfgs, uint32_t cgfLen, const char *name)
{
    AT = 0;
    sys::delayMs(800);
    AT = 1;
    sys::delayMs(200);
    if ((name != nullptr) && (*name))
        com << "AT+NAME=" << name << "\r\n";
    while (cgfLen--)
    {
        sys::delayMs(10);
        com << "AT+" << (*cfgs) << "\r\n";
        ++cfgs;
    }
}

B40CfgsType __rbt = B40_AT_reboot();

void B40::reset()
{
    if (rst.available())
    {
        rst = 1;
        sys::delayMs(5);
        rst = 0;
    }
    else
        this->config(&__rbt, 1);
    sys::delayMs(10);
}

// const char *__b40_end = "OK\r\n";
#include "string.h"
extern uint8_t tmpBuf[25 + 8 + 7];
uint8_t tmpBuf[25 + 8 + 7];
uint8_t tmpCnt = 0;
void B40::getName(char *buf, uint32_t len)
{
    uint32_t tm;
    uint32_t dl;
    // com.setInterrupt(tmpBuf, 25 + 8 + 7);
    AT = 0;
    sys::delayMs(800);
    AT = 1;
    sys::delayMs(200);
    com.setInterrupt([](uint8_t d)
                     { tmpBuf[tmpCnt++] = d; });
    com << "AT+NAME=?\r\n";
    sys::delayMs(1000);
    // tm = sys::getTimeStamp();
    // while (1)
    // {
    // if (sys::getTimeStamp() - tm >= 1000)
    //     goto _nameErr;
    // dl = com.getBufDataLen();
    // if (dl >= 15)
    // {
    // if (tmpBuf[dl - 1] == '\n' && tmpBuf[dl - 2] == '\r' && tmpBuf[dl - 3] == 'K' && tmpBuf[dl - 4] == 'O')
    // if (1)
    // {
        // dl -= 14;
        // if (len < dl)
        //     goto _nameErr;
        // memcpy(buf, tmpBuf + 8, dl);
        // buf[dl] = 0;
        memcpy(buf, tmpBuf, 10);
        buf[10] = 0;
        goto _nameEnd;
    // }
    // }
    sys::delayMs(1);
    // }

_nameErr:
    *buf = 'f';
    buf[1] = 0;
_nameEnd:
    com.interruptCMD(0);
    com << "AT+TS=1\r\n";

    return;
}
#endif /* D579F3E4_81BF_49F4_ACDC_BBD3F215DFDB */
