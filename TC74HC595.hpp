/**
 * @file TC74HC595.hpp
 * @brief
 * @date Mar 16, 2022
 */

#ifndef TC74HC595_HPP_
#define TC74HC595_HPP_

#include "gpio.h"

namespace tc74hc595 {

/**
 * GPIO のピンを指定するための構造体
 */
struct GPIO {
	GPIO_TypeDef* port;	//!< GPIOのPort
	uint16_t pin;	//!< GPIOのPin
};

/**
 * ビットを出力する開始する順序 を指定するための列挙型クラス
 */
enum BIT_ORDER {
	MSBFIRST,/**< MSBFIRST */
	LSBFIRST /**< LSBFIRST */
};

/**
 * TC74HC595 を使うためのクラス
 */
class TC74HC595 {
public:
	TC74HC595(GPIO SI_pin, GPIO SCK_pin, GPIO RCK_pin);
	void update(uint8_t *pval, uint8_t number_of_ic);
	void shift_out(BIT_ORDER bit_order, uint8_t val);
private:
	GPIO SI_pin;	//!< シリアル出力 ピン
	GPIO SCK_pin;	//!< シフトレジスタクロック ピン
	GPIO RCK_pin;	//!< ラッチクロック ピン
};

} /* namespace tc74hc595 */

#endif /* TC74HC595_HPP_ */
