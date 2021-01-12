<h1 align="center">
  <br>
  <a href="#"><img src="https://i.ibb.co/0qFhJ3j/4b907629-0d89-41f5-be73-9b17969abfaa-200x200.png" alt="DDAliasAnalysis" width="200"></a>
  <br>
  DD - Alias Analysis
  <br>
</h1>

<h4 align="center">Basic Demand Driven Alias Analysis implementation</h4>


## Table of Contents

- [Getting Started](#getting-started)
  - [Building from source](#build-from-source)
- [Usage](#usage)

## Getting Started

Basic implementation of demand driven alias analysis in LLVM.   
[x] Uses simple demand generation technique   
[x] The driver gets activated on virtual function call sites   

### Building from source
```sh
$ git clone this_repository.git
$ cd this_repository
$ mkdir build; cd build
$ cmake .. && make
```

## Usage
Use ```DDAADriver``` to run the analysis on any LLVM IR file.    
Example: ```DDAADriver test.ll```    
