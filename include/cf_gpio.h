/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 */

/*
 * [ GPIO module ]
 * 
 * input type: JSON
 * input data: JSON
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <lcf_log.h>
#include <cf_string.h>
#include <cf_common.h>
#include <cf_pipe.h>
#include <cf_buffer.h>
#include <cf_timer.h>
#include <cf_fdevent.h>
#include <cf_json.h>

#define MDS_GPIO_ELEM_CLASS_NAME   "GPIO"
#define MDS_MSG_TYPE_JSON  "JSON"

typedef struct cf_gpio CFGpio;

struct cf_gpio{
    int port;
    int fd;
    enum {GPIO_MODE_INPUT, GPIO_MODE_OUTPUT} mode;
    union {
		struct {
			enum {GPIO_TRIG_RISING, GPIO_TRIG_FALLING, GPIO_TRIG_BOTH} trigger;
			char action[1024];
            CFFdevents* evts;
			CFFdevent valueEvt;
            void(*triggerHndl)(CFGpio* gio, void* ctx);
            void* ctx;
            BOOL curState;
		} _input_;
		struct {
			BOOL phase1State;
			int phase1Period;
			int phase2Period;
			int count;
			BOOL stoppedState;
			CFTimer phase1Timer;
			CFTimer phase2Timer;
		} _output_;
	}_u_;
};
#define u_input	_u_._input_
#define u_output	_u_._output_

int CFGpioOutputInit(CFGpio* gio,
			int port,
			BOOL phase1State,
			int phase1Period,
			int phase2Period,
			int count,
			BOOL stoppedState);
int CFGpioOutputExit(CFGpio* gio);
int CFGpioOutputStart(CFGpio* gio);
int CFGpioOutputStop(CFGpio* gio);
int CFGpioOutputReset(CFGpio* gio,
			BOOL phase1State,
			int phase1Period,
			int phase2Period,
			int count,
			BOOL stoppedState);

int CFGpioInputInit(CFGpio* gio, int port, int trigger, void(triggerHndl)(CFGpio* gio, void* ctx), void* ctx, CFFdevents* evts);
int CFGpioInputExit(CFGpio* gio);
int CFGpioInputGetState(CFGpio* gio);
/*
    {
        "class": "GPIO",
        "name": "WPS_BTN",
        "port": 1,
        "mode": "input",
        "trigger": "rising",
        "action": "echo rising"
    },
    {
        "class": "GPIO",
        "name": "wifi_led",
        "port": 2,
        "mode": "output",
        "state": [0,500,500,1,-1]
    }
*/
int CFGpioInitByJson(CFGpio* gio, CFFdevents* evts, CFJson* jConf);
int CFGpioExit(CFGpio* gio);

