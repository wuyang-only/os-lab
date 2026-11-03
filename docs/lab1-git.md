# 实验一 任务 1：Git 安装、配置与远程仓库同步

> 记录时间：2026-11-03　环境：Windows 10 x64 + Git 2.56.0.windows.4 + GitHub
> 远程仓库：<https://github.com/wuyang-only/os-lab>

## 1. 安装 Git

Windows 下官方安装包默认需要管理员权限，本次改为**解压官方 tar.bz2 发行包到用户目录**，
无需管理员权限，效果与正常安装一致（含 `git.exe`、Git Bash、OpenSSH）。

```powershell
# 下载（GitHub 直连较慢，改用国内镜像；版本 2.56.0.windows.4）
# https://registry.npmmirror.com/-/binary/git-for-windows/v2.56.0.windows.4/Git-2.56.0.4-64-bit.tar.bz2

# 解压到用户程序目录
tar -xjf git-full.tar.bz2 -C "$env:LOCALAPPDATA\Programs\Git"

# 把安装目录加入用户 PATH（新开终端生效），然后验证
git --version
# git version 2.56.0.windows.4
```

安装后目录：`cmd\git.exe`（命令入口）、`bin\bash.exe`（Git Bash）、`usr\bin\ssh.exe`（SSH 客户端）。

## 2. 配置 Git

```bash
git config --global user.name  "wuyang"
git config --global user.email "Antonio_wu2006@outlook.com"
git config --global init.defaultBranch main
git config --global core.quotepath false      # 正常显示中文文件名
git config --global http.sslBackend openssl   # 规避 Windows schannel 证书报错
git config --global --list
```

实际输出：

```
user.name=wuyang
user.email=Antonio_wu2006@outlook.com
init.defaultbranch=main
core.quotepath=false
http.sslbackend=openssl
```

## 3. 生成 SSH Key 并添加到 GitHub

```bash
ssh-keygen -t ed25519 -C "Antonio_wu2006@outlook.com" -f ~/.ssh/id_ed25519 -N ""
```

生成的文件：

| 文件 | 说明 |
| --- | --- |
| `C:\Users\PC\.ssh\id_ed25519` | 私钥，本地保存，不可外传 |
| `C:\Users\PC\.ssh\id_ed25519.pub` | 公钥，粘贴到 GitHub |

公钥内容：

```
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIBuyS7p05jveiYTpfARa0V2WUb8BVR3K6AvFpkchfEuq Antonio_wu2006@outlook.com
```

添加路径：GitHub 头像 → Settings → SSH and GPG keys → New SSH key → 粘贴公钥 → Add SSH key。

验证连接：

```bash
ssh -T git@github.com
# Hi wuyang-only! You've successfully authenticated, but GitHub does not provide shell access.
```

## 4. 创建本地仓库

```bash
mkdir os-lab && cd os-lab
git init -b main
git add -A
git commit -m "feat: 初始化 os-lab 仓库，添加 README、示例代码与 .gitignore"
# [main (root-commit) fc38bb5] feat: 初始化 os-lab 仓库...
#  4 files changed, 72 insertions(+)
```

## 5. 关联远程仓库并同步

```bash
git remote add origin git@github.com:wuyang-only/os-lab.git
git remote -v
# origin  git@github.com:wuyang-only/os-lab.git (fetch)
# origin  git@github.com:wuyang-only/os-lab.git (push)

git push -u origin main
# branch 'main' set up to track 'origin/main'.

git push origin --tags
# * [new tag]  v1.0 -> v1.0
```

**代码下载（clone）**：另建目录克隆远程仓库，验证远程内容完整。

```bash
git clone git@github.com:wuyang-only/os-lab.git os-lab-clone
# Cloning into 'os-lab-clone'...
git log --oneline --decorate --graph --all
```

**双向同步**：在克隆副本中修改 README 并推送，再回到原仓库拉取，验证两端一致。

```bash
# 在 os-lab-clone 中
git commit -am "docs: 克隆仓库中补充双向同步验证说明"
git push origin main            # 713f3ae..4d0fcde  main -> main

# 回到 os-lab 中
git pull --no-rebase origin main
# Updating 713f3ae..4d0fcde
# Fast-forward
#  README.md | 4 ++++
```

## 6. 分支管理

```bash
git switch -c dev                                  # 创建并切换到 dev 分支
git add hello.c
git commit -m "feat: hello.c 支持通过命令行参数指定问候对象"

git switch main                                    # 切回主干
git merge --no-ff dev -m "merge: 将 dev 分支的问候参数功能合并到 main"
# Merge made by the 'ort' strategy.

git tag -a v1.0 -m "实验一任务1：本地仓库与分支管理完成"
git log --oneline --decorate --graph --all
```

提交历史：

```
* 4d0fcde (HEAD -> main, origin/main) docs: 克隆仓库中补充双向同步验证说明
*   713f3ae (tag: v1.0) merge: 将 dev 分支的问候参数功能合并到 main
|\
| * e6a72da (dev) feat: hello.c 支持通过命令行参数指定问候对象
|/
* 5d98f2c docs: 记录 Git 安装、全局配置与 SSH Key 生成过程
* fc38bb5 feat: 初始化 os-lab 仓库，添加 README、示例代码与 .gitignore
```

## 7. 遇到的问题与解决

| 问题 | 现象 | 解决 |
| --- | --- | --- |
| GitHub 直连下载慢 | 安装包约 12 KB/s | 改用 npmmirror 镜像，25 s 下载完成 |
| 安装包需要管理员权限 | `/CURRENTUSER` 静默安装失败 | 解压 tar.bz2 发行包到用户目录并加入 PATH |
| HTTPS 报 schannel 错误 | `SEC_E_NO_CREDENTIALS` | 配置 `http.sslBackend=openssl` |
| GitHub 网页访问不稳 | 无法创建仓库 | 开启 VPN 后创建成功 |
