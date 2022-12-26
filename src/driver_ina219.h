/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_ina219.h
 * @brief     driver ina219 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2021-06-13
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2021/06/13  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_INA219_H
#define DRIVER_INA219_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ina219_driver ina219 driver function
 * @brief    ina219 driver modules
 * @{
 */

/**
 * @addtogroup ina219_basic_driver
 * @{
 */

/**
 * @brief ina219 address enumeration definition
 */
typedef enum
{
    INA219_ADDRESS_0 = (0x40 << 1),        /**< A0 = GND, A1 = GND */
    INA219_ADDRESS_1 = (0x41 << 1),        /**< A0 = VS+, A1 = GND */
    INA219_ADDRESS_2 = (0x42 << 1),        /**< A0 = SDA, A1 = GND */
    INA219_ADDRESS_3 = (0x43 << 1),        /**< A0 = SCL, A1 = GND */
    INA219_ADDRESS_4 = (0x44 << 1),        /**< A0 = GND, A1 = VS+ */
    INA219_ADDRESS_5 = (0x45 << 1),        /**< A0 = VS+, A1 = VS+ */
    INA219_ADDRESS_6 = (0x46 << 1),        /**< A0 = SDA, A1 = VS+ */
    INA219_ADDRESS_7 = (0x47 << 1),        /**< A0 = SCL, A1 = VS+ */
    INA219_ADDRESS_8 = (0x48 << 1),        /**< A0 = GND, A1 = SDA */
    INA219_ADDRESS_9 = (0x49 << 1),        /**< A0 = VS+, A1 = SDA */
    INA219_ADDRESS_A = (0x4A << 1),        /**< A0 = SDA, A1 = SDA */
    INA219_ADDRESS_B = (0x4B << 1),        /**< A0 = SCL, A1 = SDA */
    INA219_ADDRESS_C = (0x4C << 1),        /**< A0 = GND, A1 = SCL */
    INA219_ADDRESS_D = (0x4D << 1),        /**< A0 = VS+, A1 = SCL */
    INA219_ADDRESS_E = (0x4E << 1),        /**< A0 = SDA, A1 = SCL */
    INA219_ADDRESS_F = (0x4F << 1)         /**< A0 = SCL, A1 = SCL */
} ina219_address_t;

/**
 * @brief ina219 bus voltage enumeration definition
 */
typedef enum
{
    INA219_BUS_VOLTAGE_RANGE_16V = 0,        /**< ±16V */
    INA219_BUS_VOLTAGE_RANGE_32V = 1,        /**< ±32V */
} ina219_bus_voltage_range_t;

/**
 * @brief ina219 pga enumeration definition
 */
typedef enum
{
    INA219_PGA_40_MV  = 0,        /**< ±40 mV */
    INA219_PGA_80_MV  = 1,        /**< ±80 mV */
    INA219_PGA_160_MV = 2,        /**< ±160 mV */
    INA219_PGA_320_MV = 3,        /**< ±320 mV */
} ina219_pga_t;

/**
 * @brief ina219 adc mode enumeration definition
 */
typedef enum
{
    INA219_ADC_MODE_9_BIT_1_SAMPLES    = 0x0,        /**< 9 bit / 1 samples */
    INA219_ADC_MODE_10_BIT_1_SAMPLES   = 0x1,        /**< 10 bit / 1 samples */
    INA219_ADC_MODE_11_BIT_1_SAMPLES   = 0x2,        /**< 11 bit / 1 samples */
    INA219_ADC_MODE_12_BIT_1_SAMPLES   = 0x3,        /**< 12 bit / 1 samples */
    INA219_ADC_MODE_12_BIT_2_SAMPLES   = 0x9,        /**< 12 bit / 2 samples */
    INA219_ADC_MODE_12_BIT_4_SAMPLES   = 0xA,        /**< 12 bit / 4 samples */
    INA219_ADC_MODE_12_BIT_8_SAMPLES   = 0xB,        /**< 12 bit / 8 samples */
    INA219_ADC_MODE_12_BIT_16_SAMPLES  = 0xC,        /**< 12 bit / 16 samples */
    INA219_ADC_MODE_12_BIT_32_SAMPLES  = 0xD,        /**< 12 bit / 32 samples */
    INA219_ADC_MODE_12_BIT_64_SAMPLES  = 0xE,        /**< 12 bit / 64 samples */
    INA219_ADC_MODE_12_BIT_128_SAMPLES = 0xF,        /**< 12 bit / 128 samples */
} ina219_adc_mode_t;

/**
 * @brief ina219 mode enumeration definition
 */
typedef enum
{
    INA219_MODE_POWER_DOWN                   = 0x0,        /**< power down */
    INA219_MODE_SHUNT_VOLTAGE_TRIGGERED      = 0x1,        /**< shunt voltage triggered */
    INA219_MODE_BUS_VOLTAGE_TRIGGERED        = 0x2,        /**< bus voltage triggered */
    INA219_MODE_SHUNT_BUS_VOLTAGE_TRIGGERED  = 0x3,        /**< shunt and bus triggered */
    INA219_MODE_ADC_OFF                      = 0x4,        /**< adc off */
    INA219_MODE_SHUNT_VOLTAGE_CONTINUOUS     = 0x5,        /**< shunt voltage continuous */
    INA219_MODE_BUS_VOLTAGE_CONTINUOUS       = 0x6,        /**< bus voltage continuous */
    INA219_MODE_SHUNT_BUS_VOLTAGE_CONTINUOUS = 0x7,        /**< shunt and bus voltage continuous */
} ina219_mode_t;

/**
 * @brief ina219 handle structure definition
 */
typedef struct ina219_handle_s
{
    uint8_t iic_addr;                                                                   /**< iic device address */
    uint8_t (*iic_init)(void);                                                          /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                                        /**< point to an iic_deinit function address */
    uint8_t (*iic_read)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);         /**< point to an iic_read function address */
    uint8_t (*iic_write)(uint8_t addr, uint8_t reg, uint8_t *buf, uint16_t len);        /**< point to an iic_write function address */
    void (*delay_ms)(uint32_t ms);                                                      /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                                    /**< point to a debug_print function address */
    double r;                                                                           /**< resistance */
    double current_lsb;                                                                 /**< current lsb */
    uint8_t inited;                                                                     /**< inited flag */
} ina219_handle_t;

