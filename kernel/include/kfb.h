#pragma once

struct kernel_fb {
    int             available;
    int             owner_pid;

    unsigned char*  fb_ptr;
    unsigned int    width;
    unsigned int    height;
    unsigned int    pitch;
    unsigned int    isrgb;
};

int                 fb_kernel_init      ();
struct kernel_fb*   fb_kernel_claim     (int requester_pid);
