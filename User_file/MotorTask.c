#include "freertos.h"
#include "Motortask.h"
#include "cmsis_os.h"
#include "feeder.h"

#define PI 3.141593f

float target_vel = 1.5f;

FeederInstance_s *feeder;

FeederInitConfig_s FeederInitConfig = {
	.motor_config = {
    .can_config = {
            .can_number = 1,
            .tx_id = 0x02,//01
            .rx_id = 0x12,//11
    },
    .parameters = {
            .pos_max = 3.141593f,
            .vel_max = 30.0f,//30
            .tor_max = 10.0f,//10
            .kp_max = 100.0f,
            .kd_max = 10.0f,
            .kp_int = 0.0f,
            .kd_int = 0.0f,
    },
    .control_mode = DM_POSITION,
        .topic_name = "feeder",
        .type = J4310,
        .velocity_pid_config = {
            .kp = 0.6f,
            .ki = 0.07f,
            .kd = 1.5f,
            .i_max = 2.0f,
            .out_max = 3.0f,
    },
    .angle_pid_config = {
            .kp = 37.0f, 
            .ki = 0.0f,
            .kd = 7.0f,
            .i_max = 3.0f,
            .out_max = 8.0f,
            .angle_max = 2*PI,
    },
  }
};

FrictionInstance_s *friction;
FrictionInitConfig_s FrictionInitConfig = {
	.target_speed = 2000.0f,
	.motor_config = {
		.type = M3508,
		.reduction_ratio = 1.0f,
		.control_mode = DJI_VELOCITY,
    .can_config = {
            .can_number = 1,
            .tx_id = 0x200,
            .rx_id = 0x206,
    },
    .velocity_pid_config = {
			.kp = 0.0f,
      .ki = 0.0f,
      .kd = 0.0f,
      .i_max = 2000.0f,
      .out_max = 16384.0f,
    },
  }
};

void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
//	friction = Friction_Register(&FrictionInitConfig);
//  friction->power = POWER_ON;
	 feeder = Feeder_Register(&FeederInitConfig);
   feeder->power = POWER_ON;
  /* Infinite loop */
  for(;;)
  {
		Feeder_Control(feeder);
//    Friction_Wheel_Normal(friction);
//		Motor_Dji_Transmit(friction->motor);
    osDelay(1);
  }
  /* USER CODE END StartTask02 */
}
