Onestring
#############################

What is Onestring?
===================================
``onestring`` is a multi-sized, Unicode-compatible replacement
for ``std::string``. Onestring contains all the
basic functions found in ``std::string`` while optimizing
the use of dynamic allocation wherever possible.
To handle Unicode, each Onestring is made of Onechars,
which are enhanced characters.


Using a Onestring
=====================================

Creating a ``onestring``
--------------------------------------
You can create a ``onestring`` with characters initialized with the ``=`` operator
or leave it blank.

..  code-block:: c++

    // Empty Onestring.
    onestring blankString;

    // Containing Onechars.
    onestring fullString = "these are Unicode Characters";

You can also use the ``=`` operator to create a new ``onestring`` with an existing
``onestring``.

..  code-block:: c++

    // Create the first Onestring.
    onestring firstString = "copy me";

    // Containing Onechars.
    onestring secondString = firstString;

    std::cout << secondString << std::endl; // secondString now contains "copy me".

Adding to a ``onestring``
---------------------------------------

``+``, ``+=``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

The ``+=`` and ``+`` operators add additional Unicode characters at the end of the existing ``onestring``.

Using ``+=``:

..  code-block:: c++

    //Declare a Onestring.
    onestring more = "apple";

    // Use += to append an "s".
    more += "s";

    std::cout << more << std::endl; // "apples".
    
    // Use + to append "!".
    more = more + "!";

    std::cout << more << std::endl; // "apples!".

``append()``, ``push_back()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Alternatively, you can use the functions ``append()`` and ``push_back()`` to add additional Unicode characters at the end of the existing ``onestring``.

Using ``append()``:

..  code-block:: c++

    // Declare a Onestring.
    onestring fruit = "apple";

    // Add "s" to `fruit`.
    fruit.append('s');

    std::cout << fruit << std::endl; // Now `fruit` is "apples".

Using ``push_back()``:

..  code-block:: c++

    // Add "!" to `fruit`.
    fruit.push_back('!');

    std::cout << fruit << std::endl; // "apples!".

``insert()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``insert()`` allows you to insert a Unicode character into an existing ``onestring`` at a given position.

..  code-block:: c++

    // Declare a Onestring
    onestring alphabet = "abcdf";

    // Insert a value into `alphabet`.
    // The first value in the function refers to the index to be inserted.
    // The second value refers to the value to be inserted.
    alphabet.insert(4, 'E');

    std::cout << alphabet << std::endl; // "abcdEf".

Removing from a ``onestring``
---------------------------------------

``clear()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``clear()`` erases the contents of a Onestring.

..  code-block:: c++

    // Declare a Onestring.
    Onestring sleeve = "something";

    // Clear the contents of `sleeve`.
    sleeve.clear();

    std::cout << sleeve << std::endl; // Now `sleeve` is empty.

``erase()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``erase()`` erases part of a string, reducing its length.

..  code-block:: c++

    // Declare a Onestring.
    onestring pokemon = "Pikachu";

    //Reduce the length of `pokemon`.
    pokemon.erase(2);

    std::cout << pokemon << std::endl; // "Pi"


``pop_back()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``pop_back()`` removes the last Unicode character in the Onestring

..  code-block:: c++

    // Declare a Onestring.
    Onestring alphabet = "abcdef";

    // Remove the last element from `alphabet`.
    alphabet.pop_back();

    std::cout << alphabet << std::endl; // "abcde".

``replace()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``replace()`` replaces characters in the onestring.

1. First parameter is the position where you want to replace.
2. Second parameter is number of characters you want to replace.
3. Third parameter is the characters you want add on your ``onestring``.

..  code-block:: c++

    // Declare a Onestring.
    onestring hero = "Mario";

    //Replacing "M" of `hero`.
    hero.replace(0, 1, 'W');

    std::cout << hero << std::endl; // "Wario"

Accessing Elements of a ``onestring``
---------------------------------------
``[]``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The ``[]`` operator acceses a Unicode character at a given location in a
``onestring``.

..  code-block:: c++

    // Declare a Onestring.
    onestring test = "hello";

    // Check what character is at position 1 in `test`.
    std::cout << test[1] << std::endl; // 'e'.

``at()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``at()`` can be used as an alternative to ``[]``.

..  code-block:: c++

    // Declare a Onestring.
    onestring alphabet = "abcdef";

    // Find the Onechar at position 3 in `alphabet`.
    std::cout << alphabet.at(3) << std::endl; // 'd'.

``back()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``back()`` returns the last Unicode character in a ``onestring``.

..  code-block:: c++

    // Declare a Onestring.
    onestring day = "Sunday";

    // Get last the Onechar in `day`.
    std::cout << day.back() << std::endl; // 'y'.

``front()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``front()`` returns the first Unicode character in a ``onestring``.

..  code-block:: c++

    // Declare a Onestring
    onestring day = "Monday";

    // Get first the Onechar in `day`
    std::cout << day.back() << std::endl; // The function returns "M".

..  note:: If the string is empty, the function will return ``undefined``, but memory safe.

Comparing Onestrings
---------------------------------------

``==``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The ``==`` operator checks for equivalence between two strings and returns
a boolean with the result.

