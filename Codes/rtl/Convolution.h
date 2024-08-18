#ifndef __convolution_H_
#define __convolution_H_

#include "systemc.h"
#include "Adder.h"
#include "Multiplier.h"

SC_MODULE(Convolution) {
    sc_in<sc_logic> clk, start_conv;
    sc_in<sc_lv<8>> img_element;
    sc_in<sc_lv<6>> kernel_index;
    sc_in<sc_lv<8>> bias;
    sc_in<sc_lv<8>> kernel[9];
    sc_out<sc_logic> conv_done;
    sc_out<sc_lv<8>> out[4];

    sc_signal<sc_lv<8>> img[36];

    Adder* Adder_;
    Multiplier* Multiplier_;


    SC_CTOR(Convolution) {


        // Multiplier_ = new Multiplier("Multiplier_inst");
            // Multiplier_->A(kernel[kernel_index.read().to_uint()]);
            // Multiplier_->B(img_element);
            // Multiplier_->Y(mult_out);
        // Adder_ = new Adder("Adder_ins");
            // Adder_->A(mult_out);
            // Adder_->B(adder_out);
            // Adder_->Y(adder_out);

        SC_THREAD(genInnerImg);
        SC_THREAD(evl)
        sensitive << clk.pos();
    } 

    void genInnerImg() {
        while (true)
        {
            unsigned int index = kernel_index.read().to_uint();
            if (index < 36) {
                img[index] = img_element;
            }
            wait(1,SC_NS);
        }
    }

    void evl() {
        while (true)
        {
            if (clk == sc_logic_1 && clk.event()) {
                conv_done = sc_logic_0;
                if (start_conv == sc_logic_1) {
                    int tmp;
                    tmp = 0;
                    for(int i = 0; i < 9; i++)
                        tmp += img[i].read().to_uint() * kernel[i%9].read().to_uint();
                    out[0] = tmp + bias.read().to_uint();
                    tmp = 0;
                    for(int i = 9; i < 18; i++)
                        tmp += img[i].read().to_uint() * kernel[i%9].read().to_uint();
                    out[1] = tmp + bias.read().to_uint();
                    tmp = 0;
                    for(int i = 18; i < 27; i++)
                        tmp += img[i].read().to_uint() * kernel[i%9].read().to_uint();
                    out[2] = tmp + bias.read().to_uint();
                    tmp = 0;
                    for(int i = 27; i < 36; i++)
                        tmp += img[i].read().to_uint() * kernel[i%9].read().to_uint();
                    out[3] = tmp + bias.read().to_uint();
                    conv_done = sc_logic_1;
                }
            }
            wait();
        }
    }
};


SC_MODULE(Convolution_TB){
    sc_signal<sc_logic> clk, start_conv;
    sc_signal<sc_lv<8>> img_element;
    sc_signal<sc_lv<6>> kernel_index;
    sc_signal<sc_lv<8>> bias;
    sc_signal<sc_lv<8>> kernel[9];
    sc_signal<sc_lv<8>> out[4];
    sc_signal<sc_logic> conv_done;

    Convolution* UUT;

    SC_CTOR(Convolution_TB) {
        UUT = new Convolution("conv_test");
        UUT->clk(clk);
        UUT->start_conv(start_conv);
        UUT->kernel_index(kernel_index);
        UUT->img_element(img_element);
        UUT->bias(bias);
        UUT->conv_done(conv_done);
        for (int i = 0; i < 9; i++)
            UUT->kernel[i](kernel[i]);
        for (int i = 0; i < 4; i++)
            UUT->out[i](out[i]);

        SC_THREAD(clocking);
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

    void inputting() {
        start_conv = sc_logic_0;
        bias = -1;
        kernel[0] = "00000000";
        kernel[1] = "00000001";
        kernel[2] = "00000000";
        kernel[3] = "00000001";
        kernel[4] = "00000001";
        kernel[5] = "00000001";
        kernel[6] = "00000000";
        kernel[7] = "00000001";
        kernel[8] = "00000000";
        wait(100,SC_NS);
        kernel_index = 0;
        img_element = 0;
        wait(100,SC_NS);
        img_element = 0;
        kernel_index = 1;
        wait(100,SC_NS);
        img_element = 0;
        kernel_index = 2;
        wait(100,SC_NS);
        img_element = 1;
        kernel_index = 3;
        wait(100,SC_NS);
        img_element = 1;
        kernel_index = 4;
        wait(100,SC_NS);
        img_element = 1;
        kernel_index = 5;
        wait(100,SC_NS);
        img_element = 1;
        kernel_index = 6;
        wait(100,SC_NS);
        img_element = 0;
        kernel_index = 7;
        wait(100,SC_NS);
        img_element = 0;
        kernel_index = 8;
        start_conv = sc_logic_1;
    }

};

#endif