#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "systemc.h"

SC_MODULE(Controller){
    sc_in<sc_logic> clk, rst, start, co, conv_done_sig;
    sc_out<sc_logic> ld1, clr2, cnt1, cnt2, start_conv, write, done;
    sc_out<sc_lv<2>> mode;

    sc_signal<int> ps, ns;

    SC_CTOR(Controller) {
        SC_METHOD(comb);
        sensitive << ps << start << co << conv_done_sig;
        SC_THREAD(seq);
        sensitive << clk << rst;
    }

    void comb() {
        cnt1 = sc_logic_0;
        cnt2 = sc_logic_0;
        ld1 = sc_logic_0;
        clr2 = sc_logic_0;
        start_conv = sc_logic_0;
        done = sc_logic_0;
        switch (ps)
        {
        case 0:
            if (start == sc_logic_0)
                ns = 0;
            else if (start == sc_logic_1)
                ns = 1;
            break;
        case 1:
            mode = "00";
            ld1 = sc_logic_1;
            clr2 = sc_logic_1;
            ns = 2;
            break;
        case 2: 
            cnt1 = sc_logic_1;
            cnt2 = sc_logic_1;
            if (co == sc_logic_1)
                ns = 3;
            else if (co == sc_logic_0)
                ns = 2;
            break;
        case 3:
            mode = "01";
            ld1 = sc_logic_1;
            ns = 4;
            break;
        case 4:
            cnt1 = sc_logic_1;
            cnt2 = sc_logic_1;
            if (co == sc_logic_1)
                ns = 5;
            else if (co == sc_logic_0)
                ns = 4;
            break;
        case 5:
            mode = "10";
            ld1 = sc_logic_1;
            ns = 6;
            break;
        case 6:
            cnt1 = sc_logic_1;
            cnt2 = sc_logic_1;
            if (co == sc_logic_1)
                ns = 7;
            else if (co == sc_logic_0)
                ns = 6;
            break;
        case 7:
            mode = "11";
            ld1 = sc_logic_1;
            ns = 8;
            break;
        case 8:
            cnt1 = sc_logic_1;
            cnt2 = sc_logic_1;
            if (co == sc_logic_1)
                ns = 9;
            else if (co == sc_logic_0)
                ns = 8;
            break;
        case 9:
            start_conv = sc_logic_1;
            if (conv_done_sig == sc_logic_1)
                ns = 10;
            else if (conv_done_sig == sc_logic_0)
                ns = 9;
                break;;
        case 10:
            done = sc_logic_1;
            ns = 0;
            break;
        default:
            cnt1 = sc_logic_0;
            cnt2 = sc_logic_0;
            ld1 = sc_logic_0;
            clr2 = sc_logic_0;
            start_conv = sc_logic_0;
            done = sc_logic_0;
            ns = 0;
            break;
        }
    }

    void seq() {
        while (true)
        {
            if (rst == sc_logic_1)
                ps = 0;
            else if (clk.posedge())
                ps = ns;
            wait();
        }
        
    }
};

#endif