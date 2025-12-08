// Server Policy
// Input:       Raw Frame Buffer Resource
// Function:    1. Split screen in 4
//              2. Assign S1 -> C1, S2 -> C2, S3 -> C3, S4 -> C4
//              3. Lock Assigment, E.g., C1 cannot access S2
// Definitions: S is the Screen represented by the frame buffer.
//                  This policy dictates that the screen is split into four (4) regions.
//              S1 is Screen 1 whose locaton is top left region.
//              C1 is Client 1.
// Frame Buffer:
//              -----------------------------------------
//              | R1 | R2 | R3 | R4 | R5 | R6 | R7 | R8 |
//              -----------------------------------------
//              Data stored in row major format.
//              Splitting horizontally is easy, e.g., S1 = R1..R4; S2 = R4..R8
//              If we want to split vertically, we must split each row.
//              This way we have:
//                  S1 = R1a + R2a + R3a ... 
//                  S2 = R1b + R2b + R3b ...
// Output:      Screen Region Descriptor

#include "kfb.h"            // kernel/include/kfb.h
#include "uart0.h"          // kernel/include/uart0.h
#include "fb_server.h"      // app/include/fb_server.h
#include "fb_surface.h"     // app/include/fb_surface.h
#include <stddef.h>

void fb_clear();

static int server_pid = 90001;
struct kernel_fb *fb;       // ptr to the frame buffer as the kernel sees it

int fb_server_create_surface(struct fb_surface *out)
{
    if (fb == NULL) {
        uart0_puts("Server: Could not provide surface to client.\n");
        return -1;
    };

    out->base = fb->fb_ptr;
    out->width = fb->width;
    out->height = fb->height;
    out->pitch = fb->pitch;
    out->isrgb = fb->isrgb;
    uart0_puts("Server: Successfully created fb_surface.\n");
    return 1;
}

int fb_server_reconfig(struct fb_surface *surface, unsigned int width, unsigned int height, unsigned int depth)
{
    uart0_puts("Server: Receieved reconfigure request from client, forwarding to kernel.\n");
    if (surface == NULL) {
        uart0_puts("Server: Bad surface provided.\n");
    }

    //adding clear function here for demo, remove later
    uart0_puts("Server: Clearing frame buffer before reconfiguring.\n");
    fb_clear();
    uart0_puts("Delay for 1s to prevent flickering.\n");
    wait_msec(1000000);
    
    int res;
    res = fb_kernel_reconfig(server_pid, width, height, depth);
    if (res == -1) {
        uart0_puts("Server: Bad configuration provided.\n");
        return -1;
    }

    surface->base = fb->fb_ptr;
    surface->width = fb->width;
    surface->height = fb->height;
    surface->pitch = fb->pitch;
    surface->isrgb = fb->isrgb;

    return 1;
}

void fb_clear() {
    uint32_t *p = (uint32_t*)fb->fb_ptr;
    size_t pixels = fb->width * fb->height;

    for (size_t i = 0; i < pixels; i++) {
        p[i] = 0;  // e.g., 0x00000000 for black
    }
}

int fb_server_init()
{
    //int server_pid;
    //server_pid = 90001;         // just some random number
    
    fb = fb_kernel_claim(server_pid);

    if (fb == NULL) {
        uart0_puts("Server: Failed to claim frame buffer.\n");
        uart0_puts("Server: Make sure the frame buffer has been initialized from the perspective of the kernel.\n");
        uart0_puts("Server: If initialized, then the buffer has already been claimed.\n");
        return -1;
    }
    
    uart0_puts("Server: Successfully claimed frame buffer from Kernel.\n");
    return 0;
}
