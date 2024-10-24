#!/bin/sh

# cleanup
rm -rf obj_dir
rm -f counter.vcd

# run Verilator to translate Verilog into Cpp including test bench
verilator -Wall --cc --trace counter.sv --exe counter_tb.cpp

# build Cpp proj via make autogen'd by verilator
#multithreading disabled

make -C obj_dir/ -f Vcounter.mk Vcounter

# run executable sim file
obj_dir/Vcounter