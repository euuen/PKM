# linux使用vbox

这里就以ubuntu举例了

首先需要把自己添加到disk硬盘组，要不然你的vbox访问不了硬盘

记得关闭kvm

```sh
sudo modprobe -r kvm_amd
```