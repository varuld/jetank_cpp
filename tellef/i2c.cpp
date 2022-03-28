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

constexpr int addr = 0x60;

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

void forward(int file, double speed)
{

    __u8 forward_reg[8] = {0x0c, 0x0d, 0x10, 0x11, 0x28, 0x29, 0x3c, 0x3d};
    __u8 other_reg[4] = {0x2b, 0x31, 0x35, 0x37};
    if (speed < 0)
    {
        speed = 0;
    }
    else if (speed > 1.0)
    {
        speed = 1.0;
    }
    int s1 = (int) (255 * speed * 16);
    int s2 = (int) (255 * speed * 16);
    __u8 v1 = val1(s1);
    __u8 v2 = val2(s2);
    __s32 res;
    for (int i = 0; i < sizeof(other_reg); i++)
    {
        res = i2c_smbus_write_byte_data(file, other_reg[i], 0x10);
    }
    for (int i = 0; i < sizeof(forward_reg); i += 2)
    {
        res = i2c_smbus_write_byte_data(file, forward_reg[i], v1);
        res = i2c_smbus_write_byte_data(file, forward_reg[i+1], v2);
    }
}
void stop_forward(int file)
{
    __u8 forward_reg[8] = {0x0c, 0x0d, 0x10, 0x11, 0x28, 0x29, 0x3c, 0x3d};
    __s32 res;
    for (int i = 0; i < sizeof(forward_reg); i += 2)
    {
        res = i2c_smbus_write_byte_data(file, forward_reg[i], 0x00);
        res = i2c_smbus_write_byte_data(file, forward_reg[i+1], 0x00);
    }
}

void rightward(int file, double speed)
{

    __u8 rightward_reg[8] = {0x0c, 0x0d, 0x10, 0x11, 0x28, 0x29, 0x3c, 0x3d};
    __u8 other_reg[4] = {0x2b, 0x31, 0x35, 0x37};
    if (speed < 0)
    {
        speed = 0;
    }
    else if (speed > 1.0)
    {
        speed = 1.0;
    }
    int s1 = (int) (255 * speed * 16);
    int s2 = (int) (255 * speed * 16);
    __u8 v1 = val1(s1);
    __u8 v2 = val2(s2);
    __s32 res;
	for (int i = 0; i < sizeof(other_reg); i+=2)
    {
        res = i2c_smbus_write_byte_data(file, other_reg[i], 0xc0);
        res = i2c_smbus_write_byte_data(file, other_reg[i+1], 0x04);
    }
    for (int i = 0; i < sizeof(rightward_reg); i += 2)
    {
        res = i2c_smbus_write_byte_data(file, rightward_reg[i], v1);
        //res = i2c_smbus_write_byte_data(file, forward_reg[i+1], v2);
    }
}
void stop_rightward(int file)
{
    __u8 rightward_reg[8] = {0x0c, 0x0d, 0x10, 0x11, 0x28, 0x29, 0x3c, 0x3d};
	__s32 res;
	for (int i = 0; i < sizeof(rightward_reg); i += 2)
    {
        res = i2c_smbus_write_byte_data(file, rightward_reg[i], 0x00);
        res = i2c_smbus_write_byte_data(file, rightward_reg[i+1], 0x00);
    }
}

void leftward(int file, double speed)
{
	__u8 leftward_reg[8] = {0x08, 0x09, 0x10, 0x11, 0x28, 0x29, 0x3c, 0x3d};
    __u8 other_reg[2] = {0x2b, 0x2f}; //, 0x35, 0x37};
    if (speed < 0)
    {
        speed = 0;
    }
    else if (speed > 1.0)
    {
        speed = 1.0;
    }
	//int s1 = (int) (255 * speed * 16);
    //int s2 = (int) (255 * speed * 16);
    //__u8 v1 = val1(s1);
    //__u8 v2 = val2(s2);
    __s32 res;
	for (int i = 0; i < sizeof(other_reg); i++)
    {
		res = i2c_smbus_write_byte_data(file, other_reg[i], 0x10);
        //res = i2c_smbus_write_byte_data(file, other_reg[i], 0xc0);
        //res = i2c_smbus_write_byte_data(file, other_reg[i+1], 0x04);
    }
    for (int i = 0; i < sizeof(leftward_reg); i += 2)
    {
        res = i2c_smbus_write_byte_data(file, leftward_reg[i], 0xc0);
        res = i2c_smbus_write_byte_data(file, forward_reg[i+1], 0x04);
    }
}

