# URC IO-Expander

## プログラム

![プログラムの動き](img/URC_Program.png)

RobotSystem クラスを継承した Robot クラスを編集することで，それぞれのモードのロボットの動きをプログラムすることができる．

### Disable ~

ロボットが試合前後に行う動き．

### Autonomous ~

ロボットが自動操縦時間中に行う動き．

### Teleop ~

ロボットが手動操縦時間中に行う動き．

### Test ~

bool urc::test をtrueにした時の動き．上の関数は実行されない．

### ~ Init()

各モードの最初に行う動き．

### ~ Periodic()

各モードの最中，Init()後に行い続ける動き．

## 入出力

### dio デジタル入出力

#### pinMode(int pin, int status)

pinで指定したピンの入出力を，INPUT(入力)またはOUTPUT(出力)に設定する．

#### Init()

pinModeで指定したピンの入出力情報を確定させる．

#### digitalWrite(int pin, int status)

OUTPUTに設定されたピンのうち指定したpinの出力を，HIGH(出力オン)またはLOW(出力オフ)に設定する．

#### digitalRead(int pin)

指定したpinの入力状態を取得する．


