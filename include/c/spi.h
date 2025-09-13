// Copyright (c) 2025 Shifei Technologies. All rights reserved.
//
// This file is part of internal projects, unauthorized copying of this file
// via any medium is strictly prohibited.

// Copyright (c) 2025 Shifei Technologies. All rights reserved.
//
// This file is part of internal projects, unauthorized copying of this file
// via any medium is strictly prohibited.

//
// Created by zheng zhao on 2025/9/12.
//

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
