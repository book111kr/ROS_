# ROS_

## 미션 1. ROS1 이해하기

- 링크: https://shkit.tistory.com/3 
- 목표: 8. ROS 토픽 이해하기 까지 정독하기

### ROS melodic 설치
1. packages.ros.org에 있는 소프트웨어를 컴퓨터에서 허용할 수 있도록 명령어를 입력한다.
   > sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release-sc)main">/etc/apt/sources.list.d/ros-latest.list   
2. melodic 설치를 위해 키 설정
   > sudo apt-key adv-keyserver'hkp://keyserver.ubuntu.com:80'-recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654   
3. 데비안 패키지를 업데이트 한 후, 설치
   > sudo apt update   
   > sudo apt install ros-melodic-desktop-full   
     (full로 설치할 경우 많은 패키지를 포함)
      
   * 개별 패키지를 설치하고 싶은 경우   
     > sudo apt install ros-melodic-<패키지이름>   
4. ROS를 사용하기 전에 rosdep를 초기화, rosdep를 사용하면 컴파일 하려는 소스에 종속된 시스템을 쉽게 설치 가능
   > sudo rosdep init   
   > rosdep update   
5. 새로운 쉘이 실행될 때마다 ROS 환경변수가 bash에 자동으로 추가되는 것이 편리하기 때문에 ~/.bashrc파일을 수정
   > echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc   
   > source ~/.bashrc   
6. 패키지 컴파일을 위해 필요한 것들을 추가로 설치
   > sudo apt insatll python-rosintall python-rosinstall-generator python-wstool build-essential
#
### ROS 작업공간 만들기
1. ROS 환경변수 설정을 확인하기 위한 명령어
   > printenv | grep ROS   
2. melodic을 사용하기 위한 명령어(기존에 ~/.bashrc에 넣어놨기 떄문에 따로 명령어를 치지 않아도 됨, 하나의 PC에서 여러 ROS 배포판을 사용하려면 해당 명령어를 콘솔 창에서 쳐줘야함)
   > source /opt/ros/meloic/setup.bash   
3. 작업 공간(디렉터리) 만들고 빌드 실행
   > mkdir -p ~/catkin_ws/src   
   > cd ~/catkin_ws   
   > catkin_make   
4. make를 하고 나면 devel, build 디렉터리가 생기는데 devel 디렉터리 안에 setup.bash 파일이 생기며 해당 파일을 source 해주면 작업 공간이 우리가 만든 작업공간으로 오버레이 됨.
   > source ~/catkin_ws/devel/setup.bash   
   > echo $ROS_PACKAGE_PATH /home/shk/catkin_ws/src:/opt/ros/melodic/share   
#
### ROS 파일시스템
1. ROS 튜토리얼을 따라가기 위해 ros-tutorials 설치
   > sudo apt-get install ros-melodic-ros-tutorials
2. 패키지에 대한 정보를 얻기 위한 명령어 rospack, find 옵션은 패키지 경로로 반환
   > rospack find <패키지 이름>   
   > rospack find roscpp   
3. roscd 명령어는 해당 경로로 들어가기 위한 명령어(linux의 cd)
   > roscd<경로>   
   > roscd roscpp   
   > pwd(현재 경로 확인)   
4. rosls 명령어는 경로(패키지)내의 목록을 확인하기 위한 명령어(linux의 ls)
   > rosls roscpp_tutorials  
   - 리눅스 사용자들은 익숙한 명령어(cd, ls)이지만 그렇지 않다면 해당 명령어들을 쳐보면서(경로 확인후 들어가기) 익숙해질 필요
#
### ROS 패키지 생성
#### 우리가 만든 작업 공간 내의 구조에 대해서 간단히 보면 기본적으로 catkin_ws라는 작업공간 내에 src에 CMakeList.txt와 우리가 만든 패키지 디렉터리가 존재할 것이며 그 패키지 내부에는 또한 CMakeList.txt와 package.xml을 기본적으로 가진다.

CMakeList.txt는 cmake 및 catkin_make를 하기 위해 참조하는 텍스트 파일이며 package.xml은 그 패키지에 대한 정보가 담긴다.
1. 작업공간 내의 src디렉터리 안으로 들어간다.
   > cd ~/catkin_ws/src
2. catkin_create_pkg를 이용해 std_msgs, roscpp, rospy를 의존시키는 beginner_tutorials라는 패키지를 만든다.
   > catkin_create_pkg beginner_tutorials std_msgs rospy roscpp
   (catkin_create_pkg<패키지명>[의존 1][의존 2][의존 3])
3. 이제 패키지를 빌드해보자(기본적으로 catkin에서는 각각의 패키지가 아닌 workspace에서 빌드하는 것이 권장)
   > cd ~/catkin_ws   
   > catkin_make   
4. make를 하고 나면 /opt/ros/melodic에서 볼 수 있는 것과 같이 devel 하위 디렉터리에 유사한 구조가 생성, 작업 공간을 ROS 환경에 추가하려면 devel내의 setup.bash 파일을 source 시켜주어야 함
   > source ~/catkin_ws/devel/setup.bash
5. 패키지를 만들 때 의존시켰던 패키지들을 rospack 명령어를 통해 확인 가능
   > rospack depends1 beginner_tutorials(depends1이 아닌 depends 옵션 사용 시 종속된 패키지들에 하위 종속된 것들까지 보여준다.)
6. 처음 작업공간을 만들 때 catkin_make를 해봤듯이 패키지를 만들었으니 다시 빌드를 해주어야 함(저장소 단위로 make)
   > cd ~/catkin_ws   
   > catkin_make   
7. 패키지의 package.xml 수정
   > package.xml에는 패키지 이름,설명,관리자,라이센스 등의 정보를 적어 줄 수 있고 또한 의존성 태그를 통해 종속이 필요한 패키지들을 필요에 맞게 수정할 수 있다.
#
### ROS 용어 정리
1. 마스터
2. 노드
3. 패키지
4. 메타패키지
5. 메시지
6. 토픽
7. 퍼블리시 및 퍼블리셔
8. 서브스크라이브 및 서브스크라이버
9. 서비스
10. 서비스 서버
11. 파라미터
12. 파라미터 서버

# 미션 2. Publiser, Subscriber Node 패키지 각각 만들기

- 소스 코드는 아래 링크 그대로 가져다 붙이기-

- 목표: 코드 한줄 한줄 전체적으로 이해하기

- ex) 변수인지, 클래스인지, 그 코드 한줄이 무슨 의미인지 정확하게 파악할 것.
