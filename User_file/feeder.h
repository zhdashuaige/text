#ifndef __FEEDER_H__
#define __FEEDER_H__
#include "dev_motor_dm.h"
#include "dev_motor_dji.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

extern float out_speed;
extern float move;
extern float out_position;
extern float target_position;

typedef enum
{
    POWER_OFF = 0,
    POWER_ON = 1,
}POWER_STATE_e;

typedef enum
{
    CLAW_JAW_NONE = 0,     
    CLAW_JAW_FORWARD = 1,  
    CLAW_JAW_BACKWARD = 2,
}CLAW_JAW_STATE_e;

typedef struct
{
    POWER_STATE_e power;
    DmMotorInstance_s *motor;
} FeederInstance_s;

typedef struct
{
		float target_speed;
    DmMotorInitConfig_s motor_config;
} FeederInitConfig_s;

typedef struct
{
		float target_speed;
    POWER_STATE_e power;
    DjiMotorInstance_s *motor;
	  
} FrictionInstance_s;

typedef struct
{
	 float target_speed;
    DjiMotorInitConfig_s motor_config;
} FrictionInitConfig_s;

FeederInstance_s *Feeder_Register(FeederInitConfig_s *config);
FrictionInstance_s *Friction_Register(FrictionInitConfig_s *config);
void Friction_Wheel_Normal(FrictionInstance_s *friction);
void Feeder_Control(FeederInstance_s* feeder);
#endif
