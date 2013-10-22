/*
The aggregate CPenMax displays the second largest(penultimate) value.


Registration:
create or replace aggregate penmax(int4)
returns int4 state (int4, int4)
language cpp api version 2 parameter style npsgeneric
external class name 'CPenMax' 
external host object '/panasas/scratch/Netezza_test/penmax.o_x86'
external spu object '/panasas/scratch/Netezza_test/penmax.o_spu10';

Usage:
create table test (x int, b int);
insert into test values(2,3);
insert into test values(1,4);
insert into test values(1,6);
insert into test values(3,8);
insert into test values(5,7);

select * from test;
select penmax(x) from test;
select penmax(y) from test; 
 */

#include "udxinc.h"
#include <string.h>

using namespace nz::udx_ver2;

class CPenMax: public Uda{
	public:
	CPenMax(UdxInit *pInit):Uda(pInit){}
	static Uda* instantiate(UdxInit *pInit);
	virtual void initializeState();
	virtual void accumulate();
	virtual void merge();
	virtual ReturnValue finalResult();
};

Uda* CPenMax::instantiate(UdxInit *pInit){
	CPenMax *pPenMax = new CPenMax(pInit);
	return (Uda *)pPenMax;
}

void CPenMax::initializeState(){
	setStateNull(0, true);
	setStateNull(1, true);
}

void CPenMax::accumulate(){
	int *pCurrMax = int32State(0);
	bool currMaxNull = isStateNull(0);
	int *pCurrPenMax = int32State(1);
	bool currPenMaxNull = isStateNull(1);
	int currVal = int32Arg(0);
	bool currValNull = isArgNull(0);
	
	if(!currValNull){
		if(currMaxNull){
			setStateNull(0, false);
			*pCurrMax = currVal;
		}else{
			if(currVal > *pCurrMax){
				setStateNull(1, false);
				*pCurrPenMax = *pCurrMax;
				*pCurrMax = currVal;
			}else if(currPenMaxNull || currVal > *pCurrPenMax){
				setStateNull(1, false);
				*pCurrPenMax = currVal;
			}
		}
	}
}

void CPenMax::merge(){
	int *pCurrMax = int32State(0);
	bool currMaxNull = isStateNull(0);
	int *pCurrPenMax = int32State(1);
	bool currPenMaxNull = isStateNull(1);
	
	int nextMax = int32Arg(0);
	int nextMaxNull = isArgNull(0);
	
	int nextPenMax = int32Arg(1);
	int nextPenMaxNull = isArgNull(1);
	
	if(!nextMaxNull){
		if(currMaxNull){
			setStateNull(0, false);
			*pCurrMax = nextMax;
		}else{
			if( nextMax > *pCurrMax){
				setStateNull(1, false);
				*pCurrPenMax = *pCurrMax;
				*pCurrMax = nextMax;
			}else if ( currPenMaxNull || nextMax > *pCurrPenMax){
				setStateNull(1, false);
				*pCurrPenMax = nextMax;
			}
		}
		
		if (!nextPenMaxNull){
			if(isStateNull(1)){
				setStateNull(1, false);
				*pCurrPenMax = nextPenMax;
			}else{
				if (nextPenMax > *pCurrPenMax){
					*pCurrPenMax = nextPenMax;
				}
			}
		}
	}
}

ReturnValue CPenMax::finalResult(){
	int currPenMax = int32Arg(1);
	bool currPenMaxNull = isArgNull(1);
	if (currPenMaxNull) NZ_UDX_RETURN_NULL();
	setReturnNull(false);
	NZ_UDX_RETURN_INT32(currPenMax);
}		
