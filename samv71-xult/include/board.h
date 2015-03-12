/************************************************************************************
 * configs/samv71-xult/include/board.h
 *
 *   Copyright (C) 2015 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

#ifndef __CONFIGS_SAMV71_XULT_INCLUDE_BOARD_H
#define __CONFIGS_SAMV71_XULT_INCLUDE_BOARD_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <stdbool.h>

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/
/* Clocking *************************************************************************/
/* After power-on reset, the SAMV71Q device is running out of the Master Clock using
 * the Fast RC Oscillator running at 4 MHz.
 *
 *   MAINOSC:  Frequency = 12MHz (crystal)
 *
 * 300MHz Settings:
 *   PLLA: PLL Divider = 1, Multiplier = 20 to generate PLLACK = 240MHz
 *   Master Clock (MCK): Source = PLLACK, Prescalar = 1 to generate MCK = 120MHz
 *   CPU clock: 120MHz
 *
 */

/* Main oscillator register settings.
 *
 * The main oscillator could be either the embedded 4/8/12 MHz fast RC oscillators
 * or an external 3-20 MHz crystal or ceramic resonator.  The external clock source
 * is selected by default in sam_clockconfig.c.  Here we need to specify the main
 * oscillator start-up time.
 *
 * REVISIT... this is old information:
 * The start up time should be should be:
 *
 *   Start Up Time = 8 * MOSCXTST / SLCK = 56 Slow Clock Cycles.
 */

#define BOARD_CKGR_MOR_MOSCXTST    (62 << PMC_CKGR_MOR_MOSCXTST_SHIFT) /* Start-up Time */

/* PLLA configuration.
 *
 *   Divider = 1
 *   Multiplier = 25
 *
 * Yields:
 *
 *   PLLACK = 25 * 12MHz / 1 = 300MHz
 */

#define BOARD_CKGR_PLLAR_STMODE    PMC_CKGR_PLLAR_STMODE_FAST
#define BOARD_CKGR_PLLAR_COUNT     (63 << PMC_CKGR_PLLAR_COUNT_SHIFT)
#define BOARD_CKGR_PLLAR_MUL       PMC_CKGR_PLLAR_MUL(25)
#define BOARD_CKGR_PLLAR_DIV       PMC_CKGR_PLLAR_DIV_BYPASS

/* PMC master clock register settings.
 *
 *  BOARD_PMC_MCKR_CSS - The source of main clock input.  This may be one of:
 *
 *    PMC_MCKR_CSS_SLOW   Slow Clock
 *    PMC_MCKR_CSS_MAIN   Main Clock
 *    PMC_MCKR_CSS_PLLA   PLLA Clock
 *    MC_MCKR_CSS_UPLL    Divided UPLL Clock
 *
 *  BOARD_PMC_MCKR_PRES - Source clock pre-scaler.  May be one of:
 *
 *    PMC_MCKR_PRES_DIV1  Selected clock
 *    PMC_MCKR_PRES_DIV2  Selected clock divided by 2
 *    PMC_MCKR_PRES_DIV4  Selected clock divided by 4
 *    PMC_MCKR_PRES_DIV8  Selected clock divided by 8
 *    PMC_MCKR_PRES_DIV16 Selected clock divided by 16
 *    MC_MCKR_PRES_DIV32  Selected clock divided by 32
 *    PMC_MCKR_PRES_DIV64 Selected clock divided by 64
 *    PMC_MCKR_PRES_DIV3  Selected clock divided by 3
 *
 *  The prescaler determines (1) the CPU clock and (2) the input into the
 *  second divider that then generates the Master Clock (MCK).  MCK is the
 *  source clock of the peripheral clocks.
 *
 *  BOARD_PMC_MCKR_MDIV - MCK divider.  May be one of:
 *
 *    PMC_MCKR_MDIV_DIV1  Master Clock is Prescaler Output Clock / 1
 *    PMC_MCKR_MDIV_DIV2  Master Clock = Prescaler Output Clock / 2
 *    PMC_MCKR_MDIV_DIV4  Master Clock = Prescaler Output Clock / 4
 *    PMC_MCKR_MDIV_DIV3  Master Clock = Prescaler Output Clock / 3
 */

#define BOARD_PMC_MCKR_CSS         PMC_MCKR_CSS_PLLA   /* Source = PLLA */
#define BOARD_PMC_MCKR_PRES        PMC_MCKR_PRES_DIV1  /* Prescaler = /1 */
#define BOARD_PMC_MCKR_MDIV        PMC_MCKR_MDIV_DIV2  /* MCK divider = /2 */

/* USB clocking
 * To be provided
 */

#define BOARD_PMC_MCKR_UPLLDIV2    0           /* UPLL clock not divided by 2 */

