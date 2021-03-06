#include <micro/port/queue.hpp>
#include <micro/port/task.hpp>
#include <micro/utils/log.hpp>
#include <micro/utils/str_utils.hpp>

#include <cfg_board.hpp>
#include <SensorHandler.hpp>

#include <cstring>

using namespace micro;

extern queue_t<SensorControlData, 1> sensorControlDataQueue;
queue_t<Measurements, 1> measurementsQueue;

namespace {

SensorHandler sensorHandler(spi_Sensor, { gpio_SS_ADC0, gpio_SS_ADC1, gpio_SS_ADC2, gpio_SS_ADC3, gpio_SS_ADC4, gpio_SS_ADC5 },
    gpio_LE_OPTO, gpio_OE_OPTO, gpio_LE_IND, gpio_LE_IND);

Measurements measurements;
SensorControlData sensorControl;

std::pair<uint8_t, uint8_t> getScanRange() {
    std::pair<uint8_t, uint8_t> range = { 0, cfg::NUM_SENSORS - 1 };

    if (sensorControl.scanRangeRadius > 0) {
        range.first  = micro::max(sensorControl.scanRangeCenter, sensorControl.scanRangeRadius) - sensorControl.scanRangeRadius;
        range.second = micro::min(sensorControl.scanRangeCenter + sensorControl.scanRangeRadius, cfg::NUM_SENSORS - 1);
    }

    return range;
}

} // namespace

extern "C" void runSensorTask(void) {

    sensorHandler.initialize();

    while (true) {
        sensorHandler.writeLeds(sensorControl.leds);

        for (uint8_t i = 0; i < cfg::NUM_SENSORS; ++i) {
            measurements[i] = 0;
        }

        if (sensorControl.scanEnabled) {
            sensorHandler.readSensors(measurements, getScanRange());
        }

        measurementsQueue.send(measurements);
        sensorControlDataQueue.receive(sensorControl);
    }
}

extern void spi_SensorTxCpltCallback() {
    sensorHandler.onTxFinished();
}

extern void spi_SensorTxRxCpltCallback() {
    sensorHandler.onTxFinished();
}
