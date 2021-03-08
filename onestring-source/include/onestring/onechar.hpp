/** Onechar
 * Version: 1.0
 *
 * Onechar is an enhanced UTF-8 character class which is fully compatible with
 * the atomic char type, c-strings, and std::string.
 *
 * Author(s): Jason C. McDonald, Scott Taylor, Jarek Thomas, Bowen Volwiler
 */

/* LICENSE (BSD-3-Clause)
 * Copyright (c) 2016-2021 MousePaw Media.
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

#ifndef ONESTRING_ONECHAR_HPP
#define ONESTRING_ONECHAR_HPP

#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

class onestring;

/** Stores a single unicode character */
class onechar
{
	friend onestring;

private:
	/* We never store more than 4 bytes of meaningful data.
	 * The null terminator is stored as an implementation detail, but
	 * is ignored by virtually all Onechar functions. */
	static const size_t MAX_SIZE = 4;

	/// The number of bytes stored.
	size_t size;

	/// The character array as a c-string.
	char internal[MAX_SIZE + 1];

	/** Store an ASCII character in this onechar
	 * \param the char to copy */
	void parse(const char ch)
	{
		// char is always ASCII (one byte)
		this->size = 1;
		// Store the character
		this->internal[0] = ch;
	}

	/** Extract and store a Unicode character from a c-string.
	 * If more than one character is present in the c-string, only the
	 * first will be parsed out; the rest will be ignored.
	 * \param the c-string to extract the character from */
	void parse(const char* cstr)
	{
		/* Determine the bytesize of the Unicode character
		 * at the start of the c-string */
		this->size = evaluateLength(cstr);
		// Store the character via direct copy to internal array
		memcpy(this->internal, cstr, sizeof(char) * this->size);
	}

	/** Extract and store a Unicode character from a std::string.
	 * If more than one character is present in the std::string, only
	 * the first will be parsed out; the rest will be ignored.
	 * \param the std::string to extract the character from */
	void parse(const std::string& str)
	{
		// Extract the c-string from the std::string and parse it
		parse(str.c_str());
	}

	/** Extract and store a Unicode character from a c-string at the
	 * given index. Returns the number of characters in the extracted
	 * Unicode character, to aid in external parsing algorithms.
	 * \param the c-string to extract the character from
	 * \param the index of the start of the Unicode character
	 * \return the number of elements (chars) parsed out */
	size_t parseFromString(const char* cstr, size_t index)
	{
		/* Determine the bytesize of the Unicode character
		 * at the target location in the c-string */
		this->size = evaluateLength(cstr + index);
		// Store the character via direct copy to internal array
		memcpy(this->internal, cstr + index, sizeof(char) * this->size);
		// Return the number of characters we parsed in the c-string
		return this->size;
	}

	/** Extract and store a Unicode character from a std::string at the
	 * given index. Returns the number of characters in the extracted
	 * Unicode character, to aid in external parsing algorithms.
	 * \param the std::string to extract the character from
	 * \param the index of the start of the Unicode character
	 * \return the number of elements (chars) parsed out */
	size_t parseFromString(const std::string& str, size_t index)
	{
		// Extract the c-string from the std::string and parse it
		return parseFromString(str.c_str(), index);
	}

public:
	/** Initialize a onechar as a null terminator */
	onechar() : size(1), internal{'\0', '\0', '\0', '\0', '\0'}
	{
		// The default value of a onechar should be a null terminator
	}

	/** Initialize a onechar with an ASCII character */
	// cppcheck-suppress noExplicitConstructor
	onechar(const char ch) : size(1), internal{'\0', '\0', '\0', '\0', '\0'}
	{
		// Store the ASCII character
		parse(ch);
	}

	/** Initialize a onechar with an ASCII or Unicode character
	 * in a c-string. */
	// cppcheck-suppress noExplicitConstructor
	onechar(const char* cstr) : size(1), internal{'\0', '\0', '\0', '\0', '\0'}
	{
		// Extract the first ASCII or Unicode character from the c-string
		parse(cstr);
	}

