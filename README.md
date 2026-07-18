# DictCPP - A C++ Dictionary

[![C++][cpp-badge]][cpp]
[![GitHub][github-badge]][github]
[![Cmake][cmake-badge]][cmake]
[![GitHub Actions][github-actions-badge]][github-actions]
[![CMake on Ubuntu][cmake-ubuntu-badge]][cmake-ubuntu]
[![CMake on Windows][cmake-windows-badge]][cmake-windows]
[![Coverage Upload][coverage-upload-badge]][coverage-upload]
[![Read the Docs][rtd-badge]][rtd]
[![Documentation][doc-badge]][docs]
[![CodeCov][codecov-badge]][codecov]
[![Coverage][coverage-badge]][coverage]
[![License][license-badge]][license]
[![BuyMeACoffee][buymeacoffee-badge]][buymeacoffee]
[![No AI][noai-badge]](#)

This is a header-only C++ template library implementation of a Python dictionary.
In particular the ordering of elements within a Python dictionary is determined by the order they are added.
The aim of this project is to provide a self-contained structure which provides similar methods to a Python dictionary in C++.

## Usage

A `Dict<Key, Value>` is a template class with `Key` and `Value` the types of keys and values respectively.

```cpp
#include "dictcpp.hpp"
#include "tests/catch.hpp"

auto make_dictionary() {
    auto dict = Dict<char, int>();

    dict['a'] = 20;
    dict['b'] = 100;
    dict['c'] = 500;

    return dict;
}
```

Dictionaries can also be initialised using initialiser list:

```cpp
auto initialise() {
    const auto dict = Dict<char, int>{
        {'a', 1},
        {'c', 2},
        {'e', 3}
    };

    return dict;
}
```

Elements can be accessed using:

```cpp
void each_item() {
    const auto dict = Dict<char, int>{
            {'a', 1},
            {'c', 2},
            {'e', 3},
            {'a', 9}
    };
    
    for (const &[key, value]: dict.items()) {
        assert(dict.at(key) == value);
    }
}

std::vector<char> keys() {
    const auto dict = Dict<char, int>{
            {'a', 1},
            {'c', 2},
            {'e', 3},
            {'a', 9}
    };

    return dict.keys();
}

std::vector<char> values() {
    const auto dict = Dict<char, int>{
            {'a', 1},
            {'c', 2},
            {'e', 3},
            {'a', 9}
    };

    return dict.values();
}
```

For further information see the library [documentation][docs].

<!-- Badges -->

[cpp-badge]: https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white
[github-badge]: https://img.shields.io/badge/github-%23121011.svg?style=for-the-badge&logo=github&logoColor=white
[cmake-badge]: https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white
[github-actions-badge]: https://img.shields.io/badge/github%20actions-%232671E5.svg?style=for-the-badge&logo=githubactions&logoColor=white
[cmake-ubuntu-badge]: https://img.shields.io/github/actions/workflow/status/zwill22/DictCPP/cmake_ubuntu.yml?style=for-the-badge&logo=github&label=CMake%20on%20Ubuntu
[cmake-windows-badge]: https://img.shields.io/github/actions/workflow/status/zwill22/DictCPP/cmake_windows.yml?style=for-the-badge&logo=github&label=CMake%20on%20Windows
[coverage-upload-badge]: https://img.shields.io/github/actions/workflow/status/zwill22/DictCPP/coverage.yml?style=for-the-badge&logo=github&label=Coverage%20Upload
[codecov-badge]: https://img.shields.io/badge/Codecov-F01F7A?logo=codecov&logoColor=fff&style=for-the-badge
[coverage-badge]: https://img.shields.io/codecov/c/github/zwill22/dictcpp?style=for-the-badge&logo=codecov
[rtd-badge]: https://img.shields.io/badge/Read%20the%20Docs-%23000000?style=for-the-badge&logo=readthedocs&logoColor=white
[doc-badge]: https://img.shields.io/readthedocs/dictcpp?style=for-the-badge&logo=readthedocs
[buymeacoffee-badge]: https://img.shields.io/badge/Buy%20Me%20a%20Coffee-ffdd00?style=for-the-badge&logo=buy-me-a-coffee&logoColor=black
[license-badge]: https://img.shields.io/github/license/zwill22/dictcpp?style=for-the-badge
[noai-badge]: https://custom-icon-badges.demolab.com/badge/No%20AI-2f2f2f?logo=non-ai&logoColor=white&style=for-the-badge

<!-- Links -->

[cpp]: https://isocpp.org/
[github]: https://github.com/zwill22/DictCPP
[cmake]: https://cmake.org/
[github-actions]: https://github.com/zwill22/DictCPP/actions
[cmake-ubuntu]: https://github.com/zwill22/dictcpp/actions/workflows/cmake_ubuntu.yml
[cmake-windows]: https://github.com/zwill22/dictcpp/actions/workflows/cmake_windows.yml
[coverage-upload]: https://github.com/zwill22/dictcpp/actions/workflows/coverage.yml
[rtd]: https://about.readthedocs.com/
[buymeacoffee]: https://coff.ee/zmwill
[license]: https://github.com/zwill22/dictcpp/blob/main/LICENSE
[codecov]: https://about.codecov.io/
[coverage]: https://codecov.io/gh/zwill22/dictcpp
[docs]: https://dictcpp.readthedocs.io/en/latest/?badge=latest
