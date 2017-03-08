#ifndef _ACER_COLOR_ENGINE_MTK_H_
#define _ACER_COLOR_ENGINE_MTK_H_

void acer_color_initial(void);
int acer_color_analysis_histogram( unsigned int *His, int count);
int acer_color_luma_smooth(void);
int acer_sunlight_readable_luma_smooth(void);
int acer_ALS_analysis_function(int current_ALS_value);
int acer_sunlight_content_analysis_function(int content_aware_profile, int sunlight_readable_profile);
void acer_sunlight_content_smooth(int *, int *);

typedef struct {
    int acer_previous_color_sunlight_engine_enable;
    int acer_previous_content_aware_profile;
    int acer_content_aware_profile;
    int acer_sunlight_readable_profile;
    int acer_sunlight_content_profile;
    int acer_previous_sunlight_content_profile;
    int acer_combine_Sunlight_CurrentFlag;
    int acer_combine_Content_CurrentFlag;
    int acer_combine_Content_PreviousFlag;
    int acer_combine_Sunlight_PreviousFlag;
    int *acer_final_luma_curve;
    int acer_auto_backlight_enable;
    int acer_combine_luma_gain[29];
} ACER_SMART_COLOR_PARAM;

#endif //_ACER_COLOR_ENGINE_MTK_H
