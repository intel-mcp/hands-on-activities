# Hands-on “Working with Intel Xeon and Intel Xeon Phi Architecture”

## Remote access to the training platform

This document assumes that the testing platform has been setup and is ready to
use. We will be using a state-of-the-art server with Intel Xeon processors and
Intel Xeon Phi coprocessors  as well as several Intel software development
tools. 

To simplify nomenclature, we will refer to the testing platform as _the host_
(or _the host system_), and the Xeon Phi coprocessors installed in the host
system as _mic0_, _mic1_, and so forth.  Participants should work alone or
in pairs on a workstation - preferably running Linux or Mac - with Internet
access.  All the exercises are command-line based and should be executed on the
host system by means of a secure shell (SSH) connection.  Ideally the
participant workstation should be able to run X11.

Use the syntax below to log in to the host system:

```bash
ssh -X mcp-server -l traineeN
```

The `-X` toggle enables the _X forwarding_ mechanism. That enables the user to
open X applications at their local machine. The traineeN is the credential given
to you by the instructor.

It is important to check if the Xeon Phi coprocessors are up and running. In
order to do so, one must perform the following command:

```bash
micctrl --status
```

The previous command shows the status of all MIC cards installed on the host
system. ```status = ‘online’``` means that the mics are functional and can be
used to go on with the hands-on activities.


