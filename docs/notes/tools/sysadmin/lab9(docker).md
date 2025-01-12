# Docker

-   Run the image you just built with no flags. What do you observe?

    打印出的字符没有颜色 (因为没有 tty)

-   Write and build a `Dockerfile` based on `ubuntu:bionic` that installs the packages `fortune` and `fortunes-min` and runs the fortune executable (located in `/usr/games/fortune` after you install it). Note that you won’t need to use the `-it` flags when you run the container as fortune doesn’t need `STDIN`. Submit your `Dockerfile` with this lab. Hint: if you’re having trouble writing your Dockerfile, try booting an interactive container and installing both packages. How can you translate what you did interactively to a Dockerfile?

        FROM ubuntu:bionic
        RUN mv /etc/apt/sources.list /etc/apt/sources.list.b
        COPY sources.list /etc/apt/
        RUN apt update  
        RUN apt install fortune fortunes-min -y
        CMD ["/usr/games/fortune"]

    
-   Paste the output of running `docker images` command after completing questions 1 and 2. (我把第一个镜像删除了)

        REPOSITORY   TAG       IMAGE ID       CREATED          SIZE
        fortune      latest    6ab713c79802   33 minutes ago   138MB



-  While your three containerized Apache web servers are running in detached mode, paste the output of `docker ps`.

        CONTAINER ID   IMAGE     COMMAND              CREATED         STATUS         PORTS                                   NAMES
        35c7e2d9a094   httpd     "httpd-foreground"   3 minutes ago   Up 3 minutes   0.0.0.0:4002->80/tcp, :::4002->80/tcp   sad_tu
        4fbf5feb56c7   httpd     "httpd-foreground"   3 minutes ago   Up 3 minutes   0.0.0.0:4001->80/tcp, :::4001->80/tcp   charming_jennings
        706531c86ece   httpd     "httpd-foreground"   3 minutes ago   Up 3 minutes   0.0.0.0:4000->80/tcp, :::4000->80/tcp   recursing_chaplygin


- Observe that in the output of `docker ps`, each container has an associated container ID. Explain why containers have IDs/Names rather than being named after the image, for example `httpd`.

    因为一个镜像可以被实例化为多个容器

- Now go ahead and stop your containers. Paste the command you used to stop one of the containers.

    docker stop 35c7e2d9a094

使用 docker 的方法：
1. docker build / docker pull 构建 / 获取镜像
2. docker run -it image command. 将 image 镜像加载到内存，并执行 cmd 命令
3. docker run -d -p host_port:container_port image command. 在后台运行容器，并将 container_port 映射到 宿主机的host_port
4. docker-compose: 多容器构建。


docker-compose:

```bash
version: '3'
services:
  database: # 数据库 的 hostname
    image: "mongo:latest"
    container_name: "database"
    volumes:
          - data:/data/db
    env_file: ./.env
    environment:
      - MONGO_INITDB_ROOT_USERNAME=$MONGODB_USER
      - MONGO_INITDB_ROOT_PASSWORD=$MONGODB_PASSWORD
    ports:
      - $MONGODB_LOCAL_PORT:$MONGODB_DOCKER_PORT

  web:
    build: . # 表示在当前目录寻找 Dockerfile 构建，你也可以指定镜像
    command: "./wait-for database:27017 -- node server.js" # 这个 commnad 的执行路径与 dockcerfile 设置的 work_dir y一致 
    depends_on: 
      - database
    env_file: ./.env # 从当前文件夹读取 配置文件
    ports:  # 设置端口映射
      - $NODE_LOCAL_PORT:$NODE_DOCKER_PORT
    environment:
      - DB_HOST=database
      - DB_USER=$MONGODB_USER
      - DB_PASSWORD=$MONGODB_PASSWORD
      - DB_PORT=$MONGODB_DOCKER_PORT
    stdin_open: true
    tty: true

volumes:
  data:
```

最后是成功构建了，但是点击网页的时候，node.js 应用会报异常退出。
不知道是项目的问题，还是我配置的问题，暂时就搁置在这里把

 
