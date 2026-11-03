# 实验一 任务 1：Git 安装、配置与远程仓库同步

> 记录时间：2026-11-03　环境：Windows 10 x64 + Git 2.56.0.windows.4 + GitHub

## 1. 安装 Git

本次采用 Git for Windows 官方发行包（`Git-2.56.0.4-64-bit.tar.bz2`）解压安装到用户目录，
无需管理员权限：

```powershell
# 下载（使用国内镜像加速）
# https://registry.npmmirror.com/-/binary/git-for-windows/v2.56.0.windows.4/Git-2.56.0.4-64-bit.tar.bz2

# 解压到 C:\Users\PC\AppData\Local\Programs\Git
tar -xjf git-full.tar.bz2 -C "$env:LOCALAPPDATA\Programs\Git"

# 加入用户 PATH 后验证
git --version
# git version 2.56.0.windows.4
```

安装目录结构：`cmd\git.exe`（命令入口）、`bin\bash.exe`（Git Bash）、`usr\bin\ssh.exe`（SSH 客户端）。

## 2. 配置 Git

```bash
git config --global user.name  "wuyang"
git config --global user.email "Antonio_wu2006@outlook.com"
git config --global init.defaultBranch main
git config --global core.quotepath false      # 正常显示中文文件名
git config --global http.sslBackend openssl   # 避免 Windows schannel 证书问题
git config --global --list
```

## 3. 生成 SSH Key 并添加到 GitHub

```bash
ssh-keygen -t ed25519 -C "Antonio_wu2006@outlook.com" -f ~/.ssh/id_ed25519 -N ""
# 公钥：C:\Users\PC\.ssh\id_ed25519.pub
```

将 `id_ed25519.pub` 的内容粘贴到 GitHub → Settings → SSH and GPG keys → New SSH key。

验证：

```bash
ssh -T git@github.com
# Hi wuyang! You've successfully authenticated, but GitHub does not provide shell access.
```

## 4. 创建本地仓库

```bash
mkdir os-lab && cd os-lab
git init -b main
git add -A
git commit -m "feat: 初始化 os-lab 仓库，添加 README、示例代码与 .gitignore"
```

## 5. 关联远程仓库并同步

（待完成：创建 GitHub 空仓库 → `git remote add origin` → `git push -u origin main`）

## 6. 分支管理

（待完成：创建 dev 分支 → 修改提交 → 合并回 main → 删除分支）
