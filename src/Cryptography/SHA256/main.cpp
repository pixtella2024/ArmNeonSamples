#include <assert.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>

#include "Sha256Neon.h"
#include "Sha256Ref.h"

#define DATA_SIZE_MAX (1024 * 1024 * 16)

uint8_t g_testData[DATA_SIZE_MAX];

int main(int argc, char *argv[]) {
    if (argc < 6) {
        std::cout << "argument error" << std::endl;
        return -1;
    }
    const std::string outputDir = std::string(argv[1]) + "/";
    const int32_t     minSize   = atoi(argv[2]);
    const int32_t     maxSize   = atoi(argv[3]);
    const int32_t     testCnt   = atoi(argv[4]);
    const int32_t     inputSeed = atoi(argv[5]);

    assert(minSize > 0 && minSize <= DATA_SIZE_MAX);
    assert(maxSize > 0 && maxSize <= DATA_SIZE_MAX);
    assert(minSize <= maxSize);
    assert(testCnt > 0);

    const uint64_t dataSizeDiff = (uint64_t)(maxSize - minSize);

    uint64_t seed;
    if (inputSeed < 0) {
        std::random_device seedGen;
        seed = seedGen();
    } else {
        seed = (uint64_t)inputSeed;
    }
    std::mt19937_64 mt64(seed);
    std::cout << "seed: " << seed << std::endl;

    std::string   resultFileName = outputDir + "result.csv";
    std::ofstream resultFile;
    resultFile.open(resultFileName, std::ios::out | std::ios::trunc);

    resultFile << "FileName,FileSize,ResultHash,RefTime[us],NeonTime[us],ratio" << std::endl;

    uint32_t hash[8];
    Sha256  *p_ref  = new Sha256Ref();
    Sha256  *p_neon = new Sha256Neon();
    for (int testId = 0; testId < testCnt; testId++) {
        printf("TEST ID = %d\n", testId);

        const uint32_t dataSize        = (uint32_t)(mt64() % dataSizeDiff) + (uint32_t)minSize;
        uint64_t      *p_TmpTestData64 = (uint64_t *)g_testData;
        for (int32_t i = 0; i < (dataSize >> 3); ++i) {
            *p_TmpTestData64++ = mt64();
        }
        uint8_t *p_TmpTestDate8 = (uint8_t *)p_TmpTestData64;
        for (int32_t i = 0; i < (dataSize & 7); ++i) {
            *p_TmpTestDate8++ = (uint8_t)(mt64() & 0xFF);
        }

        std::string   fileName = std::to_string(testId) + ".bin";
        std::string   filePath = outputDir + fileName;
        std::ofstream fout;
        fout.open(filePath, std::ios::out | std::ios::binary | std::ios::trunc);
        if (!fout) {
            std::cout << "error: file open (" << fileName << ")" << std::endl;
            continue;
        }

        fout.write((char *)g_testData, dataSize);
        fout.close();

        p_ref->CalcHach(g_testData, dataSize);
        p_neon->CalcHach(g_testData, dataSize);

        const std::string refHashVal  = p_ref->GetHashVal();
        const std::string neonHashVal = p_neon->GetHashVal();
        if (refHashVal == neonHashVal) {
            const int32_t refProcTime  = p_ref->GetProcTime();
            const int32_t neonProcTime = p_neon->GetProcTime();
            const double  ratio        = (double)refProcTime / (double)neonProcTime;

            std::cout << refHashVal << std::endl;
            std::cout << "Data size: " << dataSize << std::endl;
            std::cout << "Ref : " << refProcTime << "[us]" << std::endl;
            std::cout << "Neon: " << neonProcTime << "[us]" << std::endl;
            std::cout << "Ratio: " << ratio << std::endl;

            resultFile << fileName << ",";
            resultFile << dataSize << ",";
            resultFile << refHashVal << ",";
            resultFile << refProcTime << ",";
            resultFile << neonProcTime << ",";
            resultFile << ratio << std::endl;
        } else {
            std::cout << "results don't match" << std::endl;
            std::cout << "Ref : " << refHashVal << std::endl;
            std::cout << "Neon: " << neonHashVal << std::endl;
            break;
        }
        std::cout << std::endl;
    }

    resultFile.close();
    delete (p_ref);
    delete (p_neon);

    printf("Done\n");
    return 0;
}