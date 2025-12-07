#pragma once

struct kernel_fb {
    int available;
    int owner_pid;

    unsigned char* fb_ptr;
    unsigned int width;
    unsigned int height;
    unsigned int pitch;
    unsigned int isrgb;
};

int kernel_fb_init();
struct kernel_fb* kernel_fb_claim(int requester_pid);
