# SHA-3

[![FIPS 202](https://img.shields.io/badge/standard-FIPS%20202-blue?style=flat)](https://csrc.nist.gov/pubs/fips/202/final)
![C++20](https://img.shields.io/badge/code-C++20-purple?style=flat)
![Google Code Style](https://img.shields.io/badge/style-Google-purple?style=flat)
[![Benchmark](https://img.shields.io/badge/benchmark-race-brightgreen?style=flat)](docs/benchmark.md)
[![GitHub license](https://img.shields.io/github/license/gdaneek/sha-3?style=flat)](https://github.com/gdaneek/sha-3/blob/master/LICENSE)
[![CMake tests](https://github.com/gdaneek/sha-3/actions/workflows/test.yml/badge.svg?)](https://github.com/gdaneek/sha-3/actions/workflows/test.yml)
[![Deploy Pages](https://github.com/gdaneek/sha-3/actions/workflows/pages.yml/badge.svg?)](https://github.com/gdaneek/sha-3/actions/workflows/pages.yml)
[![CI/CD Benchmark](https://github.com/gdaneek/sha-3/actions/workflows/benchmark.yml/badge.svg?)](https://github.com/gdaneek/sha-3/actions/workflows/benchmark.yml)

**High-performance** implementation of SHA-3 hashing according to the *FIPS 202* standard

---

## 📦 Installation

Clone the repository:

```bash
git clone https://github.com/gdaneek/sha-3.git
```

Build the project using CMake:

```bash
mkdir build
cmake -S . -B build
cmake --build build
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

📚 Explore [**usage examples**](examples/) and the [**programmer's guide**](https://gdaneek.github.io/sha-3) for more information.

---

## 📄 Documentation

Read the full documentation online at [**GitHub Pages**](https://gdaneek.github.io/sha-3).

Alternatively, generate the documentation locally with Doxygen:

```bash
doxygen docs/Doxyfile
```

The generated documentation will be available in the `docs/code/` subfolder.

---

## 🧪 Benchmark

See [**Manual benchmark**](docs/benchmark.md) for performance testing instructions or
results of automatic CI/CD benchmarking below

<details>
<summary>Github Actions benchmarking</summary>


> Runs on ubuntu latest


<!-- BENCHMARK_START -->

### sha-3-224

| Command | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `./sha3 224 4GB` | 9.784 ± 0.003 | 9.781 | 9.792 | 1.00 |
| `./chunked_sha3_224 4GB` | 9.884 ± 0.011 | 9.877 | 9.906 | 1.01 ± 0.00 |
| `openssl dgst -sha3-224 4GB` | 10.084 ± 0.063 | 10.022 | 10.257 | 1.03 ± 0.01 |
| `sha3sum -a 224 4GB` | 16.449 ± 0.722 | 16.210 | 18.504 | 1.68 ± 0.07 |
| `rhash --sha3-224 4GB` | 12.276 ± 0.011 | 12.262 | 12.299 | 1.25 ± 0.00 |

### sha-3-256

| Command | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `./sha3 256 4GB` | 10.338 ± 0.003 | 10.334 | 10.345 | 1.00 |
| `./chunked_sha3_256 4GB` | 10.434 ± 0.011 | 10.426 | 10.463 | 1.01 ± 0.00 |
| `openssl dgst -sha3-256 4GB` | 10.641 ± 0.049 | 10.605 | 10.778 | 1.03 ± 0.00 |
| `sha3sum -a 256 4GB` | 17.119 ± 0.301 | 17.005 | 17.973 | 1.66 ± 0.03 |
| `rhash --sha3-256 4GB` | 12.937 ± 0.053 | 12.895 | 13.078 | 1.25 ± 0.01 |

### sha-3-384

| Command | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `./sha3 384 4GB` | 13.397 ± 0.006 | 13.391 | 13.410 | 1.03 ± 0.00 |
| `./chunked_sha3_384 4GB` | 13.483 ± 0.018 | 13.472 | 13.530 | 1.03 ± 0.00 |
| `openssl dgst -sha3-384 4GB` | 13.064 ± 0.018 | 13.046 | 13.101 | 1.00 |
| `sha3sum -a 384 4GB` | 21.465 ± 0.025 | 21.437 | 21.510 | 1.64 ± 0.00 |
| `rhash --sha3-384 4GB` | 16.663 ± 0.020 | 16.643 | 16.706 | 1.28 ± 0.00 |

### sha-3-512

| Command | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `./sha3 512 4GB` | 19.168 ± 0.022 | 19.147 | 19.210 | 1.04 ± 0.00 |
| `./chunked_sha3_512 4GB` | 19.254 ± 0.014 | 19.244 | 19.292 | 1.04 ± 0.00 |
| `openssl dgst -sha3-512 4GB` | 18.455 ± 0.011 | 18.441 | 18.473 | 1.00 |
| `sha3sum -a 512 4GB` | 29.898 ± 0.056 | 29.845 | 30.021 | 1.62 ± 0.00 |
| `rhash --sha3-512 4GB` | 23.764 ± 0.040 | 23.724 | 23.867 | 1.29 ± 0.00 |


### Summary

| Top | Command |
|-----|---------|
| 🥇 | ./sha3<br>openssl |
| 🥈 | ./chunked_sha3 |
| 🥉 | rhash |

<!-- BENCHMARK_END -->

</details>


---

## 📜 License

Distributed under the **MIT License**. See [LICENSE](LICENSE) for details.
