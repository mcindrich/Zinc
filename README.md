# Zinc
Programming language, written in C++.

## Compilation

```sh
git clone https://github.com/mcindrich/zinc --recursive
cd zinc
mkdir build && cd build && cmake .. && make -j$(nproc)
```

## Usage
```
Usage: zinc [options] fname 

Positional arguments:
fname        	file name of a program to run

Optional arguments:
-h --help    	shows help message and exits
-v --version 	prints version information and exits
```

## License
[MIT](https://choosealicense.com/licenses/mit/)