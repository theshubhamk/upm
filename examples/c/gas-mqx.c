/*
 * Author: Noel Eck <noel.eck@intel.com>
 * Copyright (c) 2016 Intel Corporation.
 *
 * This program and the accompanying materials are made available under the
 * terms of the The MIT License which is available at
 * https://opensource.org/licenses/MIT.
 *
 * SPDX-License-Identifier: MIT
 */

#include <unistd.h>
#include <signal.h>

#include "mqx.h"
#include "upm_utilities.h"

bool shouldRun = true;

void sig_handler(int signo)
{
    if (signo == SIGINT)
        shouldRun = false;
}

int main()
{
    signal(SIGINT, sig_handler);

    //! [Interesting]

    // Instantiate a mqx sensor on analog pin A0
    mqx_context sensor = mqx_init(0);

    if (!sensor)
    {
        printf("mqx_init() failed.\n");
        return -1;
    }

    // Set the aref, scale, and offset
    mqx_set_aref(sensor, 5.0);
    mqx_set_scale(sensor, 1.0);
    mqx_set_offset(sensor, -.1);
    printf("aRef: %0.03f scale: %0.03f offset: %0.03f\n\n",
            mqx_get_aref(sensor),
            mqx_get_scale(sensor),
            mqx_get_offset(sensor));

    // Every half a second, sample the sensor output
    while (shouldRun)
    {
        float normalized = 0.0;
        float raw_volts = 0.0;
        float volts = 0.0;

        mqx_get_normalized(sensor, &normalized);
        mqx_get_raw_volts(sensor, &raw_volts);
        mqx_get_volts(sensor, &volts);

        printf("Normalized output: %0.03f, raw mqx sensor output: %0.03f v "
                "adjusted output: %0.03f v\n", normalized, raw_volts, volts);

        upm_delay_ms(500);
    }

    //! [Interesting]

    printf("Exiting\n");

    mqx_close(sensor);

    return 0;
}
