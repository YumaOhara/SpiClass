// SpiClass.hpp
//         Created on:
//      Author:yuma
#pragma once
#include "main.h"
#include <stdint.h> //


class SpiClass{
public:
    SpiClass(SPI_TypeDef * const spi, GPIO_TypeDef * const ss_gpio,const uint32_t ss_pin);

    uint8_t SpiRead8bit(const uint8_t addr,const uint8_t data) const;     //指定アドレスのデータを読み取る（8bit）
    uint16_t SpiRead16bit(const uint8_t addr,const uint8_t data) const;   //指定アドレスのデータを読み取る（16bit）
    void SpiWrite8bit(const uint8_t addr,const uint8_t data) const;   //  指定アドレスのデータに書き込む

private:
    uint8_t Spi_txrx(const uint8_t data) const;   //8bit送信+受信

    inline void CS_EN() const;    //SPI通信開始
    inline void CS_DIS() const;   //SPI通信終了

    SPI_TypeDef * const _spi;
	GPIO_TypeDef * const _ss_gpio;
	const uint32_t _ss_pin;
};


