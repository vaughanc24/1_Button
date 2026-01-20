// COLIN VAUGHAN 1/20/2026
// This code connects to a LED output and a button input
// The code assumes the button is in an active high configuration
// Pressing the button activates the LED on every other button press
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"

void delay_ms(int t) {
  vTaskDelay(t /portTICK_PERIOD_MS);
}

#define LED_GPIO GPIO_NUM_10       // Choose your LED pin
#define BUTTON_GPIO GPIO_NUM_4       // Choose your button pin
#define LOOP_DELAY_MS 25          // Loop delay in milliseconds

void app_main(void) {

    // Configure LED outputx  
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    gpio_pullup_dis(LED_GPIO);
    gpio_pulldown_dis(LED_GPIO);
    gpio_intr_disable(LED_GPIO);

    // Configure Button input
    gpio_reset_pin(BUTTON_GPIO);
    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);

    gpio_pullup_en(BUTTON_GPIO);
    gpio_pulldown_dis(BUTTON_GPIO);
    gpio_intr_disable(BUTTON_GPIO);

    //logic variables
    bool bstate = false;   
    bool lstate = false;   
    bool pressed;          
    int press_count = 0;   
   

    while (1){
        pressed = (gpio_get_level(BUTTON_GPIO) == 1);

        // Detect: released -> pressed
      if (!bstate && pressed){
        bstate = true;  // remember button is pressed
      }
      // Detect: pressed -> released 
      if (bstate && !pressed){
        press_count++;

       // Every other press turns LED ON 
        if (press_count % 2 == 0){
          lstate = true;
        }
        else{
          lstate = false;
        }

        gpio_set_level(LED_GPIO, lstate);
        bstate = false; // remember button is released
    }

    delay_ms(LOOP_DELAY_MS);
    printf("Button state: %d | Press count: %d | LED: %d\n", pressed, press_count, lstate);
   }
}


