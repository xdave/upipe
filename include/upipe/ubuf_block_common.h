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
 * @short Upipe useful common definitions for block managers
 */

#ifndef _UPIPE_UBUF_BLOCK_COMMON_H_
/** @hidden */
#define _UPIPE_UBUF_BLOCK_COMMON_H_
#ifdef __cplusplus
extern "C" {
#endif

#include <upipe/ubuf.h>
#include <upipe/ubuf_block.h>

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

/** @This initializes common sections of a block ubuf.
 *
 * @param ubuf pointer to ubuf
 * @param bool true if UBUF_MAP_BLOCK & UBUF_UNMAP_BLOCK need to be called
 * @return pointer to ubuf or NULL in case of failure
 */
static inline void ubuf_block_common_init(struct ubuf *ubuf, bool map)
{
    struct ubuf_block *block = ubuf_block_from_ubuf(ubuf);
    block->offset = 0;
    block->size = 0;
    block->next_ubuf = NULL;
    block->total_size = 0;

    block->map = map;
    block->buffer = NULL;

    block->cached_ubuf = ubuf;
    block->cached_offset = 0;
    uchain_init(&ubuf->uchain);
}

/** @internal @This sets the members of the block structure for block ubuf.
 *
 * @param ubuf pointer to ubuf
 * @param offset new offset
 * @param size new size
 */
static inline void ubuf_block_common_set(struct ubuf *ubuf, size_t offset,
                                         size_t size)
{
    struct ubuf_block *block = ubuf_block_from_ubuf(ubuf);
    block->offset = offset;
    block->total_size += size - block->size;
    block->size = size;
}

/** @internal @This sets the buffer member of the block structure for block
 * ubuf.
 *
 * @param buffer optional pointer to the buffer
 */
static inline void ubuf_block_common_set_buffer(struct ubuf *ubuf,
                                                uint8_t *buffer)
{
    struct ubuf_block *block = ubuf_block_from_ubuf(ubuf);
    block->buffer = buffer;
}

/** @This duplicates common sections of a block ubuf, and duplicates other
 * segments.
 *
 * @param ubuf pointer to ubuf
 * @param new_ubuf pointer to ubuf to overwrite
 * @return false in case of error
 */
static inline bool ubuf_block_common_dup(struct ubuf *ubuf,
                                         struct ubuf *new_ubuf)
{
    struct ubuf_block *block = ubuf_block_from_ubuf(ubuf);
    struct ubuf_block *new_block = ubuf_block_from_ubuf(new_ubuf);
    new_block->offset = block->offset;
    new_block->size = block->size;
    new_block->total_size = block->total_size;
    new_block->buffer = block->buffer;
    if (block->next_ubuf != NULL)
        if (unlikely((new_block->next_ubuf = ubuf_dup(block->next_ubuf))
                       == NULL))
            return false;
    new_block->cached_ubuf = new_ubuf;
    new_block->cached_offset = 0;
    return true;
}

/** @This duplicates common sections of a block ubuf, and duplicates part of
 * other segments.
 *
 * @param ubuf pointer to ubuf
 * @param new_ubuf pointer to ubuf to overwrite
 * @param offset offset in the buffer
 * @param size final size of the buffer
 * @return false in case of error
 */
static inline bool ubuf_block_common_splice(struct ubuf *ubuf,
                                            struct ubuf *new_ubuf, int offset,
                                            int size)
{
    struct ubuf_block *block = ubuf_block_from_ubuf(ubuf);
    struct ubuf_block *new_block = ubuf_block_from_ubuf(new_ubuf);
    assert(offset < block->size);
    new_block->offset = block->offset + offset;
    new_block->size = block->size - offset;
    if (new_block->size > size)
        new_block->size = size;
    new_block->total_size = size;
    new_block->buffer = block->buffer;
    size -= new_block->size;

    if (size > 0) {
        assert(block->next_ubuf != NULL);
        if (unlikely((new_block->next_ubuf = ubuf_block_splice(block->next_ubuf,
                                                          0, size)) == NULL))
            return false;
    }
    new_block->cached_ubuf = new_ubuf;
    new_block->cached_offset = 0;
    return true;
}

/** @internal @This frees the ubuf containg the next segments of the current
 * ubuf.
 *
 * @param ubuf pointer to ubuf
 */
static inline void ubuf_block_common_clean(struct ubuf *ubuf)
{
    struct ubuf_block *block = ubuf_block_from_ubuf(ubuf);
    if (block->next_ubuf != NULL)
        ubuf_free(block->next_ubuf);
}

#ifdef __cplusplus
}
#endif
#endif
