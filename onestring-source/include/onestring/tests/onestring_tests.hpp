/** Tests for Onestring
 * Version: 0.5
 *
 * Author(s): Jason C. McDonald, Scott Taylor, Bo Volwiler
 */

/* LICENSE (BSD-3-Clause)
 * Copyright (c) 2016-2019 MousePaw Media.
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

#ifndef ONESTRING_TESTS_HPP
#define ONESTRING_TESTS_HPP

#include <string>

#include "onestring/onestring.hpp"

#include "goldilocks/goldilocks.hpp"
#include "goldilocks/assertions.hpp"
#include "iosqueak/channel.hpp"

class TestOnestring : public Test
{
public:
	enum class TestStringType {
		CHAR,
		OCHAR_ASCII,
		OCHAR_UNICODE,
		CSTR_ASCII,
		CSTR_UNICODE,
		STR_ASCII,
		STR_UNICODE,
		OSTR_ASCII,
		OSTR_UNICODE
	};

	char ch_1 = 'M';
	char ch_2 = 'm';

	onechar ochr_ascii_1 = "M";
	onechar ochr_ascii_2 = "m";

	onechar ochr_unicode_1 = "🐭";
	onechar ochr_unicode_2 = "🦊";

	onestring ostr_ch_ascii_1 = "M";
	onestring ostr_ch_ascii_2 = "m";
	onestring ostr_ch_unicode_1 = "🐭";
	onestring ostr_ch_unicode_2 = "🦊";

	// We'll extract the c-strings from these as needed.
	std::string str_ascii_1 = "The quick brown fox jumped over the lazy dog.";
	std::string str_unicode_1 =
		"The quick brown 🦊 jumped over the lazy 🐶.";
	std::string str_ascii_2 = "Jackdaws love my big sphinx of quartz.";
	std::string str_unicode_2 = "🐦 ❤️ my big sphinx of 💎.";

	onestring ostr_ascii_1 = "The quick brown fox jumped over the lazy dog.";
	onestring ostr_unicode_1 =
		"The quick brown 🦊 jumped over the lazy 🐶.";
	onestring ostr_ascii_2 = "Jackdaws love my big sphinx of quartz.";
	onestring ostr_unicode_2 = "🐦 ❤️ my big sphinx of 💎.";

protected:
	TestStringType stringType;

	testdoc_t title;

public:
	explicit TestOnestring(TestStringType type) : stringType(type)
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				title = "(char)";
				break;
			}
			case TestStringType::OCHAR_ASCII: {
				title = "(onechar, ASCII)";
				break;
			}
			case TestStringType::OCHAR_UNICODE: {
				title = "(onechar, Unicode)";
				break;
			}
			case TestStringType::CSTR_ASCII: {
				title = "(c-string, ASCII)";
				break;
			}
			case TestStringType::CSTR_UNICODE: {
				title = "(c-string, Unicode)";
				break;
			}
			case TestStringType::STR_ASCII: {
				title = "(std::string, ASCII)";
				break;
			}
			case TestStringType::STR_UNICODE: {
				title = "(std::string, Unicode)";
				break;
			}
			case TestStringType::OSTR_ASCII: {
				title = "(onestring, ASCII)";
				break;
			}
			case TestStringType::OSTR_UNICODE: {
				title = "(onestring, Unicode)";
				break;
			}
		}
	}

	virtual testdoc_t get_title() override = 0;

	virtual testdoc_t get_docs() override = 0;
};

// O-tB201[a-i]
class TestOnestring_Assign : public TestOnestring
{
protected:
	onestring test;

public:
	explicit TestOnestring_Assign(TestStringType type) : TestOnestring(type) {}

	testdoc_t get_title() override { return "Onestring: Assign " + title; }

	testdoc_t get_docs() override { return "Test assignment to a onestring."; }

	bool janitor() override
	{
		test = "";
		return true;
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				test.assign(ch_1);
				PL_ASSERT_EQUAL(test, ostr_ch_ascii_1);
				return true;
			}
			case TestStringType::OCHAR_ASCII: {
				test.assign(ochr_ascii_1);
				PL_ASSERT_EQUAL(test, ostr_ch_ascii_1);
				return true;
			}
			case TestStringType::OCHAR_UNICODE: {
				test.assign(ochr_unicode_1);
				PL_ASSERT_EQUAL(test, ostr_ch_unicode_1);
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				test.assign(str_ascii_1.c_str());
				PL_ASSERT_EQUAL(test, ostr_ascii_1);
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				test.assign(str_unicode_1.c_str());
				PL_ASSERT_EQUAL(test, ostr_unicode_1);
				return true;
			}
			case TestStringType::STR_ASCII: {
				test.assign(str_ascii_1);
				PL_ASSERT_EQUAL(test, ostr_ascii_1);
				return true;
			}
			case TestStringType::STR_UNICODE: {
				test.assign(str_unicode_1);
				PL_ASSERT_EQUAL(test, ostr_unicode_1);
				return true;
			}
			case TestStringType::OSTR_ASCII: {
				test.assign(ostr_ascii_1);
				PL_ASSERT_EQUAL(test, ostr_ascii_1);
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				test.assign(ostr_unicode_1);
				PL_ASSERT_EQUAL(test, ostr_unicode_1);
				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB202[a-i]
class TestOnestring_Equals : public TestOnestring
{
protected:
	onestring test;

public:
	explicit TestOnestring_Equals(TestStringType type) : TestOnestring(type) {}

	testdoc_t get_title() override { return "Onestring: Equals " + title; }

	testdoc_t get_docs() override
	{
		return "Test comparison with the equals() function.";
	}

	bool janitor() override
	{
		test = "";
		return true;
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				test = ch_1;
				PL_ASSERT_TRUE(test.equals(ch_1));
				PL_ASSERT_FALSE(test.equals(ch_2));
				return true;
			}
			case TestStringType::OCHAR_ASCII: {
				test = ochr_ascii_1;
				PL_ASSERT_TRUE(test.equals(ochr_ascii_1));
				PL_ASSERT_FALSE(test.equals(ochr_ascii_2));
				return true;
			}
			case TestStringType::OCHAR_UNICODE: {
				test = ochr_unicode_1;
				PL_ASSERT_TRUE(test.equals(ochr_unicode_1));
				PL_ASSERT_FALSE(test.equals(ochr_unicode_2));
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				test = str_ascii_1;
				PL_ASSERT_TRUE(test.equals(str_ascii_1.c_str()));
				PL_ASSERT_FALSE(test.equals(str_ascii_2.c_str()));
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				test = str_unicode_1;
				PL_ASSERT_TRUE(test.equals(str_unicode_1.c_str()));
				PL_ASSERT_FALSE(test.equals(str_unicode_2.c_str()));
				return true;
			}
			case TestStringType::STR_ASCII: {
				test = str_ascii_1;
				PL_ASSERT_TRUE(test.equals(str_ascii_1));
				PL_ASSERT_FALSE(test.equals(str_ascii_2));
				return true;
			}
			case TestStringType::STR_UNICODE: {
				test = str_unicode_1;
				PL_ASSERT_TRUE(test.equals(str_unicode_1));
				PL_ASSERT_FALSE(test.equals(str_unicode_2));
				return true;
			}
			case TestStringType::OSTR_ASCII: {
				test = ostr_ascii_1;
				PL_ASSERT_TRUE(test.equals(ostr_ascii_1));
				PL_ASSERT_FALSE(test.equals(ostr_ascii_2));
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				test = ostr_unicode_1;
				PL_ASSERT_TRUE(test.equals(ostr_unicode_1));
				PL_ASSERT_FALSE(test.equals(ostr_unicode_2));
				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB203[a-i]
class TestOnestring_OpEquals : public TestOnestring
{
protected:
	onestring test;

public:
	explicit TestOnestring_OpEquals(TestStringType type) : TestOnestring(type)
	{
	}

	testdoc_t get_title() override { return "Onestring: Equals (==) " + title; }

	testdoc_t get_docs() override
	{
		return "Test comparison with the == operator.";
	}

	bool janitor() override
	{
		test = "";
		return true;
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				test = ch_1;
				PL_ASSERT_TRUE(test == ch_1);
				PL_ASSERT_FALSE(test == ch_2);

				PL_ASSERT_TRUE(ch_1 == test);
				PL_ASSERT_FALSE(ch_2 == test);
				return true;
			}
			case TestStringType::OCHAR_ASCII: {
				test = ochr_ascii_1;
				PL_ASSERT_TRUE(test == ochr_ascii_1);
				PL_ASSERT_FALSE(test == ochr_ascii_2);

				PL_ASSERT_TRUE(ochr_ascii_1 == test);
				PL_ASSERT_FALSE(ochr_ascii_2 == test);
				return true;
			}
			case TestStringType::OCHAR_UNICODE: {
				test = ochr_unicode_1;
				PL_ASSERT_TRUE(test == ochr_unicode_1);
				PL_ASSERT_FALSE(test == ochr_unicode_2);

				PL_ASSERT_TRUE(ochr_unicode_1 == test);
				PL_ASSERT_FALSE(ochr_unicode_2 == test);
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				test = str_ascii_1;
				PL_ASSERT_TRUE(test == str_ascii_1.c_str());
				PL_ASSERT_FALSE(test == str_ascii_2.c_str());

				PL_ASSERT_TRUE(str_ascii_1.c_str() == test);
				PL_ASSERT_FALSE(str_ascii_2.c_str() == test);
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				test = str_unicode_1;
				PL_ASSERT_TRUE(test == str_unicode_1.c_str());
				PL_ASSERT_FALSE(test == str_unicode_2.c_str());

				PL_ASSERT_TRUE(str_unicode_1.c_str() == test);
				PL_ASSERT_FALSE(str_unicode_2.c_str() == test);
				return true;
			}
			case TestStringType::STR_ASCII: {
				test = str_ascii_1;
				PL_ASSERT_TRUE(test == str_ascii_1);
				PL_ASSERT_FALSE(test == str_ascii_2);

				PL_ASSERT_TRUE(str_ascii_1 == test);
				PL_ASSERT_FALSE(str_ascii_2 == test);
				return true;
			}
			case TestStringType::STR_UNICODE: {
				test = str_unicode_1;
				PL_ASSERT_TRUE(test == str_unicode_1);
				PL_ASSERT_FALSE(test == str_unicode_2);

				PL_ASSERT_TRUE(str_unicode_1 == test);
				PL_ASSERT_FALSE(str_unicode_2 == test);
				return true;
			}
			case TestStringType::OSTR_ASCII: {
				test = ostr_ascii_1;
				PL_ASSERT_TRUE(test == ostr_ascii_1);
				PL_ASSERT_FALSE(test == ostr_ascii_2);

				PL_ASSERT_TRUE(ostr_ascii_1 == test);
				PL_ASSERT_FALSE(ostr_ascii_2 == test);
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				test = ostr_unicode_1;
				PL_ASSERT_TRUE(test == ostr_unicode_1);
				PL_ASSERT_FALSE(test == ostr_unicode_2);

				PL_ASSERT_TRUE(ostr_unicode_1 == test);
				PL_ASSERT_FALSE(ostr_unicode_2 == test);
				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB204[a-i]
class TestOnestring_OpNotEquals : public TestOnestring
{
protected:
	onestring test;

public:
	explicit TestOnestring_OpNotEquals(TestStringType type)
	: TestOnestring(type)
	{
	}

	testdoc_t get_title() override
	{
		return "Onestring: Not Equals (!=) " + title;
	}

	testdoc_t get_docs() override
	{
		return "Test comparison with the != operator.";
	}

	bool janitor() override
	{
		test = "";
		return true;
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				test = ch_1;
				PL_ASSERT_TRUE(test != ch_2);
				PL_ASSERT_FALSE(test != ch_1);

				PL_ASSERT_TRUE(ch_2 != test);
				PL_ASSERT_FALSE(ch_1 != test);
				return true;
			}
			case TestStringType::OCHAR_ASCII: {
				test = ochr_ascii_1;
				PL_ASSERT_TRUE(test != ochr_ascii_2);
				PL_ASSERT_FALSE(test != ochr_ascii_1);

				PL_ASSERT_TRUE(ochr_ascii_2 != test);
				PL_ASSERT_FALSE(ochr_ascii_1 != test);
				return true;
			}
			case TestStringType::OCHAR_UNICODE: {
				test = ochr_unicode_1;
				PL_ASSERT_TRUE(test != ochr_unicode_2);
				PL_ASSERT_FALSE(test != ochr_unicode_1);

				PL_ASSERT_TRUE(ochr_unicode_2 != test);
				PL_ASSERT_FALSE(ochr_unicode_1 != test);
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				test = str_ascii_1;
				PL_ASSERT_TRUE(test != str_ascii_2.c_str());
				PL_ASSERT_FALSE(test != str_ascii_1.c_str());

				PL_ASSERT_TRUE(str_ascii_2.c_str() != test);
				PL_ASSERT_FALSE(str_ascii_1.c_str() != test);
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				test = str_unicode_1;
				PL_ASSERT_TRUE(test != str_unicode_2.c_str());
				PL_ASSERT_FALSE(test != str_unicode_1.c_str());

				PL_ASSERT_TRUE(str_unicode_2.c_str() != test);
				PL_ASSERT_FALSE(str_unicode_1.c_str() != test);
				return true;
			}
			case TestStringType::STR_ASCII: {
				test = str_ascii_1;
				PL_ASSERT_TRUE(test != str_ascii_2);
				PL_ASSERT_FALSE(test != str_ascii_1);

				PL_ASSERT_TRUE(str_ascii_2 != test);
				PL_ASSERT_FALSE(str_ascii_1 != test);
				return true;
			}
			case TestStringType::STR_UNICODE: {
				test = str_unicode_1;
				PL_ASSERT_TRUE(test != str_unicode_2);
				PL_ASSERT_FALSE(test != str_unicode_1);

				PL_ASSERT_TRUE(str_unicode_2 != test);
				PL_ASSERT_FALSE(str_unicode_1 != test);
				return true;
			}
			case TestStringType::OSTR_ASCII: {
				test = ostr_ascii_1;
				PL_ASSERT_TRUE(test != ostr_ascii_2);
				PL_ASSERT_FALSE(test != ostr_ascii_1);

				PL_ASSERT_TRUE(ostr_ascii_2 != test);
				PL_ASSERT_FALSE(ostr_ascii_1 != test);
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				test = ostr_unicode_1;
				PL_ASSERT_TRUE(test != ostr_unicode_2);
				PL_ASSERT_FALSE(test != ostr_unicode_1);

				PL_ASSERT_TRUE(ostr_unicode_2 != test);
				PL_ASSERT_FALSE(ostr_unicode_1 != test);
				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB205[a-i]
class TestOnestring_Compare : public TestOnestring
{
protected:
	onestring test;

public:
	explicit TestOnestring_Compare(TestStringType type) : TestOnestring(type) {}

	testdoc_t get_title() override { return "Onestring: Compare " + title; }

	testdoc_t get_docs() override
	{
		return "Test comparison with the compare() function.";
	}

	bool janitor() override
	{
		test = "";
		return true;
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				char eq = 'B';
				char lt = 'A';
				char gt = 'C';

				test = eq;
				PL_ASSERT_EQUAL(test.compare(eq), 0);
				PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
				PL_ANTIASSERT_EQUAL(test.compare(gt), 0);

				PL_ASSERT_LESS(test.compare(gt), 0);
				PL_ANTIASSERT_LESS(test.compare(eq), 0);
				PL_ANTIASSERT_LESS(test.compare(lt), 0);

				PL_ASSERT_GREATER(test.compare(lt), 0);
				PL_ANTIASSERT_GREATER(test.compare(eq), 0);
				PL_ANTIASSERT_GREATER(test.compare(gt), 0);
				return true;
			}
			case TestStringType::OCHAR_ASCII: {
				onechar eq = "B";
				onechar lt = "A";
				onechar gt = "C";

				test = eq;
				PL_ASSERT_EQUAL(test.compare(eq), 0);
				PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
				PL_ANTIASSERT_EQUAL(test.compare(gt), 0);

				PL_ASSERT_LESS(test.compare(gt), 0);
				PL_ANTIASSERT_LESS(test.compare(eq), 0);
				PL_ANTIASSERT_LESS(test.compare(lt), 0);

				PL_ASSERT_GREATER(test.compare(lt), 0);
				PL_ANTIASSERT_GREATER(test.compare(eq), 0);
				PL_ANTIASSERT_GREATER(test.compare(gt), 0);
				return true;
			}
			case TestStringType::OCHAR_UNICODE: {
				onechar eq = "🐭";
				onechar lt = "🐁";
				onechar gt = "🦊";

				test = eq;
				PL_ASSERT_EQUAL(test.compare(eq), 0);
				PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
				PL_ANTIASSERT_EQUAL(test.compare(gt), 0);

				PL_ASSERT_LESS(test.compare(gt), 0);
				PL_ANTIASSERT_LESS(test.compare(eq), 0);
				PL_ANTIASSERT_LESS(test.compare(lt), 0);

				PL_ASSERT_GREATER(test.compare(lt), 0);
				PL_ANTIASSERT_GREATER(test.compare(eq), 0);
				PL_ANTIASSERT_GREATER(test.compare(gt), 0);
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				std::string eq = "abcB";
				std::string lt = "abcA";
				std::string gt = "abcC";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_EQUAL(test.compare(eq.c_str()), 0);
				PL_ANTIASSERT_EQUAL(test.compare(lt.c_str()), 0);
				PL_ANTIASSERT_EQUAL(test.compare(gt.c_str()), 0);
				PL_ANTIASSERT_EQUAL(test.compare(shorter.c_str()), 0);
				PL_ANTIASSERT_EQUAL(test.compare(longer.c_str()), 0);

				PL_ASSERT_LESS(test.compare(gt.c_str()), 0);
				PL_ASSERT_LESS(test.compare(longer.c_str()), 0);
				PL_ANTIASSERT_LESS(test.compare(eq.c_str()), 0);
				PL_ANTIASSERT_LESS(test.compare(lt.c_str()), 0);
				PL_ANTIASSERT_LESS(test.compare(shorter.c_str()), 0);

				PL_ASSERT_GREATER(test.compare(lt.c_str()), 0);
				PL_ASSERT_GREATER(test.compare(shorter.c_str()), 0);
				PL_ANTIASSERT_GREATER(test.compare(eq.c_str()), 0);
				PL_ANTIASSERT_GREATER(test.compare(gt.c_str()), 0);
				PL_ANTIASSERT_GREATER(test.compare(longer.c_str()), 0);
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				std::string eq = "🐭abc🐭";
				std::string lt = "🐭abc🐁";
				std::string gt = "🐭abc🦊";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_EQUAL(test.compare(eq.c_str()), 0);
				PL_ANTIASSERT_EQUAL(test.compare(lt.c_str()), 0);
				PL_ANTIASSERT_EQUAL(test.compare(gt.c_str()), 0);
				PL_ANTIASSERT_EQUAL(test.compare(shorter.c_str()), 0);
				PL_ANTIASSERT_EQUAL(test.compare(longer.c_str()), 0);

				PL_ASSERT_LESS(test.compare(gt.c_str()), 0);
				PL_ASSERT_LESS(test.compare(longer.c_str()), 0);
				PL_ANTIASSERT_LESS(test.compare(eq.c_str()), 0);
				PL_ANTIASSERT_LESS(test.compare(lt.c_str()), 0);
				PL_ANTIASSERT_LESS(test.compare(shorter.c_str()), 0);

				PL_ASSERT_GREATER(test.compare(lt.c_str()), 0);
				PL_ASSERT_GREATER(test.compare(shorter.c_str()), 0);
				PL_ANTIASSERT_GREATER(test.compare(eq.c_str()), 0);
				PL_ANTIASSERT_GREATER(test.compare(gt.c_str()), 0);
				PL_ANTIASSERT_GREATER(test.compare(longer.c_str()), 0);
				return true;
			}
			case TestStringType::STR_ASCII: {
				std::string eq = "abcB";
				std::string lt = "abcA";
				std::string gt = "abcC";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_EQUAL(test.compare(eq), 0);
				PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
				PL_ANTIASSERT_EQUAL(test.compare(gt), 0);
				PL_ANTIASSERT_EQUAL(test.compare(shorter), 0);
				PL_ANTIASSERT_EQUAL(test.compare(longer), 0);

				PL_ASSERT_LESS(test.compare(gt), 0);
				PL_ASSERT_LESS(test.compare(longer), 0);
				PL_ANTIASSERT_LESS(test.compare(eq), 0);
				PL_ANTIASSERT_LESS(test.compare(lt), 0);
				PL_ANTIASSERT_LESS(test.compare(shorter), 0);

				PL_ASSERT_GREATER(test.compare(lt), 0);
				PL_ASSERT_GREATER(test.compare(shorter), 0);
				PL_ANTIASSERT_GREATER(test.compare(eq), 0);
				PL_ANTIASSERT_GREATER(test.compare(gt), 0);
				PL_ANTIASSERT_GREATER(test.compare(longer), 0);
				return true;
			}
			case TestStringType::STR_UNICODE: {
				std::string eq = "🐭abc🐭";
				std::string lt = "🐭abc🐁";
				std::string gt = "🐭abc🦊";
				std::string shorter = "🐭ab";
				std::string longer = "🐭abc🦊🦊";

				test = eq;
				PL_ASSERT_EQUAL(test.compare(eq), 0);
				PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
				PL_ANTIASSERT_EQUAL(test.compare(gt), 0);
				PL_ANTIASSERT_EQUAL(test.compare(shorter), 0);
				PL_ANTIASSERT_EQUAL(test.compare(longer), 0);

				PL_ASSERT_LESS(test.compare(gt), 0);
				PL_ASSERT_LESS(test.compare(longer), 0);
				PL_ANTIASSERT_LESS(test.compare(eq), 0);
				PL_ANTIASSERT_LESS(test.compare(lt), 0);
				PL_ANTIASSERT_LESS(test.compare(shorter), 0);

				PL_ASSERT_GREATER(test.compare(lt), 0);
				PL_ASSERT_GREATER(test.compare(shorter), 0);
				PL_ANTIASSERT_GREATER(test.compare(eq), 0);
				PL_ANTIASSERT_GREATER(test.compare(gt), 0);
				PL_ANTIASSERT_GREATER(test.compare(longer), 0);
				return true;
			}
			case TestStringType::OSTR_ASCII: {
				onestring eq = "abcB";
				onestring lt = "abcA";
				onestring gt = "abcC";
				onestring shorter = "ab";
				onestring longer = "abcabc";

				test = eq;
				PL_ASSERT_EQUAL(test.compare(eq), 0);
				PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
				PL_ANTIASSERT_EQUAL(test.compare(gt), 0);
				PL_ANTIASSERT_EQUAL(test.compare(shorter), 0);
				PL_ANTIASSERT_EQUAL(test.compare(longer), 0);

				PL_ASSERT_LESS(test.compare(gt), 0);
				PL_ASSERT_LESS(test.compare(longer), 0);
				PL_ANTIASSERT_LESS(test.compare(eq), 0);
				PL_ANTIASSERT_LESS(test.compare(lt), 0);
				PL_ANTIASSERT_LESS(test.compare(shorter), 0);

				PL_ASSERT_GREATER(test.compare(lt), 0);
				PL_ASSERT_GREATER(test.compare(shorter), 0);
				PL_ANTIASSERT_GREATER(test.compare(eq), 0);
				PL_ANTIASSERT_GREATER(test.compare(gt), 0);
				PL_ANTIASSERT_GREATER(test.compare(longer), 0);
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				onestring eq = "🐭abc🐭";
				onestring lt = "🐭abc🐁";
				onestring gt = "🐭abc🦊";
				onestring shorter = "🐭ab";
				onestring longer = "🐭abc🦊🦊";

				test = eq;
				PL_ASSERT_EQUAL(test.compare(eq), 0);
				PL_ANTIASSERT_EQUAL(test.compare(lt), 0);
				PL_ANTIASSERT_EQUAL(test.compare(gt), 0);
				PL_ANTIASSERT_EQUAL(test.compare(shorter), 0);
				PL_ANTIASSERT_EQUAL(test.compare(longer), 0);

				PL_ASSERT_LESS(test.compare(gt), 0);
				PL_ASSERT_LESS(test.compare(longer), 0);
				PL_ANTIASSERT_LESS(test.compare(eq), 0);
				PL_ANTIASSERT_LESS(test.compare(lt), 0);
				PL_ANTIASSERT_LESS(test.compare(shorter), 0);

				PL_ASSERT_GREATER(test.compare(lt), 0);
				PL_ASSERT_GREATER(test.compare(shorter), 0);
				PL_ANTIASSERT_GREATER(test.compare(eq), 0);
				PL_ANTIASSERT_GREATER(test.compare(gt), 0);
				PL_ANTIASSERT_GREATER(test.compare(longer), 0);
				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB206[a-i]
class TestOnestring_OpLess : public TestOnestring
{
protected:
	onestring test;

public:
	explicit TestOnestring_OpLess(TestStringType type) : TestOnestring(type) {}

	testdoc_t get_title() override
	{
		return "Onestring: Less Than (<) " + title;
	}

	testdoc_t get_docs() override
	{
		return "Test comparison with the < operator.";
	}

	bool janitor() override
	{
		test = "";
		return true;
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				char eq = 'B';
				char lt = 'A';
				char gt = 'C';

				test = eq;
				PL_ASSERT_TRUE(test < gt);
				PL_ASSERT_FALSE(test < eq);
				PL_ASSERT_FALSE(test < lt);

				PL_ASSERT_FALSE(gt < test);
				PL_ASSERT_FALSE(eq < test);
				PL_ASSERT_TRUE(lt < test);
				return true;
			}
			case TestStringType::OCHAR_ASCII: {
				onechar eq = "B";
				onechar lt = "A";
				onechar gt = "C";

				test = eq;
				PL_ASSERT_TRUE(test < gt);
				PL_ASSERT_FALSE(test < eq);
				PL_ASSERT_FALSE(test < lt);

				PL_ASSERT_FALSE(gt < test);
				PL_ASSERT_FALSE(eq < test);
				PL_ASSERT_TRUE(lt < test);
				return true;
			}
			case TestStringType::OCHAR_UNICODE: {
				onechar eq = "🐭";
				onechar lt = "🐁";
				onechar gt = "🦊";

				test = eq;
				PL_ASSERT_TRUE(test < gt);
				PL_ASSERT_FALSE(test < eq);
				PL_ASSERT_FALSE(test < lt);

				PL_ASSERT_FALSE(gt < test);
				PL_ASSERT_FALSE(eq < test);
				PL_ASSERT_TRUE(lt < test);
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				std::string eq = "abcB";
				std::string lt = "abcA";
				std::string gt = "abcC";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test < gt.c_str());
				PL_ASSERT_TRUE(test < longer.c_str());
				PL_ASSERT_FALSE(test < eq.c_str());
				PL_ASSERT_FALSE(test < lt.c_str());
				PL_ASSERT_FALSE(test < shorter.c_str());

				PL_ASSERT_FALSE(gt.c_str() < test);
				PL_ASSERT_FALSE(longer.c_str() < test);
				PL_ASSERT_FALSE(eq.c_str() < test);
				PL_ASSERT_TRUE(lt.c_str() < test);
				PL_ASSERT_TRUE(shorter.c_str() < test);
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				std::string eq = "🐭abc🐭";
				std::string lt = "🐭abc🐁";
				std::string gt = "🐭abc🦊";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test < gt.c_str());
				PL_ASSERT_TRUE(test < longer.c_str());
				PL_ASSERT_FALSE(test < eq.c_str());
				PL_ASSERT_FALSE(test < lt.c_str());
				PL_ASSERT_FALSE(test < shorter.c_str());

				PL_ASSERT_FALSE(gt.c_str() < test);
				PL_ASSERT_FALSE(longer.c_str() < test);
				PL_ASSERT_FALSE(eq.c_str() < test);
				PL_ASSERT_TRUE(lt.c_str() < test);
				PL_ASSERT_TRUE(shorter.c_str() < test);
				return true;
			}
			case TestStringType::STR_ASCII: {
				std::string eq = "abcB";
				std::string lt = "abcA";
				std::string gt = "abcC";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test < gt);
				PL_ASSERT_TRUE(test < longer);
				PL_ASSERT_FALSE(test < eq);
				PL_ASSERT_FALSE(test < lt);
				PL_ASSERT_FALSE(test < shorter);

				PL_ASSERT_FALSE(gt < test);
				PL_ASSERT_FALSE(longer < test);
				PL_ASSERT_FALSE(eq < test);
				PL_ASSERT_TRUE(lt < test);
				PL_ASSERT_TRUE(shorter < test);
				return true;
			}
			case TestStringType::STR_UNICODE: {
				std::string eq = "🐭abc🐭";
				std::string lt = "🐭abc🐁";
				std::string gt = "🐭abc🦊";
				std::string shorter = "🐭ab";
				std::string longer = "🐭abc🦊🦊";

				test = eq;
				PL_ASSERT_TRUE(test < gt);
				PL_ASSERT_TRUE(test < longer);
				PL_ASSERT_FALSE(test < eq);
				PL_ASSERT_FALSE(test < lt);
				PL_ASSERT_FALSE(test < shorter);

				PL_ASSERT_FALSE(gt < test);
				PL_ASSERT_FALSE(longer < test);
				PL_ASSERT_FALSE(eq < test);
				PL_ASSERT_TRUE(lt < test);
				PL_ASSERT_TRUE(shorter < test);
				return true;
			}
			case TestStringType::OSTR_ASCII: {
				onestring eq = "abcB";
				onestring lt = "abcA";
				onestring gt = "abcC";
				onestring shorter = "ab";
				onestring longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test < gt);
				PL_ASSERT_TRUE(test < longer);
				PL_ASSERT_FALSE(test < eq);
				PL_ASSERT_FALSE(test < lt);
				PL_ASSERT_FALSE(test < shorter);

				PL_ASSERT_FALSE(gt < test);
				PL_ASSERT_FALSE(longer < test);
				PL_ASSERT_FALSE(eq < test);
				PL_ASSERT_TRUE(lt < test);
				PL_ASSERT_TRUE(shorter < test);
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				onestring eq = "🐭abc🐭";
				onestring lt = "🐭abc🐁";
				onestring gt = "🐭abc🦊";
				onestring shorter = "🐭ab";
				onestring longer = "🐭abc🦊🦊";

				test = eq;
				PL_ASSERT_TRUE(test < gt);
				PL_ASSERT_TRUE(test < longer);
				PL_ASSERT_FALSE(test < eq);
				PL_ASSERT_FALSE(test < lt);
				PL_ASSERT_FALSE(test < shorter);

				PL_ASSERT_FALSE(gt < test);
				PL_ASSERT_FALSE(longer < test);
				PL_ASSERT_FALSE(eq < test);
				PL_ASSERT_TRUE(lt < test);
				PL_ASSERT_TRUE(shorter < test);
				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB207[a-i]
class TestOnestring_OpLessEqual : public TestOnestring
{
protected:
	onestring test;

public:
	explicit TestOnestring_OpLessEqual(TestStringType type)
	: TestOnestring(type)
	{
	}

	testdoc_t get_title() override
	{
		return "Onestring: Less/Equal (<=) " + title;
	}

	testdoc_t get_docs() override
	{
		return "Test comparison with the <= operator.";
	}

	bool janitor() override
	{
		test = "";
		return true;
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				char eq = 'B';
				char lt = 'A';
				char gt = 'C';

				test = eq;
				PL_ASSERT_TRUE(test <= gt);
				PL_ASSERT_TRUE(test <= eq);
				PL_ASSERT_FALSE(test <= lt);

				PL_ASSERT_FALSE(gt <= test);
				PL_ASSERT_TRUE(eq <= test);
				PL_ASSERT_TRUE(lt <= test);
				return true;
			}
			case TestStringType::OCHAR_ASCII: {
				onechar eq = "B";
				onechar lt = "A";
				onechar gt = "C";

				test = eq;
				PL_ASSERT_TRUE(test <= gt);
				PL_ASSERT_TRUE(test <= eq);
				PL_ASSERT_FALSE(test <= lt);

				PL_ASSERT_FALSE(gt <= test);
				PL_ASSERT_TRUE(eq <= test);
				PL_ASSERT_TRUE(lt <= test);
				return true;
			}
			case TestStringType::OCHAR_UNICODE: {
				onechar eq = "🐭";
				onechar lt = "🐁";
				onechar gt = "🦊";

				test = eq;
				PL_ASSERT_TRUE(test <= gt);
				PL_ASSERT_TRUE(test <= eq);
				PL_ASSERT_FALSE(test <= lt);

				PL_ASSERT_FALSE(gt <= test);
				PL_ASSERT_TRUE(eq <= test);
				PL_ASSERT_TRUE(lt <= test);
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				std::string eq = "abcB";
				std::string lt = "abcA";
				std::string gt = "abcC";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test <= gt.c_str());
				PL_ASSERT_TRUE(test <= longer.c_str());
				PL_ASSERT_TRUE(test <= eq.c_str());
				PL_ASSERT_FALSE(test <= lt.c_str());
				PL_ASSERT_FALSE(test <= shorter.c_str());

				PL_ASSERT_FALSE(gt.c_str() <= test);
				PL_ASSERT_FALSE(longer.c_str() <= test);
				PL_ASSERT_TRUE(eq.c_str() <= test);
				PL_ASSERT_TRUE(lt.c_str() <= test);
				PL_ASSERT_TRUE(shorter.c_str() <= test);
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				std::string eq = "🐭abc🐭";
				std::string lt = "🐭abc🐁";
				std::string gt = "🐭abc🦊";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test <= gt.c_str());
				PL_ASSERT_TRUE(test <= longer.c_str());
				PL_ASSERT_TRUE(test <= eq.c_str());
				PL_ASSERT_FALSE(test <= lt.c_str());
				PL_ASSERT_FALSE(test <= shorter.c_str());

				PL_ASSERT_FALSE(gt.c_str() <= test);
				PL_ASSERT_FALSE(longer.c_str() <= test);
				PL_ASSERT_TRUE(eq.c_str() <= test);
				PL_ASSERT_TRUE(lt.c_str() <= test);
				PL_ASSERT_TRUE(shorter.c_str() <= test);
				return true;
			}
			case TestStringType::STR_ASCII: {
				std::string eq = "abcB";
				std::string lt = "abcA";
				std::string gt = "abcC";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test <= gt);
				PL_ASSERT_TRUE(test <= longer);
				PL_ASSERT_TRUE(test <= eq);
				PL_ASSERT_FALSE(test <= lt);
				PL_ASSERT_FALSE(test <= shorter);

				PL_ASSERT_FALSE(gt <= test);
				PL_ASSERT_FALSE(longer <= test);
				PL_ASSERT_TRUE(eq <= test);
				PL_ASSERT_TRUE(lt <= test);
				PL_ASSERT_TRUE(shorter <= test);
				return true;
			}
			case TestStringType::STR_UNICODE: {
				std::string eq = "🐭abc🐭";
				std::string lt = "🐭abc🐁";
				std::string gt = "🐭abc🦊";
				std::string shorter = "🐭ab";
				std::string longer = "🐭abc🦊🦊";

				test = eq;
				PL_ASSERT_TRUE(test <= gt);
				PL_ASSERT_TRUE(test <= longer);
				PL_ASSERT_TRUE(test <= eq);
				PL_ASSERT_FALSE(test <= lt);
				PL_ASSERT_FALSE(test <= shorter);

				PL_ASSERT_FALSE(gt <= test);
				PL_ASSERT_FALSE(longer <= test);
				PL_ASSERT_TRUE(eq <= test);
				PL_ASSERT_TRUE(lt <= test);
				PL_ASSERT_TRUE(shorter <= test);
				return true;
			}
			case TestStringType::OSTR_ASCII: {
				onestring eq = "abcB";
				onestring lt = "abcA";
				onestring gt = "abcC";
				onestring shorter = "ab";
				onestring longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test <= gt);
				PL_ASSERT_TRUE(test <= longer);
				PL_ASSERT_TRUE(test <= eq);
				PL_ASSERT_FALSE(test <= lt);
				PL_ASSERT_FALSE(test <= shorter);

				PL_ASSERT_FALSE(gt <= test);
				PL_ASSERT_FALSE(longer <= test);
				PL_ASSERT_TRUE(eq <= test);
				PL_ASSERT_TRUE(lt <= test);
				PL_ASSERT_TRUE(shorter <= test);
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				onestring eq = "🐭abc🐭";
				onestring lt = "🐭abc🐁";
				onestring gt = "🐭abc🦊";
				onestring shorter = "🐭ab";
				onestring longer = "🐭abc🦊🦊";

				test = eq;
				PL_ASSERT_TRUE(test <= gt);
				PL_ASSERT_TRUE(test <= longer);
				PL_ASSERT_TRUE(test <= eq);
				PL_ASSERT_FALSE(test <= lt);
				PL_ASSERT_FALSE(test <= shorter);

				PL_ASSERT_FALSE(gt <= test);
				PL_ASSERT_FALSE(longer <= test);
				PL_ASSERT_TRUE(eq <= test);
				PL_ASSERT_TRUE(lt <= test);
				PL_ASSERT_TRUE(shorter <= test);
				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB208[a-i]
class TestOnestring_OpGreater : public TestOnestring
{
protected:
	onestring test;

public:
	explicit TestOnestring_OpGreater(TestStringType type) : TestOnestring(type)
	{
	}

	testdoc_t get_title() override
	{
		return "Onestring: Less Than (>) " + title;
	}

	testdoc_t get_docs() override
	{
		return "Test comparison with the > operator.";
	}

	bool janitor() override
	{
		test = "";
		return true;
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				char eq = 'B';
				char lt = 'A';
				char gt = 'C';

				test = eq;
				PL_ASSERT_TRUE(test > lt);
				PL_ASSERT_FALSE(test > eq);
				PL_ASSERT_FALSE(test > gt);

				PL_ASSERT_FALSE(lt > test);
				PL_ASSERT_FALSE(eq > test);
				PL_ASSERT_TRUE(gt > test);
				return true;
			}
			case TestStringType::OCHAR_ASCII: {
				onechar eq = "B";
				onechar lt = "A";
				onechar gt = "C";

				test = eq;
				PL_ASSERT_TRUE(test > lt);
				PL_ASSERT_FALSE(test > eq);
				PL_ASSERT_FALSE(test > gt);

				PL_ASSERT_FALSE(lt > test);
				PL_ASSERT_FALSE(eq > test);
				PL_ASSERT_TRUE(gt > test);
				return true;
			}
			case TestStringType::OCHAR_UNICODE: {
				onechar eq = "🐭";
				onechar lt = "🐁";
				onechar gt = "🦊";

				test = eq;
				PL_ASSERT_TRUE(test > lt);
				PL_ASSERT_FALSE(test > eq);
				PL_ASSERT_FALSE(test > gt);

				PL_ASSERT_FALSE(lt > test);
				PL_ASSERT_FALSE(eq > test);
				PL_ASSERT_TRUE(gt > test);
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				std::string eq = "abcB";
				std::string lt = "abcA";
				std::string gt = "abcC";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test > lt.c_str());
				PL_ASSERT_TRUE(test > shorter.c_str());
				PL_ASSERT_FALSE(test > eq.c_str());
				PL_ASSERT_FALSE(test > gt.c_str());
				PL_ASSERT_FALSE(test > longer.c_str());

				PL_ASSERT_FALSE(lt.c_str() > test);
				PL_ASSERT_FALSE(shorter.c_str() > test);
				PL_ASSERT_FALSE(eq.c_str() > test);
				PL_ASSERT_TRUE(gt.c_str() > test);
				PL_ASSERT_TRUE(longer.c_str() > test);
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				std::string eq = "🐭abc🐭";
				std::string lt = "🐭abc🐁";
				std::string gt = "🐭abc🦊";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test > lt.c_str());
				PL_ASSERT_TRUE(test > shorter.c_str());
				PL_ASSERT_FALSE(test > eq.c_str());
				PL_ASSERT_FALSE(test > gt.c_str());
				PL_ASSERT_FALSE(test > longer.c_str());

				PL_ASSERT_FALSE(lt.c_str() > test);
				PL_ASSERT_FALSE(shorter.c_str() > test);
				PL_ASSERT_FALSE(eq.c_str() > test);
				PL_ASSERT_TRUE(gt.c_str() > test);
				PL_ASSERT_TRUE(longer.c_str() > test);
				return true;
			}
			case TestStringType::STR_ASCII: {
				std::string eq = "abcB";
				std::string lt = "abcA";
				std::string gt = "abcC";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test > lt);
				PL_ASSERT_TRUE(test > shorter);
				PL_ASSERT_FALSE(test > eq);
				PL_ASSERT_FALSE(test > gt);
				PL_ASSERT_FALSE(test > longer);

				PL_ASSERT_FALSE(lt > test);
				PL_ASSERT_FALSE(shorter > test);
				PL_ASSERT_FALSE(eq > test);
				PL_ASSERT_TRUE(gt > test);
				PL_ASSERT_TRUE(longer > test);
				return true;
			}
			case TestStringType::STR_UNICODE: {
				std::string eq = "🐭abc🐭";
				std::string lt = "🐭abc🐁";
				std::string gt = "🐭abc🦊";
				std::string shorter = "🐭ab";
				std::string longer = "🐭abc🦊🦊";

				test = eq;
				PL_ASSERT_TRUE(test > lt);
				PL_ASSERT_TRUE(test > shorter);
				PL_ASSERT_FALSE(test > eq);
				PL_ASSERT_FALSE(test > gt);
				PL_ASSERT_FALSE(test > longer);

				PL_ASSERT_FALSE(lt > test);
				PL_ASSERT_FALSE(shorter > test);
				PL_ASSERT_FALSE(eq > test);
				PL_ASSERT_TRUE(gt > test);
				PL_ASSERT_TRUE(longer > test);
				return true;
			}
			case TestStringType::OSTR_ASCII: {
				onestring eq = "abcB";
				onestring lt = "abcA";
				onestring gt = "abcC";
				onestring shorter = "ab";
				onestring longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test > lt);
				PL_ASSERT_TRUE(test > shorter);
				PL_ASSERT_FALSE(test > eq);
				PL_ASSERT_FALSE(test > gt);
				PL_ASSERT_FALSE(test > longer);

				PL_ASSERT_FALSE(lt > test);
				PL_ASSERT_FALSE(shorter > test);
				PL_ASSERT_FALSE(eq > test);
				PL_ASSERT_TRUE(gt > test);
				PL_ASSERT_TRUE(longer > test);
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				onestring eq = "🐭abc🐭";
				onestring lt = "🐭abc🐁";
				onestring gt = "🐭abc🦊";
				onestring shorter = "🐭ab";
				onestring longer = "🐭abc🦊🦊";

				test = eq;
				PL_ASSERT_TRUE(test > lt);
				PL_ASSERT_TRUE(test > shorter);
				PL_ASSERT_FALSE(test > eq);
				PL_ASSERT_FALSE(test > gt);
				PL_ASSERT_FALSE(test > longer);

				PL_ASSERT_FALSE(lt > test);
				PL_ASSERT_FALSE(shorter > test);
				PL_ASSERT_FALSE(eq > test);
				PL_ASSERT_TRUE(gt > test);
				PL_ASSERT_TRUE(longer > test);
				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB209[a-i]
class TestOnestring_OpGreaterEqual : public TestOnestring
{
protected:
	onestring test;

public:
	explicit TestOnestring_OpGreaterEqual(TestStringType type)
	: TestOnestring(type)
	{
	}

	testdoc_t get_title() override
	{
		return "Onestring: Greater/Equal (>=) " + title;
	}

	testdoc_t get_docs() override
	{
		return "Test comparison with the >= operator.";
	}

	bool janitor() override
	{
		test = "";
		return true;
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				char eq = 'B';
				char lt = 'A';
				char gt = 'C';

				test = eq;
				PL_ASSERT_TRUE(test >= lt);
				PL_ASSERT_TRUE(test >= eq);
				PL_ASSERT_FALSE(test >= gt);

				PL_ASSERT_FALSE(lt >= test);
				PL_ASSERT_TRUE(eq >= test);
				PL_ASSERT_TRUE(gt >= test);
				return true;
			}
			case TestStringType::OCHAR_ASCII: {
				onechar eq = "B";
				onechar lt = "A";
				onechar gt = "C";

				test = eq;
				PL_ASSERT_TRUE(test >= lt);
				PL_ASSERT_TRUE(test >= eq);
				PL_ASSERT_FALSE(test >= gt);

				PL_ASSERT_FALSE(lt >= test);
				PL_ASSERT_TRUE(eq >= test);
				PL_ASSERT_TRUE(gt >= test);
				return true;
			}
			case TestStringType::OCHAR_UNICODE: {
				onechar eq = "🐭";
				onechar lt = "🐁";
				onechar gt = "🦊";

				test = eq;
				PL_ASSERT_TRUE(test >= lt);
				PL_ASSERT_TRUE(test >= eq);
				PL_ASSERT_FALSE(test >= gt);

				PL_ASSERT_FALSE(lt >= test);
				PL_ASSERT_TRUE(eq >= test);
				PL_ASSERT_TRUE(gt >= test);
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				std::string eq = "abcB";
				std::string lt = "abcA";
				std::string gt = "abcC";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test >= lt.c_str());
				PL_ASSERT_TRUE(test >= shorter.c_str());
				PL_ASSERT_TRUE(test >= eq.c_str());
				PL_ASSERT_FALSE(test >= gt.c_str());
				PL_ASSERT_FALSE(test >= longer.c_str());

				PL_ASSERT_FALSE(lt.c_str() >= test);
				PL_ASSERT_FALSE(shorter.c_str() >= test);
				PL_ASSERT_TRUE(eq.c_str() >= test);
				PL_ASSERT_TRUE(gt.c_str() >= test);
				PL_ASSERT_TRUE(longer.c_str() >= test);
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				std::string eq = "🐭abc🐭";
				std::string lt = "🐭abc🐁";
				std::string gt = "🐭abc🦊";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test >= lt.c_str());
				PL_ASSERT_TRUE(test >= shorter.c_str());
				PL_ASSERT_TRUE(test >= eq.c_str());
				PL_ASSERT_FALSE(test >= gt.c_str());
				PL_ASSERT_FALSE(test >= longer.c_str());

				PL_ASSERT_FALSE(lt.c_str() >= test);
				PL_ASSERT_FALSE(shorter.c_str() >= test);
				PL_ASSERT_TRUE(eq.c_str() >= test);
				PL_ASSERT_TRUE(gt.c_str() >= test);
				PL_ASSERT_TRUE(longer.c_str() >= test);
				return true;
			}
			case TestStringType::STR_ASCII: {
				std::string eq = "abcB";
				std::string lt = "abcA";
				std::string gt = "abcC";
				std::string shorter = "ab";
				std::string longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test >= lt);
				PL_ASSERT_TRUE(test >= shorter);
				PL_ASSERT_TRUE(test >= eq);
				PL_ASSERT_FALSE(test >= gt);
				PL_ASSERT_FALSE(test >= longer);

				PL_ASSERT_FALSE(lt >= test);
				PL_ASSERT_FALSE(shorter >= test);
				PL_ASSERT_TRUE(eq >= test);
				PL_ASSERT_TRUE(gt >= test);
				PL_ASSERT_TRUE(longer >= test);
				return true;
			}
			case TestStringType::STR_UNICODE: {
				std::string eq = "🐭abc🐭";
				std::string lt = "🐭abc🐁";
				std::string gt = "🐭abc🦊";
				std::string shorter = "🐭ab";
				std::string longer = "🐭abc🦊🦊";

				test = eq;
				PL_ASSERT_TRUE(test >= lt);
				PL_ASSERT_TRUE(test >= shorter);
				PL_ASSERT_TRUE(test >= eq);
				PL_ASSERT_FALSE(test >= gt);
				PL_ASSERT_FALSE(test >= longer);

				PL_ASSERT_FALSE(lt >= test);
				PL_ASSERT_FALSE(shorter >= test);
				PL_ASSERT_TRUE(eq >= test);
				PL_ASSERT_TRUE(gt >= test);
				PL_ASSERT_TRUE(longer >= test);
				return true;
			}
			case TestStringType::OSTR_ASCII: {
				onestring eq = "abcB";
				onestring lt = "abcA";
				onestring gt = "abcC";
				onestring shorter = "ab";
				onestring longer = "abcabc";

				test = eq;
				PL_ASSERT_TRUE(test >= lt);
				PL_ASSERT_TRUE(test >= shorter);
				PL_ASSERT_TRUE(test >= eq);
				PL_ASSERT_FALSE(test >= gt);
				PL_ASSERT_FALSE(test >= longer);

				PL_ASSERT_FALSE(lt >= test);
				PL_ASSERT_FALSE(shorter >= test);
				PL_ASSERT_TRUE(eq >= test);
				PL_ASSERT_TRUE(gt >= test);
				PL_ASSERT_TRUE(longer >= test);
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				onestring eq = "🐭abc🐭";
				onestring lt = "🐭abc🐁";
				onestring gt = "🐭abc🦊";
				onestring shorter = "🐭ab";
				onestring longer = "🐭abc🦊🦊";

				test = eq;
				PL_ASSERT_TRUE(test >= lt);
				PL_ASSERT_TRUE(test >= shorter);
				PL_ASSERT_TRUE(test >= eq);
				PL_ASSERT_FALSE(test >= gt);
				PL_ASSERT_FALSE(test >= longer);

				PL_ASSERT_FALSE(lt >= test);
				PL_ASSERT_FALSE(shorter >= test);
				PL_ASSERT_TRUE(eq >= test);
				PL_ASSERT_TRUE(gt >= test);
				PL_ASSERT_TRUE(longer >= test);
				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB210
class TestOnestring_At : public Test
{
protected:
	onestring test = "⛰ The Matterhorn ⛰";

public:
	TestOnestring_At() {}

	testdoc_t get_title() override { return "Onestring: at()"; }

	testdoc_t get_docs() override
	{
		return "Test accessing one character of a onestring with at()";
	}

	bool run() override
	{
		onechar toCheck;
		toCheck = "⛰";
		PL_ASSERT_EQUAL(test.at(17), toCheck);
		return true;
	}
};

// O-tB211
class TestOnestring_OpAt : public Test
{
protected:
	onestring test = "⛰ The Matterhorn ⛰";

public:
	TestOnestring_OpAt() {}

	testdoc_t get_title() override { return "Onestring: at ([])"; }

	testdoc_t get_docs() override
	{
		return "Test accessing one character of a onestring with the [] "
			   "operator.";
	}

	bool run() override
	{
		onechar toCheck;
		toCheck = "⛰";
		PL_ASSERT_EQUAL(test[17], toCheck);
		return true;
	}
};

// O-tB212
class TestOnestring_Back : public Test
{
protected:
	onestring start = "⛰ The Matterhorn ⛰";
	onestring goal = "⛰ The Matterhorn !";
	onestring test;

public:
	TestOnestring_Back() {}

	testdoc_t get_title() override { return "Onestring: back()"; }

	testdoc_t get_docs() override
	{
		return "Test accessing the last character of a onestring with back()";
	}

	bool janitor() override
	{
		test = start;
		return (test == start);
	}

	bool run() override
	{
		onechar& ochr = test.back();
		PL_ASSERT_EQUAL(ochr, "⛰");

		ochr = "!";
		PL_ASSERT_EQUAL(ochr, "!");
		PL_ASSERT_EQUAL(test, goal);

		return true;
	}
};

// O-tB213
class TestOnestring_Front : public Test
{
protected:
	onestring start = "⛰ The Matterhorn ⛰";
	onestring goal = "! The Matterhorn ⛰";
	onestring test;

public:
	TestOnestring_Front() {}

	testdoc_t get_title() override { return "Onestring: front()"; }

	testdoc_t get_docs() override
	{
		return "Test accessing the first character of a onestring with front()";
	}

	bool janitor() override
	{
		test = start;
		return (test == start);
	}

	bool run() override
	{
		onechar& ochr = test.front();
		PL_ASSERT_EQUAL(ochr, "⛰");

		ochr = "!";
		PL_ASSERT_EQUAL(ochr, "!");
		PL_ASSERT_EQUAL(test, goal);

		return true;
	}
};

// O-tB214
class TestOnestring_Capacity : public Test
{
protected:
	onestring test = "🐦 ❤️ my big sphinx of 💎.";

public:
	TestOnestring_Capacity() {}

	testdoc_t get_title() override { return "Onestring: at ([])"; }

	testdoc_t get_docs() override
	{
		return "Test accessing one character of a onestring with the [] "
			   "operator.";
	}

	bool run() override
	{
		size_t expected_capacity = onestring::BASE_SIZE;
		size_t string_length = test.length();
		while (expected_capacity < string_length) {
			expected_capacity *= onestring::RESIZE_FACTOR;
		}
		PL_ASSERT_EQUAL(test.capacity(), expected_capacity);
		return true;
	}
};

// O-tB215
class TestOnestring_PopBack : public Test
{
protected:
	onestring start = "The quick brown 🦊 jumped over the lazy 🐶📣";
	onestring target = "The quick brown 🦊 jumped over the lazy 🐶";
	onestring test;

public:
	TestOnestring_PopBack() {}

	testdoc_t get_title() override { return "Onestring: pop_back()"; }

	testdoc_t get_docs() override
	{
		return "Tests for removing characters from a onestring using "
			   "pop_back().";
	}

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		test = start;
		return (test == start);
	}

	bool run() override
	{
		test.pop_back();
		PL_ASSERT_EQUAL(test, target);
		return true;
	}
};

// O-tB216
class TestOnestring_Length : public Test
{
protected:
	onestring start = "Ø÷Ø÷Ø÷Ø÷Ø÷Ø÷Ø÷";
	onestring test;

public:
	TestOnestring_Length() {}

	testdoc_t get_title() override { return "Onestring: length()"; }

	testdoc_t get_docs() override { return "Test the length() function."; }

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		test = start;
		return (test == start);
	}

	bool run() override
	{
		PL_ASSERT_EQUAL(test.length(), 14U);
		test.pop_back();
		PL_ASSERT_EQUAL(test.length(), 13U);
		return true;
	}
};

// O-tB217
class TestOnestring_Size : public Test
{
protected:
	onestring start = "M©‽🐭‽©M";
	onestring test;

public:
	TestOnestring_Size() {}

	testdoc_t get_title() override { return "Onestring: size()"; }

	testdoc_t get_docs() override { return "Test the size() function."; }

	bool pre() override { return janitor(); }

	bool janitor() override
	{
		test = start;
		return (test == start);
	}

	bool run() override
	{
		PL_ASSERT_EQUAL(test.size(4), 11u);
		PL_ASSERT_EQUAL(test.size(4, 3), 11u);

		PL_ASSERT_EQUAL(test.size(), 17u);
		// Remove last 'M' (1 byte)
		test.pop_back();
		PL_ASSERT_EQUAL(test.size(), 16u);
		// Remove last '©' (2 bytes)
		test.pop_back();
		PL_ASSERT_EQUAL(test.size(), 14u);
		// Remove last '‽' (3 bytes)
		test.pop_back();
		PL_ASSERT_EQUAL(test.size(), 11u);
		// Remove last '🐭' (4 bytes)
		test.pop_back();
		PL_ASSERT_EQUAL(test.size(), 7u);
		return true;
	}
};

// O-tB218
class TestOnestring_Copy : public Test
{
protected:
	onestring test = "🐦 ❤ my big sphinx of 💎.";
	onestring sub1 = "🐦 ❤";   // len=3, pos=0
	onestring sub2 = "of 💎";  // len=4, pos=18

public:
	TestOnestring_Copy() {}

	testdoc_t get_title() override { return "Onestring: copy()"; }

	testdoc_t get_docs() override
	{
		return "Test copying to a c-string with copy().";
	}

	bool run() override
	{
		// Test copying the entire string.
		char* cstr = new char[test.size()];
		test.copy(cstr, test.size());
		PL_ASSERT_EQUAL(test, cstr);
		delete[] cstr;

		// Test copying substring 1
		cstr = new char[test.size(3, 0)];
		test.copy(cstr, test.size(3, 0), 3, 0);
		PL_ASSERT_EQUAL(sub1, cstr);
		delete[] cstr;

		// Test copying substring 2
		cstr = new char[test.size(4, 18)];
		test.copy(cstr, test.size(4, 18), 4, 18);
		PL_ASSERT_EQUAL(sub2, cstr);
		delete[] cstr;

		return true;
	}
};

// O-tB219
class TestOnestring_CStr : public Test
{
public:
	TestOnestring_CStr() {}

	testdoc_t get_title() override { return "Onestring: c_str()"; }

	testdoc_t get_docs() override
	{
		return "Test the c-string returned by the c_str() function.";
	}

	bool run() override
	{
		const char* cstr = "The quick brown 🦊 jumped over the lazy 🐶.";
		onestring test = cstr;
		PL_ASSERT_EQUAL(strcmp(cstr, test.c_str()), 0);
		return true;
	}
};

// O-tB220
class TestOnestring_Empty : public Test
{
protected:
	onestring test1 = "";
	onestring test2 = "a";

public:
	TestOnestring_Empty() {}

	testdoc_t get_title() override { return "Onestring: empty()"; }

	testdoc_t get_docs() override
	{
		return "Test that the empty() function returns true on an empty "
			   "string.";
	}

	bool run() override
	{
		PL_ASSERT_TRUE(test1.empty());
		PL_ASSERT_FALSE(test2.empty());
		return true;
	}
};

// O-tB221
class TestOnestring_Substr : public Test
{
protected:
	onestring start = "🐦 ❤ my big sphinx of 💎.";
	onestring sub1 = "🐦 ❤";      // pos = 0, len = 3
	onestring sub2 = "of 💎";     // pos = 18, len = 4
	onestring sub3 = "x of 💎.";  // pos = 16, len = (undefined)
public:
	TestOnestring_Substr() {}

	testdoc_t get_title() override { return "Onestring: substr()"; }

	testdoc_t get_docs() override
	{
		return "Test creation of substrings with substr()";
	}

	bool run() override
	{
		onestring test1 = start.substr(0, 3);
		PL_ASSERT_EQUAL(test1, sub1);

		onestring test2 = start.substr(18, 4);
		PL_ASSERT_EQUAL(test2, sub2);

		onestring test3 = start.substr(16);
		PL_ASSERT_EQUAL(test3, sub3);

		return true;
	}
};

// O-tB222
class TestOnestring_Append : public TestOnestring
{
protected:
	onestring start = "TEST";
	onestring test;

public:
	explicit TestOnestring_Append(TestStringType type) : TestOnestring(type) {}

	testdoc_t get_title() override { return "Onestring: Append " + title; }

	testdoc_t get_docs() override
	{
		return "Test appending to a onestring with append().";
	}

	bool janitor() override
	{
		test = start;
		return (test == start);
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				char ch = '!';
				test.append(ch);
				PL_ASSERT_EQUAL(test, "TEST!");

				test.append(ch, 3);
				PL_ASSERT_EQUAL(test, "TEST!!!!");
				return true;
			}
			case TestStringType::OCHAR_ASCII: {
				onechar ochr = "!";
				test.append(ochr);
				PL_ASSERT_EQUAL(test, "TEST!");

				test.append(ochr, 3);
				PL_ASSERT_EQUAL(test, "TEST!!!!");
				return true;
			}
			case TestStringType::OCHAR_UNICODE: {
				onechar ochr = "‽";
				test.append(ochr);
				PL_ASSERT_EQUAL(test, "TEST‽");

				test.append(ochr, 3);
				PL_ASSERT_EQUAL(test, "TEST‽‽‽‽");
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				std::string str = "!!!";
				test.append(str.c_str());
				PL_ASSERT_EQUAL(test, "TEST!!!");

				test.append(str.c_str(), 3);
				PL_ASSERT_EQUAL(test, "TEST!!!!!!!!!!!!");
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				std::string str = "‽‽‽";
				test.append(str.c_str());
				PL_ASSERT_EQUAL(test, "TEST‽‽‽");

				test.append(str.c_str(), 3);
				PL_ASSERT_EQUAL(test, "TEST‽‽‽‽‽‽‽‽‽‽‽‽");
				return true;
			}
			case TestStringType::STR_ASCII: {
				std::string str = "!!!";
				test.append(str);
				PL_ASSERT_EQUAL(test, "TEST!!!");

				test.append(str, 3);
				PL_ASSERT_EQUAL(test, "TEST!!!!!!!!!!!!");
				return true;
			}
			case TestStringType::STR_UNICODE: {
				std::string str = "‽‽‽";
				test.append(str);
				PL_ASSERT_EQUAL(test, "TEST‽‽‽");

				test.append(str, 3);
				PL_ASSERT_EQUAL(test, "TEST‽‽‽‽‽‽‽‽‽‽‽‽");
				return true;
			}
			case TestStringType::OSTR_ASCII: {
				onestring ostr = "!!!";
				test.append(ostr);
				PL_ASSERT_EQUAL(test, "TEST!!!");

				test.append(ostr, 3);
				PL_ASSERT_EQUAL(test, "TEST!!!!!!!!!!!!");
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				onestring ostr = "‽‽‽";
				test.append(ostr);
				PL_ASSERT_EQUAL(test, "TEST‽‽‽");

				test.append(ostr, 3);
				PL_ASSERT_EQUAL(test, "TEST‽‽‽‽‽‽‽‽‽‽‽‽");
				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB223
class TestOnestring_OpAppend : public TestOnestring
{
protected:
	onestring start = "TEST";
	onestring test = "TEST";

public:
	explicit TestOnestring_OpAppend(TestStringType type) : TestOnestring(type)
	{
	}

	testdoc_t get_title() override { return "Onestring: Append (+=) " + title; }

	testdoc_t get_docs() override
	{
		return "Test appending to a onestring with the += operator.";
	}

	bool janitor() override
	{
		test = start;
		return (test == start);
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				char ch = '!';
				test += ch;
				PL_ASSERT_EQUAL(test, "TEST!");
				return true;
			}
			case TestStringType::OCHAR_ASCII: {
				onechar ochr = "!";
				test += ochr;
				PL_ASSERT_EQUAL(test, "TEST!");
				return true;
			}
			case TestStringType::OCHAR_UNICODE: {
				onechar ochr = "‽";
				test += ochr;
				PL_ASSERT_EQUAL(test, "TEST‽");
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				std::string str = "!!!";
				test += str.c_str();
				PL_ASSERT_EQUAL(test, "TEST!!!");
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				std::string str = "‽‽‽";
				test += str.c_str();
				PL_ASSERT_EQUAL(test, "TEST‽‽‽");
				return true;
			}
			case TestStringType::STR_ASCII: {
				std::string str = "!!!";
				test += str;
				PL_ASSERT_EQUAL(test, "TEST!!!");
				return true;
			}
			case TestStringType::STR_UNICODE: {
				std::string str = "‽‽‽";
				test += str;
				PL_ASSERT_EQUAL(test, "TEST‽‽‽");
				return true;
			}
			case TestStringType::OSTR_ASCII: {
				onestring ostr = "!!!";
				test += ostr;
				PL_ASSERT_EQUAL(test, "TEST!!!");
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				onestring ostr = "‽‽‽";
				test += ostr;
				PL_ASSERT_EQUAL(test, "TEST‽‽‽");
				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB224
class TestOnestring_Clear : public Test
{
protected:
	onestring start = "Ø÷Ø÷Ø÷Ø÷Ø÷Ø÷Ø÷";
	onestring test;

public:
	TestOnestring_Clear() {}

	testdoc_t get_title() override { return "Onestring: clear()"; }

	testdoc_t get_docs() override
	{
		return "Tests for clearing all items in a onestring with clear().";
	}

	bool janitor() override
	{
		test = start;
		return (!test.empty());
	}

	bool run() override
	{
		test.clear();
		PL_ASSERT_TRUE(test.empty());
		return true;
	}
};

// O-tB225
class TestOnestring_Erase : public Test
{
protected:
	onestring start = "The quick brown 🦊 jumped over the lazy 🐶.";
	onestring outcome1 = "The lazy 🐶.";  // pos = 4, len = 30
	onestring outcome2 =
		"The quick brown 🦊 jumped";  // pos = 24, len = (undefined)
	onestring test;

public:
	TestOnestring_Erase() {}

	testdoc_t get_title() override { return "Onestring: erase()"; }

	testdoc_t get_docs() override
	{
		return "Test erasing part of a string with erase()";
	}

	bool janitor() override
	{
		test = start;
		return (test == start);
	}

	bool run() override
	{
		test.erase(4, 30);
		PL_ASSERT_EQUAL(test, outcome1);

		// Reset the test string
		janitor();

		test.erase(24);
		PL_ASSERT_EQUAL(test, outcome2);

		return true;
	}
};

// O-tB226[a-i]
class TestOnestring_Insert : public TestOnestring
{
protected:
	// This string is designed to force a resize on a single insert.
	onestring start = "TSTING!!";
	onestring test;

public:
	explicit TestOnestring_Insert(TestStringType type) : TestOnestring(type) {}

	testdoc_t get_title() override { return "Onestring: Insert " + title; }

	testdoc_t get_docs() override
	{
		return "Test adding to a onestring with insert().";
	}

	bool janitor() override
	{
		test = start;
		return (test == start);
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				char ch = 'E';
				test.insert(1, ch);
				PL_ASSERT_EQUAL(test, "TESTING!!");
				return true;
			}
			case TestStringType::OCHAR_ASCII: {
				onechar ochr = "E";
				test.insert(1, ochr);
				PL_ASSERT_EQUAL(test, "TESTING!!");
				return true;
			}
			case TestStringType::OCHAR_UNICODE: {
				onechar ochr = "Ё";
				std::cout << ochr.c_str() << std::endl;
				test.insert(1, ochr);
				PL_ASSERT_EQUAL(test, "TЁSTING!!");
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				std::string cstr = "ESS";
				test.insert(1, cstr.c_str());
				PL_ASSERT_EQUAL(test, "TESSSTING!!");
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				std::string cstr = "ЁSS";
				test.insert(1, cstr.c_str());
				PL_ASSERT_EQUAL(test, "TЁSSSTING!!");
				return true;
			}
			case TestStringType::STR_ASCII: {
				std::string str = "ESS";
				test.insert(1, str);
				PL_ASSERT_EQUAL(test, "TESSSTING!!");
				return true;
			}
			case TestStringType::STR_UNICODE: {
				std::string str = "ЁSS";
				test.insert(1, str);
				PL_ASSERT_EQUAL(test, "TЁSSSTING!!");
				return true;
			}
			case TestStringType::OSTR_ASCII: {
				onestring ostr = "ESS";
				test.insert(1, ostr);
				PL_ASSERT_EQUAL(test, "TESSSTING!!");
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				onestring ostr = "ЁSS";
				test.insert(1, ostr);
				PL_ASSERT_EQUAL(test, "TЁSSSTING!!");
				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB227[a-i]
class TestOnestring_Replace : public TestOnestring
{
protected:
	onestring start = "The red fox jumped over the dog.";
	// replace pos=31, len=1, '!'
	onestring goal1 = "The red fox jumped over the dog!";
	// replace pos=31, len=1, '…'
	onestring goal1b = "The red fox jumped over the dog…";
	// replace pos=8, len=3, '🦊'
	onestring goal2 = "The red 🦊 jumped over the dog!";
	// replace pos=26, len=3, "lazy 🐶"
	onestring goal3 = "The red 🦊 jumped over the lazy 🐶!";
	// replace pos=4, len=3, "quick brown"
	onestring goal4 = "The quick brown 🦊 jumped over the lazy 🐶!";
	onestring test;

public:
	explicit TestOnestring_Replace(TestStringType type) : TestOnestring(type) {}

	testdoc_t get_title() override { return "Onestring: Replace " + title; }

	testdoc_t get_docs() override
	{
		return "Test replacing part of a onestring with replace().";
	}

	bool janitor() override
	{
		test = start;
		return (test == start);
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				char ch = '!';
				test.replace(31, 1, ch);
				PL_ASSERT_EQUAL(test, goal1);
				return true;
			}
			case TestStringType::OCHAR_ASCII: {
				onechar ochr = "!";
				test.replace(31, 1, ochr);
				PL_ASSERT_EQUAL(test, goal1);
				return true;
			}
			case TestStringType::OCHAR_UNICODE: {
				onechar ochr = "…";
				test.replace(31, 1, ochr);
				PL_ASSERT_EQUAL(test, goal1b);
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				std::string cstr = "!";
				test.replace(31, 1, cstr.c_str());
				PL_ASSERT_EQUAL(test, goal1);
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				std::string cstr = "!";
				test.replace(31, 1, cstr.c_str());
				PL_ASSERT_EQUAL(test, goal1);

				cstr = "🦊";
				test.replace(8, 3, cstr.c_str());
				PL_ASSERT_EQUAL(test, goal2);

				cstr = "lazy 🐶";
				test.replace(26, 3, cstr.c_str());
				PL_ASSERT_EQUAL(test, goal3);

				cstr = "The quick brown fox";
				test.replace(4, 3, cstr.c_str(), 4, 11);
				PL_ASSERT_EQUAL(test, goal4);

				return true;
			}
			case TestStringType::STR_ASCII: {
				std::string str = "!";
				test.replace(31, 1, str);
				PL_ASSERT_EQUAL(test, goal1);
				return true;
			}
			case TestStringType::STR_UNICODE: {
				std::string str = "!";
				test.replace(31, 1, str);
				PL_ASSERT_EQUAL(test, goal1);

				str = "🦊";
				test.replace(8, 3, str);
				PL_ASSERT_EQUAL(test, goal2);

				str = "lazy 🐶";
				test.replace(26, 3, str);
				PL_ASSERT_EQUAL(test, goal3);

				str = "The quick brown fox";
				test.replace(4, 3, str, 4, 11);
				PL_ASSERT_EQUAL(test, goal4);

				return true;
			}
			case TestStringType::OSTR_ASCII: {
				onestring ostr = "!";
				test.replace(31, 1, ostr);
				PL_ASSERT_EQUAL(test, goal1);
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				onestring ostr = "!";
				test.replace(31, 1, ostr);
				PL_ASSERT_EQUAL(test, goal1);

				ostr = "🦊";
				test.replace(8, 3, ostr);
				PL_ASSERT_EQUAL(test, goal2);

				ostr = "lazy 🐶";
				test.replace(26, 3, ostr);
				PL_ASSERT_EQUAL(test, goal3);

				ostr = "The quick brown fox";
				test.replace(4, 3, ostr, 4, 11);
				PL_ASSERT_EQUAL(test, goal4);

				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB228
class TestOnestring_Reverse : public Test
{
protected:
	onestring start = "The quick brown 🦊 jumped over the lazy 🐶.";
	onestring test;
	onestring goal1 =
		".🐶 yzal eht revo depmuj 🦊 nworb kciuq ehT";  // 41 characters
	onestring goal2 =
		"🐶 yzal eht revo depmuj 🦊 nworb kciuq ehT";  // 40 characters
	onestring goal3 = "The quick brown 🦊 jumped over the lazy 🐶";

public:
	TestOnestring_Reverse() {}

	testdoc_t get_title() override { return "Onestring: reverse()"; }

	testdoc_t get_docs() override
	{
		return "Test reversing a string reverse()";
	}

	bool janitor() override
	{
		test = start;
		return (test == start);
	}

	bool run() override
	{
		// Test reversal of ODD number of characters (41)
		test.reverse();
		PL_ASSERT_EQUAL(test, goal1);
		test.reverse();
		PL_ASSERT_EQUAL(test, start);

		/* Remove a single character from the end, to test reversal
		 * of EVEN number of characters (40) */
		test.pop_back();
		test.reverse();
		PL_ASSERT_EQUAL(test, goal2);
		test.reverse();
		PL_ASSERT_EQUAL(test, goal3);

		return true;
	}
};