void stop_leftward(int file)
{
	__u8 leftward_reg[8] = {0x08, 0x09, 0x10, 0x11, 0x28, 0x29, 0x3c, 0x3d};
	__s32 res;
	for (int i = 0; i < sizeof(rightward_reg); i += 2)
	{
		res = i2c_smbus_write_byte_data(file, rightward_reg[i], 0x00);
		res = i2c_smbus_write_byte_data(file, rightward_reg[i+1], 0x00);
	}
}

void backward(int file, double speed)
{
	__u8 backward_reg[8] = {0x08, 0x09, 0x14, 0x15, 0x28, 0x29, 0x3c, 0x3d};
    //__u8 other_reg[4] = {0x2b, 0x31, 0x35, 0x37};
    __u8 other_reg[4] = {0x2d, 0x2f, 0x33, 0x39};
    //__u8 other_reg[4] = {0x33, 0x39, 0x3c, 0x3d};
    if (speed > 0)
    {
        speed = 0;
    }
    else if (speed > -1.0)
    {
        speed = -1.0;
    }
    int s1 = -1 * ((int) (255 * speed * 16));
    int s2 = -1 * ((int) (255 * speed * 16));
    __u8 v1 = val1(s1);
    __u8 v2 = val2(s2);
    __s32 res;
    for (int i = 0; i < sizeof(other_reg); i++)
    {
        res = i2c_smbus_write_byte_data(file, other_reg[i], 0x10);
    }
    for (int i = 0; i < sizeof(backward_reg); i += 2)
    {
        res = i2c_smbus_write_byte_data(file, backward_reg[i], v1);
		if (backward_reg[i+1] == 0x29)
		{
			res = i2c_smbus_write_byte_data(file, backward_reg[i+1], 0x09);
		}
		else
		{
			res = i2c_smbus_write_byte_data(file, backward_reg[i+1], v2);
		}

    }
	/*
	res = i2c_smbus_write_byte_data(file, backward_reg[0], 0x60);
	res = i2c_smbus_write_byte_data(file, backward_reg[1], 0x10);
	res = i2c_smbus_write_byte_data(file, backward_reg[2], 0x60);
	res = i2c_smbus_write_byte_data(file, backward_reg[3], 0x06);
	res = i2c_smbus_write_byte_data(file, backward_reg[4], 0x60);
	res = i2c_smbus_write_byte_data(file, backward_reg[5], 0x09);
	res = i2c_smbus_write_byte_data(file, backward_reg[6], 0x60);
	res = i2c_smbus_write_byte_data(file, backward_reg[7], 0x06);
	*/
}



int main()
{
    int file;
    int adapter_nr = 1;
    char filename[20];

    snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);
    if (file < 0)
    {
        printf("Could not open %s.\n", filename);
        return -1;
    }



    if (ioctl(file, I2C_SLAVE, addr) < 0)
    {
        printf("IO Control failed.\n");
        return -1;
    }
    initialize(file);
    double speed = 0.4;
    char ch;
    bool running = false, speed_changed = false, turn_right = false;
    system("stty raw");
    while (1)
    {
        if (speed_changed)
        {
            printf("Current speed: %3.1f\n", speed);
        }
        ch = getchar();
        if (ch == 'w' && !running || speed_changed)
        {
            forward(file, speed);
			/*if (speed < 0)
			{
            	//forward(file, speed);
				backward(file, speed);
			}
			else
			{
            	forward(file, speed);
				//backward(file, speed);
			}
			*/
            running = true;
            speed_changed = false;
        }
        else if (ch == 'w' && !running || turn_right)
		{
			rightward(file, speed);
		}
        else if (ch == 's' && running)
        {
            stop_forward(file);
            running = false;
        }
		else if (ch == 's' && turn_right)
        {
            stop_rightward(file);
            turn_right = false;
        }
        else if (ch == 65)
        {
            speed += 0.1;
            speed_changed = true;
        }
        else if (ch == 66)
        {
            speed -= 0.1;
            speed_changed = true;
        }
		else if (ch == 67)
        {
            //speed += 0.1;
            //speed_changed = true;
			turn_right = true;
        }
/*		else if (ch == 68)
        {
            speed += 0.1;
            speed_changed = true;
        }*/
        else if (ch == 'q')
        {
            if (running)
            {
                stop_forward(file);
            }
            system("stty cooked");
            system("clear");
            return 0;
        }
    }
}
