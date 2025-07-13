# Arch Linux使用樱花内网穿透frp

我的建议是，最好不要用dokcer运行natfrp（樱花内网穿透），直接安装在实机里吧。就是说，选择这个命令。

```sh
sudo bash -c ". <(curl -sSL https://doc.natfrp.com/launcher.sh) direct"
```

然后，我推荐啊，只是推荐，不要让他开机自启动

```sh
sudo systemctl disable natfrp-service
```

要启动的时候就用
```sh
sudo systemctl start natfrp-service
```

要关闭的时候用（不要以为用crtl+c就可以解决了）
```sh
sudo systemctl stop natfrp-service
```
