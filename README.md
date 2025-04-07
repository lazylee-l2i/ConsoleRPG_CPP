# ProjectCZelda

> 🎮 콘솔 기반 C++ RPG 프로젝트

## 📌 1. 프로젝트 개요

- **언어**: C++14  
- **개발 환경**: Visual Studio 2022  
- **실행 방식**: Windows 콘솔  
- **설명**:  
  고전 RPG 스타일의 콘솔 게임으로, 플레이어와 몬스터, NPC, 아이템 간의 상호작용을 통해 맵을 탐험하고 퀘스트를 완료하는 시스템을 구현했다.

---

## 🧩 2. 클래스 설명

### 2-1. Entity 클래스

#### 🔹 Actor
- 플레이어, 몬스터, NPC를 모두 포함하는 추상 클래스
- 주요 속성: `name`, `attack`, `hp`, `Pos`, `direction`
- 주요 기능:
  - `Move()`, `SetHP()`, `GetDirectionByPos()` 등

#### 🔹 Item
- 드롭 가능한 필드 아이템 객체
- 주요 속성: `name`, `effectValue`, `stackSize`, `stackCount`, `itemPos`
- 주요 기능:
  - 회복 아이템(`heart`), 퀘스트 아이템(`quest`) 구현

#### 🔹 Pos (Struct)
- 좌표 정보 (`x`, `y`)
- 연산자 오버로딩을 통해 위치 비교, 이동 연산 지원

---

### 2-2. Manager 클래스

#### 🎮 GameManager
- 게임의 핵심 컨트롤러
- 기능:
  - `InsertActorInMap()`, `AutoGenerateMonster()`, `SpawnItemAfterMonsterDead()`
  - Actor 및 Item 객체 생성/소멸 관리

#### 🗺️ MapManager
- 맵 구조 관리 및 출력 담당
- 기능:
  - `GenerateMap()`, `ShowMap()`, `EntityObstacleCheck()`
  - 맵 내부의 이동, 장애물 체크, 엔티티 배치 구현

#### 🔄 UpdateManager
- 입력과 행동 반영 처리
- 기능:
  - `PlayerUpdate()`, `MonsterUpdate()`, `NPCUpdate()`

#### 🤝 InteractionManager
- 충돌 및 상호작용 처리
- 기능:
  - `CheckUserCollision()`, `UserAttackMonster()`, `CheckMonsterCollision()`

---

## 🧭 3. 전체적 워크플로우

```mermaid
flowchart TD
    Start[게임 시작] --> Init[Manager 초기화]
    Init --> Input[입력 처리 (UpdateManager)]
    Input --> Action[행동 업데이트]
    Action --> Collision[충돌 및 상호작용 체크 (InteractionManager)]
    Collision --> MapRender[맵 렌더링 (MapManager)]
    MapRender --> Loop[게임 상태 확인 및 루프]
    Loop -->|계속| Input
    Loop -->|게임 종료| End[게임 종료 및 메모리 정리]
```

---

## ⚠️ 4. 미흡한 점 및 마무리

- `MapManager`의 렌더링이 복잡하고 느림 → 최적화를 시도했지만 대규모 맵에서 성능 저하가 존재
- Entity 데이터를 `map`, `vector`로 분산하여 관리함으로써 접근성이 혼란스러움
- `InteractionManager`와 `UpdateManager`의 기능이 명확히 분리되지 않은 구조
- 향후 개선 방향:
  - WinAPI 기반 GUI 렌더링으로 전환 고려
  - Entity 통합 컨테이너 구조 재설계
  - 컴포넌트 기반 Actor 구성 시도