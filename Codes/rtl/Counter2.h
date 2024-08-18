#ifndef __COUNTER2_H__
#define __COUNTER2_H__

#include "systemc.h"

SC_MODULE(Counter2) {
    sc_in<sc_logic> clk, rst, clr,cnt;
    sc_out<sc_lv<6>> out;

    SC_CTOR(Counter2) {
        SC_THREAD(evl);
        sensitive << rst << clk;
    }

    void evl() {
        while (true)
        {
            if (rst == sc_logic_1)
                out = "000000";
            if (clr == sc_logic_1)
                out = "000000";
            if (clk == SC_LOGIC_1 && clk.event()) {
                if (cnt == sc_logic_1)
                    out = out.read().to_uint() + 1;
            }
            wait();
        }
    }
        
};

SC_MODULE(Counter2_TB) {
    sc_signal<sc_logic> clk, rst, clr,cnt;
    sc_signal<sc_lv<6>> out;

    Counter2 *UUT;

    SC_CTOR(Counter2_TB){
        UUT = new Counter2("Counter2_ins");
        UUT->clk(clk);
        UUT->rst(rst);
        UUT->clr(clr);
        UUT->cnt(cnt);
        UUT->out(out);

        SC_THREAD(clocking);
        SC_THREAD(rstting);
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
        wait(3,SC_NS);
        rst = sc_logic_0;
    }

    void inputting() {
        cnt = sc_logic_0;
        clr = sc_logic_0;
        wait(13,SC_NS);
        cnt = sc_logic_1;
        wait(500,SC_NS);
        cnt = sc_logic_0;
        clr = sc_logic_1;
    }
};

#endif