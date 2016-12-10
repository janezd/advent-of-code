#ifndef __ADVENT_HPP
#define __ADVENT_HPP

#include "LedControl.h"

static LedControl lcd(12, 11, 10, 1);
static bool lcd_initialized = false;

void showNumber(long long number, char pos, char width=4);
void done();
void tick(int d=10);

#endif