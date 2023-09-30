#include <string.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include "pwm.h"

int main(int argc,char*argv[]){

    S_PWM pwm1;

    if(argc !=3){
        printf("Not enough arguments!!\n");
    }l

    long long int duty   = atoi(argv[1]); 
    long long int period = atoi( argv[2]);
    printf("entering the infite loop \n");
    
    load_pwm(&pwm1,PWM0);
    set_pwm_enable(&pwm1,0);

    printf("duty >> %lld period >> %lld\n",duty,period);
    
while(1){
   set_pwm_enable(&pwm1,0); 
      set_pwm_duty_cycle(&pwm1,duty);
      set_pwm_period(&pwm1,period);
      set_pwm_enable(&pwm1,1);
      sleep(5);
   
}


    return 0;
}

