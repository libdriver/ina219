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
 * @file      driver_ina219.c
 * @brief     driver ina219 source file
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

#include "driver_ina219.h" 
#include <math.h>

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Texas Instruments INA219"        /**< chip name */
#define MANUFACTURER_NAME         "Texas Instruments"               /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        3.0f                              /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                              /**< chip max supply voltage */
#define MAX_CURRENT               1.0f                              /**< chip max current */
#define TEMPERATURE_MIN           -25.0f                            /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                             /**< chip max operating temperature */
#define DRIVER_VERSION            1000                              /**< driver version */

/**
 * @brief chip register definition
 */
#define INA219_REG_CONF                 0x00        /**< configuration register */
#define INA219_REG_SHUNT_VOLTAGE        0x01        /**< shunt voltage register */
#define INA219_REG_BUS_VOLTAGE          0x02        /**< bus voltage register */
#define INA219_REG_POWER                0x03        /**< power register */
#define INA219_REG_CURRENT              0x04        /**< current register */
#define INA219_REG_CALIBRATION          0x05        /**< calibration register */

/**
 * @brief      iic interface read bytes
 * @param[in]  *handle points to an ina219 handle structure
 * @param[in]  reg is the iic register address
 * @param[out] *data points to a data buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_ina219_iic_read(ina219_handle_t *handle, uint8_t reg, uint16_t *data)
{
    uint8_t buf[2];
    
    memset(buf, 0, sizeof(uint8_t) * 2);                                        /* clear the buffer */
    if (handle->iic_read(handle->iic_addr, reg, (uint8_t *)buf, 2) != 0)        /* read data */
    {
        return 1;                                                               /* return error */
    }
    else
    {
        *data = (uint16_t)buf[0] << 8 | buf[1];                                 /* get data */
        
        return 0;                                                               /* success return 0 */
    }
}

/**
 * @brief     iic interface write bytes
 * @param[in] *handle points to an ina219 handle structure
 * @param[in] reg is the iic register address
 * @param[in] data is the written data
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_ina219_iic_write(ina219_handle_t *handle, uint8_t reg, uint16_t data)
{
    uint8_t buf[2];
    
    buf[0] = (uint8_t)((data >> 8) & 0xFF);                                      /* get MSB */
    buf[1] = (uint8_t)((data >> 0) & 0xFF);                                      /* get LSB */
    if (handle->iic_write(handle->iic_addr, reg, (uint8_t *)buf, 2) != 0)        /* write data */
    {
        return 1;                                                                /* return error */
    }
    else
    {
        return 0;                                                                /* success return 0 */
    }
}

/**
 * @brief     set the resistance
 * @param[in] *handle points to an ina219 handle structure
 * @param[in] resistance is the current sampling resistance value
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t ina219_set_resistance(ina219_handle_t *handle, double resistance)
{
    if (handle == NULL)            /* check handle */
    {
        return 2;                  /* return error */
    }
    
    handle->r = resistance;        /* set resistance */
    
    return 0;                      /* success return 0 */
}

/**
 * @brief      get the resistance
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *resistance points to a current sampling resistance value buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ina219_get_resistance(ina219_handle_t *handle, double *resistance)
{
    if (handle == NULL)            /* check handle */
    {
        return 2;                  /* return error */
    }
    
    *resistance = handle->r;       /* get resistance */
    
    return 0;                      /* success return 0 */
}

/**
 * @brief     set the iic address pin
 * @param[in] *handle points to an ina219 handle structure
 * @param[in] addr_pin is the address pin
 * @return    status code
 *            - 0 success
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t ina219_set_addr_pin(ina219_handle_t *handle, ina219_address_t addr_pin)
{
    if (handle == NULL)                          /* check handle */
    {
        return 2;                                /* return error */
    }
    
    handle->iic_addr = (uint8_t)addr_pin;        /* set pin */
    
    return 0;                                    /* success return 0 */
}

