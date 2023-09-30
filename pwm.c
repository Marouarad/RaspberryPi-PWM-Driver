#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pwm.h"


// choose pwm0 or pwm1
int load_pwm(S_PWM *ps_pwm, char id_canal[2]){

//the file where we gonna write the id
FILE *p_pwm; 

    if ((p_pwm = fopen("/sys/class/pwm/pwmchip0/export", "w")) == NULL)
    {
        printf("Cannot open export file.\n");
        exit(1);
    }

    //putting the cursor on the first line/column of the file
    rewind(p_pwm); 
    //storing the id in the file
    strcpy(ps_pwm->id_canal, id_canal);
    fwrite(&ps_pwm->id_canal, sizeof(char), 1, p_pwm); 
    fclose(p_pwm);
  
    return 0;
}

//Enable Disable Function:-----------  ---------------  -------

int set_pwm_enable(S_PWM *ps_pwm, int i_enable)
{
    FILE *p_pwm_enable;
    char pwm_enable[37];
    char c_enable[2];

        sprintf(pwm_enable, "/sys/class/pwm/pwmchip0/pwm%s/enable", ps_pwm->id_canal);

        if ((p_pwm_enable = fopen(pwm_enable, "w")) == NULL)
        {
            printf("Cannot open enable file.\n");
            exit(1);
        }

        rewind(p_pwm_enable);//putting the cursor on the first line/column of the file
        sprintf(c_enable, "%d", i_enable);
        ps_pwm->enable = i_enable;
        //writing the value 1 for enable or 0 desable in the file
        fwrite(&c_enable, sizeof(char), 1, p_pwm_enable);
        fclose(p_pwm_enable);
  
    return 0;
}

//Defifing the pwm Period

int set_pwm_period(S_PWM *ps_pwm, long long int i_period){

    FILE *p_pwm_period;
    char pwm_period[37];
    char c_period[8];
    
    set_pwm_enable(ps_pwm,0); 

    sprintf(pwm_period, "/sys/class/pwm/pwmchip0/pwm%s/period", ps_pwm->id_canal);
    
    if ((p_pwm_period = fopen(pwm_period, "w")) == NULL)
        {
            printf("Cannot open period file.\n");
            exit(1);
        }
        rewind(p_pwm_period); 
        sprintf(c_period, "%lli", i_period); 

        ps_pwm->period = i_period;
        //write the period value in the period file
        fwrite(&c_period, sizeof(char), 8, p_pwm_period);
        fclose(p_pwm_period);
        
        set_pwm_enable(ps_pwm,1);//-- Enable pin after changing the period value (disabled before changing values)
  
    return 0;
}


//duty cyle

int set_pwm_duty_cycle(S_PWM *ps_pwm, long long int i_duty_cycle){

    FILE *p_pwm_duty_cycle;
    char pwm_duty_cycle[50];
    char c_duty_cycle[8];
    
    set_pwm_enable(ps_pwm,0);// disabling before changing any value
    
    
    sprintf(pwm_duty_cycle, "/sys/class/pwm/pwmchip0/pwm%s/duty_cycle", ps_pwm->id_canal);
    if ((p_pwm_duty_cycle = fopen(pwm_duty_cycle, "w")) == NULL)
        {
            printf("Cannot open duty cycle file.\n");
            exit(1);
        }

        rewind(p_pwm_duty_cycle);
 
        sprintf(c_duty_cycle, "%lli", i_duty_cycle); 
        ps_pwm->duty_cycle = i_duty_cycle;

        fwrite(&c_duty_cycle, sizeof(char), 8, p_pwm_duty_cycle);
        fclose(p_pwm_duty_cycle);

        set_pwm_enable(ps_pwm,1);
  
  
    return 0;
}