// O-tB229
class TestOnestring_Swap : public Test
{
protected:
	std::string start1 = "The quick brown 🦊 jumped over the lazy 🐶.";
	std::string start2 = "🐦 ❤️ my big sphinx of 💎.";
	onestring test_ostr_1;
	onestring test_ostr_2;
	std::string test_str;

public:
	TestOnestring_Swap() {}

	testdoc_t get_title() override { return "Onestring: swap()"; }

	testdoc_t get_docs() override
	{
		return "Test swapping two strings with swap()";
	}

	bool janitor() override
	{
		test_ostr_1 = start1;
		test_ostr_2 = start2;
		test_str = start2;
		return (test_ostr_1 == start1 && test_ostr_2 == start2 &&
				test_str == start2);
	}

	bool run() override
	{
		test_ostr_1.swap(test_ostr_2);
		PL_ASSERT_EQUAL(test_ostr_1, start2);
		PL_ASSERT_EQUAL(test_ostr_2, start1);

		test_ostr_2.swap(test_str);
		PL_ASSERT_EQUAL(test_ostr_2, start2);
		PL_ASSERT_EQUAL(test_str, start1);

		return true;
	}
};

// O-tB230
class TestOnestring_Expand : public Test
{
public:
	TestOnestring_Expand() {}

