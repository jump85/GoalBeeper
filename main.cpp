#include "pico/stdlib.h"
#include "pico/sleep.h"
#include "pico/runtime_init.h"
#include "hardware/rosc.h"
#include "hardware/clocks.h"
#include "hardware/structs/scb.h"
#include "hardware/pll.h"
#include "hardware/pwm.h" 
#include <stdio.h>

const int rightDot = 26;
const int rightUnder3 = 22;
const int rightUnder2 = 21;
const int rightUnder1 = 20;

const int rightOver4 = 19;
const int rightOver3 = 18;
const int rightOver2 = 17;
const int rightOver1 = 16;

const int big1 = 13;
const int d2 = 12;
const int d3 = 11;
const int big4 = 10;
const int big5 = 9;
const int d4 = 8;

const int d1 = 2;
const int big8 = 3;
const int big9 = 4;
const int big10 = 6;
const int bigDot = 5;
const int big12 = 7;

const int buzzer = 14;
const int button1 = 15; // verde
const int button2 = 0;  // rosso
const int buttonA = 28; // blu
const int buttonB = 27; // giallo

int start = 0;
int timer = 5;
int timerLevel = 2;

int risA = 0;
int risB = 0;

int num1 = 0;
int num2 = 0;
int num3 = 0;
int num4 = 0;

int buttonGreenValuePrev = 0, buttonRedValuePrev = 0, buttonAValuePrev = 0, buttonBValuePrev = 0;
bool timerExp = false;

// Funzioni di display piccolo
void littleOne()
{
	gpio_put(rightDot, 0);
	gpio_put(rightUnder3, 1);
	gpio_put(rightUnder2, 0);
	gpio_put(rightUnder1, 0);

	gpio_put(rightOver4, 0);
	gpio_put(rightOver3, 1);
	gpio_put(rightOver2, 0);
	gpio_put(rightOver1, 0);
}



void littleFive()
{
	gpio_put(rightDot, 0);
	gpio_put(rightUnder3, 1);
	gpio_put(rightUnder2, 1);
	gpio_put(rightUnder1, 0);

	gpio_put(rightOver4, 1);
	gpio_put(rightOver3, 1);
	gpio_put(rightOver2, 1);
	gpio_put(rightOver1, 0);
}


void littleThree()
{
	gpio_put(rightDot, 0);
	gpio_put(rightUnder3, 1);
	gpio_put(rightUnder2, 1);
	gpio_put(rightUnder1, 0);

	gpio_put(rightOver4, 1);
	gpio_put(rightOver3, 0);
	gpio_put(rightOver2, 1);
	gpio_put(rightOver1, 1);
}

void littleEight()
{
	gpio_put(rightDot, 1);
	gpio_put(rightUnder3, 1);
	gpio_put(rightUnder2, 1);
	gpio_put(rightUnder1, 0);

	gpio_put(rightOver4, 1);
	gpio_put(rightOver3, 1);
	gpio_put(rightOver2, 1);
	gpio_put(rightOver1, 1);
}



void littleZero()
{
	gpio_put(rightDot, 1);
	gpio_put(rightUnder3, 1);
	gpio_put(rightUnder2, 1);
	gpio_put(rightUnder1, 1);

	gpio_put(rightOver4, 0);
	gpio_put(rightOver3, 1);
	gpio_put(rightOver2, 1);
	gpio_put(rightOver1, 1);
}



void littleEmpty()
{
	gpio_put(rightDot, 0);
	gpio_put(rightUnder3, 0);
	gpio_put(rightUnder2, 0);
	gpio_put(rightUnder1, 0);

	gpio_put(rightOver4, 0);
	gpio_put(rightOver3, 0);
	gpio_put(rightOver2, 0);
	gpio_put(rightOver1, 0);
}
// Funzioni di display grande
void bigZero() {
    gpio_put(big1, 1);
    gpio_put(big4, 1);
    gpio_put(big5, 1);
    gpio_put(big8, 0);
    gpio_put(big9, 1);
    gpio_put(big10, 1);
    gpio_put(bigDot, 0);
    gpio_put(big12, 1);
}

void bigOne() {
    gpio_put(big1, 1);
    gpio_put(big4, 0);
    gpio_put(big5, 0);
    gpio_put(big8, 0);
    gpio_put(big9, 1);
    gpio_put(big10, 0);
    gpio_put(bigDot, 0);
    gpio_put(big12, 0);
}

void bigTwo() {
    gpio_put(big1, 1);
    gpio_put(big4, 0);
    gpio_put(big5, 1);
    gpio_put(big8, 1);
    gpio_put(big9, 0);
    gpio_put(big10, 1);
    gpio_put(bigDot, 0);
    gpio_put(big12, 1);
}

void bigThree() {
    gpio_put(big1, 1);
    gpio_put(big4, 0);
    gpio_put(big5, 1);
    gpio_put(big8, 1);
    gpio_put(big9, 1);
    gpio_put(big10, 1);
    gpio_put(bigDot, 0);
    gpio_put(big12, 0);
}

