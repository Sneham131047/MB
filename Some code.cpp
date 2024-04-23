#include "mbed.h" 
#include "ADXL345_I2C.h" 
ADXL345_I2C accelerometer(PB_11,PB_10); 
Serial pc(USBTX,USBRX); 
int X_out_raw,Y_out_raw,Z_out_raw; 
int X_out,Y_out,Z_out; 
int main(){ 
    int readings[3]={0,0,0}; 
    pc.printf("Starting ADXL345 test...\n"); 
    wait(.001); 
    pc.printf("Device ID is: 0x%02x\n",accelerometer.getDeviceID()); 
    wait(.001); 
    if(accelerometer.setPowerControl(0x00)){ 
        pc.printf("didn't initialize power control\n"); 
        return 0; 
    } 
    wait(.001); 
    if(accelerometer.setDataFormatControl(0x0B)){ 
        pc.printf("didn't set data format\n"); 
        return 0; 
    } 
    wait(.001); 
    if (accelerometer.setDataRate(ADXL345_3200HZ)) { 
        pc.printf("didn't set data rate\n");        
        return 0; 
    }         
    wait(.001);        
    if(accelerometer.setPowerControl (MeasurementMode)) { 
        pc.printf("didn't set the power control to measurement\n"); 
        return 0; 
    }         
    while (1){        
        wait(0.1);        
        accelerometer.getOutput(readings);         
        wait(0.1); 
        X_out_raw = (int16_t)readings[0]; 
        Y_out_raw =(int16_t)readings[1]; 
        Z_out_raw =(int16_t)readings[2]; 
        X_out = 0.94 *X_out + 0.06* X_out_raw; 
        Y_out = 0.94 *Y_out + 0.06 * Y_out_raw; 
        Z_out = 0.94 *Z_out + 0.06 * Z_out_raw; 
        pc.printf("X:%i,Y:%i,Z:%i\r\n",X_out, Y_out, Z_out); 
    } 
} 