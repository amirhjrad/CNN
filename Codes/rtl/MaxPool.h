#ifndef __MAXPOOL_H__
#define __MAXPOOL_H__
#include "systemc.h"

SC_MODULE(MaxPool){
    sc_in<sc_lv<8> > A1, A2, A3, A4;
    sc_out<sc_lv<8> > Y;

    SC_CTOR(MaxPool){
        SC_METHOD(evl);
        sensitive << A1 << A2 << A3 << A4;
    }

    void evl(){
        if ( (A1.read().to_uint() >= A2.read().to_uint()) && 
             (A1.read().to_uint() >= A3.read().to_uint()) &&
             (A1.read().to_uint() >= A4.read().to_uint()) )
            Y = A1;
        else if ( (A2.read().to_uint() >= A1.read().to_uint()) && 
                  (A2.read().to_uint() >= A3.read().to_uint()) &&
                  (A2.read().to_uint() >= A4.read().to_uint()) )
            Y = A2;
        else if ( (A3.read().to_uint() >= A1.read().to_uint()) && 
                  (A3.read().to_uint() >= A2.read().to_uint()) &&
                  (A3.read().to_uint() >= A4.read().to_uint()) )
            Y = A3;
        else if ( (A4.read().to_uint() >= A1.read().to_uint()) && 
                  (A4.read().to_uint() >= A3.read().to_uint()) &&
                  (A4.read().to_uint() >= A2.read().to_uint()) )
            Y = A4;
    }
};



SC_MODULE(MaxPool_TB) {
    sc_signal<sc_lv<8>> A1, A2, A3, A4;
    sc_signal<sc_lv<8>> Y;

    MaxPool *UUT;

    SC_CTOR(MaxPool_TB) {
        UUT = new MaxPool("ReLU_INS");
        UUT->A1(A1);
        UUT->A2(A2);
        UUT->A3(A3);
        UUT->A4(A4);
        UUT->Y(Y);


        SC_THREAD(inputting);
    }

    void inputting() {
        A1 = 3;
        A2 = 10;
        A3 = 2;
        A4 = 1;
    }
};


#endif