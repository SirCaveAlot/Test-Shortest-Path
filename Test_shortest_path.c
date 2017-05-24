/*
 * Test_shortest_path.c
 *
 * Created: 2017-05-23 20:54:21
 *  Author: Deep
 */ 


#include <avr/io.h>
#include "Adjacent_array.h"
#include "global_variables.h"
#include "Main_array.h"
#include "Positioning.h"
#include "SearchAndFind.h"
#include "ShortestPath.h"

int main(void)
{
	robot_pos.x_tile = 14;
	robot_pos.y_tile = 14;
	robot_pos.angle = 0;
	
	Main_array_init(Find_y_end_position(), Find_x_end_position());
	Pathfinder();
	nearest_path_to_array();
	while(!nearest_path_driven)
	{
		drive_nearest_path();
	}
	while(!nearest_path_driven_back)
	{
		drive_back_nearest_path();
	}
    return 0;
}