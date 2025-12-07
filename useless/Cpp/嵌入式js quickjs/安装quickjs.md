# 安装quickjs

去github上下载quickjs的源代码，然后编译

```sh
# 四核编译速度更快
make -j4
```

 然后安装到ubuntu里面

```sh
sudo make install
```

然后就可以愉快的使用了

下面创建一个新的文件夹，写一个cmakelist内容为

```cmake
# ./CMakeLists.txt
cmake_minimum_required (VERSION 3.28)

project (hello)

add_executable(${PROJECT_NAME} 
    main.cpp
)

# 2. 查找QuickJS的库文件
find_library(QUICKJS_LIBRARY
    NAMES quickjs
    PATHS /usr/local/lib/quickjs
    NO_DEFAULT_PATH
)

target_link_libraries(${PROJECT_NAME}
    ${QUICKJS_LIBRARY}
)
```

这里我不知道是为什么，直接写quickjs到target里面，cmake找不到，后面用find_libraray就好了

然后写一个main.cpp文件

```cpp
// main.cpp
#include <iostream>
#include <fstream>
#include <quickjs/quickjs-libc.h> // 包含必要的头文件

int main() {
    // 1. 初始化运行时和上下文
    JSRuntime* rt = JS_NewRuntime();
    if (!rt) {
        std::cerr << "Failed to create runtime" << std::endl;
        return 1;
    }

    // 可选：设置内存限制（例如64MB）
    JS_SetMemoryLimit(rt, 64 * 1024 * 1024);

    JSContext* ctx = JS_NewContext(rt);
    if (!ctx) {
        std::cerr << "Failed to create context" << std::endl;
        JS_FreeRuntime(rt);
        return 1;
    }

    // 注册标准库辅助函数，如console.log
    js_std_add_helpers(ctx, 0, nullptr);

    // 2. 读取并执行JavaScript文件
    std::ifstream file("hello.js");
    if (!file.is_open()) {
        std::cerr << "Could not open hello.js" << std::endl;
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return 1;
    }

    std::string scriptContent((std::istreambuf_iterator<char>(file)),
                              std::istreambuf_iterator<char>());
    file.close();

    JSValue evalResult = JS_Eval(ctx, scriptContent.c_str(), scriptContent.length(),
                                 "hello.js", JS_EVAL_TYPE_GLOBAL);
    if (JS_IsException(evalResult)) {
        JSValue exception = JS_GetException(ctx);
        const char* errorMsg = JS_ToCString(ctx, exception);
        std::cerr << "Error evaluating script: " << errorMsg << std::endl;
        JS_FreeCString(ctx, errorMsg);
        JS_FreeValue(ctx, exception);
        JS_FreeValue(ctx, evalResult);
        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
        return 1;
    }
    JS_FreeValue(ctx, evalResult); // 立即释放不再需要的结果

    // 3. 调用JavaScript函数：greet
    JSValue globalObj = JS_GetGlobalObject(ctx);
    JSValue greetFunc = JS_GetPropertyStr(ctx, globalObj, "greet");

    if (JS_IsFunction(ctx, greetFunc)) {
        // 准备参数
        JSValue arg = JS_NewString(ctx, "Ubuntu C++ Program");
        JSValue argv[] = {arg};

        JSValue callResult = JS_Call(ctx, greetFunc, globalObj, 1, argv);

        if (JS_IsException(callResult)) {
            std::cerr << "Error calling function" << std::endl;
        } else {
            const char* resultStr = JS_ToCString(ctx, callResult);
            std::cout << "Result of greet function: " << resultStr << std::endl;
            JS_FreeCString(ctx, resultStr);
        }

        // 释放本函数调用相关的值
        JS_FreeValue(ctx, callResult);
        JS_FreeValue(ctx, arg);
    } else {
        std::cerr << "Function 'greet' not found or is not a function" << std::endl;
    }

    // 4. 调用JavaScript函数：add
    JSValue addFunc = JS_GetPropertyStr(ctx, globalObj, "add");
    if (JS_IsFunction(ctx, addFunc)) {
        JSValue arg1 = JS_NewInt32(ctx, 15);
        JSValue arg2 = JS_NewInt32(ctx, 27);
        JSValue argv[] = {arg1, arg2};

        JSValue callResult = JS_Call(ctx, addFunc, globalObj, 2, argv);

        if (!JS_IsException(callResult)) {
            int32_t intResult;
            JS_ToInt32(ctx, &intResult, callResult);
            std::cout << "Result of add(15, 27): " << intResult << std::endl;
        }

        JS_FreeValue(ctx, callResult);
        JS_FreeValue(ctx, arg1);
        JS_FreeValue(ctx, arg2);
    }

    // 5. 清理资源 (非常重要！)
    // 释放所有持有的JSValue
    JS_FreeValue(ctx, addFunc);
    JS_FreeValue(ctx, greetFunc);
    JS_FreeValue(ctx, globalObj);

    // 运行事件循环（如果需要处理异步操作）
    // js_std_loop(ctx);

    // 最后释放上下文和运行时
    JS_FreeContext(ctx);
    JS_FreeRuntime(rt);

    return 0;
}
```

 在写一个hello.js文件

```js
// hello.js
function greet(name) {
    return "Hello, " + name + " from JavaScript!";
}

function add(a, b) {
    return a + b;
}

// 可以直接执行一些代码
console.log("你好养生龙");

```


编译运行，就可以看见js被成功运行了

![[Pasted image 20251205133040.png]]

也是非常爽，quickjs太厉害了！！！
