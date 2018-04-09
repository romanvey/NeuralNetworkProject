/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
extern "C" {
#include "main.h"
#include "lcd5110.h"
}
#include "stm32f3xx_hal.h"
#include "spi.h"
#include "gpio.h"

#include <vector>

/* USER CODE BEGIN Includes */

#define LCD_CS_Pin                  GPIO_PIN_14
#define LCD_CS_GPIO_Port            GPIOB
#define LCD_RST_Pin                 GPIO_PIN_11
#define LCD_RST_GPIO_Port           GPIOB
#define LCD_DC_Pin                  GPIO_PIN_12
#define LCD_DC_GPIO_Port            GPIOB

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

class Display {
public:
	virtual void display_number(int number) = 0;
	virtual void clear() = 0;
};

class Nokia5110Display: public Display {
private:
	LCD5110_display lcd;

public:
	Nokia5110Display(LCD5110_display* lcd) {
		this->lcd = *lcd;
	}

	void display_number(int number) {
		clear();
		set_cursor(0, 0);
		LCD5110_printf(&lcd, BLACK, "\n \n     %04d", number);
	}

	void clear() {
		LCD5110_clear_scr(&lcd);
	}

	void set_cursor(int x, int y) {
		LCD5110_set_cursor(x, y, &lcd);
	}
};

class DiodsDisplay: public Display {
private:
	uint16_t* diods_pins;
	GPIO_TypeDef** diods_gpios;
	int size;

public:
	DiodsDisplay(uint16_t diods_pins[], GPIO_TypeDef* diods_gpios[], int size) {
		this->diods_pins = diods_pins;
		this->diods_gpios = diods_gpios;
		this->size = size;
	}

	void display_number(int number) {
		for (int i = 0; i < size; i++) {
		        HAL_GPIO_WritePin(diods_gpios[size - 1 - i], diods_pins[size - 1 - i],
		        		((number & (1 << i)) >> i) ? GPIO_PIN_SET : GPIO_PIN_RESET);
		    }
	}

	void clear() {
		for (int diod_ind = 0; diod_ind < size; diod_ind++) {
			HAL_GPIO_WritePin(diods_gpios[diod_ind], diods_pins[diod_ind], GPIO_PIN_RESET);
		}
	}
};

class NumberDisplay: public Display {
private:
	std::vector<Display*> displays;

public:
	void display_number(int number) {
		for (unsigned i = 0; i < displays.size(); i++) {
			displays[i]->display_number(number);
		}
	}

	void clear() {
		for (unsigned i = 0; i < displays.size(); i++) {
			displays[i]->clear();
		}
	}

	void add_display(Display* display) {
		displays.push_back(display);
	}

	void remove_display(int index) {
		displays.erase(displays.begin() + index, displays.begin() + index + 1);
	}

	void clear_displays() {
		displays.clear();
	}
};

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI2_Init();

  /* USER CODE BEGIN 2 */

    uint16_t diods_pins[] = {GPIO_PIN_8, GPIO_PIN_9, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12,
                           GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15};
    const uint16_t number_of_diods = 8;
    GPIO_TypeDef* diods_gpios[] = {GPIOE, GPIOE, GPIOE, GPIOE, GPIOE,
                           GPIOE, GPIOE, GPIOE};

    LCD5110_display lcd;
    lcd.hw_conf.spi_handle = &hspi2;
    lcd.hw_conf.spi_cs_pin = LCD_CS_Pin;
    lcd.hw_conf.spi_cs_port = LCD_CS_GPIO_Port;
    lcd.hw_conf.rst_pin =  LCD_RST_Pin;
    lcd.hw_conf.rst_port = LCD_RST_GPIO_Port;
    lcd.hw_conf.dc_pin =  LCD_DC_Pin;
    lcd.hw_conf.dc_port = LCD_DC_GPIO_Port;
    lcd.def_scr = lcd5110_def_scr;
    LCD5110_init(&lcd.hw_conf, LCD5110_NORMAL_MODE, 0x40, 2, 3);

    NumberDisplay number_display;
    number_display.add_display(new Nokia5110Display(&lcd));
    number_display.add_display(new DiodsDisplay(diods_pins, diods_gpios, number_of_diods));

    // number_display.remove_display(1);
    // number_display.clear_displays();
    // number_display.add_display(new Nokia5110Display(&lcd));

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1){
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
        for (int number = 0; number < 255; number++) {
        	number_display.display_number(number);
        	HAL_Delay(1000);
        }
    }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
extern "C" void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    while(1){}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */

/**
  * @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
