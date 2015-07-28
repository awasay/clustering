#include "data.h"

/* Global vars*/
float glbl_D_x = -1;
float glbl_D_x_sqrd = -1;
float glbl_max_D_x_sqrd = -1; 				//distances can't be negatives.
float glbl_point_with_max_d_x = -1;
float glbl_point_with_max_d_x_sqrd = -1;
int glbl_closest_center = -1;



/**
 *
 */
 Data::Data() {
 
 }

 /*Misc Functions*/
/**
 *
 */
 vector<string>& Data::divide(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


/**
 *
 *
 */
 vector<string> Data::divide(const string &s, char delim) {
    vector<string> elems;
    divide(s, delim, elems);
    return elems;
}

/*misc functions*/

/**
 *
 * @brief Loads the Database into the newly created object of class Data
 */
int Data::LoadData(string file_name, int data_size, int input_dim) {
	
	data_points = new DataPoint[data_size];
	data_points_size = data_size;
	dimension = input_dim;
	
	string line;
	ifstream my_file (file_name);

	int posn = 0;
	int dim;
	
	if (my_file.is_open()) {
		while ( getline (my_file,line,';') && data_size != 0){
			
			vector <string> items = divide(line,',');
			
			data_points[posn].values = new DataType[input_dim];
			//set minimum distance for every new point to infinity for starters.
			data_points[posn].minimum_distance = std::numeric_limits<double>::infinity();
			data_size--;		
			dim = 0;
			assert(items.size() <= input_dim);
			for (int i = 0; i < input_dim; ++i){
				data_points[posn].values[dim] = stof(items[i]);
				dim++;
			}
			posn++;
		}
	}
	else {
		cout << "Unable to open file";
    }
	my_file.close();
	return 0;
}


/**
 * @param   k   The size of the Cluster Center array.
 * @return      Returns 0 on successfull addition of the Cluster Center.
 * @brief       Randomly initializes the array of size K containing the Cluster Centers
 */
int Data::InitializeClusterCenters(int k) {
	
	cluster_centers = new ClusterCenters();
	cluster_centers->cluster_centers_size = k;
	cluster_centers->centers = new DataPoint[k];
	srand(time(NULL));
	for (int i = 0; i < k; ++i) {
		int position = rand() % data_points_size;
		AddClusterCenters(position);
	}
	return 0;
}


/**
 * @param       position    The position of the N array that is needed.
 * @return                  Returns a DataPoint stored in the specified position.
 * @brief                   Returns the object in the specified position in the N array.
 */
DataPoint Data::GetDataPoint(int position) {

	assert(position < data_points_size);
	return data_points[position];
}  	


/**
 * @param       position    The position of the K array that is needed.
 * @return                  Returns a Cluster Center DataPoint stored in the specified position.
 * @brief                   Returns the object in the specified position in the K array.
 */
ClusterCenters Data::GetClusterCenter(int position) {
	int cc_size = cluster_centers->cluster_centers_size;
	assert(position < cc_size);
	return cluster_centers[position];
}


/**
 * @param       data_point_position         The position of the data point in the N_array.
 * @param       cluster_center_position     The position of the cluster center in the K_array.
 * @return                                  Returns the distance between the Center and the Point.
 * @brief                                   Calculates the distance between a given Center and a given Point.
 */
float Data::GetDistance(int data_point_position, int cluster_center_position) {

	//assert(data_point_position < data_points_size);
	//assert(cluster_center_position < cluster_centers->cluster_centers_size);

	float sum = 0;
	if (cluster_centers->centers[cluster_center_position].values == NULL) {
		exit(1);
	}
	for (int i = 0; i < dimension; ++i) {
		sum+=pow(data_points[data_point_position].values[i] - cluster_centers->centers[cluster_center_position].values[i], 2);
	}
	return sqrt(sum);
}


void Data::PrintDistance(int data_point_position, int cluster_center_position) {
    assert(data_point_position < data_points_size);
	assert(cluster_center_position < cluster_centers->cluster_centers_size);

	DataType* data_point_values;
	DataType* cluster_center_values;

	cout<<"Distance between Cluster Center with coordinates: (";

	for (int i = 0; i < dimension; ++i) {
		data_point_values = &data_points[data_point_position].values[i];
		cluster_center_values = &cluster_centers->centers[cluster_center_position].values[i];
	}
	for (int i = 0; i < dimension; ++i) {
		cout<<cluster_center_values[i]<<" ";
		
	}
	cout<<"), and Data Point with coordinates: (";
	for (int i = 0; i < dimension; ++i) {
		cout<<data_point_values[i]<<" ";
	}
	cout<<"), is: ";
    printf("%f\n", GetDistance(data_point_position, cluster_center_position));
}


/**
 * @param       data_point_position         The position of the data point in the N_array.
 * @return                                  Returns 1 if the Cluster center was successfully created.
 * @brief                                   Adds a new Cluster Center to the K_array.
 */
int Data::AddClusterCenters(int data_point_position) {
	assert(data_point_position < data_points_size);

	cluster_centers->centers[cluster_centers->current_position] = data_points[data_point_position];
	cluster_centers->current_position++;
	
	return 1;
}


/**
 *
 * @brief
 */
int Data::PrintData() {

	for (int i = 0; i < data_points_size; ++i)
	{
		for (int j = 0; j < dimension; ++j){
			cout<<data_points[i].values[j]<<"\t";
		}
		cout<<endl;
	}
	return 0;
}


void Data::PrintAllDistances() {

	for (int i = 0; i < cluster_centers->cluster_centers_size; ++i) {
		for (int j = 0; j < data_points_size; ++j) {
			PrintDistance(j,i);
		}
	}

}

/**
 *
 * @brief
 */
void Data::AssignToCenters() {
	int k = cluster_centers->cluster_centers_size;
	int n = data_points_size;
	for (int i = 0; i < k; ++i) {
		
		for (int j = 0; j < n - 1; ++j) {
			float point_to_center_dist1 = GetDistance(j, i);
			float point_to_center_dist2 = GetDistance(j+1, i);
			//Checking 2 points at the same time = 1 less iteration.
			if (point_to_center_dist1 < point_to_center_dist2) {
				//means that Data point 1 is closer and assign it to the center
				if (data_points[j].minimum_distance > point_to_center_dist1) {
					data_points[j].minimum_distance = point_to_center_dist1;
					data_points[j].center = &cluster_centers->centers[i];
				}
				//continue;
			}
			else if (point_to_center_dist2 < point_to_center_dist1) {
				if (data_points[j+1].minimum_distance > point_to_center_dist1) {
					data_points[j+1].minimum_distance = point_to_center_dist1;
					data_points[j+1].center = &cluster_centers->centers[i];
				}
				//continue;
			}
			else {
				//SPECIAL CASE. EQUAL DISTANCE
				data_points[j+1].center = &cluster_centers->centers[i];
				data_points[j].center = &cluster_centers->centers[i];
				data_points[j+1].minimum_distance = point_to_center_dist2;
				data_points[j].minimum_distance = point_to_center_dist1;
			}
		}
	}

}


void Data::AllocateSpaceForClusterCentersKPP(int cc_size) {
	cluster_centers = new ClusterCenters();
	cluster_centers->cluster_centers_size = cc_size;
	cluster_centers->centers = new DataPoint[cc_size];
}




/**
 *
 * @brief returns the closest cluster center.
 */
int Data::GetClosestClusterCenter(int data_point_position) {
	int min_index = 0;
	double minimum_distance = -1;
	int cc_size = cluster_centers->cluster_centers_size;

	for (int i = 0; i < cc_size-1; ++i) {
		//cout<<endl<<"cluster center count = "<<i<<endl<<"data_point_position = "<<data_point_position<<endl;

		double dist = GetDistance(data_point_position, i);
		if (minimum_distance > dist && dist != 0) {
			minimum_distance = dist;
			min_index = i;
		}
	}
	return min_index;
}




void Data::EasyApproximationOfCenters(int data_point_position) {
	if (glbl_D_x_sqrd > glbl_max_D_x_sqrd) {
		glbl_max_D_x_sqrd = glbl_D_x_sqrd;
		glbl_point_with_max_d_x = data_point_position;
	}
}


int Data::FlipACoin(float probability) {
	//generate random number beetween 0 and 1
	double p = ((double)rand() / RAND_MAX);
	//heads.
	if (p <= probability) {
		return 0;
	}
	else { //tails.
		return 1;
	}
}

void Data::DifficultApproximationOfCenters(float* array, int sum) {

	for (int i = 0; i < data_points_size; ++i) {
		
		float probability = array[i] / sum;
		int coin = FlipACoin(probability);
		// 0->heads, 1->tails.
		if (coin == 0) {
			glbl_point_with_max_d_x = i;
		}
		else {
			EasyApproximationOfCenters(i);
		}
	}
}


/**
 *
 * @brief creates the cluster centers based on the users choice.
 */
void Data::CarefullSeedingKPP(int K){
	//initializing 1st center at random.
	srand(time(NULL));
	//set cc[0] = ...
	int data_point_position  = rand() % data_points_size;
	AddClusterCenters(data_point_position);
	
	float* D_x_array = new float[data_points_size];
	float sum_D_x_sqrd = -1;

	//until K centers have been chosen.
	for (int i = 1; i < K; ++i) {
		//for each data point x.
		glbl_point_with_max_d_x_sqrd = 0;
		sum_D_x_sqrd = -1;
		
		//iterate threw the data_points.
		for (int j = 0; j < data_points_size; ++j) {
			//find the closest cluster center.
			glbl_closest_center = GetClosestClusterCenter(j);

			//compute D(x) dist between x and nearest center already chosen.
			glbl_D_x = GetDistance(j, glbl_closest_center);
			glbl_D_x_sqrd = pow(glbl_D_x, 2);


			//1. Start of easy approximation of center. Point with max (D(x))^2, will be center.
			//EasyApproximationOfCenters(j);
			// End of easy approximation. Uncomment this and comment the other implementation to avoid Seg Faults!


			//2.a Start of Difficult, more costly, but more efficient approximation of center.
			//Initialize some values. The sum of ALL D(x)^2 and an array of size N containing all
			//and for each point, have it's corresponding D(x)^2 in an array. 
			D_x_array[j] = glbl_D_x_sqrd;
			sum_D_x_sqrd += glbl_D_x_sqrd;
		}
		//2.b Approximating 1 center at a time by flipping a coin.
		DifficultApproximationOfCenters(D_x_array, sum_D_x_sqrd);

		AddClusterCenters(glbl_point_with_max_d_x); 
	}
	delete D_x_array;
}

Data::~Data(){

}
