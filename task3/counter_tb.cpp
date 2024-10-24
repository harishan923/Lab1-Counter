#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"


int main(int argc, char **argv, char **env) {
    int i;
    int clk;
    int j = 0;

    Verilated::commandArgs(argc, argv);

    // init top verilog instance
    Vcounter* top = new Vcounter;

    // init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");

    //init Vbuddy
    if (vbdOpen()!=1) return(-1);
    vbdHeader("Lab1: Counter");

    // initialize simulation inputs
    top->clk = 1;
    top->rst = 0;
    top->en = 0;

    // run simulation for many clock cycles
    for (i=0; i<1000; i++) {

        // dump variables into VCD file and toggle clock
        for (clk=0; clk<2; clk++) {
            tfp->dump(2*i+clk);  // unit is in ps!!!
            top->clk = !top->clk;
            top->eval();
            /*
            if (top->count == 9 && j != 3){
                j++;
                top->count -= 1;
                break;
            }
            */
        }

        // ++++ send count to vbud
        vbdPlot(int(top->count), 0, 1023);
        //vbdHex(4, (int(top->count) >> 16) & 0xF);
        //vbdHex(3, (int(top->count) >> 8) & 0xF);
        //vbdHex(2, (int(top->count) >> 4) & 0xF);
        //vbdHex(1, int(top->count) & 0xF);
        vbdCycle(i+1);
        // ---- end of vbud out

        //change rst and en signals during simulation
        top->rst = (i < 2) | (i == 15);
        top->en = vbdFlag();

        //wait 3 cycles after 0x09 reached on counter
        //top->rst = 0;
        //top->en = (i > 4);

        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose(); // ++++
    tfp->close();
    exit(0);
}
