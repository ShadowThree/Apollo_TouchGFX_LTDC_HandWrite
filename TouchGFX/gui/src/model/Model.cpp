#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#ifndef SIMULATOR
//#include "dbger.h"
#include "atk_ncr.h"
extern char result[CHAR_NUM+1];
#endif

Model::Model() : modelListener(0)
{

}

void Model::tick()
{
#ifndef SIMULATOR
	if(result[0]) {
//		LOG_DBG((char*)"tick showResult: %s\n", result);
		modelListener->showResult(result);
	}
#endif
}
