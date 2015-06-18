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
	int LoadData(char** filename, int data_size);  		/* Load values from a file */
	DataPoint GetDataPoint(int position);  	/* Given a certain position, get the value from the dataset */
	float GetDistance(int data_point_position, int cluster_center_position); /*Get the distance between two points*/
	int AddClusterCenters(int data_point_position);	/* Add cluster centers */


};



int main(){
	return 0;
}





#endif