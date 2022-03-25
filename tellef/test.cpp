#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <iostream>
#include <string>

std::string readI2C(int file_i2c, unsigned char * buffer, int length)
{
    std::string res;
    if (read(file_i2c, buffer, length) != length)
    {
        std::cout << "Failed to read from the i2c bus.\n" << std::endl;
    }
    else
    {
        std::cout << "Data read: \n" << buffer << std::endl;
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
        std::cout << "Failed to open the i2c bus";
        return 1;
    }

    int addr = 0x60;
    if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
    {
        std::cout << "Failed to acquire bus acces and/or talk to slave.";
        return 1;
    }

    std::string i2c_data = readI2C(file_i2c, buffer, length);

    std::cout << i2c_data << std::endl;

    return 0;
}