/**
 * @brief      get the iic address pin
 * @param[in]  *handle points to an ina219 handle structure
 * @param[out] *addr_pin points to an address pin buffer
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ina219_get_addr_pin(ina219_handle_t *handle, ina219_address_t *addr_pin)
{
    if (handle == NULL)                                      /* check handle */
    {
        return 2;                                            /* return error */
    }
    
    *addr_pin = (ina219_address_t)(handle->iic_addr);        /* get pin */
    
    return 0;                                                /* success return 0 */
}

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
uint8_t ina219_soft_reset(ina219_handle_t *handle)
{
    uint8_t res;
    uint16_t prev;
   
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
       
        return 1;                                                              /* return error */
    }
    prev &= ~(1 << 15);                                                        /* clear soft reset */
    prev |= 1 << 15;                                                           /* set soft reset */

    return a_ina219_iic_write(handle, INA219_REG_CONF, (uint16_t )prev);       /* write config */
}

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
uint8_t ina219_set_bus_voltage_range(ina219_handle_t *handle, ina219_bus_voltage_range_t range)
{
    uint8_t res;
    uint16_t prev;
   
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
       
        return 1;                                                              /* return error */
    }
    prev &= ~(1 << 13);                                                        /* clear range bit */
    prev |= range << 13;                                                       /* set range bit */

    return a_ina219_iic_write(handle, INA219_REG_CONF, (uint16_t )prev);       /* write config */
}

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
uint8_t ina219_get_bus_voltage_range(ina219_handle_t *handle, ina219_bus_voltage_range_t *range)
{
    uint8_t res;
    uint16_t prev;
   
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
       
        return 1;                                                              /* return error */
    }
    *range = (ina219_bus_voltage_range_t)((prev >> 13) & 0x01);                /* get range */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t ina219_set_pga(ina219_handle_t *handle, ina219_pga_t pga)
{
    uint8_t res;
    uint16_t prev;
   
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
       
        return 1;                                                              /* return error */
    }
    prev &= ~(3 << 11);                                                        /* clear pga bit */
    prev |= pga << 11;                                                         /* set pga bit */

    return a_ina219_iic_write(handle, INA219_REG_CONF, (uint16_t )prev);       /* write config */
}

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
uint8_t ina219_get_pga(ina219_handle_t *handle, ina219_pga_t *pga)
{
    uint8_t res;
    uint16_t prev;
   
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
       
        return 1;                                                              /* return error */
    }
    *pga = (ina219_pga_t)((prev >> 11) & 0x03);                                /* get pga */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t ina219_set_bus_voltage_adc_mode(ina219_handle_t *handle, ina219_adc_mode_t mode)
{
    uint8_t res;
    uint16_t prev;
   
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
       
        return 1;                                                              /* return error */
    }
    prev &= ~(0xF << 7);                                                       /* clear mode bit */
    prev |= mode << 7;                                                         /* set mode bit */

    return a_ina219_iic_write(handle, INA219_REG_CONF, (uint16_t )prev);       /* write config */
}

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
uint8_t ina219_get_bus_voltage_adc_mode(ina219_handle_t *handle, ina219_adc_mode_t *mode)
{
    uint8_t res;
    uint16_t prev;
   
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
       
        return 1;                                                              /* return error */
    }
    *mode = (ina219_adc_mode_t)((prev >> 7) & 0xF);                            /* get mode */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t ina219_set_shunt_voltage_adc_mode(ina219_handle_t *handle, ina219_adc_mode_t mode)
{
    uint8_t res;
    uint16_t prev;
   
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
       
        return 1;                                                              /* return error */
    }
    prev &= ~(0xF << 3);                                                       /* clear mode bit */
    prev |= mode << 3;                                                         /* set mode bit */

    return a_ina219_iic_write(handle, INA219_REG_CONF, (uint16_t )prev);       /* write config */
}

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
uint8_t ina219_get_shunt_voltage_adc_mode(ina219_handle_t *handle, ina219_adc_mode_t *mode)
{
    uint8_t res;
    uint16_t prev;
   
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
       
        return 1;                                                              /* return error */
    }
    *mode = (ina219_adc_mode_t)((prev >> 3) & 0xF);                            /* get mode */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t ina219_set_mode(ina219_handle_t *handle, ina219_mode_t mode)
{
    uint8_t res;
    uint16_t prev;
   
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
       
        return 1;                                                              /* return error */
    }
    prev &= ~(0x7 << 0);                                                       /* clear mode bit */
    prev |= mode << 0;                                                         /* set mode bit */
    res = a_ina219_iic_write(handle, INA219_REG_CONF, (uint16_t )prev);        /* write config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: write conf register failed.\n");          /* write conf register failed */
       
        return 1;                                                              /* return error */
    }
    if ((mode >= INA219_MODE_SHUNT_VOLTAGE_TRIGGERED) &&                       /* check mode */
        (mode <= INA219_MODE_SHUNT_BUS_VOLTAGE_TRIGGERED))
    {
        uint8_t m, mode1, mode2, t;
        
        mode1 = (prev >> 3) & 0xF;                                             /* get shunt adc mode */
        mode2 = (prev >> 7) & 0xF;                                             /* get bus adc mode */
        m = (mode1 > mode2) ? mode1 : mode2;                                   /* get max mode */
        if (m <= 8)                                                            /* check mode */
        {
            handle->delay_ms(1);                                               /* delay 1 ms */
        }
        else
        {
            t = (uint8_t)(0.532 * pow(2, m - 8)) + 1;                          /* get time */
            handle->delay_ms(t);                                               /* delay time */
        }
        
        return 0;                                                              /* success return 0 */
    }
    else
    {
        return 0;                                                              /* success return 0 */
    }
}

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
uint8_t ina219_get_mode(ina219_handle_t *handle, ina219_mode_t *mode)
{
    uint8_t res;
    uint16_t prev;
   
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
       
        return 1;                                                              /* return error */
    }
    *mode = (ina219_mode_t)((prev >> 0) & 0x7);                                /* get mode */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t ina219_read_shunt_voltage(ina219_handle_t *handle, int16_t *raw, float *mV)
{
    uint8_t res;
    union
    {
        uint16_t u;
        int16_t s;
    } u;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_SHUNT_VOLTAGE, (uint16_t *)&u.u);      /* read shunt voltage */
    if (res != 0)                                                                     /* check result */
    {
        handle->debug_print("ina219: read shunt voltage register failed.\n");         /* read shunt voltage register failed */
       
        return 1;                                                                     /* return error */
    }
    *raw = u.s;                                                                       /* set the raw */
    *mV = (float)(*raw) / 100.0f;                                                     /* set the converted data */
    
    return 0;                                                                         /* success return 0 */
}

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
uint8_t ina219_read_bus_voltage(ina219_handle_t *handle, uint16_t *raw, float *mV)
{
    uint8_t res;
   
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_BUS_VOLTAGE, (uint16_t *)raw);       /* read bus voltage */
    if (res != 0)                                                                   /* check result */
    {
        handle->debug_print("ina219: read bus voltage register failed.\n");         /* read bus voltage register failed */
       
        return 1;                                                                   /* return error */
    }
    if (((*raw) & (1 << 0)) != 0)
    {
        handle->debug_print("ina219: math overflow.\n");                            /* math overflow */
       
        return 4;                                                                   /* return error */
    }
    if (((*raw) & (1 << 1)) == 0)
    {
        handle->debug_print("ina219: conversion not ready.\n");                     /* math overflow */
       
        return 5;                                                                   /* return error */
    }
    *raw = (*raw) >> 3;                                                             /* right shift 3 */
    *mV = (float)(*raw) * 4.0f;                                                     /* set the converted data */
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t ina219_read_current(ina219_handle_t *handle, int16_t *raw, float *mA)
{
    uint8_t res;
    union
    {
        uint16_t u;
        int16_t s;
    } u;
   
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CURRENT, (uint16_t *)&u.u);      /* read current */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("ina219: read current register failed.\n");         /* read current register failed */
       
        return 1;                                                               /* return error */
    }
    *raw = u.s;                                                                 /* set the raw */
    *mA = (float)((double)(*raw) * handle->current_lsb * 1000);                 /* set the converted data */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t ina219_read_power(ina219_handle_t *handle, uint16_t *raw, float *mW)
{
    uint8_t res;
   
    if (handle == NULL)                                                         /* check handle */
    {
        return 2;                                                               /* return error */
    }
    if (handle->inited != 1)                                                    /* check handle initialization */
    {
        return 3;                                                               /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_POWER, (uint16_t *)raw);         /* read power */
    if (res != 0)                                                               /* check result */
    {
        handle->debug_print("ina219: read power register failed.\n");           /* read power register failed */
       
        return 1;                                                               /* return error */
    }
    *mW = (float)((double)(*raw) * handle->current_lsb * 20.0 * 1000.0);        /* set the converted data */
    
    return 0;                                                                   /* success return 0 */
}

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
uint8_t ina219_get_calibration(ina219_handle_t *handle, uint16_t *data)
{
    uint8_t res;
   
    if (handle == NULL)                                                              /* check handle */
    {
        return 2;                                                                    /* return error */
    }
    if (handle->inited != 1)                                                         /* check handle initialization */
    {
        return 3;                                                                    /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CALIBRATION, (uint16_t *)data);       /* read calibration */
    if (res != 0)                                                                    /* check result */
    {
        handle->debug_print("ina219: read calibration register failed.\n");          /* read calibration register failed */
       
        return 1;                                                                    /* return error */
    }
    
    return 0;                                                                        /* success return 0 */
}

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
uint8_t ina219_calculate_calibration(ina219_handle_t *handle, uint16_t *calibration)
{
    uint8_t res;
    uint16_t prev;
    uint8_t pga;
    double v;
   
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    if ((handle->r >= -0.000001f)  && (handle->r <= 0.000001f))                /* check the r */
    {
        handle->debug_print("ina219: r can't be zero.\n");                     /* r can't be zero */
       
        return 4;                                                              /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read conf */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
       
        return 1;                                                              /* return error */
    }
    pga = (prev >> 11) & 0x3;                                                  /* get pga */
    switch (pga)                                                               /* select the pga */
    {
        case 0 :
        {
            v = 0.04;                                                          /* 0.04 V */
            res = 0;                                                           /* set ok */
            
            break;
        }
        case 1 :
        {
            v = 0.08;                                                          /* 0.08 V */
            res = 0;                                                           /* set ok */
            
            break;
        }
        case 2 :
        {
            v = 0.16;                                                          /* 0.16 V */
            res = 0;                                                           /* set ok */
            
            break;
        }
        case 3 :
        {
            v = 0.32;                                                          /* 0.32 V */
            res = 0;                                                           /* set ok */
            
            break;
        }
        default :
        {
            v = 0.0;                                                           /* 0.0 V */
            res = 1;                                                           /* set failed */
            
            break;
        }
    }
    if (res == 1)
    {
        handle->debug_print("ina219: pga is invalid.\n");                      /* pga is invalid*/
        
        return 5;                                                              /* return error */
    }
    else
    {
        handle->current_lsb = v / handle->r / pow(2.0, 15.0);                  /* current lsb */
        *calibration = (uint16_t)(0.04096 / (v / pow(2.0, 15.0)));             /* set calibration */
        
        return 0;                                                              /* success return 0 */
    }
}

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
uint8_t ina219_set_calibration(ina219_handle_t *handle, uint16_t data)
{
    uint8_t res;
   
    if (handle == NULL)                                                             /* check handle */
    {
        return 2;                                                                   /* return error */
    }
    if (handle->inited != 1)                                                        /* check handle initialization */
    {
        return 3;                                                                   /* return error */
    }
    
    res = a_ina219_iic_write(handle, INA219_REG_CALIBRATION, data);                 /* write calibration */
    if (res != 0)                                                                   /* check result */
    {
        handle->debug_print("ina219: write calibration register failed.\n");        /* write calibration register failed */
       
        return 1;                                                                   /* return error */
    }
    
    return 0;                                                                       /* success return 0 */
}

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
uint8_t ina219_init(ina219_handle_t *handle)
{
    uint8_t res;
    uint16_t prev;
    
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->debug_print == NULL)                                           /* check debug_print */
    {
        return 3;                                                              /* return error */
    }
    if (handle->iic_init == NULL)                                              /* check iic_init */
    {
        handle->debug_print("ina219: iic_init is null.\n");                    /* iic_init is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->iic_deinit == NULL)                                            /* check iic_deinit */
    {
        handle->debug_print("ina219: iic_deinit is null.\n");                  /* iic_deinit is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->iic_read == NULL)                                              /* check iic_read */
    {
        handle->debug_print("ina219: iic_read is null.\n");                    /* iic_read is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->iic_write == NULL)                                             /* check iic_write */
    {
        handle->debug_print("ina219: iic_write is null.\n");                   /* iic_write is null */
        
        return 3;                                                              /* return error */
    }
    if (handle->delay_ms == NULL)                                              /* check delay_ms */
    {
        handle->debug_print("ina219: delay_ms is null.\n");                    /* delay_ms is null */
        
        return 3;                                                              /* return error */
    }
    
    if (handle->iic_init() != 0)                                               /* iic init */
    {
        handle->debug_print("ina219: iic init failed.\n");                     /* iic init failed */
        
        return 1;                                                              /* return error */
    }
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read conf */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
        (void)handle->iic_deinit();                                            /* iic deinit */
       
        return 4;                                                              /* return error */
    }
    prev |= 1 << 15;
    res = a_ina219_iic_write(handle, INA219_REG_CONF, prev);                   /* write conf */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: write conf register failed.\n");          /* write conf register failed */
        (void)handle->iic_deinit();                                            /* iic deinit */
        
        return 4;                                                              /* return error */
    }
    handle->delay_ms(10);                                                      /* delay 10 ms */
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read conf */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
        (void)handle->iic_deinit();                                            /* iic deinit */
        
        return 4;                                                              /* return error */
    }
    if ((prev & (1 << 15)) != 0)                                               /* check the result */
    {
        handle->debug_print("ina219: soft reset failed.\n");                   /* soft reset failed */
        (void)handle->iic_deinit();                                            /* iic deinit */
        
        return 4;                                                              /* return error */
    }
    
    handle->inited = 1;                                                        /* flag inited */
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t ina219_deinit(ina219_handle_t *handle)
{
    uint8_t res;
    uint16_t prev;
   
    if (handle == NULL)                                                        /* check handle */
    {
        return 2;                                                              /* return error */
    }
    if (handle->inited != 1)                                                   /* check handle initialization */
    {
        return 3;                                                              /* return error */
    }
    
    res = a_ina219_iic_read(handle, INA219_REG_CONF, (uint16_t *)&prev);       /* read config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: read conf register failed.\n");           /* read conf register failed */
       
        return 4;                                                              /* return error */
    }
    prev &= ~(0x07);                                                           /* clear mode */
    res = a_ina219_iic_write(handle, INA219_REG_CONF, (uint16_t )prev);        /* write config */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: write conf register failed.\n");          /* write conf register failed */
       
        return 4;                                                              /* return error */
    }
    res = handle->iic_deinit();                                                /* iic deinit */
    if (res != 0)                                                              /* check result */
    {
        handle->debug_print("ina219: iic deinit failed.\n");                   /* iic deinit failed */
       
        return 1;                                                              /* return error */
    }
    
    return 0;                                                                  /* success return 0 */
}

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
uint8_t ina219_set_reg(ina219_handle_t *handle, uint8_t reg, uint16_t data)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    return a_ina219_iic_write(handle, reg, data);       /* write data */
}

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
uint8_t ina219_get_reg(ina219_handle_t *handle, uint8_t reg, uint16_t *data)
{
    if (handle == NULL)                                /* check handle */
    {
        return 2;                                      /* return error */
    }
    if (handle->inited != 1)                           /* check handle initialization */
    {
        return 3;                                      /* return error */
    }
    
    return a_ina219_iic_read(handle, reg, data);       /* read data */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an ina219 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ina219_info(ina219_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(ina219_info_t));                         /* initialize ina219 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
