#include "testBench.h"

int sc_main(int agrc, char **argv) {
    TestBench TB("TB_INST");
    sc_trace_file *VCDFile;
    VCDFile = sc_create_vcd_trace_file("VCD");
    sc_trace(VCDFile, TB.clk, "clk");
    // sc_trace(VCDFile, TB.rst, "rst");
    sc_trace(VCDFile, TB.start, "start");
    sc_trace(VCDFile, TB.done, "done");
    sc_trace(VCDFile, TB.Result, "Result");
    sc_start(1000, SC_NS);
    return 0;
}