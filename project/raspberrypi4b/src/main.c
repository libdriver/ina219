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
 * @file      main.c
 * @brief     main source file
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

#include "driver_ina219_shot.h"
#include "driver_ina219_basic.h"
#include "driver_ina219_read_test.h"
#include "driver_ina219_register_test.h"
#include <stdlib.h>

/**
 * @brief     ina219 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 *             - 1 run failed
 *             - 5 param is invalid
 * @note      none
 */
uint8_t ina219(uint8_t argc, char **argv)
{
    if (argc == 1)
    {
        goto help;
    }
    else if (argc == 2)
    {
        if (strcmp("-i", argv[1]) == 0)
        {
            ina219_info_t info;
            
            /* print ina219 info */
            ina219_info(&info);
            ina219_interface_debug_print("ina219: chip is %s.\n", info.chip_name);
            ina219_interface_debug_print("ina219: manufacturer is %s.\n", info.manufacturer_name);
            ina219_interface_debug_print("ina219: interface is %s.\n", info.interface);
            ina219_interface_debug_print("ina219: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
            ina219_interface_debug_print("ina219: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
            ina219_interface_debug_print("ina219: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
            ina219_interface_debug_print("ina219: max current is %0.2fmA.\n", info.max_current_ma);
            ina219_interface_debug_print("ina219: max temperature is %0.1fC.\n", info.temperature_max);
            ina219_interface_debug_print("ina219: min temperature is %0.1fC.\n", info.temperature_min);
            
            return 0;
        }
        else if (strcmp("-p", argv[1]) == 0)
        {
            /* print pin connection */
            ina219_interface_debug_print("ina219: SCL connected to GPIO3(BCM).\n");
            ina219_interface_debug_print("ina219: SDA connected to GPIO2(BCM).\n");
            
            return 0;
        }
        else if (strcmp("-h", argv[1]) == 0)
        {
            /* show ina219 help */
            
            help:
            
            ina219_interface_debug_print("ina219 -i\n\tshow ina219 chip and driver information.\n");
            ina219_interface_debug_print("ina219 -h\n\tshow ina219 help.\n");
            ina219_interface_debug_print("ina219 -p\n\tshow ina219 pin connections of the current board.\n");
            ina219_interface_debug_print("ina219 -t reg -a <addr>\n\trun ina219 register test.addr can be \"0\"-\"F\".\n");
            ina219_interface_debug_print("ina219 -t read <times> -a <addr> -r <value>\n\trun ina219 read test.times is test times."
                                         "addr can be \"0\"-\"F\".value is the resistance value.\n");
            ina219_interface_debug_print("ina219 -c read <times> -a <addr> -r <value>\n\trun ina219 read function.times is test times."
                                         "addr can be \"0\"-\"F\".value is the resistance value.\n");
            ina219_interface_debug_print("ina219 -c shot <times> -a <addr> -r <value>\n\trun ina219 shot function.times is test times."
                                         "addr can be \"0\"-\"F\".value is the resistance value.\n");
            
            return 0;
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 5)
    {
        if (strcmp("-t", argv[1]) == 0)
        {
            if (strcmp("reg", argv[2]) == 0)
            {
                if (strcmp("-a", argv[3]) == 0)
                {
                    uint8_t res;
                    ina219_address_t addr_pin;
                    
                    if (strcmp("0", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_0;
                    }
                    else if (strcmp("1", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_1;
                    }
                    else if (strcmp("2", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_2;
                    }
                    else if (strcmp("3", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_3;
                    }
                    else if (strcmp("4", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_4;
                    }
                    else if (strcmp("5", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_5;
                    }
                    else if (strcmp("6", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_6;
                    }
                    else if (strcmp("7", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_7;
                    }
                    else if (strcmp("8", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_8;
                    }
                    else if (strcmp("9", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_9;
                    }
                    else if (strcmp("A", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_A;
                    }
                    else if (strcmp("B", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_B;
                    }
                    else if (strcmp("C", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_C;
                    }
                    else if (strcmp("D", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_D;
                    }
                    else if (strcmp("E", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_E;
                    }
                    else if (strcmp("F", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_F;
                    }
                    else
                    {
                        return 5;
                    }
                    
                    res = ina219_register_test(addr_pin);
                    if (res != 0)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
                else
                {
                    return 5;
                }
            }
            else
            {
                return 5;
            }
        }
        else
        {
            return 5;
        }
    }
    else if (argc == 8)
    {
        if (strcmp("-t", argv[1]) == 0)
        {
            if (strcmp("read", argv[2]) == 0)
            {
                uint32_t times;
                
                times = atoi(argv[3]);
                
                if (strcmp("-a", argv[4]) == 0)
                {
                    ina219_address_t addr_pin;
                    
                    if (strcmp("0", argv[5]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_0;
                    }
                    else if (strcmp("1", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_1;
                    }
                    else if (strcmp("2", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_2;
                    }
                    else if (strcmp("3", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_3;
                    }
                    else if (strcmp("4", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_4;
                    }
                    else if (strcmp("5", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_5;
                    }
                    else if (strcmp("6", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_6;
                    }
                    else if (strcmp("7", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_7;
                    }
                    else if (strcmp("8", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_8;
                    }
                    else if (strcmp("9", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_9;
                    }
                    else if (strcmp("A", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_A;
                    }
                    else if (strcmp("B", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_B;
                    }
                    else if (strcmp("C", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_C;
                    }
                    else if (strcmp("D", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_D;
                    }
                    else if (strcmp("E", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_E;
                    }
                    else if (strcmp("F", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_F;
                    }
                    else
                    {
                        return 5;
                    }
                    if (strcmp("-r", argv[6]) == 0)
                    {
                        uint8_t res;
                        double r;
                        
                        r = atof(argv[7]);
                        
                        res = ina219_read_test(addr_pin, r, times);
                        if (res != 0)
                        {
                            return 1;
                        }
                        else
                        {
                            return 0;
                        }
                        
                    }
                    else
                    {
                        return 5;
                    }
                }
                else
                {
                    return 5;
                }
            }
            else
            {
                return 5;
            }
        }
        else if (strcmp("-c", argv[1]) == 0)
        {
            if (strcmp("read", argv[2]) == 0)
            {
                uint32_t i, times;
                
                times = atoi(argv[3]);
                if (strcmp("-a", argv[4]) == 0)
                {
                    ina219_address_t addr_pin;
                    
                    if (strcmp("0", argv[5]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_0;
                    }
                    else if (strcmp("1", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_1;
                    }
                    else if (strcmp("2", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_2;
                    }
                    else if (strcmp("3", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_3;
                    }
                    else if (strcmp("4", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_4;
                    }
                    else if (strcmp("5", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_5;
                    }
                    else if (strcmp("6", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_6;
                    }
                    else if (strcmp("7", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_7;
                    }
                    else if (strcmp("8", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_8;
                    }
                    else if (strcmp("9", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_9;
                    }
                    else if (strcmp("A", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_A;
                    }
                    else if (strcmp("B", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_B;
                    }
                    else if (strcmp("C", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_C;
                    }
                    else if (strcmp("D", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_D;
                    }
                    else if (strcmp("E", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_E;
                    }
                    else if (strcmp("F", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_F;
                    }
                    else
                    {
                        return 5;
                    }
                    if (strcmp("-r", argv[6]) == 0)
                    {
                        uint8_t res;
                        double r;
                        
                        r = atof(argv[7]);
                        res = ina219_basic_init(addr_pin, r);
                        if (res != 0)
                        {
                            return 1;
                        }
                        ina219_interface_delay_ms(1000);
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
                        }
                        
                        (void)ina219_basic_deinit();
                        
                        return 0;
                    }
                    else
                    {
                        return 5;
                    }
                }
                else
                {
                    return 5;
                }
            }
            else if (strcmp("shot", argv[2]) == 0)
            {
                uint32_t i, times;
                
                times = atoi(argv[3]);
                if (strcmp("-a", argv[4]) == 0)
                {
                    ina219_address_t addr_pin;
                    
                    if (strcmp("0", argv[5]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_0;
                    }
                    else if (strcmp("1", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_1;
                    }
                    else if (strcmp("2", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_2;
                    }
                    else if (strcmp("3", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_3;
                    }
                    else if (strcmp("4", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_4;
                    }
                    else if (strcmp("5", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_5;
                    }
                    else if (strcmp("6", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_6;
                    }
                    else if (strcmp("7", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_7;
                    }
                    else if (strcmp("8", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_8;
                    }
                    else if (strcmp("9", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_9;
                    }
                    else if (strcmp("A", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_A;
                    }
                    else if (strcmp("B", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_B;
                    }
                    else if (strcmp("C", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_C;
                    }
                    else if (strcmp("D", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_D;
                    }
                    else if (strcmp("E", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_E;
                    }
                    else if (strcmp("F", argv[4]) == 0)
                    {
                        addr_pin = INA219_ADDRESS_F;
                    }
                    else
                    {
                        return 5;
                    }
                    if (strcmp("-r", argv[6]) == 0)
                    {
                        uint8_t res;
                        double r;
                        
                        r = atof(argv[7]);
                        res = ina219_shot_init(addr_pin, r);
                        if (res != 0)
                        {
                            return 1;
                        }
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
                        }
                        
                        (void)ina219_shot_deinit();
                        
                        return 0;
                    }
                    else
                    {
                        return 5;
                    }
                }
                else
                {
                    return 5;
                }
            }
            else
            {
                return 5;
            }
        }
        else
        {
            return 5;
        }
    }
    
    /* param is invalid */
    else
    {
        return 5;
    }
}

/**
 * @brief     main function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *             - 0 success
 * @note      none
 */
int main(uint8_t argc, char **argv)
{
    uint8_t res;

    res = ina219(argc, argv);
    if (res == 0)
    {
        /* run success */
    }
    else if (res == 1)
    {
        ina219_interface_debug_print("ina219: run failed.\n");
    }
    else if (res == 5)
    {
        ina219_interface_debug_print("ina219: param is invalid.\n");
    }
    else
    {
        ina219_interface_debug_print("ina219: unknow status code.\n");
    }

    return 0;
}
