#include "stm32l432xx.h"

volatile uint8_t counter = 0;

// Button delay
#define DEBOUNCE_DELAY 300000

// LED pins - all on GPIOA, pins 0-7
#define LED_PORT GPIOA
#define LED_PINS 0xFF  // Using pins 0-7 for LEDs

// Button pins - on GPIOB
#define BUTTON_PORT GPIOB
#define INCREMENT_BTN_PIN 0  // PB0
#define DECREMENT_BTN_PIN 1  // PB1
#define RESET_BTN_PIN     2  // PB2

void SystemInit(void);
void GPIO_Init(void);
void delay(volatile uint32_t count);
uint8_t readButton(uint8_t pin);
void updateLEDs(uint8_t value);

int main(void)
{
    SystemInit();
    
    GPIO_Init();
    
    while (1)
    {
        if (readButton(INCREMENT_BTN_PIN))
        {
            counter++;
            updateLEDs(counter);
            delay(DEBOUNCE_DELAY);
        }
        
        if (readButton(DECREMENT_BTN_PIN))
        {
            counter--;
            updateLEDs(counter);
            delay(DEBOUNCE_DELAY);
        }
        
        if (readButton(RESET_BTN_PIN))
        {
            counter = 0;
            updateLEDs(counter);
            delay(DEBOUNCE_DELAY);
        }
    }
}

void SystemInit(void)
{
    // Enable clock for GPIOA and GPIOB
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN;
}

void GPIO_Init(void)
{
    // Configure LED pins as outputs (GPIOA pins 0-7)
    // Clear the bits first
    LED_PORT->MODER &= ~(0xFFFF);  // Clear mode bits for pins 0-7
    LED_PORT->MODER |= 0x5555;     // Set as outputs (01 pattern for each pin)
    
    // Configure button pins as inputs with pull-up resistors
    // Clear the mode bits for button pins
    BUTTON_PORT->MODER &= ~((3 << (INCREMENT_BTN_PIN * 2)) | 
                           (3 << (DECREMENT_BTN_PIN * 2)) | 
                           (3 << (RESET_BTN_PIN * 2)));
    
    // Enable pull-up resistors for button pins
    BUTTON_PORT->PUPDR &= ~((3 << (INCREMENT_BTN_PIN * 2)) | 
                           (3 << (DECREMENT_BTN_PIN * 2)) | 
                           (3 << (RESET_BTN_PIN * 2)));
    BUTTON_PORT->PUPDR |= ((1 << (INCREMENT_BTN_PIN * 2)) | 
                          (1 << (DECREMENT_BTN_PIN * 2)) | 
                          (1 << (RESET_BTN_PIN * 2)));
    
    // Initial LED state
    updateLEDs(counter);
}

void delay(volatile uint32_t count)
{
    while (count--);
}

uint8_t readButton(uint8_t pin)
{
    // Return 1 if button is pressed (active low due to pull-up)
    return !(BUTTON_PORT->IDR & (1 << pin));
}

void updateLEDs(uint8_t value)
{
    // Clear all LED pins
    LED_PORT->ODR &= ~LED_PINS;
    
    // Set the pins according to the counter value
    LED_PORT->ODR |= (value & LED_PINS);
}
