#include <gui/screen1_screen/Screen1View.hpp>
#include "main.h"
#include "string.h"

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
	memset((void*)LTDC_L1_ADDR, 0xFF, LTDC_L1_WIDTH * LTDC_L1_HEIGHT * 2);
}
