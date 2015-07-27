#include "data.h"
#include "./tools/run_perf.hh"
#include "./tools/timer.hh"

using namespace std;



int main(int argc, char* argv[]){
	cout<<endl<<endl<<endl;
	int N, K, dims;

    N = atoi(argv[1]);
    K = atoi(argv[2]);
    dims = atoi(argv[3]);

    string test_file_name = argv[4];

	timer* t = new timer();
	perfProfiler* p = new perfProfiler("cycles,cache-misses", false);
	
	t->start();
	p->startPerf();

	//sleep(2);


	//1. Uncomment for k-means
	/*
	Data* d = new Data();
	d->LoadData(test_file_name, N, dims);

	d->initialize_Cluster_Centers(K);
	d->AssignToCenters();
	d->PrintAllDistances();
	d->PrintData();
	*/

	//2. Uncomment for k-means++
	Data* dpp = new Data();
	dpp->LoadData(test_file_name, N, dims);
	dpp->allocate_space_for_cluster_centers_KPP(K);
	dpp->carefull_seeding_KPP(K);
	




	/* commmon for both implementations*/
	dpp->AssignToCenters();
	//dpp->PrintData();
	//d->PrintAllDistances();



	t->end();
	p->endPerf();
	cout<<"\nTotal Running time: "<<t->getDiff()<<" seconds."<<endl;
	return 0;
}
