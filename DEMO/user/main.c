/***********************************************************************
*@Author: Dz_hui
*@Date: 2020-06-01 11:54:53
*@FilePath: \RT1052_test\DEMO\user\main.c
*@Drscription: 
***********************************************************************/

#include "board.h"
#include "rtthread.h"
#include "main.h"

/*******************************************************************
 * 变量
 *******************************************************************/
static uint32_t count=0;

static rt_thread_t led_thread=RT_NULL;
static rt_thread_t key_thread=RT_NULL;
static rt_thread_t mpu_thread=RT_NULL;

static rt_sem_t test_sem=RT_NULL;
/*******************************************************************
 * 函数声明
 *******************************************************************/
void led_thread_entry(void *parameter);
void key_thread_entry(void *parameter);
void mpu_thread_entry(void *parameter);
/***********************************************************************
*@Function: int main(void)
*@Input: 
*@Return: none
*@Author: Dz_hui
*@Date: 2020-06-14 17:07:50
*@Drscription: MAIN函数
***********************************************************************/
int main(void)
{
	uint8_t open_time=0;
	uint8_t a_buff[6]={0};
	uint8_t g_buff[6]={0};
	uint16_t accel1[3]={0};
	uint16_t gryo1[3]={0};

	#if 0
	PLI2C_write_data(EEPROM_LPI2C_PORT,EEPROM_WRITE_ADDR,0x01,0x00);
	#endif



	test_sem=rt_sem_create("test_sem",
							1,
							RT_IPC_FLAG_FIFO);
							
	led_thread=rt_thread_create("led",
								led_thread_entry,
								RT_NULL,
								512,
								3,
								20);
	if(led_thread !=RT_NULL)
	{
		rt_thread_startup(led_thread);
	}
	else
	{
		return -1;
	}

	key_thread=rt_thread_create("key",
								key_thread_entry,
								RT_NULL,
								512,
								2,
								20);
	if(led_thread !=RT_NULL)
	{
		rt_thread_startup(key_thread);
	}
	else
	{
		return -1;
	}
	
	mpu_thread=rt_thread_create("mpu",
								mpu_thread_entry,
								RT_NULL,
								512,
								3,
								20);
	if(mpu_thread !=RT_NULL)
	{
		rt_thread_startup(mpu_thread);
	}
	else
	{
		return -1;
	}
	
	#if 1
	LPI2C_read_data(EEPROM_LPI2C_PORT,EEPROM_READ_ADDR,0x01,&open_time);
	open_time++;
	PLI2C_write_data(EEPROM_LPI2C_PORT,EEPROM_WRITE_ADDR,0x01,open_time);
	printf("TIMES:=%d\n\n\n",open_time);
	printf("LAST TIME MPU6050_VAL:\n");
	LPI2C_read_buff(EEPROM_LPI2C_PORT,EEPROM_WRITE_ADDR,EEPROM_WRITEADDR,a_buff,6);
	LPI2C_read_buff(EEPROM_LPI2C_PORT,EEPROM_WRITE_ADDR,0x08,g_buff,6);
	
	accel1[0]=(a_buff[0]<<8)|a_buff[1];
	accel1[1]=(a_buff[2]<<8)|a_buff[3];
	accel1[2]=(a_buff[4]<<8)|a_buff[5];
	gryo1[0]=(g_buff[0]<<8)|g_buff[1];
	gryo1[1]=(g_buff[2]<<8)|g_buff[3];
	gryo1[2]=(g_buff[4]<<8)|g_buff[5];

	printf("ACCEL:x=%d  y=%d  z=%d\n",accel1[0],accel1[1],accel1[2]);
	printf("GRYO:x=%d  y=%d  z=%d\n",gryo1[0],gryo1[1],gryo1[2]);
#endif

}
/*********************************线程**********************************/
void led_thread_entry(void *parameter)
{
	while(1)
	{
		if(count%3==0)
		{
			LED_TOGGLE();
			rt_sem_release(test_sem);
			rt_thread_delay(100);
		}
		
		else if(count%3==1)
		{
			LED_TOGGLE();
			rt_sem_release(test_sem);
			rt_thread_delay(200);
		}

		else if(count%3==2)
		{
			LED_ON();
			rt_sem_release(test_sem);
		}
		
	}
}

void key_thread_entry(void *parameter)
{
	rt_err_t uwret=RT_EOK;
	static uint8_t flg=1;
	while(1)
	{
		uwret=rt_sem_take(test_sem,RT_WAITING_FOREVER);
		if(uwret ==RT_EOK)
		{
			if(KEY_READ()==KEY_ON &&flg )
			{
				flg=0;
				count++;
				printf("led更改为：模式%d\n",(count%3)+1);
			}
			else if (KEY_READ()==KEY_OFF)
			{
				flg=1;
			}
			
		}

		rt_thread_delay(50);
	}
}

void mpu_thread_entry(void *parameter)
{
	uint16_t accel[3];
	uint16_t gryo[3];
	static uint8_t flg=1;
	uint8_t accel_buff[6];
	uint8_t gryo_buff[6];

	
	while(1)
	{
		MPU6050_read_accel(accel);
		MPU6050_read_gryo(gryo);

		if(MODE_KEY_READ()==KEY_ON && flg)
		{
			flg=0;
			accel_buff[0]=accel[0]>>8;
			accel_buff[1]=accel[0]|0x08;
			accel_buff[2]=accel[1]>>8;
			accel_buff[3]=accel[1]|0x08;
			accel_buff[4]=accel[2]>>8;
			accel_buff[5]=accel[2]|0x08;
			gryo_buff[0]=gryo[0]>>8;
			gryo_buff[1]=gryo[0]|0x08;
			gryo_buff[2]=gryo[1]>>8;
			gryo_buff[3]=gryo[1]|0x08;
			gryo_buff[4]=gryo[2]>>8;
			gryo_buff[5]=gryo[2]|0x08;
			LPI2C_write_buff(EEPROM_LPI2C_PORT,EEPROM_WRITE_ADDR,EEPROM_WRITEADDR,accel_buff,6);
			LPI2C_write_buff(EEPROM_LPI2C_PORT,EEPROM_WRITE_ADDR,0x08,gryo_buff,6);
			
			

		}

		else if(MODE_KEY_READ()==KEY_OFF)
		{
			flg=1;
		}
		rt_thread_delay(50);
		
	}
	

}
/****************************END OF FILE**********************/
