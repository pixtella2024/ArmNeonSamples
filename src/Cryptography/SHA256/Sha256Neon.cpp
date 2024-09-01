#include "Sha256Neon.h"
#include <assert.h>
#include <chrono>
#include <cmath>
#include <string.h>

#include <arm_neon.h>

Sha256Neon::Sha256Neon() {}

Sha256Neon::~Sha256Neon() {}

void Sha256Neon::CalcBlock(const uint8_t *p_blockData, uint32_t *hash) {
    uint32_t word[64];
    for (int32_t t = 0; t < 16; t += 4) {
        const uint8x16_t vBlockDataBig = vld1q_u8(&p_blockData[4 * t]);
        const uint8x16_t vWord         = vrev32q_u8(vBlockDataBig);
        vst1q_u32(&word[t], vreinterpretq_u32_u8(vWord));
    }

    uint32_t   test    = vsha1h_u32(0);
    uint32x4_t vW0_3   = vld1q_u32(&word[0]);
    uint32x4_t vW4_7   = vld1q_u32(&word[4]);
    uint32x4_t vW8_11  = vld1q_u32(&word[8]);
    uint32x4_t vW12_15 = vld1q_u32(&word[12]);
    uint32x4_t vW16_19 = vsha256su0q_u32(vW0_3, vW4_7);
    vW16_19            = vsha256su1q_u32(vW16_19, vW8_11, vW12_15);
    vst1q_u32(&word[16], vW16_19);

    for (int32_t t = 20; t < 64; t += 4) {
        vW0_3   = vW4_7;
        vW4_7   = vW8_11;
        vW8_11  = vW12_15;
        vW12_15 = vW16_19;
        vW16_19 = vsha256su0q_u32(vW0_3, vW4_7);
        vW16_19 = vsha256su1q_u32(vW16_19, vW8_11, vW12_15);
        vst1q_u32(&word[t], vW16_19);
    }

    uint32x4_t vUpdatedHashAbcd = vld1q_u32(&hash[0]);
    uint32x4_t vUpdatedHashEfgh = vld1q_u32(&hash[4]);
    uint32x4_t vHashAbcd, vHashEfgh;
    for (int32_t t = 0; t < 64; t += 4) {
        vHashAbcd = vUpdatedHashAbcd;
        vHashEfgh = vUpdatedHashEfgh;

        uint32x4_t vWord = vld1q_u32(&word[t]);
        uint32x4_t vK    = vld1q_u32(&this->m_k[t]);
        uint32x4_t vWK   = vaddq_u32(vWord, vK);

        vUpdatedHashAbcd = vsha256hq_u32(vHashAbcd, vHashEfgh, vWK);
        vUpdatedHashEfgh = vsha256h2q_u32(vHashEfgh, vHashAbcd, vWK);
    }
    vHashAbcd = vaddq_u32(vld1q_u32(&hash[0]), vUpdatedHashAbcd);
    vHashEfgh = vaddq_u32(vld1q_u32(&hash[4]), vUpdatedHashEfgh);

    vst1q_u32(&hash[0], vHashAbcd);
    vst1q_u32(&hash[4], vHashEfgh);
}

void Sha256Neon::CalcHach(const uint8_t *messageData, const int32_t messageLen) {
    assert(messageLen > 0);

    auto start = std::chrono::system_clock::now();

    InitHash();

    uint32_t *hash = m_hash;

    const int32_t  paddLen             = CalcPaddingLen(messageLen);
    const int32_t  inputDataLen        = messageLen + paddLen;
    const int32_t  blockCnt            = inputDataLen >> 6;
    const int32_t  messageBlockLoopCnt = messageLen >> 6;
    const int32_t  remainMessageLen    = messageLen & 0x3f;
    const uint8_t *p_blockData         = messageData;

    for (int32_t i = 0; i < messageBlockLoopCnt; ++i) {
        CalcBlock(p_blockData, hash);
        p_blockData += 64;
    }

    const int32_t remainDataLen   = inputDataLen - (messageLen - remainMessageLen);
    uint8_t      *paddingAreaData = this->m_paddingAreaData;
    const int32_t copyLoopCnt     = (remainMessageLen + 15) >> 4;
    for (int32_t i = 0; i < copyLoopCnt; ++i) {
        uint8x16_t vBlockData = vld1q_u8(&p_blockData[16 * i]);
        vst1q_u8(&paddingAreaData[16 * i], vBlockData);
    }
    paddingAreaData[remainMessageLen] = 0x80;
    const int32_t separator           = ((remainMessageLen + 1 + 7) & (~7));
    for (int32_t i = remainMessageLen + 1; i < separator; ++i) {
        paddingAreaData[i] = 0;
    }
    uint64_t *p_paddingAreaData64 = (uint64_t *)(&paddingAreaData[separator]);
    for (int32_t i = separator; i < (remainDataLen - 8); i += 8) {
        *p_paddingAreaData64++ = 0ULL;
    }
    uint64_t   bits     = (uint64_t)messageLen * 8ULL;
    uint64x1_t vBits    = vdup_n_u64(bits);
    uint8x8_t  vRevBits = vrev64_u8(vreinterpret_u8_u64(vBits));
    vst1_u8(&paddingAreaData[remainDataLen - 8], vRevBits);

    for (int32_t i = 0; i < remainDataLen; i += 64) {
        CalcBlock(&paddingAreaData[i], hash);
    }

    auto                                      end      = std::chrono::system_clock::now();
    std::chrono::duration<double, std::micro> procTime = end - start;
    this->m_procTime                                   = (int32_t)(std::round(procTime.count()));
}