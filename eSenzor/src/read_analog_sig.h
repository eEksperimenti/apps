#define PATH_LEN 512
#define NUM_ANA_SIG 4
#define NUM_ANA_SIG_LEN 1000

extern float *rp_ain0_val;
extern float *rp_ain1_val;
extern float *rp_ain2_val;
extern float *rp_ain3_val;
extern float *pdelta_T;
extern float *pnum_of_meas;
extern int app_running;
extern pthread_mutex_t rp_analog_sig_mutex;

void *reading_analog_sig(void *ptr);
void *read_analog_sig2(void *ptr);
int rp_start_API(void);
int rp_stop_API(void);