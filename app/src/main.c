/*
 *
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>
#define SLEEP_TIME_MS 1000

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)

static const struct gpio_dt_spec leds[] = {
    GPIO_DT_SPEC_GET(LED0_NODE, gpios),
    GPIO_DT_SPEC_GET(LED1_NODE, gpios),
    GPIO_DT_SPEC_GET(LED2_NODE, gpios),
};

#define NUM_LEDS ARRAY_SIZE(leds)

int main(void)
{
    int ret;
    printk("HEELLLO\n");
    for (int i = 0; i < NUM_LEDS; i++) {
        if (!gpio_is_ready_dt(&leds[i])) {
            printf("LED %d not ready\n", i);
            return 1;
        }

        ret = gpio_pin_configure_dt(&leds[i], GPIO_OUTPUT_ACTIVE);
        if (ret < 0) {
            printf("Failed to configure LED %d (err %d)\n", i, ret);
            return 1;
        }
    }

    while (1) {
        for (int i = 0; i < NUM_LEDS; i++) {
            gpio_pin_toggle_dt(&leds[i]);
        }

        printf("Toggled all LEDs\n");
        k_msleep(SLEEP_TIME_MS);
    }

    return 0;
}

