/*
 * Copyright (C) 2025-09-15  zheng zhao
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License v3.0 or later.
 * See <https://www.gnu.org/licenses/>.
 */


#ifndef SPI_H
#define SPI_H

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "spicommon.h"

int spi_open(const char *const dev, const struct spi_config config);

int spi_close(const int fd);

int spi_xtransfer(const int fd, const uint8_t *const tx, uint8_t *rx, const uint32_t len);

int spi_read(const int fd, uint8_t *rx, const uint32_t len);

int spi_write(const int fd, const uint8_t *const tx, const uint32_t len);

#ifdef __cplusplus
}
#endif
#endif //SPI_H