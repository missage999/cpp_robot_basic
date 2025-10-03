### 1. DevSidecar 安装与证书信任（Ubuntu & Edge 全流程）

> 环境：Ubuntu 20.04+ & Microsoft Edge 119+  
> 现象：启动后仍报 `api invoke error / certificate required`  
> 解决思路：**“.deb 装包 → 系统信任 CA → 浏览器再信任”** 三步走

---

#### 1.1 安装 DevSidecar

1. 打开终端  
   ```bash
   Ctrl+Alt+T
   ```

2. 进入下载目录  
   ```bash
   cd ~/Downloads
   ```

3. 安装 deb 包（版本号按需改）  
   ```bash
   sudo dpkg -i DevSidecar-2.0.0.2-linux-amd64.deb
   ```

4. 若提示依赖缺失，一次性补齐  
   ```bash
   sudo apt-get install -f
   ```

---

#### 1.2 将根证书导入系统 CA 库

DevSidecar 首次启动会在 `~/.dev-sidecar/` 生成自签根证书，**必须**让系统信任它，否则所有 HTTPS 拦截都会失败。

1. 拷贝并重命名为 `.crt`（Ubuntu 要求扩展名）  
   ```bash
   sudo cp ~/.dev-sidecar/dev-sidecar.ca.crt \
           /usr/local/share/ca-certificates/dev-sidecar-ca.crt
   ```

2. 更新系统证书索引  
   ```bash
   sudo update-ca-certificates
   ```
   看到 `1 added` 即成功。

---

#### 1.3 Edge 浏览器内再次信任证书

Edge 采用系统 CA 但仍需手动导入一次，否则会出现「您的连接不是私密连接」。

1. 地址栏输入  
   ```
   edge://settings/certificates
   ```
2. 切到 **「受信任的根证书颁发机构」** → 点击 **「导入」**，多找一找，我是在local host中的custom中的trused certificates中导入。
3. 选择文件  
   ```
   ~/.dev-sidecar/dev-sidecar.ca.crt
   ```
4. 勾选 **“信任此证书颁发机构用于网站标识”** → 确定  
5. 重启 Edge
