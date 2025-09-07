Usage examples
==============

.. _example-1:

Example 1: hashing memory-mapped files
--------------------------------------


This code demonstrates the simplest usage scenario of the SHA-3 library, utilizing memory-mapped files to perform hashing on the entire file in a single operation.
This approach is efficient for files that can fit entirely in memory, as it minimizes system calls and allows the SHA-3 algorithm to process the data in one contiguous block.


.. literalinclude:: ../../examples/single_mode.cc
   :language: cpp
   :lines: 8-32, 34-35, 47-52

.. _example-2:

Example 2: hashing file block-by-block
--------------------------------------


The code below is designed for processing large volumes of data or data that is stored in multiple locations.
It demonstrates how to use the combination of ``update`` and ``finalize`` methods to incrementally process data chunks while maintaining the correct hash computation.
This approach is memory-efficient and suitable for streaming applications or handling files that are too large to load into memory at once.


.. literalinclude:: ../../examples/chunked.cc
   :language: cpp
   :lines: 8-16, 18, 27-64, 66, 75-81
   :emphasize-lines: 17-28


The highlighted code performs automatically alignment the desired buffer size according to SHA-3's block size requirements and ``posix_memalign`` alignment constraints
