# rouge 구현

### 구현된 기능
- 절차적 생성 알고리즘을 이용한 랜덤 맵 생성
- 기본적 전투(일방향), 던전탈출
- 금수집
- 몬스터, 몬스터 인공지능

### 프로젝트 구조
```
include/
- findpath.h - 길찾기알고리즘&우선순위큐
- inventory.h - 인벤토리
- item.h - 아이템 데치터
- map.h - 맵 자동생성 & 업데이트
- monster.h - 몬스터 인공지능,
- util.h - 기타 쓸만한 함수들
- vector.h - 동적 크기 배열
src/
- 위 헤더에 대한 구현
- main.c
```

### 세부적인것들

#### main.c

기본적인초기화, 몹생성과

다음과 같은 루프를 구성한다.

player_info()
print_map()
move()
attack() - 실질적인 판정

#### findpath.c

- pq_create() - 우선순위 큐 노드 생성
- pq_destroy() - 노드 할당 해제
- pq_enque() - 힙 트리 구성
- pq_swap_node() - 두노드를 서로 바꾼다.
- pq_dequqeue() -  힙트리에서 최소값을 뺀다.
- huristic() - A*알고리즘에서 휴리스틱 값을 구하는 함수(맨해튼 거리)
- findpath() - 각 방에 존재하는 문을 다른 방의 문과 잇기위해 A*알고리즘을 이용해 최단거리를 구한다.(힙트리기반)

#### map.c
- updateParam() - 방의 최대 개수 수정.
- allocate_room() - 방 구조체를 하나 생성한다.
- initRooms() - 방 구조체 초기화
- isBlock() 방이 유효한지 확인한다.
- drawRoom() - 방 구조체를 참고해 실제로 방을 2차원 배열상에 그린다.
- generate_map() -  위 함수들을 묶어 하나의 맵을 생성한다.
- print_map() - 맵을 표현한다.
### 구현&수정할것
- 게임오버
- 맵생성 알고리즘 수정
- 인벤토리
- 아이템 수집
- 다음 던전으로 넘어가기
- 레벨업
- 불필요한 코드 제거, 메모리 누수 해결