	/** Initialize a onechar with an ASCII or Unicode character
	 * in a std::string. */
	// cppcheck-suppress noExplicitConstructor
	onechar(const std::string& str)
	: size(1), internal{'\0', '\0', '\0', '\0', '\0'}
	{
		// Extract the first ASCII or Unicode character from the std::string
		parse(str);
	}

	/** Initialize a onechar as a copy of another. */
	onechar(const onechar& cpy)
	: size(cpy.size), internal{'\0', '\0', '\0', '\0', '\0'}
	{
		// Directly copy the contents of the internal array
		memcpy(this->internal, cpy.internal, cpy.size);
	}

	/** Initialize a onechar by moving another. */
	onechar(onechar&& mov) : size(mov.size)
	{
		// Directly copy the contents of the internal array
		// TODO: Is there a way just to steal the pointer?
		memcpy(this->internal, mov.internal, mov.size);
	}

	/** Destructor */
	~onechar() = default;

	/** Test for equality against a character
	 * \param the char to test against
	 * \return true if equal, else false*/
	bool equals(const char cmp) const
	{
		return ((this->size == 1) && (this->internal[0] == cmp));
	}

	/** Test for equality against a c-string.
	 * Does NOT ignore extraneous characters in the c-string
	 * \param the c-string to test against
	 * \return true if equal, else false */
	bool equals(const char* cmp) const
	{
		size_t cmpSize = evaluateLength(cmp);
		// If the string doesn't null-terminate after one character, mismatch.
		if (cmp[cmpSize] != '\0') {
			return false;
		}
		// Ensure the character size matches
		if (cmpSize != this->size) {
			return false;
		}
		return (memcmp(this->internal, cmp, cmpSize) == 0);
	}

	/** Test for equality against the first character in a c-string.
	 * Unlike equals(), DOES ignore extraneous characters
	 * \param the c-string to test against
	 * \return true in equal, else false */
	bool equals_at(const char* cmp) const
	{
		size_t cmpSize = evaluateLength(cmp);
		// Ensure the character size matches
		if (cmpSize != this->size) {
			return false;
		}
		return (memcmp(this->internal, cmp, cmpSize) == 0);
	}

	/** Test for equality against a std::string
	 * Does NOT ignore extraneous characters in the std::string
	 * \param the std::string to test against
	 * \return true if equal, else false */
	bool equals(const std::string& cmp) const
	{
		// Extract the c-string from the std::string and compare it directly
		return equals(cmp.c_str());
	}

	/** Test for equality against another onechar
	 * \param the onechar to test against
	 * \return true if equal, else false */
	bool equals(const onechar& cmp) const
	{
		// Ensure the character bytelengths are the same
		if (this->size != cmp.size) {
			return false;
		}
		// Perform a raw memory comparison
		return (memcmp(this->internal, cmp.internal, this->size) == 0);
	}

	/** Returns the c-string representation of the onechar.
	 * Appends a null terminator.
	 * \return c-string of the character */
	const char* c_str() const { return this->internal; }

	/** Compare against a character.
	 * \param the char to test against
	 * \return 0 if equal to argument, negative if less, positive if greater */
	int compare(const char cmp) const
	{
		/* This algorithm will not return a meaningful integer; only its
		 * relation to 0 will be useful */

		int sizeDiff = this->size - 1;
		// If the bytesize was the same...
		if (sizeDiff == 0) {
			// ...return the results of a direct memory comparison
			return memcmp(this->internal, &cmp, 1);
		}
		// Otherwise, return the difference in bytesize.
		return sizeDiff;
	}

