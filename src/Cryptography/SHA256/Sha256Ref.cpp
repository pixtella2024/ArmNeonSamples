#include "Sha256Ref.h"
#include <assert.h>
#include <chrono>
#include <cmath>
#include <string.h>

Sha256Ref::Sha256Ref() {}

Sha256Ref::~Sha256Ref() {}

uint32_t Sha256Ref::ReadBigEndian(const uint8_t *p_data) {
    uint32_t val  = (uint32_t)(p_data[0]) << (8 * 3);
    val          += (uint32_t)(p_data[1]) << (8 * 2);
    val          += (uint32_t)(p_data[2]) << (8 * 1);
    val          += (uint32_t)(p_data[3]);

    return val;
}

uint32_t Sha256Ref::RotR(const uint32_t val, const int32_t shift) { return (val >> shift) | (val << (32 - shift)); }

uint32_t Sha256Ref::CalcLSigma0(const uint32_t val) { return (RotR(val, 7) ^ RotR(val, 18) ^ (val >> 3)); }

uint32_t Sha256Ref::CalcLSigma1(const uint32_t val) { return (RotR(val, 17) ^ RotR(val, 19) ^ (val >> 10)); }

uint32_t Sha256Ref::CalcUSigma0(const uint32_t val) { return (RotR(val, 2) ^ RotR(val, 13) ^ RotR(val, 22)); }

uint32_t Sha256Ref::CalcUSigma1(const uint32_t val) { return (RotR(val, 6) ^ RotR(val, 11) ^ RotR(val, 25)); }

void Sha256Ref::CalcWord(uint32_t *p_wt) {
    uint32_t wt  = CalcLSigma1(p_wt[-2]);
    wt          += p_wt[-7];
    wt          += CalcLSigma0(p_wt[-15]);
    wt          += p_wt[-16];

    p_wt[0] = wt;
}

void Sha256Ref::CalcBlock(const uint8_t *p_blockData, uint32_t *hash) {
    uint32_t word[64];
    for (int32_t t = 0; t < 16; ++t) {
        word[t] = ReadBigEndian(&p_blockData[4 * t]);
    }
    for (int32_t t = 16; t < 64; ++t) {
        CalcWord(&word[t]);
    }

    uint32_t a = hash[0];
    uint32_t b = hash[1];
    uint32_t c = hash[2];
    uint32_t d = hash[3];
    uint32_t e = hash[4];
    uint32_t f = hash[5];
    uint32_t g = hash[6];
    uint32_t h = hash[7];

    for (int32_t t = 0; t < 64; ++t) {
        const uint32_t tmp0 = ((a & b) ^ (a & c) ^ (b & c)) + CalcUSigma0(a);
        const uint32_t tmp1 = h + CalcUSigma1(e) + ((e & f) ^ (~e & g)) + this->m_k[t] + word[t];

        h = g;
        g = f;
        f = e;
        e = d + tmp1;
        d = c;
        c = b;
        b = a;
        a = tmp0 + tmp1;
    }

    hash[0] += a;
    hash[1] += b;
    hash[2] += c;
    hash[3] += d;
    hash[4] += e;
    hash[5] += f;
    hash[6] += g;
    hash[7] += h;
}

void Sha256Ref::CalcHach(const uint8_t *messageData, const int32_t messageLen) {
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
    memcpy(paddingAreaData, p_blockData, remainMessageLen);
    paddingAreaData[remainMessageLen] = 0x80;
    for (int32_t i = remainMessageLen + 1; i < (remainDataLen - 8); ++i) {
        paddingAreaData[i] = 0;
    }
    uint64_t bits                      = (uint64_t)messageLen * 8ULL;
    paddingAreaData[remainDataLen - 8] = (uint8_t)((bits & 0xff00000000000000ULL) >> (7 * 8));
    paddingAreaData[remainDataLen - 7] = (uint8_t)((bits & 0x00ff000000000000ULL) >> (6 * 8));
    paddingAreaData[remainDataLen - 6] = (uint8_t)((bits & 0x0000ff0000000000ULL) >> (5 * 8));
    paddingAreaData[remainDataLen - 5] = (uint8_t)((bits & 0x000000ff00000000ULL) >> (4 * 8));
    paddingAreaData[remainDataLen - 4] = (uint8_t)((bits & 0x00000000ff000000ULL) >> (3 * 8));
    paddingAreaData[remainDataLen - 3] = (uint8_t)((bits & 0x0000000000ff0000ULL) >> (2 * 8));
    paddingAreaData[remainDataLen - 2] = (uint8_t)((bits & 0x000000000000ff00ULL) >> (1 * 8));
    paddingAreaData[remainDataLen - 1] = (uint8_t)((bits & 0x00000000000000ffULL));

    for (int32_t i = 0; i < remainDataLen; i += 64) {
        CalcBlock(&paddingAreaData[i], hash);
    }

    auto                                      end      = std::chrono::system_clock::now();
    std::chrono::duration<double, std::micro> procTime = end - start;
    this->m_procTime                                   = (int32_t)(std::round(procTime.count()));
}