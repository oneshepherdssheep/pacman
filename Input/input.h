#ifndef INPUT_H
#define INPUT_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "colours.h"
#include "../Utils/utils.h"

#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'
#define QUIT 'Q'

bool INPUT_isEventAMove(enum TEvent event);
enum TEvent INPUT_getLastUserInputEvent();
enum TEvent INPUT_getLastAIInputEvent();

#endif