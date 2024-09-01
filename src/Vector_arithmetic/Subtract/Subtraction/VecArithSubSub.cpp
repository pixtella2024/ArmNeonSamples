#include <iostream>
#include <limits>
#include <stdint.h>

#include <arm_neon.h>

int main(int argc, char *argv[]) {
    std::cout << "\"Vector arithmetic / Subtract / Subtraction\" の intrinsic 関数 サンプルコード" << std::endl;

    uint16_t src0_u[] = {0, 1, UINT16_MAX - 1, UINT16_MAX, 2, 2, 2, 2};
    uint16_t src1_u[] = {1, 1, 1, 1, 0, 1, UINT16_MAX - 1, UINT16_MAX};
    uint16_t dst_u[8];

    int16_t src0_s[] = {0, -1, INT16_MAX, INT16_MIN, -2, 2, 2, -2};
    int16_t src1_s[] = {-1, 1, -1, 1, 0, -1, INT16_MAX, INT16_MIN};
    int16_t dst_s[8];

    // vsub_xxx の動作
    { // unsigned
        std::cout << "[vsub_u16]" << std::endl;

        uint16x4_t vSrc0 = vld1_u16(src0_u);
        uint16x4_t vSrc1 = vld1_u16(src1_u);

        uint16x4_t vDst = vsub_u16(vSrc0, vSrc1);

        vst1_u16(dst_u, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_u[i] << " - " << (int32_t)src1_u[i] << " = " << (int32_t)dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vsub_s16]" << std::endl;

        int16x4_t vSrc0 = vld1_s16(src0_s);
        int16x4_t vSrc1 = vld1_s16(src1_s);

        int16x4_t vDst = vsub_s16(vSrc0, vSrc1);

        vst1_s16(dst_s, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_s[i] << " - " << (int32_t)src1_s[i] << " = " << (int32_t)dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vsubq_xxx の動作
    { // unsigned
        std::cout << "[vsubq_u16]" << std::endl;

        uint16x8_t vSrc0 = vld1q_u16(src0_u);
        uint16x8_t vSrc1 = vld1q_u16(src1_u);

        uint16x8_t vDst = vsubq_u16(vSrc0, vSrc1);

        vst1q_u16(dst_u, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_u[i] << " - " << (int32_t)src1_u[i] << " = " << (int32_t)dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vsubq_s16]" << std::endl;

        int16x8_t vSrc0 = vld1q_s16(src0_s);
        int16x8_t vSrc1 = vld1q_s16(src1_s);

        int16x8_t vDst = vsubq_s16(vSrc0, vSrc1);

        vst1q_s16(dst_s, vDst);

        for (int32_t i = 0; i < 8; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_s[i] << " - " << (int32_t)src1_s[i] << " = " << (int32_t)dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vsubd_xxx の動作
    { // unsigned
        std::cout << "[vsubd_u64]" << std::endl;

        uint64_t src0 = 1;
        uint64_t src1 = 2;

        uint64_t dst = vsubd_u64(src0, src1);

        std::cout << src0 << " - " << src1 << " = " << dst << std::endl;
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vsubd_s64]" << std::endl;

        int64_t src0 = INT64_MIN;
        int64_t src1 = 1;

        int64_t dst = vsubd_s64(src0, src1);

        std::cout << src0 << " - " << src1 << " = " << dst << std::endl;
        std::cout << std::endl;
    }

    return 0;
}