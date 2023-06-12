
#include "BL_Analog.hpp"

AnalogBaseBlock::AnalogBaseBlock(const std::string &bt, const std::string &bn, uint _adc)
    : LeafBlock(bt, bn), valid(false), adc(_adc)
{
    if (!adcInitialized)
    {
        adc_init();
        adcInitialized = true;
    }

    if (adc > 4)
        Error("AnalogBaseBlock: ADC should be within 0 and 4");
    else
    {
        valid = true;
    }
}

AnalogBaseBlock::~AnalogBaseBlock() {}

void AnalogBaseBlock::calculate()
{
    if (valid)
    {
        adc_select_input(adc);
        adcOutput = adc_read();
        std::cout << "Read on: " << adc << ": " << adcOutput << std::endl;
    }
}

bool AnalogBaseBlock::adcInitialized(false);

/*-------------------------------------------------------------------------------------*/

AnalogInBlock::AnalogInBlock(const std::string &bn, uint _adc)
    : AnalogBaseBlock("AnalogInBlock", bn, _adc), output(0.0)
{
    if (adc > 2)
    {
        Error("AnalogInBlock:: ADC should be within 0 and 2");
        valid = false;
    }
    else
    {
        addDefaultOutput(&output);
    }
}

AnalogInBlock::~AnalogInBlock()
{
}

void AnalogInBlock::calculate()
{
    AnalogBaseBlock::calculate();
    output = (double)adcOutput;

    std::cout << "Read on: " << adc << ": " << output << std::endl;
}

/*-------------------------------------------------------------------------------------*/

CPUTempBlock::CPUTempBlock(const std::string &bn)
    : AnalogBaseBlock("CPUTempBlock", bn, CPU_TEMP_CHANNEL), output(0.0)
{
    adc_set_temp_sensor_enabled(true);
    addDefaultOutput(&output);
}

CPUTempBlock::~CPUTempBlock()
{
}

void CPUTempBlock::calculate()
{
    AnalogBaseBlock::calculate();

    double adcVoltage = 3.3*adcOutput / (double)(1 << 12);

    output = (double)27 - (adcVoltage - 0.706) / 0.001721;

    std::cout << "Read on: CPU_Temp: " << output << std::endl;
}

const uint CPUTempBlock::CPU_TEMP_CHANNEL(4);