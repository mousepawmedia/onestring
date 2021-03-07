/** Onestring
 * Version: 1.0
 *
 * Onestring is a multi-sized, Unicode-compatible (UTF-8) replacement for
 * std::basic_string. Onestring contains all the functionality found in
 * std::basic_string, and then some! It is fully compatible with c-strings,
 * std::basic_string, and the primitive char data type. To handle Unicode,
 * each Onestring is composed of Onechars, an enhanced UTF-8 character class.
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

#ifndef ONESTRING_ONESTRING_HPP
#define ONESTRING_ONESTRING_HPP

#include <algorithm>
#include <cctype>  // isspace()
#include <cstring>
#include <iomanip>
#include <iostream>
#include <istream>

#include "onestring/onechar.hpp"

class onestring
{
public:
	/// The default size the onestring is initialized at
	inline static const size_t BASE_SIZE = 4;

	/// The greatest possible value for an element.
	inline static const size_t npos = -1;

	/// The factor the capacity is multiplied by to resize
	inline static const float RESIZE_FACTOR = 1.5;

private:
	inline static const float RESIZE_LIMIT = npos / RESIZE_FACTOR;

	/// The maximum number of elements that can be stored without resize
	size_t _capacity;

	/// The number of elements currently stored
	size_t _elements;

	/// The array of onechars
	onechar* internal;

	/// The cached c-string. We store this pointer to ensure it is cleaned up
	/// properly.
	mutable char* _c_str;

public:
	/*******************************************
	 * Constructors + Destructor
	 *******************************************/

	/**Default Constructor*/
	onestring()
	: _capacity(BASE_SIZE), _elements(0), internal(nullptr), _c_str(0)
	{
		allocate(this->_capacity);
		// assign('\0');
	}

	/**Create a onestring from c-string (string literal)
	 * \param the c-string to be converted to onestring */
	// cppcheck-suppress noExplicitConstructor
	onestring(const char* cstr)
	: _capacity(BASE_SIZE), _elements(0), internal(nullptr), _c_str(0)
	{
		allocate(this->_capacity);
		assign(cstr);
	}

	/**Create a onestring from std::basic_string
	 * \param the string to be converted to onestring */
	// cppcheck-suppress noExplicitConstructor
	template<typename T> onestring(const std::basic_string<T>& str)
	: _capacity(BASE_SIZE), _elements(0), internal(nullptr), _c_str(0)
	{
		allocate(this->_capacity);
		append(str);
	}

	/**Create a onestring from another onestring
	 * \param the onestring to be copied */
	onestring(const onestring& ostr)
	: _capacity(BASE_SIZE), _elements(0), internal(nullptr), _c_str(0)
	{
		allocate(this->_capacity);
		assign(ostr);
	}

	/**Create a onestring from a char
	 *  \param the char to be added */
	// cppcheck-suppress noExplicitConstructor
	onestring(char ch)
	: _capacity(BASE_SIZE), _elements(0), internal(nullptr), _c_str(0)
	{
		allocate(this->_capacity);
		assign(ch);
	}

	/**Create a onestring from a onechar
	 *  \param the onechar to be added */
	// cppcheck-suppress noExplicitConstructor
	onestring(const onechar& ochr)
	: _capacity(BASE_SIZE), _elements(0), internal(nullptr), _c_str(0)
	{
		allocate(this->_capacity);
		assign(ochr);
	}

	/**Destructor*/
	~onestring()
	{
		if (_c_str != nullptr) {
			delete[] _c_str;
		}

		if (internal != nullptr) {
			delete[] internal;
		}
	}

private:
	/*******************************************
	 * Memory Management
	 ********************************************/

	/** Allocates the requested space exactly.
	 * This is the primary function responsible for allocation.
	 * \param the number of elements to allocate space for */
	void allocate(size_t capacity)
	{
		this->_capacity = capacity;

		// If we're allocating down, throw away the excess elements.
		if (this->_elements > this->_capacity) {
			this->_elements = this->_capacity;
		}

		// Allocate a new array with the new size.
		onechar* newArr = new onechar[this->_capacity];

		// If an old array exists...
		if (this->internal != nullptr) {
			for (size_t i = 0; i < this->_elements; ++i) {
				newArr[i] = std::move(this->internal[i]);
			}

			// Delete the old structure
			delete[] internal;
			this->internal = nullptr;
		}

		// Store the new structure.
		this->internal = newArr;
	}

	/** Shifts the contents of the onestring efficiently.
	 * WARNING: Does not check for validity of shift, nor perform
	 * expansions or shrinks. That is the responsibility of the caller.
	 * \param the first index to shift
	 * \param how much to shift by, and in what direction.
	 * Negative values shift back, positive shift forward. */
	void shift(size_t fromIndex, int offset)
	{
		// WARNING: We do NOT handle expansion in this function; only shifting.

		// If we're shifting forward...
		if (offset > 0) {
			// Work from last element being moved to first
			size_t target = _elements;
			// Copy each element forward to its new position.
			while (target-- > fromIndex) {
				this->internal[target + offset] = this->internal[target];
			}
		}
		// Otherwise, if we're shifting backward...
		else if (offset < 0) {
			// Work from first element being moved to last
			size_t target = fromIndex;
			// Copy each element back to its new position.
			while (target < _elements) {
				this->internal[target + offset] = this->internal[target];
				++target;
			}
		}
	}

	/** Invalidate the cached c_str and recreate it.
	  * Normally called after any mutating operation.
	  */
	void invalidate_c_str() {
		// If we have a c-string instance cached, deallocate it.
		if (this->_c_str != nullptr) {
			this->_c_str = nullptr;
			delete[] this->_c_str;
		}
	}

