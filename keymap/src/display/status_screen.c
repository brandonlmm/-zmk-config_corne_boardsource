#include <zephyr/kernel.h>
#include <lvgl.h>

#include <zmk/display/status_screen.h>
#include <zmk/display/widgets/battery_status.h>
#include <zmk/display/widgets/layer_status.h>
#include <zmk/display/widgets/output_status.h>

static lv_obj_t *screen;
static struct zmk_widget_battery_status battery_widget;
static struct zmk_widget_layer_status   layer_widget;
static struct zmk_widget_output_status  output_widget;

lv_obj_t *zmk_display_status_screen(void) {
    screen = lv_obj_create(NULL);

    /* Battery % (top-right) */
    zmk_widget_battery_status_init(&battery_widget, screen);
    lv_obj_align(zmk_widget_battery_status_obj(&battery_widget), LV_ALIGN_TOP_RIGHT, -2, 2);

    /* Layer (bottom-left) */
    zmk_widget_layer_status_init(&layer_widget, screen);
    lv_obj_align(zmk_widget_layer_status_obj(&layer_widget), LV_ALIGN_BOTTOM_LEFT, 2, -2);

    /* Output (bottom-right) */
    zmk_widget_output_status_init(&output_widget, screen);
    lv_obj_align(zmk_widget_output_status_obj(&output_widget), LV_ALIGN_BOTTOM_RIGHT, -2, -2);

    /* Side label so halves look different */
    lv_obj_t *side = lv_label_create(screen);
#if IS_ENABLED(CONFIG_SHIELD_CORNE_LEFT)
    lv_label_set_text(side, "L");
#else
    lv_label_set_text(side, "R");
#endif
    lv_obj_align(side, LV_ALIGN_TOP_LEFT, 4, 2);

    return screen;
}
