#ifndef __MULTIPLIER_H__
#define __MULTIPLIER_H__

#include "systemc.h"

SC_MODULE(Multiplier) {
    sc_in<sc_lv<8>> A, B;
    sc_out<sc_lv<8>> Y;

    SC_CTOR(Multiplier) {
        SC_METHOD(evl);
        sensitive << A << B;
    }

    void evl() {
        int a = A.read().to_uint();
        int b = B.read().to_uint();
        Y = a * b;
    }
};



SC_MODULE(Multiplier_TB) {
    sc_signal<sc_lv<8>> A, B;
    sc_signal<sc_lv<8>> Y;

    Multiplier * UUT;

    SC_CTOR(Multiplier_TB) {
        UUT = new Multiplier("mull_inst");
        UUT->A(A);
        UUT->B(B);
        UUT->Y(Y);
        

        SC_THREAD(inputting);
    }

    void inputting() {
        while (true)
        {
            A = 2;
            B = 3;
            wait(10,SC_NS);
            A = 5;
            B = 2;
            wait(10,SC_NS);
            A = 4;
            B = 3;
            wait(10,SC_NS);
        }
        
    }
};

#endif