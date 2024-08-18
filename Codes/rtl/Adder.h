#ifndef __ADDER_H__
#define __ADDER_H__

#include "systemc.h"

SC_MODULE(Adder) {
    sc_in<sc_lv<8>> A, B;
    sc_out<sc_lv<8>> Y;

    SC_CTOR(Adder) {
        SC_METHOD(evl);
        sensitive << A << B;
    }

    void evl() {
        Y = A.read().to_uint() + B.read().to_uint();
    }
};

SC_MODULE(Adder_TB){
    sc_signal<sc_lv<8>> A, B;
    sc_signal<sc_lv<8>> Y;

    Adder *UUT;

    SC_CTOR(Adder_TB) {
        UUT = new Adder("Adder_inst");
        UUT->A(A);
        UUT->B(B);
        UUT->Y(Y);

        SC_THREAD(inputting);
        // sensitive << A << B;
    }

    void inputting() {
        while (true)
        {
        A = 1;
        B = 4;
        wait(10,SC_NS);
        A = 6;
        B = 7;
        wait(10,SC_NS);
        }
    }
};

#endif