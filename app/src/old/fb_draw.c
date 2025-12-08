
//TODO: determine what data a client would need to pass to this function
//1. fb_surface
//2. data to draw
/**
 * Show a picture
 */
void lfb_showpicture()
{
    int x,y;
    unsigned char *ptr=lfb;
    char *data=homer_data, pixel[4];

    ptr += (height-homer_height)/2*pitch + (width-homer_width)*2;
    for(y=0;y<homer_height;y++) {
        for(x=0;x<homer_width;x++) {
            HEADER_PIXEL(data, pixel);
            // the image is in RGB. So if we have an RGB framebuffer, we can copy the pixels
            // directly, but for BGR we must swap R (pixel[0]) and B (pixel[2]) channels.
            *((unsigned int*)ptr)=isrgb ? *((unsigned int *)&pixel) : (unsigned int)(pixel[0]<<16 | pixel[1]<<8 | pixel[2]);
            ptr+=4;
        }
        ptr+=pitch-homer_width*4;
    }
}
