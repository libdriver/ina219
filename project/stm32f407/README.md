### 1. chip

#### 1.1 chip info

chip name : STM32F407ZGT6.

extern oscillator : 8MHz.

uart pin: TX/RX PA9/PA10.

iic pin: SCL/SDA PB8/PB9.

### 2. shell

#### 2.1 shell parameter

baud rate: 115200

data bits : 8

stop bits: 1

parity: none

flow control: none

### 3. ina219

#### 3.1 command Instruction

​          ina219 is a basic command which can test all ina219 driver function:

​          -i        show ina219 chip and driver information.

​          -h       show ina219 help.

​          -p       show ina219 pin connections of the current board.

​          -t (reg -a <addr> | read <times> -a <addr> -r <value>)

​          -t reg -a <addr>       run ina219 register test. addr can be "0"-"F".

​          -t read <times> -a <addr> -r <value>       run ina219 read test. times is test times.addr can be "0"-"F".value is the resistance value.

​          -c (read <times> -a <addr> -r <value>  | shot <times> -a <addr> -r <value>)

​          -c read <times> -a <addr> -r <value>         run ina219 read function.times is test times.addr can be "0"-"F".value is the resistance value.

​          -c shot <times> -a <addr> -r <value>         run ina219 shot function.times is test times.addr can be "0"-"F".value is the resistance value.

#### 3.2 command example

```shell
ina219 -i

ina219: chip is Texas Instruments INA219.
ina219: manufacturer is Texas Instruments.
ina219: interface is IIC.
ina219: driver version is 1.0.
ina219: min supply voltage is 3.0V.
ina219: max supply voltage is 5.5V.
ina219: max current is 1.00mA.
ina219: max temperature is 85.0C.
ina219: min temperature is -25.0C.
```

```shell
ina219 -p

ina219: SCL connected to GPIOB PIN8.
ina219: SDA connected to GPIOB PIN9.
```

