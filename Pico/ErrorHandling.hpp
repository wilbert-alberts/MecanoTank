/*
 * Block.h
 *
 *  Created on: 7 Jun 2023
 *      Author: walberts
 */

#ifndef _ERROR_HANDLING_HPP_
#define _ERROR_HANDLING_HPP_

#include <string>
#include <iostream>
#include <stdexcept>
#include <memory>


class VoidSuccessT
{
public:
    VoidSuccessT(const std::string &msg) : success(false), errorMsg(std::make_shared<const std::string>(msg))
    {
    }
    VoidSuccessT(std::shared_ptr<const std::string> msg) : success(false), errorMsg(msg)
    {
    }
    VoidSuccessT() : success(true), errorMsg(std::make_shared<const std::string>("OK"))
    {
    }
    virtual ~VoidSuccessT() {}

    bool success;
    std::shared_ptr<const std::string> errorMsg;
};

template <typename T>
class SuccessT: public VoidSuccessT
{
public:
    SuccessT(T r, const std::string &msg) : VoidSuccessT(msg), result(r)
    {
    }
    SuccessT(T r, std::shared_ptr<const std::string> msg) : VoidSuccessT(msg), result(r)
    {
    }
    SuccessT(T r) : VoidSuccessT(), result(r)
    {
    }
    virtual ~SuccessT() {}

    T result;
};

void Error(const std::string &msg);

void Warning(const std::string &msg);

#endif