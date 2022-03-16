/**
 * @file TC74HC595.cpp
 * @brief
 * @date Mar 16, 2022
 */

#include <TC74HC595.hpp>

namespace tc74hc595 {

/**
 * コンストラクタ
 * @param SI_pin シリアル出力 ピン
 * @param SCK_pin シフトレジスタクロックピン
 * @param RCK_pin ラッチクロック ピン
 */
TC74HC595::TC74HC595(GPIO SI_pin, GPIO SCK_pin, GPIO RCK_pin
):
		SI_pin(SI_pin),
		SCK_pin(SCK_pin),
		RCK_pin(RCK_pin)
{
}

/**
 * Arduino の shiftOut()関数をHAL環境用に書き直した関数
 * @param data_pin 各ビットを出力するピン
 * @param clock_pin dataPinに正しい値が出力された後、 パルスを出力するピン
 * @param bit_order ビットを出力する開始する順序。MSBFIRST(MSBから開始)もしくはLSBFIRST（LSBから開始）を指定する
 * @param val データを取り出す値
 */
void TC74HC595::shift_out(GPIO data_pin, GPIO clock_pin, BIT_ORDER bit_order, uint8_t val) {
    for (uint8_t i=0; i<8; i++)  {
		HAL_GPIO_WritePin(clock_pin.port, clock_pin.pin, GPIO_PIN_RESET);
		if (bit_order == LSBFIRST) {
			HAL_GPIO_WritePin(data_pin.port, data_pin.pin, (GPIO_PinState)(val & 1));
			val >>= 1;
		} else {
			HAL_GPIO_WritePin(data_pin.port, data_pin.pin, (GPIO_PinState)((val & 128) != 0));
			val <<= 1;
		}
		// ほんとはここにclockをLowにするやつがあった
		HAL_GPIO_WritePin(clock_pin.port, clock_pin.pin, GPIO_PIN_SET);
    }
}

/**
 * 更新関数
 * @param pval 値の配列の先頭アドレス
 * @param number_of_ic 直列につなげた TC74HC595 の数
 */
void TC74HC595::update(uint8_t *pval, uint8_t number_of_ic) {
	HAL_GPIO_WritePin(RCK_pin.port, RCK_pin.pin, GPIO_PIN_RESET);
	for (uint8_t i=0; i<number_of_ic; i++) {
		shift_out(SI_pin, SCK_pin, LSBFIRST, *(pval+8*i) );
	}
	HAL_GPIO_WritePin(RCK_pin.port, RCK_pin.pin, GPIO_PIN_SET);
}

} /* namespace tc74hc595 */
