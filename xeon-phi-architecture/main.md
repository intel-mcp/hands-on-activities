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

1. Run it using the `micnativeloadex` tool:  

```bash
micnativeloadex hello-world.mic
```

2. or alternatively you can perform a secure copy to the Intel Xeon Phi filesystem
and execute it locally. For instance if you are willing to run the example at
the _mic0_ board, perform the following sequence of commands:

```bash
scp hello-world.mic mic0:~/
ssh mic0
./hello-world.mic
```



