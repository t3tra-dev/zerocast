[[英語/English](README.md)]

# zerocast

**"zerocast"** は史上最高の圧縮率を誇る _非可逆_ 圧縮技術です。

zerocast では全てのデータを 0 byte に圧縮することで "未定義" 倍の圧縮率を実現します。データの展開には無限の猿を用いることで有限時間以内に復元することが可能です。

ええと...もちろんこれはジョークだぜ！

## usage

このリポジトリでは `zerocast` CLI が実装されています。使用方法は以下の通りです:

```sh
# ヘルプ (エイリアス: --help, -h)
zerocast help

# 圧縮
zerocast compress <input_path> [output_path]

# 復元
zerocast decompress <input_path> [output_path]

# バージョン (エイリアス: --version, -v)
zerocast version
```

また、`libzerocast` C ライブラリを用いて zerocast の `zerocast_compress` 関数と `zerocast_decompress` 関数が `zerocast.h` から利用可能です。

各シグネチャは以下の通りです:

```c
ZEROCAST_API size_t zerocast_compress(const unsigned char *input_data,
                                      size_t input_size,
                                      unsigned char **out_data);

ZEROCAST_API int zerocast_decompress(const unsigned char *input_data,
                                     size_t input_size,
                                     unsigned char **out_data,
                                     size_t *out_size,
                                     FILE *error_stream);
```

## build & install

`zerocast` CLI は以下の方法でビルド・インストールできます:

```sh
# build
cmake -S . -B build && cmake --build build

# install
sudo cmake --install build
```

## run with Docker

Docker を使って以下のコマンドでも起動できます:

```sh
docker compose run --remove-orphans zerocast
```

以下のコマンドで `README.md` を圧縮できます:

```sh
docker compose run --remove-orphans zerocast zerocast compress README.md
```

圧縮後は `README.md_out` に保存されます。

## related works

- 無限の猿定理
- 神
- バックアップを取らなかった技術者達

ユーザー製作:

- [otoneko1102/amazing-compression-tech](https://github.com/otoneko1102/amazing-compression-tech)

## license

このプロジェクトはMITライセンスの元で公開されています。詳細については [LICENSE](LICENSE) ファイルをご覧ください。
