#ifndef DATA_H
#define DATA_H

#include <assert.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>

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

typedef struct DataPoint {
	DataType* values;
	DataPoint* center;				//pointer to the center it corresponds to.
	float minimum_distance;
}DataPoint;


typedef struct ClusterCenters{
	DataPoint* centers;
	int current_position = 0;
	int cluster_centers_size;
}ClusterCenters;




/* Global vars*/
extern float glbl_D_x;
extern float glbl_D_x_sqrd;
extern float glbl_max_D_x_sqrd;
extern float glbl_point_with_max_d_x;
extern float glbl_point_with_max_d_x_sqrd;
extern int glbl_closest_center;


class Data {

private:
	DataPoint* data_points; 			/*  The array of stored data values */
	int dimension;						/*  The dimension of each point */
	int data_points_size;				/*  Number of data points */
	ClusterCenters* cluster_centers;	/*  The cluster centers */

	vector<string> divide(const string &s, char delim);
	vector<string>& divide(const string &s, char delim, vector<string> &elems);
	
	/* k-means */
	int AddClusterCenters(int);	/* Add cluster centers */
	void PrintDistance(int data_point_position, int cluster_center_position);

	/* k-means ++ */
	int GenerateRandomNumber(int);
	int GetClosestClusterCenter(int);
	void EasyApproximationOfCenters(int);
	void DifficultApproximationOfCenters(float*, int);
	int FlipACoin(float);

public:
	Data();					/*Constructor*/
	~Data();				/*Destructor*/

	/* k-means */
	int InitializeClusterCenters(int);
	DataPoint GetDataPoint(int);  	/* Given a certain position, get the value from the dataset */
	ClusterCenters GetClusterCenter(int);
	

	/* k-means ++ */
	void CarefullSeedingKPP(int);
	void AllocateSpaceForClusterCentersKPP(int);


	/* shared stuff */
	int LoadData(string, int, int);  		/* Load values from a file */
	void PrintAllDistances();
	float GetDistance(int, int); /*Get the distance between two points*/
	int PrintData();
	void AssignToCenters();
};



#endif