	testdoc_t get_title() override { return "Onestring: Expand"; }

	testdoc_t get_docs() override
	{
		return "Test directly expanding the allocated space with expand().";
	}

	bool run() override
	{
		onestring test;
		test.append("🐉🐉🐉");
		PL_ASSERT_GREATER_EQUAL(test.capacity(), 3u);

		test.expand(3);
		test.append("🐉🐉🐉");
		PL_ASSERT_GREATER_EQUAL(test.capacity(), 6u);

		test.expand(9);
		test.append("🐉🐉🐉🐉🐉🐉🐉🐉🐉");
		PL_ASSERT_GREATER_EQUAL(test.capacity(), 15u);

		return true;
	}
};

// O-tB231
class TestOnestring_Reserve : public Test
{
public:
	TestOnestring_Reserve() {}

	testdoc_t get_title() override { return "Onestring: Reserve"; }

	testdoc_t get_docs() override
	{
		return "Test directly reserving allocated space with reserve().";
	}

	bool run() override
	{
		onestring test;
		test.reserve(10);
		PL_ASSERT_GREATER_EQUAL(test.capacity(), 10u);

		test.reserve(45);
		PL_ASSERT_GREATER_EQUAL(test.capacity(), 55u);

		test.reserve(99);
		PL_ASSERT_GREATER_EQUAL(test.capacity(), 99u);

		return true;
	}
};

