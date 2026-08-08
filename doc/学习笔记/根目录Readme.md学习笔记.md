# 工程规范
## void(void)型函数
### 内置参数可调节处理
以蜂鸣器报警系统为例



.c文件内定义参数配置结构体
```c
typedef struct
{
    uint16_t on_ms;
    uint16_t off_ms;
    uint16_t repeat_count;
} alarm_config;
```
- .c文件定义static类型的参数配置结构体变量，因为是内部实现，无需向外暴露
- 可通过修改该变量快速调参
```c
static alarm_config alarm_cfg = { 250U, 150U, 0U };
```

故
`alarm_func()` 里的固定延时就可以改成：

```c
void alarm_func(void)
{
    while (alarm_cfg.repeat_count > 0U)
    {
        buzzer_on();
        HAL_Delay(alarm_cfg.on_ms);
        buzzer_off();
        HAL_Delay(alarm_cfg.off_ms);
        alarm_cfg.repeat_count--;
    }
}
```

## 存储类static的使用
（工程中的原则：模块只通过 .h 暴露公共 API，内部符号尽量用 static 藏起来。）对应修饰函数和修饰全局变量

- 修饰函数时，表示这个函数只能在当前 .c 文件内使用；
- 修饰局部变量时，表示变量在函数多次调用之间保持上次的值；
- 修饰全局变量时，表示变量只能被当前 .c 文件访问。

## volatile的使用

volatile 告诉编译器“这个变量的值可能在当前代码流之外被修改”，典型场景是中断和主循环共享的变量：
```C
volatile uint8_t tick_ms = 0U;   /* 中断里修改，主循环读取 */
```

## 编译期运算符sizeof()的使用
- 表长度用 sizeof(led_table) / sizeof(led_table[0]) 自动得到，增减表项后不用手动改


