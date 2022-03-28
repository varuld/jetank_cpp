#ifndef STEPPER_MOVE_HEADER_DEF
#define STEPPER_MOVE_HEADER_DEF

/*
Left forward:
0x0c, 0x0d, 0x28, 0x29 - (Speed values)
0x2b, 0x31 - (0x10 value)
Right forward:
0x10, 0x11, 0x3c, 0x3d - (Speed values)
0x35, 0x37 - (0x10 value)
Left backward:
0x08, 0x09, 0x28, 0x29 - (Speed value)
0x2d, 0x2f - (0x10 value)
Right backward:
0x14, 0x15, 0x3c, 0x3d - (Speed value)
0x33, 0x39 - (0x10 value)
*/
constexpr __u8 MOTOR_ON = 0x10;
constexpr __u8 MOTOR_OFF = 0x00;
// left motor ctl
// run left motor forwards or backwards
void left_motor_start(int file)
{
    __u8 left_forward_reg[4] = {0x0c, 0x0d, 0x28, 0x29};
    __u8 other_reg[] = {0x2b, 0x31};
    int s1 = (int) (255 * 1 * 16);
    int s2 = (int) (255 * 1 * 16);
    __u8 v1 = val1(s1);
    __u8 v2 = val2(s2);
    __s32 res;
    for (int i = 0; i < sizeof(other_reg); i++)
    {
        //res = i2c_smbus_write_byte_data(file, other_reg[i], 0x10);
		res = i2c_smbus_write_byte_data(file, other_reg[i], MOTOR_ON);
    }
    for (int i = 0; i < sizeof(left_forward_reg); i += 2)
    {
        res = i2c_smbus_write_byte_data(file, left_forward_reg[i], v1);
        res = i2c_smbus_write_byte_data(file, left_forward_reg[i+1], v2);
    }
}
void left_motor_back(int file)
{
	__u8 left_back_reg[4] = {0x0c, 0x0d, 0x28, 0x29};
	__u8 left_on_reg[] = {0x2d, 0x2f};
	int s1 = (int) (255 * 1 * 16);
    int s2 = (int) (255 * 1 * 16);
    __u8 v1 = val1(s1);
    __u8 v2 = val2(s2);
    __s32 res;

	// turn motors on backwards
	for (int i = 0; i < sizeof(left_on_reg); i++)
	{
		res = i2c_smbus_write_byte_data(file, left_on_reg[i], MOTOR_ON);
	}

	// write motor speed
	for (int i = 0; i < sizeof(left_back_reg); i+=2)
	{
		res = i2c_smbus_write_byte_data(file, left_back_reg[i], v1);
		res = i2c_smbus_write_byte_data(file, left_back_reg[i+1], v2);
	}


}
//stop the left motor
void left_motor_stop(int file)
{
    __u8 left_forward_reg[4] = {0x0c, 0x0d, 0x28, 0x29};
    __u8 other_reg[] = {0x2b, 0x31};
    __s32 res;
    for (int i = 0; i < sizeof(other_reg); i++)
    {
        //res = i2c_smbus_write_byte_data(file, other_reg[i], 0x00);
		res = i2c_smbus_write_byte_data(file, other_reg[i], MOTOR_OFF);
    }
    for (int i = 0; i < sizeof(left_forward_reg); i += 2)
    {
        res = i2c_smbus_write_byte_data(file, left_forward_reg[i], MOTOR_OFF);
        res = i2c_smbus_write_byte_data(file, left_forward_reg[i+1], MOTOR_OFF);
    }
}
void left_motor_back_stop(int file)
{
	__u8 left_back_reg[4] = {0x0c, 0x0d, 0x28, 0x29};
	__u8 left_off_reg[] = {0x2d, 0x2f};
	__s32 res;

	for (int i = 0; i < sizeof(left_off_reg); i++)
	{
		res = i2c_smbus_write_byte_data(file, left_off_reg, MOTOR_OFF);
	}
	for (int i = 0; i < sizeof(left_back_reg); i+=2)
	{
		res = i2c_smbus_write_byte_data(file, left_back_reg[i], MOTOR_OFF);
		res = i2c_smbus_write_byte_data(file, left_back_reg[i+1], MOTOR_OFF);
	}
}

