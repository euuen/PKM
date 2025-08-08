# miniconda的使用

我不推荐用anaconda，主要是anaconda很卡，毕竟是图形化界面，而且anaconda能做到的，miniconda也能做到。总之，我感觉miniconda的使用体验更好。

# 列举已有的环境

```python
conda env list
```

## 创建一个虚拟环境

命令：
```python
conda create -n <ENV_NAME> python=<VERSION>
```

# 激活一个虚拟环境

```python
conda activate <ENV_NAME>
```

