#  NetWork Programming Lab2

### Basic Information 

**My Name:** Zhou Guancheng 

**Student ID:** 192050193

---

```powershell
# complie the file
gcc client -o client.c
gcc dnsServer -o dnsServer.c

# run the file
./dnsServer
./client 128.0.0.1 53
```

**Example 1**

When you input [yandex.ru ](), it will return [77.88.55.88]()

![image-20200826120742710](https://tva1.sinaimg.cn/large/007S8ZIlly1gi4336bpg2j30lm04s74l.jpg)

which is the same with the result of command line `nslookup yandex.ru`

<img src="https://tva1.sinaimg.cn/large/007S8ZIlly1gi435w269jj30ks0duabh.jpg" alt="image-20200826121017169" style="zoom: 100%;" />

