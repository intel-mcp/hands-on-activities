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


