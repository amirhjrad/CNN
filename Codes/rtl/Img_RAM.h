#ifndef __IMG_RAM_H__
#define __IMG_RAM_H__

#include "systemc.h"

SC_MODULE(Img_RAM) {
    sc_in<sc_logic> clk, rst, write;
    sc_in<sc_lv<4> > addr;
    sc_in<sc_lv<8> > data_in;
    sc_out<sc_lv<8> > data_out;

    sc_signal<sc_lv<8> > ram[16];

    SC_CTOR(Img_RAM) {
        SC_THREAD(init);
        SC_THREAD(writeMem);
        sensitive << clk << write << data_in;
        SC_METHOD(readMem);
        sensitive << addr;
    }

    void init() {
        // ifstream in("img_RAM.txt");
        // int i;
        // sc_lv<8> data;
        // for (i = 0; i<16; i++) {
        //     in >> data;
        //     ram[i] = data;
        // }

        ram[0] = "00000000";
        ram[1] = "00000000";
        ram[2] = "00000000";
        ram[3] = "00000000";
        ram[4] = "00000001";
        ram[5] = "00000001";
        ram[6] = "00000001";
        ram[7] = "00000001";
        ram[8] = "00000001";
        ram[9] = "00000000";
        ram[10] = "00000000";
        ram[11] = "00000001";
        ram[12] = "00000001";
        ram[13] = "00000001";
        ram[14] = "00000001";
        ram[15] = "00000001";

        // ram[0] = sc_lv<8>(1);
        // ram[1] = sc_lv<8>(1);
        // ram[2] = sc_lv<8>(1);
        // ram[3] = sc_lv<8>(0);
        // ram[4] = sc_lv<8>(1);
        // ram[5] = sc_lv<8>(0);
        // ram[6] = sc_lv<8>(0);
        // ram[7] = sc_lv<8>(0);
        // ram[8] = sc_lv<8>(1);
        // ram[9] = sc_lv<8>(1);
        // ram[10] = sc_lv<8>(1);
        // ram[11] = sc_lv<8>(0);
        // ram[12] = sc_lv<8>(0);
        // ram[13] = sc_lv<8>(0);
        // ram[14] = sc_lv<8>(0);
        // ram[15] = sc_lv<8>(1);


        // ram[0] = sc_lv<8>(0);
        // ram[1] = sc_lv<8>(1);
        // ram[2] = sc_lv<8>(1);
        // ram[3] = sc_lv<8>(1);
        // ram[4] = sc_lv<8>(0);
        // ram[5] = sc_lv<8>(0);
        // ram[6] = sc_lv<8>(1);
        // ram[7] = sc_lv<8>(0);
        // ram[8] = sc_lv<8>(0);
        // ram[9] = sc_lv<8>(0);
        // ram[10] = sc_lv<8>(1);
        // ram[11] = sc_lv<8>(0);
        // ram[12] = sc_lv<8>(0);
        // ram[13] = sc_lv<8>(0);
        // ram[14] = sc_lv<8>(1);
        // ram[15] = sc_lv<8>(0);

        // ram[0] = sc_lv<8>(0);
        // ram[1] = sc_lv<8>(1);
        // ram[2] = sc_lv<8>(1);
        // ram[3] = sc_lv<8>(1);
        // ram[4] = sc_lv<8>(0);
        // ram[5] = sc_lv<8>(0);
        // ram[6] = sc_lv<8>(1);
        // ram[7] = sc_lv<8>(0);
        // ram[8] = sc_lv<8>(0);
        // ram[9] = sc_lv<8>(0);
        // ram[10] = sc_lv<8>(1);
        // ram[11] = sc_lv<8>(0);
        // ram[12] = sc_lv<8>(0);
        // ram[13] = sc_lv<8>(0);
        // ram[14] = sc_lv<8>(0);
        // ram[15] = sc_lv<8>(0);

        // ram[0] = sc_lv<8>(0);
        // ram[1] = sc_lv<8>(0);
        // ram[2] = sc_lv<8>(1);
        // ram[3] = sc_lv<8>(0);
        // ram[4] = sc_lv<8>(0);
        // ram[5] = sc_lv<8>(1);
        // ram[6] = sc_lv<8>(0);
        // ram[7] = sc_lv<8>(1);
        // ram[8] = sc_lv<8>(0);
        // ram[9] = sc_lv<8>(0);
        // ram[10] = sc_lv<8>(1);
        // ram[11] = sc_lv<8>(0);
        // ram[12] = sc_lv<8>(0);
        // ram[13] = sc_lv<8>(0);
        // ram[14] = sc_lv<8>(0);
        // ram[15] = sc_lv<8>(0);

        // ram[0] = sc_lv<8>(0);
        // ram[1] = sc_lv<8>(0);
        // ram[2] = sc_lv<8>(0);
        // ram[3] = sc_lv<8>(1);
        // ram[4] = sc_lv<8>(0);
        // ram[5] = sc_lv<8>(1);
        // ram[6] = sc_lv<8>(0);
        // ram[7] = sc_lv<8>(0);
        // ram[8] = sc_lv<8>(1);
        // ram[9] = sc_lv<8>(1);
        // ram[10] = sc_lv<8>(1);
        // ram[11] = sc_lv<8>(1);
        // ram[12] = sc_lv<8>(0);
        // ram[13] = sc_lv<8>(1);
        // ram[14] = sc_lv<8>(0);
        // ram[15] = sc_lv<8>(0);
    }

    void writeMem() {
        while (true)
        {
            if (clk == sc_logic_1 && clk.event()) {
                if (write == sc_logic_1)
                    ram[addr.read().to_uint()] = data_in;
            }
            wait();
        }
    }

    void readMem() {
        data_out = ram[addr.read().to_uint()];
    }
};


SC_MODULE(Img_RAM_TB) {
    sc_signal<sc_logic> clk, rst, write;
    sc_signal<sc_lv<4> > addr;
    sc_signal<sc_lv<8> > data_in;
    sc_signal<sc_lv<8> > data_out;

    Img_RAM *UUT;

    SC_CTOR(Img_RAM_TB) {
        UUT = new Img_RAM("Img_inst");
        UUT->clk(clk);
        UUT->rst(rst);
        UUT->write(write);
        UUT->addr(addr);
        UUT->data_in(data_in);
        UUT->data_out(data_out);

        SC_THREAD(clocking);
        SC_THREAD(rstting);
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

    void rstting() {
        rst = sc_logic_0;
        wait(7,SC_NS);
        rst = sc_logic_0;
        wait(7,SC_NS);
        rst = sc_logic_0;
    }

    void inputting() {
        addr = 0;
        wait(10,SC_NS);
        addr = 1;
        wait(10,SC_NS);
        addr = 2;
        wait(10,SC_NS);
        addr = 4;
        wait(10,SC_NS);
        addr = 5;
        wait(10,SC_NS);
        addr = 6;
        wait(10,SC_NS);
        addr = 8;
        wait(10,SC_NS);
        addr = 9;
        wait(10,SC_NS);
        addr = 10;
        wait(10,SC_NS);
    }
};

#endif