/**
 * @brief ina219 information structure definition
 */
typedef struct ina219_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} ina219_info_t;

/**
 * @}
 */

/**
 * @defgroup ina219_link_driver ina219 link driver function
 * @brief    ina219 link driver modules
 * @ingroup  ina219_driver
 * @{
 */

/**
 * @brief     initialize ina219_handle_t structure
 * @param[in] HANDLE points to an ina219 handle structure
 * @param[in] STRUCTURE is ina219_handle_t
 * @note      none
 */
#define DRIVER_INA219_LINK_INIT(HANDLE, STRUCTURE)   memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE points to an ina219 handle structure
 * @param[in] FUC points to an iic_init function address
 * @note      none
 */
#define DRIVER_INA219_LINK_IIC_INIT(HANDLE, FUC)    (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE points to an ina219 handle structure
 * @param[in] FUC points to an iic_deinit function address
 * @note      none
 */
#define DRIVER_INA219_LINK_IIC_DEINIT(HANDLE, FUC)  (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read function
 * @param[in] HANDLE points to an ina219 handle structure
 * @param[in] FUC points to an iic_read function address
 * @note      none
 */
#define DRIVER_INA219_LINK_IIC_READ(HANDLE, FUC)    (HANDLE)->iic_read = FUC

/**
 * @brief     link iic_write function
 * @param[in] HANDLE points to an ina219 handle structure
 * @param[in] FUC points to an iic_write function address
 * @note      none
 */
#define DRIVER_INA219_LINK_IIC_WRITE(HANDLE, FUC)   (HANDLE)->iic_write = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an ina219 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_INA219_LINK_DELAY_MS(HANDLE, FUC)    (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an ina219 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_INA219_LINK_DEBUG_PRINT(HANDLE, FUC) (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup ina219_basic_driver ina219 basic driver function
 * @brief    ina219 basic driver modules
 * @ingroup  ina219_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an ina219 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ina219_info(ina219_info_t *info);

/**
 * @brief     set the iic address pin
 * @param[in] *handle points to an ina219 handle structure
 * @param[in] addr_pin is the address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t ina219_set_addr_pin(ina219_handle_t *handle, ina219_address_t addr_pin);

/**
 * @brief      get the iic address pin
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *addr_pin points to an address pin buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ina219_get_addr_pin(ina219_handle_t *handle, ina219_address_t *addr_pin);

/**
 * @brief     set the resistance
 * @param[in] *handle points to an ina219 handle structure
 * @param[in] resistance is the current sampling resistance value
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t ina219_set_resistance(ina219_handle_t *handle, double resistance);

/**
 * @brief      get the resistance
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *resistance points to a current sampling resistance value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ina219_get_resistance(ina219_handle_t *handle, double *resistance);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an ina219 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 *            - 4 soft reset failed
 * @note      none
 */
