# Not Mini Shell

예를 들면 echo "hello world" | wc -l 이라는 입력이 들어오면  
| 단위로 먼저 스플릿을 하고  
그 다음 echo, "hello world"를 나누고 wc, -l을 나눕니다  


char **cmds라는 배열에 {"echo", "hello world"}라는 char ** 변수와  
{"wc", "-l"} char ** 변수를 넣고 있습니다.


제가 편하기 위해서인데 그래서 set_pipes 함수가 char ***을 매개변수로 바꾸면  
바로 사용이 가능한 상태입니다.


제가 약간 바꿔서 사용한 코드를 parse.c에 넣었습니다.  
궁금하신게 있으면 연락주세요!!