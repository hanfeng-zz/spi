/*
 * Copyright (C) 2025-09-15  zheng zhao
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License v3.0 or later.
 * See <https://www.gnu.org/licenses/>.
 */


#ifndef SPI_CPLUSPLUS_H
#define SPI_CPLUSPLUS_H

#pragma once

#include "spicommon.h"
#include <iostream>

class SpiCPlusPlus {
public:
    SpiCPlusPlus(const SpiCPlusPlus &) = delete;

    SpiCPlusPlus &operator=(const SpiCPlusPlus&) = delete;

    SpiCPlusPlus(const SpiCPlusPlus &&) = delete;

    SpiCPlusPlus &operator=(const SpiCPlusPlus&&) = delete;
    
    SpiCPlusPlus() = default;
    
    ~SpiCPlusPlus();

    int open(const std::string &dev, const struct spi_config &config);

    int xtransfer(const uint8_t *const tx, uint8_t *rx, const uint32_t &len);

    int read(uint8_t *rx, const uint32_t &len);

    int write(const uint8_t *const tx, const uint32_t &len);
protected:
    void close();
private:
    int _fd = -1;
};


#endif //SPI_CPLUSPLUS_H
