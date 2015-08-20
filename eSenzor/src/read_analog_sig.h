extern float *rp_ain0_val;
extern float *rp_ain1_val;
extern float *rp_ain2_val;
extern float *rp_ain3_val;
extern int APP_running;
extern pthread_mutex_t rp_analog_sig_mutex;
void *reading_analog_sig( void *ptr );
int rp_start_API(void);
int rp_stop_API(void);