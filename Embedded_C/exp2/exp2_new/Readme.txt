The pwm project is a simple demonstration program of the SDK SCTimer's driver capabiltiy to generate PWM signals. The PWM outputs may be observed with an oscilloscope.

In this example, The pwm module generates three PWM signals. The example will initialize clock, pin mux configuration, then configure the pwm module to make it work.

The example configures 3 PWM signals at 1kHZ
- SCTIMER output 0.  (Red LED on Alakart)
- SCTIMER output 1.  (Green LED on Alakart)
- SCTIMER output 2.  (Blue LED on Alakart)

All PWM signals start with 15% duty cycle ratios. PWM duty cycle ratios may be updated via button presses.
