# Treap Tester

## Introduction

* Project 1 for [COMP90077](https://handbook.unimelb.edu.au/2020/subjects/comp90077) (Advanced Algorithms and Data Structures) at the University of Melbourne, 2020 Sem1.

* Performance analysis (experimental study) about the [Treap](https://en.wikipedia.org/wiki/Treap) data structure, including:

1. A data generator, which generate each data element in the form of a pair (id, key), where key is a integer drawn from 1 to 10^7

2. A randomized treap and a simple competitor (dynamic array), support insert, delete and search operations

3. Different experiments:

    a. Time v.s. Number of Insertions (only allow insertion, length ranged from 0.1M to 1M)
    
    b. Time v.s. Deletion Percentage (fixed length of 1M, only allow insertion and deletion, with deletion percentage ranged from 0.1% to 10%)
    
    c. Time v.s. Search Percentage (fixed length of 1M, only allow insertion and search, with search percentage ranged from 0.1% to 10%)
    
    d. Time v.s. Length of Mixed Operation Sequence (allow all operations, with fixed deletion and search percentage as 5%, length ranged from 0.1M to 1M)

* For detailed description please check out [project specification](docs/specification.pdf) and [final report](docs/report.pdf)

## Contribution
Xiuge Chen

xiugec@student.unimelb.edu.au

Subject: COMP90077 Advanced Algorithms and Data Structures

University of Melbourne