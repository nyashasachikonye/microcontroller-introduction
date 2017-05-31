//SCHKUZ002 MLKTSH012
#include <stdint.h>

//PROGRAM PROTOTYPES
void delay(void);
int main(void);
void infinite_loop(void);

//VARIABLE DECLARATION
#define GPIO_IDR_0                  ((uint32_t)0x00000001)
#define GPIO_IDR_1                  ((uint32_t)0x00000002)
#define GPIO_IDR_2                  ((uint32_t)0x00000004)
#define GPIO_IDR_3                  ((uint32_t)0x00000008)
#define ADC_CHSELR_CHSEL5           ((uint32_t)0x00000020)
#define ADC_CHSELR_CHSEL6           ((uint32_t)0x00000040)
#define ADC_CFGR1_RES_1             ((uint32_t)0x00000010)
#define ADC_CFGR1_RES_2             ((uint32_t)0x00000030)
#define ADC_CR_ADCAL                ((uint32_t)0x80000000)
#define ADC_CR_ADEN                 ((uint32_t)0x00000001)
#define ADC_ISR_ADRDY               ((uint32_t)0x00000001)
#define ADC_CR_ADSTART              ((uint32_t)0x00000004)
#define ADC_ISR_EOC                 ((uint32_t)0x00000004)

//REGISTER DECLARATION
#define GPIOB_ODR                   ((uint16_t*)0x48000414)
#define GPIOA_IDR                   ((uint32_t*)0x48000010)
#define GPIOB_MODER                 ((uint16_t*)0x48000400)
#define GPIOB_PUPDR                 ((uint16_t*)0x4800000C)
#define GPIOA_MODER                 ((uint16_t*)0x48000000)
#define ADC_CHSELR                  ((uint16_t*)0x40012428)
#define ADC_CFGR1                   ((uint16_t*)0x4001240C)
#define ADC_CR                      ((uint16_t*)0x40012408)
#define ADC_ISR                     ((uint16_t*)0x40012400)
#define ADC_DR                      ((uint16_t*)0x40012440)

//MAIN PROGRAM ROUTINE
int main(void)
{
    *(uint32_t*)0x40021014 |= 0x60000;                                                  //Clocking the GPIOB & GPIOA Ports
    *GPIOB_MODER = 0x5555;                                                    //Enabling GPIOB PINS to OUTPUT
    *GPIOA_MODER = 0x3C00;                                                    //Set Switch to input and pot PA5 & PA6 to analog
    
    *GPIOB_PUPDR = 0x55;                                                       //set sw0-1 to pullup
    *GPIOB_ODR = 0x00C0;                                                    //Writing A0 to GPIOB_ODR
    *(uint32_t*)0x40021018 |= 0x200;                                                    //Clocking ADC
    
    *ADC_CHSELR |= ADC_CHSELR_CHSEL5;                                        // select channel 5
    *ADC_CFGR1 |= ADC_CFGR1_RES_1;
    *ADC_CR |= ADC_CR_ADCAL;
    
    while( ((*ADC_CR & ADC_CR_ADCAL)) != 0);
          ((*ADC_CR)) |= ADC_CR_ADEN;           // set ADEN=1 in the ADC_CR register
           while((((*(uint16_t*)0x40012400)) & ADC_ISR_ADRDY) == 0);
           infinite_loop();                                                                    //Infinite Loop
           }
           
           void infinite_loop(void)
    {
        while (1)
        {
            
            if ((*GPIOA_IDR & GPIO_IDR_0) == 0)
            {
                *GPIOB_ODR += 1;
                delay();
            }
            else if ((*GPIOA_IDR & GPIO_IDR_1) == 0)
            {
                *GPIOB_ODR = 0xC0;
            }
            else if ((*GPIOA_IDR & GPIO_IDR_2) == 0)
            {
                *ADC_CHSELR = ADC_CHSELR_CHSEL5;
                *ADC_CR |= ADC_CR_ADSTART;
                while(((*ADC_ISR) & ADC_ISR_EOC) == 0);
                *GPIOB_ODR = (*ADC_DR);
            }
            else if ((*GPIOA_IDR & GPIO_IDR_3) == 0)
            {
                *ADC_CHSELR = ADC_CHSELR_CHSEL6;
                *ADC_CR |= ADC_CR_ADSTART;
                while(((*ADC_ISR) & ADC_ISR_EOC) == 0);
                *GPIOB_ODR = 0xFF - (*ADC_DR);
            }
        }
    }
           
           void delay(void)
    {
        volatile uint32_t i = 0;
        
        for(; i < 310213; i++)
        {
            //do nothing
        }
        
    }
           
