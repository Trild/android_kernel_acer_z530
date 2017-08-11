#ifndef bu52054_hall_sensor
#include <linux/input.h>
#include <linux/earlysuspend.h>
#include <linux/switch.h>

#define bu52054_hall_sensor
#define BU52054_NAME	"hall_sensor"

#define HALL_DEBUG(fmt, arg...) \
	do {\
		if (debug_enable)\
			printk("[hall_sensor][info] %s: "fmt, __FUNCTION__, ##arg);\
	} while(0)

struct bu52054_hall {
	struct delayed_work bu52054_work;
	int state;
        struct switch_dev sdev;
};
#endif
