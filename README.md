# assessment-may24

## Build

Tested on Ubuntu 22.04 LTS.

Requirements: build-essential, gcc, cmake, libcurlpp-dev

```
mkdir build
cd build
cmake ..
```

Executables are in `build/part1` and `build/part2`.

## Run

### Part 1

Unit tests

```
./build/part1/testpart1
```

Demo app

```
./build/part1/part1 part1/resource/98-0.txt 
```

## Debug (Visual Studio Code)

### launch.json 

```
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "test part1",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/part1/testpart1",
            "args": [
            ],
            "environment": [
                {
                    "name": "config",
                    "value": "Debug"
                }
            ],
            "cwd": "${workspaceFolder}"
        },
        {
            "name": "app part1",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/build/part1/part1",
            "args": [
                "part1/resource/98-0.txt"
            ],
            "environment": [
                {
                    "name": "config",
                    "value": "Debug"
                }
            ],
            "cwd": "${workspaceFolder}"
        }
    ]
}
```