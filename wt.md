###
# Wt
###

---

---

---

---

---

---

Wt（または "Witty"）は、C++でウェブアプリケーションを開発するためのフレームワークです。以下に、Wtを使用してHello Worldを表示する基本的な例を示します。

まず、Wtをインストールし、サンプルコードを作成します。

### サンプルコード

```cpp
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WText.h>

class HelloApplication : public Wt::WApplication {
public:
    HelloApplication(const Wt::WEnvironment& env) : Wt::WApplication(env) {
        // Root container
        auto container = root();
        
        // Create a text widget with "Hello, World!"
        auto text = std::make_unique<Wt::WText>("Hello, World!", container);
        
        // Add the text widget to the root container
        container->addWidget(std::move(text));
    }
};

int main(int argc, char** argv) {
    // Create a Wt application
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<HelloApplication>(env);
    });
}
```

### コードの説明

1. `WApplication` クラスを継承した `HelloApplication` クラスを定義します。これはWtアプリケーションのエントリポイントとなります。
2. `HelloApplication` のコンストラクタで、`Wt::WApplication` を初期化します。
3. `root()` メソッドを使用して、ウェブページのルートとなるコンテナを取得します。
4. `Wt::WText` を使用してテキストウィジェットを作成し、「Hello, World!」というテキストを指定します。
5. `addWidget()` を使用して、テキストウィジェットをルートコンテナに追加します。
6. `main()` 関数で、`Wt::WRun()` を呼び出してアプリケーションを実行します。ラムダ式を使用して `HelloApplication` のインスタンスを作成し、Wt環境を渡します。

### コンパイルと実行

このコードをコンパイルするには、Wtのインストールが必要です。以下のようにコンパイルします（Linuxの場合）:

```bash
g++ -o hello_wt hello_wt.cpp -lwthttp -lwt
```

コンパイル後、実行します:

```bash
./hello_wt --http-address=0.0.0.0 --http-port=8080
```

ブラウザで `http://localhost:8080` を開くと、「Hello, World!」というテキストが表示されます。

これで、Wtを使用して簡単なHello Worldアプリケーションを作成する方法がわかりました。

---
Wt（Witty）をインストールする方法について、基本的な手順を以下に示します。Wtのインストールには、コンパイルや依存関係の準備が必要ですが、それぞれの環境に合わせて適切な手順を選択してください。

### 1. 必要な依存関係のインストール

まず、Wtをビルドするために必要な依存関係をインストールします。一般的な依存関係には、以下のものが含まれます（環境によっては異なる場合があります）:

- C++コンパイラ（通常はgccやclang）
- CMake（ビルドシステム）
- Boostライブラリ（特にboost-devやlibboost-all-devなど）

これらの依存関係は、各ディストリビューションのパッケージマネージャを使用してインストールできます。たとえば、Ubuntuでのインストールコマンドは以下のようになります:

```bash
sudo apt-get update
sudo apt-get install build-essential cmake libboost-dev libboost-all-dev
```

### 2. Wtのソースコードの取得

Wtの公式リポジトリからソースコードを取得します。GitHubのリポジトリからクローンする場合は以下のコマンドを使用します:

```bash
git clone https://github.com/emweb/wt.git
cd wt
```

### 3. Wtのビルドとインストール

次に、Wtをビルドしてインストールします。以下の手順に従ってください:

```bash
mkdir build
cd build
cmake ..
make
sudo make install
```

これにより、Wtがシステムにインストールされます。`make install` の前に `make` を実行することで、ビルドが正常に完了する必要があります。

### 4. ビルドの確認

ビルドが完了したら、簡単なHello Worldのプログラムをコンパイルして実行してみてください。前述のHello Worldの例を使用して、Wtが正しく動作しているか確認できます。

### 注意事項

- ビルド中に依存関係が不足している場合、エラーメッセージが表示されることがあります。その場合は、必要な依存関係を追加でインストールしてください。
- インストール先がシステムのパスにない場合は、ビルド時に適切なインストールディレクトリを指定することができます（例: `cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..`）。

これで、Wtをインストールし、基本的な動作を確認する準備が整いました。

---
