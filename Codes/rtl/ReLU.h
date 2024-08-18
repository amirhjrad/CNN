#ifndef __RELU_H__
#define __RELU_H__

#include "systemc.h"

SC_MODULE(ReLU) {
    sc_in<sc_lv<8>> A1, A2, A3, A4;
    sc_out<sc_lv<8>> Y1, Y2, Y3, Y4;

    SC_CTOR(ReLU) {
        SC_METHOD(evl);
        sensitive << A1 << A2 << A3 << A4;
    }  

    void evl() {
        if (A1.read().to_int() < 0)
            Y1 = 0;
        else Y1 = A1;
        if (A2.read().to_int() < 0)
            Y2 = 0;
        else Y2 = A2;
        if (A3.read().to_int() < 0)
            Y3 = 0;
        if (A4.read().to_int() < 0)
            Y4 = 0;
        else Y4 = A4;
    }
};


SC_MODULE(ReLU_TB) {
    sc_signal<sc_lv<8>> A1, A2, A3, A4;
    sc_signal<sc_lv<8>> Y1, Y2, Y3, Y4;

    ReLU *UUT;

    SC_CTOR(ReLU_TB) {
        UUT = new ReLU("ReLU_INS");
        UUT->A1(A1);
        UUT->A2(A2);
        UUT->A3(A3);
        UUT->A4(A4);
        UUT->Y1(Y1);
        UUT->Y2(Y2);
        UUT->Y3(Y3);
        UUT->Y4(Y4);

        SC_THREAD(inputting);
    }

    void inputting() {
        A1 = -3;
        A2 = 10;
        A3 = 2;
        A4 = -1;
    }
};


#endif