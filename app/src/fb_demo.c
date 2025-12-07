// Demo frame buffer policies

int demo_split()
{
    fb_init();                                      // calls kernel frame buffer allocator
    fb_split();                                     // policy to split frame buffer horizontally
    
    struct fb_region client1 = fb_create_region();  // creates uninitialized regions
    struct fb_region client2 = fb_create_region();  // creates uninitialized regions

    int status1 = fb_init_client(&client1);         // inits if there is an available region, retval 0=success, -1=failure
    int status2 = fb_init_client(&client2);

    fb_write(&client1, &data);
    fb_write(&client2, &data);

    //wait a bit
    fb_draw();
}
