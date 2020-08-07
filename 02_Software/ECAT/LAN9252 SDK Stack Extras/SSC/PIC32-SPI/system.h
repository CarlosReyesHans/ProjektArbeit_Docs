/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* TODO Define system operating frequency */

/* Microcontroller MIPs (FCY) */
#define SYS_FREQ     80000000L
#define FCY          SYS_FREQ

/* Core Timer configuration*/
#define TOGGLES_PER_SEC (10)
#define CORE_TICK_RATE  (SYS_FREQ/2/TOGGLES_PER_SEC)

extern UINT8 tenMSTicker;
/******************************************************************************/
/* System Function Prototypes                                                 */
/******************************************************************************/

/* Custom oscillator configuration funtions, reset source evaluation
functions, and other non-peripheral microcontroller initialization functions
go here. */

void ConfigureCoreTimer();

