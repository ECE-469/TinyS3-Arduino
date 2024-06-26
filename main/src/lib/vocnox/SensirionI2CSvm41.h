/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * I2C-Generator: 0.3.0
 * Yaml Version: 0.7.1
 * Template Version: 0.7.0-92-gb5d271c
 */
/*
 * Copyright (c) 2021, Sensirion AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of Sensirion AG nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SENSIRIONI2CSVM41_H
#define SENSIRIONI2CSVM41_H

#include "Arduino.h"
#include "../sensirion-core/SensirionCore.h"
#include <Wire.h>

class SensirionI2CSvm41
{

public:
  SensirionI2CSvm41();
  /**
   * begin() - Initializes the SensirionI2CSvm41 class.
   *
   * @param i2cBus Arduino stream object to use for communication.
   *
   */
  void begin(TwoWire &i2cBus);

  /**
   * startMeasurement() - Starts continuous measurement in polling mode.
   *
   * @note This command is only available in idle mode.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t startMeasurement(void);

  /**
   * stopMeasurement() - Stops the measurement mode and returns to idle mode.
   *
   * @note This command is only available in measurement mode.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t stopMeasurement(void);

  /**
   * readMeasuredValuesAsIntegers() - Returns the new measurement results as
   * integers.
   *
   * @note This command is only available in measurement mode. The firmware
   * updates the measurement values every second. Polling data with a faster
   * sampling rate will return the same values. The first measurement is
   * available 1 second after the start measurement command is issued. Any
   * readout prior to this will return zero initialized values.
   *
   * @param humidity Compensated ambient humidity in % RH with a scaling
   * factor of 100.
   *
   * @param temperature Compensated ambient temperature in degrees celsius
   * with a scaling of 200.
   *
   * @param vocIndex VOC algorithm output with a scaling value of 10.
   *
   * @param noxIndex NOx algorithm output with a scaling value of 10.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t readMeasuredValuesAsIntegers(int16_t &humidity,
                                        int16_t &temperature,
                                        int16_t &vocIndex, int16_t &noxIndex);

  /**
   * readMeasuredValues() - Returns the new measurement results.
   *
   * @note This command is only available in measurement mode. The firmware
   * updates the measurement values every second. Polling data with a faster
   * sampling rate will return the same values. The first measurement is
   * available 1 second after the start measurement command is issued. Any
   * readout prior to this will return zero initialized values.
   *
   * @param humidity Compensated ambient humidity in % RH.
   *
   * @param temperature Compensated ambient temperature in degrees celsius.
   *
   * @param vocIndex VOC algorithm output.
   *
   * @param noxIndex NOx algorithm output.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t readMeasuredValues(float &humidity, float &temperature,
                              float &vocIndex, float &noxIndex);

  /**
   * readMeasuredRawValues() - Returns the measured raw values.
   *
   * @note This command is only available in measurement mode. The firmware
   * updates the measurement values every second. Polling data with a faster
   * sampling rate will return the same values. The first measurement is
   * available 1 second after the start measurement command is issued. Any
   * readout prior to this will return zero initialized values.
   *
   * @param rawHumidity Uncompensated raw humidity in % RH as read from the
   * SHT40 with a scaling factor of 100.
   *
   * @param rawTemperature Uncompensated raw temperature in degrees celsius as
   * read from the SHT40 with a scaling of 200.
   *
   * @param rawVocTicks Raw VOC output ticks as read from the SGP sensor.
   *
   * @param rawNoxTicks Raw NOx output ticks as read from the SGP sensor.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t readMeasuredRawValues(int16_t &rawHumidity,
                                 int16_t &rawTemperature,
                                 uint16_t &rawVocTicks,
                                 uint16_t &rawNoxTicks);

  /**
   * setTemperatureOffsetForRhtMeasurementsTicks() - Sets the T-Offset for the
   * temperature compensation of the RHT algorithm.
   *
   * @param tOffset Temperature offset in degrees celsius with a scaling of
   * 200.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t setTemperatureOffsetForRhtMeasurementsTicks(int16_t tOffset);

  /**
   * setTemperatureOffsetForRhtMeasurements() - Sets the T-Offset for the
   * temperature compensation of the RHT algorithm.
   *
   * @param tOffset Temperature offset in degrees celsius.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t setTemperatureOffsetForRhtMeasurements(float tOffset);

  /**
   * getTemperatureOffsetForRhtMeasurementsTicks() - Gets the T-Offset for the
   * temperature compensation of the RHT algorithm.
   *
   * @param tOffset Temperature offset in degrees celsius with a scaling of
   * 200.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t getTemperatureOffsetForRhtMeasurementsTicks(int16_t &tOffset);

  /**
   * getTemperatureOffsetForRhtMeasurements() - Gets the T-Offset for the
   * temperature compensation of the RHT algorithm.
   *
   * @param tOffset Temperature offset in degrees celsius.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t getTemperatureOffsetForRhtMeasurements(float &tOffset);

  /**
   * setVocAlgorithmTuningParameters() - Sets the parameters to customize the
   * VOC algorithm. This command is only available in idle mode.
   *
   * @param vocIndexOffset VOC index representing typical (average)
   * conditions. Allowed values are in range 1..250. The default value is 100.
   *
   * @param learningTimeOffsetHours Time constant to estimate the VOC
   * algorithm offset from the history in hours. Past events will be forgotten
   * after about twice the learning time. Allowed values are in range 1..1000.
   * The default value is 12 hours.
   *
   * @param learningTimeGainHours Time constant to estimate the VOC algorithm
   * gain from the history in hours. Past events will be forgotten after about
   * twice the learning time. Allowed values are in range 1..1000. The default
   * value is 12 hours.
   *
   * @param gatingMaxDurationMinutes Maximum duration of gating in minutes
   * (freeze of estimator during high VOC index signal). Set to zero to
   * disable the gating. Allowed values are in range 0..3000. The default
   * value is 180 minutes.
   *
   * @param stdInitial Initial estimate for standard deviation. Lower value
   * boosts events during initial learning period, but may result in larger
   * device-to-device variations. Allowed values are in range 10..5000. The
   * default value is 50.
   *
   * @param gainFactor Gain factor to amplify or to attenuate the VOC index
   * output. Allowed values are in range 1..1000. The default value is 230.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t setVocAlgorithmTuningParameters(int16_t vocIndexOffset,
                                           int16_t learningTimeOffsetHours,
                                           int16_t learningTimeGainHours,
                                           int16_t gatingMaxDurationMinutes,
                                           int16_t stdInitial,
                                           int16_t gainFactor);

  /**
   * getVocAlgorithmTuningParameters() - Gets the currently set parameters for
   * customizing the VOC algorithm
   *
   * @param vocIndexOffset VOC index representing typical (average)
   * conditions.
   *
   * @param learningTimeOffsetHours Time constant to estimate the VOC
   * Algorithm offset from the history in hours. Past events will be forgotten
   * after about twice the learning time.
   *
   * @param learningTimeGainHours Time constant to estimate the VOC Algorithm
   * gain from the history in hours. Past events will be forgotten after about
   * twice the learning time.
   *
   * @param gatingMaxDurationMinutes Maximum duration of gating in minutes
   * (freeze of estimator during high VOC index signal). Zero disables the
   * gating.
   *
   * @param stdInitial Initial estimate for standard deviation. Lower value
   * boosts events during initial learning period, but may result in larger
   * device-to-device variations.
   *
   * @param gainFactor Factor to amplify or to attenuate the VOC Index output.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t getVocAlgorithmTuningParameters(int16_t &vocIndexOffset,
                                           int16_t &learningTimeOffsetHours,
                                           int16_t &learningTimeGainHours,
                                           int16_t &gatingMaxDurationMinutes,
                                           int16_t &stdInitial,
                                           int16_t &gainFactor);

  /**
   * setNoxAlgorithmTuningParameters() - Sets the parameters to customize the
   * NOx algorithm. This command is only available in idle mode.
   *
   * @param noxIndexOffset NOx index representing typical (average)
   * conditions. Allowed values are in range 1..250. The default value is 1.
   *
   * @param learningTimeOffsetHours Time constant to estimate the NOx
   * algorithm offset from the history in hours. Past events will be forgotten
   * after about twice the learning time. Allowed values are in range 1..1000.
   * The default value is 12 hours.
   *
   * @param learningTimeGainHours Time constant to estimate the NOx algorithm
   * gain from the history in hours. Past events will be forgotten after about
   * twice the learning time. Allowed values are in range 1..1000. The default
   * value is 12 hours. Note that this value is not relevant for NOx algorithm
   * type.
   *
   * @param gatingMaxDurationMinutes Maximum duration of gating in minutes
   * (freeze of estimator during high NOx index signal). Set to zero to
   * disable the gating. Allowed values are in range 0..3000. The default
   * value is 720 minutes.
   *
   * @param stdInitial Initial estimate for standard deviation. Lower value
   * boosts events during initial learning period, but may result in larger
   * device-to-device variations. Allowed values are in range 10..5000. The
   * default value is 50. Note that this value is not relevant for NOx
   * algorithm type.
   *
   * @param gainFactor Gain factor to amplify or to attenuate the VOC index
   * output. Allowed values are in range 1..1000. The default value is 230.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t setNoxAlgorithmTuningParameters(int16_t noxIndexOffset,
                                           int16_t learningTimeOffsetHours,
                                           int16_t learningTimeGainHours,
                                           int16_t gatingMaxDurationMinutes,
                                           int16_t stdInitial,
                                           int16_t gainFactor);

  /**
   * getNoxAlgorithmTuningParameters() - Gets the currently set parameters for
   * customizing the NOx algorithm
   *
   * @param noxIndexOffset NOx index representing typical (average)
   * conditions.
   *
   * @param learningTimeOffsetHours Time constant to estimate the NOx
   * Algorithm offset from the history in hours. Past events will be forgotten
   * after about twice the learning time.
   *
   * @param learningTimeGainHours Time constant to estimate the NOx Algorithm
   * gain from the history in hours. Past events will be forgotten after about
   * twice the learning time. Note that this value is not relevant for NOx
   * algorithm type.
   *
   * @param gatingMaxDurationMinutes Maximum duration of gating in minutes
   * (freeze of estimator during high NOx index signal). Zero disables the
   * gating.
   *
   * @param stdInitial Initial estimate for standard deviation. Lower value
   * boosts events during initial learning period, but may result in larger
   * device-to-device variations. Note that this value is not relevant for NOx
   * algorithm type.
   *
   * @param gainFactor Factor to amplify or to attenuate the NOx Index output.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t getNoxAlgorithmTuningParameters(int16_t &noxIndexOffset,
                                           int16_t &learningTimeOffsetHours,
                                           int16_t &learningTimeGainHours,
                                           int16_t &gatingMaxDurationMinutes,
                                           int16_t &stdInitial,
                                           int16_t &gainFactor);

  /**
   * storeNvData() - Stores all algorithm parameters to the non-volatile
   * memory.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t storeNvData(void);

  /**
   * setVocAlgorithmState() - Sets the VOC algorithm state. This command is
   * only available in idle mode.
   *
   * @param state Current VOC algorithm state.
   *
   * @note Retrieved values can only be used after at least 3 hours of
   * continuous operation. Restoring the state by calling set voc state
   * should not be done after interruptions of more than 10 minutes.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t setVocAlgorithmState(const uint8_t state[], uint8_t stateSize);

  /**
   * getVocAlgorithmState() - Gets the current VOC algorithm state.
   *
   * @param state Current VOC algorithm state.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t getVocAlgorithmState(uint8_t state[], uint8_t stateSize);

  /**
   * getVersion() - Gets the version information for the hardware, firmware
   * and protocol.
   *
   * @param firmwareMajor Firmware major version number.
   *
   * @param firmwareMinor Firmware minor version number.
   *
   * @param firmwareDebug Firmware debug state. If the debug state is set, the
   * firmware is in development.
   *
   * @param hardwareMajor Hardware major version number.
   *
   * @param hardwareMinor Hardware minor version number.
   *
   * @param protocolMajor Protocol major version number.
   *
   * @param protocolMinor Protocol minor version number.
   *
   * @param padding Padding byte, ignore this.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t getVersion(uint8_t &firmwareMajor, uint8_t &firmwareMinor,
                      bool &firmwareDebug, uint8_t &hardwareMajor,
                      uint8_t &hardwareMinor, uint8_t &protocolMajor,
                      uint8_t &protocolMinor);

  /**
   * getSerialNumber() - Gets the serial number from the device.
   *
   * @param serialNumber Ascii string containing the serial number. The string
   * has the null-termination character included.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t getSerialNumber(unsigned char serialNumber[],
                           uint8_t serialNumberSize);

  /**
   * deviceReset() - Executs a reset on the device.
   *
   * @note The device will reply before executing the reset.
   *
   * @return 0 on success, an error code otherwise
   */
  uint16_t deviceReset(void);

private:
  TwoWire *_i2cBus = nullptr;
};

#endif /* SENSIRIONI2CSVM41_H */