public:
	/** Requests that the string capacity be expanded to accommodate
	 * the given number of additional characters.
	 * `s.expand(n)` is equivalent to `s.reserve(s.length() + n)`
	 * \param the number of additional elements to reserve space for */
	void expand(size_t expansion) { reserve(this->_elements + expansion); }

	/** Requests that the string capacity be expanded to accommodate
	 * the given number of characters.
	 * \param the number of elements to reserve space for */
	void reserve(size_t elements)
	{
		// If we're already large enough, don't reallocate.
		if (this->_capacity >= elements) {
			return;
		}

		// A capacity of 0 will trigger a complete reallocation
		if (this->_capacity == 0) {
			this->_capacity = BASE_SIZE;
		}

		// If we're about to blow past indexing, manually set the capacity.
		if (elements >= RESIZE_LIMIT) {
			this->_capacity = npos;
		}

		// Expand until we have enough space.
		while (this->_capacity < elements) {
			this->_capacity *= RESIZE_FACTOR;
		}

		allocate(this->_capacity);
	}

	void resize(size_t elements)
	{
		// Don't reallocate if we already have the exact size needed.
		if (this->_capacity == elements) {
			return;
		}

		// Reallocate to EXACTLY the needed size.
		allocate(elements);
	}

	void resize(size_t elements, const onechar& ch)
	{
		int to_add = elements - this->_elements;
		std::cout << to_add << std::endl;
		resize(elements);

		if (to_add > 0) {
			append(ch, to_add);
		}
	}

	void shrink_to_fit()
	{
		// We simply need to reallocate for the EXACT number of elements we have
		allocate(this->_elements);
	}

	/** Evaluate the number of Unicode characters in a c-string
	 * \param the c-string to evaluate
	 * \return the character count */
	static size_t characterCount(const char* cstr)
	{
		size_t index = 0;
		size_t count = 0;
		while (cstr[index] != '\0') {
			index += onechar::evaluateLength(cstr + index);
			++count;
		}
		return count;
	}

	/*******************************************
	 * Accessors
	 *******************************************/

	/** Gets the onechar at a given position
	 * \param the index of the onechar to return
	 * \return a reference to the corresponding onechar */
	onechar& at(size_t pos)
	{
		if (pos > _elements) {
			throw std::out_of_range("Onestring::at(): Index out of bounds.");
		}

		return internal[pos];
	}

	const onechar& at(size_t pos) const
	{
		if (pos > _elements) {
			throw std::out_of_range("Onestring::at(): Index out of bounds.");
		}

		return internal[pos];
	}

	/** Gets the last onechar in the string.
	 * If the string is empty, this has undefined behavior
	 * (although it is guaranteed memory safe.)
	 * \return a reference to the last onechar in the string.
	 */
	onechar& back()
	{
		// WARNING: If string is empty, this is undefined (but memory safe)
		// Return a reference to the last element in the string.
		return this->internal[_elements - 1];
	}

	const onechar& back() const
	{
		// WARNING: If string is empty, this is undefined (but memory safe)
		// Return a reference to the last element in the string.
		return this->internal[_elements - 1];
	}

	/** Gets the current capacity of the onestring.
	 * Used primarily internally for resizing purposes.
	 * \return the size of the onestring */
	size_t capacity() const { return _capacity; }

	/** Copies a substring from the onestring to the given c-string.
	 * Guaranteed to copy the entirety of any Unicode character,
	 * or else skip it (no partial character copies).
	 * \param pointer to an array of characters (c-string)
	 * \param the maximum number of char elements in the c-string
	 * \param the number of Unicode characters to copy. Defaults to 0,
	 * which will copy the maximum number of characters that will fit
	 * into the c-string.
	 * \param the position of the first character to be copied (optional)
	 * If this is greater than the string length, it throws out_of_range
	 * \return the number of char elements copied to the array */
	size_t copy(char* arr, size_t max, size_t len = 0, size_t pos = 0) const
	{
		// Reminder: len and pos default to 0

		if (pos >= this->_elements) {
			throw std::out_of_range(
				"Onestring::copy(): specified pos out of range");
		}

		// Remove one char from the max to account for the null terminator.
		--max;

		// The indices for the c-string and (this) onestring.
		size_t cstr_i = 0;
		size_t ostr_i = pos;

		// Account for unspecified len, or adjust so it doesn't blow past the
		// end.
		if (len == 0 || len + pos > this->_elements) {
			len = this->_elements - pos;
		}

		while (cstr_i < max && ostr_i < (pos + len)) {
			memcpy(arr + cstr_i,
				   this->internal[ostr_i].internal,
				   this->internal[ostr_i].size);
			cstr_i += this->internal[ostr_i].size;
			++ostr_i;
		}

		arr[cstr_i] = '\0';

		return cstr_i;
	}

	/** Returns a c-string equivalent of a onestring.
	  * Pointer may become invalidated by calls to other member functions.
	  * \return the c-string */
	const char* c_str() const
	{
		// If we have a c-string instance cached, just return that.
		if (this->_c_str != nullptr) {
			return this->_c_str;
		}

		// Otherwise, allocate a new c-string.
		size_t n = size();
		this->_c_str = new char[n];

		// Convert and store each onechar's value in the c-string
		char* dest = this->_c_str;
		for (size_t i = 0; i < _elements; ++i) {
			memcpy(dest, internal[i].internal, internal[i].size);
			dest += internal[i].size;
		}

		// Append the null terminator to the end of the c-string
		this->_c_str[n - 1] = '\0';

		// Return the pointer to the new cached c-string
		return this->_c_str;
	}

	/** Returns a std::basic_string equivalent of a onestring
	 * \return the std::basic_string
	 */
	template<typename T>
	operator std::basic_string<T>() const {
		auto r = std::basic_string<T>(this->c_str());
		return r;
	}

	/** Returns a c-string equivalent of a onestring
	 * Alias for onestring::c_str()
	 * \return the c-string */
	const char* data() const { return c_str(); }

	/**Checks to see if a onestring contains any data
	 * \returns true if empty, else false */
	bool empty() const { return (_elements == 0); }

	/** Gets the first onechar in the string.
	 * If the string is empty, this has undefined behavior
	 * (although it is guaranteed memory safe.)
	 * \return a reference to the first onechar in the string.
	 */
	onechar& front()
	{
		// WARNING: If string is empty, this is undefined (but memory safe)
		// Return a reference to the first element in the string.
		return this->internal[0];
	}

	const onechar& front() const
	{
		// WARNING: If string is empty, this is undefined (but memory safe)
		// Return a reference to the last element in the string.
		return this->internal[0];
	}

	/**Gets the current number of elements in the onestring
	 * \return the number of elements */
	size_t length() const { return _elements; }

	/** Returns the largest possible index allowed in onestring.
	 * This is theoretical only, based on implementation. Allocation
	 * may fail well before this. */
	static size_t max_size() { return npos; }

	/**Creates a smaller string out of
	 * a series of onechars in the existing onestring
	 * \param the position to begin the string to be created
	 * \param the length of the string to be created, optional.
	 * \return the created string */
	onestring substr(size_t pos = 0, size_t len = npos) const
	{
		if (pos >= this->_elements) {
			throw std::out_of_range(
				"Onestring::substr(): specified pos out of range");
		}

		onestring r;

		// Calculate size of substr (number of elements)
		size_t elements_to_copy =
			(len > _elements - pos) ? (_elements - pos) : len;
		// Reserve necessary space in the new onestring
		r.reserve(elements_to_copy);
		// Copy the characters for the substring
		for (size_t i = 0; i < elements_to_copy; ++i) {
			r.internal[i] = this->internal[pos + i];
		}
		// Record how many elements were copied.
		r._elements = elements_to_copy;
		return r;
	}

	/**Gets the byte size of the equivalent c-string.
	 * WARNING: Given a onestring 's', s.size() < sizeof(s)
	 * \return the number of bytes in the onestring */
	size_t size() const
	{
		// Start counting at 1 to account for the null terminator.
		size_t bytes = 1;
		// Sum all of the byte lengths of the onechars.
		for (size_t i = 0; i < _elements; ++i) {
			bytes += this->internal[i].size;
		}
		return bytes;
	}

	/** Gets the byte size of the equivalent c-string for the
	 * specified substring.
	 * \param the number of Unicode characters in the substring.
	 * \param the position of the first character in the substring.
	 * Defaults to 0.
	 * If this is greater than the string length, it throws out_of_range
	 */
	size_t size(size_t len, size_t pos = 0) const
	{
		// Ensure the starting position is in range.
		if (pos >= this->_elements) {
			throw std::out_of_range(
				"Onestring::size(): specified pos out of range");
		}

		// Start counting at 1 to account for the null terminator.
		size_t bytes = 1;

		// Sum all of the byte lengths of the onechars in the range
		for (size_t i = pos; i < (pos + len) && i < _elements; ++i) {
			bytes += this->internal[i].size;
		}
		return bytes;
	}

	/*******************************************
	 * Comparison
	 ********************************************/

	/** Compares the onestring against a single char.
	 * \return an integer representing the result.
	 * Returns a negative integer IF this onestring is shorter
	 * OR the same length and lower in value
	 * Returns zero if the values are the same
	 * Returns a positive integer IF this onestring is longer
	 * OR the same length and higher in value */
	int compare(const char ch) const
	{
		int sizeDiff = this->_elements - 1;
		if (sizeDiff == 0) {
			return this->internal[0].compare(ch);
		}
		return sizeDiff;
	}

	/** Compares the onestring against a single onechar.
	 * \return an integer representing the result.
	 * Returns a negative integer IF this onestring is shorter
	 * OR the same length and lower in value
	 * Returns zero if the values are the same
	 * Returns a positive integer IF this onestring is longer
	 * OR the same length and higher in value */
	int compare(const onechar& ochr) const
	{
		int sizeDiff = this->_elements - 1;
		if (sizeDiff == 0) {
			return this->internal[0].compare(ochr);
		}
		return sizeDiff;
	}

	/** Compares the onestring against a c-string.
	 * \return an integer representing the result.
	 * Returns a negative integer IF this onestring is shorter
	 * OR the same length and lower in value
	 * Returns zero if the values are the same
	 * Returns a positive integer IF this onestring is longer
	 * OR the same length and higher in value */
	int compare(const char* cstr) const
	{
		/* This algorithm will not return a meaningful integer; only its
		 * relation to 0 will be useful */

		int sizeDiff = this->_elements - characterCount(cstr);

		if (sizeDiff == 0) {
			size_t j = 0;
			// If the strings are the same length, compare each character...
			for (size_t i = 0; i < this->_elements; ++i) {
				// Return the compare result of the first character mismatch
				int r = this->internal[i].compare(cstr + j);
				if (r != 0) {
					return r;
				}

				j += onechar::evaluateLength(cstr + j);
			}
		}
		return sizeDiff;
	}

	/** Compares the onestring against a std::basic_string.
	 * \return an integer representing the result.
	 * Returns a negative integer IF this onestring is shorter
	 * OR the same length and lower in value
	 * Returns zero if the values are the same
	 * Returns a positive integer IF this onestring is longer
	 * OR the same length and higher in value */
	template<typename T>
	int compare(const std::basic_string<T>& str) const { return compare(str.c_str()); }

	/** Compares the onestring against a onestring.
	 * \return an integer representing the result.
	 * Returns a negative integer IF this onestring is shorter
	 * OR the same length and lower in value
	 * Returns zero if the values are the same
	 * Returns a positive integer IF this onestring is longer
	 * OR the same length and higher in value */
	int compare(const onestring& ostr) const
	{
		/* This algorithm will not return a meaningful integer; only its
		 * relation to 0 will be useful */

		int sizeDiff = this->_elements - ostr._elements;
		if (sizeDiff == 0) {
			// If the strings are the same length, compare each character...
			for (size_t i = 0; i < this->_elements; ++i) {
				// Return the compare result of the first character mismatch
				int r = this->internal[i].compare(ostr.internal[i]);
				if (r != 0) {
					return r;
				}
			}
		}
		return sizeDiff;
	}

	/** Tests if the onestring value is equivalent to a single char.
	 * \param the char to compare against
	 * \return true if equal, else false */
	bool equals(const char ch) const
	{
		return (this->_elements == 1 && this->internal[0] == ch);
	}

	/** Tests if the onestring value is equivalent to a single onechar.
	 * \param the onechar to compare against
	 * \return true if equal, else false */
	bool equals(const onechar& ochr) const
	{
		return (this->_elements == 1 && this->internal[0] == ochr);
	}

	/** Tests if the onestring value is equivalent to a c-string.
	 * \param the c-string to compare against
	 * \return true if equal, else false */
	bool equals(const char* cstr) const
	{
		size_t index = 0;
		size_t compare_to = 0;
		if (this->_elements != characterCount(cstr)) {
			return false;
		}
		while (cstr[index] != '\0') {
			if (!(this->internal[compare_to].equals_at(cstr + index))) {
				return false;
			}
			index += onechar::evaluateLength(cstr + index);
			if (compare_to++ > this->_elements) {
				return false;
			}
		}

		return true;
	}

	/** Tests if the onestring value is equivalent to a std::basic_string.
	 * \param the std::basic_string to compare against
	 * \return true if equal, else false */
	template<typename T>
	bool equals(const std::basic_string<T>& str) const { return equals(str.c_str()); }

	/** Tests if the onestring value is equivalent to another onestring.
	 * \param the onestring to compare against
	 * \return true if equal, else false */
	bool equals(const onestring& ostr) const
	{
		if (this->_elements != ostr._elements) {
			return false;
		}

		for (size_t index = 0; index < this->_elements; ++index) {
			if (this->internal[index] != ostr.internal[index]) {
				return false;
			}
		}
		return true;
	}

	/*******************************************
	 * Mutators
	 ********************************************/

	// TODO How many need rvalue versions?

	/** Appends a character to the end of the onestring.
	 * \param the char to append
	 * \param how many times to repeat the append, default 1
	 * \return a reference to the onestring */
	onestring& append(const char ch, size_t repeat = 1)
	{
		expand(repeat);

		for (size_t a = 0; a < repeat; ++a) {
			// Insert a 1-byte ASCII char
			internal[_elements++] = ch;
		}
		this->invalidate_c_str();
		return *this;
	}

	/** Appends a character to the end of the onestring.
	 * \param the onechar to append
	 * \param how many times to repeat the append, default 1
	 * \return a reference to the onestring */
	onestring& append(const onechar& ochr, size_t repeat = 1)
	{
		expand(repeat);

		for (size_t a = 0; a < repeat; ++a) {
			internal[_elements++] = ochr;
		}
		this->invalidate_c_str();
		return *this;
	}

	/** Appends characters to the end of the onestring.
	 * \param the c-string to append from
	 * \param how many times to repeat the append, default 1
	 * \return a reference to the onestring */
	onestring& append(const char* cstr, size_t repeat = 1)
	{
		size_t len = characterCount(cstr);
		expand(len * repeat);

		for (size_t a = 0; a < repeat; ++a) {
			size_t index = 0;
			// Loop through each character in the string literal
			while (cstr[index] != '\0') {
				index += internal[_elements++].parseFromString(cstr, index);
			}
		}
		this->invalidate_c_str();
		return *this;
	}

	/** Appends characters to the end of the onestring.
	 * \param the std::basic_string to append from
	 * \param how many times to repeat the append, default 1
	 * \return a reference to the onestring */
	template<typename T>
	onestring& append(const std::basic_string<T>& str, size_t repeat = 1)
	{
		// Parse the internal c string directly.
		append(str.c_str(), repeat);
		this->invalidate_c_str();
		return *this;
	}

	/** Appends characters to the end of the onestring.
	 * \param the onestring to append from
	 * \param how many times to repeat the append, default 1
	 * \return a reference to the onestring */
	onestring& append(const onestring& ostr, size_t repeat = 1)
	{
		expand(ostr._elements * repeat);

		for (size_t a = 0; a < repeat; ++a) {
			for (size_t i = 0; i < ostr._elements; ++i) {
				this->internal[_elements + i] = ostr.internal[i];
			}

			_elements += ostr._elements;
		}
		this->invalidate_c_str();
		return *this;
	}

	/** Assigns a character to the onestring.
	 * \param the char to copy
	 * \return a reference to the onestring */
	onestring& assign(const char ch)
	{
		clear();
		reserve(1);
		this->internal[_elements++] = ch;
		this->invalidate_c_str();
		return *this;
	}

	/** Assigns a character to the onestring.
	 * \param the onechar to copy
	 * \return a reference to the onestring */
	onestring& assign(const onechar& ochr)
	{
		clear();
		reserve(1);
		this->internal[_elements++] = ochr;
		this->invalidate_c_str();
		return *this;
	}

	/** Assigns characters to the onestring.
	 * \param the c-string to copy from
	 * \return a reference to the onestring */
	onestring& assign(const char* cstr)
	{
		clear();

		size_t len = characterCount(cstr);
		reserve(len);

		// Loop through each character in the string literal
		size_t index = 0;
		while (cstr[index] != '\0') {
			// Parse and store the character.
			index += internal[_elements++].parseFromString(cstr, index);
		}
		this->invalidate_c_str();
		return *this;
	}

	/** Assigns characters to the onestring.
	 * \param the std::basic_string to copy from
	 * \return a reference to the onestring */
	template<typename T>
	onestring& assign(const std::basic_string<T>& str)
	{
		assign(str.c_str());
		this->invalidate_c_str();
		return *this;
	}

	/** Assigns characters to the onestring.
	 * \param the onestring to copy from
	 * \return a reference to the onestring */
	onestring& assign(const onestring& ostr)
	{
		clear();
		reserve(ostr._elements);
		for (size_t i = 0; i < ostr._elements; ++i) {
			this->internal[i] = ostr.internal[i];
		}
		_elements = ostr._elements;
		this->invalidate_c_str();
		return *this;
	}

	/** Clears a onestring and reallocates it back to BASE_SIZE */
	void clear()
	{
		if (_elements > 0) {
			delete[] this->internal;
			internal = nullptr;
			_capacity = 0;
			reserve(BASE_SIZE);
			_elements = 0;
			this->invalidate_c_str();
		}
	}

	/** Erases part of a string, reducing its length.
	 * \param the first character to erase. Defaults to 0.
	 * If this is greater than the string length, it throws out_of_range
	 * \param the total number of characters to erase
	 * Defaults to all the characters from the given start position
	 * to the end of the string.
	 * \returns a reference to the onestring */
	onestring& erase(size_t pos = 0, size_t len = npos)
	{
		if (pos > _elements) {
			throw std::out_of_range("Onestring::erase(): Index out of bounds.");
		}

		// Calculate the number of elements we need to REMOVE
		len = (len > _elements - pos) ? (_elements - pos) : len;

		// If there are any elements remaining after the erasure...
		if (_elements - pos - len > 0) {
			// Move the remaining elements back
			shift(pos + len, -(len));
		}

		// Update the number of elements
		_elements = _elements - len;

		this->invalidate_c_str();
		return *this;
	}

	/** Extracts characters from the istream, parses them as Unicode,
	 * and stores them in the onestring until the delimiter is found.
	 * Any previous contents of the onestring will be replaced.
	 * \param the istream to extract from
	 * \param the onestring to store to
	 * \param the optional delimiter. The newline character is used if
	 * none is specified.
	 * \return the same istream passed to the function */
	static std::istream& getline(std::istream& is,
								 onestring& ostr,
								 char delim = '\n')
	{
		ostr.clear();

		char ch;
		while (is.get(ch) && ch != delim) {
			ostr.append(ch);
		}
		return is;
	}

	/** Inserts a character in the onestring at the given position.
	 * \param the index to insert at.
	 * If this is greater than the string length, it throws out_of_range
	 * \param the char to insert
	 * \return a reference to the onestring */
	onestring& insert(size_t pos, char ch)
	{
		// Ensure the insertion position is in range.
		if (pos >= this->_elements) {
			throw std::out_of_range(
				"Onestring::insert(): specified pos out of range");
		}

		// Reserve needed space
		expand(1);
		// Move the right partition to make room for the new element
		shift(pos, 1);

		// Insert the new element
		this->internal[pos] = ch;
		// Increase the element count
		++_elements;

		this->invalidate_c_str();
		return *this;
	}

	/** Inserts a character in the onestring at the given position.
	 * \param the index to insert at.
	 * If this is greater than the string length, it throws out_of_range
	 * \param the onechar to insert
	 * \return a reference to the onestring */
	onestring& insert(size_t pos, onechar& ochr)
	{
		// Ensure the insertion position is in range.
		if (pos >= this->_elements) {
			throw std::out_of_range(
				"Onestring::insert(): specified pos out of range");
		}

		// Reserve needed space
		expand(1);
		// Move the right partition to make room for the new element
		shift(pos, 1);

		// Insert the new element
		this->internal[pos] = ochr;
		// Increase the element count
		++_elements;

		this->invalidate_c_str();
		return *this;
	}

	/** Inserts characters in the onestring at the given position.
	 * \param the index to insert at.
	 * If this is greater than the string length, it throws out_of_range
	 * \param the c-string to insert
	 * \return a reference to the onestring */
	onestring& insert(size_t pos, char* cstr)
	{
		// Ensure the insertion position is in range.
		if (pos >= this->_elements) {
			throw std::out_of_range(
				"Onestring::insert(): specified pos out of range");
		}

		size_t elements_to_insert = characterCount(cstr);
		// Reserve needed space
		expand(elements_to_insert);
		// Move the right partition to make room for the new element
		shift(pos, elements_to_insert);

		// Insert the new elements
		size_t index = 0;
		while (cstr[index] != '\0') {
			// Parse and store the character.
			index += internal[pos++].parseFromString(cstr, index);
		}
		// Increase the element count
		_elements += elements_to_insert;

		this->invalidate_c_str();
		return *this;
	}

	/** Inserts characters in the onestring at the given position.
	 * \param the index to insert at.
	 * If this is greater than the string length, it throws out_of_range
	 * \param the std::basic_string to insert
	 * \return a reference to the onestring */
	template<typename T>
	onestring& insert(size_t pos, std::basic_string<T>& str)
	{
		return insert(pos, str.c_str());
	}

	/** Inserts characters in the onestring at the given position.
	 * \param the index to insert at.
	 * If this is greater than the string length, it throws out_of_range
	 * \param the onestring to insert
	 * \return a reference to the onestring */
	onestring& insert(size_t pos, const onestring& ostr)
	{
		// Ensure the insertion position is in range.
		if (pos >= this->_elements) {
			throw std::out_of_range(
				"Onestring::insert(): specified pos out of range");
		}

		size_t elements_to_insert = ostr._elements;
		// Reserve needed space
		expand(elements_to_insert);
		// Move the right partition to make room for the new element
		shift(pos, elements_to_insert);

		// Insert the new elements
		for (size_t i = 0; i < ostr._elements; ++i) {
			this->internal[pos + i] = ostr.internal[i];
		}
		// Increase the element count
		_elements += elements_to_insert;

		this->invalidate_c_str();
		return *this;
	}

	/**Removes the last element in a onestring */
	void pop_back()
	{
		if (_elements > 0) {
			/* We don't actually need to delete anything. The space will be
			 * reused or deallocated as needed by other functions. */
			--_elements;
			this->invalidate_c_str();
		}
	}

	/** Appends a character to the end of the onestring.
	 * \param the char to append */
	void push_back(char ch) { append(ch); }

	/** Appends a character to the end of the onestring.
	 * \param the onechar to append */
	void push_back(const onechar& ochr) { append(ochr); }

	/** Appends characters to the end of the onestring.
	 * \param the c-string to append from */
	void push_back(const char* cstr) { append(cstr); }

	/** Appends characters to the end of the onestring.
	 * \param the std::basic_string to append from */
	template<typename T>
	void push_back(const std::basic_string<T>& str) { append(str); }

	/** Appends characters to the end of the onestring.
	 * \param the onestring to append from */
	void push_back(const onestring& ostr) { append(ostr); }

	// TODO: Implement rvalue versions of most of the above

