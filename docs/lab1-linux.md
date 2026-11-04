# 实验一 任务 2：Linux 操作基础

> 环境：Ubuntu 20.04.6 LTS（VMware Workstation 17 虚拟机，2 vCPU / 2 GB 内存 / 20 GB 磁盘）
> 登录用户：`ubuntu`（sudo 免密）　镜像源：阿里云 focal

## 1. 目录与文件操作（第 1—3 步）

```bash
sudo mkdir /test3
sudo mkdir /test3/AA /test3/BB
sudo touch /test3/AA/file.txt
ls -lR /test3
```

结果：

```
/test3:
drwxr-xr-x 2 root root 4096 AA
drwxr-xr-x 2 root root 4096 BB

/test3/AA:
-rw-r--r-- 1 root root 0 file.txt

/test3/BB:
（空）
```

## 2. 复制、移动与查看（第 4—7 步）

```bash
sudo cp -r /etc/binfmt.d /test3/AA/
sudo mv /test3/AA/binfmt.d /test3/BB/tab
cat /test3/BB/tab/qemu-arm.conf
vim -es -c '%print' -c 'q!' /test3/BB/tab/qemu-arm.conf
```

> **说明**：Ubuntu 20.04 中 `/etc/binfmt.d` 是**目录**（systemd 的 binfmt 配置目录，默认为空），
> 因此复制时需要 `-r`，移动后 `tab` 也是目录。为完成“查看文件内容 / vim 查看”两步，
> 复制后在该目录内放入了一个示例配置 `qemu-arm.conf` 再查看。

查看结果：

```
# /etc/binfmt.d/qemu-arm.conf
# 示例：为 ARM 架构可执行文件注册 binfmt_misc 解释器
:qemu-arm:M::\x7fELF\x01\x01\x01\x00...:/usr/bin/qemu-arm-static:F
```

## 3. 在 /etc 下查找包含 sys 的文件（第 8 步）

```bash
sudo grep -rl "sys" /etc 2>/dev/null | head -5
```

结果：

```
/etc/deluser.conf
/etc/modprobe.d/iwlwifi.conf
/etc/modprobe.d/mdadm.conf
/etc/mdadm/mdadm.conf
/etc/security/faillock.conf
```

## 4. 删除目录（第 9—10 步）

```bash
sudo rm -r /test3/AA     # 删除空/非空目录 AA
sudo rm -rf /test3/BB    # 强制递归删除 BB 及其下文件
ls -l /test3             # total 0
```

## 5. 更换 Ubuntu 镜像源（第 11—18 步）

```bash
lsb_release -a
# Description: Ubuntu 20.04.6 LTS
# Release:     20.04
# Codename:    focal

ls /etc/apt
# apt.conf.d  auth.conf.d  preferences.d  sources.list  sources.list.d  trusted.gpg.d

sudo cp /etc/apt/sources.list /etc/apt/sources.list.back      # 备份

sudo vim /etc/apt/sources.list                                 # 编辑，替换为阿里云源
```

替换后的 `/etc/apt/sources.list`（focal 对应阿里云镜像）：

```
deb https://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
deb-src https://mirrors.aliyun.com/ubuntu/ focal main restricted universe multiverse
deb https://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
deb-src https://mirrors.aliyun.com/ubuntu/ focal-updates main restricted universe multiverse
deb https://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse
deb-src https://mirrors.aliyun.com/ubuntu/ focal-backports main restricted universe multiverse
deb https://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
deb-src https://mirrors.aliyun.com/ubuntu/ focal-security main restricted universe multiverse
```

更新与升级：

```bash
sudo apt-get update
# Fetched 49.8 MB in 24s (2090 kB/s)

sudo apt-get upgrade -y
# 升级完成后：Ubuntu 20.04.6 LTS，内核 5.4.0-216-generic
```

镜像参考：<https://developer.aliyun.com/mirror/ubuntu>

## 6. Shell 脚本：奇偶数判别（第 19 步）

```bash
sudo vim /test3/odd_even.sh
sudo chmod +x /test3/odd_even.sh
```

脚本内容：

```bash
#!/bin/bash
# 实验一任务2：判断输入整数是奇数还是偶数
read -p "请输入一个整数: " num
if ! [[ "$num" =~ ^-?[0-9]+$ ]]; then
    echo "输入错误：$num 不是整数"
    exit 1
fi
if (( num % 2 == 0 )); then
    echo "$num 是偶数"
else
    echo "$num 是奇数"
fi
```

测试：

```bash
echo 4  | /test3/odd_even.sh    # 4 是偶数
echo 7  | /test3/odd_even.sh    # 7 是奇数
echo -3 | /test3/odd_even.sh    # -3 是奇数
echo abc| /test3/odd_even.sh    # 输入错误：abc 不是整数
```

## 7. 实验环境说明

- 原“标准教学系统”虚拟机账号未知，无法登录，故使用 Ubuntu 官方云镜像
  （`focal-server-cloudimg-amd64.vmdk`，20.04.6）新建虚拟机：
  磁盘扩容至 20 GB，cloud-init 自动创建 `ubuntu` 用户并注入 SSH 公钥，无需人工安装。
- 虚拟机通过 VMware NAT 联网，IP `192.168.41.129`，全部命令经 SSH 执行。
