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
| `./sha3 224 4GB` | 9.790 ± 0.015 | 9.780 | 9.825 | 1.00 |
| `./chunked_sha3_224 4GB` | 9.845 ± 0.031 | 9.807 | 9.911 | 1.01 ± 0.00 |
| `openssl dgst -sha3-224 4GB` | 10.066 ± 0.007 | 10.058 | 10.083 | 1.03 ± 0.00 |
| `sha3sum -a 224 4GB` | 16.242 ± 0.029 | 16.212 | 16.310 | 1.66 ± 0.00 |
| `rhash --sha3-224 4GB` | 12.286 ± 0.024 | 12.265 | 12.345 | 1.26 ± 0.00 |

### sha-3-256

| Command | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `./sha3 256 4GB` | 10.344 ± 0.021 | 10.329 | 10.387 | 1.00 |
| `./chunked_sha3_256 4GB` | 10.403 ± 0.020 | 10.379 | 10.444 | 1.01 ± 0.00 |
| `openssl dgst -sha3-256 4GB` | 10.680 ± 0.062 | 10.639 | 10.851 | 1.03 ± 0.01 |
| `sha3sum -a 256 4GB` | 17.104 ± 0.159 | 17.003 | 17.410 | 1.65 ± 0.02 |
| `rhash --sha3-256 4GB` | 12.945 ± 0.024 | 12.917 | 12.996 | 1.25 ± 0.00 |

### sha-3-384

| Command | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `./sha3 384 4GB` | 13.404 ± 0.013 | 13.384 | 13.423 | 1.02 ± 0.01 |
| `./chunked_sha3_384 4GB` | 13.447 ± 0.031 | 13.412 | 13.503 | 1.02 ± 0.01 |
| `openssl dgst -sha3-384 4GB` | 13.120 ± 0.115 | 13.054 | 13.349 | 1.00 |
| `sha3sum -a 384 4GB` | 21.642 ± 0.363 | 21.433 | 22.497 | 1.65 ± 0.03 |
| `rhash --sha3-384 4GB` | 16.714 ± 0.027 | 16.684 | 16.764 | 1.27 ± 0.01 |

### sha-3-512

| Command | Mean [s] | Min [s] | Max [s] | Relative |
|:---|---:|---:|---:|---:|
| `./sha3 512 4GB` | 19.177 ± 0.026 | 19.150 | 19.229 | 1.04 ± 0.01 |
| `./chunked_sha3_512 4GB` | 19.220 ± 0.030 | 19.178 | 19.268 | 1.04 ± 0.01 |
| `openssl dgst -sha3-512 4GB` | 18.514 ± 0.106 | 18.439 | 18.807 | 1.00 |
| `sha3sum -a 512 4GB` | 29.958 ± 0.041 | 29.900 | 30.044 | 1.62 ± 0.01 |
| `rhash --sha3-512 4GB` | 23.812 ± 0.026 | 23.773 | 23.851 | 1.29 ± 0.01 |


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
