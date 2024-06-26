/*
 * THIS FILE IS AUTOMATICALLY GENERATED
 *
 * I2C-Generator: 0.3.0
 * Yaml Version: 0.7.1
 * Template Version: 0.7.0-84-g1150250
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

#include "SensirionI2CSvm41.h"

#define SVM41_I2C_ADDRESS 0x6A

SensirionI2CSvm41::SensirionI2CSvm41()
{
}

void SensirionI2CSvm41::begin(TwoWire &i2cBus)
{
    _i2cBus = &i2cBus;
}

uint16_t SensirionI2CSvm41::startMeasurement()
{
    uint16_t error = 0;
    uint8_t buffer[2];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x10, buffer, 2);

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    delay(1);
    return error;
}

uint16_t SensirionI2CSvm41::stopMeasurement()
{
    uint16_t error = 0;
    uint8_t buffer[2];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x104, buffer, 2);

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    delay(50);
    return error;
}

uint16_t SensirionI2CSvm41::readMeasuredValuesAsIntegers(int16_t &humidity,
                                                         int16_t &temperature,
                                                         int16_t &vocIndex,
                                                         int16_t &noxIndex)
{
    uint16_t error = 0;
    uint8_t buffer[12];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x405, buffer, 12);

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    if (error)
    {
        return error;
    }

    delay(50);

    SensirionI2CRxFrame rxFrame(buffer, 12);
    error = SensirionI2CCommunication::receiveFrame(SVM41_I2C_ADDRESS, 12,
                                                    rxFrame, *_i2cBus);
    if (error)
    {
        return error;
    }

    error |= rxFrame.getInt16(humidity);
    error |= rxFrame.getInt16(temperature);
    error |= rxFrame.getInt16(vocIndex);
    error |= rxFrame.getInt16(noxIndex);
    return error;
}

uint16_t SensirionI2CSvm41::readMeasuredValues(float &humidity,
                                               float &temperature,
                                               float &vocIndex,
                                               float &noxIndex)
{
    uint16_t error;
    int16_t humidityTicks;
    int16_t temperatureTicks;
    int16_t vocTicks;
    int16_t noxTicks;

    error = readMeasuredValuesAsIntegers(humidityTicks, temperatureTicks,
                                         vocTicks, noxTicks);
    if (error)
    {
        return error;
    }

    humidity = static_cast<float>(humidityTicks) / 100.0f;
    temperature = static_cast<float>(temperatureTicks) / 200.0f;
    vocIndex = static_cast<float>(vocTicks) / 10.0f;
    noxIndex = static_cast<float>(noxTicks) / 10.0f;
    return NoError;
}

uint16_t SensirionI2CSvm41::readMeasuredRawValues(int16_t &rawHumidity,
                                                  int16_t &rawTemperature,
                                                  uint16_t &rawVocTicks,
                                                  uint16_t &rawNoxTicks)
{
    uint16_t error = 0;
    uint8_t buffer[12];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x3D2, buffer, 12);

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    if (error)
    {
        return error;
    }

    delay(50);

    SensirionI2CRxFrame rxFrame(buffer, 12);
    error = SensirionI2CCommunication::receiveFrame(SVM41_I2C_ADDRESS, 12,
                                                    rxFrame, *_i2cBus);
    if (error)
    {
        return error;
    }

    error |= rxFrame.getInt16(rawHumidity);
    error |= rxFrame.getInt16(rawTemperature);
    error |= rxFrame.getUInt16(rawVocTicks);
    error |= rxFrame.getUInt16(rawNoxTicks);
    return error;
}

uint16_t SensirionI2CSvm41::setTemperatureOffsetForRhtMeasurementsTicks(
    int16_t tOffset)
{
    uint16_t error = 0;
    uint8_t buffer[5];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x6014, buffer, 5);

    error |= txFrame.addInt16(tOffset);

    if (error)
    {
        return error;
    }

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    delay(10);
    return error;
}

uint16_t
SensirionI2CSvm41::setTemperatureOffsetForRhtMeasurements(float tOffset)
{
    int16_t tOffsetTicks = static_cast<int16_t>(tOffset * 200.0f);
    return setTemperatureOffsetForRhtMeasurementsTicks(tOffsetTicks);
}

uint16_t SensirionI2CSvm41::getTemperatureOffsetForRhtMeasurementsTicks(
    int16_t &tOffset)
{
    uint16_t error = 0;
    uint8_t buffer[3];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x6014, buffer, 3);

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    if (error)
    {
        return error;
    }

    delay(1);

    SensirionI2CRxFrame rxFrame(buffer, 3);
    error = SensirionI2CCommunication::receiveFrame(SVM41_I2C_ADDRESS, 3,
                                                    rxFrame, *_i2cBus);
    if (error)
    {
        return error;
    }

    error |= rxFrame.getInt16(tOffset);
    return error;
}

uint16_t
SensirionI2CSvm41::getTemperatureOffsetForRhtMeasurements(float &tOffset)
{
    uint16_t error;
    int16_t tOffsetTicks;

    error = getTemperatureOffsetForRhtMeasurementsTicks(tOffsetTicks);
    if (error)
    {
        return error;
    }

    tOffset = static_cast<float>(tOffsetTicks) / 200.0f;
    return NoError;
}

uint16_t SensirionI2CSvm41::setVocAlgorithmTuningParameters(
    int16_t vocIndexOffset, int16_t learningTimeOffsetHours,
    int16_t learningTimeGainHours, int16_t gatingMaxDurationMinutes,
    int16_t stdInitial, int16_t gainFactor)
{
    uint16_t error = 0;
    uint8_t buffer[20];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x60D0, buffer, 20);

    error |= txFrame.addInt16(vocIndexOffset);
    error |= txFrame.addInt16(learningTimeOffsetHours);
    error |= txFrame.addInt16(learningTimeGainHours);
    error |= txFrame.addInt16(gatingMaxDurationMinutes);
    error |= txFrame.addInt16(stdInitial);
    error |= txFrame.addInt16(gainFactor);

    if (error)
    {
        return error;
    }

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    delay(50);
    return error;
}

uint16_t SensirionI2CSvm41::getVocAlgorithmTuningParameters(
    int16_t &vocIndexOffset, int16_t &learningTimeOffsetHours,
    int16_t &learningTimeGainHours, int16_t &gatingMaxDurationMinutes,
    int16_t &stdInitial, int16_t &gainFactor)
{
    uint16_t error = 0;
    uint8_t buffer[18];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x60D0, buffer, 18);

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    if (error)
    {
        return error;
    }

    delay(50);

    SensirionI2CRxFrame rxFrame(buffer, 18);
    error = SensirionI2CCommunication::receiveFrame(SVM41_I2C_ADDRESS, 18,
                                                    rxFrame, *_i2cBus);
    if (error)
    {
        return error;
    }

    error |= rxFrame.getInt16(vocIndexOffset);
    error |= rxFrame.getInt16(learningTimeOffsetHours);
    error |= rxFrame.getInt16(learningTimeGainHours);
    error |= rxFrame.getInt16(gatingMaxDurationMinutes);
    error |= rxFrame.getInt16(stdInitial);
    error |= rxFrame.getInt16(gainFactor);
    return error;
}

uint16_t SensirionI2CSvm41::setNoxAlgorithmTuningParameters(
    int16_t noxIndexOffset, int16_t learningTimeOffsetHours,
    int16_t learningTimeGainHours, int16_t gatingMaxDurationMinutes,
    int16_t stdInitial, int16_t gainFactor)
{
    uint16_t error = 0;
    uint8_t buffer[20];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x60E1, buffer, 20);

    error |= txFrame.addInt16(noxIndexOffset);
    error |= txFrame.addInt16(learningTimeOffsetHours);
    error |= txFrame.addInt16(learningTimeGainHours);
    error |= txFrame.addInt16(gatingMaxDurationMinutes);
    error |= txFrame.addInt16(stdInitial);
    error |= txFrame.addInt16(gainFactor);

    if (error)
    {
        return error;
    }

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    delay(50);
    return error;
}

uint16_t SensirionI2CSvm41::getNoxAlgorithmTuningParameters(
    int16_t &noxIndexOffset, int16_t &learningTimeOffsetHours,
    int16_t &learningTimeGainHours, int16_t &gatingMaxDurationMinutes,
    int16_t &stdInitial, int16_t &gainFactor)
{
    uint16_t error = 0;
    uint8_t buffer[18];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x60E1, buffer, 18);

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    if (error)
    {
        return error;
    }

    delay(50);

    SensirionI2CRxFrame rxFrame(buffer, 18);
    error = SensirionI2CCommunication::receiveFrame(SVM41_I2C_ADDRESS, 18,
                                                    rxFrame, *_i2cBus);
    if (error)
    {
        return error;
    }

    error |= rxFrame.getInt16(noxIndexOffset);
    error |= rxFrame.getInt16(learningTimeOffsetHours);
    error |= rxFrame.getInt16(learningTimeGainHours);
    error |= rxFrame.getInt16(gatingMaxDurationMinutes);
    error |= rxFrame.getInt16(stdInitial);
    error |= rxFrame.getInt16(gainFactor);
    return error;
}

uint16_t SensirionI2CSvm41::storeNvData()
{
    uint16_t error = 0;
    uint8_t buffer[2];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x6002, buffer, 2);

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    delay(500);
    return error;
}

uint16_t SensirionI2CSvm41::setVocAlgorithmState(const uint8_t state[],
                                                 uint8_t stateSize)
{
    uint16_t error = 0;
    uint8_t buffer[14];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x6181, buffer, 14);

    error |= txFrame.addBytes(state, stateSize);

    if (error)
    {
        return error;
    }

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    delay(50);
    return error;
}

uint16_t SensirionI2CSvm41::getVocAlgorithmState(uint8_t state[],
                                                 uint8_t stateSize)
{
    uint16_t error = 0;
    uint8_t buffer[12];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0x6181, buffer, 12);

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    if (error)
    {
        return error;
    }

    delay(50);

    SensirionI2CRxFrame rxFrame(buffer, 12);
    error = SensirionI2CCommunication::receiveFrame(SVM41_I2C_ADDRESS, 12,
                                                    rxFrame, *_i2cBus);
    if (error)
    {
        return error;
    }

    error |= rxFrame.getBytes(state, stateSize);
    return error;
}

uint16_t
SensirionI2CSvm41::getVersion(uint8_t &firmwareMajor, uint8_t &firmwareMinor,
                              bool &firmwareDebug, uint8_t &hardwareMajor,
                              uint8_t &hardwareMinor, uint8_t &protocolMajor,
                              uint8_t &protocolMinor)
{
    uint16_t error = 0;
    uint8_t buffer[12];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0xD100, buffer, 12);

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    if (error)
    {
        return error;
    }

    delay(1);

    SensirionI2CRxFrame rxFrame(buffer, 12);
    error = SensirionI2CCommunication::receiveFrame(SVM41_I2C_ADDRESS, 12,
                                                    rxFrame, *_i2cBus);
    if (error)
    {
        return error;
    }

    error |= rxFrame.getUInt8(firmwareMajor);
    error |= rxFrame.getUInt8(firmwareMinor);
    error |= rxFrame.getBool(firmwareDebug);
    error |= rxFrame.getUInt8(hardwareMajor);
    error |= rxFrame.getUInt8(hardwareMinor);
    error |= rxFrame.getUInt8(protocolMajor);
    error |= rxFrame.getUInt8(protocolMinor);
    uint8_t padding;
    error |= rxFrame.getUInt8(padding); // remove padding
    return error;
}

uint16_t SensirionI2CSvm41::getSerialNumber(unsigned char serialNumber[],
                                            uint8_t serialNumberSize)
{
    uint16_t error = 0;
    uint8_t buffer[39];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0xD033, buffer, 39);

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    if (error)
    {
        return error;
    }

    delay(1);

    SensirionI2CRxFrame rxFrame(buffer, 39);
    error = SensirionI2CCommunication::receiveFrame(SVM41_I2C_ADDRESS, 39,
                                                    rxFrame, *_i2cBus);
    if (error)
    {
        return error;
    }

    error |= rxFrame.getBytes(serialNumber, serialNumberSize);
    return error;
}

uint16_t SensirionI2CSvm41::deviceReset()
{
    uint16_t error = 0;
    uint8_t buffer[2];
    SensirionI2CTxFrame txFrame =
        SensirionI2CTxFrame::createWithUInt16Command(0xD304, buffer, 2);

    error = SensirionI2CCommunication::sendFrame(SVM41_I2C_ADDRESS, txFrame,
                                                 *_i2cBus);
    delay(100);
    return error;
}
