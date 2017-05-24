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
	Main_array_init(Find_y_end_position(), Find_x_end_position());
	Pathfinder();
	nearest_path_to_array();
	drive_nearest_path();
	drive_back_nearest_path();
    while(1)
    {
        
    }
}