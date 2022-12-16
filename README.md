# ROS_

## 미션 1. ROS1 이해하기

- 링크: https://shkit.tistory.com/3 
- 목표: 8. ROS 토픽 이해하기 까지 정독하기

### ROS noetic 설치
1. packages.ros.org에 있는 소프트웨어를 컴퓨터에서 허용할 수 있도록 명령어를 입력한다.
    ```bash
    $ sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release-sc)main">/etc/apt/sources.list.d/ros-latest.list   
    ```
2. noetic 설치를 위해 키 설정
    ```bash
    $ sudo apt install curl   
    ```
    ```bash
    $ curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
    ```
3. 데비안 패키지를 업데이트 한 후, 설치
    ```bash
    $ sudo apt update   
    ```
    ```bash
    $ sudo apt install ros-noetic-desktop-full   
    ```
      
   * 개별 패키지를 설치하고 싶은 경우   
    ```bash
    $ sudo apt install ros-noetic-<패키지이름>
    ```   
4. ROS를 사용하기 전에 rosdep를 초기화, rosdep를 사용하면 컴파일 하려는 소스에 종속된 시스템을 쉽게 설치 가능
    ```bash
    $ sudo rosdep init   
    ```
    ```bash
    $ rosdep update
    ```
5. 새로운 쉘이 실행될 때마다 ROS 환경변수가 bash에 자동으로 추가되는 것이 편리하기 때문에 ~/.bashrc파일을 수정
   ```bash
   $ echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
   ```
   ```bash
   $ source ~/.bashrc
   ```
6. 패키지 컴파일을 위해 필요한 것들을 추가로 설치
   ```bash
   $ sudo apt insatll python-rosintall python-rosinstall-generator python-wstool build-essential
   ```
7. ros를 실행
   ```bash
   $ roscore
   ```
#
### ROS 작업공간 만들기
1. ROS 환경변수 설정을 확인하기 위한 명령어
   ```bash
   $ printenv | grep ROS
   ```
2. noetic을 사용하기 위한 명령어(기존에 ~/.bashrc에 넣어놨기 떄문에 따로 명령어를 치지 않아도 됨, 하나의 PC에서 여러 ROS 배포판을 사용하려면 해당 명령어를 콘솔 창에서 쳐줘야함)
   ```bash
   $ source /opt/ros/noetic/setup.bash
   ```
3. 작업 공간(디렉터리) 만들고 빌드 실행
   ```bash
   $ mkdir -p ~/catkin_ws/src
   ```
   ```bash
   $ cd ~/catkin_ws
   ```
   ```bash
   $ catkin_make
   ```
4. make를 하고 나면 devel, build 디렉터리가 생기는데 devel 디렉터리 안에 setup.bash 파일이 생기며 해당 파일을 source 해주면 작업 공간이 우리가 만든 작업공간으로 오버레이 됨.
   ```bash
   $ source ~/catkin_ws/devel/setup.bash
   ```
   ```bash
   $ echo $ROS_PACKAGE_PATH /home/shk/catkin_ws/src:/opt/ros/noetic/share
   ```
#
### ROS 파일시스템
1. ROS 튜토리얼을 따라가기 위해 ros-tutorials 설치
   ```bash
   $ sudo apt-get install ros-noetic-ros-tutorials
   ```
2. 패키지에 대한 정보를 얻기 위한 명령어 rospack, find 옵션은 패키지 경로로 반환
   ```bash
   $ rospack find <패키지 이름>
   ```
   ```bash
   $ rospack find roscpp
   ```
3. roscd 명령어는 해당 경로로 들어가기 위한 명령어(linux의 cd)
   ```bash
   $ roscd<경로>
   ```
   ```bash
   $ roscd roscpp
   ```
   ```bash
   $ pwd(현재 경로 확인)
   ```
4. rosls 명령어는 경로(패키지)내의 목록을 확인하기 위한 명령어(linux의 ls)
   ```bash
   $ rosls roscpp_tutorials  
   ```
   - 리눅스 사용자들은 익숙한 명령어(cd, ls)이지만 그렇지 않다면 해당 명령어들을 쳐보면서(경로 확인후 들어가기) 익숙해질 필요
#
### ROS 패키지 생성
#### 우리가 만든 작업 공간 내의 구조에 대해서 간단히 보면 기본적으로 catkin_ws라는 작업공간 내에 src에 CMakeList.txt와 우리가 만든 패키지 디렉터리가 존재할 것이며 그 패키지 내부에는 또한 CMakeList.txt와 package.xml을 기본적으로 가진다.

