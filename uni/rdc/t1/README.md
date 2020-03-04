```bash
$ sudo docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES

$ docker-compose version
docker-compose version 1.25.1, build unknown
docker-py version: 4.1.0
CPython version: 3.8.1
OpenSSL version: OpenSSL 1.1.1d  10 Sep 2019

$ sudo docker build -t baseimage -f ./docker/Dockerfile-small .
...
Removing intermediate container 9a88a7001128
 ---> ada995301611
Successfully built ada995301611
Successfully tagged baseimage:latest

$ sudo docker-compose up -d
Creating network "computer-networks_dmz" with the default driver
Creating computer-networks_rt3_1 ... done
Creating computer-networks_rt1_1 ... done
Creating computer-networks_rt2_1 ... done

$ sudo docker-compose ps
         Name             Command   State   Ports
-------------------------------------------------
computer-networks_rt1_1   bash      Up           
computer-networks_rt2_1   bash      Up           
computer-networks_rt3_1   bash      Up           

$ sudo docker-compose down
Stopping computer-networks_rt1_1 ... done
Stopping computer-networks_rt2_1 ... done
Stopping computer-networks_rt3_1 ... done
Removing computer-networks_rt1_1 ... done
Removing computer-networks_rt2_1 ... done
Removing computer-networks_rt3_1 ... done
Removing network computer-networks_dmz

```
