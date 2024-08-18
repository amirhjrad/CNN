#ifndef __COUNTER1_H__
#define __COUNTER1_H__

#include "systemc.h"

SC_MODULE(Counter1) {
    sc_in<sc_logic> clk, rst, cnt, ld;
    sc_in<sc_lv<2> > mode;
    sc_out<sc_lv<4> > out;
    sc_out<sc_logic> co;

    SC_CTOR(Counter1) {
        SC_THREAD(evl);
        sensitive << clk.pos() << rst;
        SC_THREAD(assign);
        sensitive << clk.pos();
    }

    void evl() {
        while (true)
        {
            if (rst == sc_logic_1)
                out = "0000";
            if (ld ==sc_logic_1) {
                if (mode.read() == "00")
                    out = "0000";
                else if (mode.read() == "01")
                    out = "0001";
                else if (mode.read() == "10")
                    out = "0100";
                else if (mode.read() == "11")
                    out = "0101";
            }
            if (clk == sc_logic_1 && clk.event()) {
                if (cnt == sc_logic_1) {
                    if (mode.read() == "00") {
                        if (out.read().to_uint() + 1 == 3)
                            out = 4;
                        else if (out.read().to_uint() + 1 == 7)
                            out = 8;
                        else                         
                            out = out.read().to_uint() + 1;
                    }
                    else if (mode.read() == "01") {
                        if (out.read().to_uint() + 1 == 4)
                            out = 5;
                        else if (out.read().to_uint() + 1 == 8)
                            out = 9;
                        else out = out.read().to_uint() + 1;
                    }
                    else if (mode.read() == "10") {
                        if (out.read().to_uint() + 1 == 7)
                            out = 8;
                        else if (out.read().to_uint() + 1 == 11) 
                            out = 12;
                        else out = out.read().to_uint() + 1;
                    }
                    else if (mode.read() == "11") {
                        if (out.read().to_uint() + 1 == 8)
                            out = 9;
                        else if (out.read().to_uint() + 1 == 12)
                            out = 13;
                        else out = out.read().to_uint() + 1;
                    }
                }
                if (co == sc_logic_1 && mode.read() == "00")
                    out = "0001";
                else if (co == sc_logic_1 && mode.read() == "01")
                    out = "0100";
                else if (co == sc_logic_1 && mode.read() == "10")
                    out = "0101";
                // else if (co == sc_logic_1 && mode.read() == "11")
                //     out = "0000";
            }
            wait();
        }   
    }

    void assign() {
        while (true)
        {
            if (mode.read() == "00") {
                if (out.read() == 9) 
                    co = sc_logic_1;
                else 
                    co = sc_logic_0;
            }
            else if (mode.read() == "01") {
                if (out.read() == 10)
                    co = sc_logic_1;
                else 
                    co = sc_logic_0;
            }
            else if (mode.read() == "10") {
                if (out.read() == 13)
                    co = sc_logic_1;
                else 
                    co = sc_logic_0;
            }
            else if (mode.read() == "11") {
                if (out.read() == 13)
                    co = sc_logic_1;
                else 
                    co = sc_logic_0;
            }
            wait();
        }
    }
};



SC_MODULE(Counter1_TB) {
    sc_signal<sc_logic> clk, rst, cnt, ld;
    sc_signal<sc_lv<2> > mode;
    sc_signal<sc_lv<4> > out;
    sc_signal<sc_logic> co;

    Counter1* UUT;

    SC_CTOR(Counter1_TB) {
        UUT = new Counter1("Counter1_Ins");
        UUT->rst(rst);
        UUT->mode(mode);
        UUT->out(out);
        UUT->co(co);
        UUT->cnt(cnt);
        UUT->clk(clk);
        UUT->ld(ld);

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
        wait(7,SC_NS);
        rst = sc_logic_1;
        wait(7,SC_NS);
        rst = sc_logic_0;
    }

    void inputting() {
        mode = "00";
        ld = sc_logic_1;
        wait(10,SC_NS);
        ld = sc_logic_0;
        wait(10,SC_NS);
        cnt = sc_logic_1;
        wait(100,SC_NS);
        cnt = sc_logic_0;
        wait(20,SC_NS);
        mode = "01";
        ld = sc_logic_1;
        wait(10,SC_NS);
        ld = sc_logic_0;
        cnt = sc_logic_1;
        wait(100,SC_NS);
        cnt = sc_logic_0;
        wait(20,SC_NS);
        mode = "10";
        ld = sc_logic_1;
        wait(10,SC_NS);
        ld = sc_logic_0;
        cnt = sc_logic_1;
        wait(100,SC_NS);
        cnt = sc_logic_0;
        wait(20,SC_NS);
        mode = "11";
        ld = sc_logic_1;
        wait(10,SC_NS);
        ld = sc_logic_0;
        cnt = sc_logic_1;
        wait(100,SC_NS);
        cnt = sc_logic_0;
        wait(20,SC_NS);
    }
};

#endif