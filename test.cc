#include "data.h"
#include "./tools/run_perf.hh"
#include "./tools/timer.hh"

using namespace std;

void KMeans(string test_file_name, int n, int k, int dims) {
	Data* d = new Data();
	
	d->LoadData(test_file_name, n, dims);

	d->InitializeClusterCenters(k);
	d->AssignToCenters();
	
	//d->PrintAllDistances();
	//d->PrintData();
}

void KMeansPlusPlus(string test_file_name, int n, int k, int dims) {
	Data* dpp = new Data();
	
	dpp->LoadData(test_file_name, n, dims);
	dpp->AllocateSpaceForClusterCentersKPP(k);
	
	dpp->CarefullSeedingKPP(k);
	dpp->AssignToCenters();

	//dpp->PrintData();
	//dpp->PrintAllDistances();
}



int main(int argc, char* argv[]) {
	cout<<"argc = "<<argc<<endl;
	if (argc == 5) {

		//Get the data from command line.
		int n = atoi(argv[1]);
		cout<<"n = "<<n<<endl;
		int k = atoi(argv[2]);
		cout<<"k = "<<k<<endl;
		int dims = atoi(argv[3]);
		cout<<"dims = "<<dims<<endl;
		string test_file_name = argv[4];
		cout<<"test_file_name = "<<test_file_name<<endl;


		timer* t = new timer();
		perfProfiler* p = new perfProfiler("cycles,cache-misses", false);

		t->start();
		p->startPerf();


		//1. Uncomment for k-means
		KMeans(test_file_name, n, k, dims);


		//2. Uncomment for k-means++
		//KMeansPlusPlus(test_file_name, n, k, dims);


		t->end();
		p->endPerf();

		cout<<"\nTotal Running time: "<<t->getDiff()<<" seconds."<<endl;
		return 0;
	}
	else {
		cout<<"Incorrect number of arguments."<<endl;
		exit(EXIT_FAILURE);
	}
}
