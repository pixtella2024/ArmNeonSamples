#include <iostream>
#include <limits>
#include <stdint.h>

#include <arm_neon.h>

int main(int argc, char *argv[]) {
    std::cout << "\"Vector arithmetic / Add / Saturating addition\" の intrinsic 関数 サンプルコード" << std::endl;

    uint16_t src0_u[] = {0, 1, UINT16_MAX - 1, UINT16_MAX, 2, 2, 2, 2};
    uint16_t src1_u[] = {1, 1, 1, 1, 0, 1, UINT16_MAX - 1, UINT16_MAX};
    uint16_t dst_u[8];

    int16_t src0_s[] = {0, -1, INT16_MAX, INT16_MIN, -2, 2, 2, -2};
    int16_t src1_s[] = {-1, 1, 1, -1, 0, -1, INT16_MAX, INT16_MIN};
    int16_t dst_s[8];

    // vqadd_xxx の動作
    { // unsigned
        std::cout << "[vqadd_u16]" << std::endl;

        uint16x4_t vSrc0 = vld1_u16(src0_u);
        uint16x4_t vSrc1 = vld1_u16(src1_u);

        uint16x4_t vDst = vqadd_u16(vSrc0, vSrc1);

        vst1_u16(dst_u, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_u[i] << " + " << (int32_t)src1_u[i] << " = " << (int32_t)dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vqadd_s16]" << std::endl;

        int16x4_t vSrc0 = vld1_s16(src0_s);
        int16x4_t vSrc1 = vld1_s16(src1_s);

        int16x4_t vDst = vqadd_s16(vSrc0, vSrc1);

        vst1_s16(dst_s, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_s[i] << " + " << (int32_t)src1_s[i] << " = " << (int32_t)dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vqaddq の動作
    { // unsigned
        std::cout << "[vqaddq_u16]" << std::endl;

        uint16x8_t vSrc0 = vld1q_u16(src0_u);
        uint16x8_t vSrc1 = vld1q_u16(src1_u);

        uint16x8_t vDst = vqaddq_u16(vSrc0, vSrc1);

        vst1q_u16(dst_u, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_u[i] << " + " << (int32_t)src1_u[i] << " = " << (int32_t)dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vqaddq_s16]" << std::endl;

        int16x8_t vSrc0 = vld1q_s16(src0_s);
        int16x8_t vSrc1 = vld1q_s16(src1_s);

        int16x8_t vDst = vqaddq_s16(vSrc0, vSrc1);

        vst1q_s16(dst_s, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_s[i] << " + " << (int32_t)src1_s[i] << " = " << (int32_t)dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vqaddb_u8, vqaddh_u16, vqadds_u32, vqaddd_u64 の動作
    {
        std::cout << "[vqaddh_u16]" << std::endl;

        for (int32_t i = 0; i < 8; i++) {
            uint16_t dst = vqaddh_u16(src0_u[i], src1_u[i]);

            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_u[i] << " + " << (int32_t)src1_u[i] << " = " << (int32_t)dst << std::endl;
        }
        std::cout << std::endl;
    }
    // vqaddb_s8, vqaddh_s16, vqadds_s32, vqaddd_s64 の動作
    {
        std::cout << "[vqaddh_s16]" << std::endl;
        for (int32_t i = 0; i < 8; i++) {
            int16_t dst = vqaddh_s16(src0_s[i], src1_s[i]);

            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_s[i] << " + " << (int32_t)src1_s[i] << " = " << (int32_t)dst << std::endl;
        }
        std::cout << std::endl;
    }

    src0_u[0] = UINT16_MAX;
    src0_u[1] = 0;
    src0_s[1] = INT16_MIN;

    // vsqadd_uxx の動作
    {
        std::cout << "[vsqadd_u16]" << std::endl;

        uint16x4_t vSrcU = vld1_u16(src0_u);
        int16x4_t  vSrcS = vld1_s16(src0_s);

        uint16x4_t vDst = vsqadd_u16(vSrcU, vSrcS);

        vst1_u16(dst_u, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_u[i] << " + " << (int32_t)src0_s[i] << " = " << (int32_t)dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vuqadd_sxx の動作
    {
        std::cout << "[vuqadd_s16]" << std::endl;

        uint16x4_t vSrcU = vld1_u16(src0_u);
        int16x4_t  vSrcS = vld1_s16(src0_s);

        int16x4_t vDst = vuqadd_s16(vSrcS, vSrcU);

        vst1_s16(dst_s, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_s[i] << " + " << (int32_t)src0_u[i] << " = " << (int32_t)dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vsqaddq_uxx の動作
    {
        std::cout << "[vsqaddq_u16]" << std::endl;

        uint16x8_t vSrcU = vld1q_u16(src0_u);
        int16x8_t  vSrcS = vld1q_s16(src0_s);

        uint16x8_t vDst = vsqaddq_u16(vSrcU, vSrcS);

        vst1q_u16(dst_u, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_u[i] << " + " << (int32_t)src0_s[i] << " = " << (int32_t)dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vuqaddq_sxx の動作
    {
        std::cout << "[vuqaddq_s16]" << std::endl;

        uint16x8_t vSrcU = vld1q_u16(src0_u);
        int16x8_t  vSrcS = vld1q_s16(src0_s);

        int16x8_t vDst = vuqaddq_s16(vSrcS, vSrcU);

        vst1q_s16(dst_s, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_s[i] << " + " << (int32_t)src0_u[i] << " = " << (int32_t)dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vsqaddb_u8, vsqaddh_u16, vsqadds_u32, vsqaddd_u64 の動作
    {
        std::cout << "[vsqaddh_u16]" << std::endl;

        for (int32_t i = 0; i < 8; i++) {
            uint16_t dst = vsqaddh_u16(src0_u[i], src0_s[i]);

            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_u[i] << " + " << (int32_t)src0_s[i] << " = " << (int32_t)dst << std::endl;
        }
        std::cout << std::endl;
    }
    // vuqaddb_s8, vuqaddh_s16, vuqadds_s32, vuqaddd_s64 の動作
    {
        std::cout << "[vuqaddh_s16]" << std::endl;
        for (int32_t i = 0; i < 8; i++) {
            int16_t dst = vuqaddh_s16(src0_s[i], src0_u[i]);

            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_s[i] << " + " << (int32_t)src0_u[i] << " = " << (int32_t)dst << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}