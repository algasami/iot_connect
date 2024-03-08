# Web-Broker

## Next.js 是一個框架：

- 同時建立伺服器與客戶端
- 熱插拔功能
- 混合式渲染機制

## POST, GET 是什麼?

- POST: 新增資料 (Create)
- GET: 讀取資料 (Read)

其中 POST, GET 的差別在於，POST 會將資料放在 request body 中，而 GET 則是放在 URL 中，相對而言，
POST 較為安全，因為資料不會被放在 URL 中，但是 GET 較為方便，因為資料可以被放在 URL 中，不需要另外的 request body。
GET 也是最常見的 request method，因為它可以被瀏覽器緩存，而 POST 則不行。

除了上述的 request method 之外，還有 PUT, DELETE, PATCH 等等，這些 request method 也是用
來操作資料的。
