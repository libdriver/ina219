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
#include "shell.h"
#include "clock.h"
#include "delay.h"
#include "uart.h"
#include "getopt.h"
#include <stdlib.h>

/**
 * @brief global var definition
 */
uint8_t g_buf[256];        /**< uart buffer */
volatile uint16_t g_len;   /**< uart buffer length */

/**
 * @brief     ina219 full function
 * @param[in] argc is arg numbers
 * @param[in] **argv is the arg address
 * @return    status code
 *            - 0 success
 *            - 1 run failed
 *            - 5 param is invalid
 * @note      none
 */
uint8_t ina219(uint8_t argc, char **argv)
{
    int c;
    int longindex = 0;
    const char short_options[] = "hipe:t:";
    const struct option long_options[] =
    {
        {"help", no_argument, NULL, 'h'},
        {"information", no_argument, NULL, 'i'},
        {"port", no_argument, NULL, 'p'},
        {"example", required_argument, NULL, 'e'},
        {"test", required_argument, NULL, 't'},
        {"addr", required_argument, NULL, 1},
        {"resistance", required_argument, NULL, 2},
        {"times", required_argument, NULL, 3},
        {NULL, 0, NULL, 0},
    };
    char type[33] = "unknown";
    uint32_t times = 3;
    double r = 0.1;
    ina219_address_t addr = INA219_ADDRESS_0;
    
    /* if no params */
    if (argc == 1)
    {
        /* goto the help */
        goto help;
    }
    
    /* init 0 */
    optind = 0;
    
    /* parse */
    do
    {
        /* parse the args */
        c = getopt_long(argc, argv, short_options, long_options, &longindex);
        
        /* judge the result */
        switch (c)
        {
            /* help */
            case 'h' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "h");
                
                break;
            }
            
            /* information */
            case 'i' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "i");
                
                break;
            }
            
            /* port */
            case 'p' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "p");
                
                break;
            }
            
            /* example */
            case 'e' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "e_%s", optarg);
                
                break;
            }
            
            /* test */
            case 't' :
            {
                /* set the type */
                memset(type, 0, sizeof(char) * 33);
                snprintf(type, 32, "t_%s", optarg);
                
                break;
            }
            
            /* addr */
            case 1 :
            {
                /* set the addr pin */
                if (strcmp("0", optarg) == 0)
                {
                    addr = INA219_ADDRESS_0;
                }
                else if (strcmp("1", optarg) == 0)
                {
                    addr = INA219_ADDRESS_1;
                }
                else if (strcmp("2", optarg) == 0)
                {
                    addr = INA219_ADDRESS_2;
                }
                else if (strcmp("3", optarg) == 0)
                {
                    addr = INA219_ADDRESS_3;
                }
                else if (strcmp("4", optarg) == 0)
                {
                    addr = INA219_ADDRESS_4;
                }
                else if (strcmp("5", optarg) == 0)
                {
                    addr = INA219_ADDRESS_5;
                }
                else if (strcmp("6", optarg) == 0)
                {
                    addr = INA219_ADDRESS_6;
                }
                else if (strcmp("7", optarg) == 0)
                {
                    addr = INA219_ADDRESS_7;
                }
                else if (strcmp("8", optarg) == 0)
                {
                    addr = INA219_ADDRESS_8;
                }
                else if (strcmp("9", optarg) == 0)
                {
                    addr = INA219_ADDRESS_9;
                }
                else if (strcmp("A", optarg) == 0)
                {
                    addr = INA219_ADDRESS_A;
                }
                else if (strcmp("B", optarg) == 0)
                {
                    addr = INA219_ADDRESS_B;
                }
                else if (strcmp("C", optarg) == 0)
                {
                    addr = INA219_ADDRESS_C;
                }
                else if (strcmp("D", optarg) == 0)
                {
                    addr = INA219_ADDRESS_D;
                }
                else if (strcmp("E", optarg) == 0)
                {
                    addr = INA219_ADDRESS_E;
                }
                else if (strcmp("F", optarg) == 0)
                {
                    addr = INA219_ADDRESS_F;
                }
                else
                {
                    return 5;
                }
                
                break;
            }
            
            /* resistance */
            case 2 :
            {
                /* set the resistance */
                r = atof(optarg);
                
                break;
            }

            /* running times */
            case 3 :
            {
                /* set the times */
                times = atol(optarg);
                
                break;
            } 
            
            /* the end */
            case -1 :
            {
                break;
            }
            
            /* others */
            default :
            {
                return 5;
            }
        }
    } while (c != -1);

    /* run the function */
    if (strcmp("t_reg", type) == 0)
    {
        uint8_t res;
        
        /* run the reg test */
        res = ina219_register_test(addr);
        if (res != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("t_read", type) == 0)
    {
        uint8_t res;
        
        /* run the read test */
        res = ina219_read_test(addr, r, times);
        if (res != 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else if (strcmp("e_read", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* basic init */
        res = ina219_basic_init(addr, r);
        if (res != 0)
        {
            return 1;
        }
        
        /* delay 1000ms */
        ina219_interface_delay_ms(1000);
        
        /* loop */
        for (i = 0; i < times; i++)
        {
            float mV;
            float mA;
            float mW;
            
            /* read data */
            res = ina219_basic_read(&mV, &mA, &mW);
            if (res != 0)
            {
                (void)ina219_basic_deinit();
                
                return 1;
            }
            
            /* output */
            ina219_interface_debug_print("ina219: %d/%d.\n", i + 1, times);
            ina219_interface_debug_print("ina219: bus voltage is %0.3fmV.\n", mV);
            ina219_interface_debug_print("ina219: current is %0.3fmA.\n", mA);
            ina219_interface_debug_print("ina219: power is %0.3fmW.\n", mW);
            ina219_interface_delay_ms(1000);
        }
        
        /* deinit */
        (void)ina219_basic_deinit();
        
        return 0;
    }
    else if (strcmp("e_shot", type) == 0)
    {
        uint8_t res;
        uint32_t i;
        
        /* shot init */
        res = ina219_shot_init(addr, r);
        if (res != 0)
        {
            return 1;
        }
        
        /* delay 1000ms */
        ina219_interface_delay_ms(1000);

        /* loop */
        for (i = 0; i < times; i++)
        {
            float mV;
            float mA;
            float mW;
            
            /* read data */
            res = ina219_shot_read(&mV, &mA, &mW);
            if (res != 0)
            {
                (void)ina219_shot_deinit();
                
                return 1;
            }
            
            /* output */
            ina219_interface_debug_print("ina219: %d/%d.\n", i + 1, times);
            ina219_interface_debug_print("ina219: bus voltage is %0.3fmV.\n", mV);
            ina219_interface_debug_print("ina219: current is %0.3fmA.\n", mA);
            ina219_interface_debug_print("ina219: power is %0.3fmW.\n", mW);
            ina219_interface_delay_ms(1000);
        }
        
        /* shot deinit */
        (void)ina219_shot_deinit();
        
        return 0;
    }
    else if (strcmp("h", type) == 0)
    {
        help:
        ina219_interface_debug_print("Usage:\n");
        ina219_interface_debug_print("  ina219 (-i | --information)\n");
        ina219_interface_debug_print("  ina219 (-h | --help)\n");
        ina219_interface_debug_print("  ina219 (-p | --port)\n");
        ina219_interface_debug_print("  ina219 (-t reg | --test=reg) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F>]\n");
        ina219_interface_debug_print("  ina219 (-t read | --test=read) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F>]\n");
        ina219_interface_debug_print("         [--resistance=<r>] [--times=<num>]\n");
        ina219_interface_debug_print("  ina219 (-e read | --example=read) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F>]\n");
        ina219_interface_debug_print("         [--resistance=<r>] [--times=<num>]\n");
        ina219_interface_debug_print("  ina219 (-e shot | --example=shot) [--addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F>]\n");
        ina219_interface_debug_print("         [--resistance=<r>] [--times=<num>]\n");
        ina219_interface_debug_print("\n");
        ina219_interface_debug_print("Options:\n");
        ina219_interface_debug_print("      --addr=<0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F>\n");
        ina219_interface_debug_print("                                 Set the addr pin.([default: 0])\n");
        ina219_interface_debug_print("  -e <read | shot>, --example=<read | shot>\n");
        ina219_interface_debug_print("                                 Run the driver example.\n");
        ina219_interface_debug_print("  -h, --help                     Show the help.\n");
        ina219_interface_debug_print("  -i, --information              Show the chip information.\n");
        ina219_interface_debug_print("  -p, --port                     Display the pin connections of the current board.\n");
        ina219_interface_debug_print("      --resistance=<r>           Set the sample resistance.([default: 0.1])\n");
        ina219_interface_debug_print("  -t <reg | read>, --test=<reg | read>\n");
        ina219_interface_debug_print("                                 Run the driver test.\n");
        ina219_interface_debug_print("      --times=<num>              Set the running times.([default: 3])\n");

        return 0;
    }
    else if (strcmp("i", type) == 0)
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
    else if (strcmp("p", type) == 0)
    {
        /* print pin connection */
        ina219_interface_debug_print("ina219: SCL connected to GPIOB PIN8.\n");
        ina219_interface_debug_print("ina219: SDA connected to GPIOB PIN9.\n");
        
        return 0;
    }
    else
    {
        return 5;
    }
}

/**
 * @brief main function
 * @note  none
 */
int main(void)
{
    uint8_t res;
    
    /* stm32f407 clock init and hal init */
    clock_init();
    
    /* delay init */
    delay_init();
    
    /* uart init */
    uart_init(115200);
    
    /* shell init && register ina219 function */
    shell_init();
    shell_register("ina219", ina219);
    uart_print("ina219: welcome to libdriver ina219.\n");
    
    while (1)
    {
        /* read uart */
        g_len = uart_read(g_buf, 256);
        if (g_len != 0)
        {
            /* run shell */
            res = shell_parse((char *)g_buf, g_len);
            if (res == 0)
            {
                /* run success */
            }
            else if (res == 1)
            {
                uart_print("ina219: run failed.\n");
            }
            else if (res == 2)
            {
                uart_print("ina219: unknown command.\n");
            }
            else if (res == 3)
            {
                uart_print("ina219: length is too long.\n");
            }
            else if (res == 4)
            {
                uart_print("ina219: pretreat failed.\n");
            }
            else if (res == 5)
            {
                uart_print("ina219: param is invalid.\n");
            }
            else
            {
                uart_print("ina219: unknown status code.\n");
            }
            uart_flush();
        }
        delay_ms(100);
    }
}