```shell
ina219 -t reg -a 0

ina219: chip is Texas Instruments INA219.
ina219: manufacturer is Texas Instruments.
ina219: interface is IIC.
ina219: driver version is 1.0.
ina219: min supply voltage is 3.0V.
ina219: max supply voltage is 5.5V.
ina219: max current is 1.00mA.
ina219: max temperature is 85.0C.
ina219: min temperature is -25.0C.
ina219: start register test.
ina219: ina219_set_addr_pin/ina219_get_addr_pin test.
ina219: set addr pin 0.
ina219: check addr pin ok.
ina219: set addr pin 1.
ina219: check addr pin ok.
ina219: set addr pin 2.
ina219: check addr pin ok.
ina219: set addr pin 3.
ina219: check addr pin ok.
ina219: set addr pin 4.
ina219: check addr pin ok.
ina219: set addr pin 5.
ina219: check addr pin ok.
ina219: set addr pin 6.
ina219: check addr pin ok.
ina219: set addr pin 7.
ina219: check addr pin ok.
ina219: set addr pin 8.
ina219: check addr pin ok.
ina219: set addr pin 9.
ina219: check addr pin ok.
ina219: set addr pin 10.
ina219: check addr pin ok.
ina219: set addr pin 11.
ina219: check addr pin ok.
ina219: set addr pin 12.
ina219: check addr pin ok.
ina219: set addr pin 13.
ina219: check addr pin ok.
ina219: set addr pin 14.
ina219: check addr pin ok.
ina219: set addr pin 15.
ina219: check addr pin ok.
ina219: ina219_set_resistance/ina219_get_resistance test.
ina219: set resistance 0.068000.
ina219: check resistance 0.068000.
ina219: ina219_set_bus_voltage_range/ina219_get_bus_voltage_range test.
ina219: set bus voltage range 16V.
ina219: check bus voltage range ok.
ina219: set bus voltage range 32V.
ina219: check bus voltage range ok.
ina219: ina219_set_pga/ina219_get_pga test.
ina219: set pga 40 mV.
ina219: check pga ok.
ina219: set pga 80 mV.
ina219: check pga ok.
ina219: set pga 160 mV.
ina219: check pga ok.
ina219: set pga 320 mV.
ina219: check pga ok.
ina219: ina219_set_bus_voltage_adc_mode/ina219_get_bus_voltage_adc_mode test.
ina219: set bus voltage adc mode 9 bit 1 sample.
ina219: check adc mode ok.
ina219: set bus voltage adc mode 10 bit 1 sample.
ina219: check adc mode ok.
ina219: set bus voltage adc mode 11 bit 1 sample.
ina219: check adc mode ok.
ina219: set bus voltage adc mode 12 bit 1 sample.
ina219: check adc mode ok.
ina219: set bus voltage adc mode 12 bit 2 sample.
ina219: check adc mode ok.
ina219: set bus voltage adc mode 12 bit 4 sample.
ina219: check adc mode ok.
ina219: set bus voltage adc mode 12 bit 8 sample.
ina219: check adc mode ok.
ina219: set bus voltage adc mode 12 bit 16 sample.
ina219: check adc mode ok.
ina219: set bus voltage adc mode 12 bit 32 sample.
ina219: check adc mode ok.
ina219: set bus voltage adc mode 12 bit 64 sample.
ina219: check adc mode ok.
ina219: set bus voltage adc mode 12 bit 128 sample.
ina219: check adc mode ok.
ina219: ina219_set_shunt_voltage_adc_mode/ina219_get_shunt_voltage_adc_mode test.
ina219: set shunt voltage adc mode 9 bit 1 sample.
ina219: check adc mode ok.
ina219: set shunt voltage adc mode 10 bit 1 sample.
ina219: check adc mode ok.
ina219: set shunt voltage adc mode 11 bit 1 sample.
ina219: check adc mode ok.
ina219: set shunt voltage adc mode 12 bit 1 sample.
ina219: check adc mode ok.
ina219: set shunt voltage adc mode 12 bit 2 sample.
ina219: check adc mode ok.
ina219: set shunt voltage adc mode 12 bit 4 sample.
ina219: check adc mode ok.
ina219: set shunt voltage adc mode 12 bit 8 sample.
ina219: check adc mode ok.
ina219: set shunt voltage adc mode 12 bit 16 sample.
ina219: check adc mode ok.
ina219: set shunt voltage adc mode 12 bit 32 sample.
ina219: check adc mode ok.
ina219: set shunt voltage adc mode 12 bit 64 sample.
ina219: check adc mode ok.
ina219: set shunt voltage adc mode 12 bit 128 sample.
ina219: check adc mode ok.
ina219: ina219_set_mode/ina219_get_mode test.
ina219: set power down mode.
ina219: check chip mode ok.
ina219: set adc off mode.
ina219: check chip mode ok.
ina219: set shunt voltage continuous mode.
ina219: check chip mode ok.
ina219: set bus voltage continuous mode.
ina219: check chip mode ok.
ina219: set shunt bus voltage continuous mode.
ina219: check chip mode ok.
ina219: set shunt voltage triggered mode.
ina219: check chip mode ok.
ina219: set bus voltage triggered mode.
ina219: check chip mode ok.
ina219: set shunt bus voltage triggered mode.
ina219: check chip mode ok.
ina219: ina219_calculate_calibration test.
ina219: set pga 40 mV.
ina219: calculate calibration 33554.
ina219: set pga 80 mV.
ina219: calculate calibration 16777.
ina219: set pga 160 mV.
ina219: calculate calibration 8388.
ina219: set pga 320 mV.
ina219: calculate calibration 4194.
ina219: ina219_set_calibration/ina219_get_calibration test.
ina219: set calibration 8651.
ina219: check calibration ok.
ina219: ina219_soft_reset test.
ina219: finish register test.
```