..  code-block:: c++

    // Declare two Onestring.
    onestring dogs = "fun";
    onestring cats = "mean";

    // Check for equivalence.
    if (dogs == cats) {
      return dogs;
    } else {
      return cats;
    }

    // This statement would return `cats`.

    // Reassign `cats`.
    cats = "fun";

    // Check for equivalence.
    if (dogs == cats) {
      return dogs;
    } else {
      return cats;
    }

    // The statement now returns `dogs`.

``compare()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``compare()`` compares the onestring against a c-string and an integer representing the result. Also, it returns one of the following integers:

1. If the ``onestring`` is shorter, it will return a negative integer.
2. If the values are the same, it will return ``0``.
3. If the ``onestring`` is longer, it will return a positive integer.

..  code-block:: c++

    // Declare two Onestring.
    onestring jack = "short";
    onestring alain = "big";

    //Compare two Onestring.
    std::cout << jack.compare(alain) << std::endl; \\ Returns 2.

``equals()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``equals()`` checks for equality.

..  code-block:: c++

    // Declare a Onestring.
    onestring checker = "red";

    // Compare with another Onestring.
    std::cout << checker.equals("black") << std::endl; // Returns false.

    // Compare again.
    std::cout << checker.equals("red") << std::endl; // Returns true.

``<, >, <=, >=``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The ``<``, ``>``, ``<=``, and ``>=`` operators compare string sizes, with the first
relative to the second. ``<`` is less than, ``>`` is greater than, and ``<=`` and
``>=`` are less than or equal to, and greater than or equal to, respectively.

..  code-block:: c++

    // Delcare three Onestrings.
    onestring first = "one";
    onestring second = "two";
    onestring third = "three";

    // Compare `first` to `second`.
    if (first < second) {
      return first;
    } else {
      return second;
    }

    // The statement returns "two".

    if (first <= second) {
      return first;
    } else {
      return second;
    }

    // The statement now returns "one".

    if (third > second) {
      return third;
    } else {
      return second;
    }

    // Finally, this statement returns "three".

Other Functions
--------------------------------------

``c_str()``, ``data()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Alternatively, you can use ``c_str()`` and ``data()`` return a c-string equivalent of a onestring.

..  code-block:: c++

    // Declare a Onestring.
    onestring car = "Ford";

    // Using `c_str()`.
    std::cout << car.c_str() << std::endl;

    // Using `data()`.
    std::cout << car.data() << std::endl;

    // Both will return the same value which is "Ford".


``capacity()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``capacity()`` returns the current capacity of the onestring (it is used primarily internally for resizing purposes.

..  code-block:: c++

    // Declare a Onestring.
    onestring bird = "Orchids";

    // Check the capacity of `bird`.
    std::cout << bird.capacity() << std::endl; // Returns 9.

``empty()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``empty()`` checks to see if a ``onestring`` is empty.
If the ``onestring`` is empty, the function returns ``true``, otherwise it returns ``false``.

..  code-block:: c++

    // Declare a Onestring.
    onestring toyBox;

    // Check to see if `toybox` empty.
    std::cout << toyBox.empty() << std::endl; // Returns true.

    // Assign values to `toyBox`.
    toyBox = "basketball";

    // Check again to see if its empty.
    std::cout << toyBox.empty() << std::endl; // Returns false.

``getType()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The ``getType()`` function returns a boolean that represents either a ``onestring``.
or a ``QuickString``.

``length()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``length()`` returns the current number of elements in a ``onestring``.

..  code-block:: c++

    // Declare a Onestring.
    onestring planet = "Mars";

    // Check the length of `planet`.
    std::cout << planet.length() << std::endl; // Returns 4.

``max_size()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``max_size()`` returns the greatest possible size in memory the ``onestring`` can take up without resizing.

..  code-block:: c++

    // Declare a Onestring.
    onestring city = "Paris";

    // Check the max size of `city`.
    std::cout << city.first.max_size() << std::endl; // Returns 18446744073709551615.

``reverse()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``reverse()`` reverses the contents of the ``onestring`` in place.

.. code-block:: c++

    //Declare Onestring.
    onestring animal = "Lion";

    //Reverse characters of `animal`
    animal.reverse();

    std::cout << animal << std::endl; // "noiL"

``size()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``size()`` returns the number of bytes in the ``onestring``.

..  code-block:: c++

    // Declare a Onestring.
    onestring checker = "red";

    // check the size of `checker`.
    std::cout << checker.size() << std::endl; // Returns 4.

``substr()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``substr()`` creates a new substring based on a range of characters in an exisiting
``Onestring``

..  code-block:: c++

    // Declare a Onestring.
    onestring full = "monochromatic";

    // Declare a new Onestring using `full` and substr.
    onestring partial = full.substr(0,3);

    std::cout << partial << std::endl; // "mono".

    // The numbers in the function call refers to the range to be copied into the new string.

``swap()``
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
``swap()`` switches the contents of the current ``onestring`` with another.
The two ``onestrings`` must be of the same size.

..  code-block:: c++

    // Declare two Onestrings.
    onestring first = "primary";
    onestring second = "secondary";

    // Swap `primary` and `secondary`.
    first.swap(second);

    std::cout << first << std::endl; // "secondary".
    std::cout << second << std::endl;// "primary".
