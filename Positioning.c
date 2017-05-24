/*
 * Positioning.c
 *
 * Created: 5/17/2017 8:31:50 AM
 *  Author: guswe541
 */ 


#include <avr/io.h>
#include <stdbool.h>
#include <string.h>
#include "Positioning.h"
#include "SearchAndFind.h"
#include "global_variables.h"

#define up 8
#define down 2
#define left 4
#define right 6

//position to the right of the robot x coordinates
int8_t right_x_pos()
{
	int8_t right_x_pos = robot_pos.x_tile;

	if(Get_robot_direction() == up)
	{
		right_x_pos += 1;
	}
	else if(Get_robot_direction() == down)
	{
		right_x_pos -= 1;
	}

	return right_x_pos;
}

//position to the right of the robot y coordinates
int8_t right_y_pos()
{
	int8_t right_y_pos = robot_pos.y_tile;

	if(Get_robot_direction() == left)
	{
		right_y_pos -= 1;
	}
	else if(Get_robot_direction() == right)
	{
		right_y_pos += 1;
	}
	return right_y_pos;
}

//position to the left of the robot x coordinates
int8_t left_x_pos()
{
	int8_t left_x_pos = robot_pos.x_tile;
	if(Get_robot_direction() == up)
	{
		left_x_pos -=1;
	}
	else if(Get_robot_direction() == down)
	{
		left_x_pos +=1;
	}
	return left_x_pos;
}

//position to the left of the robot y coordinates
int8_t left_y_pos()
{
	int8_t left_y_pos = robot_pos.y_tile;
	if(Get_robot_direction() == left)
	{
		left_y_pos +=1;
	}
	else if(Get_robot_direction() == right)
	{
		left_y_pos -=1;
	}
	return left_y_pos;
}

int8_t back_x_pos()
{
	int8_t back_x_pos = robot_pos.x_tile;

	if(Get_robot_direction() == left)
	{
		back_x_pos +=1;
	}
	else if(Get_robot_direction() == right)
	{
		back_x_pos -=1;
	}
	return back_x_pos;
}

int8_t back_y_pos()
{
	int8_t back_y_pos = robot_pos.y_tile;
	if(Get_robot_direction() == up)
	{
		back_y_pos +=1;
	}
	else if(Get_robot_direction() == down)
	{
		back_y_pos -=1;
	}
	return back_y_pos;
}

uint8_t y_positions_forward(uint8_t next_direction, uint8_t steps_forward)
{
	uint8_t next_ypos = robot_pos.y_tile;
	if(next_direction == up)
	{
		next_ypos = robot_pos.y_tile - steps_forward;
	}
	else if(next_direction == down)
	{
		next_ypos = robot_pos.y_tile + steps_forward;
	}
	return next_ypos;
}

uint8_t x_positions_forward(uint8_t next_direction, uint8_t steps_forward)
{
	int8_t next_xpos = robot_pos.x_tile;
	if(next_direction == right)
	{
		next_xpos = robot_pos.x_tile + steps_forward;
	}
	else if(next_direction == left)
	{
		next_xpos = robot_pos.x_tile - steps_forward;
	}
	return next_xpos;
}



