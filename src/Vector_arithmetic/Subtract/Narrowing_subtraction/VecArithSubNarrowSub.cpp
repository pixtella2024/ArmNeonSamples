#include <iostream>
#include <limits>
#include <stdint.h>

#include <arm_neon.h>

int main(int argc, char *argv[]) {
    std::cout << "\"Vector arithmetic / Subtract / Narrowing subtraction\" の intrinsic 関数 サンプルコード"
              << std::endl;

    uint16_t src0_u[] = {UINT16_MAX / 2 - 1, 1, UINT16_MAX - 1, UINT16_MAX, 2, 2, 2, 2};
    uint16_t src1_u[] = {1, 2, 1, 1, 0, 1, UINT16_MAX - 1, UINT16_MAX};
    uint16_t dst_u[8];

    int16_t src0_s[] = {0, -1, INT16_MIN, INT16_MAX, -2, 2, INT16_MIN, INT16_MAX};
    int16_t src1_s[] = {-1, 1, 1, -1, 0, -1, INT16_MAX, INT16_MIN};
    int16_t dst_s[8];

    // vhsub_xxx の動作
    { // unsigned
        std::cout << "[vhsub_u16]" << std::endl;

        uint16x4_t vSrc0 = vld1_u16(src0_u);
        uint16x4_t vSrc1 = vld1_u16(src1_u);

        uint16x4_t vDst = vhsub_u16(vSrc0, vSrc1);

        vst1_u16(dst_u, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_u[i] << " - " << (int32_t)src1_u[i] << ") >> 1 = " << (int32_t)dst_u[i]
                      << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vhsub_s16]" << std::endl;

        int16x4_t vSrc0 = vld1_s16(src0_s);
        int16x4_t vSrc1 = vld1_s16(src1_s);

        int16x4_t vDst = vhsub_s16(vSrc0, vSrc1);

        vst1_s16(dst_s, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_s[i] << " - " << (int32_t)src1_s[i] << ") >> 1 = " << (int32_t)dst_s[i]
                      << std::endl;
        }
        std::cout << std::endl;
    }

    // vhsubq_xxx の動作
    { // unsigned
        std::cout << "[vhsubq_u16]" << std::endl;

        uint16x8_t vSrc0 = vld1q_u16(src0_u);
        uint16x8_t vSrc1 = vld1q_u16(src1_u);

        uint16x8_t vDst = vhsubq_u16(vSrc0, vSrc1);

        vst1q_u16(dst_u, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_u[i] << " - " << (int32_t)src1_u[i] << ") >> 1 = " << (int32_t)dst_u[i]
                      << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vhsubq_s16]" << std::endl;

        int16x8_t vSrc0 = vld1q_s16(src0_s);
        int16x8_t vSrc1 = vld1q_s16(src1_s);

        int16x8_t vDst = vhsubq_s16(vSrc0, vSrc1);

        vst1q_s16(dst_s, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_s[i] << " - " << (int32_t)src1_s[i] << ") >> 1 = " << (int32_t)dst_s[i]
                      << std::endl;
        }
        std::cout << std::endl;
    }

    // vsubhn_xxx および vsubhn_high_xxx の動作
    { // unsigned
        std::cout << "[vsubhn_u16]" << std::endl;

        src0_u[0] = 0xffff;
        src1_u[0] = 0x0001;

        src0_u[1] = 0x0100;
        src1_u[1] = 0x0001;

        src0_u[2] = 0xff00;
        src1_u[2] = 0x0001;

        src0_u[3] = 0x0000;
        src1_u[3] = 0x0001;

        src0_u[4] = 0xff00;
        src1_u[4] = 0x0100;

        src0_u[5] = 0xff00;
        src1_u[5] = 0x00ff;

        src0_u[6] = 0xffff;
        src1_u[6] = 0x007f;

        src0_u[7] = 0xffff;
        src1_u[7] = 0x0080;

        uint8_t *tmpDst_u = (uint8_t *)dst_u;

        uint16x8_t vSrc0 = vld1q_u16(src0_u);
        uint16x8_t vSrc1 = vld1q_u16(src1_u);

        uint8x8_t vDst_l = vsubhn_u16(vSrc0, vSrc1);

        vst1_u8(tmpDst_u, vDst_l);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_u[i] << " - " << (int32_t)src1_u[i]
                      << " ) >> 8 = " << (int32_t)tmpDst_u[i] << std::endl;
        }
        std::cout << std::endl;

        std::cout << "[vsubhn_high_u16]" << std::endl;

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

        uint8x16_t vDst_h = vsubhn_high_u16(vDst_l, vSrc0, vSrc1);

        vst1q_u8(tmpDst_u, vDst_h);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)tmpDst_u[i] << std::endl;
        }
        for (int32_t i = 8; i < 16; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_u[i - 8] << " - " << (int32_t)src1_u[i - 8]
                      << " ) >> 8 = " << (int32_t)tmpDst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vsubhn_s16]" << std::endl;

        src0_s[0] = 0xffff;
        src1_s[0] = 0x0001;

        src0_s[1] = 0x0100;
        src1_s[1] = 0x0001;

        src0_s[2] = 0x7f00;
        src1_s[2] = 0x0001;

        src0_s[3] = 0x0000;
        src1_s[3] = 0x0001;

        src0_s[4] = 0x7fff;
        src1_s[4] = 0x007f;

        src0_s[5] = 0x7fff;
        src1_s[5] = 0x0080;

        src0_s[6] = 0xffff;
        src1_s[6] = 0x007f;

        src0_s[7] = 0xffff;
        src1_s[7] = 0x0080;

        int8_t *tmpDst_s = (int8_t *)dst_s;

        int16x8_t vSrc0 = vld1q_s16(src0_s);
        int16x8_t vSrc1 = vld1q_s16(src1_s);

        int8x8_t vDst_l = vsubhn_s16(vSrc0, vSrc1);

        vst1_s8(tmpDst_s, vDst_l);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_s[i] << " - " << (int32_t)src1_s[i]
                      << " ) >> 8 = " << (int32_t)tmpDst_s[i] << std::endl;
        }
        std::cout << std::endl;

        std::cout << "[vsubhn_high_s16]" << std::endl;

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

        int8x16_t vDst_h = vsubhn_high_s16(vDst_l, vSrc0, vSrc1);

        vst1q_s8(tmpDst_s, vDst_h);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)tmpDst_s[i] << std::endl;
        }
        for (int32_t i = 8; i < 16; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "( " << (int32_t)src0_s[i - 8] << " - " << (int32_t)src1_s[i - 8]
                      << " ) >> 8 = " << (int32_t)tmpDst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vrsubhn_xxx および vrsubhn_high_xxx の動作
    { // unsigned
        std::cout << "[vrsubhn_u16]" << std::endl;

        src0_u[0] = 0xffff;
        src1_u[0] = 0x0001;

        src0_u[1] = 0x0100;
        src1_u[1] = 0x0001;

        src0_u[2] = 0xff00;
        src1_u[2] = 0x0001;

        src0_u[3] = 0x0000;
        src1_u[3] = 0x0001;

        src0_u[4] = 0xff00;
        src1_u[4] = 0x0100;

        src0_u[5] = 0xff00;
        src1_u[5] = 0x00ff;

        src0_u[6] = 0xffff;
        src1_u[6] = 0x007f;

        src0_u[7] = 0xffff;
        src1_u[7] = 0x0080;

        uint8_t *tmpDst_u = (uint8_t *)dst_u;

        uint16x8_t vSrc0 = vld1q_u16(src0_u);
        uint16x8_t vSrc1 = vld1q_u16(src1_u);

        uint8x8_t vDst_l = vrsubhn_u16(vSrc0, vSrc1);

        vst1_u8(tmpDst_u, vDst_l);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "(( " << (int32_t)src0_u[i] << " - " << (int32_t)src1_u[i] << " ) + " << (1 << 7)
                      << ") >> 8 = " << (int32_t)tmpDst_u[i] << std::endl;
        }
        std::cout << std::endl;

        std::cout << "[vrsubhn_high_u16]" << std::endl;

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

        uint8x16_t vDst_h = vrsubhn_high_u16(vDst_l, vSrc0, vSrc1);

        vst1q_u8(tmpDst_u, vDst_h);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)tmpDst_u[i] << std::endl;
        }
        for (int32_t i = 8; i < 16; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "(( " << (int32_t)src0_u[i - 8] << " - " << (int32_t)src1_u[i - 8] << " ) + " << (1 << 7)
                      << ") >> 8 = " << (int32_t)tmpDst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vrsubhn_s16]" << std::endl;

        src0_s[0] = 0xffff;
        src1_s[0] = 0x0001;

        src0_s[1] = 0x0100;
        src1_s[1] = 0x0001;

        src0_s[2] = 0x7f00;
        src1_s[2] = 0x0001;

        src0_s[3] = 0x0000;
        src1_s[3] = 0x0001;

        src0_s[4] = 0x7fff;
        src1_s[4] = 0x007f;

        src0_s[5] = 0x7fff;
        src1_s[5] = 0x0080;

        src0_s[6] = 0xffff;
        src1_s[6] = 0x007f;

        src0_s[7] = 0xffff;
        src1_s[7] = 0x0080;

        int8_t *tmpDst_s = (int8_t *)dst_s;

        int16x8_t vSrc0 = vld1q_s16(src0_s);
        int16x8_t vSrc1 = vld1q_s16(src1_s);

        int8x8_t vDst_l = vrsubhn_s16(vSrc0, vSrc1);

        vst1_s8(tmpDst_s, vDst_l);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "(( " << (int32_t)src0_s[i] << " - " << (int32_t)src1_s[i] << " ) + " << (1 << 7)
                      << ") >> 8 = " << (int32_t)tmpDst_s[i] << std::endl;
        }
        std::cout << std::endl;

        std::cout << "[vrsubhn_high_s16]" << std::endl;

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

        int8x16_t vDst_h = vrsubhn_high_s16(vDst_l, vSrc0, vSrc1);

        vst1q_s8(tmpDst_s, vDst_h);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)tmpDst_s[i] << std::endl;
        }
        for (int32_t i = 8; i < 16; i++) {
            std::cout << "[" << i << "] ";
            std::cout << "(( " << (int32_t)src0_s[i - 8] << " - " << (int32_t)src1_s[i - 8] << " ) + " << (1 << 7)
                      << ") >> 8 = " << (int32_t)tmpDst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}