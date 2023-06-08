/*
 * TerminalFactory.h
 *
 *  Created on: 7 Jun 2023
 *      Author: walberts
 */

#ifndef TERMINALFACTORY_H_
#define TERMINALFACTORY_H_

#include <string>
#include <memory>

namespace TerminalFactory {

	const std::string separator(".");

	std::unique_ptr<const Terminal> createFromString(const std::string& fqn);
}
#endif /* TERMINALFACTORY_H_ */

