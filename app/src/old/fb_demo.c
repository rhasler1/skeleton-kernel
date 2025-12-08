// Demo frame buffer policies
#include "fb_server.h"
#include "fb_surface.h"

void demo()
{
    int res = init_fb_server();
    struct fb_surface surface;
    create_fb_surface(&surface);
}