	/** Compare against a c-string.
	 * Does NOT ignore extraneous characters in the c-string
	 * \param the c-string to test against
	 * \return 0 if equal to argument, negative if less, positive if greater */
	int compare(const char* cmp) const
	{
		/* This algorithm will not return a meaningful integer; only its
		 * relation to 0 will be useful */

		int sizeDiff = this->size - evaluateLength(cmp);
		// If the bytesize was the same...
		if (sizeDiff == 0) {
			// ...return the results of a direct memory comparison
			return memcmp(this->internal, cmp, this->size);
		}
		// Otherwise, return the difference in bytesize.
		return sizeDiff;
	}

	/** Compare against a std::string.
	 * Does NOT ignore extraneous characters in the std::string
	 * \param the std::string to test against
	 * \return 0 if equal to argument, negative if less, positive if greater */
	int compare(const std::string& cmp) const
	{
		// Extract the c-string from the std::string and directly compare it.
		return compare(cmp.c_str());
	}

	/** Compare against another onechar
	 * \param the onechar to test against
	 * \return 0 if equal to argument, negative if less, positive if greater */
	int compare(const onechar& cmp) const
	{
		/* This algorithm will not return a meaningful integer; only its
		 * relation to 0 will be useful */

		int sizeDiff = this->size - cmp.size;
		// If the bytesize was the same...
		if (sizeDiff == 0) {
			// ...return the results of a direct memory comparison
			return memcmp(this->internal, cmp.internal, this->size);
		}
		// Otherwise, return the difference in bytesize.
		return sizeDiff;
	}

	/** Evaluate the number of bytes in a Unicode character.
	 * Ignores all subsequent characters.
	 * \param the pointer to the Unicode character (c-string)
	 * \return the number of bytes in the Unicode character */
	static size_t evaluateLength(const char* cstr)
	{
		switch (cstr[0] & 0xF0) {
			case 0xF0: {
				// Unicode code points U+10000 to U+10FFFF
				return 4;
			}
			case 0xE0: {
				// Unicode code points U+0800 to U+FFFF
				return 3;
			}
			case 0xD0:
			case 0xC0: {
				// Unicode code points U+0080 to U+07FF
				return 2;
			}
			default: {
				// Unicode code points U+0000 to U+007F
				return 1;
			}
		}
		// Can't happen
		return 0;
	}

	// Assignment Operators

	onechar& operator=(char ch)
	{
		parse(ch);
		return *this;
	}

	onechar& operator=(const char* cstr)
	{
		parse(cstr);
		return *this;
	}

	onechar& operator=(const std::string& str)
	{
		parse(str);
		return *this;
	}

	onechar& operator=(const onechar& cpy)
	{
		if (this != &cpy) {
			this->size = cpy.size;
			memcpy(this->internal, cpy.internal, cpy.size);
		}
		return *this;
	}

	onechar& operator=(onechar&& mov)
	{
		if (this != &mov) {
			this->size = mov.size;
			memcpy(this->internal, mov.internal, mov.size);
		}
		return *this;
	}

	// Comparison Operators

	bool operator==(const char cmp) const { return equals(cmp); }
	bool operator==(const char* cmp) const { return equals(cmp); }
	bool operator==(const std::string& cmp) const { return equals(cmp); }
	bool operator==(const onechar& cmp) const { return equals(cmp); }

	bool operator!=(const char cmp) const { return !equals(cmp); }
	bool operator!=(const char* cmp) const { return !equals(cmp); }
	bool operator!=(const std::string& cmp) const { return !equals(cmp); }
	bool operator!=(const onechar& cmp) const { return !equals(cmp); }

	bool operator<(const char cmp) const { return (compare(cmp) < 0); }
	bool operator<(const char* cmp) const { return (compare(cmp) < 0); }
	bool operator<(const std::string& cmp) const { return (compare(cmp) < 0); }
	bool operator<(const onechar& cmp) const { return (compare(cmp) < 0); }

