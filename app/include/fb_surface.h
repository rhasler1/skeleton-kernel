#pragma once

struct fb_surface {
    unsigned char *base;        //beginning of this surface
    unsigned int width;
    unsigned int height;

    unsigned int pitch;
    unsigned int isrgb;
};
