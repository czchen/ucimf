#include <stdint.h>
#include <iiimcf.h>

#ifdef __cplusplus
extern "C" {
#endif

/* initialization */
int iiimccf_init();
int iiimccf_exit();

/* status switching */
int iiimccf_on();
int iiimccf_off();

/* keyboard input */
int iiimccf_proc( int keycode, int keychar, int modifier );

/* committed output */
int iiimccf_result( char* *buf_out );

/* current screen setting */
void iiimccf_scrn( int height, int width, int resolution );

/* current position */
void iiimccf_pos( int x, int y);

/* request refresh */
void iiimccf_refresh();

#ifdef __cplusplus
}
#endif
