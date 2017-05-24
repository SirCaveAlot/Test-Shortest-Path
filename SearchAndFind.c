/*
 * SearchAndFind.c
 *
 * Created: 5/12/2017 2:53:12 PM
 *  Author: marwa079
 */ 

#define up 8
#define right 6
#define down 2
#define left 4

#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "SearchAndFind.h"
#include "Positioning.h"
#include "global_variables.h"
#include "Movement.h"
#include "Main_array.h"


//As long as we don't find a wall ahead or a clear at the right hand side, the robot keeps moving forward
//BUT! if we first off, find a clear way to travel to the right, we turn right and if we find a wall we
//clearly have to turn left

int nearest_path_array[29][29]; //contains the coordinates with the nearest path

void nearest_path_to_array() //takes the coordinates from gurras_array and puts it in nearest_path_array[29][29]
{
	int m = 0;
	while(main_node_array[m][2] != 0)
	{
		nearest_path_array[main_node_array[m][0]][main_node_array[m][1]] = 3;
		m++;
	}
	nearest_path_array[main_node_array[m][0]][main_node_array[m][1]] = 3;
	
}

bool detect_path(int next_yposition, int next_xposition, int value) //detects if coordinate is given path coordinate
{
/*	nearest_path_to_array();*/
	if(nearest_path_array[next_yposition][next_xposition] == value)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void set_coordinate_in_NP_array(int y, int x, int value) //sets coordinate in nearest_path_array to value
{
	nearest_path_array[y][x] = value;
}



void drive_nearest_path() //follows given path from gurras_array
{
	uint8_t steps = 0;
	while(detect_path(y_positions_forward(Get_robot_direction(), steps + 1), x_positions_forward(Get_robot_direction(), steps + 1), 3))
	{
		if(detect_path(y_positions_forward(Get_robot_direction(), steps), x_positions_forward(Get_robot_direction(), steps), 3))
		{
			set_coordinate_in_NP_array(y_positions_forward(Get_robot_direction(), steps), x_positions_forward(Get_robot_direction(), steps), 1);
		}
		steps++;
	}
	if(map_array[robot_pos.y_tile][robot_pos.x_tile] == 2)
	{
		nearest_path_driven = true;
	}
	else if(steps > 0)
	{
		//robot_move_distance(steps);
		Movement_Queue_Put('f');
		Movement_Queue_Put(steps);
		robot_pos.x_tile = x_positions_forward(Get_robot_direction(), steps);
		robot_pos.y_tile = y_positions_forward(Get_robot_direction(), steps);
	}
	else if(detect_path(right_y_pos(), right_x_pos(), 3))
	{
		//set_coordinate_in_NP_array(ypos, xpos, 1);
		//robot_turn_right();
		Movement_Queue_Put('r');
		Movement_Queue_Put(90);
		if(robot_pos.angle == 0)
		{
			robot_pos.angle = 3 * M_PI / 2;
		}
		else
		{
			robot_pos.angle -= M_PI / 2;
		}
	}
	else if(detect_path(left_y_pos(), left_x_pos(), 3))
	{
		//set_coordinate_in_NP_array(ypos, xpos, 1);
		//robot_turn_left();
		Movement_Queue_Put('l');
		Movement_Queue_Put(90);
		if(robot_pos.angle == 3 * M_PI / 2)
		{
			robot_pos.angle = 0;
		}
		else
		{
			robot_pos.angle += M_PI / 2;
		}
	}

}

uint8_t Get_robot_direction()
{
	uint8_t direction = 66;
	
	if(robot_pos.angle == 0)
	{
		direction = 8;
	}
	else if(robot_pos.angle == M_PI/2)
	{
		direction = 4;
	}
	else if(robot_pos.angle == M_PI)
	{
		direction = 2;
	}
	else if(robot_pos.angle == 3*M_PI/2)
	{
		direction = 6;
	}
	return direction;
}


void drive_back_nearest_path() //drives the same way back, drives_nearest_path need to be finished when starting this function
{
	int steps = 0;
	if(robot_pos.y_tile == 14 && robot_pos.x_tile == 14)
	{
		nearest_path_driven = true;
		return;
	}
	while(detect_path(y_positions_forward(Get_robot_direction(), steps + 1), x_positions_forward(Get_robot_direction(), steps + 1), 1))/* && */
		 /*(y_positions_forward(Get_robot_direction(), steps) != 14 && x_positions_forward(Get_robot_direction(), steps) != 14)*/
	{
		if(steps > 15)
		{
			nearest_path_driven_back = true;
			Movement_Queue_Put('f');
			Movement_Queue_Put(15);
			return;
		}
		steps++;
	}
	if(steps > 0)
	{
		//robot_move_distance(steps);
		Movement_Queue_Put('f');
		Movement_Queue_Put(steps);
		robot_pos.x_tile = x_positions_forward(Get_robot_direction(), steps);
		robot_pos.y_tile = y_positions_forward(Get_robot_direction(), steps);
	}
	else if(detect_path(right_y_pos(), right_x_pos(), 1))
	{
		Movement_Queue_Put('r');
		Movement_Queue_Put(90);
		if(robot_pos.angle == 0)
		{
			robot_pos.angle = 3 * M_PI / 2;
		}
		else
		{
			robot_pos.angle -= M_PI / 2;
		}
		//robot_turn_right();
	}
	else if(detect_path(left_y_pos(), left_x_pos(), 1))
	{
		//robot_turn_left();
		Movement_Queue_Put('l');
		Movement_Queue_Put(90);
		if(robot_pos.angle == 3 * M_PI / 2)
		{
			robot_pos.angle = 0;
		}
		else
		{
			robot_pos.angle += M_PI / 2;
		}
	}
	else if(detect_path(back_y_pos(), back_x_pos(), 1)) 
	{
		Movement_Queue_Put('l');
		Movement_Queue_Put(180);
		if(robot_pos.angle == M_PI)
		{
			robot_pos.angle = 0;
		}
		else if(robot_pos.angle == 3 * M_PI / 2)
		{
			robot_pos.angle = M_PI / 2;
		}
		else 
		{
			robot_pos.angle += M_PI;
		}
	}
	else
	{
		nearest_path_driven_back = true;
	}

}