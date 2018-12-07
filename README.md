# DirectX12ドキュメント

## 現在の目標！
DirectXデバイスを作成し、基本的なコマンド系のクラスを作成する。

## 必要な機能
PBRを用いたForward+レンダリングを行う。
CPUとGPUの処理を並列実行させ、処理速度を高速に。
複数のスレッドによるコマンドの発行。
オブジェクトの描画をインスタンシングにて行う。
全体のフレームをカウントし、現在返すべきフレームインデックスをグローバルで取得できるようにする。
すべてのコマンドリストの設定を一括で反映させる。
ひとつのコマンドリストの設定を変更する。

## 旧処理手順
### WinMain
デバッグ機能を有効にする。
メインウィンドウを作成する。
ゲームループ機能を作成する。
DirectX12デバイスを作成する。
コマンド系を作成する。

### RootSignatureTest
モデルの読み込み
ルートシグネチャの作成
インプットレイアウトの設定
PSOの作成


## 実装していく項目
### GameTime
全体の時間系を管理するクラス。
ゲーム開始後のフレーム数や全体の時間、そのフレームでかかった時間、
現在のフレームインデックス、ひとつ前のフレームインデックスを取得できるようにする。

### DrawPipeline
メインでゲームの描画を担うコマンドパイプラインを管理する。
描画パスを変更する際にここを修正するような設計にする。
現在考えられるパスはライトカリング、不透明パス、透明パス
またシャドウやアンチエイリアスなどの設定追加も考えられる。

### RenderingOrder
描画を行う際にはここにそのオブジェクトの情報を伝える。
パイプラインはここに登録されているひとつ前のフレームのオブジェクト情報から描画を行っていく。

### GameLoop
全体的な処理の流れを管理するクラス。
大きく分けると更新処理と描画処理の並列化を行ったり、時間などのグローバル情報の更新を行う。


## クラス化する標準機能
バリア
フェンス
ディスクリプターヒープ
各種View
コマンドアロケーター
コマンドリスト
コマンドキュー
頂点情報
テクスチャ情報