# 操作系统实验一：Git 与 Linux 操作基础

本仓库用于《操作系统》实验一 **任务 1（Git 基础与操作）** 的练习与过程记录。

## 实验环境

| 项目 | 说明 |
| --- | --- |
| 操作系统 | Windows 10 (x64) |
| Git 版本 | 2.56.0.windows.4 |
| 代码托管平台 | GitHub |
| 终端 | Git Bash / PowerShell |

## 仓库结构

```
os-lab/
├── README.md            # 仓库说明
├── hello.c              # 示例 C 程序
├── test.sh              # 第一个 Shell 脚本
├── .gitignore           # 忽略规则
└── docs/
    └── lab1-git.md      # 实验步骤记录
```

## 任务 1 完成情况

- [x] 安装并配置 Git（user.name / user.email）
- [x] 生成 SSH Key 并添加到 GitHub
- [x] 创建本地仓库并与 GitHub 远程仓库关联
- [x] 本地代码与托管平台代码同步（add / commit / push / clone / pull）
- [x] Git 分支管理（创建、切换、修改、合并、删除分支）

## 常用命令

```bash
git status                 # 查看工作区状态
git add .                  # 添加改动到暂存区
git commit -m "message"    # 提交到本地仓库
git push origin main       # 推送到远程仓库
git pull origin main       # 拉取远程更新
git branch -a              # 查看所有分支
git log --oneline --graph  # 图形化查看提交历史
```
