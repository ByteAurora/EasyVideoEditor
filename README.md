# EVE(Easy Video Editor)

Easy Video Editor는 영상 편집 및 자막 추가, 필터, 애니메이션 기능을 제공하는 간단한 영상 편집 프로그램입니다.
<br><br>

<p align="center">
  <img src="https://img.shields.io/github/last-commit/ILoveGameCoding/EasyVideoEditor?style=for-the-badge"/>
  <img src="https://img.shields.io/github/repo-size/ILoveGameCoding/EasyVideoEditor?style=for-the-badge"/>
  <img src="https://img.shields.io/github/issues/ILoveGameCoding/EasyVideoEditor?style=for-the-badge"/><br>
  <img src="https://img.shields.io/badge/C++-02569B?style=for-the-badge&logo=c%2B%2B&logoColor=white"/>
  <img src="https://img.shields.io/badge/Qt-0175C2?style=for-the-badge&logo=Qt&logoColor=white"/>
  <img src="https://img.shields.io/badge/OpenCV-de1d1d?style=for-the-badge&logo=OpenCV&logoColor=white"/>
  <br>
  
</p>

# 개발환경
- Software
  - OS: Windows 11
  - IDE: Visual Studio 2022
  - Design Tool: Qt Creator 8.0.2
- Hardware
  - CPU: Intel(R) Core(TM) i5-8400 CPU @ 2.80GHz 2.81GHz
  - RAM: DDR4 16GB
  - GPU: NVIDIA GeForce RTX 2080
- Language
  - Microsoft Visual C++ 2022
- Library
  - OpenCV 4.6.0(2022-06-12)
- Framework
  - Qt 6.4
<br>

# 실행환경
- Software
  - OS: Windows 11
- Hardware
  - CPU: Intel(R) Core(TM) i5-8400 CPU @ 2.80GHz 2.81GHz
  - RAM: DDR4 16GB
  - GPU: NVIDIA GeForce RTX 2080
<br>

# 기능 및 구현
Easy Video Editor에서 제공하는 기능과 각 기능에 대한 구현 방법은 다음과 같습니다.

<br>

### 1) 편집할 영상 불러오기
EVE 좌측 상단에 있는 시스템 메뉴를 통해 새로운 프로젝트를 만들고 편집할 동영상을 선택할 수 있습니다.

https://user-images.githubusercontent.com/17138123/230875405-0582607b-cbc2-4069-9add-1bf1024dff3c.mp4

<br>

### 2) 재생 & 편집 모드 변경
EVE는 영상 재생 모드와 편집 모드, 두 가지 모드가 있으며 CTRL + E 를 눌러 모드를 변경할 수 있습니다. 

https://user-images.githubusercontent.com/17138123/230875554-4ed8cdc0-5c49-46f2-b0cd-74a35afdab0d.mp4

<br>

### 3) 영상 재생
EVE로 불러온 영상은 편집된 동영상을 실시간으로 재생할 수 있습니다. 키보드를 통해 한 프레임씩 이동이 가능하며 5초 앞으로 가기 및 뒤로가기 기능도 제공합니다.

https://user-images.githubusercontent.com/17138123/230875708-0b889244-9472-41dd-8017-c50e601e3f5d.mp4

<br>

### 4) 색 강조
색 강조 탭에서는 프레임의 RGB 값들을 설정한 값만큼 높여주거나 줄여주는 기능을 제공합니다.

https://user-images.githubusercontent.com/17138123/230875753-a45eaaca-8c0d-41d2-98e9-053b6c04b600.mp4

<br>

### 5) 밝기 조절
밝기 조절 탭에서는 RGB 값을 동일한 값만큼 전체적으로 더하거나 빼주는 기능을 제공합니다.

https://user-images.githubusercontent.com/17138123/230875941-8796b3dd-4db3-4a79-8be4-3459eae7b804.mp4

<br>

### 6) 대비 조절
대비 조절 탭에서는 BGR 형식을 LAB 형식으로 변환하여 명도를 담당하는 L의 값을 CLAHE를 적용하여 대비를 조절하는 기능을 제공합니다.

https://user-images.githubusercontent.com/17138123/230876259-39acfd1d-8f9c-47a9-b481-6dba5e034cb7.mp4

<br>

### 7) 선명도 및 필터 효과
선명도 및 필터 효과 탭에서는 GaussianBlur를 이용하여 부드럽거나 날카로운 느낌을 주는 기능을 제공합니다. 또한 BGR 형식을 HSV 형식으로 변환하여 값들을 변경하는 방식을 이용해 회색조, 따뜻하게, 차갑게, 화사하게와 같은 색감을 입히는 기능도 제공합니다.

