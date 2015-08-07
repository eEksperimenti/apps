 #ifndef __RP_H
 #define __RP_H
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 
 #include <stdint.h>
 #include <stdbool.h>
 
 
 
 #define RP_OK     0
 
 #define RP_EOED   1
 
 #define RP_EOMD   2
 
 #define RP_ECMD   3
 
 #define RP_EMMD   4
 
 #define RP_EUMD   5
 
 #define RP_EOOR   6
 
 #define RP_ELID   7
 
 #define RP_EMRO   8
 
 #define RP_EWIP   9
 
 #define RP_EPN    10
 
 #define RP_UIA    11
 
 #define RP_FCA    12
 
 #define RP_RCA    13
 
 #define RP_BTS    14
 
 #define RP_EIPV   15
 
 #define RP_EUF    16
 
 #define RP_ENN    17
 
 #define RP_EFOB   18
 
 #define RP_EFCB   19
 
 #define RP_EABA   20
 
 #define RP_EFRB   21
 
 #define RP_EFWB   22
 
 
 typedef enum {
     RP_LED0,       
     RP_LED1,       
     RP_LED2,       
     RP_LED3,       
     RP_LED4,       
     RP_LED5,       
     RP_LED6,       
     RP_LED7,       
     RP_DIO0_P,     
     RP_DIO1_P,     
     RP_DIO2_P,     
     RP_DIO3_P,     
     RP_DIO4_P,     
     RP_DIO5_P,     
     RP_DIO6_P,     
     RP_DIO7_P,     
     RP_DIO0_N,     
     RP_DIO1_N,     
     RP_DIO2_N,     
     RP_DIO3_N,     
     RP_DIO4_N,     
     RP_DIO5_N,     
     RP_DIO6_N,     
     RP_DIO7_N      
 } rp_dpin_t;
 
 typedef enum {
     RP_LOW, 
     RP_HIGH 
 } rp_pinState_t;
 
 typedef enum {
     RP_IN, 
     RP_OUT 
 } rp_pinDirection_t;
 
 typedef enum {
     RP_AOUT0,      
     RP_AOUT1,      
     RP_AOUT2,      
     RP_AOUT3,      
     RP_AIN0,       
     RP_AIN1,       
     RP_AIN2,       
     RP_AIN3        
 } rp_apin_t;
 
 typedef enum {
     RP_TEMP_FPGA,  
     RP_VCC_PINT,   
     RP_VCC_PAUX,   
     RP_VCC_BRAM,   
     RP_VCC_INT,    
     RP_VCC_AUX,    
     RP_VCC_DDR     
 } rp_health_t;
 
 typedef enum {
     RP_WAVEFORM_SINE,       
     RP_WAVEFORM_SQUARE,     
     RP_WAVEFORM_TRIANGLE,   
     RP_WAVEFORM_RAMP_UP,    
     RP_WAVEFORM_RAMP_DOWN,  
     RP_WAVEFORM_DC,         
     RP_WAVEFORM_PWM,        
     RP_WAVEFORM_ARBITRARY   
 } rp_waveform_t;
 
 typedef enum {
     RP_GEN_MODE_CONTINUOUS, 
     RP_GEN_MODE_BURST,      
     RP_GEN_MODE_STREAM      
 } rp_gen_mode_t;
 
 
 typedef enum {
     RP_GEN_TRIG_SRC_INTERNAL = 1,   
     RP_GEN_TRIG_SRC_EXT_PE = 2,     
     RP_GEN_TRIG_SRC_EXT_NE = 3,     
     RP_GEN_TRIG_GATED_BURST     
 } rp_trig_src_t;
 
 typedef enum {
     RP_CH_1, 
     RP_CH_2  
 } rp_channel_t;
 
 typedef enum {
     RP_SMP_125M,     
     RP_SMP_15_625M,  
     RP_SMP_1_953M,   
     RP_SMP_122_070K, 
     RP_SMP_15_258K,  
     RP_SMP_1_907K    
 } rp_acq_sampling_rate_t;
 
 
 typedef enum {
     RP_DEC_1,     
     RP_DEC_8,     
     RP_DEC_64,    
     RP_DEC_1024,  
     RP_DEC_8192,  
     RP_DEC_65536  
 } rp_acq_decimation_t;
 
 
 typedef enum {
     RP_TRIG_SRC_DISABLED, 
     RP_TRIG_SRC_NOW,      
     RP_TRIG_SRC_CHA_PE,   
     RP_TRIG_SRC_CHA_NE,   
     RP_TRIG_SRC_CHB_PE,   
     RP_TRIG_SRC_CHB_NE,   
     RP_TRIG_SRC_EXT_PE,   
     RP_TRIG_SRC_EXT_NE,   
     RP_TRIG_SRC_AWG_PE,   
     RP_TRIG_SRC_AWG_NE    
 } rp_acq_trig_src_t;
 
 
 typedef enum {
     RP_TRIG_STATE_TRIGGERED, 
     RP_TRIG_STATE_WAITING,   
 } rp_acq_trig_state_t;
 
 
 typedef struct {
     uint32_t fe_ch1_fs_g_hi; 
     uint32_t fe_ch2_fs_g_hi; 
     uint32_t fe_ch1_fs_g_lo; 
     uint32_t fe_ch2_fs_g_lo; 
     int32_t  fe_ch1_dc_offs; 
     int32_t  fe_ch2_dc_offs; 
     uint32_t be_ch1_fs;      
     uint32_t be_ch2_fs;      
     int32_t  be_ch1_dc_offs; 
     int32_t  be_ch2_dc_offs; 
 } rp_calib_params_t;
 
 
 
 int rp_Init();
 
 int rp_Release();
 
 int rp_Reset();
 
 const char* rp_GetVersion();
 
 rp_calib_params_t rp_GetCalibrationSettings();
 
 const char* rp_GetError(int errorCode);
 
 
 
 int rp_DpinReset();
 
 int rp_DpinSetState(rp_dpin_t pin, rp_pinState_t state);
 
 int rp_DpinGetState(rp_dpin_t pin, rp_pinState_t* state);
 
 int rp_DpinSetDirection(rp_dpin_t pin, rp_pinDirection_t direction);
 
 int rp_DpinGetDirection(rp_dpin_t pin, rp_pinDirection_t* direction);
 
 
 
 
 int rp_ApinReset();
 
 
 int rp_ApinGetValue(rp_apin_t pin, float* value);
 
 int rp_ApinGetValueRaw(rp_apin_t pin, uint32_t* value);
 
 int rp_ApinSetValue(rp_apin_t pin, float value);
 
 int rp_ApinSetValueRaw(rp_apin_t pin, uint32_t value);
 
 int rp_ApinGetRange(rp_apin_t pin, float* min_val,  float* max_val);
 
 
 
 
 int rp_AcqSetDecimation(rp_acq_decimation_t decimation);
 
 int rp_AcqGetDecimation(rp_acq_decimation_t* decimation);
 
 int rp_AcqGetDecimationFactor(uint32_t* decimation);
 
 int rp_AcqSetSamplingRate(rp_acq_sampling_rate_t sampling_rate);
 
 int rp_AcqGetSamplingRate(rp_acq_sampling_rate_t* sampling_rate);
 
 int rp_AcqGetSamplingRateHz(float* sampling_rate);
 
 int rp_AcqSetAveraging(bool enabled);
 
 int rp_AcqGetAveraging(bool *enabled);
 
 int rp_AcqSetTriggerSrc(rp_acq_trig_src_t source);
 
 int rp_AcqGetTriggerSrc(rp_acq_trig_src_t* source);
 
 int rp_AcqGetTriggerState(rp_acq_trig_state_t* state);
 
 int rp_AcqSetTriggerDelay(int32_t decimated_data_num);
 
 int rp_AcqGetTriggerDelay(int32_t* decimated_data_num);
 
 int rp_AcqSetTriggerDelayNs(int64_t time_ns);
 
 int rp_AcqGetTriggerDelayNs(int64_t* time_ns);
 
 int rp_AcqSetTriggerLevel(float voltage);
 
 int rp_AcqGetTriggerLevel(float* voltage);
 
 int rp_AcqSetTriggerHyst(float voltage);
 
 int rp_AcqGetTriggerHyst(float* voltage);
 
 int rp_AcqSetGain(rp_channel_t channel, rp_pinState_t state);
 
 int rp_AcqGetGain(rp_channel_t channel, rp_pinState_t* state);
 
 int rp_AcqGetGainV(rp_channel_t channel, float* voltage);
 
 int rp_AcqGetWritePointer(uint32_t* pos);
 
 int rp_AcqGetWritePointerAtTrig(uint32_t* pos);
 
 int rp_AcqStart();
 
 int rp_AcqReset();
 
 uint32_t rp_AcqGetNormalizedDataPos(uint32_t pos);
 
 int rp_AcqGetDataPosRaw(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, int16_t* buffer, uint32_t *buffer_size);
 
 int rp_AcqGetDataPosV(rp_channel_t channel, uint32_t start_pos, uint32_t end_pos, float* buffer, uint32_t *buffer_size);
 
 int rp_AcqGetDataRaw(rp_channel_t channel,  uint32_t pos, uint32_t* size, int16_t* buffer);
 
 int rp_AcqGetOldestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer);
 
 int rp_AcqGetLatestDataRaw(rp_channel_t channel, uint32_t* size, int16_t* buffer);
 
 int rp_AcqGetDataV(rp_channel_t channel, uint32_t pos, uint32_t* size, float* buffer);
 
 int rp_AcqGetOldestDataV(rp_channel_t channel, uint32_t* size, float* buffer);
 
 int rp_AcqGetLatestDataV(rp_channel_t channel, uint32_t* size, float* buffer);
 
 
 int rp_AcqGetBufSize(uint32_t* size);
 
 
 
 
 
 int rp_HealthGetValue(rp_health_t sensor, float* value);
 
 
 
 
 
 int rp_GenReset();
 
 int rp_GenOutEnable(rp_channel_t channel);
 
 int rp_GenOutDisable(rp_channel_t channel);
 
 int rp_GenOutIsEnabled(rp_channel_t channel, bool *value);
 
 int rp_GenAmp(rp_channel_t channel, float amplitude);
 
 int rp_GenGetAmp(rp_channel_t channel, float *amplitude);
 
 int rp_GenOffset(rp_channel_t channel, float offset);
 
 int rp_GenGetOffset(rp_channel_t channel, float *offset);
 
 int rp_GenFreq(rp_channel_t channel, float frequency);
 
 int rp_GenGetFreq(rp_channel_t channel, float *frequency);
 
 int rp_GenPhase(rp_channel_t channel, float phase);
 
 int rp_GenGetPhase(rp_channel_t channel, float *phase);
 
 int rp_GenWaveform(rp_channel_t channel, rp_waveform_t type);
 
 int rp_GenGetWaveform(rp_channel_t channel, rp_waveform_t *type);
 
 int rp_GenArbWaveform(rp_channel_t channel, float *waveform, uint32_t length);
 
 int rp_GenGetArbWaveform(rp_channel_t channel, float *waveform, uint32_t *length);
 
 int rp_GenDutyCycle(rp_channel_t channel, float ratio);
 
 int rp_GenGetDutyCycle(rp_channel_t channel, float *ratio);
 
 int rp_GenMode(rp_channel_t channel, rp_gen_mode_t mode);
 
 int rp_GenGetMode(rp_channel_t channel, rp_gen_mode_t *mode);
 
 int rp_GenBurstCount(rp_channel_t channel, int num);
 
 int rp_GenGetBurstCount(rp_channel_t channel, int *num);
 
 int rp_GenBurstRepetitions(rp_channel_t channel, int repetitions);
 
 int rp_GenGetBurstRepetitions(rp_channel_t channel, int *repetitions);
 
 int rp_GenBurstPeriod(rp_channel_t channel, uint32_t period);
 
 int rp_GenGetBurstPeriod(rp_channel_t channel, uint32_t *period);
 
 int rp_GenTriggerSource(rp_channel_t channel, rp_trig_src_t src);
 
 int rp_GenGetTriggerSource(rp_channel_t channel, rp_trig_src_t *src);
 
 int rp_GenTrigger(int mask);
 
 
 
 
 int rp_I2cRead(int addr, char *data, int length);
 
 
 int rp_I2cWrite(int addr, char *data, int length);
 
 
 #ifdef __cplusplus
 }
 #endif
 
 #endif //__RP_H