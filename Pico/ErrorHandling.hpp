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
    VoidSuccessT(bool s, const std::string &msg) : success(s), errorMsg(std::make_shared<const std::string>(msg))
    {
    }
    VoidSuccessT(bool s, std::shared_ptr<const std::string> msg) : success(s), errorMsg(msg)
    {
    }
    VoidSuccessT() : success(true), errorMsg(std::make_shared<const std::string>())
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
    SuccessT(T r, bool s, const std::string &msg) : VoidSuccessT(s, msg), result(r)
    {
    }
    SuccessT(T r, bool s, std::shared_ptr<const std::string> msg) : VoidSuccessT(s, msg), result(r)
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