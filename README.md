# assessment-may24

## Build

Tested on Ubuntu 22.04 LTS.

Requirements: build-essential, gcc, cmake, libcurlpp-dev

```
mkdir build
cd build
cmake ..
make
```

Executables are in `build/part1` and `build/part2`.

## Run

### Part 1

Demo app

```
./build/part1/part1 part1/resource/98-0.txt 
```

Unit tests

```
./build/part1/testpart1
```


### Part 2

Parser speed measure

```
$ ./part2/part2 ../part2/resource/binance.txt 
Parsed (500) trades in 2309µs
First trade --------------------
Aggregate Trade ID: 173264206
Price: 57475.1
Quantity: 0.017
First trade ID: 288456246
Last trade ID: 288456246
Timestamp: 1723827137604
Buyer was maker: 0

Last trade --------------------
Aggregate Trade ID: 173264705
Price: 57279.3
Quantity: 0.851
First trade ID: 288456807
Last trade ID: 288456807
Timestamp: 1723828061140
Buyer was maker: 1
```

`part2` without an argument queries the binance endpoint for BTCUSDT.

Unit tests

```
./build/part2/testpart2
```