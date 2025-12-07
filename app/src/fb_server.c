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


#include "kfb.h"            // see kernel/include/kfb.h
#include "uart0.h"
#include "fb_server.h"
#include "fb_surface.h"
#include <stddef.h>

struct kernel_fb *fb;      // ptr to the frame buffer as the kernel sees it

void get_fb_surface(struct fb_surface *out)
{
    if (fb == NULL) {
        uart0_puts("Server: Could not provide surface to client.\n");
    };

    out->base = fb->fb_ptr;
    out->width = fb->width;
    out->height = fb->height;
}

int init_fb_server()
{
    int server_pid;
    server_pid = 90001;         // just some random number
    
    fb = kernel_fb_claim(server_pid);

    if (fb == NULL) {
        uart0_puts("Server: Failed to claim frame buffer.\n");
        uart0_puts("Server: Make sure the frame buffer has been initialized from the perspective of the kernel.\n");
        uart0_puts("Server: If initialized, then the buffer has already been claimed.\n");
        return -1;
    }
    
    uart0_puts("Server: Successfully claimed frame buffer.\n");
    return 0;
}
