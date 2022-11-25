[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver INA219
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ina219/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der INA219 ist ein Strom-Shunt und Leistungsmonitor mit einer I2C- oder SMBUS-kompatiblen Schnittstelle. Das Gerät überwacht sowohl den Shunt-Spannungsabfall als auch die Bus-Versorgungsspannung mit programmierbaren Umwandlungszeiten und Filterung. Ein programmierbarer Kalibrierwert, kombiniert mit einem internen Multiplikator, ermöglicht das direkte Ablesen des Stroms in Ampere. Ein zusätzliches Multiplikationsregister berechnet die Leistung in Watt. Die I2C- oder SMBUS-kompatible Schnittstelle verfügt über 16 programmierbare Adressen. Der INA219 erkennt über Shunts auf Bussen, die von 0 bis 26 V variieren können. Das Gerät verwendet eine einzelne 3- bis 5,5-V-Versorgung und zieht maximal 1 mA an Versorgung Strom. Dieser Chip kann in Servern, Telekommunikationsgeräten, Notebooks, Energieverwaltung, Batterieladegeräten, Schweißgeräten, Netzteilen, Testgeräten usw. verwendet werden.

LibDriver INA219 ist der voll funktionsfähige Treiber von INA219, der von LibDriver eingeführt wurde. Er bietet kontinuierliches Lesen, Einzelmoduslesen, Stromerfassung, Spannungserfassung und Leistungserfassung. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver INA219-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver INA219IIC.

/test enthält den Testcode des LibDriver INA219-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver INA219-Beispielcode.

/doc enthält das LibDriver INA219-Offlinedokument.

/Datenblatt enthält INA219-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie /src, /interface und /example zu Ihrem Projekt hinzu.

### Nutzung

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


### Dokument

Online-Dokumente: https://www.libdriver.com/docs/ina219/index.html

Offline-Dokumente: /doc/html/index.html

### Beitrag

Bitte senden Sie eine E-Mail an lishifenging@outlook.com

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com