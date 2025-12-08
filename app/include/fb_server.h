#pragma once

#include "fb_surface.h"

int     fb_server_init              ();                         // attempts to claim fb from kernel
int     fb_server_reconfig          (struct fb_surface *surface, unsigned int width, unsigned int height, unsigned int depth);
int     fb_server_create_surface    (struct fb_surface *out);   // passes memory regions to clients