// O-tB232
class TestOnestring_Resize : public Test
{
public:
	TestOnestring_Resize() {}

	testdoc_t get_title() override { return "Onestring: Resize"; }

	testdoc_t get_docs() override
	{
		return "Test resizing up and down with resize().";
	}

	bool run() override
	{
		onestring test = "Hello!";
		test.resize(9, '!');
		PL_ASSERT_EQUAL(test.capacity(), 9u);
		PL_ASSERT_EQUAL(test, "Hello!!!!");

		test.resize(5);
		PL_ASSERT_EQUAL(test.capacity(), 5u);
		PL_ASSERT_EQUAL(test, "Hello");

		test.resize(10);
		PL_ASSERT_EQUAL(test.capacity(), 10u);
		PL_ASSERT_EQUAL(test, "Hello");

		return true;
	}
};

// O-tB233
class TestOnestring_ShrinkToFit : public Test
{
public:
	TestOnestring_ShrinkToFit() {}

	testdoc_t get_title() override { return "Onestring: Shrink To Fit"; }

	testdoc_t get_docs() override
	{
		return "Test shrinking capacity to the number of elements with "
			   "shrink_to_fit()";
	}

	bool run() override
	{
		onestring test = "Hello!!";
		test.shrink_to_fit();
		PL_ASSERT_EQUAL(test.capacity(), 7u);
		PL_ASSERT_EQUAL(test, "Hello!!");

		test.append("!!");
		test.shrink_to_fit();
		PL_ASSERT_EQUAL(test.capacity(), 9u);
		PL_ASSERT_EQUAL(test, "Hello!!!!");

		return true;
	}
};

