#define PATH_LEN 512
#define NUM_ANA_SIG 4
#define NUM_ANA_SIG_LEN 512
#define SIG_LENGTH 1024

extern float *pdelta_T;
extern float *pnum_of_meas;
extern float *ptrig_mode;
extern float *pchange;
extern float *pN;
extern int api_running;
extern int api_wait;
extern pthread_mutex_t rp_analog_sig_mutex;
extern pthread_mutex_t rp_main_params_mutex;
extern float *ptime;
extern float *ana_sig_array;

void *read_analog_sig(void *ptr);
void *read_analog_sig2(void *ptr);
int rp_start_API(void);
int rp_init_API(void);
int rp_stop_API(void);
int rp_copy_analog_signals(float ***signals, int *sig_idx);