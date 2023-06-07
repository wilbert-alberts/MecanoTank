#ifndef SUM_HPP_
#define SUM_HPP_

#include "BL_Leaf.hpp"
#include "T.hpp"

#include <vector>

class SumBlock : public LeafBlock
{
public:
    SumBlock(const std::string &bn, unsigned int nrInputs);
    virtual ~SumBlock();
    virtual void calculate();

//    double *getOutput(const Terminal &t = OUT_OUTPUT);
//    void setInput(const Terminal &t = IN_INPUT, double *src = nullptr);

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
