#include <vector>
#include <string>
#include <iostream>

#include "BL_Trace.hpp"

TraceBlockAbstract::TraceBlockAbstract(uint nrOfDoublesToBuffer) : buffer(new double[nrOfDoublesToBuffer]), bufferSize(
																												nrOfDoublesToBuffer),
																   time(0), idx(0), nrTraceables(0), nrTraces(
																										 0)
{
}

TraceBlockAbstract::~TraceBlockAbstract()
{
	delete[] buffer;
}

void TraceBlockAbstract::calculate()
{

	if (tryLockTraceData())
	{
		// Retrieve and store all traceables
		for (uint i = 0; i < nrTraceables; i++)
		{
			auto value = *(traceables[i]);
			buffer[idx++] = value;
			// std::cout << "Trace: store " << value << " at position " << idx << std::endl; 
		}
		// See whether we need to start back at idx 0
		if (idx + nrTraceables > bufferSize)
		{
			idx = 0;
		}
		// Increase time.
		time++;
		unlockTraceData();
	}
}

void TraceBlockAbstract::clearTraceables()
{
	lockTraceData();
	traceables.clear();
	labels.clear();
	nrTraceables = 0;
	nrTraces = 0;
	time = 0;
	idx = 0;
	unlockTraceData();
}

void TraceBlockAbstract::addTraceable(const std::string &name, double *src)
{
	lockTraceData();
	traceables.push_back(src);
	labels.push_back(name);
	nrTraceables++;
	nrTraces = bufferSize / nrTraceables;
	time = 0;
	idx = 0;
	unlockTraceData();
}

VoidSuccessT TraceBlockAbstract::clearTraceable(const std::string &name)
{
	lockTraceData();

	int i = 0;
	auto labelsIter = labels.begin();
	auto traceablesIter = traceables.begin();
	auto r = VoidSuccessT();
	while (i < nrTraceables && labels[i] != name)
	{
		i++;
		labelsIter++;
		traceablesIter++;
	}
	if (i < nrTraceables)
	{
		// We found the traceable.
		traceables.erase(traceablesIter);
		labels.erase(labelsIter);
		nrTraceables--;
		nrTraces = bufferSize / nrTraceables;
		time = 0;
		idx = 0;
	}
	else
	{
		r = VoidSuccessT("Unable to find traceable.");
	}
	unlockTraceData();
	return r;
}
void TraceBlockAbstract::startDump()
{
	lockTraceData();
	if (time * nrTraceables > bufferSize)
	{
		dumpStartTime = time - nrTraces;
	}
	else
	{
		dumpStartTime = 0;
	}
	dumping = true;
}

std::string TraceBlockAbstract::getHeader(const std::string fieldSeparator)
{
	std::string result = "time";
	for (auto iter = labels.begin(); iter != labels.end(); iter++)
	{
		result += fieldSeparator + *iter;
	}
	return result;
}

uint TraceBlockAbstract::getStartTime()
{
	return dumpStartTime;
}

uint TraceBlockAbstract::getEndTime()
{
	return time;
}

std::string TraceBlockAbstract::getTraceOfTime(uint t,
											   const std::string fieldSeparator)
{
	if (t >= dumpStartTime && t < time)
	{
		std::string result = std::to_string(t);
		if (nrTraceables > 0)
		{
			uint traceIdx = t % nrTraces;
			uint arrayIdx = traceIdx * nrTraceables;
			for (int i = 0; i < nrTraceables; i++)
			{
				double value = buffer[arrayIdx + i];
				result += fieldSeparator+ std::to_string(value);
			}
		}
		return result;
	}
	else
	{
		return "Error: Illegal time in getTraceOfTime()";
	}
}

void TraceBlockAbstract::endDump()
{
	dumpStartTime = UINT32_MAX;
	dumping = false;
	unlockTraceData();
}

std::string TraceBlockAbstract::dumpTraceToString()
{
	std::string result;
	startDump();
	result += getHeader() + "\n";
	for (uint t = getStartTime(); t < getEndTime(); t++)
	{
		result += getTraceOfTime(t) + "\n";
	}
	endDump();
	return result;
}

void TraceBlockAbstract::dumpTraceToStdout()
{
	startDump();
	std::cout << getHeader() << std::endl;
	for (uint t = getStartTime(); t < getEndTime(); t++)
	{
		std::cout << getTraceOfTime(t) << std::endl;
	}
	endDump();

	//	uint dumpIdx(0);
	//	uint dumpTime(0);
	//	dumpLabels();
	//	if (time * nrTraceables > bufferSize) { // We've overrun the buffer
	//											// Start at idx and dump until idx-1 (mod bufferSize)
	//		dumpIdx = idx;
	//		dumpTime = time - nrTraces;
	//		// First dump from idx to bufferSize
	//		while (dumpIdx < (nrTraces * nrTraceables)) {
	//			dumpTrace(dumpTime, buffer + dumpIdx, nrTraceables);
	//			dumpIdx += nrTraceables;
	//			dumpTime++;
	//		}
	//	} // Start at 0 and dump until idx-1
	//	dumpIdx = 0;
	//	while (dumpIdx < idx) {
	//		dumpTrace(dumpTime, buffer + dumpIdx, nrTraceables);
	//		dumpIdx += nrTraceables;
	//		dumpTime++;
	//	}
}

// void TraceBlockAbstract::dumpLabels() {
//
//	std::cout << "time";
//	for (uint i = 0; i < traceables.size(); i++) {
//		std::cout << ", " << labels[i];
//	}
//	std::cout << std::endl;
// }
//
// void TraceBlockAbstract::dumpTrace(uint time, double *traceables,
//		uint nrTraceables) {
//	lockTraceData();
//	std::cout << time;
//	for (uint i = 0; i < nrTraceables; i++) {
//		std::cout << ", " << traceables[i];
//	}
//	unlockTraceData();
//	std::cout << std::endl;
// }

void TraceBlockAbstract::Error(const std::string &msg)
{
	std::cerr << "Error: " << msg << std::endl;
}

/************************ TraceBlock *******************************8*/

TraceBlock::TraceBlock() : TraceBlockAbstract(BUFFERSIZE_IN_DOUBLES), Block("TraceBlock", "tracer")
{
	// std::cout << "Traceblock: allocating memory for: " << BUFFERSIZE_IN_DOUBLES << " doubles"<< std::endl;
	semTraceData = xSemaphoreCreateBinary();
	xSemaphoreGive(semTraceData);
}
TraceBlock::~TraceBlock()
{
}

void TraceBlock::calculate()
{
	TraceBlockAbstract::calculate();
}

void TraceBlock::lockTraceData()
{
	// const TickType_t takeDumping = 5000 / portTICK_PERIOD_MS;

	auto r = xSemaphoreTake(semTraceData, portMAX_DELAY);
}

bool TraceBlock::tryLockTraceData()
{
	auto r = xSemaphoreTake(semTraceData, 0);
	return r == pdTRUE;
}

void TraceBlock::unlockTraceData()
{
	xSemaphoreGive(semTraceData);
}
