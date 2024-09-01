#include <iostream>
#include <limits>
#include <stdint.h>

#include <arm_neon.h>

int main(int argc, char *argv[]) {
    std::cout << "\"Vector arithmetic / Subtract / Saturating subtract\" の intrinsic 関数 サンプルコード" << std::endl;

    uint16_t src0_u[] = {2, 2, 2, 2, 2, 2, 2, 2};
    uint16_t src1_u[] = {1, 2, 3, 4, 1, UINT16_MAX - 2, UINT16_MAX - 1, UINT16_MAX};
    uint16_t dst_u[8];

    int16_t src0_s[] = {-2, -2, 2, 2, -100, -100, 100, 100};
    int16_t src1_s[] = {1, INT16_MAX, -1, INT16_MIN, 1, INT16_MAX, -1, INT16_MIN};
    int16_t dst_s[8];

    // vqsub_xxx の動作
    { // unsigned
        std::cout << "[vqsub_u16]" << std::endl;

        uint16x4_t vSrc0 = vld1_u16(src0_u);
        uint16x4_t vSrc1 = vld1_u16(src1_u);

        uint16x4_t vDst = vqsub_u16(vSrc0, vSrc1);

        vst1_u16(dst_u, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_u[i] << " - " << (int32_t)src1_u[i] << " = " << (int32_t)dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vqsub_s16]" << std::endl;

        int16x4_t vSrc0 = vld1_s16(src0_s);
        int16x4_t vSrc1 = vld1_s16(src1_s);

        int16x4_t vDst = vqsub_s16(vSrc0, vSrc1);

        vst1_s16(dst_s, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_s[i] << " - " << (int32_t)src1_s[i] << " = " << (int32_t)dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vqsubq の動作
    { // unsigned
        std::cout << "[vqsubq_u16]" << std::endl;

        uint16x8_t vSrc0 = vld1q_u16(src0_u);
        uint16x8_t vSrc1 = vld1q_u16(src1_u);

        uint16x8_t vDst = vqsubq_u16(vSrc0, vSrc1);

        vst1q_u16(dst_u, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_u[i] << " - " << (int32_t)src1_u[i] << " = " << (int32_t)dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vqsubq_s16]" << std::endl;

        int16x8_t vSrc0 = vld1q_s16(src0_s);
        int16x8_t vSrc1 = vld1q_s16(src1_s);

        int16x8_t vDst = vqsubq_s16(vSrc0, vSrc1);

        vst1q_s16(dst_s, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_s[i] << " - " << (int32_t)src1_s[i] << " = " << (int32_t)dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vqsubb_u8, vqsubh_u16, vqsubs_u32, vqsubd_u64 の動作
    {
        std::cout << "[vqsubh_u16]" << std::endl;

        for (int32_t i = 0; i < 8; i++) {
            uint16_t dst = vqsubh_u16(src0_u[i], src1_u[i]);

            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_u[i] << " - " << (int32_t)src1_u[i] << " = " << (int32_t)dst << std::endl;
        }
        std::cout << std::endl;
    }
    // vqsubb_s8, vqsubh_s16, vqsubs_s32, vqsubd_s64 の動作
    {
        std::cout << "[vqsubh_s16]" << std::endl;
        for (int32_t i = 0; i < 8; i++) {
            int16_t dst = vqsubh_s16(src0_s[i], src1_s[i]);

            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_s[i] << " - " << (int32_t)src1_s[i] << " = " << (int32_t)dst << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}