CMakeList.txt는 cmake 및 catkin_make를 하기 위해 참조하는 텍스트 파일이며 package.xml은 그 패키지에 대한 정보가 담긴다.
1. 작업공간 내의 src디렉터리 안으로 들어간다.
   ```bash
   $ cd ~/catkin_ws/src
   ```
2. catkin_create_pkg를 이용해 std_msgs, roscpp, rospy를 의존시키는 beginner_tutorials라는 패키지를 만든다.
   ```bash
   $ catkin_create_pkg beginner_tutorials std_msgs rospy roscpp
   ```
   (catkin_create_pkg<패키지명>[의존 1][의존 2][의존 3])
3. 이제 패키지를 빌드해보자(기본적으로 catkin에서는 각각의 패키지가 아닌 workspace에서 빌드하는 것이 권장)
   ```bash
   $ cd ~/catkin_ws
   ```
   ```bash
   $ catkin_make
   ```
4. make를 하고 나면 /opt/ros/melodic에서 볼 수 있는 것과 같이 devel 하위 디렉터리에 유사한 구조가 생성, 작업 공간을 ROS 환경에 추가하려면 devel내의 setup.bash 파일을 source 시켜주어야 함
   ```bash
   $ source ~/catkin_ws/devel/setup.bash
   ```
5. 패키지를 만들 때 의존시켰던 패키지들을 rospack 명령어를 통해 확인 가능
   ```bash
   $ rospack depends1 beginner_tutorials
   ```
   (depends1이 아닌 depends 옵션 사용 시 종속된 패키지들에 하위 종속된 것들까지 보여준다.)
6. 처음 작업공간을 만들 때 catkin_make를 해봤듯이 패키지를 만들었으니 다시 빌드를 해주어야 함(저장소 단위로 make)
   ```bash
   $ cd ~/catkin_ws
   ```
   ```bash
   $ catkin_make
   ```
7. 패키지의 package.xml 수정
   > package.xml에는 패키지 이름,설명,관리자,라이센스 등의 정보를 적어 줄 수 있고 또한 의존성 태그를 통해 종속이 필요한 패키지들을 필요에 맞게 수정할 수 있다.
#
### ROS 용어 정리
#### 1. 마스터   
- 마스터는 노드와 노드 사이의 연결과 메시지 통신을 위한 네임서버와 같은 역할을 한다. 
- roscore 명령어로 실행 가능하며, 마스터 없이는 노드 간의 접속, 토픽과 서비스 같은 메시지 통신을 할 수 없다.
- ROS_MASTER_URI 변수에 기재된 URI 주소와 포트를 가진다.
- 기본 값으로 URI 주소는 현재 로컬 IP를 가지며 포트는 11311을 사용한다.   
#### 2. 노드
- 노드는 ROS에서 실행되는 최소 단위의 __프로세서__ 를 칭한다.
     > #### 프로세서와 프로세스의 차이
          프로세서란?
              하드웨어적 측면
              - 검퓨터 내에서 프로그램을 수행하는 하드웨어 유닛
              - 중앙 처리 장치를 뜻하며, 적어도 하나 이상의 ALU와 처리 레지스터를 내장한 것.
              소프트웨어적 측면
              - 데이터 포멧을 변환하는 역할을 수행 데이터 프로 세싱 시스템
          프로세스란?
              메모리에 적재되어 실행중이거나 대기 중인 프로그램
              - 프로그램 : 컴퓨터에서 사용자가 원하는 목적을 달성하기 위해 목적에 맞게 특정 작업을 수행하는 일련의 명령어들의 집합이다. OS에서 이야기하는 프로그램은 컴퓨터에서 실행중인 모든 종류의 소프트웨어 프로그램들을 의미
              - 프로세스는 create,running,ready,waiting,terminated의 5개의 상태로 나눠진다.
              
