#include "data.h"
#include <assert.h>
#include <math.h>

Data::Data(){

}

int Data::LoadData(char** filename, int size_data_set){

	

}

DataPoint Data::GetDataPoint(int position){

	assert(position<data_points_size);
	return data_points[position];
}  	

float Data::GetDistance(int data_point_position, int cluster_center_position){

	assert(data_point_position<data_points_size);
	assert(cluster_center_position<cluster_centers->cluster_centers_size);

	float sum=0;
	
	for (int i = 0; i < dimension; ++i){
		
		sum+=pow(data_points[data_point_position].values[i]-cluster_centers->center[cluster_center_position].values[i],2);
	}
	return sqrt(sum);

}

int Data::AddClusterCenters(int data_point_position){

	assert(data_point_position<data_points_size);

	cluster_centers->center[cluster_centers->current_position]=data_points[data_point_position];
	cluster_centers->current_position++;	
	
	return 1;
}

Data::~Data(){

}