# 🗡️ ProjectCZelda

**콘솔에서 구현한 젤다풍 액션 RPG 프로젝트**

---

## 📌 프로젝트 개요

`ProjectCZelda`는 콘솔 환경에서 작동하는 젤다 스타일의 2D RPG 게임입니다.  
플레이어는 맵을 탐험하고 몬스터를 처치하며, 다양한 상호작용과 시스템을 통해 RPG 세계를 경험합니다.  
주요 특징은 싱글톤 매니저 구조, 시간 제어 기반의 업데이트 루프, 몬스터 생성 및 상호작용 시스템 등입니다.

---

## 🧩 클래스 구조 요약

### 📦 엔티티 및 액터
- **Entity** : 모든 객체의 기본 클래스 (플레이어, 몬스터, 아이템 등)
- **Actor** : `Entity`를 상속, 이동/상호작용이 가능한 캐릭터
- **Item** : 필드에 생성되는 아이템들의 기반 클래스

### ⚙️ 매니저
- **GameManager** : 게임 루프 플래그 및 흐름 제어
- **EntityManager** : 모든 엔티티의 생성, 관리
- **MapManager** : 맵 데이터 생성 및 위치 체크
- **UpdateManager** : 플레이어 및 몬스터의 상태 갱신
- **InputManager** : 입력 처리 담당
- **TimeManager** : 프레임 단위 시간 제어
- **TileCollector** : 특정 타일 수집 로직 담당
- **StartScreen** : 시작화면 로직 포함
- **Utill** : 유틸리티 함수 모음

---

## 🔁 게임 루프

```mermaid
flowchart TD
    A[main()] --> B[Game()]
    B --> C[Init()]
    C --> D[싱글톤 매니저 초기화]
    D --> E[EntityManager로 플레이어 생성]
    E --> F[TimeManager 루프 시작]
    F --> G[PlayerUpdate() - 스레드 루프]
    G --> H[UpdateManager::UpdatePlayer()]
    F --> I[Update() - 일정 프레임마다 몬스터 업데이트]

---

## ▶️ 실행 방법

1. Visual Studio 등 C++ 빌드 환경에서 `ZeldaRun.cpp`를 실행 파일로 컴파일
2. 콘솔에서 실행
3. 방향키 입력 및 게임 진행

---

## 📝 현재 미구현 또는 개선 예정 사항

- 게임 종료 조건 및 결과 화면
- 저장/불러오기 기능
- 미니맵 구현
---

## 🙌 Special Notes

- 모든 매니저는 싱글톤 또는 static 구조로 설계되어 전역 접근을 쉽게 합니다.
- 구조적 분리를 고려하여 각 컴포넌트를 최대한 독립적으로 설계하였습니다.
