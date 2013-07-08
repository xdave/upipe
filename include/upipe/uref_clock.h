/*
 * Copyright (C) 2012-2013 OpenHeadend S.A.R.L.
 *
 * Authors: Christophe Massiot
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/** @file
 * @short Upipe clock attributes for uref
 */

#ifndef _UPIPE_UREF_CLOCK_H_
/** @hidden */
#define _UPIPE_UREF_CLOCK_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <upipe/uref.h>
#include <upipe/uref_attr.h>

#include <stdint.h>

UREF_ATTR_UNSIGNED_UREF(clock, systime, systime, reception time in system clock)
UREF_ATTR_UNSIGNED_UREF(clock, systime_rap, systime_rap,
        reception time in system clock of the last random access point)
UREF_ATTR_UNSIGNED_UREF(clock, pts, pts, presentation timestamp in Upipe clock)
UREF_ATTR_UNSIGNED_UREF(clock, pts_orig, pts_orig,
        original presentation timestamp in stream clock)
UREF_ATTR_UNSIGNED_UREF(clock, pts_sys, pts_sys,
        presentation timestamp in system clock)
UREF_ATTR_UNSIGNED_UREF(clock, dts, dts, decoding timestamp in Upipe clock)
UREF_ATTR_UNSIGNED_UREF(clock, dts_orig, dts_orig,
        original decoding timestamp in stream clock)
UREF_ATTR_UNSIGNED_UREF(clock, dts_sys, dts_sys,
        decoding timestamp in system clock)
UREF_ATTR_UNSIGNED_SH(clock, vbv_delay, UDICT_TYPE_CLOCK_VBVDELAY,
        vbv/dts delay)
UREF_ATTR_UNSIGNED_SH(clock, duration, UDICT_TYPE_CLOCK_DURATION, duration)
UREF_ATTR_SMALL_UNSIGNED(clock, index_rap, "k.index_rap",
                    frame offset from last random access point)
UREF_ATTR_RATIONAL(clock, rate, "k.rate", playing rate)


#ifdef __cplusplus
}
#endif
#endif
