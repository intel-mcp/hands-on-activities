# Hands-on “Working with Intel Xeon and Intel Xeon Phi Architecture”

## Prerequisites
In order to go ahead with the training session we assume that you have a fully
working connection with the Manycore server. If not, please follow the
instructions [here](requirements/remote-access.md).

## Tasks

### Monitoring the Hardware with MPSS

Answer the following questions:

1. Discover if the _MPSS_ daemon is running.  

  You can query the system for information about running process with the
  `systemctl` command line tool.

2. How Many Intel Xeon Phi devices are deployed?  

  You can use the `micinfo` or the `mpssinfo` commands to discover informations
  about the devices:


3. What is the temperature of the Xeon Phi boards installed?  

  You can use the `micsmc` to retrieve information about the Intel Xeon Phi
  boards.

4. How many cores are there available at the Xeon Phi Processor?  
  
  The special file `/proc/cpuinfo` contains information about the installed
  processors.

5. How many threads can the processor execute in parallel?  

  The same file (`/proc/cpuinfo`) holds information about how many threads each
  core can execute in parallel.

6. How many cores are there at each Intel Xeon Phi board? How many threads can
each core execute?


### Compiling and Running for Intel Xeon and Intel Xeon Phi

[This code](src/hello-world.c) shows the amount of available threads
available.

#### Running on Intel Xeon (host)
In order to compile and run the code one must perform the commands:

```bash
icc hello-world.c -o hello-world
./hello-world
```

The `icc` command is the main C compiler provided by the Intel Parallel Studio.

#### Running on Intel Xeon Phi (mic)

Compile and run in Intel Xeon Phi using `micnativeloadex`:

```bash
icc hello-world.c -o hello-world.mic -mmic
```

The previous `icc` command execution generated a new binary file that can run on
the Intel Xeon Phi architecture. That same file is not compatible with the
**x86_64** architecture. If you try to run it you'll probably get the following
error:

```
-bash: ./hello-world.mic: impossible to execute binary file
```

You can run execute the generated binary file at the Intel Xeon Phi using one of
the following alternatives:

##### Run it using the `micnativeloadex` tool:  

```bash
micnativeloadex hello-world.mic
```

##### Run locally on Intel Xeon Phi

Alternatively you can perform a secure copy to the Intel Xeon Phi filesystem and
execute it locally. For instance if you are willing to run the example at the
_mic0_ board, perform the following sequence of commands:

```bash
scp hello-world.mic mic0:~/
ssh mic0
./hello-world.mic
```

Now that you performed your first program execution at the Intel Xeon Phi,
answer the question:

1. How Many threads are available at the Intel Xeon? And at the Intel Xeon Phi?


### Offloading

[This code](src/hello-world-offload.c) offloads part of program to the Intel
Xeon Phi.

In order to build the executable one should perform:

```bash
icc hello-world-offload.c -o hello-world-offload
./hello-world-offload
```

One should note that the binary is executed **at the host**. It is responsible
for copying the code that should be offloaded to the Intel Xeon Phi board and
executing it.

The directive `#pragma offload target(mic)` tells the host to delegate part of
its execution to the Intel Xeon Phi board (if any present). In case the host has
no board attached, the code is executed only at the host machine.

#### Offload with Data Transfer

[This code](src/hello-world-offload-data-transfer.c) shows how to implement a
function with data transfer to be executed on intel Xeon Phi.

```bash
icc hello-world-offload-data-transfer.c -o hello-world-offload-data-transfer
./hello-world-offload-data-transfer
```

One should note that the directive `__attribute__((target(mic)))` is responsible
for telling the compiler that the following function can be executed at the
Intel Xeon Phi if any available.

The following directive tells that the variables `a`, `b`, and `sum` should me
made available also at the coprocessor. 

```c
__declspec(target(mic))
double a, b, sum;
```


##### Offload Debugging

The Operating System reads the content of the variable `OFFLOAD_REPORT` in order
to establish how much debugging output should be generated while executing the
offload operation.

To discover how much data was transfered from the host to the mic and vice-versa
one should set the value of `OFFLOAD_REPORT` to **2**:

```bash
export OFFLOAD_REPORT=2
```

Then run the same code:

```bash
./hello-world-offload-data-transfer
```

After that one should be able to answer the following question:

1. How much data was trasfered from the host to the mic  and from the mic to the
host?

#### Access to Environment Variables while Offloading

[This code](src/hello-world-offload2.c) shows how to access environment
variables from within a C code. 

The code `hello-world-offload3.c` prints the value of the environment variable
`ENV_VAR`.

In order to test the code one should define the value of such variable:

```bash
export ENV_VAR=2
```

Then compile and execute the code:

```bash
icc hello-world-offload2.c -o hello-world-offload2
./hello-world-offload2
```

One can easily see that both mic and host share the same environment variable.
This can be the case in many applications, but sometimes it useful to make a
distinction of the variable content. We can do that defining a prefix to all
variables that will be made available to the mic operating system.

In order to define such prefix one has to define the `MIC_ENV_PREFIX` variable:

```bash
export MIC_ENV_PREFIX=PHI
```

Now the software being offloaded has a separate context from the software being
executed at the host. 

Lets check what would be the output of the variable if we define a separate
value for the mic:

```bash
export PHI_ENV_VAR=4
./hello-world-offload2
```

After that one should be able to answer the following questions:

1. Is it possible to define which mic will be used for the offload?

2. What happens if we don't define the `PHI_ENV_VAR`?
