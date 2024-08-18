#ifndef __PATERNFINDER_H__
#define __PATERNFINDER_H__

#include "DataPath.h"
#include "Controller.h"

SC_MODULE(PatternFinder){
    sc_in<sc_logic> rst, clk, start;
    sc_in<sc_lv<8>> bias1;
    sc_in<sc_lv<8>> bias2;
    sc_in<sc_lv<8>> bias3;
    sc_in<sc_lv<8>> kernel1[9];
    sc_in<sc_lv<8>> kernel2[9];
    sc_in<sc_lv<8>> kernel3[9];
    sc_out<sc_logic> done;
    sc_out<sc_lv<3>> pattern;

    sc_signal<sc_logic> ld1, clr2, cnt1, cnt2, start_conv, write, co;
    sc_signal<sc_lv<2>> mode;
    sc_signal<sc_logic> conv_done_sig;
    
    DataPath* DataPath_;
    Controller* Controller_;

    SC_CTOR(PatternFinder) {
        DataPath_ = new DataPath("DataPath_Ins");
            DataPath_->clk(clk);
            DataPath_->rst(rst);
            DataPath_->ld1(ld1);
            DataPath_->clr2(clr2);
            DataPath_->cnt1(cnt1);
            DataPath_->cnt2(cnt2);
            DataPath_->start_conv(start_conv);
            DataPath_->write(write);
            DataPath_->mode(mode);
            DataPath_->bias1(bias1);
            DataPath_->bias2(bias2);
            DataPath_->bias3(bias3);
            DataPath_->co1(co);
            DataPath_->conv_done_sig(conv_done_sig);
            DataPath_->pattern(pattern);
            for (int i = 0; i < 9; i++) {
                DataPath_->kernel1[i](kernel1[i]);
                DataPath_->kernel2[i](kernel2[i]);
                DataPath_->kernel3[i](kernel3[i]);
            }
        Controller_ = new Controller("Controller_Ins");
            Controller_->clk(clk);
            Controller_->rst(rst);
            Controller_->start(start);
            Controller_->co(co);
            Controller_->conv_done_sig(conv_done_sig);
            Controller_->ld1(ld1);
            Controller_->clr2(clr2);
            Controller_->cnt1(cnt1);
            Controller_->cnt2(cnt2);
            Controller_->start_conv(start_conv);
            Controller_->write(write);
            Controller_->mode(mode);
            Controller_->done(done);
    }

};

#endif