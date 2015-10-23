현재 실행중인 프로세스의 목록을 출력하여 한 눈에 확인 할 수 있다. 
프로세스명, 프로세스 아이콘, cpu, memory 점유도, path, pid, company, description, Virus Total 검사 정보

virustotal을 이용하여 주기적으로 malware 탐색
	- hash값 비교를 통해 기존에 분석을 했던 프로세스는 검사하지 않도록 하여 cost 낮춤

하이라이팅을 통해 유용한 정보들을 쉽게 확인 할 수 있다.
	- user process, system process의 구분
	- cpu, memory 점유도가 특이한 경우
	- malware라고 의심되는 프로세스
	- 실행되거나 종료되는 프로세스

특이 사항에 대한 로깅 및 리포팅
	다음과 같은 프로세스에 대해 log를 확인 할 수 있다.
	또한 sms 또는 email과 같은 방법으로 리포팅을 한다.
	- cpu, memory 점유도가 특이한 프로세스
	- malware라고 의심되는 프로세스

Menu
	- 파일     > 종료
	- 프로세스 > kill Process
		   > Check Virus Total
		   > Search Online(검색엔진을 통한 검색)
	- 사용자   > report(이메일, sms번호등 지정)
	- 도움말   > help
		   > about(제작자, version등)

accelerator(단축키)
	- 파일     > 종료(x)
	- 프로세스 > kill Process(Del)

context menu(우클릭)
	- 프로세스 컬럼 > kill Process(Del)
	- 프로세스 컬럼 > Check Virus Total
	- 프로세스 컬럼 > Search Online
