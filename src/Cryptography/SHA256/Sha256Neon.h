#ifndef __SHA_256_NEON_H__
#define __SHA_256_NEON_H__

#include "Sha256.h"

class Sha256Neon : public Sha256 {
  private:
    void CalcBlock(const uint8_t *p_blockData, uint32_t *hash);

  public:
    void CalcHach(const uint8_t *messageData, const int32_t messageLen);
    Sha256Neon(/* args */);
    ~Sha256Neon();
};

#endif // __SHA_256_NEON_H__