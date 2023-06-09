/*
 * TerminalFactory.cpp
 *
 *  Created on: 7 Jun 2023
 *      Author: walberts
 */

#include <string>
#include <memory>

#include "T.hpp"
#include "T_ID.hpp"
#include "T_Composite.hpp"

#include "T_Factory.hpp"

namespace TerminalFactory {

std::unique_ptr<const Terminal> createFromString(const std::string& fqn) {

	size_t separatorIdx = fqn.find(Terminal::separator);
	if (separatorIdx == std::string::npos) {
		// No separator, create IDTerminal
		return std::make_unique<const IDTerminal>(fqn);
	}
	else {
		std::string headID = fqn.substr(0, separatorIdx);
		std::string tailID = fqn.substr(separatorIdx+1, std::string::npos);

		std::unique_ptr<const Terminal> tail = createFromString(tailID);
		std::unique_ptr<const IDTerminal> head = std::make_unique<IDTerminal>(headID);

		std::unique_ptr<const Terminal> result = std::make_unique<const CompositeTerminal>(std::move(head), std::move(tail));
		return result;
	}
}

}
