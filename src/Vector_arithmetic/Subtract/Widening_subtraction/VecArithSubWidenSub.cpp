#include <iostream>
#include <stdint.h>

#include <arm_neon.h>

int main(int argc, char *argv[]) {
    std::cout << "\"Vector arithmetic / Subtract / Widening subtraction\" の intrinsic 関数 サンプルコード"
              << std::endl;

    uint16_t src0_u[] = {0, 1, UINT16_MAX - 1, UINT16_MAX, 2, 2, 1, 0};
    uint16_t src1_u[] = {1, 1, 1, 1, 0, 1, 1, 1};
    uint32_t src2_u[] = {0, 1, UINT32_MAX - 1, UINT32_MAX, 2, UINT32_MAX, 2, 0};
    uint32_t dst_u[4];

    int16_t src0_s[] = {0, -1, INT16_MAX, INT16_MIN, -2, 2, 2, -2};
    int16_t src1_s[] = {-1, 1, -1, 1, 0, -1, INT16_MAX, INT16_MIN};
    int32_t src2_s[] = {0, -1, INT32_MAX, INT32_MIN, 2, INT32_MAX, INT32_MIN, 2};
    int32_t dst_s[4];

    // vsubl_xxx の動作
    { // unsigned
        std::cout << "[vsubl_u16]" << std::endl;

        uint16x4_t vSrc0 = vld1_u16(src0_u);
        uint16x4_t vSrc1 = vld1_u16(src1_u);

        uint32x4_t vDst = vsubl_u16(vSrc0, vSrc1);

        vst1q_u32(dst_u, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_u[i] << " - " << (int32_t)src1_u[i] << " = " << dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vsubl_s16]" << std::endl;

        int16x4_t vSrc0 = vld1_s16(src0_s);
        int16x4_t vSrc1 = vld1_s16(src1_s);

        int32x4_t vDst = vsubl_s16(vSrc0, vSrc1);

        vst1q_s32(dst_s, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_s[i] << " - " << (int32_t)src1_s[i] << " = " << dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vsubl_high_xxx の動作
    { // unsigned
        std::cout << "[vsubl_high_u16]" << std::endl;

        uint16x8_t vSrc0 = vld1q_u16(src0_u);
        uint16x8_t vSrc1 = vld1q_u16(src1_u);

        uint32x4_t vDst = vsubl_high_u16(vSrc0, vSrc1);

        vst1q_u32(dst_u, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_u[i + 4] << " - " << (int32_t)src1_u[i + 4] << " = " << dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vsubl_high_s16]" << std::endl;

        int16x8_t vSrc0 = vld1q_s16(src0_s);
        int16x8_t vSrc1 = vld1q_s16(src1_s);

        int32x4_t vDst = vsubl_high_s16(vSrc0, vSrc1);

        vst1q_s32(dst_s, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << (int32_t)src0_s[i + 4] << " - " << (int32_t)src1_s[i + 4] << " = " << dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vsubw_xxx の動作
    { // unsigned
        std::cout << "[vsubw_u16]" << std::endl;

        uint32x4_t vSrc0 = vld1q_u32(src2_u);
        uint16x4_t vSrc1 = vld1_u16(src1_u);

        uint32x4_t vDst = vsubw_u16(vSrc0, vSrc1);

        vst1q_u32(dst_u, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << src2_u[i] << " - " << (int32_t)src1_u[i] << " = " << dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vsubw_s16]" << std::endl;

        int32x4_t vSrc0 = vld1q_s32(src2_s);
        int16x4_t vSrc1 = vld1_s16(src1_s);

        int32x4_t vDst = vsubw_s16(vSrc0, vSrc1);

        vst1q_s32(dst_s, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << src2_s[i] << " - " << (int32_t)src1_s[i] << " = " << dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    // vsubw_high_xxx の動作
    { // unsigned
        std::cout << "[vsubw_high_u16]" << std::endl;

        uint32x4_t vSrc0 = vld1q_u32(&src2_u[4]);
        uint16x8_t vSrc1 = vld1q_u16(src1_u);

        uint32x4_t vDst = vsubw_high_u16(vSrc0, vSrc1);

        vst1q_u32(dst_u, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << src2_u[i + 4] << " - " << (int32_t)src1_u[i + 4] << " = " << dst_u[i] << std::endl;
        }
        std::cout << std::endl;
    }
    { // signed
        std::cout << "[vsubw_high_s16]" << std::endl;

        int32x4_t vSrc0 = vld1q_s32(&src2_s[4]);
        int16x8_t vSrc1 = vld1q_s16(src1_s);

        int32x4_t vDst = vsubw_high_s16(vSrc0, vSrc1);

        vst1q_s32(dst_s, vDst);

        for (int32_t i = 0; i < 4; i++) {
            std::cout << "[" << i << "] ";
            std::cout << src2_s[i + 4] << " - " << (int32_t)src1_s[i + 4] << " = " << dst_s[i] << std::endl;
        }
        std::cout << std::endl;
    }

    return 0;
}