Quick start
===========

📦 Installation
---------------

Clone the repository:

.. code:: bash

   git clone https://github.com/gdaneek/sha-3.git

Build the project using CMake:

.. code:: bash

   mkdir build
   cmake -S . -B build
   cmake --build build

After building, the executables will be located in the ``build/``
directory.

🛠️Program Usage
----------------

There are two ways to compute SHA-3 hashes:

1. Mode-Specific Executables
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Use files named ``sha3_<mode>`` (where ``<mode>`` = ``224``, ``256``,
``384``, or ``512``) to compute the hash:

.. code:: bash

   sha3_256 file.txt

This command computes the SHA-3 hash of ``file.txt`` using the 256-bit
mode.

--------------

2. Unified Executable
~~~~~~~~~~~~~~~~~~~~~

Use the main executable ``sha3`` and specify the mode as a command-line
argument:

.. code:: bash

   sha3 512 file.txt

This computes the SHA-3 hash of ``file.txt`` using the 512-bit mode.

   Versions with the ``chunked_`` prefix use an alternative file
   processing method, but produce the same results
