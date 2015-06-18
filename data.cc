#include "data.h"
#include <assert.h>

Data::Data(){

}

int Data::LoadData(char** filename){

}

DataType Data::GetDataPoint(int position){

	assert(position<data_points_size);
	return data_points[position];
}  	

float Data::GetDistance(int data_point_position, int cluster_center_position){

}

int Data::AddClusterCenters(int data_point_position){

	assert(data_point_position<data_points_size);

	cluster_centers->center[cluster_centers->current_position]=data_points[data_point_position];
	cluster_centers->current_position++;	
	
	return 1;
}

Data::~Data(){

}