/* Resulting frequencies */

#define BOARD_MAINOSC_FREQUENCY    (12000000)  /* MAINOSC: 12MHz crystal on-board */
#define BOARD_PLLA_FREQUENCY       (300000000) /* PLLACK:  25 * 12Mhz / 1 */
#define BOARD_CPU_FREQUENCY        (300000000) /* CPU:     PLLACK / 1 */
#define BOARD_MCK_FREQUENCY        (150000000) /* MCK:     PLLACK / 1 / 2 */

/* HSMCI clocking
 *
 * Multimedia Card Interface clock (MCCK or MCI_CK) is Master Clock (MCK)
 * divided by (2*(CLKDIV+1)).
 *
 *   MCI_SPEED = MCK / (2*(CLKDIV+1))
 *   CLKDIV = MCK / MCI_SPEED / 2 - 1
 *
 * Where CLKDIV has a range of 0-255.
 */

/* FLASH wait states.
 *
 * Wait states Max frequency at 105 centigrade (STH conditions)
 *
 *           VDDIO
 *      1.62V     2.7V
 * --- -------  -------
 *  0   26 MHz   30 MHz
 *  1   52 MHz   62 MHz
 *  2   78 MHz   93 MHz
 *  3  104 MHz  124 MHz
 *  4  131 MHz  150 MHz
 *  5  150 MHz  --- MHz
 *
 * Given: VDDIO=3.3V, VDDCORE=1.2V, MCK=150MHz
 */

#define BOARD_FWS                  4

/* LED definitions ******************************************************************/
/* LEDs
 *
 * There are two yellow LED available on the SAM V71 Xplained Ultra board that
 * can be turned on and off.  The LEDs can be activated by driving the
 * connected I/O line to GND.
 *
 *   ------ ----------- ---------------------
 *   SAMV71 Function    Shared functionality
 *   PIO
 *   ------ ----------- ---------------------
 *   PA23   Yellow LED0 EDBG GPIO
 *   PC09   Yellow LED1 LCD, and Shield
 *   ------ ----------- ---------------------
 *
 * If CONFIG_ARCH_LEDS is not defined, then the user can control the LEDs in any
 * way.  The following definitions are used to access individual LEDs.
 */

/* LED index values for use with lpc31_setled() */

#define BOARD_LED0        0
#define BOARD_LED1        1
#define BOARD_NLEDS       2

/* LED bits for use with lpc31_setleds() */

#define BOARD_LED0_BIT    (1 << BOARD_LED0)
#define BOARD_LED1_BIT    (1 << BOARD_LED1)

/* These LEDs are not used by the board port unless CONFIG_ARCH_LEDS is
 * defined.  In that case, the usage by the board port is defined in
 * include/board.h and src/sam_autoleds.c. The LEDs are used to encode
 * OS-related events as follows:
 *
 *   SYMBOL                     Meaning                      LED state
 *                                                         LED2   LED1
 *   ------------------------  --------------------------  ------ ------ */

#define LED_STARTED          0 /* NuttX has been started   OFF    OFF    */
#define LED_HEAPALLOCATE     0 /* Heap has been allocated  OFF    OFF    */
#define LED_IRQSENABLED      0 /* Interrupts enabled       OFF    OFF    */
#define LED_STACKCREATED     1 /* Idle stack created       ON     OFF    */
#define LED_INIRQ            2 /* In an interrupt           No change    */
#define LED_SIGNAL           2 /* In a signal handler       No change    */
#define LED_ASSERTION        2 /* An assertion failed       No change    */
#define LED_PANIC            3 /* The system has crashed   N/C  Blinking */
#undef  LED_IDLE               /* MCU is is sleep mode      Not used     */

/* Thus if LED0 is statically on, NuttX has successfully booted and is,
 * apparently, running normally.  If LED1 is flashing at approximately
 * 2Hz, then a fatal error has been detected and the system has halted.
 *
 * NOTE: That LED0 is not used after completion of booting and may
 * be used by other board-specific logic.
 */

/* Button definitions ***************************************************************/
/* Buttons
 *
 * SAM V71 Xplained Ultra contains three mechanical buttons. One button is the
 * RESET button connected to the SAM V71 reset line and the others are generic
 * user configurable buttons. When a button is pressed it will drive the I/O
 * line to GND.
 *
 *   ------ ----------- ---------------------
 *   SAMV71 Function    Shared functionality
 *   PIO
 *   ------ ----------- ---------------------
 *   RESET  RESET       Trace, Shield, and EDBG
 *   PA09   SW0         EDBG GPIO and Camera
 *   PB12   SW1         EDBG SWD and Chip Erase
 *   ------ ----------- ---------------------
 *
 * NOTES:
 *
 *   - There are no pull-up resistors connected to the generic user buttons so
 *     it is necessary to enable the internal pull-up in the SAM V71 to use the
 *     button.
 *   - PB12 is set up as a system flash ERASE pin when the firmware boots. To
 *     use the SW1, PB12 has to be configured as a normal regular I/O pin in
 *     the MATRIX module. For more information see the SAM V71 datasheet.
 */

