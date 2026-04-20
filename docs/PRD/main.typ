#import "template.typ": *
#import "utils.typ": *

#show: project.with(title: title, authors: authors)

= 시스템 구성
== UI 구성 및 기능

== 데이터 파일
=== Schedule
`schedule.json` 파일은 일정 데이터를 저장하는 JSON 형식의 파일입니다. 각 일정 항목은 다음과 같은 구조를 가집니다:

#prompt([
  ```json
  {
    "id": "unique-identifier",
    "title": "일정 제목",
    "description": "일정 설명",
    "start_time": "2026-04-20T09:00:00",
    "end_time": "2026-04-22T17:00:00",
  }
  ```
])


= 컨벤션
== 네이밍 컨벤션
=== 변수
- *UI 오브젝트 이름*
  - 위젯 이름을 축약하여 앞에 붙여 `camelCase`로 작성합니다.
  - 예시: `btnAdd`, `lblTitle`
- *일반 변수*
  - `camelCase`로 작성합니다.
=== 클래스
- `PascalCase`로 작성합니다.
=== 함수
- `camelCase`로 작성합니다.
=== 파일 및 디렉토리
- `snake_case`로 작성합니다.
== 스타일
- 가독성을 위해 *한 줄에 하나의 문장*만 작성합니다.
- 주석은 설명하려는 *구문에 맞춰 들여쓰기* 합니다.
#prompt([
  ```c++
  // Good
  function someFunction() {
  ...

    // statement에 관한 주석
    statements
  }
  ```
])
- *연산자 사이*에는 *공백을 추가*하여 가독성을 높입니다.
#prompt([
  ```c++
  a+b+c+d // bad
  a + b + c + d // good
  ```
])
- *콤마 다음*에 값이 올 경우 *공백을 추가*하여 가독성을 높입니다.
#prompt([
  ```c++
  int arr[3] = {1,2,3}; // bad
  int arr[3] = {1, 2, 3}; // good
  ```
])
- *중괄호*는 함수 선언부의 *같은 줄*에 작성합니다.
#prompt([
  ```c++
  // Good
  void someFunction() {
    ...
  }
  // Bad
  void someFunction()
  {
    ...
  }
  ```
])

= 작업 분담 및 일정
== 분담
- 김정운
  - 일정 관리 Dialog UI
  - 일정 추가, 수정, 삭제 기능 연결
- 윤찬규
  - MainWindow UI
  - 일정 데이터 파일 입출력 기능
  - 일정 리스트 검색 및 갱신
== 일정
- `04.20`: UI 설계 및 기본 CRUD 기능 구현
- `04.21`: 데이터 파일 입출력 연결
- `04.22`: 프로젝트 완성 및 최종 점검
== GitHub
