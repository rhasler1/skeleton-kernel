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
int                 fb_kernel_reconfig  (
        int requester_pid,
        unsigned int width, 
        unsigned int height, 
        unsigned int depth
        );

//this is static, called by init and reconfig
//int                 fb_kernel_set       (unsigned int width, unsigned int height, unsigned int depth);
struct kernel_fb*   fb_kernel_claim     (int requester_pid);
