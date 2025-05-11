# Study_InventorySystemDesign

**Unreal Engine 5.4.4 기반의 인벤토리 + 퀵슬롯 시스템 설계 실습 프로젝트**

## 🎯 학습 목표

- 구조적이고 확장 가능한 인벤토리 시스템 구현
- UI 연동, 정렬 및 슬롯 자동 배치 등 실전 기능을 기반으로 설계 능력 향상
- OOP 원칙에 따라 컴포넌트 중심으로 시스템을 분리하고 관리
- 

## 🧩 시스템 구성

### 📦 핵심 구조

- `FInventoryItem`, `EItemType` 구조체 + 열거형 설계
- `UInventoryComponent`: 아이템 저장, 슬롯 관리, 중복 처리
- `TArray`, `TMap` 기반 정렬/탐색 시스템

### 🎮 아이템 획득 및 드랍

- `AItemBase`: 픽업 대상 액터 클래스
- `OnOverlap`, `Interact()` 방식으로 아이템 획득 처리
- `DropItem()` 호출 시 아이템 월드 스폰 구현

### 🧠 UI 출력 시스템

- `UInventoryWidget`, `UQuickSlotWidget`: 인벤토리/퀵슬롯 전용 위젯 설계
- 슬롯 위젯 아이콘, 수량 표시
- InputAction 기반 위젯 열기/닫기 처리
- Delegate 연동을 통한 실시간 UI 동기화

### 🔁 슬롯 자동 배치 및 정렬

- 비어 있는 슬롯 자동 탐색 후 아이템 배치
- 정렬 기준: 아이템 타입, 이름, 획득 순서
- TMap 또는 커스텀 비교 함수 기반 정렬 로직 설계

---

## ✅ 현재 구현된 기능

- [x] 인벤토리 슬롯 시스템 완성
- [x] 퀵슬롯 UI 및 기능 구현
- [x] 아이템 획득 및 드랍 로직 구축
- [x] 슬롯 정렬 및 자동 배치 시스템
- [x] Delegate 기반 실시간 UI 연동
- [ ] SaveGame 연동 (예정)
- [ ] 상점 / 퀘스트 연계 (예정)

---

## 🛠 기술 스택

- Unreal Engine 5.4.4 (C++)
- 구조체/열거형 기반 데이터 설계 (`FInventoryItem`, `EItemType`)
- Delegate 및 컴포넌트 중심 아키텍처
- UMG 기반 UI 연동

---

## ✍ Author
  **JellytoCodes / 2025.05**
