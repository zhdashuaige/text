#include "feeder.h"

float out_speed = 0.0f;
float out_position = 0.0f;
float move = 0.0f;
float target_position = 0.0f;
FeederInstance_s *Feeder_Register(FeederInitConfig_s *config)
{  
    FeederInstance_s *feeder = (FeederInstance_s *)pvPortMalloc(sizeof(FeederInstance_s));   
    memset(feeder, 0, sizeof(FeederInstance_s));
    feeder->motor = Motor_DM_Register(&config->motor_config);  
    feeder->power = POWER_OFF;
    return feeder;
}

FrictionInstance_s *Friction_Register(FrictionInitConfig_s *config)
{  
    FrictionInstance_s *friction = (FrictionInstance_s *)pvPortMalloc(sizeof(FrictionInstance_s));   
    memset(friction, 0, sizeof(FrictionInstance_s));
    friction->motor = Motor_Dji_Register(&config->motor_config);  
    friction->power = POWER_OFF;
		friction->target_speed = config->target_speed;
    return friction;
}
void Feeder_Control(FeederInstance_s* feeder)
{
    if(feeder->power==POWER_ON)
    {
        if(feeder->motor->motor_state!=DM_ENABLE)
        {
            Motor_Dm_Cmd(feeder->motor,DM_CMD_MOTOR_ENABLE);
						float current_pos = feeder->motor->message.out_position;
						feeder->motor->target_position = current_pos;
					  target_position = current_pos;
        }
				else
				{
						float new_target = feeder->motor->target_position;
					
						if(move==1)
						{
								new_target -= 3.141593f/2.0f;
								move = 0;
						}
						 while(new_target < -3.141593f)           
						{
								new_target += 3.141593f * 2.0f;            
						}           
						while(new_target >= 3.141593f)            
						{                
								new_target -= 3.141593f * 2.0f;           
						}
						
            feeder->motor->target_position = new_target;
						target_position = new_target;	
						
						Motor_Dm_Control(feeder->motor,feeder->motor->target_position);
						Motor_Dm_Mit_Control(feeder->motor, 0.0f, 0.0f, feeder->motor->output);
				}
    }
    else
    {
        if (feeder->motor->motor_state == DM_ENABLE)
        {
            Motor_Dm_Cmd(feeder->motor, DM_CMD_MOTOR_DISABLE);
        }
        feeder->motor->target_velocity = 0.0f;
    }
		out_speed = feeder->motor->message.out_velocity;
		out_position = feeder->motor->message.out_position;
		Motor_Dm_Transmit(feeder->motor);
}

 void Friction_Wheel_Normal(FrictionInstance_s *friction)
{
		friction->motor->output=
    Pid_Calculate(friction->motor->velocity_pid,
    friction->target_speed,friction->motor->message.out_velocity);
//	  out_speed = friction->motor->message.out_velocity;
}