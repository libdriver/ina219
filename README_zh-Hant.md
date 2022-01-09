[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md)

<div align=center>
<img src="/doc/image/logo.png"/>
</div>

## LibDriver INA219

[![API](https://img.shields.io/badge/api-reference-blue)](https://www.libdriver.com/docs/ina219/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

INA219 是一款具備 I2C 或 SMBUS 兼容接口的分流器和功率監測計。該器件監測分流器電壓降和總線電源電壓，轉換次數和濾波選項可通過編程設定。可編程校準值與內部乘法器相結合，支持直接讀取電流值（單位：安培）。通過附加乘法寄存器可計算功率（單位：瓦）。 I2C 或 SMBUS 兼容接口 具有 16 個可編程地址。 INA219 可在 0V 至 26V 範圍內感測總線中的分壓。該器件由 3V 至 5.5V 單電源供電，電源的最大流耗為 1mA。該設備可用於服務器、通信設備、筆記本、電源管理、充電器、電焊、電源和測試設備等。

LibDriver INA219是LibDriver推出的INA219的全功能驅動，該驅動提供連續模式讀取、單次模式讀取，電流採集、電壓採集和功率採集等功能。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver INA219的源文件。

/interface目錄包含了LibDriver INA219與平台無關的IIC總線模板。

/test目錄包含了LibDriver INA219驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver INA219編程範例。

/doc目錄包含了LibDriver INA219離線文檔。

/datasheet目錄包含了INA219數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，/interface目錄和/example目錄加入工程。

### 使用

#### example basic

```C
uint8_t res;

res = ina219_basic_init(INA219_ADDRESS_0, 0.1);
if (res)
{
    return 1;
}

...

for (i = 0; i < times; i++)
{
    float mV;
    float mA;
    float mW;

    res = ina219_basic_read(&mV, &mA, &mW);
    if (res)
    {
        ina219_basic_deinit();

        return 1;
    }

    ina219_interface_debug_print("ina219: %d/%d.\n", i + 1, times);
    ina219_interface_debug_print("ina219: bus voltage is %0.3fmV.\n", mV);
    ina219_interface_debug_print("ina219: current is %0.3fmA.\n", mA);
    ina219_interface_debug_print("ina219: power is %0.3fmW.\n", mW);
    ina219_interface_delay_ms(1000);
    
    ...
}

...

ina219_basic_deinit();

return 0;
```

#### example shot

```C
uint8_t res;

res = ina219_shot_init(INA219_ADDRESS_0, 0.1);
if (res)
{
    return 1;
}

...

for (i = 0; i < times; i++)
{
    float mV;
    float mA;
    float mW;

    res = ina219_shot_read(&mV, &mA, &mW);
    if (res)
    {
        ina219_shot_deinit();

        return 1;
    }

    ina219_interface_debug_print("ina219: %d/%d.\n", i + 1, times);
    ina219_interface_debug_print("ina219: bus voltage is %0.3fmV.\n", mV);
    ina219_interface_debug_print("ina219: current is %0.3fmA.\n", mA);
    ina219_interface_debug_print("ina219: power is %0.3fmW.\n", mW);
    ina219_interface_delay_ms(1000);
    
    ...
}

...

ina219_shot_deinit();

return 0;
```

### 文檔

在線文檔: https://www.libdriver.com/docs/ina219/index.html

離線文檔: /doc/html/index.htmll

### 貢獻

請聯繫lishifenging@outlook.com

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com