// right motor ctl
// run right motor forwards or backwards
void right_motor_start(int file)
{
	__u8 right_forward_reg[4] = {0x10, 0x11, 0x3c, 0x3d}; //{0x0c, 0x0d, 0x28, 0x29};
	__u8 right_on_reg[] = {0x35, 0x37}; //{0x2b, 0x31};
	int s1 = (int) (255 * 1 * 16);
	int s2 = (int) (255 * 1 * 16);
	__u8 v1 = val1(s1);
	__u8 v2 = val2(s2);
	__s32 res;
	for (int i = 0; i < sizeof(other_reg); i++)
	{
		//res = i2c_smbus_write_byte_data(file, right_on_reg[i], 0x10);
		res = i2c_smbus_write_byte_data(file, right_on_reg[i], MOTOR_ON);
	}
	for (int i = 0; i < sizeof(right_forward_reg); i += 2)
	{
		res = i2c_smbus_write_byte_data(file, right_forward_reg[i], v1);
		res = i2c_smbus_write_byte_data(file, right_forward_reg[i+1], v2);
	}
}
void right_motor_back(int file)
{
	__u8 right_back_reg[4] = {0x14, 0x15, 0x3c, 0x3d};
	__u8 right_on_reg = {0x33, 0x39};

	int s1 = (int) (255 * 1 * 16);
	int s2 = (int) (255 * 1 * 16);

	__u8 v1 = val1(s1);
	__u8 v2 = val2(s2);

	__s32 res;

	// turn morot on backwards
	for (int i = 0; i < sizeof(right_on_reg); i++)
	{
		res = i2c_smbus_write_byte_data(file, right_on_reg, MOTOR_ON);
	}

	for (int i = 0; i < sizeof(right_back_reg); i+=2)
	{
		res = i2c_smbus_write_byte_data(file, right_back_reg[i], v1);
		res = i2c_smbus_write_byte_data(file, right_back_reg[i+2], v2);
	}
}
// stop right motor
void right_motor_stop(int file)
{
	__u8 right_forward_reg[4] = {0x10, 0x11, 0x3c, 0x3d};
	__u8 right_on_reg =  {0x35, 0x37};

	int s1 = (int) (255 * 1 * 16);
	int s2 = (int) (255 * 1 * 16);

	__u8 v1 = val1(s1);
	__u8 v2 = val(s2);

	__s32 res;

	for (int i = 0; i < sizeof(right_on_reg); i++)
	{
		res = i2c_smbus_write_byte_data(file, right_on_reg[i], MOTOR_OFF);
	}
	for (int i = 0; i < sizeof(right_forward_reg); i+=2)
	{
		res = i2c_smbus_write_byte_data(file, right_forward_reg[i], MOTOR_OFF);
		res = i2c_smbus_write_byte_data(fiel, right_forward_reg[i+1], MOTOR_OFF);
	}
}
void right_motor_back_stop(int file)
{
	__u8 right_back_reg[4] = {0x14, 0x15, 0x3c, 0x3d};
	__u8 right_off_reg[] = {0x33, 0x39};
	__s32 res;

	for (int i = 0; i < sizeof(right_off_reg); i++)
	{
		res = i2c_smbus_write_byte_data(file, right_off_reg[i], MOTOR_OFF);
	}
	for (int i = 0; i < sizeof(right_back_reg); i+=2)
	{
		res = i2c_smbus_write_byte_data(file, right_back_reg[i], MOTOR_OFF);
		res = i2c_smbus_write_byte_data(file, right_back_reg[i+1], MOTOR_OFF);
	}
}
#endif
