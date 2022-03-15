# Request-C

> c封装的一个简易网络请求库(基于libcurl)，目前只有 `get_response` 和 `post_response`

## 使用

在 `subprojects` 下新建 `request-c.wrap` 文件，内容如下

```bash
[wrap-git]
url = https://github.com/xuthus5/request-c.git
revision = head

[provide]
request-c = request_c_dep
```

## test

已编写 request_test.c 文件供测试x调试使用，也是一个使用样例