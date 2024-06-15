#include <gui/screen1_screen/Screen1View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>

#ifndef SIMULATOR
//#include "dbger.h"
#endif

Screen1Presenter::Screen1Presenter(Screen1View& v)
    : view(v)
{

}

void Screen1Presenter::activate()
{

}

void Screen1Presenter::deactivate()
{

}

void Screen1Presenter::showResult(char* result)
{
#ifndef SIMULATOR
	//LOG_DBG((char*)"presenter showResult: %s\n", result);
	view.showResult(result);
#endif
}