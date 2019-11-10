#!/bin/bash

make && make load && make unload && make clean && nano /var/log/kern.log

# <ctrl+end> to the end of the kern.log file
