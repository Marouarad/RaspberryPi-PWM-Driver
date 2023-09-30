#ifndef PWM_H_
#define PWM_H_

// Define PWM pin ids
#define PWM00 "18"
#define PWM01 "12"

// Define enable and disable values
#define ENABLE "1"
#define DISABLE "0"

// PWM structure
struct S_PWM {
    char id_canal[2];          // PWM channel id
    int enable;                // PWM enable status (1 for enabled, 0 for disabled)
    long long int period;      // PWM period value
    long long int duty_cycle;  // PWM duty cycle value
};
typedef struct S_PWM S_PWM;

int load_pwm(S_PWM *ps_pwm, char id_canal[2]);// Exporting the PWM pin to the user layer


// We cannot modify any values on the PWM pin until it is disabled !!
// Enable/disable functions:-----------  ---------

// Enable or disable the PWM pin
int set_pwm_enable(S_PWM *ps_pwm, int i_enable);

// Setting up the period value
int set_pwm_period(S_PWM *ps_pwm, long long int period);

// Setting up the duty cycle value
int set_pwm_duty_cycle(S_PWM *ps_pwm, long long int duty_cycle);

#endif /*PWM_H_*/
