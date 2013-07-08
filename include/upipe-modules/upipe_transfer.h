/*
 * Copyright (C) 2013 OpenHeadend S.A.R.L.
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
 * @short Upipe module allowing to transfer other pipes to a remote event loop
 * This is particularly helpful for multithreaded applications.
 */

#ifndef _UPIPE_MODULES_UPIPE_TRANSFER_H_
/** @hidden */
#define _UPIPE_MODULES_UPIPE_TRANSFER_H_

#include <upipe/upipe.h>

#define UPIPE_XFER_SIGNATURE UBASE_FOURCC('x','f','e','r')

/** @This returns a management structure for xfer pipes. You would need one
 * management structure per target event loop (upump manager). The management
 * structure can be allocated in any thread, but must be attached in the
 * same thread as the one running the upump manager.
 *
 * @param queue_length maximum length of the internal queue of commands
 * @param msg_pool_depth maximum number of messages in the pool
 * @return pointer to manager
 */
struct upipe_mgr *upipe_xfer_mgr_alloc(uint8_t queue_length,
                                       uint16_t msg_pool_depth);

/** @This instructs an existing manager to release all structures
 * currently kept in pools. It is intended as a debug tool only.
 *
 * @param mgr pointer to a upipe manager
 */
void upipe_xfer_mgr_vacuum(struct upipe_mgr *mgr);

/** @This attaches a upipe_xfer_mgr to a given event loop. The xfer manager
 * will call upump_alloc_XXX and upump_start, so it must be done in a context
 * where it is possible, which generally means that this command is done in
 * the same thread that runs the event loop (upump managers aren't generally
 * thread-safe).
 *
 * @param mgr xfer_mgr structure
 * @param upump_mgr event loop to attach
 * @return false in case of error
 */
bool upipe_xfer_mgr_attach(struct upipe_mgr *mgr, struct upump_mgr *upump_mgr);

/** @This detaches a upipe_xfer_mgr from an event loop. This call is thread-safe
 * and may be performed from any thread. The manager cannot be reattached
 * to another thread afterwards.
 *
 * @param mgr xfer_mgr structure
 * @return false in case of error
 */
bool upipe_xfer_mgr_detach(struct upipe_mgr *mgr);

/** @This allocates and initializes an xfer pipe. An xfer pipe allows to
 * transfer an existing pipe to a remote upump_mgr. The xfer pipe is then
 * used to remotely release the transferred pipe.
 *
 * @param mgr management structure for queue source type
 * @param uprobe structure used to raise events
 * @param upipe_remote pipe to transfer to remote upump_mgr
 * @return pointer to allocated pipe, or NULL in case of failure
 */
static inline struct upipe *upipe_xfer_alloc(struct upipe_mgr *mgr,
                                             struct uprobe *uprobe,
                                             struct upipe *upipe_remote)
{
    return upipe_alloc(mgr, uprobe, UPIPE_XFER_SIGNATURE, upipe_remote);
}

#endif