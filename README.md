# C 终端贪吃蛇

一个使用 **C99** 和 **ncurses** 编写的终端贪吃蛇项目，目标是让 C 语言初学者通过一个完整的小游戏，理解数组、结构体、指针、终端输入和基础游戏循环。

> **项目状态：** 当前只有项目文档，游戏源码尚未实现。

## 项目目标

- 在 Linux 终端中运行，不需要图形界面
- 使用方向键控制蛇移动，无需按回车确认
- 实现食物、得分、加速和碰撞检测
- 保持代码结构简单，适合作为 C 语言练习项目
- 学会编译、调试和用 `Makefile` 管理多文件程序

## 计划功能

- [ ] 绘制游戏地图和信息栏
- [ ] 蛇的移动与方向控制
- [ ] 防止蛇直接反向移动
- [ ] 随机生成食物
- [ ] 吃到食物后增长并加分
- [ ] 撞墙或撞到自己后结束游戏
- [ ] 暂停、重新开始和退出
- [ ] 根据分数调整移动速度
- [ ] 退出游戏时正确恢复终端状态

## 技术栈

| 用途 | 技术 |
| --- | --- |
| 编程语言 | C99 |
| 编译器 | GCC |
| 终端界面与键盘输入 | ncurses |
| 构建工具 | Make |
| 调试工具 | GDB |
| 目标平台 | Linux 或 WSL |

主要使用的标准库和系统库：

- `<stdio.h>`：格式化输出
- `<stdlib.h>`：随机数和程序退出
- `<time.h>`：随机种子和游戏计时
- `<stdbool.h>`：布尔类型
- `<ncurses.h>`：终端绘制、非阻塞键盘输入和光标控制

## 环境准备

### Debian / Ubuntu / WSL

```bash
sudo apt update
sudo apt install build-essential libncurses-dev gdb
```

### Fedora

```bash
sudo dnf install gcc make ncurses-devel gdb
```

### Arch Linux

```bash
sudo pacman -S base-devel ncurses gdb
```

## 构建与运行

源码和 `Makefile` 完成后的目标使用方式：

```bash
make
./snake
```

单独使用 GCC 编译时，需要链接 ncurses：

```bash
gcc -std=c99 -Wall -Wextra -Wpedantic -g snake.c -lncurses -o snake
```

> 当前仓库中还没有 `snake.c` 和 `Makefile`，因此以上命令暂时不能运行。

## 操作方式

计划支持：

| 按键 | 操作 |
| --- | --- |
| `↑` `↓` `←` `→` | 控制方向 |
| `W` `A` `S` `D` | 控制方向 |
| `P` | 暂停 / 继续 |
| `R` | 重新开始 |
| `Q` | 退出 |

## 项目结构

初期采用单文件结构，方便集中理解游戏循环：

```text
Snake/
├── README.md
├── Makefile
└── snake.c
```

功能增加后可以逐步拆分：

```text
Snake/
├── README.md
├── Makefile
├── include/
│   ├── game.h
│   └── render.h
└── src/
    ├── main.c
    ├── game.c
    └── render.c
```

## 核心设计

### 游戏循环

每一帧按顺序完成以下步骤：

1. 读取非阻塞键盘输入。
2. 计算蛇的新头部位置。
3. 检查是否吃到食物。
4. 检查是否撞墙或撞到自身。
5. 更新蛇身和分数。
6. 重新绘制画面。
7. 等待固定的时间间隔。

### 数据结构

蛇身计划使用固定容量的坐标数组表示，避免在初学阶段立即引入动态内存管理：

```c
typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point body[1024];
    int length;
    int direction;
    int score;
    bool running;
} Game;
```

具体实现可能根据地图尺寸调整。

## 初学者学习清单

开始编码前，至少需要掌握：

- 变量、条件判断、循环和函数
- 一维数组和二维数组
- 结构体与枚举
- 指针作为函数参数
- 头文件和源文件的基本组织方式
- `rand()` 与 `srand()`
- 编译警告、断点和单步调试

开始使用 ncurses 时，重点学习：

- `initscr()` 与 `endwin()`
- `cbreak()` 与 `noecho()`
- `keypad()` 与 `getch()`
- `timeout()` 或 `nodelay()`
- `clear()`、`move()` 与 `mvaddch()`
- `refresh()` 与屏幕刷新机制
- `KEY_UP`、`KEY_DOWN`、`KEY_LEFT`、`KEY_RIGHT`

系统编程部分只需要先理解：

- 标准输入 `stdin`
- 终端规范模式与原始模式
- `<termios.h>` 的基本作用
- 为什么终端游戏需要非阻塞输入
- 程序退出或崩溃后如何恢复终端

## 开发顺序

1. 用 `printf` 画出固定地图和静态蛇。
2. 引入 ncurses，完成不需要回车的键盘输入。
3. 实现蛇的定时移动和方向控制。
4. 加入食物、增长和得分。
5. 加入碰撞检测与游戏结束。
6. 完成暂停、重新开始和速度调整。
7. 编写 `Makefile`，开启编译警告并使用 GDB 调试。

## 调试建议

使用以下选项编译，尽早发现未初始化变量、类型不匹配和越界风险：

```bash
gcc -std=c99 -Wall -Wextra -Wpedantic -g snake.c -lncurses -o snake
```

如果程序异常退出后终端显示混乱，可以执行：

```bash
reset
```

## 后续扩展

完成基础版本后，可以考虑：

- 最高分本地保存
- 穿墙模式
- 障碍物和关卡
- 最简单的颜色主题
- 用 SDL2 或 raylib 开发图形版本

