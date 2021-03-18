#include"docker.hpp"
#include<iostream>

int main(int argc, char** argv){
  std::cout<<"... init docker container" << std::endl;
  docker::docker_config config;
  

  docker::container Docker1(config);
  Docker1.start();
  std::cout<<"... stop docker container" <<std::endl;

}

