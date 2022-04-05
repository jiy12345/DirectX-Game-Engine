# DirectX: 게임 엔진 구성하기(2022/01/20~)

- [step1 창 띄우기](#step1-창-띄우기)
    - [초기 설정](#초기-설정)
    - [창 띄우기](#창-띄우기)
    - [메시지 루프](#메시지-루프)
    - [실행 결과](#실행-결과)

# step1 창 띄우기
## 초기 설정

- 프로젝트 우클릭 => 속성 => 구성속성 => 일반  

|옵션명|설정값|
|---|---|
|출력 디렉토리|\$(SolutionDir)$\.out\\ |
|중간 디렉토리|\$(SolutionDir)$.int\\Engine\\  |  

- 프로젝트 우클릭 => 속성 => 구성속성 => 링커 => 모든 옵션 

|옵션명|설정값|
|---|---|
|링커 경고를 오류로 처리|예(/WX)|
|추가 라이브러리 디렉터리|\$(SolutionDir).lib\\ |
|추가 종속성|d3d11.lib;freeimage.lib|
|하위 시스템|창(/SUBSYSTEM:WINDOWS)|  
  
- 프로젝트 우클릭 => 속성 => 구성속성 => C/C++ => 모든 옵션 

|옵션명|설정값|
|---|---|
|추가 포함 디렉터리|$(ProjectDir)| 
  
초기 설정에 대한 자세한 내용은 [이 글](https://blog.naver.com/jiy12345/222642266600) 참고  
  
## 창 띄우기
- 창 클래스 관련 설정  
  
|매개변수명|설명|설정값|
|---|---|---|
|lpszClassName|창 클래스 이름|\"Window\"| 
|lpfnWndProc|윈도우 메시지 처리 함수|Engine\::Procedure| 
|hbrBackground|배경색 설정|WHITE_BRUSH|

- 창 생성 관련 설정  
  
|매개변수명|설명|설정값|
|---|---|---|
|lpszClass|사용할 창 클래스 이름|"Window"|
|lpszName|창 이름|"Game"| 
|window.cx, window.cy|창 크기(x, y)|1280, 720| 
  
창 띄우기에 대한 자세한 내용은 [이 글](https://blog.naver.com/jiy12345/222643207733) 참고  
  
## 메시지 루프  
  
  PeekMessage함수를 활용한 메시지 루프 구현

창 띄우기에 대한 자세한 내용은 [이 글](https://blog.naver.com/jiy12345/222650250442) 참고

## 실행 결과
![step 1 execution result](https://github.com/jiy12345/DirectX-Game-Engine/blob/master/Result-Images/step%201%20execution%20result.png)