protected:
	/** Modifies the internal data structure in preparation for a
	 * replacement of characters. Intended ONLY to be used by
	 * replace()! DOES NOT validate pos, len, or sublen! If used
	 * improperly, can cause undefined behavior or memory errors.
	 * \param the first index of the range to replace in the onestring
	 * \param the number of characters in the range to replace
	 * \param the number of characters that will be substituted in
	 * place of the given range */
	inline void replace_setup(size_t pos, size_t len, size_t sublen)
	{
		// WARNING: pos and len are not validated. That MUST be done externally!

		// Calculate whether we're replacing 1:1, expanding, or erasing
		int difference = sublen - len;
		size_t pos_after = pos + len;
		size_t elements_after = _elements - pos_after;

		// If our replacement expands the string...
		if (difference > 0) {
			// Reserve the needed space
			expand(difference);

			// Move the right partition to make room, if necessary
			if (elements_after > 0) {
				shift(pos, difference);
			}

			// Update the element count
			_elements += difference;
		}
		// Otherwise, if our replacement shrinks the string...
		else if (difference < 0) {
			// Move the right partition back, erasing excess characters.
			if (elements_after > 0) {
				shift(pos_after, difference);
			}

			// Update the element count
			_elements += difference;
		}

		// If the string size won't change, we need no extra setup.
	}

