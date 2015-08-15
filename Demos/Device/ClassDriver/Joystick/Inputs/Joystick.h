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
  Driver for a 4-direction joystick on PORTC
*/

#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Mask for the joystick being pushed in the left direction. */
			#define JOY_LEFT                  (1 << 4)

			/** Mask for the joystick being pushed in the upward direction. */
			#define JOY_UP                    (1 << 5)

			/** Mask for the joystick being pushed in the right direction. */
			#define JOY_RIGHT                 (1 << 6)

			/** Mask for the joystick being pushed in the downward direction. */
			#define JOY_DOWN                  (1 << 7)

			/* Private Interface - For use in library only: */
			#if !defined(__DOXYGEN__)
				/* Macros: */
				#define JOY_MASK                 (JOY_LEFT | JOY_UP | JOY_RIGHT | JOY_DOWN)
			#endif

		/* Inline Functions: */
		#if !defined(__DOXYGEN__)
			static inline void Joystick_Init(void)
			{
				DDRC  &= ~JOY_MASK;
				PORTC |= JOY_MASK;
			}

			static inline uint8_t Joystick_GetStatus(void) ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Joystick_GetStatus(void)
			{
				return (uint8_t)(~PINC & JOY_MASK);
			}
		#endif

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

