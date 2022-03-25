#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <stdio.h>

std::string readI2C(int file_i2c, unsigned char * buffer, int length)
{
    std::string res;
    if (read(file_i2c, buffer, length) != length)
    {
        printf("Failed to read from the i2c bus.\n");
    }
    else
    {
        printf("Data read: %s\n", buffer);
    }
    return res;
}

int main()
{
    char * id;
    id = "/dev/i2c-1";
    unsigned char buffer[60];
    int length = 2;
    int file_i2c = open(id, O_RDWR);

    if (file_i2c < 0)
    {
        printf("Failed to open the i2c bus\n");
        return 1;
    }

    int addr = 0x60;
    if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
    {
        printf("Failed to acquire bus acces and/or talk to slave.\n");
        return 1;
    }

    std::string i2c_data = readI2C(file_i2c, buffer, length);

    printf("i2c data: %s\n", i2c_data);

    return 0;
}