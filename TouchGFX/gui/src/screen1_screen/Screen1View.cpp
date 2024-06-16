#include <gui/screen1_screen/Screen1View.hpp>
#include <touchgfx/Utils.hpp>

#ifndef SIMULATOR
#include "dbger.h"
#include "main.h"
#include "string.h"
#include "cmsis_os2.h"
#include "atk_ncr.h"
extern osEventFlagsId_t eventGroupHandle;
#endif

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::clearHandWriteArea()
{
#ifdef SIMULATOR
	touchgfx_printf("clear Hand Write Area\n");
#else
	memset((void*)LTDC_L1_ADDR, 0xFF, LTDC_L1_WIDTH * LTDC_L1_HEIGHT * 2);
	point_num = 0;
#endif
}

void Screen1View::recognize()
{
#ifdef SIMULATOR
	char myStr[] = "A2cDe";
	touchgfx_printf("recognize %s\n", myStr);
	Unicode::strncpy(txtResultBuffer, myStr, TXTRESULT_SIZE);
	txtResult.invalidate();
#else
	osEventFlagsSet(eventGroupHandle, EVT_RECOGNIZE);
#endif
}

void Screen1View::showResult(char* result)
{
#ifdef SIMULATOR
#else
	LOG_DBG((char*)"view showResult: %s\n", result);
	Unicode::strncpy(txtResultBuffer, result, TXTRESULT_SIZE);
	txtResult.invalidate();
	memset(result, 0, CHAR_NUM + 1);
#endif
}