// O-tB234
class TestOnestring_ForceResize : public Test
{
protected:
	onestring target = "🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉🐉";

public:
	TestOnestring_ForceResize() {}

	testdoc_t get_title() override { return "Onestring: Force Resize"; }

	testdoc_t get_docs() override
	{
		return "Append characters to force resizing of the Onestring's "
			   "internal structure.";
	}

	bool run() override
	{
		onestring test;
		for (size_t i = 0; i < target.length(); ++i) {
			test.append("🐉");
		}
		PL_ASSERT_EQUAL(test, target);
		return true;
	}
};

// O-tS234
class TestOnestring_ForceResizeStress : public Test
{
public:
	TestOnestring_ForceResizeStress() {}

	testdoc_t get_title() override
	{
		return "Onestring: Force Resize (Stress Test)";
	}

	testdoc_t get_docs() override
	{
		return "Append characters to force resizing of the Onestring's "
			   "internal structure.";
	}

	bool run() override
	{
		onestring test;
		size_t limit = 1000000;
		for (size_t i = 0; i < limit; ++i) {
			test.append("🐉");
		}
		PL_ASSERT_EQUAL(test[limit - 1], "🐉");
		return true;
	}
};

// O-tB240
class TestOnestring_OpPlus : public TestOnestring
{
protected:
	onestring start = "TEST";
	onestring test = "TEST";

public:
	explicit TestOnestring_OpPlus(TestStringType type) : TestOnestring(type) {}

