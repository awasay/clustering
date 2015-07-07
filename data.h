#ifndef DATA_H
#define DATA_H

#include <assert.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <string>

#include "misc.h"
using namespace std;

/*****************************************************

The API to interact with the data set. 

** status load_data(char** filename)
** 


*****************************************************/

/**
	Data type (INT by default)
*/

typedef float DataType;

/**
	each point in the data set has a dimension and values.
*/

struct DataPoint{

	DataType* values;
};

struct ClusterCenters{
	DataPoint* center;
	int current_position=0;
	int cluster_centers_size;
};

class Data{

private:
	
	DataPoint* data_points; 			/*  The array of stored data values */
	int dimension;						/*  The dimension of each point */
	int data_points_size;				/*  Number of data points */
	ClusterCenters* cluster_centers;	/*  The cluster centers */

public:
	
	Data();			/*Constructor*/
	~Data();		/*Destructor*/
	int LoadData(string file_name, int data_size, int dimension);  		/* Load values from a file */
	DataPoint GetDataPoint(int position);  	/* Given a certain position, get the value from the dataset */
	float GetDistance(int data_point_position, int cluster_center_position); /*Get the distance between two points*/
	int AddClusterCenters(int data_point_position);	/* Add cluster centers */
	int PrintData();

};



int main(){
	Data* d = new Data();
	d->LoadData("test.data",3,3);
	d->PrintData();
	return 0;
}


#endif