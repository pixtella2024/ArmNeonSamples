#include <iostream>
#include <limits>
#include <stdint.h>

#include <arm_neon.h>

int main(int argc, char *argv[]) {
    std::cout << "\"Vector arithmetic / Add / Narrowing addition\" の intrinsic 関数 サンプルコード" << std::endl;

    uint16_t src0_u[] = {UINT16_MAX / 2 - 1, 1, UINT16_MAX - 1, UINT16_MAX, 2, 2, 2, 2};
    uint16_t src1_u[] = {1, 1, 1, 1, 0, 1, UINT16_MAX - 1, UINT16_MAX};
    uint16_t dst_u[8];

    int16_t src0_s[] = {0, -1, INT16_MAX, INT16_MIN, -2, 2, 2, -2};
    int16_t src1_s[] = {-1, 1, 1, -1, 0, -1, INT16_MAX, INT16_MIN};
    int16_t dst_s[8];

    // vhadd_xxx の動作
    { // unsigned
        std::cout << "[vhadd_u16]" << std::endl;

        uint16x4_t vSrc0 = vld1_u16(src0_u);
        uint16x4_t vSrc1 = vld1_u16(src1_u);

        uint16x4_t vDst = vhadd_u16(vSrc0, vSrc1);

        vst1_u16(dst_u, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_u[i] << " + " << (int32_t)src1_u[i] << ") >> 1 = " << (int32_t)dst_u[i]
                      << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vhadd_s16]" << std::endl;

        int16x4_t vSrc0 = vld1_s16(src0_s);
        int16x4_t vSrc1 = vld1_s16(src1_s);

        int16x4_t vDst = vhadd_s16(vSrc0, vSrc1);

        vst1_s16(dst_s, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_s[i] << " + " << (int32_t)src1_s[i] << ") >> 1 = " << (int32_t)dst_s[i]
                      << std::endl;
        }
        std::cout << std::endl;
    }

    // vhaddq_xxx の動作
    { // unsigned
        std::cout << "[vhaddq_u16]" << std::endl;

        uint16x8_t vSrc0 = vld1q_u16(src0_u);
        uint16x8_t vSrc1 = vld1q_u16(src1_u);

        uint16x8_t vDst = vhaddq_u16(vSrc0, vSrc1);

        vst1q_u16(dst_u, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_u[i] << " + " << (int32_t)src1_u[i] << ") >> 1 = " << (int32_t)dst_u[i]
                      << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vhaddq_s16]" << std::endl;

        int16x8_t vSrc0 = vld1q_s16(src0_s);
        int16x8_t vSrc1 = vld1q_s16(src1_s);

        int16x8_t vDst = vhaddq_s16(vSrc0, vSrc1);

        vst1q_s16(dst_s, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_s[i] << " + " << (int32_t)src1_s[i] << ") >> 1 = " << (int32_t)dst_s[i]
                      << std::endl;
        }
        std::cout << std::endl;
    }

    // vrhadd_xxx の動作
    { // unsigned
        std::cout << "[vrhadd_u16]" << std::endl;

        uint16x4_t vSrc0 = vld1_u16(src0_u);
        uint16x4_t vSrc1 = vld1_u16(src1_u);

        uint16x4_t vDst = vrhadd_u16(vSrc0, vSrc1);

        vst1_u16(dst_u, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "(( " << (int32_t)src0_u[i] << " + " << (int32_t)src1_u[i]
                      << ") + 1) >> 1 = " << (int32_t)dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vrhadd_s16]" << std::endl;

        int16x4_t vSrc0 = vld1_s16(src0_s);
        int16x4_t vSrc1 = vld1_s16(src1_s);

        int16x4_t vDst = vrhadd_s16(vSrc0, vSrc1);

        vst1_s16(dst_s, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "(( " << (int32_t)src0_s[i] << " + " << (int32_t)src1_s[i]
                      << ") + 1) >> 1 = " << (int32_t)dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vrhaddq_xxx の動作
    { // unsigned
        std::cout << "[vrhaddq_u16]" << std::endl;

        uint16x8_t vSrc0 = vld1q_u16(src0_u);
        uint16x8_t vSrc1 = vld1q_u16(src1_u);

        uint16x8_t vDst = vrhaddq_u16(vSrc0, vSrc1);

        vst1q_u16(dst_u, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "(( " << (int32_t)src0_u[i] << " + " << (int32_t)src1_u[i]
                      << ") + 1) >> 1 = " << (int32_t)dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vrhaddq_s16]" << std::endl;

        int16x8_t vSrc0 = vld1q_s16(src0_s);
        int16x8_t vSrc1 = vld1q_s16(src1_s);

        int16x8_t vDst = vrhaddq_s16(vSrc0, vSrc1);

        vst1q_s16(dst_s, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "(( " << (int32_t)src0_s[i] << " + " << (int32_t)src1_s[i]
                      << ") + 1) >> 1 = " << (int32_t)dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vaddhn_xxx および vaddhn_high_xxx の動作
    { // unsigned
        std::cout << "[vaddhn_u16]" << std::endl;

        src0_u[0] = 0x0000;
        src1_u[0] = 0x0100;

        src0_u[1] = 0xfe00;
        src1_u[1] = 0x0100;

        src0_u[2] = 0xff00;
        src1_u[2] = 0x0100;

        src0_u[3] = 0x0001;
        src1_u[3] = 0x0001;

        src0_u[4] = 0x0001;
        src1_u[4] = 0x00fe;

        src0_u[5] = 0x0001;
        src1_u[5] = 0x00ff;

        src0_u[6] = 0x0040;
        src1_u[6] = 0x0040;

        src0_u[7] = 0xff00;
        src1_u[7] = 0x0080;

        uint8_t *tmpDst_u = (uint8_t *)dst_u;

        uint16x8_t vSrc0 = vld1q_u16(src0_u);
        uint16x8_t vSrc1 = vld1q_u16(src1_u);

        uint8x8_t vDst_l = vaddhn_u16(vSrc0, vSrc1);

        vst1_u8(tmpDst_u, vDst_l);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_u[i] << " + " << (int32_t)src1_u[i]
                      << " ) >> 8 = " << (int32_t)tmpDst_u[i] << std::endl;
        }
        std::cout << std::endl;

        std::cout << "[vaddhn_high_u16]" << std::endl;

        src0_u[0] = 0x0100;
        src1_u[0] = 0x0080;

        src0_u[1] = 0x0100;
        src1_u[1] = 0x0100;

        src0_u[2] = 0x0200;
        src1_u[2] = 0x0080;

        src0_u[3] = 0x0200;
        src1_u[3] = 0x0100;

        src0_u[4] = 0x0400;
        src1_u[4] = 0x0080;

        src0_u[5] = 0x0400;
        src1_u[5] = 0x0100;

        src0_u[6] = 0x0800;
        src1_u[6] = 0x0080;

        src0_u[7] = 0x0800;
        src1_u[7] = 0x0100;

        vSrc0 = vld1q_u16(src0_u);
        vSrc1 = vld1q_u16(src1_u);

        uint8x16_t vDst_h = vaddhn_high_u16(vDst_l, vSrc0, vSrc1);

        vst1q_u8(tmpDst_u, vDst_h);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)tmpDst_u[i] << std::endl;
        }
        for (int32_t i = 8; i < 16; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_u[i - 8] << " + " << (int32_t)src1_u[i - 8]
                      << " ) >> 8 = " << (int32_t)tmpDst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vaddhn_s16]" << std::endl;

        src0_s[0] = 0x0000;
        src1_s[0] = 0x0100;

        src0_s[1] = 0xfe00;
        src1_s[1] = 0x0100;

        src0_s[2] = 0xff00;
        src1_s[2] = 0x0100;

        src0_s[3] = 0x0001;
        src1_s[3] = 0x0001;

        src0_s[4] = 0x0001;
        src1_s[4] = 0x00fe;

        src0_s[5] = 0x0001;
        src1_s[5] = 0x00ff;

        src0_s[6] = 0x0040;
        src1_s[6] = 0x0040;

        src0_s[7] = 0xff00;
        src1_s[7] = 0x0080;

        int8_t *tmpDst_s = (int8_t *)dst_s;

        int16x8_t vSrc0 = vld1q_s16(src0_s);
        int16x8_t vSrc1 = vld1q_s16(src1_s);

        int8x8_t vDst_l = vaddhn_s16(vSrc0, vSrc1);

        vst1_s8(tmpDst_s, vDst_l);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_s[i] << " + " << (int32_t)src1_s[i]
                      << " ) >> 8 = " << (int32_t)tmpDst_s[i] << std::endl;
        }
        std::cout << std::endl;

        std::cout << "[vaddhn_high_s16]" << std::endl;

        src0_s[0] = 0x0100;
        src1_s[0] = 0x0080;

        src0_s[1] = 0x0100;
        src1_s[1] = 0x0100;

        src0_s[2] = 0x0200;
        src1_s[2] = 0x0080;

        src0_s[3] = 0x0200;
        src1_s[3] = 0x0100;

        src0_s[4] = 0x0400;
        src1_s[4] = 0x0080;

        src0_s[5] = 0x0400;
        src1_s[5] = 0x0100;

        src0_s[6] = 0x0800;
        src1_s[6] = 0x0080;

        src0_s[7] = 0x0800;
        src1_s[7] = 0x0100;

        vSrc0 = vld1q_s16(src0_s);
        vSrc1 = vld1q_s16(src1_s);

        int8x16_t vDst_h = vaddhn_high_s16(vDst_l, vSrc0, vSrc1);

        vst1q_s8(tmpDst_s, vDst_h);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)tmpDst_s[i] << std::endl;
        }
        for (int32_t i = 8; i < 16; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_s[i - 8] << " + " << (int32_t)src1_s[i - 8]
                      << " ) >> 8 = " << (int32_t)tmpDst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vraddhn_xxx および vraddhn_high_xxx の動作
    { // unsigned
        std::cout << "[vraddhn_u16]" << std::endl;

        src0_u[0] = 0x0000;
        src1_u[0] = 0x0100;

        src0_u[1] = 0xfe00;
        src1_u[1] = 0x0100;

        src0_u[2] = 0xff00;
        src1_u[2] = 0x0100;

        src0_u[3] = 0x0001;
        src1_u[3] = 0x0001;

        src0_u[4] = 0x0001;
        src1_u[4] = 0x00fe;

        src0_u[5] = 0x0001;
        src1_u[5] = 0x00ff;

        src0_u[6] = 0x0040;
        src1_u[6] = 0x0040;

        src0_u[7] = 0xff00;
        src1_u[7] = 0x0080;

        uint8_t *tmpDst_u = (uint8_t *)dst_u;

        uint16x8_t vSrc0 = vld1q_u16(src0_u);
        uint16x8_t vSrc1 = vld1q_u16(src1_u);

        uint8x8_t vDst_l = vraddhn_u16(vSrc0, vSrc1);

        vst1_u8(tmpDst_u, vDst_l);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "(( " << (int32_t)src0_u[i] << " + " << (int32_t)src1_u[i] << " ) + " << (1 << 7)
                      << ") >> 8 = " << (int32_t)tmpDst_u[i] << std::endl;
        }
        std::cout << std::endl;

        std::cout << "[vraddhn_high_u16]" << std::endl;

        src0_u[0] = 0x0100;
        src1_u[0] = 0x0080;

        src0_u[1] = 0x0100;
        src1_u[1] = 0x0100;

        src0_u[2] = 0x0200;
        src1_u[2] = 0x0080;

        src0_u[3] = 0x0200;
        src1_u[3] = 0x0100;

        src0_u[4] = 0x0400;
        src1_u[4] = 0x0080;

        src0_u[5] = 0x0400;
        src1_u[5] = 0x0100;

        src0_u[6] = 0x0800;
        src1_u[6] = 0x0080;

        src0_u[7] = 0x0800;
        src1_u[7] = 0x0100;

        vSrc0 = vld1q_u16(src0_u);
        vSrc1 = vld1q_u16(src1_u);

        uint8x16_t vDst_h = vraddhn_high_u16(vDst_l, vSrc0, vSrc1);

        vst1q_u8(tmpDst_u, vDst_h);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)tmpDst_u[i] << std::endl;
        }
        for (int32_t i = 8; i < 16; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "(( " << (int32_t)src0_u[i - 8] << " + " << (int32_t)src1_u[i - 8] << " ) + " << (1 << 7)
                      << ") >> 8 = " << (int32_t)tmpDst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vraddhn_s16]" << std::endl;

        src0_s[0] = 0x0000;
        src1_s[0] = 0x0100;

        src0_s[1] = 0xfe00;
        src1_s[1] = 0x0100;

        src0_s[2] = 0xff00;
        src1_s[2] = 0x0100;

        src0_s[3] = 0x0001;
        src1_s[3] = 0x0001;

        src0_s[4] = 0x0001;
        src1_s[4] = 0x00fe;

        src0_s[5] = 0x0001;
        src1_s[5] = 0x00ff;

        src0_s[6] = 0x0040;
        src1_s[6] = 0x0040;

        src0_s[7] = 0xff00;
        src1_s[7] = 0x0080;

        int8_t *tmpDst_s = (int8_t *)dst_s;

        int16x8_t vSrc0 = vld1q_s16(src0_s);
        int16x8_t vSrc1 = vld1q_s16(src1_s);

        int8x8_t vDst_l = vraddhn_s16(vSrc0, vSrc1);

        vst1_s8(tmpDst_s, vDst_l);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "(( " << (int32_t)src0_s[i] << " + " << (int32_t)src1_s[i] << " ) + " << (1 << 7)
                      << ") >> 8 = " << (int32_t)tmpDst_s[i] << std::endl;
        }
        std::cout << std::endl;

        std::cout << "[vraddhn_high_s16]" << std::endl;

        src0_s[0] = 0x0100;
        src1_s[0] = 0x0080;

        src0_s[1] = 0x0100;
        src1_s[1] = 0x0100;

        src0_s[2] = 0x0200;
        src1_s[2] = 0x0080;

        src0_s[3] = 0x0200;
        src1_s[3] = 0x0100;

        src0_s[4] = 0x0400;
        src1_s[4] = 0x0080;

        src0_s[5] = 0x0400;
        src1_s[5] = 0x0100;

        src0_s[6] = 0x0800;
        src1_s[6] = 0x0080;

        src0_s[7] = 0x0800;
        src1_s[7] = 0x0100;

        vSrc0 = vld1q_s16(src0_s);
        vSrc1 = vld1q_s16(src1_s);

        int8x16_t vDst_h = vraddhn_high_s16(vDst_l, vSrc0, vSrc1);

        vst1q_s8(tmpDst_s, vDst_h);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)tmpDst_s[i] << std::endl;
        }
        for (int32_t i = 8; i < 16; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "(( " << (int32_t)src0_s[i - 8] << " + " << (int32_t)src1_s[i - 8] << " ) + " << (1 << 7)
                      << ") >> 8 = " << (int32_t)tmpDst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}