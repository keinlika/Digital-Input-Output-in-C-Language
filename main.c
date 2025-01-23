// Address of the Advanced High-performance Bus 2 Enable Register
unsigned int* AHB2ENR = (unsigned int*) 0x4002104c;

// Base addresses of the GPIO Port control registers (SFRs)
Port* GPIOA = (Port*) 0x48000000; // base address of GPIOA
Port* GPIOB = (Port*) 0x48000400; // base address of GPIOB
Port* GPIOC = (Port*) 0x48000800; // base address of GPIOC

/* Part 1. Typed by Kein Lika. */
// Input pins
#define ArmButtonPin 13 // PC13
#define DisarmButtonPin 4 // PA4
#define FrontSensorPin 6 // PA6
#define BackSensorPin 7 // PA7
#define WindowSensorPin 9 // PA9

// Output pins
#define ArmStatusPin 5 // PA5
#define FrontAlarmPin 0 // PB0 green
#define BackAlarmPin 5 // PB5 yellow
#define WindowAlarmPin 10 // PA10 blue

int main(void) {
    // Turn on GPIO clocks (Ports A, B, and C)
    *AHB2ENR |= 0b111;

    /* Part 2. Typed by Kein Lika. */
    // Configure button pins as inputs
    GPIOC->MODER &= ~(0b11 << (ArmButtonPin * 2)); // configure ArmButtonPin as input
    GPIOA->MODER &= ~(0b11 << (DisarmButtonPin * 2)); // configure DisarmButtonPin as input

    // Configure reed switch pins as inputs
    GPIOA->MODER &= ~(0b11 << (FrontSensorPin * 2)); // configure FrontSensorPin as input
    GPIOA->MODER &= ~(0b11 << (BackSensorPin * 2)); // configure BackSensorPin as input
    GPIOA->MODER &= ~(0b11 << (WindowSensorPin * 2)); // configure WindowSensorPin as input

    /* Part 3. Typed by Kein Lika. */
    // Enable pull resistors
    GPIOA->PUPDR |= (0b01 << (DisarmButtonPin * 2)); // enable pull-up resistor for DisarmButtonPin
    GPIOA->PUPDR |= (0b01 << (FrontSensorPin * 2)); // enable pull-up resistor for FrontSensorPin
    GPIOA->PUPDR |= (0b01 << (BackSensorPin * 2)); // enable pull-up resistor for BackSensorPin
    GPIOA->PUPDR |= (0b01 << (WindowSensorPin * 2)); // enable pull-up resistor for WindowSensorPin

    /* Part 4. Typed by Kein Lika. */
    // Configure LED pins as outputs
    GPIOA->MODER &= ~(0b10 << (ArmStatusPin * 2)); // configure ArmStatusPin as output
    GPIOB->MODER &= ~(0b10 << (FrontAlarmPin * 2)); // configure FrontAlarmPin as output
    GPIOB->MODER &= ~(0b10 << (BackAlarmPin * 2)); // configure BackAlarmPin as output
    GPIOA->MODER &= ~(0b10 << (WindowAlarmPin * 2)); // configure WindowAlarmPin as output

    // Initialize Alarm Status (turn off all LEDs)
    GPIOA->ODR &= ~(1 << ArmStatusPin);
    GPIOB->ODR &= ~(1 << FrontAlarmPin);
    GPIOB->ODR &= ~(1 << BackAlarmPin);
    GPIOA->ODR &= ~(1 << WindowAlarmPin);

    // Armed state (initialize to disarm)
    int armed = 0;

    // Infinite loop
    while (1) {
        /* Part 5. Typed by Kein Lika. */
        // Check if ArmButton is pressed
        if ((GPIOC->IDR & (1 << ArmButtonPin)) == 0) {
            // Arm system
            armed = 1; // set arm state
            GPIOA->ODR |= (1 << ArmStatusPin); // turn on ArmStatus LED
        }

        // Check if DisarmButton is pressed
        if ((GPIOA->IDR & (1 << DisarmButtonPin)) == 0) {
            // Disarm system
            armed = 0; // reset arm state
            GPIOA->ODR &= ~(1 << ArmStatusPin); // turn off ArmStatus LED
            GPIOB->ODR &= ~(1 << FrontAlarmPin); // turn off FrontAlarm LED
            GPIOB->ODR &= ~(1 << BackAlarmPin); // turn off BackAlarm LED
            GPIOA->ODR &= ~(1 << WindowAlarmPin); // turn off WindowAlarm LED
        }

        /* Part 6. Typed by Kein Lika. */
        // If system is armed, check sensors
        if (armed) {
            // Check the FrontSensor
            if ((GPIOA->IDR & (1 << FrontSensorPin)) != 0) {
                // System armed & front door is open:
                GPIOB->ODR |= (1 << FrontAlarmPin); // turn on FrontAlarm LED
            }

            // Check the BackSensor
            if ((GPIOA->IDR & (1 << BackSensorPin)) != 0) {
                // System armed & back door is open:
                GPIOB->ODR |= (1 << BackAlarmPin); // turn on BackAlarm LED
            }

            // Check the WindowSensor
            if ((GPIOA->IDR & (1 << WindowSensorPin)) != 0) {
                // System armed & window is open:
                GPIOA->ODR |= (1 << WindowAlarmPin); // turn on WindowAlarm LED
            }
        }
    }
}