	bool operator<=(const char cmp) const { return (compare(cmp) <= 0); }
	bool operator<=(const char* cmp) const { return (compare(cmp) <= 0); }
	bool operator<=(const std::string& cmp) const
	{
		return (compare(cmp) <= 0);
	}
	bool operator<=(const onechar& cmp) const { return (compare(cmp) <= 0); }

	bool operator>(const char cmp) const { return (compare(cmp) > 0); }
	bool operator>(const char* cmp) const { return (compare(cmp) > 0); }
	bool operator>(const std::string& cmp) const { return (compare(cmp) > 0); }
	bool operator>(const onechar& cmp) const { return (compare(cmp) > 0); }

	bool operator>=(const char cmp) const { return (compare(cmp) >= 0); }
	bool operator>=(const char* cmp) const { return (compare(cmp) >= 0); }
	bool operator>=(const std::string& cmp) const
	{
		return (compare(cmp) >= 0);
	}
	bool operator>=(const onechar& cmp) const { return (compare(cmp) >= 0); }

	friend bool operator==(const char lhs, const onechar& rhs)
	{
		return rhs.equals(lhs);
	}
	friend bool operator==(const char* lhs, const onechar& rhs)
	{
		return rhs.equals(lhs);
	}
	friend bool operator==(const std::string& lhs, const onechar& rhs)
	{
		return rhs.equals(lhs);
	}

	friend bool operator!=(const char lhs, const onechar& rhs)
	{
		return !rhs.equals(lhs);
	}
	friend bool operator!=(const char* lhs, const onechar& rhs)
	{
		return !rhs.equals(lhs);
	}
	friend bool operator!=(const std::string& lhs, const onechar& rhs)
	{
		return !rhs.equals(lhs);
	}

	// Notice that we have to invert the comparison in the function body.
	friend bool operator<(const char lhs, const onechar& rhs)
	{
		return (rhs.compare(lhs) > 0);
	}
	friend bool operator<(const char* lhs, const onechar& rhs)
	{
		return (rhs.compare(lhs) > 0);
	}
	friend bool operator<(const std::string& lhs, const onechar& rhs)
	{
		return (rhs.compare(lhs) > 0);
	}

	friend bool operator<=(const char lhs, const onechar& rhs)
	{
		return (rhs.compare(lhs) >= 0);
	}
	friend bool operator<=(const char* lhs, const onechar& rhs)
	{
		return (rhs.compare(lhs) >= 0);
	}
	friend bool operator<=(const std::string& lhs, const onechar& rhs)
	{
		return (rhs.compare(lhs) >= 0);
	}

	friend bool operator>(const char lhs, const onechar& rhs)
	{
		return (rhs.compare(lhs) < 0);
	}
	friend bool operator>(const char* lhs, const onechar& rhs)
	{
		return (rhs.compare(lhs) < 0);
	}
	friend bool operator>(const std::string& lhs, const onechar& rhs)
	{
		return (rhs.compare(lhs) < 0);
	}

	friend bool operator>=(const char lhs, const onechar& rhs)
	{
		return (rhs.compare(lhs) <= 0);
	}
	friend bool operator>=(const char* lhs, const onechar& rhs)
	{
		return (rhs.compare(lhs) <= 0);
	}
	friend bool operator>=(const std::string& lhs, const onechar& rhs)
	{
		return (rhs.compare(lhs) <= 0);
	}

	// HACK: Here only to ensure compiling. Remove the need for this from
	// onestring
	char operator[](int pos) const { return this->internal[pos]; }

	// TODO: Revisit/rewrite these

	/** Helper function for operator<<
	 * \param std::ostream to put output on */
	void print(std::ostream& os) const { os << this->c_str(); }

	/** Output operator
	 * \param std::ostream to display output on
	 * \param the onechar that is the output
	 * \return the std::ostream to output */
	friend std::ostream& operator<<(std::ostream& os, const onechar& ostr)
	{
		os << ostr.c_str();
		return os;
	}
};

#endif  // ONESTRING_ONECHAR_HPP
