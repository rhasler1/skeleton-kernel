#pragma once

#include "fb_surface.h"

int     fb_server_init              ();                         // attempts to claim fb from kernel
int     fb_server_create_surface    (struct fb_surface *out);   // passes memory regions to clients
