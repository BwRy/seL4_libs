/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <stdio.h> /* For fprintf() */
#include <stdlib.h> /* For abort() */
#include <assert.h>
#include <sel4/sel4.h>
#include <sel4debug/sel4_debug.h>
#include <utils/stringify.h>

char *sel4_errlist[] = {
    [seL4_NoError] = STRINGIFY(seL4_NoError),
    [seL4_InvalidArgument] = STRINGIFY(seL4_InvalidArgument),
    [seL4_InvalidCapability] = STRINGIFY(seL4_InvalidCapability),
    [seL4_IllegalOperation] = STRINGIFY(seL4_IllegalOperation),
    [seL4_RangeError] = STRINGIFY(seL4_RangeError),
    [seL4_AlignmentError] = STRINGIFY(seL4_AlignmentError),
    [seL4_FailedLookup] = STRINGIFY(seL4_FailedLookup),
    [seL4_TruncatedMessage] = STRINGIFY(seL4_TruncatedMessage),
    [seL4_DeleteFirst] = STRINGIFY(seL4_DeleteFirst),
    [seL4_RevokeFirst] = STRINGIFY(seL4_RevokeFirst),
    [seL4_NotEnoughMemory] = STRINGIFY(seL4_NotEnoughMemory),
    NULL
};

const char *
sel4_strerror(int errcode)
{
    assert(errcode < sizeof(sel4_errlist) / sizeof(*sel4_errlist) - 1);
    return sel4_errlist[errcode];
}

void
__sel4_error(int sel4_error, const char *file,
             const char *function, int line, char * str)
{
    fprintf(stderr, "seL4 Error: %s, function %s, file %s, line %d: %s\n",
            sel4_errlist[sel4_error],
            function, file, line, str);
    abort();
}