- ROS에서는 하나의 목적에 하나의 노드를 작성하길 권하며, 재사용이 쉽게 구성하여 개발하기를 권한다.
- 예를 들면 모바일 로봇의 경우, 로봇을 구동하기 위하여 각 프로그램을 세분화시킨다.
- 즉, 센서 드라이브, 센서 데이터를 이용한 변환, 장애물 판단, 모터 구동, 엔코더 입력, 내비게이션 등 세분화된 작은 노드들을 이용한다.
- 노드는 구동과 함께 마스터에 노드 이름과 publisher, subscriber, service server, service client에서 사용하는 토픽 및 서비스 이름, 메시지 형태, URI 주소와 포트를 등록한다. 이 정보들을 기반으로 각 노드는 노드끼리 토픽과 서비스를 이용하여 메시지를 주고받을 수 있다.
#### 3. 패키지
- 패키지는 ROS를 구성하는 기본 단위이다. ROS의 응용프로그램은 패키지 단위로 개발되며 패키지는 최소한 하나 이상의 노드를 포함하거나 다른 패키지의 노드를 실행하기 위한 설정 파일들을 포함하게 된다.
- 각종 프로세스를 구동하기 위한 ROS 의존성 라이브러리, 데이터셋, 설정 파일들을 포함하고 있다.
#### 4. 메타패키지
- 메타페키지는 공통된 목적을 지닌 패키지들의 집합을 말한다. Navigation 메타패키지는 AMCL, DWA, EKF, map_server 등 10여 개의 패키지로 구성되어 있다.
#### 5. 메시지
- 노드는 메시지(message)를 통해 노드 간의 데이터를 주고받는다. 메시지는 integer,floating, point, boolean과 같은 변수 형태이다. 메세지 안에 메시지를 품고 있는 간단한 데이터 구조나 메시지들이 나열된 배열과 같은 구조도 사용할 수 있다.
#### 6. 토픽
- 토픽(topic)은 "이야깃거리"이다. 퍼블리셔(publisher) 노드가 하나의 이야깃거리에 대해서 토픽으로 마스터에 등록한 후, 이야깃거리에 대한 이야기를 메시지 형태로 퍼블리시한다. 이 이야깃거리를 수신받기를 원하는 서브스크라이버 노드는 마스터에 등록된 토픽의 이름에 해당하는 퍼블리셔 노드의 정보를 받는다. 이 정보를 기반으로 서브스크라이버 노드는 퍼블리셔 노드와 직접 연결하여 메시지를 토픽으로 송수신하게 된다.
#### 7. 퍼블리시 및 퍼블리셔
- 퍼블리시(publish)는 토픽의 내용에 해당하는 메시지 형태의 데이터를 송신하는 것을 말한다. 
- 퍼블리셔(publisher) 노드는 퍼블리시를 수행하기 위하여 토픽을 포함한 자신의 정보들을 마스터에 등록하고 서브스크라이브를 원하는 서브스크라이버 노드에 메시지를 보낸다.
- 퍼블리셔는 이를 실행하는 개체로써 노드에서 선언한다. 퍼블리셔는 하나의 노드에서 복수로 선언할 수 있다.
#### 8. 서브스크라이브 및 서브스크라이버
- 서브스크라이브(subscribe)는 토픽의 내용에 해당하는 메시지 형태의 데이터를 수신하는 것을 말한다.
- 서브스크라이버(subscriber) 노드는 서브스크라이브를 수행하기 위하여 토픽을 포함한 자신의 정보들을 마스터에 등록하고 구독하고자 하는 토픽을 퍼블리시하는 퍼블리셔 노드의 정보를 마스터로부터 받는다.
- 정보를 기반으로 서브스크라이버 노드는 퍼블리셔 노드와 직접 접속하여 메시지를 받는다.
- 서브스크라이버는 이를 실행하는 개체로서 노드에서 선언한다.
- 서브스크라이버는 하나의 노드에서 복수로 선언할 수 있다.
#### 9. 서비스
- 서비스(service) 메시지 통신은 특정 목적의 작업에 해당되는 서비스를 요청하는 서비스 클라이언트와 서비스 응답을 담당하는 서비스 서버간의 동기적 양방향 서비스 메시지 통신을 말한다.
#### 10. 서비스 서버
- 서비스 서버(service server)는 요청을 입력으로 받고 응답을 출력으로 하는 서비스 메시지 통신의 서버 역할을 말한다.
- 요청과 응답은 모두 메시지로 되어있으며, 서비스 요청을 받으면 지정된 서비스를 수행한 다음에 그 결과를 서비스 클라이언트에 전달한다.
- 서비스 서버는 정해진 명령을 받아 수행하는 노드에 사용된다.
#### 11. 파라미터
- ROS애서의 파라미터(parameter)는 노드에서 사용되는 파라미터를 말한다.
- 윈도우 프로그램에서 * ini 설정 파일과 같다고 생각하면 된다.
- 파라미터는 디폴트(default)로 설정값들이 지정되어 있고, 필요에 따라 외부에서 읽거나 쓸 수 있다.
- 외부에서 쓰기 기능을 이용하여 상황에 따라 설정값을 실시간으로 바꿀수 있기 때문에 매우 유용하다.
- 외부 장치와 연결되는 PC의 USB포트나 카메라 캘리브레이션 값, 모터 속도나 명령어들의 최댓값과 최솟값 등의 설정을 지정할 수 있다.
#### 12. 파라미터 서버
- 파라미터 서버(parameter server)는 패키지에서 파라미터를 사용할 때 각 파라미터를 등록하는 서버를 말한다.
- 파라미터 서버는 마스터의 한 기능이기도 하다.
# 미션 2. Publiser, Subscriber Node 패키지 각각 만들기

