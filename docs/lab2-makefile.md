# 实验二 编译原理基础（Makefile）与文本编辑器

> 环境：Ubuntu 20.04.6 LTS　gcc 9.4.0　GNU Make 4.2.1　Vim 8.1　nano 4.8　Emacs 26.3
> 项目位置：`lab2/my_project`

## 1. 项目结构

```
my_project/
├── Makefile
└── src/
    ├── main.c
    ├── utils.c
    ├── utils.h
    ├── extra.c      # 后续新增
    └── extra.h      # 后续新增
```

## 2. 源代码

`src/main.c`：

```c
#include <stdio.h>
#include "utils.h"
#include "extra.h"

int main() {
    printf("Hello, World!\n");
    greet("Student");
    show_version();
    return 0;
}
```

`src/utils.c`（经 vim 修改后）：

```c
#include <stdio.h>
#include "utils.h"

void greet(const char *name) {
    printf("Hello, %s! Welcome to the OS lab.\n", name);
}
```

`src/utils.h` 使用头文件保护，声明 `greet`；`src/extra.h` 同理声明 `show_version`。

## 3. Makefile

```make
# Makefile
CC = gcc
CFLAGS = -Wall -g
SRCS = src/main.c src/utils.c src/extra.c
OBJS = $(SRCS:.c=.o)
TARGET = my_program
all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS) $(TARGET)
```

- 变量：`CC`、`CFLAGS`、`SRCS`、`OBJS`、`TARGET`；
- 目标与依赖：`all` 依赖 `$(TARGET)`，`$(TARGET)` 依赖所有 `.o`；
- 命令必须以 **TAB** 开头，`$@` 表示目标，`$^` 表示全部依赖，`$<` 表示第一个依赖。

## 4. 编译与运行

```bash
make
# gcc -Wall -g -c src/main.c -o src/main.o
# gcc -Wall -g -c src/utils.c -o src/utils.o
# gcc -o my_program src/main.o src/utils.o
./my_program
# Hello, World!
# Welcome, Student!
```

## 5. 修改与重编译

用 vim 的替换命令修改 `utils.c` 中 `greet` 的输出：

```bash
vim -es -c '%s/Welcome, %s!/Hello, %s! Welcome to the OS lab./' -c 'wq' src/utils.c
make
# gcc -Wall -g -c src/utils.c -o src/utils.o
# gcc -o my_program src/main.o src/utils.o
./my_program
# Hello, World!
# Hello, Student! Welcome to the OS lab.
```

只有被修改的 `utils.c` 重新编译，`main.c` 未变，说明 make 会根据时间戳自动判断依赖。

## 6. 新增源文件与目标

新增 `src/extra.c`、`src/extra.h`，在 `main.c` 中调用 `show_version()`，并把 `extra.c` 加入 `SRCS`：

```bash
sed -i 's|^SRCS = .*|SRCS = src/main.c src/utils.c src/extra.c|' Makefile
make
# gcc -Wall -g -c src/main.c -o src/main.o
# gcc -Wall -g -c src/extra.c -o src/extra.o
# gcc -o my_program src/main.o src/utils.o src/extra.o
./my_program
# Hello, World!
# Hello, Student! Welcome to the OS lab.
# my_program v1.0 (built by GNU Make)
```

## 7. 编译四阶段验证

```bash
gcc -E src/utils.c -o /tmp/utils.i     # 预处理：展开头文件与宏
gcc -S /tmp/utils.i -o /tmp/utils.s    # 编译：生成汇编
gcc -c /tmp/utils.s -o /tmp/utils_stage.o   # 汇编：生成目标文件
gcc /tmp/utils_stage.o src/main.o src/extra.o -o /tmp/my_program_stage  # 链接
```

文件大小：`utils.i` 16454 B → `utils.s` 771 B → `utils_stage.o` 1728 B → 可执行文件 20664 B。

## 8. 清理

```bash
make clean
# rm -f src/main.o src/utils.o src/extra.o my_program
```

`make clean` 后目录中只保留源文件与 Makefile。

## 9. 文本编辑器的使用

- **Vim**：`vim src/utils.c`，普通模式按 `i` 进入插入模式，`Esc` 返回，`:wq` 保存退出；本次用 `:%s/old/new/` 完成替换。
- **nano**：`nano src/utils.h`，`Ctrl+O` 保存、`Ctrl+X` 退出。
- **Emacs**：`emacs src/extra.c`，`Ctrl+X` `Ctrl+S` 保存，`Ctrl+X` `Ctrl+C` 退出。