#define BUTTON_SW0        0
#define BUTTON_SW1        1
#define NUM_BUTTONS       2

#define BUTTON_SW0_BIT    (1 << BUTTON_SW0)
#define BUTTON_SW1_BIT    (1 << BUTTON_SW1)

/* PIO Disambiguation ***************************************************************/
/* Serial Console
 *
 * The SAMV71-XULT has no on-board RS-232 drivers so it will be necessary to use
 * either the VCOM or an external RS-232 driver.  Here are some options.
 *
 *  - Arduino Serial Shield:  One option is to use an Arduino-compatible
 *    serial shield.  This will use the RXD and TXD signals available at pins
 *    0 an 1, respectively, of the Arduino "Digital Low" connector.  On the
 *    SAMV71-XULT board, this corresponds to UART3:
 *
 *    ------ ------ ------- ------- --------
 *    Pin on SAMV71 Arduino Arduino SAMV71
 *    J503   PIO    Name    Pin     Function
 *    ------ ------ ------- ------- --------
 *      1    PD28   RX0     0       URXD3
 *      2    PD30   TX0     1       UTXD3
 *    ------ ------ ------- ------- --------
 *
 *    There are alternative pin selections only for UTXD3:
 */

#define GPIO_UART3_TXD  GPIO_UART3_TXD_1

/*  - SAMV7-XULT EXTn connectors.  USART pins are also available the EXTn
 *    connectors.  The following are labelled in the User Guide for USART
 *    functionality:
 *
 *    ---- -------- ------ --------
 *    EXT1 EXTI1    SAMV71 SAMV71
 *    Pin  Name     PIO    Function
 *    ---- -------- ------ --------
 *    13   USART_RX PB00   RXD0
 *    14   USART_TX PB01   TXD0
 *
 *    ---- -------- ------ --------
 *    EXT2 EXTI2    SAMV71 SAMV71
 *    Pin  Name     PIO    Function
 *    ---- -------- ------ --------
 *    13   USART_RX PA21   RXD1
 *    14   USART_TX PB04   TXD1
 *
 *    There are no alternative pin selections for USART0 or USART1.
 */

/*  - VCOM.  The Virtual Com Port gateway is available on USART1:
 *
 *    ------ --------
 *    SAMV71 SAMV71
 *    PIO    Function
 *    ------ --------
 *    PB04   TXD1
 *    PA21   RXD1
 *    ------ --------
 *
 *    There are no alternative pin selections for USART1.
 */

/* SSC
 *
 * Alternative pin selections are available only for SSC0 TD.
 * On the SAMV71-XULT board, PD26 supports the I2S TD function
 */

#define GPIO_SSC0_TD   GPIO_SSC0_TD_1

/************************************************************************************
 * Public Types
 ************************************************************************************/

/************************************************************************************
 * Public Data
 ************************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/************************************************************************************
 * Public Functions
 ************************************************************************************/

 /************************************************************************************
 * Name:  sam_ledinit, sam_setled, and sam_setleds
 *
 * Description:
 *   If CONFIG_ARCH_LEDS is defined, then NuttX will control the on-board LEDs.  If
 *   CONFIG_ARCH_LEDS is not defined, then the following interfaces are available to
 *   control the LEDs from user applications.
 *
 ************************************************************************************/

#ifndef CONFIG_ARCH_LEDS
void sam_ledinit(void);
void sam_setled(int led, bool ledon);
void sam_setleds(uint8_t ledset);
#endif

/************************************************************************************
 * Name:  sam_lcdclear
 *
 * Description:
 *   This is a non-standard LCD interface just for the SAM4e-EK board.  Because
 *   of the various rotations, clearing the display in the normal way by writing a
 *   sequences of runs that covers the entire display can be very slow.  Here the
 *   display is cleared by simply setting all GRAM memory to the specified color.
 *
 ************************************************************************************/

#if defined(CONFIG_SAM4EEK_LCD_RGB565)
void sam_lcdclear(uint16_t color);
#else /* if defined(CONFIG_SAM4EEK_LCD_RGB24) defined(CONFIG_SAM4EEK_LCD_RGB32) */
void sam_lcdclear(uint32_t color);
#endif

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* __CONFIGS_SAMV71_XULT_INCLUDE_BOARD_H */
