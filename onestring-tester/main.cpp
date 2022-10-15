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

	// Test find()
	onestring sport = "football";

	std::cout << sport.find("ba") << std::endl;  // Returns 4
	std::cout << sport.find("te") << std::endl;  // Returns -1

	// Test find_first_of()
	onestring flower = "daisy";

	std::cout << flower.find_first_of("iris") << std::endl;      // Returns 2
	std::cout << flower.find_first_of("bluebell") << std::endl;  // Returns -1

	// Test find_last_of()
	onestring vehicle = "plane";

	std::cout << vehicle.find_last_of("van") << std::endl;  // Returns 3
	std::cout << vehicle.find_last_of("bus") << std::endl;  // Returns -1

	// Test find_first_not_of()
	onestring name = "Jane";

	std::cout << name.find_first_not_of("Kevin") << std::endl;  // Returns 0
	std::cout << name.find_first_not_of("Jena") << std::endl;   // Returns -1

	// Test find_last_not_of()
	onestring city = "Bilbao";

	std::cout << city.find_last_not_of("Madrid") << std::endl;  // Returns 5
	std::cout << city.find_last_not_of("Bolbia") << std::endl;  // Returns -1

	// Test rfind()
	onestring color = "yellow";
	onestring letters = "bcsslbc";

	std::cout << color.rfind("l")
			  << std::endl;  // Returns 2 when it should returns 3
	std::cout << letters.rfind("bc")
			  << std::endl;  // Returns 0 when it should returns 5
	std::cout << color.rfind("po") << std::endl;    // Returns -1
	std::cout << letters.rfind("am") << std::endl;  // Returns -1

	// onestring str = "lemon";

	// std::cout << str.find_last_of("world") << std::endl;     // 3
	// std::cout << str.find_last_of("plane") << std::endl;     // 4
	// std::cout << str.find_last_of("else") << std::endl;      // 1
	// std::cout << str.find_last_of("ray") << std::endl;       // -1
	// std::cout << str.find_last_of("mall", 1) << std::endl;   // 0
	// std::cout << str.find_last_of("leech", 2) << std::endl;  // 1
	// std::cout << str.find_last_of("clamp", 3) << std::endl;  // 2
	// std::cout << str.find_last_of('o') << std::endl;         // 3
	// std::cout << str.find_last_of('o', 2) << std::endl;      // -1

	// try {
	// 	std::cout << str.find_last_of("frog", 6)  // Caught exception
	// 			  << std::endl;
	// } catch (const std::out_of_range&) {
	// 	std::cout << "Caught exception" << std::endl;
	// }

	// try {
	// 	std::cout << str.find_last_of("breeze", 8)  // Caught exception
	// 			  << std::endl;
	// } catch (const std::out_of_range&) {
	// 	std::cout << "Caught exception" << std::endl;
	// }

	// onestring emojis = "🌝⛄👽🐲🪗";

	// // emoji test
	// std::cout << emojis.find_last_of("🥁🐝🌝🍀🪗") << std::endl;  //
	// 4
	// std::cout << emojis.find_last_of("🥁🐝📡") << std::endl;        //
	// -1
	// std::cout << emojis.find_last_of("⛄🪗🌝", 3) << std::endl;      //
	// 1
	// std::cout << emojis.find_last_of("⛄🐲🪗📡", 1) << std::endl;  //
	// 1 std::cout << emojis.find_last_of("🍀🐝👽") << std::endl; // 2

	// try {
	// 	std::cout << emojis.find_last_of("⛄🐲", 6)
	// 			  << std::endl;  // Caught exception

	// } catch (const std::out_of_range&) {
	// 	std::cout << "Caught exception" << std::endl;
	// }

	// try {
	// 	std::cout << emojis.find_last_of("🍀", 8)
	// 			  << std::endl;  // Caught exception
	// } catch (const std::out_of_range&) {
	// 	std::cout << "Caught exception" << std::endl;
	// }
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
