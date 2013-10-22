/*
 * UDF var_concat, takes two input VARCHAR strings of any length, concatenate them, and returns combined VARCHAR string.
 *
 * Compilation:
 * nzudxcompile concat.cpp -o concat.o
 *
 * Registration:
 * create or replace function var_concat(varchar(any), varchar(any))
 * returns varchar(any)
 * language cpp api version 2
 * parameter style npsgeneric
 * called on null input
 * not deterministic
 * external class name 'Concat'
 * external host object '/panasas/scratch/Netezza_test/concat.o_x86'
 * external spu object '/panasas/scratch/Netezza_test/concat.o_spu10';
 *
 * Usage:
 * select var_concat('New', 'York');
 *
 *
 */
#include <string.h>
#include "udxinc.h"

using namespace nz::udx_ver2;

class Concat: public nz::udx_ver2::Udf{
	Concat(UdxInit *pInit): Udf(pInit){}
	static nz::udx_ver2::Udf* instantiate(UdxInit *pInit);
	inline bool isValidArgType(int at) const{
		return at==UDX_FIXED||at==UDX_VARIABLE;
	}
	virtual ReturnValue evaluate(){
		if(numArgs()!=2){
			throwUdxException("var_concat number of arguments is not 2");
		}
		if (isArgNull(0)) NZ_UDX_RETURN_NULL();
		if (isArgNull(1)) NZ_UDX_RETURN_NULL();
		setReturnNull(false);
		
		int argType0=argType(0);
		int argType1=argType(1);

		if(isValidArgType(argType0) && isValidArgType(argType1)){
			StringArg *a = stringArg(0);
			StringArg *b = stringArg(1);
			StringReturn *ret = stringReturnInfo();
			ret->size = a->length + b->length;
			memcpy(ret->data, a->data, a->length);
			memcpy(ret->data+a->length, b->data, b->length);
			NZ_UDX_RETURN_STRING(ret);
		}else{
			throwUdxException("Datatypes must be among char/nchar/varchar/nvarchar.");
		}
	}	

	virtual uint64 calculateSize() const{
		int argType0 = sizerArgType(0);
		int argType1 = sizerArgType(1);
		if (isValidArgType(argType0) && isValidArgType(argType1)){
			return sizerStringSizeValue(sizerStringArgSize(0)+sizerStringArgSize(1));
		}else{
			throwUdxException("Datatype mismatch.");
		}
	}
};


nz::udx_ver2::Udf* Concat::instantiate(UdxInit *pInit){
	return new Concat(pInit);
}
