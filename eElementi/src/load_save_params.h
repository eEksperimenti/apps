#ifndef __LOAD_SAVE_PARAMS_H
#define __LOAD_SAVE_PARAMS_H

#ifndef __MAIN_H
	#include "main.h"
#endif /* __MAIN_H */

#define LOAD_SAVE_BUFF_SIZE 256
#define LOAD_SAVE_PATH_SIZE 512

void load_params(rp_app_params_t *p_copy, int load_default);
void save_params(rp_app_params_t *p_copy);

#endif /* __LOAD_SAVE_PARAMS_H */