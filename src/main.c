
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/printk.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   400


#define LED		DT_NODELABEL(led4)
#define BUTTON 	DT_NODELABEL(button0)

static const struct gpio_dt_spec led_spec = GPIO_DT_SPEC_GET(LED, gpios);
static const struct gpio_dt_spec button_spec = GPIO_DT_SPEC_GET(BUTTON, gpios); 

static struct gpio_callback button_cb; 

void button_pressed_callback (const struct device *gpiob, struct gpio_callback *cb, gpio_port_pins_t pins){
	gpio_pin_toggle_dt (&led_spec);
}

int main(void)
{
	gpio_pin_configure_dt(&led_spec, GPIO_OUTPUT);
	gpio_pin_configure_dt(&button_spec, GPIO_INPUT);

	gpio_init_callback(&button_cb, button_pressed_callback, BIT(button_spec.pin));
	gpio_add_callback(button_spec.port, &button_cb);
	gpio_pin_interrupt_configure_dt(&button_spec, GPIO_INT_EDGE_TO_ACTIVE);

	while(1){
		k_msleep(SLEEP_TIME_MS);
	}
	return 0; 
}