uint8_t ina219_init(ina219_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an ina219 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t ina219_deinit(ina219_handle_t *handle);

/**
 * @brief      read the shunt voltage
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *raw points to raw data buffer
 * @param[out] *mV points to converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read shunt voltage failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_read_shunt_voltage(ina219_handle_t *handle, int16_t *raw, float *mV);

/**
 * @brief      read the bus voltage
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *raw points to raw data buffer
 * @param[out] *mV points to converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read bus voltage failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 math overflow
 *             - 5 conversion not ready
 * @note       none
 */
uint8_t ina219_read_bus_voltage(ina219_handle_t *handle, uint16_t *raw, float *mV);

/**
 * @brief      read the current
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *raw points to raw data buffer
 * @param[out] *mA points to converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read current failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_read_current(ina219_handle_t *handle, int16_t *raw, float *mA);

/**
 * @brief      read the power
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *raw points to raw data buffer
 * @param[out] *mW points to converted data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read power failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_read_power(ina219_handle_t *handle, uint16_t *raw, float *mW);

/**
 * @brief     soft reset the chip
 * @param[in] *handle points to an ina219 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 soft reset failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_soft_reset(ina219_handle_t *handle);

/**
 * @brief     set the bus voltage range
 * @param[in] *handle points to an ina219 handle structure
 * @param[in] range is the bus voltage range
 * @return    status code
 *            - 0 success
 *            - 1 set bus voltage range failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_bus_voltage_range(ina219_handle_t *handle, ina219_bus_voltage_range_t range);

/**
 * @brief      get the bus voltage range
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *range points to a bus voltage range buffer
 * @return     status code
 *             - 0 success
 *             - 1 get bus voltage range failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_bus_voltage_range(ina219_handle_t *handle, ina219_bus_voltage_range_t *range);

/**
 * @brief     set the pga
 * @param[in] *handle points to an ina219 handle structure
 * @param[in] pga is the adc pga
 * @return    status code
 *            - 0 success
 *            - 1 set pga failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_pga(ina219_handle_t *handle, ina219_pga_t pga);

/**
 * @brief      get the pga
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *pga points to an adc pga buffer
 * @return     status code
 *             - 0 success
 *             - 1 get pga failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_pga(ina219_handle_t *handle, ina219_pga_t *pga);

/**
 * @brief     set the bus voltage adc mode
 * @param[in] *handle points to an ina219 handle structure
 * @param[in] mode is the adc mode
 * @return    status code
 *            - 0 success
 *            - 1 set bus voltage adc mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_bus_voltage_adc_mode(ina219_handle_t *handle, ina219_adc_mode_t mode);

/**
 * @brief      get the bus voltage adc mode
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *mode points to an adc mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get bus voltage adc mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_bus_voltage_adc_mode(ina219_handle_t *handle, ina219_adc_mode_t *mode);

/**
 * @brief     set the shunt voltage adc mode
 * @param[in] *handle points to an ina219 handle structure
 * @param[in] mode is the adc mode
 * @return    status code
 *            - 0 success
 *            - 1 set shunt voltage adc mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_shunt_voltage_adc_mode(ina219_handle_t *handle, ina219_adc_mode_t mode);

/**
 * @brief      get the shunt voltage adc mode
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *mode points to an adc mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get shunt voltage adc mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_shunt_voltage_adc_mode(ina219_handle_t *handle, ina219_adc_mode_t *mode);

/**
 * @brief     set the mode
 * @param[in] *handle points to an ina219 handle structure
 * @param[in] mode is the chip mode
 * @return    status code
 *            - 0 success
 *            - 1 set mode failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_mode(ina219_handle_t *handle, ina219_mode_t mode);

/**
 * @brief      get the mode
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *mode points to a chip mode buffer
 * @return     status code
 *             - 0 success
 *             - 1 get mode failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_mode(ina219_handle_t *handle, ina219_mode_t *mode);

/**
 * @brief     set the calibration
 * @param[in] *handle points to an ina219 handle structure
 * @param[in] data is the calibration data
 * @return    status code
 *            - 0 success
 *            - 1 set calibration failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_calibration(ina219_handle_t *handle, uint16_t data);

/**
 * @brief      get the calibration
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *data points to a calibration data buffer
 * @return     status code
 *             - 0 success
 *             - 1 get calibration failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_calibration(ina219_handle_t *handle, uint16_t *data);

/**
 * @brief      calculate the calibration
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *calibration points to a calibration data buffer
 * @return     status code
 *             - 0 success
 *             - 1 calibration calibration failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 *             - 4 r can't be zero
 *             - 5 pga is invalid
 * @note       none
 */
uint8_t ina219_calculate_calibration(ina219_handle_t *handle, uint16_t *calibration);

/**
 * @}
 */

/**
 * @defgroup ina219_extern_driver ina219 extern driver function
 * @brief    ina219 extern driver modules
 * @ingroup  ina219_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle points to an ina219 handle structure
 * @param[in] reg is the register address
 * @param[in] data is the write data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ina219_set_reg(ina219_handle_t *handle, uint8_t reg, uint16_t data);

/**
 * @brief      get the chip register
 * @param[in]  *handle points to an ina219 handle structure
 * @param[in]  reg is the register address
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ina219_get_reg(ina219_handle_t *handle, uint8_t reg, uint16_t *data);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
