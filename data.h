#ifndef DATA_H
#define DATA_H

/*****************************************************

The API to interact with the data set. 

** status load_data(char** filename)
** 


*****************************************************/

/**
	Data type (INT by default)
*/

typedef int DataType;

/**
	each point in the data set has a dimension and values.
*/

struct DataPoint{

	DataType* values;
};

class Data{

private:
	
	DataPoint* data_points; 		/*  The array of stored data values */
	DataPoint* cluster_centers;		/*  The array of cluster centers */
	int dimension;					/*  The dimension of each point */
	int data_points_size;			/*  Number of data points */
	int cluster_centers_size;		/*	Number of cluster centers */

public:
	
	int LoadData(char** filename);  		/* Load values from a file */
	DataType GetDataPoint(int position);  	/* Given a certain position, get the value from the dataset */
	float GetDistance(int data_point_position, int cluster_center_position);
	int AddClusterCenters(int data_point_position);

};









#endif