# GO-Notes

## Chapter 1

### First Program, Hello World!

### Making a Go Module

```bash
$ mkdir ch1
$ cd ch1
```

Inside the directory, run the go mod init command to mark this directory as a Go module:

```bash
$ go mod init hello_world
go: creating new go.mod: module hello_world
```

### go Build

```Go
// ch1/hello.go
package main

import "fmt"

func main() {
fmt.Println("Hello, world!")
}
```

```bash
$ go build
$ ./hello_world
Hello, world!
```
Use -o argument for giving the file different name.(same as gcc/g++).
```bash
$ go build -o hello
```

### go fmt

The Go development tools include a command, go fmt, which automatically fixes the whitespace in your code to match the standard format. However, it can’t fix braces on the wrong line. Run it with the following:

```bash
$ go fmt ./...
hello.go
```
Using ./... tells a Go tool to apply the command to all the files in the current directory and all subdirectorie.

If you open up hello.go, you’ll see that the line with fmt.Println is now properly indented with a single tab.

### go vet

Change the fmt.Println line in hello.go to the following:
```go
// ch1/hello.go
fmt.Printf("Hello, %s!\n")
```

```bash
$ go vet ./...
# hello_world
# [hello_world]
./hello.go:6:2: fmt.Println call has possible Printf formatting directive %s
./hello.go:6:2: fmt.Println arg list ends with redundant newline
```
Correct
```go
// ch1/hello.go
fmt.printf("Hello, %s\n", "world!")
```

### Makefile

```Makefile
# ch1/Makefile
.DEFAULT_GOAL := build

.PHONY: fmt vet build
fmt:
		go fmt ./...

vet: fmt
		go vet ./...

build: vet
		go build
```

Run make and you should see the following output:
```bash
$ make
go fmt ./...
go vet ./...
go build”
```
>**NOTE:** Not supported make in windows, external download make >using chocolatey.

## Chapter 2: Predeclared Types and Declarations

### Predeclared Types

>**NOTE:** Go, like most modern languages, assigns a default zero value to any variable that is declared but not assigned a value.

* Literals
* Booleans : true, false
* Numeric Types
    - Integer types: 
        * int8, int16, int32, int64
        * uint8, uint16, uint32, uint64
    - Special Integer types
    - Integer Operator:
        * +, -, *, /, %
        * +=, -=, *=, /=, and %=
        * ==, !=, >, >=, <, and <=
        * Go has bit-manipulation operators for integers. You can bit shift left and right with << and >>, or do bit masks with & (bitwise AND), | (bitwise OR), ^ (bitwise XOR), and &^ (bitwise AND NOT).
    - Floating point types
    - Complex types (Not used by us)

### Type conversion

```go
var y float64 = 30.2
var sum1 float64 = float64(x) + y
var sum2 int = x + int(y)
fmt.Println(sum1, sum2)
```