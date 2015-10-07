#ifndef __LOAD_SAVE_PARAMS_H
#define __LOAD_SAVE_PARAMS_H

#ifndef __MAIN_H
	#include "main.h"
#endif /* __MAIN_H */

#define LOAD_SAVE_BUFF_SIZE 256
#define LOAD_SAVE_PATH_SIZE 512

#define DEFAULT_PARAMS_PATH		"/opt/www/apps/eSenzor/default_params.txt"
#define SAVED_PARAMS_PATH		"/opt/www/apps/eSenzor/saved_params.txt"


void load_params(rp_app_params_t *p_copy, int load_default);
void save_params(rp_app_params_t *p_copy);
void enable_RW(void);

#endif /* __LOAD_SAVE_PARAMS_H */