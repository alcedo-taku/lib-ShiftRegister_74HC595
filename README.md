# TC74HC595

シフトレジスタ TC74HC595 を使用するためのライブラリ

## CubeMx
```yaml
Pinout:
- SIピン, SCKピン, RCKピンとして任意の3ピンを GPIO_output に変更
```

## サンプルプログラム

### コンストラクタ
```c++
tc74hc595::TC74HC595 tc74hc595_writer({SR_SI_GPIO_Port, SR_SI_Pin}, {SR_SCK_GPIO_Port, SR_SCK_Pin}, {SR_RCK_GPIO_Port, SR_RCK_Pin});
```

### 初期化
```c++
tc74hc595_writer.init();
```

### 更新と取得
シフトレジスタを2つ直列接続する場合
```c++
uint16_t sr_data;
for ( uint8_t i=0; i<16; i++ ) {
    sr_data = (1<<i);
    tc74hc595_writer.update((uint8_t*)&sr_data, 2);
    HAL_Delay(200);
}
```
