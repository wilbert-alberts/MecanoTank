#!/usr/bin/bash

openocd -f interface/cmsis-dap-muse.cfg -f target/rp2040.cfg -c "adapter speed 950" -c "program build/mecanumtank.elf; reset halt; rp2040.core1 arp_reset assert 0 ; rp2040.core0 arp_reset assert 0 exit"
