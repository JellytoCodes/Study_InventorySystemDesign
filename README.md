# 🧪 Study_InventorySystemDesign
**Unreal Engine 5.4.4 기반의 학습용 실험 프로젝트**  

**"이 기능을 이러한 구조로 만든 이유"라는 목적에 중점을 둔 구조 설계형 인벤토리 시스템입니다.**

<br>

## ✏️ 학습 목적
> 본 프로젝트는 Unreal Engine의 구조적 설계 원칙을 바탕으로 **구현 명확성, 시스템 확장성, 책임 분리**에 중점을 둔 구조 설계 기반 프로젝트를 완성했습니다.  

<br>

## 📐 적용 설계 원칙
**📚 SRP (단일 책임 원칙)**  
&nbsp;&nbsp;&nbsp;→ AItemBase는 상호작용과 월드 오브젝트 역할에 집중하며 UInventoryComponent는 아이템의 데이터 관리 전반을 전담할 수 있도록 설계하였습니다.

**📚 DIP (의존성 역전 원칙)**  
&nbsp;&nbsp;&nbsp;→ UI와 시스템 로직은 서로 직접 의존하지 않고 Delegate를 통해 비동기적으로 연결되는 구조를 설계하였습니다.
 
**📚 LSP (리스코프 치환 원칙)**  
&nbsp;&nbsp;&nbsp;→ 구조체 기반 시스템 설계에서 FInventoryItem과 FItemDataRow는 동일한 방식으로 각 위젯에 전달 및 처리되며 이들에 대한 기능 호출은 별도의 타입 구분 없이 일관되게 작동하도록 설계하였습니다.

**📚 ISP (인터페이스 분리 원칙)**  
&nbsp;&nbsp;&nbsp;→ UI 위젯 클래스들은 각자 필요한 동작(슬롯 출력, 정렬 선택, 하이라이트 등)에만 집중되어 있으며 불필요한 의존 없이 명확한 목적에 따라 인터페이스를 분리해 구성되게 설계하였습니다.

**📚 OCP (개방-폐쇄 원칙)**  
&nbsp;&nbsp;&nbsp;→ 새로운 아이템 타입을 추가하거나 행동을 확장할 때 기존 분기문을 수정하지 않고 TMap<EItemType, FItemActionDelegate> 구조에 Delegate만 등록하면 행동이 자연스럽게 확장되도록 설계하였습니다.

**📚 Event-Driven**  
&nbsp;&nbsp;&nbsp;→ DesignOnInventoryUpdated 같은 Delegate 이벤트를 통해 인벤토리 상태가 변할 때마다 여러 위젯 시스템이 자동으로 갱신되도록 구성하였습니다. 

**📚 Data-Driven Flow**  
&nbsp;&nbsp;&nbsp;→ 아이템 속성, 분류, 가격 등 모든 메타데이터는 ItemMasterTable이라는 DataTable을 통해 외부에서 정의됩니다.  
&nbsp;&nbsp;&nbsp;→ 로직은 이 데이터를 기반으로 유연하게 동작합니다.새로운 아이템 타입을 추가하거나 행동을 확장할 때 기존 분기문을 수정하지 않고 행동이 자연스럽게 확장되도록 설계했습니다. 

<br>

## 📂 시스템 아키텍처 요약
**🧱 Character**  
&nbsp;├──ItemType을 기반으로 각 행동(공격, 소비, 설치 등)을 Delegate로 등록 및 실행  
&nbsp;└──퀵슬롯에서 선택한 아이템을 EquippedItem으로 설정하고 행동에 연동  

**🧱 InventoryComponent**  
&nbsp;├──TMap<FName, FInventoryItem> 기반의 인벤토리 구조 관리  
&nbsp;└──아이템 추가/제거/드랍 처리 및 OnInventoryUpdated를 통해 외부 통신  

**🧱 ItemDBSubsystem**  
&nbsp;├──모든 아이템 데이터를 중앙화하여 관리  
&nbsp;└──ItemID를 기반으로 아이템 속성 조회 및 로직 분리  

**🧱 InventoryWidget**  
&nbsp;├──인벤토리 슬롯을 UniformGridPanel로 출력  
&nbsp;└──ComboBoxString을 통해 정렬 기준을 선택 가능 (이름, 수량, 타입, 가격)  

**🧱 QuickSlotWidget**  
&nbsp;├──고정 10칸 구성  
&nbsp;└──현재 선택된 슬롯을 강조 표시하며, Delegate를 통해 행동 연계 가능  


## ⚙️ 핵심 구현 사항 (완료 항목)
- [X] **인벤토리 전반 흐름 구현**  
 → 아이템 획득 시 AItemBase::OnPickedUp() → InventoryComponent::AddItem() 호출  
 → DropItem()을 통해 아이템 월드에 드롭 및 RemoveItem() 호출  

- [X] **UI 동기화 처리**  
 → 아이템 아이콘 및 수량을 FItemDataRow 기반으로 출력  
 → 수량이 1개일 경우 텍스트 생략 처리  
 → 퀵슬롯은 실시간 업데이트 및 현재 선택 슬롯 강조 처리  

- [X] **정렬 시스템 구성**  
 → 콤보박스를 통해 유저가 원하는 정렬 방식 선택 가능  
 → InventoryComponent::SortItems() 호출로 리스트 재정렬  
 → 정렬 기준: 이름, 수량, 아이템 타입, 가격  

- [X] **Delegate 기반 행동 처리**  
 → EItemType → 행동 함수로의 Delegate 매핑  
 → 캐릭터는 장착 아이템의 ItemType을 기준으로 적절한 Delegate 호출  
 → 행동 분기 로직이 캐릭터 내부에 직접 고정되지 않고 유연하게 확장 가능  


## 🧑‍💻 Author
  **JellytoCodes / 2025.05**

