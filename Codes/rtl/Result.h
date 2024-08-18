#ifndef __RESULT_H__
#define __RESULT_H__
#include "systemc.h"

SC_MODULE(Result){
    sc_in<sc_lv<8> > A, B, C;
    sc_out<sc_lv<3> > res;

    SC_CTOR(Result){
        SC_METHOD(evl);
        sensitive << A << B << C;
    }

    void evl() {
        sc_uint<8> max;
        if (A.read().to_uint() >= B.read().to_uint() && A.read().to_uint() >= C.read().to_uint()){
            max = A;
            res = "001";
            cout << "Pattern 1 Detected\n";
        }
        else if (B.read().to_uint() >= A.read().to_uint() && B.read().to_uint() >= C.read().to_uint()){
            max = B;
            res = "010";
            cout << "Pattern 2 Detected\n";
        }
        else if (C.read().to_uint() >= A.read().to_uint() && C.read().to_uint() >= B.read().to_uint()){
            max = C;
            res = "100";
            cout << "Pattern 3 Detected\n";
        }
        
    }
};

#endif