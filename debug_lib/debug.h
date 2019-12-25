#ifndef _DEBUG_H
#define _DEBUG_H

#define DEBUG
//#define RAMLOG

#ifdef DEBUG
	#ifdef RAMLOG
		#include <ramlog.h>
		#define print_debug(...) ramlog_printf(__VA_ARGS__)
	#else
		#include <stdio.h>
		#define print_debug(...) printf(__VA_ARGS__)
	#endif
#else
	#define print_debug(...) do{}while(0)
#endif

#endif
