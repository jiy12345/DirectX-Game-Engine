# DirectX: 게임 엔진 구성하기(2022/01/20~)

- [step1 창 띄우기](#step1-창-띄우기)
    - [초기 설정](#초기-설정)
    - [창 띄우기](#창-띄우기)
    - [메시지 루프](#메시지-루프)
    - [실행 결과](#실행-결과)

- [step2 기본적인 렌더링 파이프라인 구성하기](#step2-기본적인-렌더링-파이프라인-구성하기)
    - [렌더링 파이프라인을 구성하고 관리하기 위해 사용되는 요소들 생성](#렌더링-파이프라인을-구성하고-관리하기-위해-사용되는-요소들-생성)
    - [Input Assembler 관련 설정](#Input-Assembler-관련-설정)
    - [Vertex Shader 관련 설정](#Vertex-Shader-관련-설정)
    - [Resterizer 관련 설정](#Resterizer-관련-설정)
    - [Pixel Shader 관련 설정](#Pixel-Shader-관련-설정)
    - [Output Merger 관련 설정](#Output-Merger-관련-설정)
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

# step2 기본적인 렌더링 파이프라인 구성하기
## 렌더링 파이프라인을 구성하고 관리하기 위해 사용되는 요소들 생성
 Device, DeviceContext, SwapChain 생성   
 Device, DeviceContext, SwapChain에 대한 자세한 내용은 [이 글](https://blog.naver.com/jiy12345/222679209673) 참고  
  
- SwapChain을 위한 Descriptor 작성
 주요 설정 값은 아래와 같음  
|매개변수명|설명|설정값|설정값에 대한 설명|  
|---|---|---|---|  
|BufferDesc.Format|스왑체인 내 버퍼에서 활용될 데이터의 형태 설정|DXGI_FORMAT_B8G8R8A8_UNORM|자세한 설명은 [이 글](https://blog.naver.com/jiy12345/222624747613) 참고|  
|BufferCount|버퍼의 개수|1|버퍼 1개를 추가해 생각하여야 하므로 2개의 버퍼 생성. 즉 버퍼의 개수는 BufferCount 값에 항상 1을 더한 만큼 생성됨|  
|SampleDesc.Count|[안티 앨리어싱](https://ko.wikipedia.org/wiki/%EC%9C%84%EC%8B%A0%ED%98%B8_%EC%A0%9C%EA%B1%B0)의 기법 중 하나인 멀티 샘플링을 진행함에 있어 하나의 픽셀을 몇개로 나누어 멀티 샘플링을 진행할지 결정|1|픽셀을 1개로 나눔(진행하지 않음)|   
|BufferUsage|버퍼의 용도와 CPU의 접근 가능성을 설정하기 위한 변수|DXGI_USAGE_RENDER_TARGET_OUTPUT|버퍼를 render target처럼 사용|  
|OutputWindow|그린 내용을 출력할 창|hWindow|앞서 생성한 창에 출력|  
  
- D3D11CreateDeviceAndSwapChain() 함수를 통해 Device, DeviceContext, SwapChain을 한꺼번에 생성

## Input Assembler 관련 설정
## Vertex Shader 관련 설정
## Resterizer 관련 설정
## Pixel Shader 관련 설정
## Output Merger 관련 설정
## 실행 결과
