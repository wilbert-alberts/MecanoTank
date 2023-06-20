#!/usr/bin/bash

openocd -f interface/cmsis-dap-muse.cfg -f target/rp2040.cfg -c "adapter speed 950" -c "init; reset; exit"
