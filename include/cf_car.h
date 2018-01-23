/*
 * Copyright (C) 2012 Chunfeng Zhang (CrazyPandar@gmail.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
 
#ifndef _CF_CAR_H_
#define _CF_CAR_H_
#include "cf_timer.h"

typedef struct cf_motor {
    const char* name;
    int fd;
}CFMotor;
int CFMotorInit(CFMotor* mt, const char* dev, const char* name);
int CFMotorForward(CFMotor* mt, uint speed);
int CFMotorBackward(CFMotor* mt, uint speed);
int CFMotorStop(CFMotor* mt);
int CFMotorBrake(CFMotor* mt);
int CFMotorExit(CFMotor* mt);


typedef struct cf_car {
    int leftMtFd;
    int rightMtFd;
    int wheelbase;
    CFTimer actionTmr;
}CFCar;

int CFCarInit(CFCar* car, const char* leftMtDev, const char* rightMtDev, int wheelbase);
int CFCarExit(CFCar* car);
int CFCarFoward(CFCar* car, uint speed, int last, int distance);
int CFCarBackward(CFCar* car, uint speed, int last, int distance);
int CFCarSpinRight(CFCar* car, uint speed, int last, int distance);
int CFCarSpinLeft(CFCar* car, uint speed, int last, int distance);
int CFCarTurnRight(CFCar* car, uint radius, uint speed, int last, int distance);
int CFCarTurnLeft(CFCar* car, uint radius, uint speed, int last, int distance);
int CFCarStop(CFCar* car);
int CFCarBrake(CFCar* car);
int CFCarGetMotorSpeed(CFCar* car, int* left, int* right);
 
#endif
