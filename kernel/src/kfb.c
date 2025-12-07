#include "kfb.h"
#include "uart0.h"
#include "mmio.h"
#include "mbox.h"
#include "delay.h"
#include <stddef.h>

// defined in kfb.h
struct kernel_fb kfb;

struct kernel_fb* fb_kernel_claim(int requester_pid)
{
    if (!kfb.available) {
        uart0_puts("Kernel FB: Frame buffer is not currently available.\n");
        return NULL;
    }

    kfb.available=0;
    kfb.owner_pid=requester_pid;
    uart0_puts("Kernel FB: Frame buffer claimed.\n");
    return &kfb;
}

int fb_kernel_init()
{
    wait_msec(100000);

    mbox[0] = 35*4;
    mbox[1] = MBOX_REQUEST;

    mbox[2] = 0x48003;
    mbox[3] = 8;
    mbox[4] = 8;
    //width
    mbox[5] = 1024;
    //height
    mbox[6] = 768;

    mbox[7] = 0x48004;
    mbox[8] = 8;
    mbox[9] = 8;
    //virtual width
    mbox[10] = 1024;
    //virtual height
    mbox[11] = 768;

    mbox[12] = 0x48009;
    mbox[13] = 8;
    mbox[14] = 8;
    //virtual x offset
    mbox[15] = 0;
    //virtual y offset
    mbox[16] = 0;

    mbox[17] = 0x48005;
    mbox[18] = 4;
    mbox[19] = 4;
    //depth
    mbox[20] = 32;

    //setting pixel order
    mbox[21] = 0x48006;
    mbox[22] = 4;
    mbox[23] = 4;
    mbox[24] = 1;

    mbox[25] = 0x40001;
    mbox[26] = 8;
    mbox[27] = 8;
    //frame buffer pointer
    mbox[28] = 4096;
    //frame buffer size
    mbox[29] = 0;

    mbox[30] = 0x40008;
    mbox[31] = 4;
    mbox[32] = 4;
    //frame buffer pitch
    mbox[33] = 0;

    mbox[34] = MBOX_TAG_LAST;

    if (mbox_call(MBOX_CH_PROP) && mbox[20]==32 && mbox[28]!=0) {
        mbox[28]&=0x3FFFFFFF;       //convert GPU address to ARM address
        
        kfb.width=mbox[5];          //get actual physical width
        kfb.height=mbox[6];         //get actual physical height
        kfb.pitch=mbox[33];         //get number of bytes per line
        kfb.isrgb=mbox[24];         //get the actual channel order
        kfb.fb_ptr=(void*)((unsigned long)mbox[28]);
        kfb.available=1;

        uart0_puts("Kernel FB: Frame buffer initialized.\n");
        uart0_puts("Kernel FB: Screen resolution set to default of 1024x768x32.\n");

        return 0;
    }
    else {
        uart0_puts("Kernel FB: Frame buffer could not be initialized.\n");
        uart0_puts("Kernel FB: Unable to set screen resolution to 1024x768x32.\n");
        
        return -1;
    }
}
