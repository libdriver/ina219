[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver INA219

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ina219/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

INA219は、I2CまたはSMBUS互換のインターフェースを備えた電流シャントおよびパワーモニターです。このデバイスは、プログラム可能な変換時間とフィルタリングを使用して、シャント電圧降下とバス供給電圧の両方を監視します。プログラム可能な校正値を内部乗算器と組み合わせることで、アンペア単位の電流を直接読み取ることができます。追加の乗算レジスタは、電力をワットで計算します。 I2CまたはSMBUS互換のインターフェイスは、16個のプログラム可能なアドレスを備えています。INA219は、0〜26 Vの範囲で変化する可能性のあるバス上のシャント全体を検知します。デバイスは単一の3〜5.5 V電源を使用し、最大1mAの電源を供給します。このチップは、サーバー、テレコム機器、ノートブックコンピューター、電源管理、バッテリー充電器、溶接機器、電源、テスト機器などで使用できます。

LibDriver INA219は、LibDriverによって発売されたINA219の全機能ドライバーであり、連続モード読み取り、シングルモード読み取り、電流取得、電圧取得、および電力取得を提供します。LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver INA219のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver INA219用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver INA219ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver INA219プログラミング例が含まれています。

/ docディレクトリには、LibDriver INA219オフラインドキュメントが含まれています。

/ datasheetディレクトリには、INA219データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/ srcディレクトリ、/ interfaceディレクトリ、および/exampleディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/ina219/index.html](https://www.libdriver.com/docs/ina219/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。