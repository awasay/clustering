#include "data.h"




Data::Data(){

}

/*Misc Functions*/

vector<string>& Data::divide(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}



vector<string> Data::divide(const string &s, char delim) {
    vector<string> elems;
    divide(s, delim, elems);
    return elems;
}

/*misc functions*/

int Data::LoadData(string file_name, int data_size, int input_dim){
	
	data_points = new DataPoint[data_size];
	data_points_size = data_size;
	dimension = input_dim;
	
	string line;
	ifstream my_file (file_name);

	int posn = 0;
	int dim;
	
	if(my_file.is_open()){
		while ( getline (my_file,line,';') && data_size != 0){
			
			vector <string> items = divide(line,',');
			
			data_points[posn].values = new DataType[input_dim];
			data_size--;
      		
      		dim=0;
      		assert(items.size() <= input_dim);
      		for (int i = 0; i < input_dim; ++i){
      			data_points[posn].values[dim] = stof(items[i]);
      			dim++;
      		}
      		
      		posn++;
      		cout<<endl;
    	}
    	
  	}else cout << "Unable to open file"; 

  	return 0;
	my_file.close();

}

int Data::initialize(int k){
	
	cluster_centers = new ClusterCenters();
	cluster_centers->centers = new DataPoint[k];
	cluster_centers->cluster_centers_size = k;
	return 0;

}

DataPoint Data::GetDataPoint(int position){

	assert(position < data_points_size);
	return data_points[position];
}  	

float Data::GetDistance(int data_point_position, int cluster_center_position){

	assert(data_point_position < data_points_size);
	assert(cluster_center_position < cluster_centers->cluster_centers_size);

	float sum=0;
	
	for (int i = 0; i < dimension; ++i){
		
		sum+=pow(data_points[data_point_position].values[i]-cluster_centers->centers[cluster_center_position].values[i],2);
	}
	return sqrt(sum);

}

int Data::AddClusterCenters(int data_point_position){

	assert(data_point_position<data_points_size);

	cluster_centers->centers[cluster_centers->current_position]=data_points[data_point_position];
	cluster_centers->current_position++;	
	
	return 1;
}

int Data::PrintData(){

	for (int i = 0; i < data_points_size; ++i)
	{
		for (int j = 0; j < dimension; ++j){
			cout<<data_points[i].values[j]<<"\t";
		}
		cout<<endl;
	}
	return 0;
}

Data::~Data(){

}








