/*
 * Copyright 2014, NICTA
 *
 * This software may be distributed and modified according to the terms of
 * the BSD 2-Clause license. Note that NO WARRANTY is provided.
 * See "LICENSE_BSD2.txt" for details.
 *
 * @TAG(NICTA_BSD)
 */

#include <autoconf.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sel4platsupport/timer.h>
#include <sel4platsupport/plat/timer.h>
#include <platsupport/mach/pwm.h>
#include <utils/util.h>
#include "../../timer_common.h"

seL4_timer_t *
sel4platsupport_get_pwm(vspace_t *vspace, simple_t *simple, vka_t *vka, seL4_CPtr notification)
{

    seL4_timer_t *timer = calloc(1, sizeof(seL4_timer_t));
    if (timer == NULL) {
        ZF_LOGE("Failed to allocate object of size %u\n", sizeof(seL4_timer_t));
        goto error;
    }

    timer_common_data_t *data = timer_common_init(vspace, simple, vka, notification, PWM_T4_INTERRUPT,
                                                  (void *) PWM_TIMER_PADDR);
    timer->data = data;

    if (timer->data == NULL) {
        goto error;
    }

    timer->handle_irq = timer_common_handle_irq;
    timer->destroy = timer_common_destroy;

    /* do hardware init */
    pwm_config_t config = {
        .vaddr = data->vaddr,
    };

    timer->timer = pwm_get_timer(&config);
    if (timer->timer == NULL) {
        goto error;
    }

    /* success */
    return timer;
error:
    if (timer != NULL) {
        timer_common_destroy(timer, vka, vspace);
    }

    return NULL;
}
