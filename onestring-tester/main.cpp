/** Onestring Tester
 * Version: 1.0
 *
 * Allows running tests and custom code for Onestring.
 *
 * Author(s): Jason C. McDonald
 */

/* LICENSE (BSD-3-Clause)
 * Copyright (c) 2016-2020 MousePaw Media.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
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
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 * CONTRIBUTING
 * See https://www.mousepawmedia.com/developers for information
 * on how to contribute to our projects.
 */

#include <iostream>
#include <string>

#include "goldilocks/shell.hpp"

#include "onestring/onestring.hpp"

#include "onestring/tests/onechar_tests.hpp"
#include "onestring/tests/onestring_tests.hpp"

/** Temporary test code goes in this function ONLY.
 * All test code that is needed long term should be
 * moved to a dedicated Goldilocks Test and TestSuite.
 */
void test_code()
{
	// str test

	onestring str = "bold";

	std::cout << str.find_first_not_of("body") << std::endl;     // 2
	std::cout << str.find_first_not_of("world") << std::endl;    // 0
	std::cout << str.find_first_not_of("art") << std::endl;      // 0
	std::cout << str.find_first_not_of("glad", 2) << std::endl;  // -1
	std::cout << str.find_first_not_of("bow", 3) << std::endl;   // 3
	std::cout << str.find_first_not_of("oolb", 1) << std::endl;  // 3
	std::cout << str.find_first_not_of("ballet") << std::endl;   // 1
	std::cout << str.find_first_not_of('b') << std::endl;        // 1

	try {
		std::cout << str.find_first_not_of("body", 4)  // Caught exception
				  << std::endl;
	} catch (const std::out_of_range&) {
		std::cout << "Caught exception" << std::endl;
	}

	try {
		std::cout << str.find_first_not_of("bbristya", 8)  // Caught exception
				  << std::endl;
	} catch (const std::out_of_range&) {
		std::cout << "Caught exception" << std::endl;
	}

	onestring emojis = "🌝⛄👽🐲🪗";

	// emoji test
	std::cout << emojis.find_first_not_of("🥁🐝📡🌝🪗")
			  << std::endl;  // 1
	std::cout << emojis.find_first_not_of("🌝⛄👽🐲🪗🐝")
			  << std::endl;                                       // -1
	std::cout << emojis.find_first_not_of("⛄🐲", 3) << std::endl;  // 4
	std::cout << emojis.find_first_not_of("⛄🐲🪗📡", 1)
			  << std::endl;                                          // 2
	std::cout << emojis.find_first_not_of("🥁🐝") << std::endl;  // 0

	try {
		std::cout << emojis.find_first_not_of("⛄🐲", 5)
				  << std::endl;  // Caught exception

	} catch (const std::out_of_range&) {
		std::cout << "Caught exception" << std::endl;
	}

	try {
		std::cout << emojis.find_first_not_of("🍀", 8)
				  << std::endl;  // Caught exception

	} catch (const std::out_of_range&) {
		std::cout << "Caught exception" << std::endl;
	}
}

/////// WARNING: DO NOT ALTER BELOW THIS POINT! ///////

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;
	// Return code.
	int r = 0;

	test_code();

	// Set up signal handling.
	channel.configure_echo(IOEchoMode::cout);

	GoldilocksShell* shell = new GoldilocksShell(">> ");
	shell->register_suite<TestSuite_Onechar>("O-sB1");
	shell->register_suite<TestSuite_Onestring>("O-sB2");

	// If we got command-line arguments.
	if(argc > 1)
	{
	    r = shell->command(argc, argv);
	}
	else
	{
	    channel << IOFormatTextAttr::bold << IOFormatTextFG::blue
	        << "===== Onestring Tester =====\n" << IOCtrl::endl;

		test_code();

	    // Shift control to the interactive console.
	    shell->interactive();
	}

	// Delete our GoldilocksShell.
	delete shell;

	return r;
}