public:
	/** Replaces characters in the onestring.
	 * \param the first position to replace.
	 * If this is greater than the string length, it throws out_of_range.
	 * \param the number of characters to replace.
	 * \param the char to replace from.
	 * \return a reference to the onestring */
	onestring& replace(size_t pos, size_t len, const char ch)
	{
		// Ensure the replacement position is in range.
		if (pos >= this->_elements) {
			throw std::out_of_range(
				"Onestring::replace(): specified pos out of range");
		}

		// Adjust len so it doesn't run past the end of the string
		len = (len > _elements - pos) ? (_elements - pos) : len;

		// Rearrange the string memory to accommodate the new data
		replace_setup(pos, len, 1);

		// Write the data, using pos as our destination index.
		this->internal[pos] = ch;

		this->invalidate_c_str();
		return *this;
	}

	/** Replaces characters in the onestring.
	 * \param the first position to replace.
	 * If this is greater than the string length, it throws out_of_range.
	 * \param the number of characters to replace.
	 * \param the onechar to replace from.
	 * \return a reference to the onestring */
	onestring& replace(size_t pos, size_t len, const onechar& ochr)
	{
		// Ensure the replacement position is in range.
		if (pos >= this->_elements) {
			throw std::out_of_range(
				"Onestring::replace(): specified pos out of range");
		}

		// Adjust len so it doesn't run past the end of the string
		len = (len > _elements - pos) ? (_elements - pos) : len;

		// Rearrange the string memory to accommodate the new data
		replace_setup(pos, len, 1);

		// Write the data, using pos as our destination index.
		this->internal[pos] = ochr;

		this->invalidate_c_str();
		return *this;
	}

	/** Replaces characters in the onestring.
	 * \param the first position to replace.
	 * If this is greater than the string length, it throws out_of_range.
	 * \param the number of characters to replace.
	 * \param the c-string to replace from.
	 * \return a reference to the onestring */
	onestring& replace(size_t pos, size_t len, const char* cstr)
	{
		// Ensure the replacement position is in range.
		if (pos >= this->_elements) {
			throw std::out_of_range(
				"Onestring::replace(): specified pos out of range");
		}

		// Adjust len so it doesn't run past the end of the string
		len = (len > _elements - pos) ? (_elements - pos) : len;

		// Rearrange the string memory to accommodate the new data
		replace_setup(pos, len, characterCount(cstr));

		// Write the data, using pos as our destination index.
		size_t index = 0;
		while (cstr[index] != '\0') {
			// Parse and store the character.
			index += internal[pos++].parseFromString(cstr, index);
		}

		this->invalidate_c_str();
		return *this;
	}

	/** Replaces characters in the onestring.
	 * \param the first position to replace.
	 * If this is greater than the string length, it throws out_of_range.
	 * \param the number of characters to replace.
	 * \param the std::basic_string to replace from.
	 * \return a reference to the onestring */
	template<typename T>
	onestring& replace(size_t pos, size_t len, const std::basic_string<T>& str)
	{
		return replace(pos, len, str.c_str());
	}

	/** Replaces characters in the onestring.
	 * \param the first position to replace.
	 * If this is greater than the string length, it throws out_of_range.
	 * \param the number of characters to replace.
	 * \param the onestring to replace from.
	 * \return a reference to the onestring */
	onestring& replace(size_t pos, size_t len, const onestring& ostr)
	{
		// Ensure the replacement position is in range.
		if (pos >= this->_elements) {
			throw std::out_of_range(
				"Onestring::replace(): specified pos out of range");
		}

		// Adjust len so it doesn't run past the end of the string
		len = (len > _elements - pos) ? (_elements - pos) : len;

		// Rearrange the string memory to accommodate the new data
		replace_setup(pos, len, ostr._elements);

		for (size_t i = 0; i < ostr._elements; ++i) {
			this->internal[pos + i] = ostr.internal[i];
		}

		this->invalidate_c_str();
		return *this;
	}

	/** Replaces characters in the onestring.
	 * \param the first position to replace.
	 * If this is greater than the string length, it throws out_of_range.
	 * \param the number of characters to replace.
	 * \param the c-string to replace from
	 * \param the index of the first character in the c-string to replace from
	 * If this is greater than the c-string length, it throws out_of_range.
	 * \param the number of characters to copy over.
	 * \return a reference to the onestring */
	onestring& replace(
		size_t pos, size_t len, const char* cstr, size_t subpos, size_t sublen)
	{
		// Ensure the replacement position is in range.
		if (pos >= this->_elements) {
			throw std::out_of_range(
				"Onestring::replace(): specified pos out of range");
		}

		size_t cstr_len = strlen(cstr);
		if (subpos >= cstr_len) {
			throw std::out_of_range(
				"Onestring::replace(): specified subpos out of range");
		}

		// Adjust len so it doesn't run past the end of the string
		len = (len > _elements - pos) ? (_elements - pos) : len;
		// Adjust sublen so it doesn't run past the end of the c-string.
		sublen = (sublen > cstr_len - subpos) ? (cstr_len - subpos) : sublen;

		// Rearrange the string memory to accommodate the new data
		replace_setup(pos, len, sublen);

		// Repurpose sublen so it marks the end of the area we are to copy from
		sublen += subpos;

		// Replace the characters in the specified range, using pos and subpos
		// as our indices.
		while (subpos < sublen) {
			// Parse and store the character.
			subpos += internal[pos++].parseFromString(cstr, subpos);
		}

		this->invalidate_c_str();
		return *this;
	}

	/** Replaces characters in the onestring.
	 * \param the first position to replace.
	 * If this is greater than the string length, it throws out_of_range.
	 * \param the number of characters to replace.
	 * \param the std::basic_string to replace from
	 * \param the index of the first character in the std::basic_string to replace
	 * from If this is greater than the std::basic_string length, it throws
	 * out_of_range. \param the number of characters to copy over. \return a
	 * reference to the onestring */
	template<typename T>
	onestring& replace(size_t pos,
					   size_t len,
					   const std::basic_string<T>& str,
					   size_t subpos,
					   size_t sublen)
	{
		return replace(pos, len, str.c_str(), subpos, sublen);
	}

	/** Replaces characters in the onestring.
	 * \param the first position to replace.
	 * If this is greater than the string length, it throws out_of_range.
	 * \param the number of characters to replace.
	 * \param the onestring to replace from
	 * \param the index of the first character in the onestring to replace from
	 * If this is greater than the onestring length, it throws out_of_range.
	 * \param the number of characters to copy over.
	 * \return a reference to the onestring */
	onestring& replace(size_t pos,
					   size_t len,
					   const onestring& ostr,
					   size_t subpos,
					   size_t sublen)
	{
		// Ensure the replacement position is in range.
		if (pos >= this->_elements) {
			throw std::out_of_range(
				"Onestring::replace(): specified pos out of range");
		}

		if (subpos >= ostr._elements) {
			throw std::out_of_range(
				"Onestring::replace(): specified subpos out of range");
		}

		// Adjust len so it doesn't run past the end of the string
		len = (len > _elements - pos) ? (_elements - pos) : len;
		// Adjust sublen so it doesn't run past the end of the c-string.
		sublen = (sublen > ostr._elements - subpos) ? (ostr._elements - subpos)
													: sublen;

		// Rearrange the string memory to accommodate the new data
		replace_setup(pos, len, sublen);

		for (size_t i = 0; i < sublen; ++i) {
			this->internal[pos + i] = ostr.internal[subpos + i];
		}

		this->invalidate_c_str();
		return *this;
	}

	/** Reverses the contents of the onestring in place. */
	onestring& reverse()
	{
		// Create temporary storage unit
		onechar temp;

		// Perform the swap
		size_t lhe = 0;
		size_t rhe = _elements - 1;
		while (lhe < rhe) {
			temp = this->internal[rhe];
			this->internal[rhe] = this->internal[lhe];
			this->internal[lhe] = temp;
			++lhe;
			--rhe;
		}

		this->invalidate_c_str();
		return *this;
	}

	/** Exchanges the content of this onestring with that of the given
	 * std::basic_string.
	 * \param the std::basic_string to swap with
	 */
	template<typename T>
	void swap(std::basic_string<T>& str)
	{
		std::basic_string<T> temp = str;
		str.assign(this->c_str());
		this->assign(temp);
		this->invalidate_c_str();
	}

	/** Exchanges the content of this onestring with that of the given
	 * onestring. \param the onestring to swap with */
	void swap(onestring& ostr)
	{
		onestring temp = ostr;
		ostr.assign(*this);
		this->assign(temp);
		this->invalidate_c_str();
	}

	/** Exchanges the content of the given strings.
	 * \param the first string to swap
	 * \param the second string to swap
	 */
	template<typename T>
	static void swap(std::basic_string<T>& lhs, onestring& rhs) { rhs.swap(lhs); }

	/** Exchanges the content of the given strings.
	 * \param the first string to swap
	 * \param the second string to swap
	 */
	template<typename T>
	static void swap(onestring& lhs, std::basic_string<T>& rhs) { lhs.swap(rhs); }

	/** Exchanges the content of the given strings.
	 * \param the first string to swap
	 * \param the second string to swap
	 */
	static void swap(onestring& lhs, onestring& rhs) { lhs.swap(rhs); }

	/*******************************************
	 * Operators
	 ********************************************/

	onechar& operator[](size_t pos) { return at(pos); }
	const onechar& operator[](size_t pos) const { return at(pos); }

	onestring& operator=(char ch)
	{
		assign(ch);
		return *this;
	}

	onestring& operator=(const onechar& ochr)
	{
		assign(ochr);
		return *this;
	}

	onestring& operator=(const char* cstr)
	{
		assign(cstr);
		return *this;
	}

	template<typename T>
	onestring& operator=(const std::basic_string<T>& str)
	{
		assign(str);
		return *this;
	}
	onestring& operator=(const onestring& ostr)
	{
		assign(ostr);
		return *this;
	}

	void operator+=(const char ch) { append(ch); }
	void operator+=(const onechar& ochr) { append(ochr); }
	void operator+=(const char* cstr) { append(cstr); }
	template<typename T>
	void operator+=(const std::basic_string<T>& str) { append(str); }
	void operator+=(const onestring& ostr) { append(ostr); }

	/** Combines a onestring and a char.
	 * \param lhs: the operand on the left of the operator
	 * \param rhs: the operand on the right of the operator
	 * \return a new onestring object
	 */
	friend onestring operator+(const onestring& lhs, const char& rhs)
	{
		onestring new_ostr(lhs);
		new_ostr.append(rhs);
		return new_ostr;
	}

	// Combines a onestring and a char.
	friend onestring operator+(const char& lhs, const onestring& rhs)
	{
		onestring new_ostr(lhs);
		new_ostr.append(rhs);
		return new_ostr;
	}

	// Combine a onestring and a std::basic_string.
	template<typename T>
	friend onestring operator+(const onestring& lhs, const std::basic_string<T>& rhs)
	{
		onestring new_ostr(lhs);
		new_ostr.append(rhs);
		return new_ostr;
	}

	// Combine a onestring and a std::basic_string.
	template<typename T>
	friend onestring operator+(const std::basic_string<T>& lhs, const onestring& rhs)
	{
		onestring new_ostr(lhs);
		new_ostr.append(rhs);
		return new_ostr;
	}

	// Combine a onestring and a c string.
	friend onestring operator+(const onestring& lhs, const char* rhs)
	{
		onestring new_ostr(lhs);
		new_ostr.append(rhs);
		return new_ostr;
	}

	// Combine a onestring and a c string.
	friend onestring operator+(const char* lhs, const onestring& rhs)
	{
		onestring new_ostr(lhs);
		new_ostr.append(rhs);
		return new_ostr;
	}

	// Combine a onestring and a onestring.
	friend onestring operator+(const onestring& lhs, const onestring& rhs)
	{
		onestring new_ostr(lhs);
		new_ostr.append(rhs);
		return new_ostr;
	}

	bool operator==(const char ch) const { return equals(ch); }
	bool operator==(const onechar& ochr) const { return equals(ochr); }
	bool operator==(const char* cstr) const { return equals(cstr); }
	template<typename T>
	bool operator==(const std::basic_string<T>& str) const { return equals(str); }
	bool operator==(const onestring& ostr) const { return equals(ostr); }

	friend bool operator==(const char ch, const onestring& ostr)
	{
		return ostr.equals(ch);
	}
	friend bool operator==(const onechar& ochr, const onestring& ostr)
	{
		return ostr.equals(ochr);
	}
	friend bool operator==(const char* cstr, const onestring& ostr)
	{
		return ostr.equals(cstr);
	}
	template<typename T>
	friend bool operator==(const std::basic_string<T>& str, const onestring& ostr)
	{
		return ostr.equals(str);
	}

	bool operator!=(const char ch) const { return !equals(ch); }
	bool operator!=(const onechar& ochr) const { return !equals(ochr); }
	bool operator!=(const char* cstr) const { return !equals(cstr); }
	template<typename T>
	bool operator!=(const std::basic_string<T>& str) const { return !equals(str); }
	bool operator!=(const onestring& ostr) const { return !equals(ostr); }

	friend bool operator!=(const char ch, const onestring& ostr)
	{
		return !ostr.equals(ch);
	}
	friend bool operator!=(const onechar& ochr, const onestring& ostr)
	{
		return !ostr.equals(ochr);
	}
	friend bool operator!=(const char* cstr, const onestring& ostr)
	{
		return !ostr.equals(cstr);
	}
	template<typename T>
	friend bool operator!=(const std::basic_string<T>& str, const onestring& ostr)
	{
		return !ostr.equals(str);
	}

	bool operator<(const char ch) const { return (compare(ch) < 0); }
	bool operator<(const onechar& ochr) const { return (compare(ochr) < 0); }
	bool operator<(const char* cstr) const { return (compare(cstr) < 0); }
	template<typename T>
	bool operator<(const std::basic_string<T>& str) const { return (compare(str) < 0); }
	bool operator<(const onestring& ostr) const { return (compare(ostr) < 0); }

	friend bool operator<(const char ch, const onestring& ostr)
	{
		return (ostr.compare(ch) > 0);
	}
	friend bool operator<(const onechar& ochr, const onestring& ostr)
	{
		return (ostr.compare(ochr) > 0);
	}
	friend bool operator<(const char* cstr, const onestring& ostr)
	{
		return (ostr.compare(cstr) > 0);
	}
	template<typename T>
	friend bool operator<(const std::basic_string<T>& str, const onestring& ostr)
	{
		return (ostr.compare(str) > 0);
	}

	bool operator<=(const char ch) const { return (compare(ch) <= 0); }
	bool operator<=(const onechar& ochr) const { return (compare(ochr) <= 0); }
	bool operator<=(const char* cstr) const { return (compare(cstr) <= 0); }
	template<typename T>
	bool operator<=(const std::basic_string<T>& str) const
	{
		return (compare(str) <= 0);
	}
	bool operator<=(const onestring& ostr) const
	{
		return (compare(ostr) <= 0);
	}

	friend bool operator<=(const char ch, const onestring& ostr)
	{
		return (ostr.compare(ch) >= 0);
	}
	friend bool operator<=(const onechar& ochr, const onestring& ostr)
	{
		return (ostr.compare(ochr) >= 0);
	}
	friend bool operator<=(const char* cstr, const onestring& ostr)
	{
		return (ostr.compare(cstr) >= 0);
	}
	template<typename T>
	friend bool operator<=(const std::basic_string<T>& str, const onestring& ostr)
	{
		return (ostr.compare(str) >= 0);
	}

	bool operator>(const char ch) const { return (compare(ch) > 0); }
	bool operator>(const onechar& ochr) const { return (compare(ochr) > 0); }
	bool operator>(const char* cstr) const { return (compare(cstr) > 0); }
	template<typename T>
	bool operator>(const std::basic_string<T>& str) const { return (compare(str) > 0); }
	bool operator>(const onestring& ostr) const { return (compare(ostr) > 0); }

	friend bool operator>(const char ch, const onestring& ostr)
	{
		return (ostr.compare(ch) < 0);
	}
	friend bool operator>(const onechar& ochr, const onestring& ostr)
	{
		return (ostr.compare(ochr) < 0);
	}
	friend bool operator>(const char* cstr, const onestring& ostr)
	{
		return (ostr.compare(cstr) < 0);
	}
	template<typename T>
	friend bool operator>(const std::basic_string<T>& str, const onestring& ostr)
	{
		return (ostr.compare(str) < 0);
	}

	bool operator>=(const char ch) const { return (compare(ch) >= 0); }
	bool operator>=(const onechar& ochr) const { return (compare(ochr) >= 0); }
	bool operator>=(const char* cstr) const { return (compare(cstr) >= 0); }
	template<typename T>
	bool operator>=(const std::basic_string<T>& str) const
	{
		return (compare(str) >= 0);
	}
	bool operator>=(const onestring& ostr) const
	{
		return (compare(ostr) >= 0);
	}

	friend bool operator>=(const char ch, const onestring& ostr)
	{
		return (ostr.compare(ch) <= 0);
	}
	friend bool operator>=(const onechar& ochr, const onestring& ostr)
	{
		return (ostr.compare(ochr) <= 0);
	}
	friend bool operator>=(const char* cstr, const onestring& ostr)
	{
		return (ostr.compare(cstr) <= 0);
	}
	template<typename T>
	friend bool operator>=(const std::basic_string<T>& str, const onestring& ostr)
	{
		return (ostr.compare(str) <= 0);
	}

	// TODO: Implement iterators

	friend std::istream& operator>>(std::istream& is, onestring& ostr)
	{
		ostr.clear();

		char ch;
		while (is.get(ch) && !isspace(ch)) {
			ostr.append(ch);
		}
		return is;
	}

	friend std::ostream& operator<<(std::ostream& os, const onestring& ostr)
	{
		os << ostr.c_str();
		return os;
	}
};

#endif  // ONESTRING_ONESTRING_HPP
