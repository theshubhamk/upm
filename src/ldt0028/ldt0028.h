/*
 * Author: Noel Eck <noel.eck@intel.com>
 * Copyright (c) 2015 Intel Corporation.
 *
 * This program and the accompanying materials are made available under the
 * terms of the The MIT License which is available at
 * https://opensource.org/licenses/MIT.
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include "upm.h"
#include "mraa/aio.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file ldt0028.h
 * @library ldt0028
 * @brief C API for the LDT0-028 Piezo Vibration Sensor
 *
 * @include ldt0028.c
 */

/**
 * driver context
 */
typedef struct _ldt0028_context {
    /* mraa aio pin context */
    mraa_aio_context aio;
    /* Analog voltage reference */
    float m_aRef;
    /* Scale */
    float m_scale;
    /* Offset in sensor units */
    float m_offset;
} *ldt0028_context;

/**
 * Initialize analog sensor
 * @param pin Analog pin
 * @return sensor context
 */
ldt0028_context ldt0028_init(int16_t pin);

/**
 * Analog sensor destructor
 * @param sensor context pointer
 */
void ldt0028_close(ldt0028_context dev);

/**
 * Set ADC reference voltage
 * @param dev sensor context pointer
 * @param aref ADC reference voltage
 * @return Function result code
 */
upm_result_t ldt0028_set_aref(const ldt0028_context dev, float aref);

/**
 * Set sensor scale.  This scale is applied to the return value:
 *     counts = counts * scale
 * @param dev sensor context pointer
 * @param scale count scale value used
 * @return Function result code
 */
upm_result_t ldt0028_set_scale(const ldt0028_context dev, float scale);

/**
 * Set sensor offset.  This offset is applied to the return value:
 *     value = value + offset
 * @param dev sensor context pointer
 * @param offset count offset value used
 * @return Function result code
 */
upm_result_t ldt0028_set_offset(const ldt0028_context dev, float offset);

/**
 * Get sensor aref
 * @param dev sensor context pointer
 * @return Sensor ADC reference voltage
 */
float ldt0028_get_aref(const ldt0028_context dev);

/**
 * Get sensor scale
 * @param dev sensor context pointer
 * @return Sensor scale
 */
float ldt0028_get_scale(const ldt0028_context dev);

/**
 * Get sensor offset
 * @param dev sensor context pointer
 * @return Sensor offset
 */
float ldt0028_get_offset(const ldt0028_context dev);

/**
 * Read normalized value for sensor
 * @param dev sensor context pointer
 * @param *value Normalized value (0.0 -> 1.0)
 * @return Function result code
 */
upm_result_t ldt0028_get_normalized(const ldt0028_context dev, float *value);

/**
 * Read raw voltage from the sensor
 * @param dev sensor context pointer
 * @param *value Raw sensor voltage
 * @return Function result code
 */
upm_result_t ldt0028_get_raw_volts(const ldt0028_context dev, float *value);

/**
 * Read scaled/offset voltage from the sensor
 * @param dev sensor context pointer
 * @param *value Adjusted sensor voltage
 * @return Function result code
 */
upm_result_t ldt0028_get_volts(const ldt0028_context dev, float *value);
#ifdef __cplusplus
}
#endif
