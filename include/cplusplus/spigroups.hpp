
//
// Created by zheng on 2025/9/13.
//

#ifndef SPI_GROUPS_H
#define SPI_GROUPS_H
#pragma once

#include "spicplusplus.h"
#include <netinet/in.h>
#include <memory>
#include <regex>
#include <cassert>

class SpiGroups {
public:
    SpiGroups() {
        _spi = std::make_shared<SpiCPlusPlus>();
        assert(nullptr != _spi);
    }

    SpiGroups(const SpiGroups&) = delete;

    void operator=(const SpiGroups&) = delete;

    SpiGroups(const SpiGroups&&) = delete;
    
    SpiGroups& operator=(const SpiGroups&&) = delete;

    virtual ~SpiGroups() = default;
    
    int open(const std::string &dev, const struct spi_config &config) {
        return _spi->open(dev, config);
    }

    int read_cpld(const uint16_t &addr, uint16_t &val) const {
        struct spi_groups_msg tx {
                .cpld = {SPI_GROUPS_READ_CPLD, htons(addr), SPI_GROUPS_INVALID_VAL_SHORT}
        }, rx {};

        int rc = _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_cpld));
        val = ntohs(rx.cpld.data);
        return rc;
    }

    int write_cpld(const uint16_t &addr, const uint16_t &val) const {
        struct spi_groups_msg tx {
                .cpld = {SPI_GROUPS_WRITE_CPLD, htons(addr), htons(val)}
        }, rx {};
        
        return _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_cpld));
    }

    int read_e1(const uint8_t &addr, uint16_t &val) const {
        struct spi_groups_msg tx {
                .e1 = {SPI_GROUPS_READ_CPLD, addr, SPI_GROUPS_INVALID_VAL_SHORT}
        }, rx {};

        int rc = _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_e1));
        val = ntohs(rx.e1.data);
        return rc;
    }

    int write_e1(const uint8_t &addr, const uint16_t &val) const {
        struct spi_groups_msg tx {
                .e1 = {SPI_GROUPS_WRITE_CPLD, addr, htons(val)}
        }, rx {};

        return _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_e1));
    }

    int read_cp500x(const uint8_t &addr, uint8_t &val) const {
        struct spi_groups_msg tx {
                .cp500x = {SPI_GROUPS_CU500X_READ, addr, SPI_GROUPS_INVALID_VAL_CHAR}
        }, rx {};

        tx.msg[0] = table_bit_reverse[tx.msg[0]];
        tx.cp500x.data = table_bit_reverse[tx.cp500x.data];

        int rc = _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_cp500x));
        val = table_bit_reverse[rx.cp500x.data];
        return rc;
    }

    int write_cp500x(const uint8_t &addr, const uint8_t &val) const {
        struct spi_groups_msg tx {
                .cp500x = {SPI_GROUPS_CU500X_WRITE, addr, val}
        }, rx {};

        tx.msg[0] = table_bit_reverse[tx.msg[0]];
        tx.cp500x.data = table_bit_reverse[tx.cp500x.data];

        return _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_cp500x));
    }

    int read_idt82v2052e(const uint8_t &addr, uint8_t &val) const {
        struct spi_groups_msg tx {
                .idt82v2052e = {addr, SPI_GROUPS_IDT82V2052E_READ, 0, SPI_GROUPS_INVALID_VAL_CHAR}}, rx {};

        tx.msg[0] = table_bit_reverse[tx.msg[0]];
        tx.idt82v2052e.data = table_bit_reverse[tx.idt82v2052e.data];

        int rc = _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_idt82v252e));

        val = table_bit_reverse[rx.idt82v2052e.data];
        return rc;
    }

    int write_idt82v2052e(const uint8_t &addr, const uint8_t &val) const {
        struct spi_groups_msg tx {
                .idt82v2052e = {addr, SPI_GROUPS_IDT82V2052E_WRITE, 0, val}}, rx {};

        tx.msg[0] = table_bit_reverse[tx.msg[0]];
        tx.idt82v2052e.data = table_bit_reverse[tx.idt82v2052e.data];

        return _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_idt82v252e));
    }

    int read_idt82p2916(const uint16_t &addr, uint8_t &val) const {
        const uint8_t addrH = addr >> 8, addrL = addr & 0xff;
        struct spi_groups_msg tx {
                .idt82p2916 = {addrH, 0, SPI_GROUPS_IDT82P2916_READ, addrL, SPI_GROUPS_INVALID_VAL_CHAR}
        }, rx {};

        int rc = _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_idt82p2916));

        val = rx.idt82p2916.data;
        return rc;
    }

    int write_idt82p2916(const uint16_t &addr, const uint8_t &val) const {
        const uint8_t addrH = addr >> 8, addrL = addr & 0xff;
        struct spi_groups_msg tx {
                .idt82p2916 = {addrH, 0, SPI_GROUPS_IDT82P2916_WRITE, addrL, val}
        }, rx {};

        return _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_idt82p2916));
    }

    int read_au5508(const uint8_t &addr, uint8_t &val) const {
        struct spi_groups_msg tx {
                .au5508 = {0, SPI_GROUPS_AU5508_READ, addr, SPI_GROUPS_INVALID_VAL_CHAR}
        }, rx {};

        int rc = _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_au5508));

        val = rx.au5508.data;
        return rc;
    }

    int write_au5508(const uint8_t &addr, const uint8_t &val) const {
        struct spi_groups_msg tx {
                .au5508 = {0, SPI_GROUPS_AU5508_WRITE, addr, val}
        }, rx {};

        return _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_au5508));
    }

    int read_au53xx(const uint8_t &addr, uint8_t &val) const {
        struct spi_groups_msg tx {
                .cu53xx = {SPI_GROUPS_AU53XX_READ, 0, addr, SPI_GROUPS_INVALID_VAL_CHAR},
        }, rx {};

        int rc = _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_cu53xx));

        val = rx.cu53xx.data;
        return rc;
    }

    int write_au53xx(const uint8_t &addr, const uint8_t &val) const {
        struct spi_groups_msg tx {
                .cu53xx = {SPI_GROUPS_AU53XX_WRITE, 0, addr, val},
        }, rx {};

        return _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_cu53xx));
    }

    int read_idt8a34xxx(const uint16_t &addr, uint8_t &val) const {
        uint8_t action_page = static_cast<uint8_t>(addr & SPI_GROUPS_8A34XXX_PAGE_WRITE);
        uint8_t addr_h = static_cast<uint8_t>((addr >> 8) & SPI_GROUPS_8A34XXX_READ_MASK);
        uint8_t addr_l = static_cast<uint8_t>((addr & SPI_GROUPS_8A34XXX_WRITE_MASK) | SPI_GROUPS_8A34XXX_READ);

        struct spi_groups_msg tx_page {
                .idt8A34xxxpage = {
                        SPI_GROUPS_8A34XXX_DEF_0, action_page, addr_h,
                        SPI_GROUPS_8A34XXX_DEF_1, SPI_GROUPS_8A34XXX_DEF_2
                }
        }, tx {
                .idt8A34xxxop = { addr_l, SPI_GROUPS_INVALID_VAL_CHAR}
        }, rx {};

        int rc = _spi->xtransfer(tx_page.msg, rx.msg, sizeof(struct spi_groups_idt8a34xxx_page));
        if (rc < 0) {
            return -2;
        }

        rc = _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_idt8a34xxx_op));
        val = rx.idt8A34xxxop.data;

        return rc;
    }

    int write_idt8a34xxx(const uint16_t &addr, const uint8_t &val) const {
        uint8_t action_page = static_cast<uint8_t>(addr & SPI_GROUPS_8A34XXX_PAGE_WRITE);
        uint8_t addr_h = static_cast<uint8_t>((addr >> 8) & SPI_GROUPS_8A34XXX_READ_MASK);
        uint8_t addr_l = static_cast<uint8_t>((addr & SPI_GROUPS_8A34XXX_WRITE));

        struct spi_groups_msg tx_page {
                .idt8A34xxxpage = {
                        SPI_GROUPS_8A34XXX_DEF_0, action_page, addr_h,
                        SPI_GROUPS_8A34XXX_DEF_1, SPI_GROUPS_8A34XXX_DEF_0
                }
        }, tx {
                .idt8A34xxxop = { addr_l, val}
        }, rx {};
        
        int rc = _spi->xtransfer(tx_page.msg, rx.msg, sizeof(struct spi_groups_idt8a34xxx_page));
        if (rc < 0) {
            return -2;
        }
        
        rc = _spi->xtransfer(tx.msg, rx.msg, sizeof(struct spi_groups_idt8a34xxx_op));
        return rc;
    }

private:
    int _fd = -1;

    std::shared_ptr<SpiCPlusPlus> _spi = nullptr;
};
#endif //SPI_GROUPS_H
