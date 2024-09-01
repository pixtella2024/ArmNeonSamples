# `Cryptography / SHA256` の intrinsic 関数 サンプルコード

## 実装内容

指定した範囲のサイズ (16MB が上限) のバイナリファイルをランダム値で生成して、そのハッシュ値を SHA-256 で算出する。  
単純に実装したコードと Neon で高速化実装したコードのそれぞれで実行および処理時間測定を行い、結果と CSV ファイルに出力する。  
実行コマンドは下記の通り

```sh
./sha256arm outputDir minSize maxSize testCnt inputSeed
```
- outputDir
    - 出力先ディレクトリ
        - 生成したバイナリファイルと結果の CSV ファイルが出力される
- minSize
    - 生成するバイナリファイルのサイズ下限値
- maxSize
    - 生成するバイナリファイルのサイズ上限値
- testCnt
    - テストの実行数
- inputSeed
    - ランダム値のシード

## 評価

### 実行環境

- マシン: Raspberry Pi 5
    - CPU: Cortex-A76 (4コア)
        - 処理時間測定のためクロック周波数は 1.5GHz に固定
    - メモリ: LPDDR4X-4267 SDRAM (4GB)
- ストレージ: BUFFALO SSD-PSTU3A
    - 容量: 1TB
- OS: Ubuntu 24.04 LTS
- コンパイラ: Ubuntu clang version 18.1.3 

### 実行結果

上記の環境において、下記のコマンドを実行した。(512KB ~ 16MB で 1000 パターン)

```sh
./sha256arm output/ 524288 16777216 1000 0
```

得られた結果が同封の `/output/result.csv` である。  
高速化率をまとめると、平均で 7.2 倍程度高速化できていることがわかる。  
