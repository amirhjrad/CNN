#include "TestBench.h"
#include "Convolution.h"

int sc_main(int argc, char** argv) {
    TestBench test("test");
    sc_trace_file *VCDFile;
    VCDFile = sc_create_vcd_trace_file("VCD");
    sc_trace(VCDFile, test.clk,"clk");
    sc_trace(VCDFile, test.start,"start");
    sc_trace(VCDFile, test.done,"done");
    sc_trace(VCDFile, test.UUT->pattern,"pattern");

    sc_start(500,SC_NS);
    return 0 ;
}