```shell
ina219 -t read 3 -a 0 -r 0.1

ina219: chip is Texas Instruments INA219.
ina219: manufacturer is Texas Instruments.
ina219: interface is IIC.
ina219: driver version is 1.0.
ina219: min supply voltage is 3.0V.
ina219: max supply voltage is 5.5V.
ina219: max current is 1.00mA.
ina219: max temperature is 85.0C.
ina219: min temperature is -25.0C.
ina219: start read test.
ina219: set pga 40 mV.
ina219: shunt voltage is 7.960mV.
ina219: bus voltage is 5032.000mV.
ina219: current is 3.955mA.
ina219: power is 20.020mW.
ina219: shunt voltage is 8.660mV.
ina219: bus voltage is 5028.000mV.
ina219: current is 3.845mA.
ina219: power is 20.020mW.
ina219: shunt voltage is 8.720mV.
ina219: bus voltage is 5028.000mV.
ina219: current is 3.784mA.
ina219: power is 19.287mW.
ina219: set pga 80 mV.
ina219: shunt voltage is 8.600mV.
ina219: bus voltage is 5028.000mV.
ina219: current is 162.402mA.
ina219: power is 833.496mW.
ina219: shunt voltage is 8.690mV.
ina219: bus voltage is 5024.000mV.
ina219: current is 163.794mA.
ina219: power is 817.383mW.
ina219: shunt voltage is 8.510mV.
ina219: bus voltage is 5024.000mV.
ina219: current is 170.190mA.
ina219: power is 818.359mW.
ina219: set pga 160 mV.
ina219: shunt voltage is 8.480mV.
ina219: bus voltage is 5020.000mV.
ina219: current is 166.602mA.
ina219: power is 819.336mW.
ina219: shunt voltage is 8.370mV.
ina219: bus voltage is 5024.000mV.
ina219: current is 174.609mA.
ina219: power is 847.656mW.
ina219: shunt voltage is 8.260mV.
ina219: bus voltage is 5028.000mV.
ina219: current is 173.975mA.
ina219: power is 869.141mW.
ina219: set pga 320 mV.
ina219: shunt voltage is 8.230mV.
ina219: bus voltage is 5024.000mV.
ina219: current is 175.586mA.
ina219: power is 882.812mW.
ina219: shunt voltage is 8.320mV.
ina219: bus voltage is 5024.000mV.
ina219: current is 172.559mA.
ina219: power is 873.047mW.
ina219: shunt voltage is 8.410mV.
ina219: bus voltage is 5024.000mV.
ina219: current is 166.016mA.
ina219: power is 863.281mW.
ina219: set triggered mode.
ina219: shunt voltage is 8.070mV.
ina219: bus voltage is 5032.000mV.
ina219: current is 161.426mA.
ina219: power is 812.500mW.
ina219: shunt voltage is 8.120mV.
ina219: bus voltage is 5028.000mV.
ina219: current is 162.402mA.
ina219: power is 816.406mW.
ina219: shunt voltage is 8.330mV.
ina219: bus voltage is 5024.000mV.
ina219: current is 166.602mA.
ina219: power is 837.891mW.
ina219: finish read test.
```

```shell
ina219 -c read 3 -a 0 -r 0.1

ina219: 1/3.
ina219: bus voltage is 4904.000mV.
ina219: current is 321.777mA.
ina219: power is 1580.078mW.
ina219: 2/3.
ina219: bus voltage is 4892.000mV.
ina219: current is 346.191mA.
ina219: power is 1699.219mW.
ina219: 3/3.
ina219: bus voltage is 4936.000mV.
ina219: current is 298.730mA.
ina219: power is 1474.609mW.
```

```shell
ina219 -c shot 3 -a 0 -r 0.1 

ina219: 1/3.
ina219: bus voltage is 4892.000mV.
ina219: current is 319.824mA.
ina219: power is 1564.453mW.
ina219: 2/3.
ina219: bus voltage is 4928.000mV.
ina219: current is 303.223mA.
ina219: power is 1494.141mW.
ina219: 3/3.
ina219: bus voltage is 4940.000mV.
ina219: current is 281.738mA.
ina219: power is 1392.578mW.
```

```shell
ina219 -h

ina219 -i
	show ina219 chip and driver information.
ina219 -h
	show ina219 help.
ina219 -p
	show ina219 pin connections of the current board.
ina219 -t reg -a <addr>
	run ina219 register test.addr can be "0"-"F".
ina219 -t read <times> -a <addr> -r <value>
	run ina219 read test.times is test times.addr can be "0"-"F".value is the resistance value.
ina219 -c read <times> -a <addr> -r <value>
	run ina219 read function.times is test times.addr can be "0"-"F".value is the resistance value.
ina219 -c shot <times> -a <addr> -r <value>
	run ina219 shot function.times is test times.addr can be "0"-"F".value is the resistance value.
```

