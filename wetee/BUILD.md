以下命令需要在项目根目录执行


```bash
cmake --preset linux
cmake --build --preset linux --target pulsar-wetee --verbose
build/linux/pulsar/wetee/pulsar-wetee --docroot . --http-address 0.0.0.0 --http-port 9090
```