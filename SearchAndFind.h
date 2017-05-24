/*
 * SearchAndFind.h
 *
 * Created: 5/12/2017 2:53:24 PM
 *  Author: marwa079
 */ 


#ifndef SEARCHANDFIND_H_
#define SEARCHANDFIND_H_

extern bool finished_with_drive_nearest_path;

uint8_t Get_robot_direction();

void set_coordinate_in_NP_array(int y, int x, int value);

void nearest_path_to_array();

void drive_nearest_path();

void drive_back_nearest_path();

bool detect_path(int next_yposition,int next_xposition, int value);

#endif /* SEARCHANDFIND_H_ */