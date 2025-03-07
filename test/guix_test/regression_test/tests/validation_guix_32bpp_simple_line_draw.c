/* This is a small demo of the high-performance GUIX graphics framework. */

#include <stdio.h>
#include "tx_api.h"
#include "gx_api.h"
#include "gx_display.h"
#include "gx_validation_utility.h"

TEST_PARAM test_parameter = {
    "guix_32bpp_simple_line_draw", /* Test name */
    25, 17, 344, 336  /* Define the coordinates of the capture area.
                         In this test, we only need to capture the line
                         drawing area.  */
};

static VOID      control_thread_entry(ULONG);
int main(int argc, char ** argv)
{
    /* Parse the command line argument. */
    gx_validation_setup(argc, argv);

    /* Start ThreadX system */
    tx_kernel_enter(); 
    return(0);
}

VOID tx_application_define(void *first_unused_memory)
{

    /* Create a dedicated thread to perform various operations
       on the line drawing example. These operations simulate 
       user input. */
    gx_validation_control_thread_create(control_thread_entry);

    /* Termiante the test if it runs for more than 100 ticks */
    /* This function is not implemented yet. */
    gx_validation_watchdog_create(100);

    /* Call the actual line example routine. */
    gx_validation_application_define(first_unused_memory);

}


/* Replace the default graphics driver with the validation driver. */
#ifdef win32_graphics_driver_setup_24xrgb  
#undef win32_graphics_driver_setup_24xrgb  
#endif
#define win32_graphics_driver_setup_24xrgb  gx_validation_graphics_driver_setup_24xrgb


#ifdef WIN32
#undef WIN32
#endif

#include "gx_validation_wrapper.h"

#include "demo_guix_lines.c"

VOID test_line_win_draw(GX_WINDOW *window)
{
GX_FILL_PIXELMAP_INFO info;
GX_DRAW_CONTEXT context;

    gx_window_draw(window);

    gx_context_brush_width_set(1);
    gx_context_line_color_set(GX_COLOR_ID_GREEN);
    gx_canvas_line_draw(299, 7, 355, 37);
    gx_canvas_line_draw(263, 338, 360, 292);
    gx_canvas_line_draw(8, 31, 92, 6);
    gx_canvas_line_draw(9, 307, 95, 341);
    gx_canvas_line_draw(30, -6, 70, 34);
    gx_canvas_line_draw(52, 5, 13, 176);
    gx_canvas_line_draw(353, 22, 315, 343);
    gx_canvas_line_draw(50, -6, 90, 35);
    gx_canvas_line_draw(19, 21, 113, 2);
    gx_canvas_line_draw(278, 5, 602, 141);
    gx_canvas_line_draw(21, 285, 183, 548);
    gx_canvas_line_draw(321, 4, 440, 346);

    gx_context_brush_pattern_set(0xf0f0f0f0);
    gx_canvas_line_draw(25, 200, 344, 200);

    memset(&info, 0, sizeof(GX_FILL_PIXELMAP_INFO));
    memset(&context, 0, sizeof(GX_DRAW_CONTEXT));
    context.gx_draw_context_brush.gx_brush_alpha = 255;
    root->gx_window_root_canvas->gx_canvas_display->gx_display_driver_horizontal_pixelmap_line_draw(&context, 34, 200, 1, &info);
}
/* This thread simulates user input.  Its priority is lower
   than the GUIX thread, so that GUIX finishes an operation 
   before this thread is able to issue the next command. */
static VOID control_thread_entry(ULONG input)
{
int frame_id = 1;

    gx_widget_draw_set((GX_WIDGET *)&main_window.main_window_line_window, test_line_win_draw); 

    gx_validation_set_frame_id(frame_id++);
    gx_validation_set_frame_comment("test 32bpp simple line draw");
    gx_validation_screen_refresh();

    /* Signal the end of the test case.  Verify the output. */
    gx_validation_end();

    exit(0);
}





