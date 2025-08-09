# SHA-3 hash

*High-performance* implementation of SHA-3 hashing according to the **FIPS 202** standard

---

## 📦 Installation

Clone the repository:

```bash
git clone https://github.com/gdaneek/sha-3.git
```

Build the project using CMake:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

After building, the executables will be located in the `build/` directory.

---

## 🛠️ Program Usage

There are two ways to compute SHA-3 hashes:

### 1. Mode-Specific Executables

Use files named `sha3_<mode>` (where `<mode>` = `224`, `256`, `384`, or `512`) to compute the hash:

```bash
sha3_256 file.txt
```

This command computes the SHA-3 hash of `file.txt` using the 256-bit mode.

---

### 2. Unified Executable

Use the main executable `sha3` and specify the mode as a command-line argument:

```bash
sha3 512 file.txt
```

This computes the SHA-3 hash of `file.txt` using the 512-bit mode.

> Versions with the `chunked_` prefix use an alternative file processing method, but produce the same results


---

## 🧑‍💻 Development

The implementation is provided as a C++ header-only library. To use it:

1. Include the header file in your project:

```cpp
#include "sha3.hpp"
```

2. Make sure the compiler knows the path to the `include/` directory of this repository.

📚 Explore [**usage examples**](example/) and the [**programmer's guide**](https://gdaneek.github.io/sha-3) for more information.

---

## 📄 Documentation

Read the full documentation online at [**GitHub Pages**](https://gdaneek.github.io/sha-3).

Alternatively, generate the documentation locally with Doxygen:

```bash
doxygen doc/Doxyfile
```

The generated documentation will be available in the `doc/code/` subfolder.

---

## 🧪 Benchmarking

See [**Manual benchmark**](doc/benchmark.md) for performance testing instructions or
see the results of automatic CI/CD benchmarking below

<details>
<summary>Github Actions benchmarking</summary>

> Runs on ubuntu latest

<!-- BENCHMARK_START -->


<!-- BENCHMARK_END -->

</details>


---

## 📜 License

Distributed under the **MIT License**. See [LICENSE](LICENSE) for details.
