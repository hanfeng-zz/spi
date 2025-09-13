
#include "spi.h"
#include "spigroups.hpp"


#include <assert.h>
#include <netinet/in.h>
#include <stdio.h>

#define TEST_BUFFER_LEN 100

struct test_e1 {
    uint8_t op;
    uint8_t addr;
    uint16_t data;
} __attribute__((packed));

int main(int argc, char *argv[]) {
    uint16_t val;
    std::string device = "/dev/spidev2.0";
    struct spi_config config = {.mode = 0, .bitsPerWord = 8, .lsbFirst = 0, .speed = 1000000, .delay = 50};

    SpiGroups spi;

    int ret = spi.open(device, config);
    assert(-1 != ret);
    //read test

    ret = spi.read_e1(0x00, val);
    assert(-1 != ret);
    printf("addr:0x0 val:0x%x\n", val);
    //write test
    ret = spi.write_e1(0x01, 0x2345);
    assert(-1 != ret);
    ret = spi.read_e1(0x01, val);
    assert(-1 != ret);
    printf("addr:0x1 val:0x%x\n", val);

    return 0;
}