// SpiClass.cpp
//         Created on:
//      Author:yuma

#include "SpiClass.hpp"
//#include "main.h"
#include <stdint.h>

SpiClass::SpiClass(SPI_TypeDef * const spi, GPIO_TypeDef * const ss_gpio, const uint32_t ss_pin)
	: _spi(spi), _ss_gpio(ss_gpio), _ss_pin(ss_pin)
{

}

void SpiClass::CS_EN() const{
    _ss_gpio->BSRR = (_ss_pin << 16);   // チップセレクトを0にして通信開始
}

void SpiClass::CS_DIS() const{
    _ss_gpio->BSRR = _ss_pin;   //チップセレクトを1にして通信終了
}

//マスターからスレーブ、スレーブからマスターにデータを送る用
uint8_t SpiClass::Spi_txrx(const uint8_t data) const
{
	while(!(_spi->SR & SPI_SR_TXE)) ;
	_spi->DR = data;
	while(!(_spi->SR & SPI_SR_RXNE)) ;
	return _spi->DR;
}

uint8_t SpiClass::SpiRead8bit(const uint8_t addr,const uint8_t data) const{
    volatile uint8_t result = 0x00;
    CS_EN();    // 通信開始
    Spi_txrx(addr);
    result = Spi_txrx(data);
    CS_DIS();   // 通信終了
    return result;
}

uint16_t SpiClass::SpiRead16bit(const uint8_t addr,const uint8_t data) const{
    volatile uint8_t result = 0x00;
    CS_EN();
    Spi_txrx(addr);
	result = static_cast<uint16_t>(Spi_txrx(static_cast<uint8_t>((data >> 8) & 0xff)) << 8);

	result = (uint16_t)(result | Spi_txrx(static_cast<uint8_t>(data & 0xff)));
    CS_DIS();
    return result;
}

void SpiClass::SpiWrite8bit(const uint8_t addr,const uint8_t data) const{
    CS_EN();
    Spi_txrx(addr & 0b01111111);    //書き込みのときアドレスの最上位ビットを0にする
    Spi_txrx(data);
    CS_DIS();
}
