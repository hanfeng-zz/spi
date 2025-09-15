
//
// Created by zheng on 2025/9/12.
//

#include "spicplusplus.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


SpiCPlusPlus::~SpiCPlusPlus() {
    close();
}

int SpiCPlusPlus::open(const std::string &dev, const struct spi_config &config) {
    /* Open block device */
    _fd = ::open(dev.c_str(), O_RDWR);
    if (_fd == -1) {
        return _fd;
    }

    /* Set SPI_POL and SPI_PHA */
    if (::ioctl(_fd, SPI_IOC_WR_MODE, &config.mode) == -1) {
        return -1;
    }

    if (::ioctl(_fd, SPI_IOC_RD_MODE, &config.mode) == -1) {
        return -1;
    }

    /* Set bits per word*/
    if (::ioctl(_fd, SPI_IOC_WR_BITS_PER_WORD, &config.bitsPerWord) == -1) {
        return -1;
    }

    if (::ioctl(_fd, SPI_IOC_RD_BITS_PER_WORD, &config.bitsPerWord) == -1) {
        return -1;
    }

    /* Set SPI speed*/
    if (::ioctl(_fd, SPI_IOC_WR_MAX_SPEED_HZ, &config.speed) == -1) {
        return -1;
    }

    if (::ioctl(_fd, SPI_IOC_RD_MAX_SPEED_HZ, &config.speed) == -1) {
        return -1;
    }

    /* Set SPI speed*/
    if (::ioctl(_fd, SPI_IOC_RD_LSB_FIRST, &config.lsbFirst) == -1) {
        return -1;
    }

    if (::ioctl(_fd, SPI_IOC_WR_LSB_FIRST, &config.lsbFirst) == -1) {
        return -1;
    }
    
    return 0;
}

void SpiCPlusPlus::close() {
    if (_fd >= 0) {
        ::close(_fd);
    }
}

int SpiCPlusPlus::xtransfer(const uint8_t *const tx, uint8_t *rx, const uint32_t &len) {
    struct spi_ioc_transfer msg {};

    msg.tx_buf = reinterpret_cast<unsigned long>(tx);
    msg.rx_buf = reinterpret_cast<unsigned long>(rx);
    msg.len    = len;

    return ::ioctl(_fd, SPI_IOC_MESSAGE(1), &msg);
}

int SpiCPlusPlus::read(uint8_t *rx, const uint32_t &len) {
    return xtransfer(nullptr, rx, len);
}

int SpiCPlusPlus::write(const uint8_t *const tx, const uint32_t &len) {
    return xtransfer(tx, nullptr, len);
}