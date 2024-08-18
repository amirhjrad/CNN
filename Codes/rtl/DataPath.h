#ifndef __DATAPATH_H__
#define __DATAPATH_H__

const int N = 3;

#include "systemc.h"
#include "Convolution.h"
#include "Counter1.h"
#include "Counter2.h"
#include "Img_RAM.h"
#include "MaxPool.h"
#include "ReLU.h"
#include "Result.h"

SC_MODULE(DataPath) {
    sc_in<sc_logic> clk, rst, ld1, clr2, cnt1, cnt2, start_conv, write;
    sc_in<sc_lv<2>> mode;
    sc_in<sc_lv<8>> bias1;
    sc_in<sc_lv<8>> bias2;
    sc_in<sc_lv<8>> bias3;
    sc_in<sc_lv<8>> kernel1[9];
    sc_in<sc_lv<8>> kernel2[9];
    sc_in<sc_lv<8>> kernel3[9];
    sc_out<sc_logic> conv_done_sig, co1;
    sc_out<sc_lv<3>> pattern;

    sc_signal<sc_lv<4>> addr;
    sc_signal<sc_lv<6>> kernel_index;
    sc_signal<sc_lv<8>> data_in;
    sc_signal<sc_lv<8>> data_out;
    sc_signal<sc_logic> conv_done[N];
    sc_signal<sc_lv<8>> conv1_out[4];
    sc_signal<sc_lv<8>> conv2_out[4];
    sc_signal<sc_lv<8>> conv3_out[4];
    sc_signal<sc_lv<8>> Relu1_out[4];
    sc_signal<sc_lv<8>> Relu2_out[4];
    sc_signal<sc_lv<8>> Relu3_out[4];
    sc_signal<sc_lv<8>> maxpool1_out;
    sc_signal<sc_lv<8>> maxpool2_out;
    sc_signal<sc_lv<8>> maxpool3_out;


    Counter1* Counter1_;
    Counter2* Counter2_;
    Img_RAM* Img_RAM_;
    Convolution* Convolution_[N];
    ReLU* ReLU1;
    ReLU* ReLU2;
    ReLU* ReLU3;
    MaxPool* MaxPool1;
    MaxPool* MaxPool2;
    MaxPool* MaxPool3;
    Result* Result_;


    SC_CTOR(DataPath) {

        Counter1_ = new Counter1("Counter1_Ins");
            Counter1_->clk(clk);
            Counter1_->rst(rst);
            Counter1_->cnt(cnt1);
            Counter1_->ld(ld1);
            Counter1_->mode(mode);
            Counter1_->out(addr);
            Counter1_->co(co1);
        Counter2_ = new Counter2("Counter2_Ins");
            Counter2_->clk(clk);
            Counter2_->rst(rst);
            Counter2_->cnt(cnt2);
            Counter2_->clr(clr2);
            Counter2_->out(kernel_index);
        Img_RAM_ = new Img_RAM("Img_RAM_Ins");
            Img_RAM_->clk(clk);
            Img_RAM_->rst(rst);
            Img_RAM_->write(write);
            Img_RAM_->addr(addr);
            Img_RAM_->data_in(data_in);
            Img_RAM_->data_out(data_out);
        for (int i = 0; i < N; i++) {
            std::stringstream ss;
            ss << "Convolution_Inst" << i;
            Convolution_[i] = new Convolution(ss.str().c_str());
            Convolution_[i]->clk(clk);
            Convolution_[i]->start_conv(start_conv);
            Convolution_[i]->img_element(data_out);
            Convolution_[i]->kernel_index(kernel_index);
            Convolution_[i]->conv_done(conv_done[i]);
        }
            for (int j = 0; j < 9; j++) {
                Convolution_[0]->kernel[j](kernel1[j]);
                Convolution_[1]->kernel[j](kernel2[j]);
                Convolution_[2]->kernel[j](kernel3[j]);
            }
            for (int j = 0; j < 4; j++) {
                Convolution_[0]->out[j](conv1_out[j]);
                Convolution_[1]->out[j](conv2_out[j]);
                Convolution_[2]->out[j](conv3_out[j]);
            }
            Convolution_[0]->bias(bias1);
            Convolution_[1]->bias(bias2);
            Convolution_[2]->bias(bias3);
        ReLU1 = new ReLU("ReLU1_Ins");
            ReLU1->A1(Convolution_[0]->out[0]);
            ReLU1->A2(Convolution_[0]->out[1]);
            ReLU1->A3(Convolution_[0]->out[2]);
            ReLU1->A4(Convolution_[0]->out[3]);
            ReLU1->Y1(Relu1_out[0]);
            ReLU1->Y2(Relu1_out[1]);
            ReLU1->Y3(Relu1_out[2]);
            ReLU1->Y4(Relu1_out[3]);
        ReLU2 = new ReLU("ReLU2_Ins");
            ReLU2->A1(Convolution_[1]->out[0]);
            ReLU2->A2(Convolution_[1]->out[1]);
            ReLU2->A3(Convolution_[1]->out[2]);
            ReLU2->A4(Convolution_[1]->out[3]);
            ReLU2->Y1(Relu2_out[0]);
            ReLU2->Y2(Relu2_out[1]);
            ReLU2->Y3(Relu2_out[2]);
            ReLU2->Y4(Relu2_out[3]);
        ReLU3 = new ReLU("ReLU3_Ins");
            ReLU3->A1(Convolution_[2]->out[0]);
            ReLU3->A2(Convolution_[2]->out[1]);
            ReLU3->A3(Convolution_[2]->out[2]);
            ReLU3->A4(Convolution_[2]->out[3]);
            ReLU3->Y1(Relu3_out[0]);
            ReLU3->Y2(Relu3_out[1]);
            ReLU3->Y3(Relu3_out[2]);
            ReLU3->Y4(Relu3_out[3]);
        MaxPool1 = new MaxPool("MaxPool1_Ins");
            MaxPool1->A1(Relu1_out[0]);
            MaxPool1->A2(Relu1_out[1]);
            MaxPool1->A3(Relu1_out[2]);
            MaxPool1->A4(Relu1_out[3]);
            MaxPool1->Y(maxpool1_out);
        MaxPool2 = new MaxPool("MaxPool2_Ins");
            MaxPool2->A1(Relu2_out[0]);
            MaxPool2->A2(Relu2_out[1]);
            MaxPool2->A3(Relu2_out[2]);
            MaxPool2->A4(Relu2_out[3]);
            MaxPool2->Y(maxpool2_out);
        MaxPool3 = new MaxPool("MaxPool3_Ins");
            MaxPool3->A1(Relu3_out[0]);
            MaxPool3->A2(Relu3_out[1]);
            MaxPool3->A3(Relu3_out[2]);
            MaxPool3->A4(Relu3_out[3]);
            MaxPool3->Y(maxpool3_out);
        Result_ = new Result("Result_Ins");
            Result_->A(maxpool1_out);
            Result_->B(maxpool2_out);
            Result_->C(maxpool3_out);
            Result_->res(pattern);

            SC_METHOD(assign);
            for (int i = 0; i < N; i++)
            {
                sensitive << conv_done[i];
            }
            
    }

    void assign() {
        if ((conv_done[0] == sc_logic_1) && 
            (conv_done[1] == sc_logic_1) && 
            (conv_done[2] == sc_logic_1))
            conv_done_sig = sc_logic_1;
        else 
            conv_done_sig = sc_logic_0;
    }

};

#endif