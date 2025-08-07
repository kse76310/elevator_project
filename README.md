요청하신 내용을 바탕으로 중복된 부분을 정리하고 마크다운 형식으로 만들어 드립니다.

***

### 💡 프로젝트 개요 및 목표

> 📢 효율적인 운행 알고리즘을 설계하고 구현하며, 하드웨어 직접 제어를 통해 펌웨어 개발 역량을 강화합니다.

### 📢 담당 역할

> Datasheet를 참고하여 LCD 드라이버를 개발하고, 하드웨어 설계 연결 및 동작을 검증했습니다.

### [ 구상도 ] - kicad
<img width="1660" height="1174" alt="image" src="https://github.com/user-attachments/assets/4c3c3242-2f27-4bbe-8dd6-d9ed29a72bfd" />

---

### 사용 기술

| Language | Hardware | OS |
| :--- | :--- | :--- |
| C | STM32 | FreeRTOS |

### 주요 역할 및 기여

#### [ 운행 알고리즘 ]

-   진행 방향을 우선으로 하여 층을 서비스하도록 설계했습니다.
-   **예시:** 5층에서 7층으로 상승 중 3층과 9층의 요청이 들어오면, **7층 → 9층 → 3층** 순서로 이동합니다.

#### [ RTOS 기반의 다중 작업 처리 ]

-   RTOS를 사용하여 모터 제어, 버튼 입력 확인, 다중 디스플레이(LCD, FND, Dot Matrix) 출력, 부저 알림 등의 기능들이 서로 영향을 주지 않고 원활하게 동시에 작동하도록 구현했습니다.

### [ 결과 ]
<img width="278" height="441" alt="스크린샷 2025-07-08 194026" src="https://github.com/user-attachments/assets/aeb2151f-1210-489d-a2d5-696409c26996" />
<img width="620" height="436" alt="스크린샷 2025-07-28 212051" src="https://github.com/user-attachments/assets/c339f380-2a42-44fe-b922-4e827c2f37dc" />