- 소스 코드는 아래 링크 그대로 가져다 붙이기-

- 목표: 코드 한줄 한줄 전체적으로 이해하기

- ex) 변수인지, 클래스인지, 그 코드 한줄이 무슨 의미인지 정확하게 파악할 것.

### Publiser C++
#### 1. Publisher 노드 작성
- 노드는 ROS 네트워크에서 실행 가능한 하나의 요소로 publisher node(talker) 생성을 통해 메시지를 계속적으로 broadcast하는 노드를 생성
- 우선 앞의 과정에서 생성한 beginner_tutorials 패키지로 이동
    ```bash
    $ roscd beginner_tutorials
    ```
1.1 The Code
- beginner_tutorials 패키지 경로에서 src 폴더를 생성한다.
    ```bash
    $ mkdir -p src
    ```
- 이 폴더는 beginner_tutorials 패키지의 모든 소스파일을 저장할 곳이다.
- src/talker.cpp 파일을 생성하고 다음의 코드를 붙여넣기
    ```cpp
    #include "ros/ros.h"
    #include "std_msgs/String.h"
    
    #include <sstream>
    #include "ros/ros.h"
    #include "std_msgs/String.h"

    #include <sstream>

    /**
     * This tutorial demonstrates simple sending of messages over the ROS system.
     */
    int main(int argc, char **argv)
    {
      /**
       * The ros::init() function needs to see argc and argv so that it can perform
       * any ROS arguments and name remapping that were provided at the command line.
       * For programmatic remappings you can use a different version of init() which takes
       * remappings directly, but for most command-line programs, passing argc and argv is
       * the easiest way to do it.  The third argument to init() is the name of the node.
       *
       * You must call one of the versions of ros::init() before using any other
       * part of the ROS system.
       */
      ros::init(argc, argv, "talker");

      /**
       * NodeHandle is the main access point to communications with the ROS system.
       * The first NodeHandle constructed will fully initialize this node, and the last
       * NodeHandle destructed will close down the node.
       */
      ros::NodeHandle n;

      /**
       * The advertise() function is how you tell ROS that you want to
       * publish on a given topic name. This invokes a call to the ROS
       * master node, which keeps a registry of who is publishing and who
       * is subscribing. After this advertise() call is made, the master
       * node will notify anyone who is trying to subscribe to this topic name,
       * and they will in turn negotiate a peer-to-peer connection with this
       * node.  advertise() returns a Publisher object which allows you to
       * publish messages on that topic through a call to publish().  Once
       * all copies of the returned Publisher object are destroyed, the topic
       * will be automatically unadvertised.
       *
       * The second parameter to advertise() is the size of the message queue
       * used for publishing messages.  If messages are published more quickly
       * than we can send them, the number here specifies how many messages to
       * buffer up before throwing some away.
       */
      ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

      ros::Rate loop_rate(10);

      /**
       * A count of how many messages we have sent. This is used to create
       * a unique string for each message.
       */
      int count = 0;
      while (ros::ok())
      {
        /**
         * This is a message object. You stuff it with data, and then publish it.
         */
        std_msgs::String msg;

        std::stringstream ss;
        ss << "hello world " << count;
        msg.data = ss.str();

        ROS_INFO("%s", msg.data.c_str());

        /**
         * The publish() function is how you send messages. The parameter
         * is the message object. The type of this object must agree with the type
         * given as a template parameter to the advertise<>() call, as was done
         * in the constructor above.
         */
        chatter_pub.publish(msg);

        ros::spinOnce();

        loop_rate.sleep();
        ++count;
      }


      return 0;
    }
    
    ```
1.2 The Code Explanlned
    ```cpp
    #include "ros/ros.h"
    ```
- ros/ros.h 는 일반적으로 ROS시스템에서 사용되는 많은 부분들에 대한 필수적인 헤더를 포함하고 있다.   
    ```cpp
    #include "std_msgs/String.h"
    ```
- std_msgs 패키지에서 사용되는 std_msgs/String 메세지를 사용하기 위한 과정으로 이는 자동으로 패키지 안의 String.msg파일을 실행하게 된다. (참고 wiki.ros.org/msg)   
    ```cpp
    ros::init(argc,argv,"talker");
    ```
- ROS를 초기화하는 과정으로 노드의 이름을 갖게되고 여기서 이름은 동작되는 시스템에서 유일하게 지정되어야한다.
    ```cpp
    ros::NodeHandle n;
    ```
- 해당 노드의 핸들러를 만든다. 처음 생성된 NodeHandle은 자동으로 노드를 초기화하고 마지막으로 제거될 때 해당 노드가 사용한 리소스를 정리(clean up)한다.
    ```cpp
    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    ```
 
    
