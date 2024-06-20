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

Wt（Witty）をMacでインストールする手順を以下に示します。Macでは、Homebrewを使用して依存関係をインストールし、ソースコードからビルドする方法を説明します。

### 1. Homebrewのインストール

まず、Homebrewを使って必要なパッケージをインストールします。HomebrewはMac用のパッケージ管理システムです。

```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

インストール後、ターミナルで以下のコマンドを実行して、Homebrewが正しくインストールされたか確認します。

```bash
brew --version
```

### 2. 必要な依存関係のインストール

次に、Wtのビルドに必要な依存関係をHomebrewを使ってインストールします。

```bash
brew install cmake boost
```

### 3. Wtのソースコードの取得とビルド

Wtの公式リポジトリからソースコードを取得し、ビルドします。

```bash
git clone https://github.com/emweb/wt.git
cd wt
mkdir build
cd build
cmake ..
make
sudo make install
```

これにより、WtがビルドされてMacにインストールされます。`make install` の実行中にパスワードが求められることがあります。

### 4. ビルドの確認

インストールが完了したら、以下の手順で動作を確認します。

1. Wtのインストール先のディレクトリを確認します。通常は `/usr/local` または `/usr/local/bin` にインストールされます。
2. 簡単なHello Worldのプログラムを作成し、コンパイルして実行します。例えば、前述のHello Worldの例を使って確認できます。

### 5. インストールの確認

インストールが完了したら、Wtが正しく動作するかどうかを確認するために、サンプルプログラムを実行してみてください。これにより、Mac上でWtを使用する準備が整います。

---