	testdoc_t get_title() override { return "Onestring: Plus (+) " + title; }

	testdoc_t get_docs() override
	{
		return "Test appending to a onestring with the + operator.";
	}

	bool janitor() override
	{
		test = start;
		return (test == start);
	}

	bool run() override
	{
		switch (stringType) {
			case TestStringType::CHAR: {
				char ch = '!';
				test = test + ch;
				PL_ASSERT_EQUAL(test, "TEST!");
				return true;
			}
			case TestStringType::CSTR_ASCII: {
				std::string str = "!!!";
				test = test + str.c_str();
				PL_ASSERT_EQUAL(test, "TEST!!!");
				return true;
			}
			case TestStringType::CSTR_UNICODE: {
				std::string str = "‽‽‽";
				test = test + str.c_str();
				PL_ASSERT_EQUAL(test, "TEST‽‽‽");
				return true;
			}
			case TestStringType::STR_ASCII: {
				std::string str = "!!!";
				test = test + str;
				PL_ASSERT_EQUAL(test, "TEST!!!");
				return true;
			}
			case TestStringType::STR_UNICODE: {
				std::string str = "‽‽‽";
				test = test + str;
				PL_ASSERT_EQUAL(test, "TEST‽‽‽");
				return true;
			}
			case TestStringType::OSTR_ASCII: {
				onestring ostr = "!!!";
				test = test + ostr;
				PL_ASSERT_EQUAL(test, "TEST!!!");
				return true;
			}
			case TestStringType::OSTR_UNICODE: {
				onestring ostr = "‽‽‽";
				test = test + ostr;
				PL_ASSERT_EQUAL(test, "TEST‽‽‽");
				return true;
			}
			default: {
				// Can't reach
				return false;
			}
		}
	}
};