https://user-images.githubusercontent.com/17138123/230876757-3154805f-f5c9-4dae-aac2-e2cde9a6f97a.mp4

| 회색조 | 따뜻하게 |
| --- | --- |
| ![필터효과_회색조](https://user-images.githubusercontent.com/17138123/230878597-81a52768-b066-4b79-9c36-9be6295b72a9.png) | ![필터효과_따뜻하게](https://user-images.githubusercontent.com/17138123/230878617-ac050b39-f77d-4128-9aec-f84cc345c27e.png) |
| <div align="center"><strong>차갑게</strong></div> | <div align="center"><strong>화사하게</strong></div> |
| ![필터효과_차갑게](https://user-images.githubusercontent.com/17138123/230878628-0b1d4a2d-27cb-4c9a-8626-e1451c0719a4.png) | ![필터효과_화사하게](https://user-images.githubusercontent.com/17138123/230878633-4de2e3a2-2237-477d-9493-9e04821cf708.png) |

<br>

### 8) 크로마키
크로마키 탭에서는 BGR 형식을 HSV로 변환 후 색상, 채도, 명도의 범위를 지정하여 마스크를 만들어 합치는 방식으로 크로마키 기능을 제공합니다. 

https://user-images.githubusercontent.com/17138123/230876816-8ed9024d-966c-44dc-a3ac-196765881322.mp4

<br>

### 9) 화면 전환
화면 전환 탭에서는 Fade-In, Fade-Out 효과를 원하는 시간만큼 줄 수 있는 기능을 제공합니다. 검은색 Mat 객체를 생성 후 addWeight() 함수를 이용하여 가중치를 조절하여 더해주는 방식을 이용하였습니다.

https://user-images.githubusercontent.com/17138123/230876863-fb983144-5a4e-4ff0-8ca0-f174d19c3a9a.mp4

<br>

### 10) 이미지 추가
이미지 추가 탭에서는 원하는 이미지를 원하는 위치와 크기로 설정하여 영상에 추가할 수 있는 기능을 제공합니다. Mat 객체를 다른 Mat 객체의 특정 위치에 특정 크기로 붙여넣는 방식으로 구현하였습니다.

https://user-images.githubusercontent.com/17138123/230877069-cdc5f8e1-e2e7-4327-a650-6b43aaa1a6c2.mp4

<br>

### 11) 자막 추가
자막 추가 탭에서는 시스템에 있는 폰트를 이용할 수 있고 원하는 색상 및 크기로 영상에 자막을 넣는 기능을 제공합니다. 이는 한글 지원을 위해 OpenCV Mat 객체를 Qt의 QImage로 변환 후 글자를 넣고 다시 Mat 객체로 변환하는 방식으로 구현하였습니다.

https://user-images.githubusercontent.com/17138123/230876992-9dbbac75-b595-4873-bf60-e2692f57e02e.mp4

<br>

### 12) 영상 추가
영상 추가 탭에서는 현재 편집 중인 영상의 특정 위치에 새로운 영상을 추가할 수 있는 기능을 제공합니다. 새롭게 추가되는 영상의 너비, 높이, FPS 값은 최초 선택했던 영상을 기준으로 적용됩니다.

https://user-images.githubusercontent.com/17138123/230877033-14f60d30-665f-44ac-bd40-a71654786c40.mp4

<br>

### 13) 영상 자르기
영상 자르기 탭에서는 편집 중인 영상의 특정 구간을 잘라내는 기능을 제공합니다.

https://user-images.githubusercontent.com/17138123/230882223-2fa711a5-e96b-4af2-a7b9-c088bc2980c9.mp4

<br>

### 14) 영상 속도 조절
영상 속도 조절 탭에서는 편집 중인 영상의 속도를 조절하는 기능을 제공합니다. 모든 프레임 영역에 대해서 프레임 속도를 변경할 경우 FPS를 줄이거나 늘리는 방식을 적용하고, 일부 영역의 속도만 변경할 경우에는 그 영역에 해당되는 프레임의 일부를 제거하거나 복사해서 추가하는 방식으로 구현하였습니다.

https://user-images.githubusercontent.com/17138123/230876977-686b1232-27fa-44b1-b6fd-9368c97b57b9.mp4

<br>

### 15) 영상 인코딩
영상 인코딩은 EVE 좌측 상단에 있는 메뉴를 통해 진행할 수 있으며 mp4, avi, wmv, mov 포맷으로 저장이 가능합니다.

https://user-images.githubusercontent.com/17138123/230876953-6503aa88-0a59-43fe-a7d9-21ce7b7345c7.mp4
