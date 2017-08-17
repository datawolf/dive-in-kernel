##  说明

该模块根据通过遍历dentry，列出指定目录下的所有的文件和文件夹信息。

## 使用方法

```
insmod ls.ko dir="/root/"
```

## 示例

```
root@localhost:h006_ls# make test
make[1]: Entering directory '/root/dive-in-kernel/h006_ls'
#############[START] #################
[ 2743.662962] [Hello] ls 
[ 2743.662981] DIR: /root/ has the following files:name = .viminfo
[ 2743.662983] name = .NERDTreeBookmarks
[ 2743.662984] name = .vimrc
[ 2743.662985] name = .vim
[ 2743.662986] name = dmesg
[ 2743.662987] name = dmes
[ 2743.662988] name = lxc-test
[ 2743.662988] name = notes
[ 2743.662989] name = temp
[ 2743.662990] name = dive-in-kernel
[ 2743.662991] name = chelper
[ 2743.662992] name = util-linux
[ 2743.662993] name = specs-c
[ 2743.662993] name = work
[ 2743.662994] name = lxc
[ 2743.662995] name = lxc-pkg-ubuntu
[ 2743.662996] name = libseccomp
[ 2743.662997] name = kernel
[ 2743.662998] name = libocispec
[ 2743.662999] name = mem_proc
[ 2743.662999] name = go
[ 2743.663000] name = uts
[ 2743.663001] name = bin
[ 2743.663002] name = lxd
[ 2743.663002] name = man-pages
[ 2743.663003] name = git
[ 2743.663004] name = test
[ 2743.663005] name = main.c
[ 2743.663006] name = skopeo
[ 2743.663006] name = .inputrc
[ 2743.663007] name = .terminfo
[ 2743.663008] name = go1.7
[ 2743.663009] name = iwyu
[ 2743.663010] name = .bash_aliases
[ 2743.663011] name = .dircolors
[ 2743.663012] name = .bash_history
[ 2743.663012] name = .bashrc
[ 2743.663013] name = .profile
[ 2743.663014] name = .bash_login
[ 2743.663015] name = .bash_profile
[ 2743.663016] name = .bash_completion
[ 2743.663016] name = .m2
[ 2743.663017] name = .sudo_as_admin_successful
[ 2743.663018] name = .ssh
[ 2743.663019] name = .hushlogin
[ 2743.663020] name = .pam_environment
[ 2743.663021] name = .cache
[ 2743.663022] name = .config
[ 2743.663023] name = .apport-ignore.xml
[ 2743.663024] name = .local
make[1]: Leaving directory '/root/dive-in-kernel/h006_ls'
make[1]: Entering directory '/root/dive-in-kernel/h006_ls'
[ 2743.680576] [Goodbye] ls
#############[ END ] #################
make[1]: Leaving directory '/root/dive-in-kernel/h006_ls'
```