// O-tB241
class TestOnestring_Cast : public Test
{
protected:
	onestring start = "The quick brown 🦊 jumped over the lazy 🐶.";
	std::string result = "The quick brown 🦊 jumped over the lazy 🐶.";

public:
	explicit TestOnestring_Cast() {}

	testdoc_t get_title() override { return "Onestring: Cast to std::string"; }

	testdoc_t get_docs() override
	{
		return "Test casting a Onestring to a std::string.";
	}

	bool run() override
	{
		std::string str = static_cast<std::string>(start);
		PL_ASSERT_EQUAL(str, result);
		return true;
	}
};

class TestSuite_Onestring : public TestSuite
{
public:
	explicit TestSuite_Onestring() {}

	testdoc_t get_title() override { return "Onestring Tests"; }

	void load_tests() override
	{
		register_test("O-tB201a",
					  new TestOnestring_Assign(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB201b",
					  new TestOnestring_Assign(
						  TestOnestring::TestStringType::OCHAR_ASCII));
		register_test("O-tB201c",
					  new TestOnestring_Assign(
						  TestOnestring::TestStringType::OCHAR_UNICODE));
		register_test("O-tB201d",
					  new TestOnestring_Assign(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB201e",
					  new TestOnestring_Assign(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB201f",
					  new TestOnestring_Assign(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB201g",
					  new TestOnestring_Assign(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB201h",
					  new TestOnestring_Assign(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB201i",
					  new TestOnestring_Assign(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB202a",
					  new TestOnestring_Equals(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB202b",
					  new TestOnestring_Equals(
						  TestOnestring::TestStringType::OCHAR_ASCII));
		register_test("O-tB202c",
					  new TestOnestring_Equals(
						  TestOnestring::TestStringType::OCHAR_UNICODE));
		register_test("O-tB202d",
					  new TestOnestring_Equals(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB202e",
					  new TestOnestring_Equals(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB202f",
					  new TestOnestring_Equals(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB202g",
					  new TestOnestring_Equals(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB202h",
					  new TestOnestring_Equals(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB202i",
					  new TestOnestring_Equals(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB203a",
					  new TestOnestring_OpEquals(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB203b",
					  new TestOnestring_OpEquals(
						  TestOnestring::TestStringType::OCHAR_ASCII));
		register_test("O-tB203c",
					  new TestOnestring_OpEquals(
						  TestOnestring::TestStringType::OCHAR_UNICODE));
		register_test("O-tB203d",
					  new TestOnestring_OpEquals(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB203e",
					  new TestOnestring_OpEquals(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB203f",
					  new TestOnestring_OpEquals(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB203g",
					  new TestOnestring_OpEquals(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB203h",
					  new TestOnestring_OpEquals(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB203i",
					  new TestOnestring_OpEquals(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB204a",
					  new TestOnestring_OpNotEquals(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB204b",
					  new TestOnestring_OpNotEquals(
						  TestOnestring::TestStringType::OCHAR_ASCII));
		register_test("O-tB204c",
					  new TestOnestring_OpNotEquals(
						  TestOnestring::TestStringType::OCHAR_UNICODE));
		register_test("O-tB204d",
					  new TestOnestring_OpNotEquals(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB204e",
					  new TestOnestring_OpNotEquals(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB204f",
					  new TestOnestring_OpNotEquals(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB204g",
					  new TestOnestring_OpNotEquals(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB204h",
					  new TestOnestring_OpNotEquals(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB204i",
					  new TestOnestring_OpNotEquals(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB205a",
					  new TestOnestring_Compare(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB205b",
					  new TestOnestring_Compare(
						  TestOnestring::TestStringType::OCHAR_ASCII));
		register_test("O-tB205c",
					  new TestOnestring_Compare(
						  TestOnestring::TestStringType::OCHAR_UNICODE));
		register_test("O-tB205d",
					  new TestOnestring_Compare(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB205e",
					  new TestOnestring_Compare(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB205f",
					  new TestOnestring_Compare(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB205g",
					  new TestOnestring_Compare(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB205h",
					  new TestOnestring_Compare(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB205i",
					  new TestOnestring_Compare(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB206a",
					  new TestOnestring_OpLess(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB206b",
					  new TestOnestring_OpLess(
						  TestOnestring::TestStringType::OCHAR_ASCII));
		register_test("O-tB206c",
					  new TestOnestring_OpLess(
						  TestOnestring::TestStringType::OCHAR_UNICODE));
		register_test("O-tB206d",
					  new TestOnestring_OpLess(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB206e",
					  new TestOnestring_OpLess(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB206f",
					  new TestOnestring_OpLess(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB206g",
					  new TestOnestring_OpLess(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB206h",
					  new TestOnestring_OpLess(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB206i",
					  new TestOnestring_OpLess(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB207a",
					  new TestOnestring_OpLessEqual(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB207b",
					  new TestOnestring_OpLessEqual(
						  TestOnestring::TestStringType::OCHAR_ASCII));
		register_test("O-tB207c",
					  new TestOnestring_OpLessEqual(
						  TestOnestring::TestStringType::OCHAR_UNICODE));
		register_test("O-tB207d",
					  new TestOnestring_OpLessEqual(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB207e",
					  new TestOnestring_OpLessEqual(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB207f",
					  new TestOnestring_OpLessEqual(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB207g",
					  new TestOnestring_OpLessEqual(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB207h",
					  new TestOnestring_OpLessEqual(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB207i",
					  new TestOnestring_OpLessEqual(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB208a",
					  new TestOnestring_OpGreater(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB208b",
					  new TestOnestring_OpGreater(
						  TestOnestring::TestStringType::OCHAR_ASCII));
		register_test("O-tB208c",
					  new TestOnestring_OpGreater(
						  TestOnestring::TestStringType::OCHAR_UNICODE));
		register_test("O-tB208d",
					  new TestOnestring_OpGreater(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB208e",
					  new TestOnestring_OpGreater(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB208f",
					  new TestOnestring_OpGreater(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB208g",
					  new TestOnestring_OpGreater(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB208h",
					  new TestOnestring_OpGreater(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB208i",
					  new TestOnestring_OpGreater(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB209a",
					  new TestOnestring_OpGreaterEqual(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB209b",
					  new TestOnestring_OpGreaterEqual(
						  TestOnestring::TestStringType::OCHAR_ASCII));
		register_test("O-tB209c",
					  new TestOnestring_OpGreaterEqual(
						  TestOnestring::TestStringType::OCHAR_UNICODE));
		register_test("O-tB209d",
					  new TestOnestring_OpGreaterEqual(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB209e",
					  new TestOnestring_OpGreaterEqual(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB209f",
					  new TestOnestring_OpGreaterEqual(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB209g",
					  new TestOnestring_OpGreaterEqual(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB209h",
					  new TestOnestring_OpGreaterEqual(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB209i",
					  new TestOnestring_OpGreaterEqual(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB210", new TestOnestring_At());
		register_test("O-tB211", new TestOnestring_OpAt());
		register_test("O-tB212", new TestOnestring_Back());
		register_test("O-tB213", new TestOnestring_Front());
		register_test("O-tB214", new TestOnestring_Capacity());
		register_test("O-tB215", new TestOnestring_PopBack());
		register_test("O-tB216", new TestOnestring_Length());
		register_test("O-tB217", new TestOnestring_Size());
		register_test("O-tB218", new TestOnestring_Copy());
		register_test("O-tB219", new TestOnestring_CStr());
		register_test("O-tB220", new TestOnestring_Empty());
		register_test("O-tB221", new TestOnestring_Substr());

		register_test("O-tB222a",
					  new TestOnestring_Append(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB222b",
					  new TestOnestring_Append(
						  TestOnestring::TestStringType::OCHAR_ASCII));
		register_test("O-tB222c",
					  new TestOnestring_Append(
						  TestOnestring::TestStringType::OCHAR_UNICODE));
		register_test("O-tB222d",
					  new TestOnestring_Append(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB222e",
					  new TestOnestring_Append(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB222f",
					  new TestOnestring_Append(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB222g",
					  new TestOnestring_Append(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB222h",
					  new TestOnestring_Append(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB222i",
					  new TestOnestring_Append(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB223a",
					  new TestOnestring_OpAppend(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB223b",
					  new TestOnestring_OpAppend(
						  TestOnestring::TestStringType::OCHAR_ASCII));
		register_test("O-tB223c",
					  new TestOnestring_OpAppend(
						  TestOnestring::TestStringType::OCHAR_UNICODE));
		register_test("O-tB223d",
					  new TestOnestring_OpAppend(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB223e",
					  new TestOnestring_OpAppend(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB223f",
					  new TestOnestring_OpAppend(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB223g",
					  new TestOnestring_OpAppend(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB223h",
					  new TestOnestring_OpAppend(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB223i",
					  new TestOnestring_OpAppend(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB224", new TestOnestring_Clear());
		register_test("O-tB225", new TestOnestring_Erase());

		register_test("O-tB226a",
					  new TestOnestring_Insert(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB226b",
					  new TestOnestring_Insert(
						  TestOnestring::TestStringType::OCHAR_ASCII));
		register_test("O-tB226c",
					  new TestOnestring_Insert(
						  TestOnestring::TestStringType::OCHAR_UNICODE));
		register_test("O-tB226d",
					  new TestOnestring_Insert(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB226e",
					  new TestOnestring_Insert(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB226f",
					  new TestOnestring_Insert(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB226g",
					  new TestOnestring_Insert(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB226h",
					  new TestOnestring_Insert(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB226i",
					  new TestOnestring_Insert(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB227a",
					  new TestOnestring_Replace(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB227b",
					  new TestOnestring_Replace(
						  TestOnestring::TestStringType::OCHAR_ASCII));
		register_test("O-tB227c",
					  new TestOnestring_Replace(
						  TestOnestring::TestStringType::OCHAR_UNICODE));
		register_test("O-tB227d",
					  new TestOnestring_Replace(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB227e",
					  new TestOnestring_Replace(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB227f",
					  new TestOnestring_Replace(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB227g",
					  new TestOnestring_Replace(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB227h",
					  new TestOnestring_Replace(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB227i",
					  new TestOnestring_Replace(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB228", new TestOnestring_Reverse());
		register_test("O-tB229", new TestOnestring_Swap());

		register_test("O-tB230", new TestOnestring_Expand());
		register_test("O-tB231", new TestOnestring_Reserve());
		register_test("O-tB232", new TestOnestring_Resize());
		register_test("O-tB233", new TestOnestring_ShrinkToFit());
		register_test("O-tB234", new TestOnestring_ForceResize());
		register_test("O-tS234", new TestOnestring_ForceResizeStress(), false);

		register_test("O-tB240a",
					  new TestOnestring_OpPlus(
						  TestOnestring::TestStringType::CHAR));
		register_test("O-tB240b",
					  new TestOnestring_OpPlus(
						  TestOnestring::TestStringType::CSTR_ASCII));
		register_test("O-tB240c",
					  new TestOnestring_OpPlus(
						  TestOnestring::TestStringType::CSTR_UNICODE));
		register_test("O-tB240d",
					  new TestOnestring_OpPlus(
						  TestOnestring::TestStringType::STR_ASCII));
		register_test("O-tB240e",
					  new TestOnestring_OpPlus(
						  TestOnestring::TestStringType::STR_UNICODE));
		register_test("O-tB240f",
					  new TestOnestring_OpPlus(
						  TestOnestring::TestStringType::OSTR_ASCII));
		register_test("O-tB240g",
					  new TestOnestring_OpPlus(
						  TestOnestring::TestStringType::OSTR_UNICODE));

		register_test("O-tB241", new TestOnestring_Cast());

		// tB4035: find
		// tB4036: find_first_not_of
		// tB4037: find_first_of
		// tB4038: find_last_not_of
		// tB4039: rfind

		// TODO: Comparative tests against std::string
	}
};

#endif  // ONESTRING_TESTS_HPP
