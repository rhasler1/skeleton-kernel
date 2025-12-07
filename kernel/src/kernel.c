#include "uart0.h"
#include "mbox.h"
#include <stdint.h>

#include "fb_client.h"
#include "fb_server.h"
#include "kfb.h"

void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3)
{
    int res;

    init_uart0();
    uart0_puts("Kernel Main: UART0 initialized\n");
    
    uart0_puts("Kernel Main: Attempting to initialize frame buffer...\n");
    res = fb_kernel_init();
    if (res == -1) {
        uart0_puts("Kernal Main: Failed.\n");
    }
    else {
        uart0_puts("Kernal Main: Succeeded.\n");
    } 

    res = fb_server_init(); // fb_server_init()
    client_demo();


    while (1) {
        uart0_putc(uart0_getc());
    }
}
