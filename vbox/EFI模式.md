# EFI模式

vbox默认好像是Legacy的BIOS启动。你要启用EFI模式，才可以让vbox使用EFI模式。

不过不知道为什么我装windows的时候，vbox会自动切换为EFI模式，但是不知道为什么Linux的时候，就只会给我用默认的Legacy模式。

现代电脑，大部分只支持用UEFI模式启动了。传动的BIOS启动，也不支持了。

所以，你如果要制作系统盘的话，一定要在vbox的设置界面启动EFI模式，这样系统才会创建ESP分区，创建efi引导。