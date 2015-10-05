#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "load_save_params.h"

void load_params(rp_app_params_t *p_copy, int load_default)
{
  FILE *fd = NULL;
  char *mode = "r";
  char *file_path = NULL;
  file_path = (char*)malloc(sizeof(char)*LOAD_SAVE_PATH_SIZE);

  if( file_path == NULL )
      return;

  file_path[0] = '\0';

  if( load_default == 1 )
    strcpy(file_path, "/opt/www/apps/ugotoviElement/default_params.txt");
  else
    strcpy(file_path, "/opt/www/apps/ugotoviElement/saved_params.txt");

  fd = fopen(file_path, mode);

  if( fd != NULL )
  {
    
    char *buff = NULL;
    buff = (char*)malloc(sizeof(char)*LOAD_SAVE_BUFF_SIZE);

    if( buff == NULL )
    {
      free(file_path);
      return;
    }
      

    buff[0] = '\0';

    char *delimeter = ":";
    char *token = NULL;
    int i;

    for( i = 0; i < PARAMS_NUM; ++i )
    {
      fscanf(fd, "%s", buff);
      token = strtok(buff, delimeter);
      token = strtok(NULL, delimeter);
      p_copy[i].value = strtof(token, NULL);
    } 

    p_copy[LOAD_SAVE_PARAMS].value = 0;
    fclose(fd);
    free(buff);
    free(file_path);
  }
}

void save_params(rp_app_params_t *p_copy)
{

  FILE *fd = NULL;
  char *mode = "w";
  char *file_path = NULL;
  file_path = (char*)malloc(sizeof(char)*LOAD_SAVE_PATH_SIZE);

  if( file_path == NULL )
      return;

  file_path[0] = '\0';
  strcpy(file_path, "/opt/www/apps/ugotoviElement/saved_params.txt");

  fd = fopen(file_path, mode);

  if( fd != NULL )
  {
    
    char *buff = NULL;
    buff = (char*)malloc(sizeof(char)*LOAD_SAVE_BUFF_SIZE);

    if( buff == NULL )
    {
      free(file_path);
      return;
    }

    buff[0] = '\0';
    char *delimeter = ":";

    int i;

    p_copy[LOAD_SAVE_PARAMS].value = 0;
    for( i = 0; i < PARAMS_NUM; ++i)
    {
      //if( strcmp(p_copy[i].name, "force_flag") == 0 )
      buff[0] = '\0';
      strcat(buff, p_copy[i].name);
      strcat(buff, delimeter);
      sprintf(file_path, "%f", p_copy[i].value);
      strcat(buff, file_path);
      fprintf(fd, "%s\n", buff);
    }

    fclose(fd);
    free(buff);
    free(file_path);
  }
}

/*void load_params(rp_app_params_t *p_copy, int load_default)
{
  FILE *fd = NULL;
  char *mode = "r";
  char *file_path = NULL;
  file_path = (char*)malloc(sizeof(char)*BUFF_SIZE);

  if( file_path == NULL )
      return;

  file_path[0] = '\0';

  if( load_default == 1 )
    strcpy(file_path, "/opt/www/apps/eSenzor/default_params.txt");
  else
    strcpy(file_path, "/opt/www/apps/eSenzor/saved_params.txt");

  fd = fopen(file_path, mode);

  if( fd != NULL )
  {
    
    char *buff = NULL;
    buff = (char*)malloc(sizeof(char)*BUFF_SIZE);

    if( buff == NULL )
      return;

    buff[0] = '\0';

    char *delimeter = ":";
    char *token = NULL;

    while( fscanf(fd, "%s", buff) == 1 )
    {
      token = strtok(buff, delimeter);

      if( strcmp(token, "trig_mode") == 0 )
      {
        token = strtok(NULL, delimeter);
        p_copy[TRIG_MODE_PARAM].value = strtof(token, NULL);
      }
      else 
        if( strcmp(token, "trig_source") == 0 )
        {
           token = strtok(NULL, delimeter);
           p_copy[TRIG_SRC_PARAM].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "trig_edge") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[TRIG_EDGE_PARAM].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "trig_delay") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[TRIG_DLY_PARAM].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "trig_level") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[TRIG_LEVEL_PARAM].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "single_btn") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[SINGLE_BUT_PARAM].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "time_range") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[TIME_RANGE_PARAM].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "en_avg_at_dec") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[EN_AVG_AT_DEC].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "auto_flag") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[AUTO_FLAG_PARAM].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "forcex_flag") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[FORCEX_FLAG_PARAM].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "prb_att_ch1") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[PRB_ATT_CH1].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gain_ch1") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GAIN_CH1].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "prb_att_ch2") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[PRB_ATT_CH2].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gain_ch2") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GAIN_CH2].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_DC_offs_1") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_DC_OFFS_1].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_DC_offs_2") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_DC_OFFS_2].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_DC_norm_1") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_DC_NORM_1].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_DC_norm_2") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_DC_NORM_2].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "scale_ch1") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[SCALE_CH1].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "scale_ch2") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[SCALE_CH2].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_trig_mod_ch1") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_TRIG_MODE_CH1].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_sig_type_ch1") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_SIG_TYPE_CH1].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_enable_ch1") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_ENABLE_CH1].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_single_ch1") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_SINGLE_CH1].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_sig_amp_ch1") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_SIG_AMP_CH1].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_sig_freq_ch1") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_SIG_FREQ_CH1].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_sig_dcoff_ch1") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_SIG_DCOFF_CH1].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_trig_mod_ch2") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_TRIG_MODE_CH2].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_sig_type_ch2") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_SIG_TYPE_CH2].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_enable_ch2") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_ENABLE_CH2].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_single_ch2") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_SINGLE_CH2].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_sig_amp_ch2") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_SIG_AMP_CH2].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_sig_freq_ch2") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_SIG_FREQ_CH2].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_sig_dcoff_ch2") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_SIG_DCOFF_CH2].value = strtof(token, NULL);
        }
      else 
        if( strcmp(token, "gen_awg_refresh") == 0 )
        {
          token = strtok(NULL, delimeter);
          p_copy[GEN_AWG_REFRESH].value = strtof(token, NULL);
        }
    } 
    p_copy[LOAD_SAVE_PARAMS].value = 0;
    fclose(fd);
    free(buff);
    free(file_path);
  }
}*/

