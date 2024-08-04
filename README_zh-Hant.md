[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver INA219

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ina219/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

INA219是一款具備I2C或SMBUS相容介面的分流器和功率監測計。 該器件監測分流器電壓降和匯流排電源電壓，轉換次數和濾波選項可通過程式設計設定。 可程式設計校準值與內部乘法器相結合，支持直接讀取電流值（組織：安培）。 通過附加乘法寄存器可計算功率（組織：瓦）。 I2C或SMBUS相容介面具有16個可程式設計地址。 INA219可在0V至26V範圍內感測匯流排中的分壓。 該器件由3V至5.5V單電源供電，晶片的最大功耗為1mA。 該設備可用於服務器、通信設備、筆記本、電源管理、充電器、電焊、電源和測試設備等。

LibDriver INA219是LibDriver推出的INA219的全功能驅動，該驅動提供連續模式讀取、單次模式讀取，電流採集、電壓採集和功率採集等功能並且它符合MISRA標準。

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

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

#### example basic

```C
#include "driver_ina219_basic.h"

uint8_t res;

res = ina219_basic_init(INA219_ADDRESS_0, 0.1);
if (res != 0)
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
    if (res != 0)
    {
        (void)ina219_basic_deinit();

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

(void)ina219_basic_deinit();

return 0;
```

#### example shot

```C
#include "driver_ina219_shot.h"

uint8_t res;

res = ina219_shot_init(INA219_ADDRESS_0, 0.1);
if (res != 0)
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
    if (res != 0)
    {
        (void)ina219_shot_deinit();

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

(void)ina219_shot_deinit();

return 0;
```

### 文檔

在線文檔: [https://www.libdriver.com/docs/ina219/index.html](https://www.libdriver.com/docs/ina219/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。

