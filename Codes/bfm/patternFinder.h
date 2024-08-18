#ifndef __PATTERNFINDER_H__
#define __PATTERNFINDER_H__
#include "systemc.h"

SC_MODULE(PatternFinder) {
    sc_in<sc_logic> clk;
    sc_in<sc_lv<8> > Img_RAM[16];
    sc_in<sc_logic> start;
    sc_out<sc_logic> done;
    sc_out<sc_lv<3> > Result;

    sc_int<8> kernel1[9] = {0,1,0, 1,1,1, 0,1,0};
    sc_int<8> kernel2[9] = {1,1,1, 1,0,0, 1,1,1};
    sc_int<8> kernel3[9] = {1,1,1, 0,1,0, 0,1,0};
    sc_int<8> bias1 = -1;
    sc_int<8> bias2 = -2;
    sc_int<8> bias3 = -2;

    sc_int<8> conv1_out[4] = {bias1, bias1, bias1, bias1};
    sc_int<8> conv2_out[4] = {bias2, bias2, bias2, bias2};
    sc_int<8> conv3_out[4] = {bias3, bias3, bias3, bias3};

    sc_int<8> maxPool1_out;
    sc_int<8> maxPool2_out;
    sc_int<8> maxPool3_out;

    SC_CTOR(PatternFinder) {
        SC_THREAD(evl);
        sensitive << clk;
    }

    void evl() {
        while (true)
        {
            if (clk == sc_logic_1 && clk.posedge()){
                if (start == sc_logic_1) {
                    // Convolutions
                    for (int i = 0; i < 9; i++) {
                        conv1_out[0] += kernel1[i] * Img_RAM[i + int(i/3)].read().to_int();
                        conv2_out[0] += kernel2[i] * Img_RAM[i + int(i/3)].read().to_int();
                        conv3_out[0] += kernel3[i] * Img_RAM[i + int(i/3)].read().to_int();
                    }
                    for (int i = 0; i < 9; i++) {
                        conv1_out[1] += kernel1[i] * Img_RAM[i + int(i/3) + 1].read().to_int();
                        conv2_out[1] += kernel2[i] * Img_RAM[i + int(i/3) + 1].read().to_int();
                        conv3_out[1] += kernel3[i] * Img_RAM[i + int(i/3) + 1].read().to_int();
                    }
                    for (int i = 0; i < 9; i++) {
                        conv1_out[2] += kernel1[i] * Img_RAM[i + int(i/3) + 4].read().to_int();
                        conv2_out[2] += kernel2[i] * Img_RAM[i + int(i/3) + 4].read().to_int();
                        conv3_out[2] += kernel3[i] * Img_RAM[i + int(i/3) + 4].read().to_int();
                    }
                    for (int i = 0; i < 9; i++) {
                        conv1_out[3] += kernel1[i] * Img_RAM[i + int(i/3) + 5].read().to_int();
                        conv2_out[3] += kernel2[i] * Img_RAM[i + int(i/3) + 5].read().to_int();
                        conv3_out[3] += kernel3[i] * Img_RAM[i + int(i/3) + 5].read().to_int();
                    }
                    cout << conv3_out[0] << endl;
                    cout << conv3_out[1] << endl;
                    cout << conv3_out[2] << endl;
                    cout << conv3_out[3] << endl;

                    for (int i = 0; i < 9; i++)
                        wait(clk.posedge_event());
                    
                    // ReLU
                    for (int i = 0; i < 4; i++) {
                        if (conv1_out[i] < 0)
                            conv1_out[i] = 0;
                        if (conv2_out[i] < 0)
                            conv2_out[i] = 0;
                        if (conv3_out[i] < 0)
                            conv3_out[i] = 0;
                    }
                    // MaxPool
                    maxPool1_out = conv1_out[0];
                    maxPool2_out = conv2_out[0];
                    maxPool3_out = conv3_out[0];
                    for (int i = 1; i < 4; i++) {
                        if (conv1_out[i] > maxPool1_out)
                            maxPool1_out = conv1_out[i];
                        if (conv2_out[i] > maxPool2_out)
                            maxPool2_out = conv2_out[i];
                        if (conv3_out[i] > maxPool3_out)
                            maxPool3_out = conv3_out[i];
                    }
                    // Result
                    if ((maxPool1_out >= maxPool2_out) && (maxPool1_out >= maxPool3_out)) {
                        Result = "001";
                        done = sc_logic_1;
                    }
                    if ((maxPool2_out >= maxPool1_out) && (maxPool2_out >= maxPool3_out)) {
                        Result = "010";
                        done = sc_logic_1;
                    }
                    if ((maxPool3_out >= maxPool2_out) && (maxPool3_out >= maxPool1_out)) {
                        Result = "100";
                        done = sc_logic_1;
                    }
                }
            }
            wait();
        }
    }
};

#endif