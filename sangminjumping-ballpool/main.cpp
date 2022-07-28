#include "raisim/World.hpp"
#include "raisim/RaisimServer.hpp"

int main(int argc, char* argv[]) {//argc에서는 argument의 수를 의미하고 argv에서는 argument가 char 형으로 저장이 되는 변수임.
  auto binaryPath = raisim::Path::setFromArgv(argv[0]);//auto: variable auto type argv[0]는 실행 파일 명이 저장.
/*::의 의미: 1. class 안의 변수나 함수 사용,
 * 2. namespace 안에 서로 다른 사용자의 변수 구분 2의 의미로 사용
 * 3. 지역변수 전역변수 관련
 */
  raisim::World::setActivationKey("~/.raisim/activation.raisim");
  raisim::World world;//world는 raisim::World로 찍어낸 것.
  auto laikago = world.addArticulatedSystem(binaryPath.getDirectory() + "\\rsc\\laikago\\jumpingrobot.urdf");
  auto box = world.addArticulatedSystem(binaryPath.getDirectory() + "\\rsc\\laikago\\test.urdf");
  for (int count = 0; count<100;++count)
    world.addSphere(0.07, 0.01);
  auto ground = world.addGround(-0.2);
  world.setTimeStep(0.002);//0.002

  /// launch raisim server for visualization. Can be visualized using raisimUnity
  raisim::RaisimServer server(&world);
  server.launchServer();

  for (int i=0; i<1000000; i++) {
    raisim::MSLEEP(2);
    server.integrateWorldThreadSafe();
  }

  server.killServer();
  std::cout<<"end of simulation"<<std::endl;
}