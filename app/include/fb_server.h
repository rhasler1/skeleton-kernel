#pragma once

#include "fb_surface.h"

int init_fb_server();                           // attempts to claim fb from kernel
void get_fb_surface(struct fb_surface *out);    // passes memory regions to clients
