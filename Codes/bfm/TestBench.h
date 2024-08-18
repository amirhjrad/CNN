#include "patternFinder.h"

SC_MODULE(TestBench) {
    sc_signal<sc_logic> clk;
    sc_signal<sc_lv<8> > Img_RAM[16];
    sc_signal<sc_logic> start;
    sc_signal<sc_logic> done;
    sc_signal<sc_lv<3> > Result;

    PatternFinder *PF;

    SC_CTOR(TestBench){
        PF = new PatternFinder("PF_Inst");
        PF->clk(clk);
        PF->start(start);
        PF->done(done);
        PF->Result(Result);
        for (int i = 0; i < 16; i++)
            PF->Img_RAM[i](Img_RAM[i]);

        SC_THREAD(clocking);
        SC_THREAD(initRam);
        SC_THREAD(inputting);
    }

    void clocking() {
        while (true)
        {
            clk = sc_logic_0;
            wait(5, SC_NS);
            clk = sc_logic_1;
            wait(5, SC_NS);
        }
        
    }

    void initRam() {
    //pattern 2
        // Img_RAM[0] = "00000000";
        // Img_RAM[1] = "00000000";
        // Img_RAM[2] = "00000000";
        // Img_RAM[3] = "00000000";
        // Img_RAM[4] = "00000001";
        // Img_RAM[5] = "00000001";
        // Img_RAM[6] = "00000001";
        // Img_RAM[7] = "00000001";
        // Img_RAM[8] = "00000001";
        // Img_RAM[9] = "00000000";
        // Img_RAM[10] = "00000000";
        // Img_RAM[11] = "00000001";
        // Img_RAM[12] = "00000001";
        // Img_RAM[13] = "00000001";
        // Img_RAM[14] = "00000001";
        // Img_RAM[15] = "00000001";

    //pattern 2
        // Img_RAM[0] = sc_lv<8>(1);
        // Img_RAM[1] = sc_lv<8>(1);
        // Img_RAM[2] = sc_lv<8>(1);
        // Img_RAM[3] = sc_lv<8>(0);
        // Img_RAM[4] = sc_lv<8>(1);
        // Img_RAM[5] = sc_lv<8>(0);
        // Img_RAM[6] = sc_lv<8>(0);
        // Img_RAM[7] = sc_lv<8>(0);
        // Img_RAM[8] = sc_lv<8>(1);
        // Img_RAM[9] = sc_lv<8>(1);
        // Img_RAM[10] = sc_lv<8>(1);
        // Img_RAM[11] = sc_lv<8>(0);
        // Img_RAM[12] = sc_lv<8>(0);
        // Img_RAM[13] = sc_lv<8>(0);
        // Img_RAM[14] = sc_lv<8>(0);
        // Img_RAM[15] = sc_lv<8>(1);

    //pattern 3
        // Img_RAM[0] = sc_lv<8>(0);
        // Img_RAM[1] = sc_lv<8>(1);
        // Img_RAM[2] = sc_lv<8>(1);
        // Img_RAM[3] = sc_lv<8>(1);
        // Img_RAM[4] = sc_lv<8>(0);
        // Img_RAM[5] = sc_lv<8>(0);
        // Img_RAM[6] = sc_lv<8>(1);
        // Img_RAM[7] = sc_lv<8>(0);
        // Img_RAM[8] = sc_lv<8>(0);
        // Img_RAM[9] = sc_lv<8>(0);
        // Img_RAM[10] = sc_lv<8>(1);
        // Img_RAM[11] = sc_lv<8>(0);
        // Img_RAM[12] = sc_lv<8>(0);
        // Img_RAM[13] = sc_lv<8>(0);
        // Img_RAM[14] = sc_lv<8>(1);
        // Img_RAM[15] = sc_lv<8>(0);


        // Img_RAM[0] = sc_lv<8>(0);
        // Img_RAM[1] = sc_lv<8>(1);
        // Img_RAM[2] = sc_lv<8>(1);
        // Img_RAM[3] = sc_lv<8>(1);
        // Img_RAM[4] = sc_lv<8>(0);
        // Img_RAM[5] = sc_lv<8>(0);
        // Img_RAM[6] = sc_lv<8>(1);
        // Img_RAM[7] = sc_lv<8>(0);
        // Img_RAM[8] = sc_lv<8>(0);
        // Img_RAM[9] = sc_lv<8>(0);
        // Img_RAM[10] = sc_lv<8>(1);
        // Img_RAM[11] = sc_lv<8>(0);
        // Img_RAM[12] = sc_lv<8>(0);
        // Img_RAM[13] = sc_lv<8>(0);
        // Img_RAM[14] = sc_lv<8>(0);
        // Img_RAM[15] = sc_lv<8>(0);


        // Img_RAM[0] = sc_lv<8>(0);
        // Img_RAM[1] = sc_lv<8>(0);
        // Img_RAM[2] = sc_lv<8>(1);
        // Img_RAM[3] = sc_lv<8>(0);
        // Img_RAM[4] = sc_lv<8>(0);
        // Img_RAM[5] = sc_lv<8>(1);
        // Img_RAM[6] = sc_lv<8>(0);
        // Img_RAM[7] = sc_lv<8>(1);
        // Img_RAM[8] = sc_lv<8>(0);
        // Img_RAM[9] = sc_lv<8>(0);
        // Img_RAM[10] = sc_lv<8>(1);
        // Img_RAM[11] = sc_lv<8>(0);
        // Img_RAM[12] = sc_lv<8>(0);
        // Img_RAM[13] = sc_lv<8>(0);
        // Img_RAM[14] = sc_lv<8>(0);
        // Img_RAM[15] = sc_lv<8>(0);


        Img_RAM[0] = sc_lv<8>(0);
        Img_RAM[1] = sc_lv<8>(0);
        Img_RAM[2] = sc_lv<8>(0);
        Img_RAM[3] = sc_lv<8>(1);
        Img_RAM[4] = sc_lv<8>(0);
        Img_RAM[5] = sc_lv<8>(1);
        Img_RAM[6] = sc_lv<8>(0);
        Img_RAM[7] = sc_lv<8>(0);
        Img_RAM[8] = sc_lv<8>(1);
        Img_RAM[9] = sc_lv<8>(1);
        Img_RAM[10] = sc_lv<8>(1);
        Img_RAM[11] = sc_lv<8>(1);
        Img_RAM[12] = sc_lv<8>(0);
        Img_RAM[13] = sc_lv<8>(1);
        Img_RAM[14] = sc_lv<8>(0);
        Img_RAM[15] = sc_lv<8>(0);
    }

    void inputting() {
        start = sc_logic_0;
        wait(17,SC_NS);
        start = sc_logic_1;
        wait(17,SC_NS);
        start = SC_LOGIC_0;
    }

};