# The Algorithms in C++

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/761ad7446aa5491e95ce143758656c04)](https://www.codacy.com/app/VladimirBalun/Algorithms?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=VladimirBalun/Algorithms&amp;utm_campaign=Badge_Grade)
[![Build status](https://ci.appveyor.com/api/projects/status/oc3xgrjv0loxl26d?svg=true)](https://ci.appveyor.com/project/VladimirBalun/algorithms)
[![Build Status](https://travis-ci.org/VladimirBalun/Algorithms.svg?branch=master)](https://travis-ci.org/VladimirBalun/Algorithms)

These algorithms are the demonstration purposes only. There are
many algorithms implementations in the C++ standard
library that are much better for performance reasons. This
project contains the following algorithms...

## Allocators

| Name allocator                           | Allocation | Free |
|:----------------------------------------:|:----------:|:----:|
| Linear allocator                         | O(1)       | -    |
| Pool allocator                           | O(1)       | O(1) |

## Caching

| Name algorithm                           |
|:----------------------------------------:|
| First in, first out (FIFO)               |
| Last recently used (LRU)                 |

## Cryptography

| Name algorithm                           |
|:----------------------------------------:|
| Caesar cipher                            |

## Data structures

| Name structure     | Indexation  | Search         | Inserting    | Deleting    | Memory |
|:------------------:|:-----------:|:--------------:|:------------:|:-----------:|:------:|
| Binary Heap        | -           | -              | O(log(n))    | O(log(n))   | O(n)   |
| Binary Tree | O(log(n))   | O(log(n))      | O(log(n))    | O(log(n))   | O(n)   |
| LinkedList         | O(n)        | O(n)           | O(1)         | O(1)        | O(n)   |
| Queue              | -           | -              | O(1)         | O(1)        | O(n)   |
| Stack              | -           | -              | O(1)         | O(1)        | O(n)   |

## Multithreading

| Name algorithm                           |
|:----------------------------------------:|
| Producer and consumer                    |

## Search

| Name algorithm    | Data Structure | Average result | Worse result |
|:-----------------:|:--------------:|:--------------:|:------------:|
| Binary search     | Sorted array   | O(log(n))      | O(log(n))    |
| Linear search     | Array          | O(n)           | O(n)         |


## SmartPointers

| Name pointer                             |
|:----------------------------------------:|
| Auto smart pointer                       |
| Unique smart pointer                     |
| Shared smart pointer                     |

## Sorting

| Name algorithm    |Data Structure | Best result | Average result | Worse result |
|:-----------------:|:-------------:|:-----------:|:--------------:|:------------:|
| Bubble sorting    |  Array        | O(n)        | O(n^2)         | O(n^2)       |
| Insertion sorting |  Array        | O(n^2)      | O(n^2)         | O(n^2)       |
| Quick sorting     |  Array        | O(log(n))   | O(log(n))      | O(n^2)       |
| Selection sorting |  Array        | O(n)        | O(n^2)         | O(n^2)       |
| Shell sorting     |  Array        | O(n^2)      | O(n^2)         | O(n^2)       |
| Stupid sorting    |  Array        | O(n)        | O(n^3)         | O(n^3)       |

---

Other algorithms will be added later. Please follow the news.
