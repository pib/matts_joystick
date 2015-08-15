/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/*
  Driver for 8 software debounced buttons on PORTB.
*/

#ifndef __BUTTONS_H__
#define __BUTTONS_H__

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Button mask for the first button on the board. */
			#define BUTTONS_BUTTON1      (1 << 0)
			#define BUTTONS_BUTTON2      (1 << 1)
			#define BUTTONS_BUTTON3      (1 << 2)
			#define BUTTONS_BUTTON4      (1 << 3)
			#define BUTTONS_BUTTON5      (1 << 4)
			#define BUTTONS_BUTTON6      (1 << 5)
			#define BUTTONS_BUTTON7      (1 << 6)
			#define BUTTONS_BUTTON8      (1 << 7)

			/* Private Interface - For use in library only: */
			#if !defined(__DOXYGEN__)
				/* Macros: */
				#define BUTTON_MASK                 (BUTTONS_BUTTON1 | BUTTONS_BUTTON2 | BUTTONS_BUTTON3 | BUTTONS_BUTTON4 | BUTTONS_BUTTON5 | BUTTONS_BUTTON6 | BUTTONS_BUTTON7 | BUTTONS_BUTTON8)
			#endif

			#define PORTB_MASK 0b01111110
			#define PORTD_MASK 0b00000010
			#define PORTE_MASK 0b01000000
		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static uint8_t debounceB0,debounceB1,debounceB2,debouncedBState;

			static inline void Buttons_Init(void)
			{
				DDRB &= ~PORTB_MASK;
				DDRD &= ~PORTD_MASK;
				DDRE &= ~PORTE_MASK;
				PORTB |= PORTB_MASK;
				PORTD |= PORTD_MASK;
				PORTE |= PORTE_MASK;
			}

			static inline uint8_t Buttons_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Buttons_GetStatus(void)
			{
			    /* Vertical counter: http://www.dattalo.com/technical/software/pic/debounce.html */
			    /* Set delta to changes from last sample */
					uint8_t buttonState = PINB & PORTB_MASK;
					buttonState |= (PIND & PORTD_MASK) >> 1;
					buttonState |= (PINE & PORTE_MASK) << 1;
			    uint8_t delta = ~buttonState ^ debouncedBState;

			    /* Increment vertical counter */
			    debounceB2 = debounceB2 ^ (debounceB1 & debounceB0);
			    debounceB1 = debounceB1 ^ debounceB0;
			    debounceB0  = ~debounceB0;

			    /* reset any unchanged bits */
			    debounceB0 &= delta;
			    debounceB1 &= delta;
			    debounceB2 &= delta;

			    /* update state & calculate returned change set */
			    debouncedBState ^= ~(~delta | debounceB0 | debounceB1 | debounceB2);

				return (uint8_t)debouncedBState;
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */
