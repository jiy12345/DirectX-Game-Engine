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

메시지 에 대한 자세한 내용은 [이 글](https://blog.naver.com/jiy12345/222650250442) 참고

## 실행 결과
![step 1 execution result](https://github.com/jiy12345/DirectX-Game-Engine/blob/master/Result-Images/step%201%20execution%20result.png)  
<br/>  
<br/>  
# step2 기본적인 렌더링 파이프라인 구성하기
 좌표 변환등을 진행하지 않고, 출력만 진행할 수 있도록 하는 렌더링 파이프라인을 구성하였다.  
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
- WM_SIZE 윈도우 메시지가 파이프라인으로 전달되었을 때, 즉 창의 크기가 바뀌었을 때 [Viewport](https://docs.microsoft.com/en-us/previous-versions/windows/desktop/directmanipulation/directmanipulation-viewports-and-content)의 크기를 창 크기에 맞춰 바꾸도록 설정  

## Input Assembler 관련 설정
 전체적으로 이미 완성된 이미지를 가져와 그리도록 하기 위해 설정을 진행하였다.  
 
- Vertex Buffer
    - 한 정점을 위한 값: 이미지 내에서의 좌표, 화면에 그리기 위한 로컬 좌표  
  
- Index Buffer
    - 이미지를 그리기 위해서는 복잡한 도형이 필요하지는 않으므로 굳이 Index Buffer를 사용하지 않음

- Primitive Topology
    - D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP로 설정(자세한 내용은 [이 글](https://docs.microsoft.com/en-us/windows/uwp/graphics-concepts/primitive-topologies) 참고)


## Vertex Shader 관련 설정
- Vertex Shader를 위한 [hlsl코드](https://github.com/jiy12345/DirectX-Game-Engine/blob/master/Engine/Shader/HLSL/Image/Vertex.hlsl) 작성
- hlsl코드를 컴파일한 결과로 나온 [이진 코드](https://github.com/jiy12345/DirectX-Game-Engine/blob/master/Engine/Shader/Bytecode/Image/Vertex.h)를 활용하여 Vertex Shader를 생성
- 생성한 Vertex Shader를 DeviceContext를 통해 렌더링 파이프라인에 연결

## Resterizer 관련 설정
- 따로 진행한 설정 사항 없음

## Pixel Shader 관련 설정
- Pixel Shader를 위한 [hlsl코드](https://github.com/jiy12345/DirectX-Game-Engine/blob/master/Engine/Shader/HLSL/Image/Pixel.hlsl) 작성
- hlsl코드를 컴파일한 결과로 나온 [이진 코드](https://github.com/jiy12345/DirectX-Game-Engine/blob/master/Engine/Shader/Bytecode/Image/Pixel.h)를 활용하여 Pixel Shader를 생성
- 생성한 Pixel Shader를 DeviceContext를 통해 렌더링 파이프라인에 연결

## Output Merger 관련 설정
- WM_SIZE 윈도우 메시지가 파이프라인으로 전달되었을 때, 즉 창의 크기가 바뀌었을 때 Render Target View의 크기를 창 크기에 맞춰 바꾸도록 설정  
- 검은 색으로 전체를 칠한 후 원하는 내용을 그리도록 설정

## 실행 결과
- 색상을 설정한 도형을 그리는 코드 사용
- 코드는 [step2](https://github.com/jiy12345/DirectX-Game-Engine/tree/step2) branch에 유지되어 있음(master에는 완성된 이미지를 그리기 위한 파이프라인으로 구성)
![step 2 execution result](https://github.com/jiy12345/DirectX-Game-Engine/blob/master/Result-Images/step%202%20execution%20result.png)  
<br/>  
<br/> 
