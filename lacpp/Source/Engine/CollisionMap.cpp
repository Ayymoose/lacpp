#include "CollisionMap.h"
#include <assert.h>

CollisionMap::CollisionMap()
{

    std::vector<BoundingBox> vector;

    // COLLISION_TAIL_CAVE_0
    BoundingBox b1(0,80,16,48);
    BoundingBox b2(0, 0, 16, 48);
    BoundingBox b3(16, 0, 48, 16);
    BoundingBox b4(96, 0, 64, 16);
    BoundingBox b5(144, 16, 16, 96);
    BoundingBox b6(104, 112, 56, 16);
    BoundingBox b7(16, 112, 40, 16);
    BoundingBox b8(56, 104, 16, 24);
    BoundingBox b9(88, 104, 16, 24);
    BoundingBox b10(16, 16, 16, 16);
    BoundingBox b11(128, 16, 16, 16);
    BoundingBox b12(16, 96, 16, 16);
    BoundingBox b13(128, 96, 16, 16);
    BoundingBox b14(32, 32, 16, 48);
    BoundingBox b15(32, 32, 16, 48);
    BoundingBox b16(48, 32, 16, 16);
    BoundingBox b17(112, 32, 16, 48);
    BoundingBox b18(96, 32, 16, 16);

    vector.emplace_back(b1);
    vector.emplace_back(b2);
    vector.emplace_back(b3);
    vector.emplace_back(b4);
    vector.emplace_back(b5);
    vector.emplace_back(b6);
    vector.emplace_back(b7);
    vector.emplace_back(b8);
    vector.emplace_back(b9);
    vector.emplace_back(b10);
    vector.emplace_back(b11);
    vector.emplace_back(b12);
    vector.emplace_back(b13);
    vector.emplace_back(b14);
    vector.emplace_back(b15);
    vector.emplace_back(b16);
    vector.emplace_back(b17);
    vector.emplace_back(b18);

    m_collisionMap[COLLISION_TAIL_CAVE_0] = vector;
    vector.clear();

    BoundingBox b19(0, 0, 16, 56);
    BoundingBox b20(0, 72, 16, 56);
    BoundingBox b21(16, 0, 16, 32);
    BoundingBox b22(16, 96, 16, 32);
    BoundingBox b23(32, 0, 128, 16);
    BoundingBox b24(128, 16, 32, 16);
    BoundingBox b25(144, 32, 16, 16);
    BoundingBox b26(32, 112, 128, 16);
    BoundingBox b27(128, 96, 32, 16);
    BoundingBox b28(144, 80, 16, 16);

    vector.emplace_back(b19);
    vector.emplace_back(b20);
    vector.emplace_back(b21);
    vector.emplace_back(b22);
    vector.emplace_back(b23);
    vector.emplace_back(b24);
    vector.emplace_back(b25);
    vector.emplace_back(b26);
    vector.emplace_back(b27);
    vector.emplace_back(b28);

    m_collisionMap[COLLISION_TAIL_CAVE_1] = vector;
    vector.clear();

    BoundingBox b29(0, 0, 16, 128);
    BoundingBox b30(16, 0, 144, 32);
    BoundingBox b31(32, 32, 48, 16);
    BoundingBox b32(0, 96, 32, 32);
    BoundingBox b33(16, 96, 16, 16);
    BoundingBox b34(80, 96, 16, 16);
    BoundingBox b35(16, 112, 80, 16);
    BoundingBox b36(96, 80, 64, 48);
    BoundingBox b37(144, 72, 16, 8);
    BoundingBox b38(144, 32, 16, 24);
    BoundingBox b39(96, 32, 48, 16);

    vector.emplace_back(b29);
    vector.emplace_back(b30);
    vector.emplace_back(b31);
    vector.emplace_back(b32);
    vector.emplace_back(b33);
    vector.emplace_back(b34);
    vector.emplace_back(b35);
    vector.emplace_back(b36);
    vector.emplace_back(b37);
    vector.emplace_back(b38);
    vector.emplace_back(b39);

    m_collisionMap[COLLISION_TAIL_CAVE_2] = vector;
    vector.clear();

    BoundingBox b40(0, 0, 160, 16);
    BoundingBox b41(0, 16, 16, 40);
    BoundingBox b42(0, 72, 16, 56);
    BoundingBox b43(144, 16, 16, 32);
    BoundingBox b44(16, 112, 48, 16);
    BoundingBox b45(96, 112, 64, 16);
    BoundingBox b46(144, 80, 16, 48);
    BoundingBox b47(16, 96, 16, 16);
    BoundingBox b48(128, 96, 16, 16);

    vector.emplace_back(b40);
    vector.emplace_back(b41);
    vector.emplace_back(b42);
    vector.emplace_back(b43);
    vector.emplace_back(b44);
    vector.emplace_back(b45);
    vector.emplace_back(b46);
    vector.emplace_back(b47);
    vector.emplace_back(b48);

    m_collisionMap[COLLISION_TAIL_CAVE_4] = vector;
    vector.clear();

    BoundingBox b49(0, 0, 16, 128);
    BoundingBox b50(16, 0, 16, 32);
    BoundingBox b51(16, 96, 16, 32);
    BoundingBox b52(32, 0, 40, 16);
    BoundingBox b53(32, 112, 128, 16);
    BoundingBox b54(88, 0, 72, 16);
    BoundingBox b55(128, 16, 32, 16);
    BoundingBox b56(144, 32, 16, 24);
    BoundingBox b57(144, 72, 16, 56);
    BoundingBox b58(128, 96, 16, 16);
    BoundingBox b59(48, 48, 16, 32);
    BoundingBox b60(96, 48, 16, 32);

    vector.emplace_back(b49);
    vector.emplace_back(b50);
    vector.emplace_back(b51);
    vector.emplace_back(b52);
    vector.emplace_back(b53);
    vector.emplace_back(b54);
    vector.emplace_back(b55);
    vector.emplace_back(b56);
    vector.emplace_back(b57);
    vector.emplace_back(b58);
    vector.emplace_back(b59);
    vector.emplace_back(b60);

    m_collisionMap[COLLISION_TAIL_CAVE_5] = vector;
    vector.clear();

    BoundingBox b61(0, 0, 16, 48);
    BoundingBox b62(0, 80, 16, 48);
    BoundingBox b63(16, 0, 56, 16);
    BoundingBox b64(48, 16, 16, 16);
    BoundingBox b65(96, 16, 16, 16);
    BoundingBox b66(48, 80, 16, 16);
    BoundingBox b67(96, 80, 16, 16);
    BoundingBox b68(88, 0, 72, 16);
    BoundingBox b69(16, 112, 144, 16);
    BoundingBox b70(144, 0, 16, 128);

    vector.emplace_back(b61);
    vector.emplace_back(b62);
    vector.emplace_back(b63);
    vector.emplace_back(b64);
    vector.emplace_back(b65);
    vector.emplace_back(b66);
    vector.emplace_back(b67);
    vector.emplace_back(b68);
    vector.emplace_back(b69);
    vector.emplace_back(b70);

    m_collisionMap[COLLISION_TAIL_CAVE_3] = vector;
    vector.clear();

    BoundingBox b71(0, 0, 16, 48);
    BoundingBox b72(0, 64, 16, 64);
    BoundingBox b73(16, 112, 56, 16);
    BoundingBox b74(88, 112, 72, 16);
    BoundingBox b75(128, 0, 32, 32);
    BoundingBox b76(48, 16, 16, 32);
    BoundingBox b77(96, 16, 16, 32);

    vector.emplace_back(b71);
    vector.emplace_back(b72);
    vector.emplace_back(b73);
    vector.emplace_back(b74);
    vector.emplace_back(b75);
    vector.emplace_back(b76);
    vector.emplace_back(b77);

    m_collisionMap[COLLISION_TAIL_CAVE_11] = vector;
    vector.clear();

    BoundingBox b78(0, 0, 32, 128);
    BoundingBox b79(32, 0, 16, 32);
    BoundingBox b80(32, 96, 16, 32);
    BoundingBox b81(48, 0, 112, 16);
    BoundingBox b82(48, 112, 112, 16);
    BoundingBox b83(144, 0, 16, 48);
    BoundingBox b84(144, 64, 16, 64);

    vector.emplace_back(b78);
    vector.emplace_back(b79);
    vector.emplace_back(b80);
    vector.emplace_back(b81);
    vector.emplace_back(b82);
    vector.emplace_back(b83);
    vector.emplace_back(b84);

    m_collisionMap[COLLISION_TAIL_CAVE_12] = vector;
    vector.clear();

    BoundingBox b85(0, 0, 32, 32);
    BoundingBox b86(0, 112, 160, 16);
    BoundingBox b87(144, 96, 16, 16);
    BoundingBox b88(144, 0, 16, 32);
    BoundingBox b89(64, 80, 16, 16);
    BoundingBox b90(112, 80, 16, 16);
    BoundingBox b91(112, 32, 16, 16);
    BoundingBox b92(144, 48, 16, 16);

    vector.emplace_back(b85);
    vector.emplace_back(b86);
    vector.emplace_back(b87);
    vector.emplace_back(b88);
    vector.emplace_back(b89);
    vector.emplace_back(b90);
    vector.emplace_back(b91);
    vector.emplace_back(b92);

    m_collisionMap[COLLISION_TAIL_CAVE_10] = vector;
    vector.clear();

    BoundingBox b93(0, 0, 16, 32);
    BoundingBox b94(0, 96, 16, 32);
    BoundingBox b95(16, 112, 56, 16);
    BoundingBox b96(16, 0, 96, 16);
    BoundingBox b97(144, 0, 16, 56);
    BoundingBox b98(144, 72, 16, 56);
    BoundingBox b99(0, 48, 64, 16);
    BoundingBox b100(48, 32, 96, 16);
    BoundingBox b101(88, 112, 72, 16);
    BoundingBox b102(128, 0, 32, 16);

    vector.emplace_back(b93);
    vector.emplace_back(b94);
    vector.emplace_back(b95);
    vector.emplace_back(b96);
    vector.emplace_back(b97);
    vector.emplace_back(b98);
    vector.emplace_back(b99);
    vector.emplace_back(b100);
    vector.emplace_back(b101);
    vector.emplace_back(b102);

    m_collisionMap[COLLISION_TAIL_CAVE_9] = vector;
    vector.clear();

    BoundingBox b103(0, 0, 16, 56);
    BoundingBox b104(0, 72, 16, 56);
    BoundingBox b105(16, 0, 48, 16);
    BoundingBox b106(16, 112, 144, 16);
    BoundingBox b107(96, 0, 64, 16);
    BoundingBox b108(144, 16, 16, 40);
    BoundingBox b109(144, 72, 16, 56);
    BoundingBox b110(48, 48, 48, 32);

    vector.emplace_back(b103);
    vector.emplace_back(b104);
    vector.emplace_back(b105);
    vector.emplace_back(b106);
    vector.emplace_back(b107);
    vector.emplace_back(b108);
    vector.emplace_back(b109);
    vector.emplace_back(b110);

    m_collisionMap[COLLISION_TAIL_CAVE_8] = vector;
    vector.clear();

    BoundingBox b111(0, 0, 16, 56);
    BoundingBox b112(0, 72, 16, 56);
    BoundingBox b113(16, 112, 144, 16);
    BoundingBox b114(16, 0, 56, 16);
    BoundingBox b115(88, 0, 72, 16);
    BoundingBox b116(144, 0, 16, 128);

    vector.emplace_back(b111);
    vector.emplace_back(b112);
    vector.emplace_back(b113);
    vector.emplace_back(b114);
    vector.emplace_back(b115);
    vector.emplace_back(b116);

    m_collisionMap[COLLISION_TAIL_CAVE_7] = vector;
    vector.clear();

    BoundingBox b117(0, 0, 64, 128);
    BoundingBox b118(80, 0, 80, 128);

    vector.emplace_back(b117);
    vector.emplace_back(b118);

    m_collisionMap[COLLISION_TAIL_CAVE_13] = vector;
    vector.clear();

    BoundingBox b119(32, 64, 16, 16);
    BoundingBox b120(32, 96, 80, 128);
    BoundingBox b121(96, 64, 16, 16);
    BoundingBox b122(96, 96, 16, 16);
    BoundingBox b123(0, 0, 64, 64);
    BoundingBox b124(80, 0, 80, 64);
    BoundingBox b125(0, 64, 32, 64);
    BoundingBox b126(112, 64, 48, 64);
    BoundingBox b127(32, 112, 80, 16);

    vector.emplace_back(b119);
    vector.emplace_back(b120);
    vector.emplace_back(b121);
    vector.emplace_back(b122);
    vector.emplace_back(b123);
    vector.emplace_back(b124);
    vector.emplace_back(b125);
    vector.emplace_back(b126);
    vector.emplace_back(b127);

    m_collisionMap[COLLISION_TAIL_CAVE_6] = vector;
    vector.clear();

    BoundingBox b128(16, 96, 16, 16);
    BoundingBox b129(32, 16, 16, 16);
    BoundingBox b130(96, 16, 16, 16);
    BoundingBox b131(128, 96, 16, 16);
    BoundingBox b132(0, 0, 160, 16);
    BoundingBox b133(0, 0, 16, 128);
    BoundingBox b134(144, 0, 16, 128);
    BoundingBox b135(0, 112, 64, 16);
    BoundingBox b136(80, 112, 80, 16);

    vector.emplace_back(b128);
    vector.emplace_back(b129);
    vector.emplace_back(b130);
    vector.emplace_back(b131);
    vector.emplace_back(b132);
    vector.emplace_back(b133);
    vector.emplace_back(b134);
    vector.emplace_back(b135);
    vector.emplace_back(b136);

    m_collisionMap[COLLISION_TAIL_CAVE_19] = vector;
    vector.clear();

    BoundingBox b137(16, 96, 16, 16);
    BoundingBox b138(48, 96, 16, 16);
    BoundingBox b139(96, 96, 16, 16);
    BoundingBox b140(32, 64, 16, 16);
    BoundingBox b141(128, 96, 32, 32);
    BoundingBox b142(0, 0, 16, 128);
    BoundingBox b143(16, 0, 16, 48);
    BoundingBox b144(32, 0, 16, 32);
    BoundingBox b145(48, 0, 24, 16);
    BoundingBox b146(88, 0, 24, 16);
    BoundingBox b147(112, 0, 24, 80);
    BoundingBox b148(136, 0, 24, 8);
    BoundingBox b149(136, 56, 24, 24);

    vector.emplace_back(b137);
    vector.emplace_back(b138);
    vector.emplace_back(b139);
    vector.emplace_back(b140);
    vector.emplace_back(b141);
    vector.emplace_back(b142);
    vector.emplace_back(b143);
    vector.emplace_back(b144);
    vector.emplace_back(b145);
    vector.emplace_back(b146);
    vector.emplace_back(b147);
    vector.emplace_back(b148);
    vector.emplace_back(b149);

    m_collisionMap[COLLISION_TAIL_CAVE_18] = vector;
    vector.clear();

    BoundingBox b150(0, 0, 160, 8);
    BoundingBox b151(16, 0, 32, 16);
    BoundingBox b152(96, 0, 32, 16);
    BoundingBox b153(24, 40, 96, 24);
    BoundingBox b154(0, 56, 24, 8);
    BoundingBox b155(0, 64, 48, 16);
    BoundingBox b156(120, 56, 40, 8);
    BoundingBox b157(96, 64, 64, 16);
    BoundingBox b158(144, 80, 16, 48);
    BoundingBox b159(0, 96, 32, 32);

    vector.emplace_back(b150);
    vector.emplace_back(b151);
    vector.emplace_back(b152);
    vector.emplace_back(b153);
    vector.emplace_back(b154);
    vector.emplace_back(b155);
    vector.emplace_back(b156);
    vector.emplace_back(b157);
    vector.emplace_back(b158);
    vector.emplace_back(b159);

    m_collisionMap[COLLISION_TAIL_CAVE_17] = vector;
    vector.clear();

    BoundingBox b160(0, 0, 64, 8);
    BoundingBox b161(56, 0, 8, 64);
    BoundingBox b162(48, 56, 8, 8);
    BoundingBox b163(0, 56, 32, 8);
    BoundingBox b164(0, 64, 32, 16);
    BoundingBox b165(48, 64, 32, 16);
    BoundingBox b166(0, 80, 16, 32);
    BoundingBox b167(0, 112, 112, 16);
    BoundingBox b168(64, 0, 16, 80);
    BoundingBox b169(80, 0, 48, 16);
    BoundingBox b170(128, 0, 32, 32);
    BoundingBox b171(144, 32, 16, 96);
    BoundingBox b172(128, 112, 16, 16);

    vector.emplace_back(b160);
    vector.emplace_back(b161);
    vector.emplace_back(b162);
    vector.emplace_back(b163);
    vector.emplace_back(b164);
    vector.emplace_back(b165);
    vector.emplace_back(b166);
    vector.emplace_back(b167);
    vector.emplace_back(b168);
    vector.emplace_back(b169);
    vector.emplace_back(b170);
    vector.emplace_back(b171);
    vector.emplace_back(b172);

    m_collisionMap[COLLISION_TAIL_CAVE_16] = vector;
    vector.clear();

    BoundingBox b173(0, 0, 160, 16);
    BoundingBox b174(0, 16, 32, 32);
    BoundingBox b175(128, 0, 32, 32);
    BoundingBox b176(144, 32, 16, 64);
    BoundingBox b177(0, 32, 16, 64);
    BoundingBox b178(0, 96, 32, 32);
    BoundingBox b179(128, 96, 32, 32);
    BoundingBox b180(32, 112, 32, 16);
    BoundingBox b181(96, 112, 32, 16);

    vector.emplace_back(b173);
    vector.emplace_back(b174);
    vector.emplace_back(b175);
    vector.emplace_back(b176);
    vector.emplace_back(b177);
    vector.emplace_back(b178);
    vector.emplace_back(b179);
    vector.emplace_back(b180);
    vector.emplace_back(b181);

    m_collisionMap[COLLISION_TAIL_CAVE_15] = vector;
    vector.clear();

    BoundingBox b182(0, 0, 16, 128);
    BoundingBox b183(144, 0, 16, 128);
    BoundingBox b184(0, 112, 72, 16);
    BoundingBox b185(88, 112, 72, 16);
    BoundingBox b186(0, 0, 72, 16);
    BoundingBox b187(88, 0, 72, 16);
    BoundingBox b188(48, 64, 64, 16);
    BoundingBox b189(48, 48, 16, 16);
    BoundingBox b190(96, 48, 16, 16);

    vector.emplace_back(b182);
    vector.emplace_back(b183);
    vector.emplace_back(b184);
    vector.emplace_back(b185);
    vector.emplace_back(b186);
    vector.emplace_back(b187);
    vector.emplace_back(b188);
    vector.emplace_back(b189);
    vector.emplace_back(b190);

    m_collisionMap[COLLISION_TAIL_CAVE_14] = vector;
    vector.clear();

    BoundingBox b191(0, 0, 16, 128);
    BoundingBox b192(144, 0, 16, 128);
    BoundingBox b193(0, 112, 72, 16);
    BoundingBox b194(88, 112, 72, 16);
    BoundingBox b195(0, 0, 72, 16);
    BoundingBox b196(88, 0, 72, 16);

    vector.emplace_back(b191);
    vector.emplace_back(b192);
    vector.emplace_back(b193);
    vector.emplace_back(b194);
    vector.emplace_back(b195);
    vector.emplace_back(b196);

    m_collisionMap[COLLISION_TAIL_CAVE_20] = vector;
    vector.clear();

    BoundingBox b197(0, 0, 128, 16);
    BoundingBox b198(0, 112, 128, 16);
    BoundingBox b199(128, 0, 32, 32);
    BoundingBox b200(128, 96, 32, 32);
    BoundingBox b201(144, 0, 16, 128);
    BoundingBox b202(0, 80, 48, 8);
    BoundingBox b203(32, 48, 16, 16);
    BoundingBox b204(48, 32, 16, 16);
    BoundingBox b205(48, 80, 16, 16);
    BoundingBox b206(64, 64, 16, 16);
    BoundingBox b207(80, 48, 16, 16);
    BoundingBox b208(96, 32, 16, 16);
    BoundingBox b209(96, 80, 16, 16);
    BoundingBox b210(112, 64, 16, 16);

    vector.emplace_back(b197);
    vector.emplace_back(b198);
    vector.emplace_back(b199);
    vector.emplace_back(b200);
    vector.emplace_back(b201);
    vector.emplace_back(b202);
    vector.emplace_back(b203);
    vector.emplace_back(b204);
    vector.emplace_back(b205);
    vector.emplace_back(b206);
    vector.emplace_back(b207);
    vector.emplace_back(b208);
    vector.emplace_back(b209);
    vector.emplace_back(b210);

    m_collisionMap[COLLISION_TAIL_CAVE_23] = vector;
    vector.clear();
    
    BoundingBox b211(0, 0, 160, 16);
    BoundingBox b212(0, 0, 16, 40);
    BoundingBox b213(0, 56, 16, 72);
    BoundingBox b214(16, 112, 56, 16);
    BoundingBox b215(88, 112, 72, 16);
    BoundingBox b216(16, 16, 16, 16);
    BoundingBox b217(16, 96, 16, 16);
    BoundingBox b218(64, 80, 96, 8);
    BoundingBox b219(32, 48, 16, 16);
    BoundingBox b220(64, 32, 16, 16);
    BoundingBox b221(80, 48, 16, 16);
    BoundingBox b222(96, 32, 16, 16);
    BoundingBox b223(112, 48, 16, 16);
    BoundingBox b999(16, 80, 16, 8);

    vector.emplace_back(b211);
    vector.emplace_back(b212);
    vector.emplace_back(b213);
    vector.emplace_back(b214);
    vector.emplace_back(b215);
    vector.emplace_back(b216);
    vector.emplace_back(b217);
    vector.emplace_back(b218);
    vector.emplace_back(b219);
    vector.emplace_back(b220);
    vector.emplace_back(b221);
    vector.emplace_back(b222);
    vector.emplace_back(b223);
    vector.emplace_back(b999);

    m_collisionMap[COLLISION_TAIL_CAVE_24] = vector;
    vector.clear();

    BoundingBox b224(0, 0, 160, 16);
    BoundingBox b225(0, 0, 16, 80);
    BoundingBox b226(0, 80, 32, 48);
    BoundingBox b227(32, 96, 16, 32);
    BoundingBox b228(48, 112, 64, 16);
    BoundingBox b229(112, 96, 48, 32);
    BoundingBox b230(128, 80, 32, 16);
    BoundingBox b231(144, 56, 16, 24);
    BoundingBox b232(144, 0, 16, 40);

    vector.emplace_back(b224);
    vector.emplace_back(b225);
    vector.emplace_back(b226);
    vector.emplace_back(b227);
    vector.emplace_back(b228);
    vector.emplace_back(b229);
    vector.emplace_back(b230);
    vector.emplace_back(b231);
    vector.emplace_back(b232);

    m_collisionMap[COLLISION_TAIL_CAVE_25] = vector;
    vector.clear();

    BoundingBox b233(0, 0, 160, 16);
    BoundingBox b234(0, 16, 48, 16);
    BoundingBox b235(96, 16, 48, 16);
    BoundingBox b236(0, 0, 16, 128);
    BoundingBox b237(144, 0, 16, 128);
    BoundingBox b238(0, 112, 72, 16);
    BoundingBox b239(88, 112, 72, 16);
    BoundingBox b240(16, 96, 16, 16);
    BoundingBox b241(128, 96, 16, 16);
    BoundingBox b242(32, 32, 16, 48);
    BoundingBox b243(112, 32, 16, 48);
    BoundingBox b244(48, 48, 16, 32);
    BoundingBox b245(96, 48, 16, 32);

    vector.emplace_back(b233);
    vector.emplace_back(b234);
    vector.emplace_back(b235);
    vector.emplace_back(b236);
    vector.emplace_back(b237);
    vector.emplace_back(b238);
    vector.emplace_back(b239);
    vector.emplace_back(b240);
    vector.emplace_back(b241);
    vector.emplace_back(b242);
    vector.emplace_back(b243);
    vector.emplace_back(b244);
    vector.emplace_back(b245);

    m_collisionMap[COLLISION_TAIL_CAVE_26] = vector;
    vector.clear();
}

std::vector<BoundingBox> CollisionMap::collisionMap(CollisionArea area)
{
    assert(area > COLLISION_AREA_NONE && area < COLLISION_AREA_COUNT);
    return m_collisionMap[area];
}