void bigFour() {
    gpio_put(big1, 1);
    gpio_put(big4, 1);
    gpio_put(big5, 0);
    gpio_put(big8, 1);
    gpio_put(big9, 1);
    gpio_put(big10, 0);
    gpio_put(bigDot, 0);
    gpio_put(big12, 0);
}

void bigFive() {
    gpio_put(big1, 0);
    gpio_put(big4, 1);
    gpio_put(big5, 1);
    gpio_put(big8, 1);
    gpio_put(big9, 1);
    gpio_put(big10, 1);
    gpio_put(bigDot, 0);
    gpio_put(big12, 0);
}

void bigSix() {
    gpio_put(big1, 0);
    gpio_put(big4, 1);
    gpio_put(big5, 1);
    gpio_put(big8, 1);
    gpio_put(big9, 1);
    gpio_put(big10, 1);
    gpio_put(bigDot, 0);
    gpio_put(big12, 1);
}

void bigSeven() {
    gpio_put(big1, 1);
    gpio_put(big4, 0);
    gpio_put(big5, 1);
    gpio_put(big8, 0);
    gpio_put(big9, 1);
    gpio_put(big10, 0);
    gpio_put(bigDot, 0);
    gpio_put(big12, 0);
}

void bigEight() {
    gpio_put(big1, 1);
    gpio_put(big4, 1);
    gpio_put(big5, 1);
    gpio_put(big8, 1);
    gpio_put(big9, 1);
    gpio_put(big10, 1);
    gpio_put(bigDot, 0);
    gpio_put(big12, 1);
}

void bigNine() {
    gpio_put(big1, 1);
    gpio_put(big4, 1);
    gpio_put(big5, 1);
    gpio_put(big8, 1);
    gpio_put(big9, 1);
    gpio_put(big10, 1);
    gpio_put(bigDot, 0);
    gpio_put(big12, 0);
}

void bigEmpty() {
    gpio_put(big1, 0);
    gpio_put(big4, 0);
    gpio_put(big5, 0);
    gpio_put(big8, 0);
    gpio_put(big9, 0);
    gpio_put(big10, 0);
    gpio_put(bigDot, 0);
    gpio_put(big12, 0);
}

// Funzioni buzzer

