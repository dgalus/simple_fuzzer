#ifndef BYTEARRAY_H
#define BYTEARRAY_H

struct ByteArray
{
    char* data;
    unsigned long length;
    ByteArray(unsigned long length, char* data)
        : data(data), length(length) {}
};

#endif // BYTEARRAY_H
