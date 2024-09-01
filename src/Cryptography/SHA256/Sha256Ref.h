#ifndef __SHA_256_REF_H__
#define __SHA_256_REF_H__

#include "Sha256.h"

class Sha256Ref : public Sha256 {
  private:
    uint32_t ReadBigEndian(const uint8_t *p_data);
    uint32_t RotR(const uint32_t val, const int32_t shift);
    uint32_t CalcLSigma0(const uint32_t val);
    uint32_t CalcLSigma1(const uint32_t val);
    uint32_t CalcUSigma0(const uint32_t val);
    uint32_t CalcUSigma1(const uint32_t val);
    void     CalcWord(uint32_t *p_wt);
    void     CalcBlock(const uint8_t *p_blockData, uint32_t *hash);

  public:
    void CalcHach(const uint8_t *messageData, const int32_t messageLen);
    Sha256Ref(/* args */);
    ~Sha256Ref();
};

#endif // __SHA_256_REF_H__