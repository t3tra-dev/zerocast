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

## build & install

`zerocast` CLI は以下の方法でビルド・インストールできます:

```sh
# build
cmake -S . -B build && cmake --build build

# install
sudo cmake --install build
```

## related works

- 無限の猿定理
- 神
- バックアップを取らなかった技術者達

ユーザー製作:

- [otoneko1102/amazing-compression-tech](https://github.com/otoneko1102/amazing-compression-tech)

## license

このプロジェクトはMITライセンスの元で公開されています。詳細については [LICENSE](LICENSE) ファイルをご覧ください。
