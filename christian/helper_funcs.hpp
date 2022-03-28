#ifndef HELPER_FUNCTIONS_HEADER_DEF
#define HELPER_FUNCTIONS_HEADER_DEF
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
//#include <i2c/smbus.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <chrono>
#include <thread>
#include <cstdlib>
__s32 i2c_smbus_access(int file, char read_write, __u8 command,
		   int size, union i2c_smbus_data *data)
{
	struct i2c_smbus_ioctl_data args;
	__s32 err;

	args.read_write = read_write;
	args.command = command;
	args.size = size;
	args.data = data;
	err = ioctl(file, I2C_SMBUS, &args);
	if (err == -1)
		err = -errno;
	return err;
}

__s32 i2c_smbus_read_byte_data(int file, __u8 command)
{
	union i2c_smbus_data data;
	int err;

	err = i2c_smbus_access(file, I2C_SMBUS_READ, command,
				   I2C_SMBUS_BYTE_DATA, &data);
	if (err < 0)
		return err;

	return 0x0FF & data.byte;
}

__s32 i2c_smbus_write_byte_data(int file, __u8 command, __u8 value)
{
	union i2c_smbus_data data;
	data.byte = value;
	return i2c_smbus_access(file, I2C_SMBUS_WRITE, command,
				I2C_SMBUS_BYTE_DATA, &data);
}

void initialize(int file)
{
	__u8 initial_val[70] = {0x01, 0x04, 0xe2, 0xe4, 0xe8, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
							0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	__u8 last_val[6] = {0x00, 0x00, 0x00, 0x00, 0x03, 0x00};
	__s32 res;
	__u8 reg = 0;
	for (int i = 0; i < sizeof(initial_val); i++)
	{
		res = i2c_smbus_write_byte_data(file, reg, initial_val[i]);
		reg++;
	}
	reg = 0xfa;
	for (int i = 0; i < 6; i++)
	{
		res = i2c_smbus_write_byte_data(file, reg, last_val[i]);
		reg++;
	}
	printf("Engines initialized\n");
	//fflush(stdout);
}
__u8 val1(int s)
{
	return s & 0xff;
}

__u8 val2(int s)
{
	return s >> 8;
}
#endif
