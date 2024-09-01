#ifndef __SHA_256_H__
#define __SHA_256_H__

#include <stdint.h>
#include <string>

class Sha256 {
  protected:
    uint32_t              m_hash[8];
    uint8_t               m_paddingAreaData[128];
    static const uint32_t m_k[];
    int32_t               m_procTime; // 処理時間 [us]

    void    InitHash();
    int32_t CalcPaddingLen(const int32_t messageLen);

  public:
    virtual ~Sha256(){};
    virtual void CalcHach(const uint8_t *inputData, const int32_t messageLen) = 0;
    std::string  GetHashVal();
    int32_t      GetProcTime();
};

#endif // __SHA_256_H__