static void buzzer_set_freq(uint32_t freq_hz) {
    // configura il pin come PWM
    gpio_set_function(buzzer, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(buzzer);
    uint chan = pwm_gpio_to_channel(buzzer);

    // scegli un wrap per risoluzione (es. 1000)
    const uint32_t wrap = 1000;

    // calcola clkdiv: freq = sys_clk / (wrap+1) / clkdiv
    const float sys_hz = (float)clock_get_hz(clk_sys);
    float clkdiv = sys_hz / ((wrap + 1) * (float)freq_hz);
    if (clkdiv < 0.01f) clkdiv = 0.01f;

    pwm_set_clkdiv(slice, clkdiv);
    pwm_set_wrap(slice, wrap);
    // 50% duty = massimo "volume" acustico tipico per buzzer
    pwm_set_chan_level(slice, chan, wrap / 2);
    pwm_set_enabled(slice, true);
}


void sound() {
    // genera 3000 Hz per 500 ms
    buzzer_set_freq(3000);
    sleep_ms(500);
    // fermati alla fine
    uint slice = pwm_gpio_to_slice_num(buzzer);
    pwm_set_enabled(slice, false);
    // ritorna pin a SIO e a livello basso
    gpio_set_function(buzzer, GPIO_FUNC_SIO);
    gpio_put(buzzer, 0);
}

void silence() {
    uint slice = pwm_gpio_to_slice_num(buzzer);
    pwm_set_enabled(slice, false);
    gpio_set_function(buzzer, GPIO_FUNC_SIO);
    gpio_put(buzzer, 0);
}

// Timer
void changeTimer() {
    timerLevel++;
    if (timerLevel > 4)
        timerLevel = 1;
}

void resetTimer() {
    switch (timerLevel) {
        case 1:
            timer = 3;
            littleThree();
            break;
        case 2:
            timer = 5;
            littleFive();
            break;
        case 3:
            timer = 8;
            littleEight();
            break;
        case 4:
            timer = 10;
            littleZero();
            break;
        default:
            break;
    }
    start = to_ms_since_boot(get_absolute_time());
}

// Display
void bigDisplay(int num, int pin) {
    gpio_put(pin, 0);
    sleep_ms(5);
    switch (num) {
        case 0: bigZero(); break;
        case 1: bigOne(); break;
        case 2: bigTwo(); break;
        case 3: bigThree(); break;
        case 4: bigFour(); break;
        case 5: bigFive(); break;
        case 6: bigSix(); break;
        case 7: bigSeven(); break;
        case 8: bigEight(); break;
        case 9: bigNine(); break;
        default: bigEmpty(); break;
    }
    gpio_put(pin, 1);
}

void calcDisplay() {
    num4 = risA / 10;
    num3 = risA % 10;
    num2 = risB / 10;
    num1 = risB % 10;
    printf("nums: %d%d%d%d\n", num4, num3, num2, num1);
}

void init(){
        stdio_init_all();

        // Inizializza tutti i pin come OUTPUT
        int output_pins[] = {rightDot, rightUnder3, rightUnder2, rightUnder1,
            rightOver4, rightOver3, rightOver2, rightOver1,
            big1, d2, d3, big4, big5, d4, d1, big8, big9, big10, bigDot, big12, buzzer};
        for (int i = 0; i < sizeof(output_pins)/sizeof(int); i++) {
            gpio_init(output_pins[i]);
            gpio_set_dir(output_pins[i], GPIO_OUT);
        }
        // Inizializza i pulsanti come INPUT
        gpio_init(button1); gpio_set_dir(button1, GPIO_IN);
        gpio_init(button2); gpio_set_dir(button2, GPIO_IN);
        gpio_init(buttonA); gpio_set_dir(buttonA, GPIO_IN);
        gpio_init(buttonB); gpio_set_dir(buttonB, GPIO_IN);
    
        resetTimer();
    
        gpio_put(d1, 1);
        gpio_put(d2, 1);
        gpio_put(d3, 1);
        gpio_put(d4, 1);


    
        sleep_ms(1000);
        
}
int main() {
    
    init();


    // Sleep until button release
    uint _scb_orig = scb_hw->scr;
    uint _en0_orig = clocks_hw->sleep_en0;
    uint _en1_orig = clocks_hw->sleep_en1;

    while (true) {



        bigDisplay(num2, d1);
        bigDisplay(num3, d2);
        bigDisplay(num4, d3);
        bigDisplay(num1, d4);

        int timerLimit = start + timer * 1000 * 60;
        int now = to_ms_since_boot(get_absolute_time());
        if (now > timerLimit) {
            bigEight();
            sound();
            timerExp = true;
        }

        int buttonGreenValue = gpio_get(button1);
        int buttonRedValue = gpio_get(button2);
        int buttonAValue = gpio_get(buttonA);
        int buttonBValue = gpio_get(buttonB);

        if (buttonGreenValue && !buttonGreenValuePrev) {
            printf("button verde!\n");
            if (timerExp) {
                silence();
                timerExp = false;
            } else {
                changeTimer();
            }
            resetTimer();
        }
        buttonGreenValuePrev = buttonGreenValue;

        if (buttonAValue && !buttonAValuePrev) {
            printf("button blu!\n");
            risA++;
            printf("%d\n", risA);
            calcDisplay();
        }
        buttonAValuePrev = buttonAValue;

        if (buttonBValue && !buttonBValuePrev) {
            printf("button giallo!\n");
            risB++;
            printf("%d\n", risB);
            calcDisplay();
        }
        buttonBValuePrev = buttonBValue;



        if (buttonRedValue && !buttonRedValuePrev) {
            printf("button rosso!\n");
            risA = 0;
            risB = 0;
            printf("%d\n", risB);
            calcDisplay();


            // Prepare to enter dormant mode until button press
            bool wake_high = true; // button pin goes high when pressed
            uint gpio_button = button2;

            // set pull according to wiring
            if (wake_high) {
                gpio_pull_down(gpio_button); // button pulls to VCC when pressed
            } else {
                gpio_pull_up(gpio_button);   // button pulls to GND when pressed
            }

            // disable all outputs
            littleEmpty();
            bigEmpty();
            silence();
            
            // small debounce / ensure we will get an edge
            sleep_ms(20);

             // save registers
            uint _scb_orig = scb_hw->scr;
            uint _en0_orig = clocks_hw->sleep_en0;
            uint _en1_orig = clocks_hw->sleep_en1;

            // prepare and enter dormant (edge=true recommended for buttons)
            sleep_run_from_xosc();
            sleep_goto_dormant_until_pin(gpio_button, wake_high, true);





            // Re-enable Ring Oscillator control
            rosc_write(&rosc_hw->ctrl, ROSC_CTRL_ENABLE_BITS);

            // restore clock registers
            scb_hw->scr             = _scb_orig;
            clocks_hw->sleep_en0    = _en0_orig;
            clocks_hw->sleep_en1    = _en1_orig;
            

            // re-initialize clocks
            sleep_ms(5); // tiny delay allowing hardware settle
            clocks_init();


            gpio_init(gpio_button);  // restore GPIO setting for dormant pin
            gpio_disable_pulls(gpio_button);
            init();

            // small debounce after wake
            sleep_ms(20);
        }



        buttonRedValuePrev = buttonRedValue;

        sleep_ms(5); // debounce
    }
}