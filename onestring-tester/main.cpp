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
<<<<<<< HEAD
	onestring ostr_test_one = "abcd";
	onestring ostr_test_two = "(>o_o)> ==>";
	onestring ostr_test_three = "dcba";
	std::string str_test = "bc";
	const char* cstr_test = "dc";
	onestring emojis = "🏁🍇🍿🍉"; 

	std::cout << ostr_test_one.find("z") << std::endl;         // -1
	std::cout << ostr_test_one.find("da") << std::endl;        // -1
	std::cout << ostr_test_one.find("bc") << std::endl;        // 1
	std::cout << ostr_test_one.find("cd") << std::endl;        // 2
	std::cout << ostr_test_one.find("bc", 3) << std::endl;     // -1
	std::cout << ostr_test_one.find("bc", 1) << std::endl;     // 1
	std::cout << ostr_test_one.find("d", 3) << std::endl;      // 3
	std::cout << ostr_test_one.find("a") << std::endl;         // 0
	std::cout << ostr_test_two.find("==>") << std::endl;       // 8
	std::cout << ostr_test_two.find("(>o", 4) << std::endl;    // -1
	std::cout << ostr_test_two.find("> ==>", 5) << std::endl;  // 6

	try {
		std::cout << ostr_test_one.find("d", 4) << std::endl;  // exception
	} catch (const std::out_of_range&) {
		std::cout << "Caught exception" << std::endl;
	}

	std::cout << "\n ---TESTING std:string--- \n" << std::endl;

	std::cout << ostr_test_one.find(str_test, 3) << std::endl;  // -1
	std::cout << ostr_test_one.find(str_test, 1) << std::endl;  // 1

	try {
		std::cout << ostr_test_one.find(str_test, 4) << std::endl;  // exception
	} catch (const std::out_of_range&) {
		std::cout << "Caught exception" << std::endl;
	}

	std::cout << "\n ---TESTING char*--- \n" << std::endl;

	std::cout << ostr_test_one.find(cstr_test, 3) << std::endl;  // -1
	std::cout << ostr_test_one.find(cstr_test) << std::endl;     // -1

	try {
		std::cout << ostr_test_one.find(cstr_test, 7) << std::endl;  // exception
	} catch (const std::out_of_range&) {
		std::cout << "Caught exception" << std::endl;
	}

	std::cout << ostr_test_three.find(cstr_test) << std::endl;  // 0

	std::cout << "\n ---TESTING emojis--- \n" << std::endl;

	std::cout << emojis.find("🍇") << std::endl;  // 1
	std::cout << emojis.find("🍇", 2) << std::endl;  // -1
	std::cout << emojis.find("🍿🍉", 1) << std::endl;  // 2
	std::cout << emojis.find("🏁") << std::endl;  // 0
	std::cout << emojis.find("😀") << std::endl;  // -1

	try {
		std::cout << emojis.find("🔤", 4)<< std::endl;  // exception
	} catch (const std::out_of_range&) {
		std::cout << "Caught exception" << std::endl;
	}
=======
	onestring str = "tyobaler";

	std::cout << str.find_last_not_of("battery") << std::endl;      // 5
	std::cout << str.find_last_not_of("roller") << std::endl;     // 4
	std::cout << str.find_last_not_of("alley") << std::endl;     // 7
	std::cout << str.find_last_not_of("baylroer") << std::endl;     // 0
	std::cout << str.find_last_not_of("obartleby") << std::endl;     // -1
	std::cout << str.find_last_not_of("trleba", 2) << std::endl;  // 2
	std::cout << str.find_last_not_of("toy", 3) << std::endl;  // -1
<<<<<<< HEAD


>>>>>>> test: add tests for find_last_not_of()
=======
	std::cout << str.find_last_not_of("mail", 4) << std::endl;  // 3
	std::cout << str.find_last_not_of("tttyb", 3) << std::endl;  // 2
	std::cout << str.find_last_not_of("tym", 5) << std::endl;  // 5
	std::cout << str.find_last_not_of("tambourine", 1) << std::endl;  // 1
	std::cout << str.find_last_not_of("ball", -1) << std::endl;  // 7
		

	try {
		std::cout << str.find_last_not_of("body", 10)
				  << std::endl;  // Caught exception
	} catch (const std::out_of_range&) {
		std::cout << "Caught exception" << std::endl;
	}

>>>>>>> feat: add more tests.
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
