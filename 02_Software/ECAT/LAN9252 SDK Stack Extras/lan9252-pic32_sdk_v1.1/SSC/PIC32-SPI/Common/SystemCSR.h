/* 
 * File:   SystemCSR.h
 * Author: kthiagarajan
 *
 * Created on May 20, 2013, 5:57 PM
 */

#ifndef SYSTEMCSR_H
#define	SYSTEMCSR_H

/*
 HBI Mapped directly accessible registers
 */

#define     BASE_ADDRESS        (0)

#define     RX_FIFO             (BASE_ADDRESS + 0)
#define     TX_FIFO             (BASE_ADDRESS + 0x20)
#define     RX_STS_FIFO_PORT    (BASE_ADDRESS + 0x40)
#define     RX_STS_FIFO_PEEK    (BASE_ADDRESS + 0x44)
#define     TX_STS_FIFO_PORT    (BASE_ADDRESS + 0x48)
#define     TX_STS_FIFO_PEEK    (BASE_ADDRESS + 0x4C)

#define     ID_REV              (BASE_ADDRESS + 0x50)
#define     IRQ_CFG             (BASE_ADDRESS + 0x54)
#define     INT_STS             (BASE_ADDRESS + 0x58)
#define     INT_EN              (BASE_ADDRESS + 0x5C)

#define     BYTE_TEST           (BASE_ADDRESS + 0x64)
#define     FIFO_INT            (BASE_ADDRESS + 0x68)
#define     RX_CFG              (BASE_ADDRESS + 0x6C)
#define     TX_CFG              (BASE_ADDRESS + 0x70)
#define     HW_CFG              (BASE_ADDRESS + 0x74)
#define     RX_DP_CTRL          (BASE_ADDRESS + 0x78)
#define     RX_FIFO_INF         (BASE_ADDRESS + 0x7C)
#define     TX_FIFO_INF         (BASE_ADDRESS + 0x80)
#define     PMT_CTRL            (BASE_ADDRESS + 0x84)

#define     RX_DROP             (BASE_ADDRESS + 0xA0)
#define     MAC_CSR_CMD         (BASE_ADDRESS + 0xA4)
#define     MAC_CSR_DATA        (BASE_ADDRESS + 0xA8)
#define     AFC_CFG             (BASE_ADDRESS + 0xAC)



#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEMCSR_H */

