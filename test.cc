

#include "data.h"
#include "./tools/run_perf.hh"
#include "./tools/timer.hh"

using namespace std;

int main(){

	timer* t = new timer();
	perfProfiler* p = new perfProfiler("cycles,cache-misses",false);

	t->start();
	p->startPerf();
	Data* d = new Data();
	d->LoadData("test.data",3,3);
	d->initialize(2);
	d->PrintData();
	//printf("%f\n",d->GetDataPoint(0).values);
	d->AddClusterCenters(0);
	d->AddClusterCenters(1);
	printf("%f\n",d->GetDistance(0,1));
	t->end();
	p->endPerf();
	return 0;
}
