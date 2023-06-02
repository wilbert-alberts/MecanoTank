#ifndef SUM_HPP_
#define SUM_HPP_

#include "BL.hpp"

#include <vector>

class SumBlock : public Block
{
public:
    SumBlock(const std::string &bn, unsigned int nrInputs);
    virtual ~SumBlock();
    virtual void calculate();

    double *getOutput();
    void setInput(unsigned int idx, double *p);

    void setOffset(double o);
    void setFactor(unsigned int idx, double o);

private:
    double offset;
    double safeValue;
    unsigned int nrInputs;

    std::vector<double> factors;

    double out;
    std::vector<double *>in;
};

#endif
