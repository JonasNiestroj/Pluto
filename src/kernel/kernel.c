void kernel_main()
{
    unsigned short c = (unsigned short)'h' | (0x0F) << 8;
    *(unsigned short *)(0xb8000 + 80) = c;
    return;
}