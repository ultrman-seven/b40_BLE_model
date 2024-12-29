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
    void disconnect(void);
    // ~B40();
};

#endif /* D579F3E4_81BF_49F4_ACDC_BBD3F215DFDB */
