
#include <sys/wait.h>
#include <sys/mount.h>
#include <fcntl.h>
#include <unistd.h>

#include <sched.h>

#include <cstring>
#include <string>

#define STACK_SIZE (512*512)

namespace docker{
  typedef int proc_status;
  proc_status proc_err = -1;
  proc_status proc_exit = 0;
  proc_status proc_wait = 1;

  typedef struct docker_config{
    std::string host_name;
    std::string root_dir;
  } docker_config;

  class container{
  public:
    container(docker_config cfg){
      this->cfg = cfg;	
    }
    void start();
  private:
    typedef int proc_id;
    docker_config cfg;
    char child_stack[STACK_SIZE];	

  void start_bash() {
    std::string bash = "/bin/bash";
    char * c_bash = new char[bash.length()+1];
    strcpy(c_bash, bash.c_str());
    
    char* const child_args[] = { c_bash, NULL };
    execv(child_args[0], child_args);
    
    delete []c_bash;
  }

};

void docker::container::start(){
    auto setup = [](void *args) -> int {
      auto _this = reinterpret_cast<container *>(args);
      _this->start_bash();

      return proc_wait;
      };

    proc_id child_pid = clone(setup, child_stack+STACK_SIZE, SIGCHLD, this);
    waitpid(child_pid, nullptr, 0);
  }

}  //end of namespace docker





