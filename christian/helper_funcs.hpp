#ifndef HELPER_FUNCTIONS_HEADER_DEF
#define HELPER_FUNCTIONS_HEADER_DEF
__u8 val1(int s)
{
    return s & 0xff;
}

__u8 val2(int s)
{
    return s >> 8;
}
#endif
