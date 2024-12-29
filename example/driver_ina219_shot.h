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
 * @file      driver_ina219_shot.c
 * @brief     driver ina219 shot source file
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

#ifndef DRIVER_INA219_SHOT_H
#define DRIVER_INA219_SHOT_H

#include "driver_ina219_interface.h"

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @addtogroup ina219_example_driver
 * @{
 */

/**
 * @brief ina219 shot example default definition
 */
#define INA219_SHOT_DEFAULT_BUS_VOLTAGE_RANGE            INA219_BUS_VOLTAGE_RANGE_32V             /**< set bus voltage range 32V */
#define INA219_SHOT_DEFAULT_BUS_VOLTAGE_ADC_MODE         INA219_ADC_MODE_12_BIT_1_SAMPLES         /**< set bus voltage adc mode 12 bit 1 sample */
#define INA219_SHOT_DEFAULT_SHUNT_VOLTAGE_ADC_MODE       INA219_ADC_MODE_12_BIT_1_SAMPLES         /**< set shunt voltage adc mode 12 bit 1 sample */
#define INA219_SHOT_DEFAULT_PGA                          INA219_PGA_320_MV                        /**< set pga 320 mV */

/**
 * @brief     shot example init
 * @param[in] addr_pin iic address pin
 * @param[in] r reference resistor value
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t ina219_shot_init(ina219_address_t addr_pin, double r);

/**
 * @brief  shot example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ina219_shot_deinit(void);

/**
 * @brief      shot example read
 * @param[out] *mV pointer to a mV buffer
 * @param[out] *mA pointer to a mA buffer
 * @param[out] *mW pointer to a mW buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t ina219_shot_read(float *mV, float *mA, float *mW);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
