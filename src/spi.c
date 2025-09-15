
// Created by zheng on 2025/9/12.
//

#include "c/spi.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


int spi_open(const char *const dev, const struct spi_config config) {
    int fd;

    /* Open block device */
    fd = open(dev, O_RDWR);
    if (fd == -1) {
        return fd;
    }

    /* Set SPI_POL and SPI_PHA */
    if (ioctl(fd, SPI_IOC_WR_MODE, &config.mode) == -1) {
        return -1;
    }
    if (ioctl(fd, SPI_IOC_RD_MODE, &config.mode) == -1) {
        return -1;
    }

    /* Set bits per word*/
    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &config.bitsPerWord) == -1) {
        return -1;
    }
    if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &config.bitsPerWord) == -1) {
        return -1;
    }

    /* Set SPI speed*/
    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &config.speed) == -1) {
        return -1;
    }
    if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &config.speed) == -1) {
        return -1;
    }

    /* Set SPI speed*/
    if (ioctl(fd, SPI_IOC_RD_LSB_FIRST, &config.lsbFirst) == -1) {
        return -1;
    }
    if (ioctl(fd, SPI_IOC_WR_LSB_FIRST, &config.lsbFirst) == -1) {
        return -1;
    }

    /* Return file descriptor */
    return fd;
}

int spi_close(const int fd) {
    return close(fd);
}

// SPI full duplex
int spi_xtransfer(const int fd, const uint8_t *const tx, uint8_t *rx, const uint32_t len) {
    struct spi_ioc_transfer msg = {0};

    msg.tx_buf = (unsigned long)tx;
    msg.rx_buf = (unsigned long)rx;
    msg.len    = len;

    return ioctl(fd, SPI_IOC_MESSAGE(1), &msg);
}

int spi_read(const int fd, uint8_t *rx, const uint32_t len) {
    return spi_xtransfer(fd, NULL, rx, len);
}

int spi_write(const int fd, const uint8_t *const tx, const uint32_t len) {
    return spi_xtransfer(fd, tx, NULL, len);
}


