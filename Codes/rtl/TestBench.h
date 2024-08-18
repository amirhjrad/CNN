#ifndef __TESTBENCH_H__
#define __TESTBENCH_H__

#include "PatternFinder.h"

SC_MODULE(TestBench){
    sc_signal<sc_logic> rst, clk, start;
    sc_signal<sc_lv<8>> bias1;
    sc_signal<sc_lv<8>> bias2;
    sc_signal<sc_lv<8>> bias3;
    sc_signal<sc_lv<8>> kernel1[9];
    sc_signal<sc_lv<8>> kernel2[9];
    sc_signal<sc_lv<8>> kernel3[9];
    sc_signal<sc_logic> done;
    sc_signal<sc_lv<3>> pattern;

    PatternFinder* UUT;

    SC_CTOR(TestBench){
        UUT = new PatternFinder("PatternFinder_Ins");
            UUT->clk(clk);
            UUT->rst(rst);
            UUT->start(start);
            UUT->bias1(bias1);
            UUT->bias2(bias2);
            UUT->bias3(bias3);
            UUT->done(done);
            UUT->pattern(pattern);
            for (int i = 0; i < 9; i++){
                UUT->kernel1[i](kernel1[i]);
                UUT->kernel2[i](kernel2[i]);
                UUT->kernel3[i](kernel3[i]);
            }

            SC_THREAD(clocking);
            SC_THREAD(rstting);
            SC_THREAD(init_convs);
            SC_THREAD(inputting);
    }

    void clocking() {
        while (true)
        {
            clk = sc_logic_0;
            wait(3,SC_NS);
            clk = sc_logic_1;
            wait(3,SC_NS);
        }
        
    }

    void rstting() {
            rst = sc_logic_0;
            wait(5,SC_NS);
            rst = sc_logic_1;
            wait(5,SC_NS);   
            rst = sc_logic_0;
            wait(5,SC_NS);        
    }

    void init_convs() {
        bias1 = -1;
        kernel1[0] = 0;
        kernel1[1] = 1;
        kernel1[2] = 0;
        kernel1[3] = 1;
        kernel1[4] = 1;
        kernel1[5] = 1;
        kernel1[6] = 0;
        kernel1[7] = 1;
        kernel1[8] = 0;

        bias2 = -2;
        kernel2[0] = 1;
        kernel2[1] = 1;
        kernel2[2] = 1;
        kernel2[3] = 1;
        kernel2[4] = 0;
        kernel2[5] = 0;
        kernel2[6] = 1;
        kernel2[7] = 1;
        kernel2[8] = 1;

        bias3 = -2;
        kernel3[0] = 1;
        kernel3[1] = 1;
        kernel3[2] = 1;
        kernel3[3] = 0;
        kernel3[4] = 1;
        kernel3[5] = 0;
        kernel3[6] = 0;
        kernel3[7] = 1;
        kernel3[8] = 0;
    }

    void inputting() {
        start = sc_logic_0;
        wait(20,SC_NS);
        start = sc_logic_1;
        wait (30, SC_NS);
        start = sc_logic_0;
    }
};

#endif