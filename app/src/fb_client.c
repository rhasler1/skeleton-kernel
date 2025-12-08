#include "fb_surface.h"
#include "fb_server.h"
#include "delay.h"
#include "uart0.h"

#include "luci_shrunk.h"



void fb_showpicture(struct fb_surface *surface);
void fb_clear();

void client_demo()
{
    int res;
    struct fb_surface surface;
    uart0_puts("Client demo: Requesting fb_surface from Server.\n");
    wait_msec(2000000);
    res = fb_server_create_surface(&surface);
    if (res == -1) {
        uart0_puts("Client demo: Request failed.\n");
    }
    uart0_puts("Client demo: Request succeeded.\n");
    uart0_puts("Client demo: Showing picture.\n");
    fb_showpicture(&surface);
    
    int width, height, depth;
    width = 1280; height = 920; depth = 32;
    uart0_puts("Client: Beginning Frame buffer reconfigure example.\n");
    for (int i = 0; i < 100; i++) {
        width = width - 200;
        height = height - 200;
        if ( (height < 300) | (width < 300) ) {
            width = 1280;
            height = 920;
        }
        uart0_puts("Client: Waiting 2s before sending frame buffer reconfigure request.\n");
        wait_msec(2000000);
        fb_server_reconfig(&surface, width, height, depth); 
        fb_showpicture(&surface);
    }
}
/*
void fb_clear(unsigned int width, unsigned int height, unsigned int depth) {
    uint32_t *p = (uint32_t*)fb_ptr;
    size_t pixels = fb_width * fb_height;

    for (size_t i = 0; i < pixels; i++) {
        p[i] = 0;  // e.g., 0x00000000 for black
    }
}*/

void fb_showpicture(struct fb_surface *surface)
{
    int x,y;
    unsigned char *ptr=surface->base;
    unsigned int height = surface->height;
    unsigned int width = surface->width;
    unsigned int pitch = surface->pitch;
    unsigned int isrgb = surface->isrgb;

    char *data=luci_data, pixel[4];

    ptr += (height-luci_height)/2*pitch + (width-luci_width)*2;
    for(y=0;y<luci_height;y++) {
        for(x=0;x<luci_width;x++) {
            HEADER_PIXEL(data, pixel);
            // the image is in RGB. So if we have an RGB framebuffer, we can copy the pixels
            // directly, but for BGR we must swap R (pixel[0]) and B (pixel[2]) channels.
            *((unsigned int*)ptr)=isrgb ? *((unsigned int *)&pixel) : (unsigned int)(pixel[0]<<16 | pixel[1]<<8 | pixel[2]);
            ptr+=4;
        }
        ptr+=pitch-luci_width*4;
    }
}

