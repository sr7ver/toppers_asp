=====================================================================
               TOPPERS on PSoC 5LP用プロジェクトファイル
                                  Last Modified: 2013 Feb 03 18:09:00
=====================================================================
このプロジェクトファイルは，TOPPERS/ASPカーネル(1.9.0)を，CY8CKIT-050
 PSoC 5LP PSoc Development Kitで動作させるための，PSoC Creatorのプロ
ジェクトファイルである．

(1) PSoC Creator
(1-1) 本プロジェクトは，PSoC Creator 3.0で作成したものである．

(1-2) 本プロジェクトは，ログインユーザのドキュメントフォルダーの
PSoC Creatorというフォルダー下に展開されている事を前提としています．

(1-3) ASPカーネル関係のファイルは，プロジェクト名[asp_eval].cydsn/aspに
フォルダー構成そのままで格納している．

(1-4) アーカイブ状態
このアーカイブファイルは，ファイルサイズ削減のため，PSoC Creatorのメ
ニューから「Clean asp_eval1」を実行している．そのためRelease/Debug両
モード(特にDebugモード)においてまず最初にビルドを実行されたい．

(2) kernel_cfg.h，kernel_cfg.c，offset.hの作成方法

(2-1) asp/OBJSフォルダーに，ユーザが作成したファイルをコピーする
ここでいうユーザが作成したファイルとは，ASPカーネルをビルドするために
必要なソフトウェア(*.h，*.c)，および必要なコンフィギュレーション情報
ファイル(*.cfg)を意味する．

★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★
もしOBJSを別な名前のフォルダーにする場合

PSoC Creatorの[Project]->[Builder Settings..]で，ARM GCC 4.7.3の下に
あるCompilerを選択し，Addtional Include DIrectories欄にある
".\asp\OBJS"をその新しい名前に変更すること
★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★

(2-2) コマンドプロンプトを起動して，asp/OBJSフォルダーへ移動し，バッチ
ファイル(set_path.bat)を実行する．

(2-3) コマンドプロンプトで，バッチファイル(make_depend.bat)を実行する
make_depend.bat %1 %2 %3
    %1 aspのトップディレクトリ                   (例：..)
    %2 対象となるコンフィギュレーションファイル  (例：sample1)
    %3 ターゲット名                              (例：cy8ckit050_gcc)

ここで%2はユーザが作成したコンフィギュレーションファイル名となるが
%1と%3は例のまま入力する．

これで，kernel_cfg.h，kernel_cfg.c，offset.hが生成される

(3) PSoC Creatorでのビルド方法
このプロジェクトファイルは，TOPPERSのサンプルプログラムをビルドする
ために作成されているので，sample1を削除しユーザアプリケーションを登録
しる必要がある．

(3-1) sample1をプロジェクトから削除
PSoC CreatorのWorkspace ExplorerのOBJSフォルダー下にあるsample1.hおよ
びsample1.cを削除する．

(3-2) ユーザ作成ソフトウェアの登録
Workspace ExplorerのOBJSフォルダーへ，(2-1)でコピーしたユーザが作成し
たファイル(*.hおよび*.c)を追加登録する．

以降は通常のPSoC Creatorの使用方法と同じで，プロジェクトのビルド
(Shift+F6)を実行すればよい．

(4) 生成オブジェクトのチェック
TOPPERSのmakeでは，最後に生成オブジェクトのチェックを行う．
PSoC Creatorとしては必須ではないが，TOPPERSのデザインフローとして同様
の手順を提供する．

(4-1) コマンドプロンプトで，バッチファイル(make_post_****.bat)を実行する
(a) Debug Modeでビルドした場合：make_post_debug.bat %1 %2 %3 %4
(b) Release Modeでビルドした場合：make_post_release.bat %1 %2 %3 %4
    %1 aspのトップディレクトリ                   (例：..)
    %2 対象となるコンフィギュレーションファイル  (例：sample1)
    %3 ターゲット名                              (例：cy8ckit050_gcc)
    %4 PSoC Creatorプロジェクト名                (例：asp_eval1)

ここで%2はユーザが作成したコンフィギュレーションファイル名，および
%4はPSoC Creatorのプロジェクト名になるが，%1と%3は例のまま入力する．

チェックが正常終了すると，check completeと表示される

Debug/Releaseいずれのモードでも，このチェックでプロジェクト名.srecと
プロジェクト名.symsというファイルが生成される．
両モードでのチェックを続けて実行した場合，これらのファイルは後から実行
した方で上書きされる．
チェックが目的なので特にファイル名は変えていない．

(5) 注意事項
下記文中にある開発担当者とは，TOPPERSプロジェクトで承認されている
TOPPERS/ASPカーネルのPSoC 5LPターゲット依存部の開発担当者の事である．

(5-1) 今回使用しているPSoCのコンポーネントはUART(version 2.30)である．
PSoC CreatorのアップデートによってUARTのバージョンが更新された場合は，
開発担当者側で動作確認の後TOPPERSプロジェクト上で通知するので，通知が
出る前にユーザ側で更新し不具合が発生しても，開発担当者側としては対応
できない．

(5-2) PSoC Creatorで利用できる他のコンポーネントについても，開発担当
者側でターゲット依存部設計および動作確認を行った後リリースして行く予
定である．

(6) バージョン履歴
2014/02/03
・ASPカーネル 1.9.0に対応
　動作確認のみ

2014/02/03
・ASPカーネル 1.8.0に対応
　char_t → char

2013/08/25
・最初のリリース
