/*! @file correlation.h
 *  @brief Defines functions to calculate cross-correlation.
 *  @author Markovtsev Vadim <v.markovtsev@samsung.com>
 *  @version 1.0
 *
 *  @section Notes
 *  This code partially conforms to <a href="http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml">Google C++ Style Guide</a>.
 *
 *  @section Copyright
 *  Copyright © 2013 Samsung R&D Institute Russia
 *
 *  @section License
 *  Licensed to the Apache Software Foundation (ASF) under one
 *  or more contributor license agreements.  See the NOTICE file
 *  distributed with this work for additional information
 *  regarding copyright ownership.  The ASF licenses this file
 *  to you under the Apache License, Version 2.0 (the
 *  "License"); you may not use this file except in compliance
 *  with the License.  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing,
 *  software distributed under the License is distributed on an
 *  "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, either express or implied.  See the License for the
 *  specific language governing permissions and limitations
 *  under the License.
 */

#ifndef INC_SIMD_CORRELATE_H_
#define INC_SIMD_CORRELATE_H_

#include <stddef.h>
#include <simd/common.h>
#include <simd/attributes.h>
#include <simd/convolve_structs.h>

SIMD_API_BEGIN

typedef struct ConvolutionFFTHandle CrossCorrelationFFTHandle;

/// @brief Prepares for the calculation of cross-correlation of two signals
/// using the FFT method.
/// @param xLength The length of the first array in float-s.
/// @param hLength The length of the second array in float-s.
/// @return The handle for cross_correlate_fft().
CrossCorrelationFFTHandle cross_correlate_fft_initialize(size_t xLength,
                                                         size_t hLength);

/// @brief Calculates the cross-correlation of two signals using
/// the FFT method.
/// @param handle The structure obtained from cross_correlate_fft_initialize().
/// @param x The first signal (long one).
/// @param h The second signal (short one).
/// @param result The resulting signal of length xLength + hLength - 1.
/// @note result and x may be the same arrays.
void cross_correlate_fft(CrossCorrelationFFTHandle handle,
                         const float *x, const float *h,
                         float *result) NOTNULL(2, 3, 4);

/// @brief Frees any resources allocated by cross_correlate_fft_initialize().
/// @param handle The structure obtained from cross_correlate_fft_initialize().
void cross_correlate_fft_finalize(CrossCorrelationFFTHandle handle);

typedef struct ConvolutionOverlapSaveHandle CrossCorrelationOverlapSaveHandle;

/// @brief Prepares for the calculation of cross-correlation of two signals
/// using the overlap-save method.
/// @param xLength The length of the first array in float-s.
/// @param hLength The length of the second array in float-s.
/// @return The handle for cross_correlate_overlap_save().
CrossCorrelationOverlapSaveHandle cross_correlate_overlap_save_initialize(
    size_t xLength, size_t hLength);

/// @brief Calculates the cross-correlation of two signals using
/// the overlap-save method.
/// @param handle The structure obtained from
/// cross_correlate_overlap_save_initialize().
/// @param x The first signal (long one).
/// @param h The second signal (short one).
/// @param result The resulting signal of length xLength + hLength - 1.
/// @note result and x may be the same arrays.
void cross_correlate_overlap_save(CrossCorrelationOverlapSaveHandle handle,
                                  const float *__restrict x,
                                  const float *__restrict h,
                                  float *result) NOTNULL(2, 3, 4);

/// @brief Frees any resources allocated by
/// cross_correlate_overlap_save_initialize().
/// @param handle The structure obtained from
/// cross_correlate_overlap_save_initialize().
void cross_correlate_overlap_save_finalize(
    CrossCorrelationOverlapSaveHandle handle);

/// @brief Calculates the cross-correlation of two signals using
/// the "brute force" method.
/// @param simd Value indicating whether to use SIMD acceleration or not.
/// @param x The first signal (long one).
/// @param xLength The length of the first array in float-s.
/// @param h The second signal (short one).
/// @param hLength The length of the second array in float-s.
/// @param result The resulting signal of length xLength + hLength - 1.
/// @note result, x and h may NOT be the same arrays.
void cross_correlate_simd(int simd,
                          const float *__restrict x, size_t xLength,
                          const float *__restrict h, size_t hLength,
                          float *__restrict result) NOTNULL(2, 4, 6);

typedef struct ConvolutionHandle CrossCorrelationHandle;

/// @brief Prepares for the calculation of cross-correlation of
/// two signals using the best method.
/// @param xLength The length of the first array in float-s.
/// @param hLength The length of the second array in float-s.
/// @return The handle for cross_correlate().
CrossCorrelationHandle cross_correlate_initialize(size_t xLength,
                                                  size_t hLength);

/// @brief Calculates the cross-correlation of two signals using
/// the best method.
/// @param handle The structure obtained from cross_correlate_initialize().
/// @param x The first signal (long one).
/// @param h The second signal (short one).
/// @param result The resulting signal of length xLength + hLength - 1.
/// @note result, x and h may NOT be the same arrays.
void cross_correlate(CrossCorrelationHandle handle,
                     const float *__restrict x, const float *__restrict h,
                     float *__restrict result) NOTNULL(2, 3, 4);

/// @brief Frees any resources allocated by
/// cross_correlate_overlap_initialize().
/// @param handle The structure obtained from
/// cross_correlate_overlap_initialize().
void cross_correlate_finalize(CrossCorrelationHandle handle);

SIMD_API_END

#endif  // INC_SIMD_CORRELATE_H_
