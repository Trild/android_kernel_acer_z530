#ifndef __DDP_DEBUG_H__
#define __DDP_DEBUG_H__

#include <linux/kernel.h>
#include "ddp_mmp.h"
#include "ddp_dump.h"

#define DISP_ENABLE_SODI_FOR_VIDEO_MODE
void ddp_debug_init(void);
void ddp_debug_exit(void);

unsigned int  ddp_debug_analysis_to_buffer(void);
unsigned int  ddp_debug_dbg_log_level(void);
unsigned int  ddp_debug_irq_log_level(void);

int ddp_mem_test(void);
int ddp_lcd_test(void);

extern bool sunlight_content_color_engine_enable; /*Acer 20150610 add for color engine debug*/
#endif /* __DDP_DEBUG_H__ */
