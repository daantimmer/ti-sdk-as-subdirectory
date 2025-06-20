// #include DEVICE_HEADER

#include "ti/devices/cc23x0r2/driverlib/interrupt.h"
#include "ti/devices/cc23x0r5/cmsis/core/cmsis_gcc.h"
#include <cstdint>

extern "C"
{
    unsigned char __attribute__((used)) __atomic_load_1(volatile void* mem, int model)
    {
        IntDisableMaster();
        __DSB();

        unsigned char result = *reinterpret_cast<volatile unsigned char*>(mem);

        __DSB();
        IntEnableMaster();

        return result;
    }

    unsigned int __attribute__((used)) __atomic_load_4(volatile void* mem, int model)
    {
        IntDisableMaster();
        __DSB();

        unsigned int result = *reinterpret_cast<volatile unsigned int*>(mem);

        __DSB();
        IntEnableMaster();

        return result;
    }

    unsigned char __attribute__((used)) __atomic_store_1(volatile void* mem, unsigned char val, int model)
    {
        IntDisableMaster();
        __DSB();

        unsigned char result = *reinterpret_cast<volatile unsigned char*>(mem) = val;

        __DSB();
        IntEnableMaster();

        return result;
    }

    unsigned int __attribute__((used)) __atomic_store_4(volatile void* mem, unsigned int val, int model)
    {
        IntDisableMaster();
        __DSB();

        unsigned int result = *reinterpret_cast<volatile unsigned int*>(mem) = val;

        __DSB();
        IntEnableMaster();

        return result;
    }

    unsigned char __attribute__((used))
    __atomic_exchange_1(volatile void* mem, unsigned char val, int model)
    {
        IntDisableMaster();
        __DSB();

        unsigned char result = *reinterpret_cast<volatile uint8_t*>(mem);
        *reinterpret_cast<volatile uint8_t*>(mem) = val;

        __DSB();
        IntEnableMaster();

        return result;
    }

    unsigned int __attribute__((used)) __atomic_exchange_4(volatile void* mem, unsigned int val, int model)
    {
        IntDisableMaster();
        __DSB();

        unsigned int result = *reinterpret_cast<volatile uint32_t*>(mem);
        *reinterpret_cast<volatile uint32_t*>(mem) = val;

        __DSB();
        IntEnableMaster();

        return result;
    }

    bool __attribute__((used)) __atomic_compare_exchange_4(volatile void* mem, void* expected, unsigned int desired, bool weak, int success, int failure)
    {
        IntDisableMaster();
        __DSB();

        if (*reinterpret_cast<volatile uint32_t*>(mem) == *reinterpret_cast<uint32_t*>(expected))
        {
            *reinterpret_cast<volatile uint32_t*>(mem) = desired;
            __DSB();
            IntEnableMaster();
            return true;
        }
        else
        {
            *reinterpret_cast<uint32_t*>(expected) = *reinterpret_cast<volatile uint32_t*>(mem);
            IntEnableMaster();
            return false;
        }
    }

    unsigned int __attribute__((used)) __atomic_fetch_add_4(volatile void* mem, unsigned int val, int model)
    {
        IntDisableMaster();
        __DSB();

        uint32_t previous = *reinterpret_cast<volatile uint32_t*>(mem);
        *reinterpret_cast<volatile uint32_t*>(mem) += val;

        __DSB();
        IntEnableMaster();

        return previous;
    }
}
